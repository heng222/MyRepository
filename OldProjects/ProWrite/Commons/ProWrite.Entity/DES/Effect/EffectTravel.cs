using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using System.ComponentModel;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.DES.Effect
{
    [Serializable]
    public class EffectTravel : LayerEffect<EffectTravel>
    {
        private static readonly Guid _Id = new Guid("0740D73C-0676-4AFC-BEB9-07F3AE6A8FA3");
        public EffectTravel()
        {
            base.Name = EffectId.Travel.Name;
            base.GUID = EffectId.Travel.Guid; ;
            base.Type = EffectType.Emphasis;
            Circular = true;
            Spacing = 10;
            Speed = -1;
        }

        [Browsable(false)]
        public DirectionWay Direction { get; set; }
        [Browsable(false)]
        public bool Circular { get; set; }
        [Browsable(false)]
        public int Spacing { get; set; }
        //???Rate
        [Browsable(false)]
        public int Speed { get; set; }
        //???not exists
        public enum DirectionWay
        {
            Up = -90,
            Down = 90,
            Left = 180,
            Right = 0,
        }
        [Browsable(false)]
        public string RotateLetters
        {
            get
            {
                if (ShapeLayer != null && ShapeLayer.Shape.Type == ProWrite.Core.ShapeType.Text)
                {
                    var lable = ShapeLayer.Shape as ShapeLabel;
                    return lable.Text;
                }
                return "";
            }
        }

        public override Property[] ToPropertyArray()
        {
            return new Property[]
                {
                    new Property{ Name = "Rate",Value = Speed.ToString()},
                    new Property { Name = "Spacing", Value = Spacing.ToString()},
                    new Property { Name = "Circular", Value = Circular ? "1":"0"},
                    new Property { Name = "Angle", Value = ((int)Direction).ToString()}
                };
        }

        public override object ToUFEEffect()
        {
            var eff = new Travel();
            eff.Circular = Circular;
            eff.Spacing = Spacing;
            eff.Speed = Speed;
            switch (Direction)
            {
                case DirectionWay.Down: eff.Direction = EffectDirectionType.DOWN; break;
                case DirectionWay.Left: eff.Direction = EffectDirectionType.LEFT; break;
                case DirectionWay.Right: eff.Direction = EffectDirectionType.RIGHT; break;
                case DirectionWay.Up: eff.Direction = EffectDirectionType.UP; break;
            }
            return eff;
        }

        public override Property[] UFEEffect
        {
            get
            {
                return new Property[]
                {
                    new Property("Circular", Circular.ToString()),
                    new Property("Spacing", Spacing.ToString()),
                    new Property("Speed", Speed.ToString()),
                    new Property("RotateLetters", RotateLetters.ToString()),
                    new Property("Direction", GetDirection()),                
                };
            }
        }

        public string GetDirection()
        {
            switch (Direction)
            {
                case DirectionWay.Down: return EffectDirectionType.DOWN.ToString(); break;
                case DirectionWay.Left: return EffectDirectionType.LEFT.ToString(); break;
                case DirectionWay.Right: return EffectDirectionType.RIGHT.ToString(); break;
                case DirectionWay.Up: return EffectDirectionType.UP.ToString(); break;
            }
            return EffectDirectionType.LEFT.ToString();

        }

        public override void FromTo(LayerEffect efc)
        {
            if (efc == null)
                return;
            base.FromTo(efc);
            EffectTravel other = efc as EffectTravel;
            if (other != null)
            {
                Direction = other.Direction;
                this.Duration = other.Duration;
                this.Circular = other.Circular;
                this.Spacing = other.Spacing;
                this.Speed = other.Speed;
            }
        }
    }
}
