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
    public class EffectRain : LayerEffect<EffectRain> 
    {
        private int _Amount = 5;
        private float _Angle = 90;
        private Color _Color = Color.White;

        public EffectRain()
        {
            base.Name = EffectId.Rain.Name;
            base.GUID = EffectId.Rain.Guid;
        }

        /// <summary>
        /// get or set Rate
        /// </summary>
        [Browsable(false)]
        public int Amount
        {
            get { return _Amount; }
            set { _Amount = value; }
        }
        
        /// <summary>
        /// get or set Angle
        /// </summary>
        [Browsable(false)]
        public float Angle
        {
            get { return _Angle; }
            set { _Angle = value; }
        }

        /// <summary>
        /// get or set Color
        /// </summary>
        [Browsable(false)]
        public Color Color
        {
            get { return _Color; }
            set { _Color = value; }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectRain other = efc as EffectRain;
            if (other != null)
            {
                _Amount = other._Amount;
                _Angle = other._Angle;
                _Color = other._Color;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("Amount", (_Amount * 1.0f / 10).ToString());
            proArr[1] = new Property("Angle", _Angle.ToString());
            proArr[2] = new Property("Color", ColorToString(_Color));
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Amount", _Amount.ToString()),
                    new Property("Color", ColorToString(_Color)),                    
                };
            }
        }

        public override object ToUFEEffect()
        {
            var eff = new Rain();
            eff.Amount = _Amount;
            eff.Color = _Color.ToArgb();
            return eff;
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _Color = SignTypeHandler.ConvertColor(_Color, signType);
        }
    }
}
