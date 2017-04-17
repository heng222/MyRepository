using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Drawing.Design;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.Unsafe;
using ProWrite.Entity.Settings;

namespace ProWrite.Entity.Shape
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class ShapePaint : ShapeBase, IEquatable<ShapePaint>
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private Color filledColor = Color.Transparent;
        private bool filled;
        private int rotation = 0;
        private Point center = Point.Empty;
        [Obsolete]
        private DashStyle lineDashStyle = DashStyle.Solid;
        protected DashKind _lineDashKind = DashKind.Solid;

        #endregion

        #region Serialized Fields Version 2
        #endregion
       
        #region Properties
        [Browsable(false)]
        public Point Center
        {
            get { return center; }
            set { center = value; }
        }

        [Browsable(false)]
        public virtual bool Filled
        {
            get { return filled; }
            set { filled = value; }
        }

        protected internal Color DrawingColor
        {
            get
            {
                if (_borderColor == Color.Black
                    || _borderColor.ToArgb() == Color.Black.ToArgb())
                    return Color.FromArgb(255, 1, 1, 1);
                return _borderColor;
            }
        }

        protected internal Color MonoSignBoardColor
        {
            get
            {
                if (_borderColor == Color.Black
                    || _borderColor.ToArgb() == Color.Black.ToArgb())
                    return Color.Transparent;
                //return _borderColor;
                return SignTypeHandler.ConvertToMonoColor(_borderColor, SignType);
            }
        }

        protected internal Color DrawingFilledColor
        {
            get
            {
                if (filledColor == Color.Black
                    || filledColor.ToArgb() == Color.Black.ToArgb())
                    return Color.FromArgb(255, 1, 1, 1);
                return filledColor;
            }
        }

        protected internal Color MonoSignFilledColor
        {
            get
            {
                if (filledColor == Color.Black
                    || filledColor.ToArgb() == Color.Black.ToArgb())
                    return Color.Transparent;
                return SignTypeHandler.ConvertToMonoColor(filledColor, SignType); ;
            }
        }

        /// <summary>
        /// Fill Color
        /// </summary>
#if DEBUG
        [Browsable(true)]
#else
        [Browsable(false)]
#endif
        public virtual Color FillColor
        {
            get
            {
                return filledColor;
                //return SignTypeHandler.ConvertColor(filledColor, SignType);
            }
            set
            {
                //value = SignTypeHandler.ConvertColor(value, SignType);
                if (value != filledColor)
                {
                    Color old = filledColor;
                    filledColor = value;
                    filled = true;
                    OnPropertyChanged("FillColor", value, old);
                }
            }
        }

        [Browsable(false)]
        [DisplayName("Line Dash")]
        public virtual DashStyle LineDashStyle
        {
            get { return (DashStyle)_lineDashKind; }
            set
            {
                if (value != LineDashStyle)
                {
                    DashStyle old = LineDashStyle;
                    //lineDashStyle = value;
                    _lineDashKind = (DashKind)value;
                    OnPropertyChanged("LineDashStyle", value, old);
                }
            }
        }

        
        [DisplayName("Line Style")]
        public DashKind LineDashKind
        {
            get { return _lineDashKind; }
            set
            {
                if (value != _lineDashKind)
                {
                    DashKind old = _lineDashKind;
                    _lineDashKind = value;
                    //LineDashStyle = (DashStyle)_lineDashKind;
                    OnPropertyChanged("LineDashKind", value, old);
                }
            }
        }

        [Browsable(false)]
        public int Rotation
        {
            get { return rotation; }
            set
            {
                rotation = value;
                if (rotation > 360)
                    rotation = rotation - 360;
                else if (rotation < -360)
                    rotation = rotation + 360;
            }
        }

        [Browsable(true)]
        [DisplayName("Line Width")]
        public override int BorderWidth
        {
            get { return base.BorderWidth; }
            set
            {
                base.BorderWidth = value;
            }
        }

        [Browsable(true)]
        [DisplayName("Line Color")]
        public override Color BorderColor
        {
            get { return base.BorderColor; }
            set { base.BorderColor = value;}
        }

        #endregion

        #region Construct Method
        public ShapePaint(): this(SignType.RGB)
        {
        }

        public ShapePaint(SignType? signType): base(signType)
        {
        }
        #endregion

        #region Method

        public virtual void PaintFigure(Graphics g, Rectangle bounds)
        {
        }
        
        public virtual void PopulateSignInfo(SignType signType, Size signSize, int zoom)
        {
            //Populate(Point.Empty, Size.Empty, signType, signSize, zoom);

        }

        protected override void UpdateSignType()
        {
            this.filledColor = SignTypeHandler.ConvertColor(filledColor, SignType);
            base.UpdateSignType();
        }

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);

            ShapePaint shapePaint = shape as ShapePaint;
            if (shapePaint != null)
            {
                center = shapePaint.center;
                filledColor = shapePaint.filledColor;
                filled = shapePaint.filled;
                rotation = shapePaint.rotation;
                //lineDashStyle = shapePaint.lineDashStyle;
                _lineDashKind = shapePaint._lineDashKind;
            }
        }

        #endregion
       
        #region IEquatable<ShapePaint> Members

        public bool Equals(ShapePaint other)
        {
            if (other == null)
                return false;
            if (other.filled != filled)
                return false;
            if (other.filledColor != filledColor)
                return false;
            if (other.center != center)
                return false;
            if (other.rotation != rotation)
                return false;
            if (other.LineDashKind != _lineDashKind)
                return false;
            //if (other.LineDashStyle != lineDashStyle)
            //    return false;

            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ShapeFontBase);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        #endregion

        protected internal virtual void DrawOutputImage(Graphics g)
        {
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }
    }

    public class ShapePaintPropertyInfo
    {
        public int BorderWidth = 1;
        public Color BorderColor = Color.White;
        public Color FilledColor = Color.Transparent;
        public DashStyle LineDashStyle = DashStyle.Solid;
        public bool Filled = false;

        public ShapePaintPropertyInfo(int width, Color borderColor, Color filledColor, DashStyle dashStyle, bool filled)
        {
            BorderWidth = width;
            BorderColor = borderColor;
            FilledColor = filledColor;
            LineDashStyle = dashStyle;
            Filled = filled;
        }
    }
}
