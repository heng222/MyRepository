using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectSlide : LayerEffect<EffectSlide>
    {
        public EffectSlide()
        {
            base.Name = EffectId.Slide.Name;
            base.GUID = EffectId.Slide.Guid;
        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectSlide other = efc as EffectSlide;
            if (other != null)
            {
                Direction = other.Direction;
            }
        }
        public override void FromTo(LayerEffect efc, bool isAddNewEffect)
        {
            if (efc == null)
                return;
            base.FromTo(efc, isAddNewEffect);
            EffectSlide other = efc as EffectSlide;
            if (other != null)
            {
                Direction = other.Direction;
            }
        }

        public override Property[] ToPropertyArray()
        {
            Property[] proArr = new Property[2];
            proArr[0] = new Property("State", StateString);
            proArr[1] = new Property("Direction",((int)Direction).ToString());
            return proArr;
        }

        public SlideDirection Direction
        {
            get;
            set;
        }
        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Direction", GetDirection()),                
                };
            }
        }

        public string GetDirection()
        {
            switch (Direction)
            {
                case SlideDirection.Down: return EffectDirectionType.DOWN.ToString(); break;
                case SlideDirection.Left: return EffectDirectionType.LEFT.ToString(); break;
                case SlideDirection.Right: return EffectDirectionType.RIGHT.ToString(); break;
                case SlideDirection.Up: return EffectDirectionType.UP.ToString(); break;
            }

            return EffectDirectionType.LEFT.ToString();
        }

        public override object ToUFEEffect()
        {
            var eff = new Slide();
            switch (Direction)
            {
                case SlideDirection.Down: eff.Direction = EffectDirectionType.DOWN; break;
                case SlideDirection.Left: eff.Direction = EffectDirectionType.LEFT; break;
                case SlideDirection.Right: eff.Direction = EffectDirectionType.RIGHT; break;
                case SlideDirection.Up: eff.Direction = EffectDirectionType.UP; break;
            }
            return eff;
        }

        
    }

    public enum SlideDirection
    {
        Left,
        Right,
        Up,
        Down,
        //In,
        //Out,
        //UpperLeft,
        //UpperRight,
        //LowerLeft,
        //LowerRight,
        //UpperCenter,
        //LowerCenter,
        //UpperCorners,
        //LowerCorners,
        //Center,
        //AllCorners,
    }

}
