using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Entity.Library;
using System.Drawing;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Visitor
{
    public class DesLayerCollectionConverter : ConverterBase<KeyValuePair<MessageInfo,Rectangle>, VideoLayerCollection>
    {
        private short _level = 0;
        

        public override VideoLayerCollection Convert(KeyValuePair<MessageInfo, Rectangle> source)
        {
            _level = 0;

            var msg = source.Key;
            var videoSize = source.Value;

            var layers = source.Key.Items;
            var videoLayers = PopulateData(layers);

            videoLayers.SignType = msg.SignType.Value;
            videoLayers.VideoSize = videoSize.Size;
            videoLayers.BackColor = msg.BackColor;
            videoLayers.Name = msg.Name;
            videoLayers.Zoom = msg.Zoom;
            videoLayers.EmphasisEffect = msg.EmphasisEffect;
            return videoLayers;
        }

        private bool AppendLayer(VideoLayerCollection layers, ShapeLayer layer)
        {
            Layer videoLayer = DESLayerConverter.Instance.Convert(layer); //layer.ToVideoLayer();
            if (videoLayer == null)
                return false;

            videoLayer.Level = _level++;
            layers.Add(videoLayer);
            return true;
        }

        private VideoLayerCollection PopulateData(ShapeLayer[] layers)
        {
            var _videoLayers = new VideoLayerCollection();
            long PlayLength = 0;
            if (layers == null || layers.Length < 1)
                return _videoLayers;

            _level = 0;

            foreach (ShapeLayer layer in layers)
            {
                if (!layer.IsEmpty)
                {
                    if (AppendLayer(_videoLayers,layer))
                    {
                        if (layer.EndTime > PlayLength)
                            PlayLength = (long)layer.EndTime;
                    }
                }
            }

            //CheckMarquee();
            _videoLayers.PlayLength = PlayLength;
            return _videoLayers;
        }
    }
}
