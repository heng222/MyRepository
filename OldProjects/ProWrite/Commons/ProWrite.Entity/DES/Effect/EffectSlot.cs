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
    public class EffectSlot : LayerEffect<EffectSlot> 
    {
        public EffectSlot()
        {
            base.Name = EffectId.Slot.Name;
            base.GUID = EffectId.Slot.Guid;
        }

        

        public override Property[] ToPropertyArray()
        {
            return null;
        }

        public override object ToUFEEffect()
        {
            return new Slot();
        }
    }
}
