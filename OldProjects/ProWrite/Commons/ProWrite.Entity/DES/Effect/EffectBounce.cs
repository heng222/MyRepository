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
    public class EffectBounce : LayerEffect<EffectBounce> 
    {
        public EffectBounce()
        {
            base.Name = EffectId.Bounce.Name;
            base.GUID = EffectId.Bounce.Guid;
        }
        
        public override Property[] ToPropertyArray()
        {
            return null;
        }

        public override object ToUFEEffect()
        {
            return new Bounce();
        }
    }
}
