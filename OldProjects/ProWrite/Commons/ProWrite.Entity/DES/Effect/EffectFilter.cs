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
    public class EffectFilter : LayerEffect<EffectFilter> 
    {
        private int _State = 1;
        private int _Width = 20;
        private int _Height = 20;

        public EffectFilter()
        {
            base.Name = EffectId.Filter.Name;
            base.GUID = EffectId.Filter.Guid;
        }

        /// <summary>
        /// get or set Width
        /// </summary>
        [Browsable(false)]
        public int Width
        {
            get { return _Width; }
            set { _Width = value; }
        }

        /// <summary>
        /// get or set Height
        /// </summary>
        [Browsable(false)]
        public int Spacing
        {
            get { return _Height; }
            set { _Height = value; }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectFilter other = efc as EffectFilter;
            if (other != null)
            {
                _Width = other._Width;
                _Height = other._Height;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("Thickness", _Width.ToString());
            proArr[2] = new Property("Spacing", _Height.ToString());
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("LineWidth", _Width.ToString()),
                    new Property("LineSpacing", _Height.ToString()),
                };
            }
        }

        public override object ToUFEEffect()
        {
            var eff = new Filter();
            eff.LineWidth = _Width;
            eff.LineSpacing = _Height;
            return eff;
        }
    }
}
