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
    public class EffectBlackHole : LayerEffect<EffectBlackHole>
    {
        private int _State = 1;
        private int _StartY = 0;
        private int _StartX = 0;

        public EffectBlackHole()
        {
            base.Name = EffectId.BlackHole.Name;
            base.GUID = EffectId.BlackHole.Guid;
        }

        /// <summary>
        /// get or set StartY
        /// </summary>
        [Browsable(false)]
        public int StartY
        {
            get { return _StartY; }
            set { _StartY = value; }
        }

        /// <summary>
        /// get or set StartX
        /// </summary>
        [Browsable(false)]
        public int StartX
        {
            get { return _StartX; }
            set { _StartX = value; }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectBlackHole other = efc as EffectBlackHole;
            if (other != null)
            {
                _StartY = other._StartY;
                _StartX = other._StartX;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[3];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("StartY", PopulatePixel(_StartY).ToString());
            proArr[2] = new Property("StartX", PopulatePixel(_StartX).ToString());
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("LocationX", _StartX.ToString()),
                    new Property("LocationY", _StartY.ToString()),
                };
            }
        }

        public override object ToUFEEffect()
        {
            var eff = new BlackHole();
            eff.LocationX =  _StartX;
            eff.LocationY = _StartY;
            return eff;
        }
    }
}
