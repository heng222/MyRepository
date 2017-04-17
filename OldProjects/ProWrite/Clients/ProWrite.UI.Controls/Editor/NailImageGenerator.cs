using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.DES;
using System.Drawing;
using System.Threading;
using DirectShowLib;

namespace ProWrite.UI.Controls.Editor
{
    public class NailImageGenerator : IGenerator
    {
        public VideoLayerCollection Layers { private get; set; }
        public int Tick { private get; set; }
        private Rectangle ClientRectangle;
        public Image NailImage { get; private set; }

        private LayerHelper helper = new LayerHelper();

        public void Generate()
        {
            Check.Require(Layers, "Layers", Check.NotNull);
            Check.Require(Layers.Count, "Layers.Count", Check.GreaterThan<int>(0));
            Check.Require(Tick, "Tick", Check.GreaterThanOrEqual<int>(0));

            ILog _log = LogManager.GetLogger(typeof(IOHelper));

            Layers.Sort(new SortComparer<Layer>("Level", false));
            var DynamicTextDS = Layers.FindAll(item => item.LayerType == LayerType.DynamicText);
            if (Layers.Count == 0)
            {
                //TODO:
                var img = new Bitmap(Layers.VideoSize.Width, Layers.VideoSize.Height);
                using (var g = Graphics.FromImage(img))
                {
                    g.Clear(Layers.BackColor);
                }
                NailImage = img;
                return;
            }

            var des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, Layers.VideoSize.Width, Layers.VideoSize.Height, Layers);
            {

                int MaxCount = Tick <= 0 ? DESConsts.BitCount : (int)Tick * DESConsts.BitCount;
                ManualResetEvent mre = new ManualResetEvent(false);
                bool hasSign = false;
                try
                {
                    Control.CheckForIllegalCrossThreadCalls = false;
                    Panel pnl = new Panel();
                    var callback = new DESVideoCallBack();

                    EventHandler onCompleted = delegate
                    {
                        if (des != null)
                            des.Dispose();
                        Control.CheckForIllegalCrossThreadCalls = true;
                        if (!hasSign)
                        {
                            hasSign = true;
                            mre.Set();
                        }
                    };

                    callback.OnCallBack = () =>
                    {
                        try
                        {
                            if (callback.m_FrameCount == 5)
                            {
                                des.Pause();
                                hasSign = true;
                                mre.Set();
                            }
                        }
                        catch(Exception e)
                        {

                             _log.Error("Generale ThumNail Exception on callBack.", e);
                             _log.Error(e);
                        }
                    };
                    des.Completed += onCompleted;
                    pnl.Width = Layers.VideoSize.Width;
                    pnl.Height = Layers.VideoSize.Height;
                    des.RenderToFrame(pnl, callback, null, DynamicTextDS, DsRect.FromRectangle(ClientRectangle), 0, Layers.PlayLength);
                    des.StartRendering();
                    des.put_CurrentPosition(Tick);

                    mre.WaitOne();
                    mre.Close();

                    if (des != null && !des.IsDisposed)
                    {
                        NailImage = des.GetImage();
                        des.Cancel();
                    }
                }
                catch(Exception e)
                {
                    _log.Error("Generale ThumNail Exception on general.", e);
                    _log.Error(e);
                    des.Cancel();
                }

            }
        }

        private static readonly NailImageGenerator Instance = new NailImageGenerator();

        public static Image GenerateNailImage(MessageControl msgControl, int tick)
        {
            msgControl.LoadModelInfo();
            var msg = msgControl.Model;
            msg.PlayValue = tick;
            return GenerateNailImage(msgControl.Model, msgControl.ShapeControl.ClientRectangle);
        }

        public static Image GenerateNailImage(MessageInfo msgInfo, Rectangle imageSize)
        {
            //Instance.Layers = Instance.helper.PopulateData(NailImageMessageInspector.Instance.Convert(msgInfo),imageSize);
            Instance.Layers = Instance.helper.PopulateData(msgInfo, imageSize);
            Instance.Tick = msgInfo.PlayValue;
            Instance.ClientRectangle = imageSize;
            Instance.Generate();

            return Instance.NailImage;
        }

    }
}
