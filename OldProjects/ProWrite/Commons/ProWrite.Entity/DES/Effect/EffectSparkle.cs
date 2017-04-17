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
    public class EffectSparkle : LayerEffect<EffectSparkle> 
    {
        private int _Amount = 20;
        private int _Size = 5;
        private Color _SparkleColor = Color.White;

        public EffectSparkle()
        {
            base.Name = EffectId.Sparkle.Name;
            base.GUID = EffectId.Sparkle.Guid;
            base.Type = EffectType.Emphasis;
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public int Amount
        {
            get { return _Amount; }
            set { _Amount = value; }
        }
        
        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public int Size
        {
            get { return _Size; }
            set { _Size = value; }
        }

        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public Color SparkleColor
        {
            get { return _SparkleColor; }
            set { _SparkleColor = value; }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectSparkle other = efc as EffectSparkle;
            if (other != null)
            {
                _Amount = other._Amount;
                _Size = other._Size;
                _SparkleColor = other._SparkleColor;
            }
        }

       

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("Amount", decimal.Divide(_Amount, 100).ToString());
            proArr[1] = new Property("Size", _Size.ToString());
            proArr[2] = new Property("SparkleColor", ColorToString(_SparkleColor));
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Amount", _Amount.ToString()),
                    new Property("Size", _Size.ToString()),
                };
            }
        }


        public override object ToUFEEffect()
        {
            return new Sparkle { Amount = _Amount, Size = _Size };
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _SparkleColor = SignTypeHandler.ConvertColor(_SparkleColor, signType);
        }
    }
}
