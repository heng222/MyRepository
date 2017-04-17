using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;
using System.Drawing;
using ProWrite.Unsafe;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectRadar : LayerEffect<EffectRadar>
    {
        public EffectRadar()
        {
            base.Name = EffectId.Radar.Name;
            base.GUID = EffectId.Radar.Guid;
        }

        private int _EdgeVisible = 1;
        private Color _EdgeColor = Color.Red;

        [Browsable(false)]
        public Color EdgeColor
        {
            get { return _EdgeColor; }
            set { _EdgeColor = value; }
        }

        [Browsable(false)]
        public int EdgeVisible
        {
            get { return _EdgeVisible; }
            set { _EdgeVisible = value; }
        }

        private DirectionWays _direction = DirectionWays.Clockwise;
        public int Direction
        {
            get { return Convert.ToInt32(_direction); }
            set 
            {
                if (value == 0)
                    _direction = DirectionWays.Clockwise;
                else
                    _direction = DirectionWays.Counterclockwise;
            }
        }

        public enum DirectionWays
        {
            Clockwise = 0,
            Counterclockwise = 1,
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            var other = efc as EffectRadar;
            if (other != null)
            {
                _direction = other._direction;
                _EdgeColor = other._EdgeColor;
                _EdgeVisible = other._EdgeVisible;
            }
        }

        public override Property[] ToPropertyArray()
        {
            return new Property[]
           {
                new Property("State",StateString),
                new Property("PointerWidth",_EdgeVisible.ToString()),
                new Property("PointerColor",_EdgeColor.ToString()),
                new Property("Direction",GetDirection()),
           };
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("EdgeColor", ColorToString(_EdgeColor)),
                    new Property("EdgeVisible", _EdgeVisible.ToString()),
                    new Property("Direction", GetDirection()),
                };
            }
        }

        public string GetDirection()
        {
            switch (_direction)
            {
                case DirectionWays.Clockwise: return EffectDirectionType.CLOCKWISE.ToString(); break;
                case DirectionWays.Counterclockwise: return EffectDirectionType.COUNTERCW.ToString(); break;
            }

            return EffectDirectionType.CLOCKWISE.ToString();
        }

        public override object ToUFEEffect()
        {
            var eff = new Radar();
            switch (_direction)
            {
                case DirectionWays.Clockwise: eff.Direction = EffectDirectionType.CLOCKWISE; break;
                case DirectionWays.Counterclockwise: eff.Direction = EffectDirectionType.COUNTERCW; break;
            }
            eff.EdgeColor = Convert.ToInt32(_EdgeColor);
            eff.EdgeVisible = _EdgeVisible > 0 ? true : false;
            return eff;
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _EdgeColor = SignTypeHandler.ConvertColor(_EdgeColor, signType);
        }
    }
}
