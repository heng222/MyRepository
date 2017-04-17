using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.Serialization;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectBijou : LayerEffect<EffectBijou>
    {
        private int _Rate = 1;
        private int _LampHeight = 3;
        private int _LampLength = 3;
        private int _GapLength = 3;
        private bool _CornersOn = true;
        private DirectionType _DirectionWay = DirectionType.Clockwise;
        private Color _Color = Color.White;

        public EffectBijou()
        {
            base.Name = EffectId.Bijou.Name;
            base.GUID = EffectId.Bijou.Guid;
            base.Type = EffectType.Emphasis;
        }

        /// <summary>
        /// get or set is Rate
        /// </summary>
        [Browsable(false)]
        [Description("Movement rate.")]
        public int Rate
        {
            get { return _Rate; }
            set { _Rate = value; }
        }

        /// <summary>
        /// get or set is LampHeight
        /// </summary>
        [Browsable(false)]
        [Description("Lamp's height when layout horizontally or width when layout vertically.")]
        public int LampHeight
        {
            get { return _LampHeight; }
            set { _LampHeight = value; }
        }

        /// <summary>
        /// get or set is LampLength
        /// </summary>
        [Browsable(false)]
        [Description("Lamp length when layout horizontally.")]
        public int LampLength
        {
            get { return _LampLength; }
            set { _LampLength = value; }
        }

        /// <summary>
        /// get or set is GapLength
        /// </summary>
        [Browsable(false)]
        public int GapLength
        {
            get { return _GapLength; }
            set { _GapLength = value; }
        }

        /// <summary>
        /// get or set is CornersOn
        /// </summary>
        [Browsable(false)]
        [Description("Are corners always on?")]
        public bool CornersOn
        {
            get { return _CornersOn; }
            set { _CornersOn = value; }
        }

        /// <summary>
        /// get or set is Direction
        /// </summary>
        [Browsable(false)]
        public DirectionType DirectionWay
        {
            get { return _DirectionWay; }
            set { _DirectionWay = value; }
        }

        /// <summary>
        /// get or set is Color
        /// </summary>
        [Browsable(false)]
        public Color Color
        {
            //get { return SignTypeHandler.ConvertColor(_Color, Layer.Shape.SignType); }
            get { return _Color; }
            set { _Color = value; }
        }

        private Color _gapColor=Color.Transparent;
        [Browsable(false)]
        public Color GapColor
        {
            get
            {
                if (Layer != null)
                    return SignTypeHandler.ConvertColor(_gapColor, Layer.Shape.SignType);
                else
                    return _gapColor;
            }
            set { _gapColor = value; }
        }

        public enum DirectionType
        {
            Clockwise = 0,
            Counterclockwise = 1,
            Alternating = 2
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectBijou other = efc as EffectBijou;
            if (other != null)
            {
                _Rate = other._Rate;
                _LampHeight = other._LampHeight;
                _LampLength = other._LampLength;
                _GapLength = other._GapLength;
                _CornersOn = other._CornersOn;
                _DirectionWay = other._DirectionWay;
                _Color = other._Color;
                _gapColor = other._gapColor;
            }
        }

        public override void FromTo(LayerEffect efc, bool isAddNewEffect)
        {
            if (efc == null)
                return;
            base.FromTo(efc, isAddNewEffect);
            EffectBijou other = efc as EffectBijou;
            if (other != null)
            {
                _Rate = other._Rate;
                _LampHeight = other._LampHeight;
                _LampLength = other._LampLength;
                _GapLength = other._GapLength;
                _CornersOn = other._CornersOn;
                _DirectionWay = other._DirectionWay;
                _Color = other._Color;
                _gapColor = other._gapColor;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[8];
            proArr[0] = new Property("Rate", PopulatePixel(Rate).ToString());
            proArr[1] = new Property("LampHeight", PopulatePixel(_LampHeight).ToString());
            proArr[2] = new Property("LampLength", PopulatePixel(_LampLength).ToString());
            proArr[3] = new Property("GapLength",  PopulatePixel(_GapLength).ToString());
            proArr[4] = new Property("CornersOn",  CornersOn ? "1" : "0");
            proArr[5] = new Property("Direction", ((int)_DirectionWay).ToString());
            proArr[6] = new Property("LampColor", ColorToString(_Color));
            proArr[7] = new Property("GapColor", ColorToString(_gapColor));
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("LampColor", ColorToString(_Color)),
                    new Property("GapColor", ColorToString(_gapColor)),
                    new Property("Rate", _Rate.ToString()),
                    new Property("GapLength", _GapLength.ToString()), 
                    new Property("LampHeight", _LampHeight.ToString()),
                    new Property("LampLenght", _LampLength.ToString()),
                    new Property("CornersAlwaysOn",CornersOn ? "True": "False" ), 
                    //new Property("On", CornersOn ? "1" : "0"),
                    //new Property("Off", CornersOn ? "0" : "1"),
                    new Property("Direction", GetDirection()),
                };
            }
        }

        public string GetDirection()
        {
            switch (_DirectionWay)
            {
                case DirectionType.Alternating: return EffectDirectionType.ALTERNATING.ToString(); break;
                case DirectionType.Clockwise: return EffectDirectionType.CLOCKWISE.ToString(); break;
                case DirectionType.Counterclockwise: return EffectDirectionType.COUNTERCW.ToString(); break;
            }

            return EffectDirectionType.LEFT.ToString();
        }

        public override object ToUFEEffect()
        {
            Bijou eff = new Bijou();
            eff.Color = _Color.ToArgb();
            eff.GapColor = _gapColor.ToArgb();
            eff.Rate = _Rate;
            eff.Thickness = _LampHeight;
            eff.Length = _LampLength;
            eff.On = CornersOn ? 1 : 0;
            eff.Off = CornersOn ? 0 : 1;

            switch (_DirectionWay)
            {
                case DirectionType.Alternating: eff.Direction = EffectDirectionType.ALTERNATING; break;
                case DirectionType.Clockwise: eff.Direction = EffectDirectionType.CLOCKWISE; break;
                case DirectionType.Counterclockwise: eff.Direction = EffectDirectionType.COUNTERCW; break;
            }
            return eff;
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _Color = SignTypeHandler.ConvertColor(_Color, signType);
            _gapColor = SignTypeHandler.ConvertColor(_gapColor, signType);
        }
    }
}
