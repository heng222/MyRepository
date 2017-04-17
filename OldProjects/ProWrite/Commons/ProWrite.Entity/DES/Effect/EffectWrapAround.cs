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
    public class EffectWrapAround : LayerEffect<EffectWrapAround> 
    {
        private DirectionWays _DirectionWay = DirectionWays.Left;
        private int _Rate = 5;
        private Color _BackColor = Color.Black;

        public EffectWrapAround()
        {
            base.Name = EffectId.WrapAround.Name;
            base.GUID = EffectId.WrapAround.Guid;
            base.Type = EffectType.Emphasis;
            Spacing = 0;
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public DirectionWays DirectionWay
        {
            get { return _DirectionWay; }
            set { _DirectionWay = value; }
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public int Rate
        {
            get { return _Rate; }
            set { _Rate = value; }
        }

        [Browsable(false)]
        public int Spacing { get; set; }

        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public Color BackColor
        {
            get { return _BackColor; }
            set { _BackColor = value; }
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
            EffectWrapAround other = efc as EffectWrapAround;
            if (other != null)
            {
                _DirectionWay = other._DirectionWay;
                _Rate = other._Rate;
                _BackColor = other._BackColor;
                Spacing = other.Spacing;
            }
        }

        

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("Direction", ((int)_DirectionWay).ToString());
            proArr[1] = new Property("Rate", PopulatePixel(_Rate).ToString());
            proArr[2] = new Property("Spacing", PopulatePixel(Spacing).ToString());
            proArr[2] = new Property("BackColor", ColorToString(_BackColor));
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Rate",_Rate.ToString()),   
                    new Property("Spacing", Spacing.ToString()),   
                    new Property("Direction", GetDirection()),                
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

            return EffectDirectionType.LEFT.ToString();
        }

        public override object ToUFEEffect()
        {
            var eff = new Wraparound();
            eff.Rate = _Rate;
            eff.Spacing = Spacing;
            switch (_DirectionWay)
            {
                case DirectionWays.Down: eff.Direction = EffectDirectionType.DOWN; break;
                case DirectionWays.Left: eff.Direction = EffectDirectionType.LEFT; break;
                case DirectionWays.Right: eff.Direction = EffectDirectionType.RIGHT; break;
                case DirectionWays.Up: eff.Direction = EffectDirectionType.UP; break;
            }
            return eff;
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _BackColor = SignTypeHandler.ConvertColor(_BackColor, signType);
        }
    }
}
