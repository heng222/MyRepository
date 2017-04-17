using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Runtime.Serialization;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Drawing.Design;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectInterleave : LayerEffect<EffectInterleave> 
    {
        private int _State = 1;
        private bool _Lines = true;
        private int _Thickness = 1;
        private DirectionWays _DirectionWay = DirectionWays.BottomCorners;

        public EffectInterleave()
        {
            base.Name = EffectId.Interleave.Name;
            base.GUID = EffectId.Interleave.Guid;
        }

        /// <summary>
        /// get or set Lines
        /// </summary>
        [Browsable(false)]
        public bool Lines
        {
            get { return _Lines; }
            set { _Lines = value; }
        }

        /// <summary>
        /// get or set Thickness
        /// </summary>
        [Browsable(false)]
        public int Thickness
        {
            get { return _Thickness; }
            set { _Thickness = value; }
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

        [Editor(Constance.Designers.Enum, typeof(UITypeEditor))]
        [TypeConverter(typeof(EnumTypeConverter))]
        public enum DirectionWays
        {
            [EnumDescription("Top Bottom")]
            TopBottom = 0,
            [EnumDescription("Left Right")]
            LeftRight = 1,
            [EnumDescription("In Out")]
            InOut = 2,
            [EnumDescription("Top Left Bottom Right")]
            TopLeftBottomRight = 3,
            [EnumDescription("Bottom Left Top Right")]
            BottomLeftTopRight = 4,
            [EnumDescription("Top Corners")]
            TopCorners = 5,
            [EnumDescription("Bottom Corners")]
            BottomCorners = 6
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectInterleave other = efc as EffectInterleave;
            if (other != null)
            {
                _Lines = other._Lines;
                _Thickness = other._Thickness;
                _DirectionWay = other._DirectionWay;
            }
        }

        public override void FromTo(LayerEffect efc, bool isAddNewEffect)
        {
            if (efc == null)
                return;
            base.FromTo(efc, isAddNewEffect);
            EffectInterleave other = efc as EffectInterleave;
            if (other != null)
            {
                _Lines = other._Lines;
                _Thickness = other._Thickness;
                _DirectionWay = other._DirectionWay;
            }
        }

        
        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[4];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("Direction", ((int)_DirectionWay).ToString());
            proArr[2] = new Property("Lines", _Lines ? "1" : "0");
            proArr[3] = new Property("Thickness", PopulatePixel(_Thickness * 10).ToString());
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("LineWidth", _Thickness.ToString()),
                    new Property("LineOrientation", _Lines ?  LineLocationType.VERTICAL.ToString() :  LineLocationType.HORIZONTAL.ToString()),
                    new Property("Direction", GetDirection()),
                };
            }
        }

        public string GetDirection()
        {
            switch (_DirectionWay)
            {
                case DirectionWays.BottomCorners: return EffectDirectionType.LOWCORNERS.ToString(); break;
                case DirectionWays.BottomLeftTopRight: return EffectDirectionType.LOWLEFT_UPRIGHT.ToString(); break;
                case DirectionWays.InOut: return EffectDirectionType.IN_OUT.ToString(); break;
                case DirectionWays.LeftRight: return EffectDirectionType.LEFT_RIGHT.ToString(); break;
                case DirectionWays.TopBottom: return EffectDirectionType.UP_DOWN.ToString(); break;
                case DirectionWays.TopCorners: return EffectDirectionType.UPCORNERS.ToString(); break;
                case DirectionWays.TopLeftBottomRight: return EffectDirectionType.UPLEFT_LOWRIGHT.ToString(); break;

            }
            return DirectionWays.BottomCorners.ToString();
        }
        public override object ToUFEEffect()
        {
            var eff = new Interleave();
            eff.LineWidth = _Thickness;
            eff.LineOrientation = _Lines ?  LineLocationType.VERTICAL :  LineLocationType.HORIZONTAL;
            switch (_DirectionWay)
            {
                case DirectionWays.BottomCorners: eff.Direction = EffectDirectionType.LOWCORNERS; break;
                case DirectionWays.BottomLeftTopRight: eff.Direction = EffectDirectionType.LOWLEFT_UPRIGHT; break;
                case DirectionWays.InOut: eff.Direction = EffectDirectionType.IN_OUT; break;
                case DirectionWays.LeftRight: eff.Direction = EffectDirectionType.LEFT_RIGHT; break;
                case DirectionWays.TopBottom: eff.Direction = EffectDirectionType.UP_DOWN; break;
                case DirectionWays.TopCorners: eff.Direction = EffectDirectionType.UPCENTER; break;
                case DirectionWays.TopLeftBottomRight: eff.Direction = EffectDirectionType.UPLEFT_LOWRIGHT; break;

            }
            return eff;
        }
    }
}
