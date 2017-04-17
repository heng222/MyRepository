using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectVenetian : LayerEffect<EffectVenetian>
    {
        public EffectVenetian()
        {
            base.Name = EffectId.Venetian.Name;
            base.GUID = EffectId.Venetian.Guid; ;
            BlindWidth = 4;
        }

        public enum DirectionWays
        {
             Left,
             Right,
             Up,
             Down,
             //UpperLeft,
             //UpperRight,
             //LowerLeft,
             //LowerRight,
        }

        [Browsable(false)]
        public DirectionWays Direction { get; set; }
        [Browsable(false)]
        public int BlindWidth { get; set; }

        public override Property[] ToPropertyArray()
        {
            return new Property[]{
                new Property("State",StateString),
                new Property("Direction",Direction.ToString()),
                new Property("BlindWidth",PopulatePixel(BlindWidth).ToString()),
            };
        }

        public override void FromTo(LayerEffect effect)
        {
            if (effect == null) return;
            base.FromTo(effect);
            var other = effect as EffectVenetian;
            Direction = other.Direction;
            BlindWidth = other.BlindWidth;
        }

        public override void FromTo(LayerEffect effect, bool isAddNewEffect)
        {
            if (effect == null) return;
            base.FromTo(effect, isAddNewEffect);
            var other = effect as EffectVenetian;
            Direction = other.Direction;
            BlindWidth = other.BlindWidth;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("BlindWidth", BlindWidth),   
                    new Property("Direction", GetDirection()),                
                };
            }
        }

        public string GetDirection()
        {
            switch (Direction)
            {
                case DirectionWays.Down: return EffectDirectionType.DOWN.ToString(); break;
                case DirectionWays.Left: return EffectDirectionType.LEFT.ToString(); break;
                //case DirectionWays.LowerLeft: return EffectDirectionType.LOWLEFT.ToString(); break;
                //case DirectionWays.LowerRight: return EffectDirectionType.LOWRIGHT.ToString(); break;
                //case DirectionWays.UpperLeft: return EffectDirectionType.UPLEFT.ToString(); break;
                //case DirectionWays.UpperRight: return EffectDirectionType.UPRIGHT.ToString(); break;
                case DirectionWays.Right: return EffectDirectionType.RIGHT.ToString(); break;
                case DirectionWays.Up: return EffectDirectionType.UP.ToString(); break;
            }

            return EffectDirectionType.LEFT.ToString();
        }

        public override object ToUFEEffect()
        {
            var eff = new Venetian();
            eff.BlindWidth = BlindWidth;
            switch (Direction)
            {
                case DirectionWays.Down: eff.Direction = EffectDirectionType.DOWN; break;
                case DirectionWays.Left: eff.Direction = EffectDirectionType.LEFT; break;
                //case DirectionWays.LowerLeft: eff.Direction = EffectDirectionType.LOWLEFT; break;
                //case DirectionWays.LowerRight: eff.Direction = EffectDirectionType.LOWRIGHT; break;
                case DirectionWays.Right: eff.Direction = EffectDirectionType.RIGHT; break;
                case DirectionWays.Up: eff.Direction = EffectDirectionType.UP; break;
                //case DirectionWays.UpperLeft: eff.Direction = EffectDirectionType.UPLEFT; break;
                //case DirectionWays.UpperRight: eff.Direction = EffectDirectionType.UPRIGHT; break;
            }
            return eff;
        }
    }
}
