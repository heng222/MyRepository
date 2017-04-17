using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectCopy : LayerEffect<EffectCopy>
    {
        public EffectCopy()
        {
            base.Name = EffectId.Copy.Name;
            base.GUID = EffectId.Copy.Guid;
        }

        public override void FromTo(LayerEffect other)
        {
            base.FromTo(other);
        }

        public override Property[] ToPropertyArray()
        {
            return null;
        }

        public override object ToUFEEffect()
        {
            var eff = new Copy();
            return eff;
        }
    }
}
