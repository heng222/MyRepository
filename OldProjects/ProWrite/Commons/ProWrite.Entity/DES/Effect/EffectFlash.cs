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
    public class EffectFlash : LayerEffect<EffectFlash> 
    {
        private int _OnTime = 500;
        private int _OffTime = 200;
        private int _WED = 0;
        private Color _BackColor = Color.Transparent;
        private FlashStyle _Style = FlashStyle.BlankFlash;
        
        public EffectFlash()
        {
            base.Name = EffectId.Flash.Name;
            base.GUID = EffectId.Flash.Guid;
            base.Type = EffectType.Emphasis;
        }
        
        
            /// <summary>
        /// get or set Style
        /// </summary>
        [Browsable(false)]
        public FlashStyle Style
        {
            get { return _Style; }
            set { _Style = value; }
        }

        /// <summary>
        /// get or set OnTime
        /// </summary>
        [Browsable(false)]
        public int OnTime
        {
            get { return _OnTime; }
            set { _OnTime = value; }
        }
        
        /// <summary>
        /// get or set OffTime
        /// </summary>
        [Browsable(false)]
        public int OffTime
        {
            get { return _OffTime; }
            set { _OffTime = value; }
        }

        /// <summary>
        /// get or set WED
        /// </summary>
        [Browsable(false)]
        public int WED
        {
            get { return _WED; }
            set { _WED = value; }
        }
        
        /// <summary>
        /// get or set BackColor
        /// </summary>
        [Browsable(false)]
        public Color BackColor
        {
            get { return _BackColor; }
            set { _BackColor = value; }
        }



        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectFlash other = efc as EffectFlash;
            if (other != null)
            {
                _OnTime = other._OnTime;
                _OffTime = other._OffTime;
                _WED = other._WED;
                _BackColor = other._BackColor;
                _Style = other._Style;
            }
        }


        public override void FromTo(LayerEffect efc, bool isAddNewEffect)
        {
            if (efc == null)
                return;
            base.FromTo(efc, isAddNewEffect);
            EffectFlash other = efc as EffectFlash;
            if (other != null)
            {
                _OnTime = other._OnTime;
                _OffTime = other._OffTime;
                _WED = other._WED;
                _BackColor = other._BackColor;
                _Style = other._Style;
            }
        }

        
        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[5];
            proArr[0] = new Property("OnTime", _OnTime.ToString());
            proArr[1] = new Property("OffTime", _OffTime.ToString());
            proArr[2] = new Property("WED", _WED.ToString());
            proArr[3] = new Property("FlashStyle", ((int)_Style).ToString());
            proArr[4] = new Property("BackColor", ColorToString(_BackColor));
            return proArr;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("OnTime", _OnTime.ToString()),
                    new Property("OffTime", _OffTime.ToString()),
                    new Property("FlashType", _Style.ToString()),
                };
            }
        }


        public override object ToUFEEffect()
        {
            return new Flash { OnTime = _OnTime, OffTime = _OffTime,  FlashType = _Style};
        }

        protected internal override void UpdateSignType(SignType signType)
        {
            base.UpdateSignType(signType);
            _BackColor = SignTypeHandler.ConvertColor(_BackColor, signType);
        }
    }
}
