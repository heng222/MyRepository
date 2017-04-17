using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.DES;
using ProWrite.Core;
using ProWrite.Entity.DES.Effect;
using System.IO;

namespace ProWrite.Entity.Shape
{

    public class DESLayerConverter : ConverterBase<ShapeLayer,Layer>
    {
        private DESLayerConverter() { }

        private static readonly DESLayerConverter instance = new DESLayerConverter();

        public static DESLayerConverter Instance
        {
            get { return instance; }
        }

        private static readonly IDESPaintVisitor Vistor = new DESPaintVisitor();
        public override Layer Convert(ShapeLayer source)
        {
            
            if (!source.IsVisible)
                return null;

            if (source.StartTime > source.EndTime)
                return null;

            source.Accept(Vistor);

            Layer videoLayer = new Layer();

            var _shape = source.Shape;
            var StartTime = source.StartTime;
            var Duration = source.Duration;
            var Name = source.Name;
            var EndTime = source.EndTime;
            var IsVisible = source.IsVisible;
            var EntryEffect = source.EntryEffect;
            var EmphasisEffect = source.EmphasisEffect;
            var ExitEffect = source.ExitEffect;
            
            if (_shape.Type == ShapeType.DynamicText || _shape.Type == ShapeType.Time || _shape.Type == ShapeType.Temperature)
            {
                ShapeDynamicTextBase DynamicText = _shape as ShapeDynamicTextBase;
                if (DynamicText.RollWay != RollWay.None)
                {
                    videoLayer.TextInfo = new EffectTravel();
                    videoLayer.TextInfo.Left = (int)(source.StartTime * Constance.Effect.UnitWidth);
                    videoLayer.TextInfo.Width = (int)(Duration * Constance.Effect.UnitWidth);
                    videoLayer.TextInfo.Direction = (EffectTravel.DirectionWay)DynamicText.RollWay;
                    videoLayer.TextInfo.Speed = DynamicText.RollRate;
                }
            }

            videoLayer.FilePath = _shape.InnerImagePath;
            videoLayer.LayerType = _shape.VideoType;
            if (videoLayer.LayerType == LayerType.Video)
            {
                if ((string.IsNullOrEmpty(videoLayer.FilePath)) || !File.Exists(videoLayer.FilePath))
                    return null;
            }
            videoLayer.Name = Name;
            videoLayer.Visible = IsVisible;
            //comment out for upload video resize bug
            if (videoLayer.LayerType == LayerType.Video)
                videoLayer.Rect = _shape.DestBounds;
            else
                videoLayer.Rect = _shape.VirtualBounds;
            videoLayer.StartTime = (long)StartTime;
            videoLayer.EndTime = (long)EndTime;

            if (!EntryEffect.IsEmpty)
            {
                videoLayer.EntryEffect = EntryEffect.Copy(false) as LayerEffect;
            }
            videoLayer.EmphasisEffect = EmphasisEffect.Copy(false) as LayerEffect;

            if (!ExitEffect.IsEmpty)
            {
                videoLayer.ExitEffect = ExitEffect.Copy(false) as LayerEffect;
            }

            return videoLayer;
        }
    }
}
