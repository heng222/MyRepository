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
    public class EffectFade : LayerEffect<EffectFade>
    {

        public EffectFade()
        {
            base.Name = EffectId.Fade.Name;
            base.GUID = EffectId.Fade.Guid;
        }

        public override Property[] ToPropertyArray()
        {
            return null;
        }

        public override object ToUFEEffect()
        {
            Fade eff = new Fade();
            return eff;
        }
    }
}
