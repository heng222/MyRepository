using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.Serialization;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectLine : LayerEffect<EffectLine>
    {
        private int _State = 1;
        private int _PullPoint = 1;
        private int _LagSpacing = 1;
        private int _LineWidth = 1;
        private DirectionWays _DirectionWay = DirectionWays.Left;

        public EffectLine()
        {
            base.Name = EffectId.Line.Name;
            base.GUID = EffectId.Line.Guid;
        }

        /// <summary>
        /// get or set PullPoint
        /// </summary>
        [Browsable(false)]
        public int PullPoint
        {
            get { return _PullPoint; }
            set { _PullPoint = value; }
        }

        /// <summary>
        /// get or set LagSpacing
        /// </summary>
        [Browsable(false)]
        public int LagSpacing
        {
            get { return _LagSpacing; }
            set { _LagSpacing = value; }
        }

        /// <summary>
        /// get or set LineWidth
        /// </summary>
        [Browsable(false)]
        public int LineWidth
        {
            get { return _LineWidth; }
            set { _LineWidth = value; }
        }

        /// <summary>
        /// get or set DirectionWay
        /// </summary>
        [Browsable(false)]
        public DirectionWays DirectionWay
        {
            get { return _DirectionWay; }
            set { _DirectionWay = value; }
        }


        public enum DirectionWays
        {
            Left = 0,
            Right = 1,
            Up = 2,
            Down = 3
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectLine other = efc as EffectLine;
            if (other != null)
            {
                _PullPoint = other._PullPoint;
                _LagSpacing = other._LagSpacing;
                _LineWidth = other._LineWidth;
                _DirectionWay = other._DirectionWay;
            }
        }

        public override void FromTo(LayerEffect efc, bool isAddNewEffect)
        {
            if (efc == null)
                return;
            base.FromTo(efc, isAddNewEffect);
            EffectLine other = efc as EffectLine;
            if (other != null)
            {
                _PullPoint = other._PullPoint;
                _LagSpacing = other._LagSpacing;
                _LineWidth = other._LineWidth;
                _DirectionWay = other._DirectionWay;
            }
        }



        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[5];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("PullPoint", PopulatePixel(_PullPoint).ToString());
            proArr[2] = new Property("LagSpacing", PopulatePixel(_LagSpacing).ToString());
            proArr[3] = new Property("LineWidth", PopulatePixel(_LineWidth).ToString());
            //PopulatePixelZoom(proArr);
            proArr[4] = new Property("Direction", GetDirection());
            return proArr;
        }

        /// <summary>
        /// 
        /// </summary>

        private void PopulatePixelZoom(Property[] proArr)
        {
            double VSignHeight = PopulatePixel(ShapeLayer.Shape.SignSize.Height);
            double VSignWidth = PopulatePixel(ShapeLayer.Shape.SignSize.Width);
            double LayerHeight = ShapeLayer.Shape.VirtualSize.Height;
            double LayerWidth = ShapeLayer.Shape.VirtualSize.Width;

            //Horizon move
            if (_DirectionWay == DirectionWays.Left
                || _DirectionWay == DirectionWays.Right)
            {
                proArr[3] = new Property("LineWidth", PopulatePixel(LineWidth) * (VSignHeight / LayerHeight));
                proArr[1] = new Property("PullPoint", PopulatePixel(PullPoint) * (VSignWidth / LayerWidth));
                proArr[2] = new Property("LagSpacing", PopulatePixel(LagSpacing) * (VSignWidth / LayerWidth));

            }
            //Vorizon move
            if (_DirectionWay == DirectionWays.Up
                || _DirectionWay == DirectionWays.Down)
            {
                proArr[3] = new Property("LineWidth", PopulatePixel(LineWidth) * (VSignWidth / LayerWidth));
                proArr[1] = new Property("PullPoint", PopulatePixel(PullPoint) * (VSignHeight / LayerHeight));
                proArr[2] = new Property("LagSpacing", PopulatePixel(LagSpacing) * (VSignHeight / LayerHeight));
            }
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("LineStagger", _LagSpacing),
                    new Property("LineWidth", _LineWidth),
                    new Property("Direction", _DirectionWay.ToString()),
                    new Property("LineLocation", _PullPoint),
                };
            }
        }

        public string GetDirection()
        {
            switch (_DirectionWay)
            {
                case DirectionWays.Down: return EffectDirectionType.DOWN.ToString(); break;
                case DirectionWays.Left: return EffectDirectionType.LEFT.ToString(); break;
                case DirectionWays.Right: return EffectDirectionType.RIGHT.ToString(); break;
                case DirectionWays.Up: return EffectDirectionType.UP.ToString(); break;
            }
            return DirectionWays.Left.ToString();
        
        }

        public override object ToUFEEffect()
        {
            var eff = new Line();
            eff.LineStagger = _LagSpacing;
            eff.LineWidth = _LineWidth;
            //eff.Location = _PullPoint;
            switch (_DirectionWay)
            {
                case DirectionWays.Down: eff.Direction = EffectDirectionType.DOWN; break;
                case DirectionWays.Left: eff.Direction = EffectDirectionType.LEFT; break;
                case DirectionWays.Right: eff.Direction = EffectDirectionType.RIGHT; break;
                case DirectionWays.Up: eff.Direction = EffectDirectionType.UP; break;
            }
            return eff;
        }
    }
}
