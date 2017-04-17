using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectMultiWipe : LayerEffect<EffectMultiWipe>
    {
        public EffectMultiWipe()
        {
            base.Name = EffectId.MultiWipe.Name;
            base.GUID = EffectId.MultiWipe.Guid;
        }

        private int _HorizontalWipes = 2;
        private int _VerticalWipes = 2;

        [Browsable(false)]
        public int HorizontalWipes
        {
            get { return _HorizontalWipes; }
            set { _HorizontalWipes = value; }
        }

        [Browsable(false)]
        public int VerticalWipes
        {
            get { return _VerticalWipes; }
            set { _VerticalWipes = value; }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectMultiWipe other = efc as EffectMultiWipe;
            if (other != null)
            {
                _HorizontalWipes  = other._HorizontalWipes;
                _VerticalWipes  = other._VerticalWipes;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("HWNum", PopulatePixel(_HorizontalWipes).ToString());
            proArr[2] = new Property("VWNum", PopulatePixel(_VerticalWipes).ToString());
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("HorizontalWipes", _HorizontalWipes.ToString()),
                    new Property("VerticalWipes", _VerticalWipes.ToString()),                    
                };
            }
        }

        public override object ToUFEEffect()
        {
            var eff = new MultiWipe();
            eff.HorizontalWipes = _HorizontalWipes;
            eff.VerticalWipes = _VerticalWipes;
            return eff;
        }
    }
}
