//---------------------------------------------------------------------
//
// File: ShapeFigure.cs
//
// Description:
// 
//
// Author: 
//
// Modify history:
//      Kevin  2008-6-19 迁移
//      Kevin  2008-6-25 把ShapeFigure.cs 文件 中的ShapeKind枚举存放到Enums文件中
//      Kevin  2008-6-25 把ShapeFigure.cs 文件 中的ArrowDirection枚举移除（.net系统中已存在）
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
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

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Summary description for ShapeFigure.
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract partial class ShapeFigure : ShapePaint,IEquatable<ShapeFigure>
	{
        #region Non Serialized Fields
        [NonSerialized]
        private static Color tranColor = Color.FromArgb(255, 1, 0, 0);
        #endregion

        #region Serialized Fields
        private Color _backColor = Color.Black;
        #endregion
		
        #region Propertys
        [Browsable(false)]
        public Color TranColor
        {
            get { return tranColor; }
        }
        
        [Category("Shape")]
        [Browsable(false)]
        public Color BackColor
        {
            get { return _backColor; }
            set
            {
                //value = SignTypeHandler.ConvertColor(value, SignType);
                if (_backColor != value)
                {
                    Color old = _backColor;
                    _backColor = value;
                    OnPropertyChanged("BackColor", _backColor, old);
                }
            }
        }

        public override LayerType LayerType
        {
            get { return LayerType.Paint; }
        }

        [Browsable(false)]
        public override Rectangle VirtualBounds
        {
            //get { return _bounds.ScaleRectangeByZoom(_zoom);}
            get { return base._virtualBounds;}
            set
            {
                if (_virtualBounds != value)
                {
                    value.Width = value.Width < _zoom ? _zoom : value.Width;
                    value.Height = value.Height < _zoom ? _zoom : value.Height;

                    Bounds = value.ScaleRectangeByZoom(1d / _zoom);
                }
            }
        }

        [Browsable(false)]
        public Rectangle Bounds
        {
            get { return _bounds; }
            set 
            {
                if (value != _bounds)
                {
                    Rectangle old = _bounds;
                    value.Width = value.Width < 1 ? 1 : value.Width;
                    value.Height = value.Height < 1 ? 1 : value.Height;
                    _bounds = value;
                    _virtualBounds = value.ScaleRectangeByZoom(Zoom);
                    OnPropertyChanged("Bounds", value, old);
                    OnBoundsChanged();
                }
            }
        }
        
        #endregion

        #region Contructed Method

        public ShapeFigure()
            : this(SignType.RGB)
        {
        }

        public ShapeFigure(SignType signType)
            : base(signType)
        {
            //_backColor = SignTypeHandler.ConvertColor(_backColor, signType);
        }

        public ShapeFigure(SignType? signType)
            : base(signType)
        {
            SignType sig = signType ?? SignType.RGB;
            //_backColor = SignTypeHandler.ConvertColor(_backColor, sig);
        }

        public ShapeFigure(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : this(signType)
        {
            _zoom = zoom;
            _borderColor = SignTypeHandler.ConvertColor(lineColor, signType);
            FillColor = SignTypeHandler.ConvertColor(fillColor, signType);
            Filled = filled;
            _borderWidth = lineWidth;

            SetRectangle(x, y, width, height);
        }

        public ShapeFigure(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : this(signType)
        {
            _zoom = zoom;
            _borderColor = SignTypeHandler.ConvertColor(rectInfo.BorderColor, signType);
            LineDashStyle = rectInfo.LineDashStyle;
            FillColor = SignTypeHandler.ConvertColor(rectInfo.FilledColor, signType);
            Filled = rectInfo.Filled;
            _borderWidth = rectInfo.BorderWidth;

            SetRectangle(x, y, width, height);
        }

        #endregion

		#region Public Methods

        protected internal override void DrawOutputImage(Graphics g)
        {
            PaintFigure(g, _virtualBounds, MonoSignBoardColor, MonoSignFilledColor, Type, _borderWidth * Zoom);
        }

        

        public override void PaintFigure(Graphics g, Rectangle bounds)
        {
            Point offset = VirtualLocation.PointSubPoint(bounds.Location);
            Rectangle rect = new Rectangle(offset, _virtualBounds.Size);
            ComputePlayerBound(rect, SignSize);
            PaintFigure(g, rect, DrawingColor, DrawingFilledColor, Type, _borderWidth * Zoom);
        }

        protected void PaintFigure(Graphics g, RectangleF innbounds, Color borderColor, Color fillColor, ShapeType shapeKind, int borderwidth)
        {
            using (GraphicsPath gp = new GraphicsPath())
            {
                switch (shapeKind)
                {
                    case ShapeType.Rectangle:
                        gp.AddRectangle(ShapePaintHelper.GetNormalizedRectangle(Rectangle.Round(innbounds)));
                        break;
                    case ShapeType.Ellipse:
                        gp.AddEllipse(ShapePaintHelper.GetNormalizedRectangle(Rectangle.Round(innbounds)));
                        break;
                    case ShapeType.UpArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Up));
                        break;
                    case ShapeType.DownArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Down));
                        break;
                    case ShapeType.RightArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Right));
                        break;
                    case ShapeType.LeftArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Left));
                        break;
                    default:
                        return;
                }
                if (Filled)
                    g.FillPath(_cache.GetSolidBrush(fillColor), gp);

                using(Pen pen = _cache.GetPen(borderColor, borderwidth, PenAlignment.Inset, LineDashStyle))
                    g.DrawPath(pen, gp);
            }
        }
        

        protected static PointF[] Rect2PointFArray(RectangleF rectf, ArrowDirection arrowDirection)
        {
            List<PointF> list = new List<PointF>();

            switch (arrowDirection)
            {
                case ArrowDirection.Up:
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Bottom));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Bottom));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    break;
                case ArrowDirection.Down:
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    break;
                case ArrowDirection.Left:
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.Right, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    break;
                case ArrowDirection.Right:
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    break;
            }

            PointF[] array = new PointF[list.Count];
            list.CopyTo(array);

            return array;
        }
       
		#endregion //End Methods

        #region Public Override mehtod extend

        public override Point GetHandle(int handleNumber)
        {
            int x, y, xCenter, yCenter;

            xCenter = _virtualBounds.X + _virtualBounds.Width / 2;
            yCenter = _virtualBounds.Y + _virtualBounds.Height / 2;
            x = _virtualBounds.X;
            y = _virtualBounds.Y;

            switch (handleNumber)
            {
                case 1:
                    x = _virtualBounds.X;
                    y = _virtualBounds.Y;
                    break;
                case 2:
                    x = xCenter;
                    y = _virtualBounds.Y;
                    break;
                case 3:
                    x = _virtualBounds.Right;
                    y = _virtualBounds.Y;
                    break;
                case 4:
                    x = _virtualBounds.Right;
                    y = yCenter;
                    break;
                case 5:
                    x = _virtualBounds.Right;
                    y = _virtualBounds.Bottom;
                    break;
                case 6:
                    x = xCenter;
                    y = _virtualBounds.Bottom;
                    break;
                case 7:
                    x = _virtualBounds.X;
                    y = _virtualBounds.Bottom;
                    break;
                case 8:
                    x = _virtualBounds.X;
                    y = yCenter;
                    break;
            }

            return new Point(x, y);
        }

        public override int HitTest(Point point)
        {
            if (!IsVisible) return -1;
            if (IsSelected)
                for (int i = 1; i <= HandleCount; i++)
                    if (GetHandleRectangle(i).Contains(point))
                        return i;

            if (PointInObject(point)) return 0;

            return -1;
        }

        public override void MoveHandleTo(Point point, int handleNumber)
        {
            int left    = _virtualBounds.Left;
            int top     = _virtualBounds.Top;
            int right   = _virtualBounds.Right;
            int bottom  = _virtualBounds.Bottom;

            switch (handleNumber)
            {
                case 1:
                    left = point.X;
                    top = point.Y;
                    break;
                case 2:
                    top = point.Y;
                    break;
                case 3:
                    right = point.X;
                    top = point.Y;
                    break;
                case 4:
                    right = point.X;
                    break;
                case 5:
                    right = point.X;
                    bottom = point.Y;
                    break;
                case 6:
                    bottom = point.Y;
                    break;
                case 7:
                    left = point.X;
                    bottom = point.Y;
                    break;
                case 8:
                    left = point.X;
                    break;
            }

            //VirtualBounds = FormatBoundsByZoom(new Rectangle(left, top, right - left, bottom - top),Zoom);
            Bounds = FormatBoundsByZoom(new Rectangle(left, top, right - left, bottom - top), Zoom).ScaleRectangeByZoom(1d / Zoom);
            IsChanged = true;
        }

        public override void Move(int deltaX, int deltaY)
        {
            if (Math.Abs(deltaX) < Zoom && Math.Abs(deltaY) < Zoom) return;
            
            IsMoving = true;
            Rectangle moveRect = _virtualBounds;
            moveRect.Offset(deltaX, deltaY);
            Bounds = FormatBoundsByZoom(moveRect, Zoom).ScaleRectangeByZoom(1d/Zoom);
            IsChanged = true;
            IsMoving = false;
        }

        public override void Normalize()
        {
            //rectangle = ShapePaintHelper.GetNormalizedRectangle(FigureRectangle);
        }

        public override void PopulateSignInfo(SignType signType, Size signSize, int zoom)
        {
            _zoom = zoom;
            SignSize = signSize;
            signType = SignType;
            BeginEdit();
            SetVirtualBounds();
            EndEdit();
        }

        #endregion

        #region Protected Method extend

        protected override bool PointInObject(Point point)
        {
            return _virtualBounds.Contains(point);
        }

        protected override void SetRectangle(int x, int y, int width, int height)
        {
            BeginEdit();
            Bounds = new Rectangle(x, y, width, height).ScaleRectangeByZoom(1d / Zoom);
            SetVirtualBounds();
            Normalize();
            EndEdit();
        }

        protected override void UpdateSignType()
        {
            base.UpdateSignType();

            _backColor = SignTypeHandler.ConvertColor(_backColor, SignType);
            tranColor = SignTypeHandler.ConvertColor(tranColor, SignType);
        }
        #endregion
        
		#region IEquatable<ShapeFigure> Members

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);

            ShapeFigure other = shape as ShapeFigure;
            if (other != null)
            {
                _backColor = other._backColor;
            }
        }

		public bool Equals(ShapeFigure other)
		{
			if (other == null)
				return false;
			if (other._backColor != _backColor)
				return false;

			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeFigure);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion

	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeRectangle : ShapeFigure
	{
        #region Construct Method

        public ShapeRectangle(SignType? signType)
            : base(signType)
        {
        }

        public ShapeRectangle()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }

        public ShapeRectangle(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : base(zoom,x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
        }

        public ShapeRectangle(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }
        #endregion

        public override ShapeBase NewInstance()
		{
			return new ShapeRectangle();
		}

		public override ShapeType  Type
		{
			get { return ShapeType.Rectangle; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitRectangle(this);
        }
	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeEllipse : ShapeFigure
	{
        #region Construct Method
        public ShapeEllipse(SignType? signType)
            : base(signType)
        {
        }

        public ShapeEllipse()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }

        public ShapeEllipse(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth,DashStyle lineDashStyle, SignType signType)
            : base(zoom, x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
        }

        public ShapeEllipse(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }
        #endregion

 		public override ShapeBase NewInstance()
		{
			return new ShapeEllipse();
		}

		public override ShapeType Type
		{
			get { return ShapeType.Ellipse; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitEllipse(this);
        }
	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeUpArrow : ShapeFigure
	{
        #region Construct Method
        public ShapeUpArrow(SignType? signType)
            : base(signType)
        {
        }

        public ShapeUpArrow()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }

        public ShapeUpArrow(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : base(zoom, x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
            
        }

        public ShapeUpArrow(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }
       
        #endregion

        public override ShapeBase NewInstance()
		{
			return new ShapeUpArrow();
		}

		public override ShapeType Type
		{
			get { return ShapeType.UpArrow; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitUpArrow(this);
        }
	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeDownArrow : ShapeFigure
	{
        #region Construct Method
        public ShapeDownArrow(SignType? signType)
            : base(signType)
        {
        }

        public ShapeDownArrow()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }
        
        public ShapeDownArrow(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : base(zoom, x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
        }

        public ShapeDownArrow(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }
       
        #endregion
     
		public override ShapeBase NewInstance()
		{
			return new ShapeDownArrow();
		}

		public override ShapeType Type
		{
			get { return ShapeType.DownArrow; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitDownArrow(this);
        }
	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeRightArrow : ShapeFigure
	{
        #region Construct Method
        public ShapeRightArrow(SignType? signType)
            : base(signType)
        {
        }

        public ShapeRightArrow()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }

        public ShapeRightArrow(int zoom,int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : base(zoom, x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
            
        }

        public ShapeRightArrow(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }
        #endregion

		public override ShapeBase NewInstance()
		{
			return new ShapeRightArrow();
		}

		public override ShapeType Type
		{
			get { return ShapeType.RightArrow; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitRightArrow(this);
        }
	}

	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeLeftArrow : ShapeFigure
	{
        #region Construct Method
        public ShapeLeftArrow(SignType? signType)
            : base(signType)
        {
        }

        public ShapeLeftArrow()
            : this((SignType?)SignType.RGB)
        {
            _zoom = 1;
            SetRectangle(0, 0, 1, 1);
            Initialize();
        }

        public ShapeLeftArrow(int zoom, int x, int y, int width, int height, Color lineColor, Color fillColor, bool filled, int lineWidth, DashStyle lineDashStyle, SignType signType)
            : base(zoom, x, y, width, height, lineColor, fillColor, filled, lineWidth, lineDashStyle, signType)
        {
        }

        public ShapeLeftArrow(int zoom, int x, int y, int width, int height, ShapePaintPropertyInfo rectInfo, SignType signType)
            : base(zoom, x, y, width, height, rectInfo, signType)
        {
        }

        #endregion
       
		public override ShapeBase NewInstance()
		{
			return new ShapeLeftArrow();
		}

		public override ShapeType Type
		{
			get { return ShapeType.LeftArrow; }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitLeftArrow(this);
        }
	}
}