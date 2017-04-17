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
    public class EffectSnow : LayerEffect<EffectSnow> 
    {
        private float _Amount = 0.5f;
        private float _Rate = 5;
        private Color _Color = Color.White;

        public EffectSnow()
        {
            base.Name = EffectId.Snow.Name;
            base.GUID = EffectId.Snow.Guid;
            base.Type = EffectType.Emphasis;
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public float Amount
        {
            get { return _Amount; }
            set { _Amount = value; }
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public float Rate
        {
            get { return _Rate; }
            set { _Rate = value; }
        }

        /// <summary>
        /// get or set sign type
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
            EffectSnow other = efc as EffectSnow;
            if (other != null)
            {
                _Amount = other._Amount;
                _Rate = other._Rate;
                _Color = other._Color;
            }
        }

        

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("Amount", _Amount.ToString());
            proArr[1] = new Property("Rate", _Rate.ToString());
            proArr[2] = new Property("Color", ColorToString(_Color));
            return proArr;
        }


        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Amount", ((int)(_Amount*100)).ToString()),
                    new Property("Color", ColorToString(_Color)),
                    new Property("Rate", ((int)(_Rate*100)).ToString()),
                };
            }
        }


        public override object ToUFEEffect()
        {
            return new Snow { Amount =(int)(_Amount*100), Color = _Color.ToArgb(), FallRate = (int)(_Rate*100), };
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _Color = SignTypeHandler.ConvertColor(_Color,signType);
        }
    }
}
