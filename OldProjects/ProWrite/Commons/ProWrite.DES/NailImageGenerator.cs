//---------------------------------------------------------------------
//
// File: NailImageGenerator.cs
//
// Description:
// Helper 
//
// Author: Jerry Xu
// Modify histories:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

namespace ProWrite.DES
{
    public class NailImageGenerator : IBatchLoadGenerator
    {
        public ShapeLayer[] Layers { private get; set; }
        public Control HWnd { private get; set; }
        public int Tick { private get; set; }
        public Image NailImage { get; private set; }

        private DESHelper helper = new DESHelper();

        public void Generate()
        {
            Check.Require(Layers, "Layers", Check.NotNull);
            Check.Require(Layers.Length, "Layers.Length", Check.GreaterThan<int>(0));
            Check.Require(HWnd, "HWnd", Check.NotNull);
            Check.Require(Tick, "Tick", Check.GreaterThanOrEqual<int>(0));

            var layers = helper.PopulateDataBatchLoad(Layers);
            layers.BackColor = HWnd.BackColor;
            //layers.VideoSize = new Size(ControlService.SignCombo.Current.Width, ControlService.SignCombo.Current.Height);
            layers.VideoSize = HWnd.Size;
            layers.Sort(new SortComparer<Layer>("Level", false));
            var DynamicTextDS = layers.FindAll(item => { return item.LayerType == LayerType.DynamicText; });
            if (layers.Count == 0)
            {
                //TODO:
                var img = new Bitmap(HWnd.Width, HWnd.Height);
                using (var g = Graphics.FromImage(img))
                {
                    g.Clear(HWnd.BackColor);
                }
                NailImage = img;
                return;
            }

            //using (var des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, HWnd.Width, HWnd.Height, layers))
            var des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, layers.VideoSize.Width, layers.VideoSize.Height, layers);
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
                        catch
                        {
                        }
                    };
                    des.Completed += onCompleted;
                    pnl.Width = layers.VideoSize.Width;
                    pnl.Height = layers.VideoSize.Height;
                    des.RenderToFrame(pnl, callback, null, DynamicTextDS, DsRect.FromRectangle(HWnd.ClientRectangle), 0, layers.PlayLength);
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
                catch
                {
                    des.Cancel();
                }

            }
        }

        private static readonly NailImageGenerator Instance = new NailImageGenerator();

        public static Image GenerateNailImage(ShapeLayer[] layers, Control hwnd, int tick)
        {
            Instance.Layers = layers;
            Instance.HWnd = hwnd;
            Instance.Tick = tick;

            Instance.Generate();

            return Instance.NailImage;
        }

        public void GenerateBatchLoad(MessageInfo message)
        {
            Check.Require(message, "MessageInfo", Check.NotNull);

            var layers = helper.PopulateDataBatchLoad(message.Items);
            layers.BackColor = message.BackColor;

            layers.VideoSize = message.Size;
            layers.Sort(new SortComparer<Layer>("Level", false));
            var DynamicTextDS = layers.FindAll(item => { return item.LayerType == LayerType.DynamicText; });
            if (layers.Count == 0)
            {
                //TODO:
                var img = new Bitmap(message.Size.Width, message.Size.Height);
                using (var g = Graphics.FromImage(img))
                {
                    g.Clear(message.BackColor);
                }
                NailImage = img;
                return;
            }
            NailImage = Image.FromFile(layers[0].FilePath);
                NailImage.Save("c:\\1.jpg");

      
        }

        public static Image GenerateNailImage(MessageInfo message)
        {
            //Instance.Layers = message.Items;
            Instance.GenerateBatchLoad(message);

            return Instance.NailImage;
        }

        public void GenerateNailImageBatchLoad(MessageInfo message)
        {
            Image img = NailImageGenerator.GenerateNailImage(message);
            if (img != null)
            {
                message.ImagePath = Constance.LibraryNailImageDir + DateTime.Now.Ticks.ToString() + ".bmp";
                IOHelper.SaveImage(img, message.ImagePath);
            }
        }
    }
}
