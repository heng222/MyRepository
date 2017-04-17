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
    public class EffectCoalesce : LayerEffect<EffectCoalesce> 
    {
        public EffectCoalesce()
        {
            base.Name = EffectId.Coalesce.Name;
            base.GUID =EffectId.Coalesce.Guid;
        }

        private int _entityWidth;
        public int EntityWidth
        {
            //get { return _entityWidth; }
            //set { _entityWidth = value; }
            get;
            set;
        }

        private int _entityHeight;

        public int EntityHeight
        {
            //get { return _entityHeight; }
            //set { _entityHeight = value; }
            get;
            set;
        }
        public override Property[] ToPropertyArray()
        {
            return new Property[]{
                new Property{ Name = "EntityWidth",Value = EntityWidth.ToString()},
                new Property{ Name = "EntityHeight",Value = EntityHeight.ToString()},
            };
        }

        public override object ToUFEEffect()
        {
            Coalesce eff = new Coalesce();
            eff.EntityWidth = EntityWidth;
            eff.EntityHeight = EntityHeight;
            return eff;
        }
        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("EntityWidth", EntityWidth.ToString()),
                    new Property("EntityHeight", EntityHeight.ToString()),
                };
            }
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectCoalesce other = efc as EffectCoalesce;
            if (other != null)
            {
                //_entityWidth = other._entityWidth;
                //_entityHeight = other._entityHeight;
                EntityWidth = other.EntityWidth;
                EntityHeight = other.EntityHeight;
            }
        }
    }
}
