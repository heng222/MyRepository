using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using System.Drawing;
using System.Drawing.Imaging;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.Entity;
using ProWrite.Entity.DES;
using DirectShowLib;
using ProWrite.UFE;
using ProWrite.UFE.Entity;
using System.Threading;
using ProWrite.Entity.Shape.Visitor;

namespace ProWrite.DES
{
    public interface IMessageInspector:IConverter<KeyValuePair<SignInfo,MessageInfo>,MessageInfo>
    {

    }

    public class VideoInspector : ConverterBase<KeyValuePair<SignInfo, MessageInfo>, MessageInfo>, IMessageInspector
    {
        private VideoInspector() { }

        public static readonly IMessageInspector Instance = new VideoInspector();

        public override MessageInfo Convert(KeyValuePair<SignInfo, MessageInfo> ctx)
        {
            MessageInfo target = ctx.Value.Copy() as MessageInfo;
            target.ReverseItems();

            var count = 0;
            var videoLayers = (from l in target.Items
                               let shapeImage = l.Shape as ShapeImage
                               let i = count++
                               where l.Shape.LayerType == LayerType.Video
                               || (shapeImage != null 
                                    && shapeImage.IsGif 
                                    && IOHelper.GetImageFromFile(shapeImage.ImageUrl).IsMultiFrameImage())
                               select new { Layer = l, Index = i }).ToArray();

            if (videoLayers == null || videoLayers.Length < 1)
            {
                PopulateSignSize(target, ctx.Key);
                return target;
            }

            var layers = new ShapeLayer[videoLayers.Length];
            for (int i = 0; i < videoLayers.Length; i++)
            {
                layers[i] = videoLayers[i].Layer;
                target.Delete(layers[i]);
            }

            target.Insert(MergeVideoLayers(target,layers), videoLayers[0].Index);

            return target;
        }

        private static void PopulateSignSize(MessageInfo source, SignInfo sign)
        {
            var sourceSize = source.Items[0].Shape.SignSize;

            if (sourceSize.Height != sign.Height || sourceSize.Width != sign.Width)
            {
                ResetSignVisitor.Instance.Sign = sign;
                source.Accept(ResetSignVisitor.Instance);
            }
        }

        private ShapeLayer MergeVideoLayers(MessageInfo mes, ShapeLayer[] videoLayers)
        {
            string fileID = Guid.NewGuid().ToString().Replace("-", "");
            string fileName = LocalFilePathMapping.GetFile(FileType.Video, fileID);

            var layers = new VideoLayerCollection();
            Layer layer = null;
          

            long minStartTime = 0;
            long maxEndTime = 0;

            Array.ForEach<ShapeLayer>(videoLayers, item =>
            {
                layer = DESLayerConverter.Instance.Convert(item);
                //comment out by Louis,for change video start time same as video layer's start time
                //layer.Level++;

                if (layer.Level == 0)
                {
                    minStartTime = layer.StartTime;
                    maxEndTime = layer.EndTime;
                }
                else
                {
                    if (layer.StartTime < minStartTime)
                        minStartTime = layer.StartTime;
                    if (layer.EndTime > maxEndTime)
                        maxEndTime = layer.EndTime;
                }

                layer.Rect = new System.Drawing.Rectangle(layer.Rect.X / mes.Zoom, layer.Rect.Y / mes.Zoom, layer.Rect.Width / mes.Zoom, layer.Rect.Height / mes.Zoom);
                layers.Add(layer);
            });

            layers.BackColor = mes.BackColor;
            layers.SignType = SignType.RGB;
            layers.VideoSize = videoLayers[0].Shape.SignSize;
            layers.Name = mes.Name;
            layers.Zoom = 1;

            layers.PlayLength = maxEndTime - minStartTime;


            layers.ParentName = "";
            layers.EmphasisEffect = mes.EmphasisEffect;
            if (layers.Count > 1)
                layers.Sort(new SortComparer<Layer>("Level", false));
           
            IBaseFilter ibfVideoCompressor = DESHelper.GetVideoCompressor("Indeo?video 5.10 Compression Filter");
            PlayState state = ProWrite.Core.PlayState.Stop;

            var des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, layers.VideoSize.Width, layers.VideoSize.Height, layers);
            des.Completed += (s,e)=>  state = PlayState.Stop;
            des.RenderToVideo(MediaSubType.Mpeg2Video, fileName, ibfVideoCompressor, null, null, null, new List<Layer>(), 0, mes.Length, layers.VideoSize);
            des.StartRendering();

            state = PlayState.Run;
            while (state == PlayState.Run)
                Thread.Sleep(100);

            des.Dispose();
            des = null;

            var newLayer = videoLayers[0].Copy();
            ShapeVideo shape = newLayer.Shape as ShapeVideo;
            if (shape == null)//shape.Type == Gif
            {
                shape = new ShapeVideo();
                shape.FromTo(newLayer.Shape);
                newLayer.Shape = shape;
            }

            shape.VideoFileID = fileID;
            shape.VideoUrl = fileName;

            newLayer.EntryEffect = LayerEffect.Empty;
            newLayer.ExitEffect = LayerEffect.Empty;
            newLayer.EmphasisEffect = LayerEffect.Empty;
            newLayer.EmphasisEffect.Left = (int)minStartTime * Constance.Effect.UnitWidth;
            newLayer.EmphasisEffect.Width = (int)maxEndTime * Constance.Effect.UnitWidth;

            return newLayer;
        }

        
    }

    public static class GifExtensions
    {
        public static bool IsMultiFrameImage(this Image gif)
        {
            return gif.GetFrameCount(new FrameDimension(gif.FrameDimensionsList[0])) > 1;
        }
    }
}
