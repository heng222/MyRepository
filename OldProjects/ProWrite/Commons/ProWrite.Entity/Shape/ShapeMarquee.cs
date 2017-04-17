//using System;
//using System.Collections.Generic;
//using System.Text;
//using System.ComponentModel;
//using System.Drawing;
//using System.Drawing.Design;
//using ProWrite.Core;
//using ProWrite.Entity.DES;
//using ProWrite.Entity.Shape;

//namespace ProWrite.Entity.Shape
//{
//    [Serializable]
//    public class ShapeMarquee : ShapeTextBase,IEquatable<ShapeMarquee>
//    {
//        private class _
//        {
//            public const string Text = "Welcome!";
//            public const int BitCount = 16;
//            public const int RollRate = 3;
//        }

//        public ShapeMarquee():this(SignType.RGB)
//        {
//        }

//        public ShapeMarquee(SignType signType)
//            : base(signType)
//        {
//            Text = _.Text;
//        }

//        private int _BitCount = 16;
//        [Browsable(false)]
//        public int BitCount
//        {
//            get { return _BitCount; }
//            set
//            {
//                if (value != BitCount)
//                {
//                    _BitCount = value;
//                }
//            }
//        }

//        private Align _Align = Align.Left;
//        public Align Align
//        {
//            get { return _Align; }
//            set
//            {
//                if (value != Align)
//                {
//                    _Align = value;
//                }
//            }
//        }

//        private Valign _Valign = Valign.Middle;
//        public Valign Valign
//        {
//            get { return _Valign; }
//            set
//            {
//                if (value != Valign)
//                {
//                    _Valign = value;
//                }
//            }
//        }

//        private RollWay _RollWay = RollWay.LeftToRight;
//        public RollWay RollWay
//        {
//            get { return _RollWay; }
//            set
//            {
//                if (value != RollWay)
//                {
//                    _RollWay = value;
//                }
//            }
//        }

//        private int _RollRate = _.RollRate;
//        public int RollRate
//        {
//            get { return _RollRate; }
//            set
//            {
//                if (value != RollRate)
//                {
//                    _RollRate = value;
//                }
//            }
//        }

//        public TextInfo ToText()
//        {
//            TextInfo item = new TextInfo();
//            item.Align = _Align;
//            item.Valign = _Valign;
//            item.BitCount = _BitCount;
//            item.Color = ForeColor;
//            item.Font = Font.Name;
//            item.FontStyle = Font.Style;
//            item.Size = (int)Font.Size;
//            item.RollRate = _RollRate;
//            item.RollWay = _RollWay;
//            item.Text = Text;
//            return item;
//        }

//        #region override property, method

//        public override ShapeType Type
//        {
//            get { return ShapeType.Marquee; }
//        }

//        public override LayerType LayerType
//        {
//            get { return LayerType.Marquee; }
//        }

//        public override ShapeBase NewInstance()
//        {
//            return new ShapeMarquee();
//        }

//        public override void FromTo(ShapeBase shape)
//        {
//            if (shape == null)
//                return;
//            base.FromTo(shape);
//            ShapeMarquee other = shape as ShapeMarquee;
//            if (other != null)
//            {
//                _Align = other._Align;
//                _BitCount = other._BitCount;
//                _RollRate = other._RollRate;
//                _RollWay = other._RollWay;
//                _Valign = other._Valign;
//            }
//        }
//        public override void Paint(Graphics g)
//        {
//            DrawString(g);
//            base.Paint(g);
//        }
//        #endregion

//        #region IEquatable<ShapeMarquee> Members

//        public bool Equals(ShapeMarquee other)
//        {
//            if (other == null)
//                return false;
//            if (other._Align != _Align)
//                return false;
//            if (other._BitCount != _BitCount)
//                return false;
//            if (other._RollRate != _RollRate)
//                return false;
//            if (other._RollWay != _RollWay)
//                return false;
//            if (other._Valign != _Valign)
//                return false;
//            return base.Equals(other);
//        }

//        public override bool Equals(object obj)
//        {
//            return Equals(obj as ShapeMarquee);
//        }

//        public override int GetHashCode()
//        {
//            return base.GetHashCode();
//        }
//        #endregion
//    }
//}