//---------------------------------------------------------------------
//
// File: ShapeLine.cs
//
// Description:
// 
//
// Author: 
//
// Modify history:
//      Kevin  2008-6-19 迁移
//      Kevin  2008-6-25 把ShapeLine.cs 文件 中的LineDirection枚举存放到Enums文件中
//      Jerry Xu 2009-4-14 Update method:GenerateLineImage()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Settings;
using ProWrite.Core.Validation;
using ProWrite.Unsafe;

namespace ProWrite.Entity.Shape
{
    /// <summary>
    /// Summary description for ShapeFigure.
    /// // 2008-6-19, Kevin 迁移
    ///    2008-11-12 Jay
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class ShapeLine : ShapePaint, IEquatable<ShapeLine>
    {
        #region Non Serialized Fields
        [NonSerialized]
        private MovePoints linePoints = new MovePoints();
        [NonSerialized]
        private int handerNum = 0;

        //  Graphic objects for hit test
        [NonSerialized]
        private GraphicsPath areaPath = null;
        [NonSerialized]
        private Pen areaPen = null;
        [NonSerialized]
        private Region areaRegion = null;

        #endregion

        #region Serialized Fields
        private Point _startSignPoint = Point.Empty;
        private Point _endSignPoint = Point.Empty;
        #endregion

        #region Properties

        [Browsable(false)]
        public MovePoints LinePoints
        {
            get
            {
                if (linePoints.IsEmpty)
                {
                    linePoints.MStart = _startSignPoint;
                    linePoints.MEnd = _endSignPoint;
                    linePoints.VBound = _virtualBounds;
                }
                return linePoints;
            }
            set
            {
                if (value != linePoints)
                {
                    MovePoints old = linePoints;
                    InnerMove(value);
                    OnPropertyChanged("LinePoints", value, old);
                }
            }
        }

        [Category("Shape")]
        [Browsable(false)]
        public Point VirtualStart
        {
            get { return _startSignPoint.PointMultiplyInt(Zoom);}
            set 
            {
                value = new Point((value.X * 1d / Zoom).GetRoundInt(), (value.Y * 1d / Zoom).GetRoundInt());
                Start = value;
            }
        }

        [Category("Shape")]
        [Browsable(false)]
        public Point VirtualEnd
        {
            get { return _endSignPoint.PointMultiplyInt(Zoom);}
            set
            {
                value = new Point((value.X * 1d / Zoom).GetRoundInt(), (value.Y * 1d / Zoom).GetRoundInt());
                End = value;
            }
        }

        [Category("Shape")]
        [Browsable(false)]
        public Point Start
        {
            get { return _startSignPoint; }
            set
            {
                if (_startSignPoint != value)
                {
                    Point old = _startSignPoint;
                    _startSignPoint = value;
                    //_startPoint = value.PointPlusInt(Zoom);
                    if (CanTrickEvent)
                    {
                        InnerMoveHandleTo(value.PointMultiplyInt(Zoom), 1);
                        //InnerMoveHandleTo(_startPoint, 1);
                        OnPropertyChanged("Start", value, old);
                    }
                }
            }
        }

        [Category("Shape")]
        [Browsable(false)]
        public Point End
        {
            get { return _endSignPoint; }
            set
            {
                if (_endSignPoint != value)
                {
                    Point old = _endSignPoint;
                    _endSignPoint = value;
                    //_endPoint = value.PointPlusInt(Zoom);
                    if (CanTrickEvent)
                    {
                        InnerMoveHandleTo(value.PointMultiplyInt(Zoom), 2);
                        //InnerMoveHandleTo(_endPoint, 2);
                        OnPropertyChanged("End", value, old);
                    }
                }
            }
        }

        [Browsable(true)]
        [DisplayName("Line Width")]
        [RangeValidator(1, 100)]
        public override int BorderWidth
        {
            get { return _borderWidth; }
            set
            {
                if (value < 1 || value > 100) return;
                if (_borderWidth != value)
                {
                    int old = _borderWidth;
                    _borderWidth = value;
                    SetVirtualBounds(value);
                    OnPropertyChanged("BorderWidth", value, old);
                }
            }
        }
       
        [Browsable(false)]
        public override bool Filled
        {
            get { return false; }
            set { ; }
        }
        
        [Browsable(false)]
        public override Color FillColor
        {
            get { return Color.Transparent;}
            set { ;}
        }

        [Browsable(false)]
        public override int LocationX
        {
            get { return base.LocationX;}
            set { base.LocationX = value;}
        }

        [Browsable(false)]
        public override int LocationY
        {
            get { return base.LocationY; }
            set { base.LocationY = value; }
        }

        [Browsable(false)]
        public override int Height
        {
            get { return base.Height; }
            set {   base.Height = value;}
        }

        [Browsable(false)]
        public override int Width
        {
            get { return base.Width; }
            set { base.Width = value; }
        }

        [Browsable(false)]
        public override int Zoom
        {
            get { return base.Zoom; }
            set
            {
                if (_zoom != value)
                {
                    BeginEdit();
                    base.Zoom = value;
                    //_startPoint = _startSignPoint.PointPlusInt(value);
                    InnerMoveHandleTo(_startSignPoint.PointMultiplyInt(value), 1);
                    //_endPoint = _endSignPoint.PointPlusInt(value);
                    InnerMoveHandleTo(_endSignPoint.PointMultiplyInt(value), 2);
                    EndEdit();
                }
            }
        }

        [Browsable(false)]
        public Point RelationStart
        {
            get
            {
                Point tmp = new Point(VirtualStart.X - VirtualBounds.X, VirtualStart.Y - VirtualBounds.Y);
                tmp.X = tmp.X / Zoom;
                tmp.Y = tmp.Y / Zoom;
                return tmp;
            }
        }

        [Browsable(false)]
        public Point RelationEnd
        {
            get
            {
                Point tmp = new Point(VirtualEnd.X - VirtualBounds.X, VirtualEnd.Y - VirtualBounds.Y);
                tmp.X = tmp.X / Zoom;
                tmp.Y = tmp.Y / Zoom;
                if (RelationStart.Equals(tmp))
                    tmp.Offset(1, 1);
                return tmp;
            }
        }
        #endregion

        #region Contruct Method
        public ShapeLine(int zoom, SignType signtype)
            : base(signtype)
        {
            this._zoom = zoom;
        }

        public ShapeLine()
            : this(1, SignType.RGB)
        {
            this._startSignPoint = new Point(0, 0);
            this._endSignPoint = new Point(1, 1);
        }

        public ShapeLine(int zoom, Point start, Point end, int width, Color foreColor, SignType signtype)
            : this(zoom, signtype)
        {
            this._startSignPoint = start;
            this._endSignPoint = end;

            this._borderWidth = width;
            this._borderColor = SignTypeHandler.ConvertColor(foreColor, signtype);
        }

        public ShapeLine(int zoom, Point start, Point end, ShapePaintPropertyInfo lineInfo, SignType signtype)
            : this(zoom, signtype)
        {
            this._startSignPoint = start;
            this._endSignPoint = end;

            this._borderColor = SignTypeHandler.ConvertColor(lineInfo.BorderColor, signtype);
            this._borderWidth = lineInfo.BorderWidth;
            this.LineDashStyle = lineInfo.LineDashStyle;
        }

        #endregion

        #region public method

        public override int HandleCount
        {
            get { return 2; }
        }

        public override Point GetHandle(int handleNumber)
        {
            if (handleNumber == 1)
                return VirtualStart;
            else
                return VirtualEnd;
        }

        public override Rectangle GetHandleRectangle(int handleNumber)
        {
            Point point = GetHandle(handleNumber);
            return new Rectangle(point.X - 4, point.Y - 4, 8, 8);
        }

        public override int HitTest(Point point)
        {
            if (!IsVisible) return -1;
            if (IsSelected)
                for (int i = 1; i <= HandleCount; i++)
                {
                    GraphicsPath gp = new GraphicsPath();
                    gp.AddRectangle(GetHandleRectangle(i));
                    bool vis = gp.IsVisible(point);
                    gp.Dispose();
                    if (vis)
                        return i;
                }
            // OK, so the point is not on a selection handle, is it anywhere else on the line?
            if (PointInObject(point))
                return 0;
            return -1;
        }

        public override bool IntersectsWith(Rectangle rectangle)
        {
            if (!IsVisible) return false;
            CreateObjects();
            return areaRegion.IsVisible(rectangle);
        }

        public override Cursor GetHandleCursor(int handleNumber)
        {
            switch (handleNumber)
            {
                case 1:
                case 2:
                    return Cursors.SizeWE;
                default:
                    return Cursors.Default;
            }
        }
        //resize the shape
        public override void MoveHandleTo(Point point, int handleNumber)
        {
            if (handleNumber == 1)
                VirtualStart = point;
            else if (handleNumber == 2)
                VirtualEnd = point;
        }
        //move the shape
        public override void Move(int deltaX, int deltaY)
        {
            if (Math.Abs(deltaX) < Zoom && Math.Abs(deltaY) < Zoom) return;

            IsMoving = true;
            LinePoints = InnerMove(deltaX, deltaY);
            IsMoving = false;
        }

        

        private void InnerMoveHandleTo(Point point, int handleNumber)
        {
            //记住当前使用的那个handler
            handerNum = handleNumber; 
            //存放不变的点
            Point sp = Point.Empty;

            if (handleNumber == 1)
                sp = VirtualEnd;
            else
                sp = VirtualStart;

            SetVirtualBoundsNew(sp, point);
            IsSelected = true;
            Invalidate();
            //areaPath.Widen(areaPen);
            //Invalidate();
        }

        private void InnerMove(MovePoints points)
        {
            _startSignPoint = points.MStart;
            _endSignPoint = points.MEnd;
            _virtualBounds = points.VBound;
 
            _isSelected = true;
            Invalidate();
        }

        public void ChangeEndPoint(Point endPoint)
        {
            IsMoving = true;
            VirtualEnd = endPoint;
            //IsMoving = true;
            //Rectangle rect = VirtualBounds;
            //rect.Size = size;
            IsMoving = false;
        }

        private MovePoints InnerMove(int deltaX, int deltaY)
        {
            linePoints.MStart = _startSignPoint;
            linePoints.MEnd = _endSignPoint;
            linePoints.VBound = VirtualBounds;

            Rectangle rect = VirtualBounds;
            int offsetX = deltaX.GetRoundInt(Zoom);
            int offsetY = deltaY.GetRoundInt(Zoom);
            rect.Offset(offsetX * Zoom, offsetY * Zoom);

            Size dsize = new Size(offsetX, offsetY);

            return new MovePoints(_startSignPoint + dsize, _endSignPoint + dsize, rect);
        }


        public override void Accept(IVisitor visitor)
        {
            visitor.VisitLine(this);
        }

        private void CommonPaintLine(Graphics g, Rectangle bound, bool play)
        {
            int w = BorderWidth * Zoom;
            Color drawColor = BorderColor;
            if (drawColor == Color.Black)
                drawColor = Color.FromArgb(255, 1,255, 1);

            using (Image tmpimg = GenerateLineImage())
            {
                InterpolationMode oldmode = g.InterpolationMode;
                g.InterpolationMode = InterpolationMode.NearestNeighbor;
                if (play)
                {
                    Point offsetBound = new Point(VirtualBounds.X - bound.X, VirtualBounds.Y - bound.Y);
                    g.DrawImage(tmpimg, new Rectangle(offsetBound, VirtualBounds.Size), 0, 0, tmpimg.Width, tmpimg.Height, GraphicsUnit.Pixel);
                }
                else
                    g.DrawImage(tmpimg, VirtualBounds, 0, 0, tmpimg.Width, tmpimg.Height, GraphicsUnit.Pixel);

                g.InterpolationMode = oldmode;
            }
        }

        public override void Move(Point point)
        {
            int w = (_virtualBounds.Location.X - point.X) / Zoom;
            int h = (_virtualBounds.Location.Y - point.Y) / Zoom;
            Size size = new Size(w,h);
            MovePoints moves = new MovePoints();
            moves.MStart = _startSignPoint - size;
            moves.MEnd = _endSignPoint - size;
            moves.VBound = new Rectangle(point, _virtualBounds.Size);
            LinePoints = moves;
        }
        public override void PaintFigure(Graphics g, Rectangle bounds)
        {
            CommonPaintLine(g, bounds,true);
        }

        protected internal override void DrawOutputImage(Graphics g)
        {
            using (Pen pen = new Pen(MonoSignBoardColor, _borderWidth * Zoom))
            //using (Pen pen = new Pen(_borderColor, _borderWidth * Zoom))
            {
                pen.DashStyle = LineDashStyle;
                g.DrawLine(pen, VirtualStart, VirtualEnd);
            }
        }

        public override void PopulateSignInfo(SignType signType, Size signSize, int zoom)
        {
            _zoom = zoom;
            SignType = signType;
            SignSize = signSize;
            
            SetVirtualBounds();
        }

        public override void Populate(Point location, Size size, SignType signType, Size signSize, int zoom)
        {
            if (SignSize != signSize)
            {
                Size nsize = GetOffsetSizeBySign(signSize);
              
                double wrate = 1d * signSize.Width / SignSize.Width;
                double hrate = 1d * signSize.Height / SignSize.Height;
                double rate = wrate <= hrate ? wrate : hrate;

                _startSignPoint.X = (int)Math.Round(_startSignPoint.X * rate);
                _startSignPoint.Y = (int)Math.Round(_startSignPoint.Y * rate);
                _endSignPoint.X = (int)Math.Round(_endSignPoint.X * rate);
                _endSignPoint.Y = (int)Math.Round(_endSignPoint.Y * rate);
                _startSignPoint = _startSignPoint + nsize;
                _endSignPoint = _endSignPoint + nsize;
            }

            base.Populate(location, size, signType, signSize, zoom);
        }

        public Size GetOffsetSizeBySign(Size nSignSize)
        {
            decimal oldSizeRatio = decimal.Divide(this.SignSize.Width, this.SignSize.Height);
            decimal newSizeRatio = decimal.Divide(nSignSize.Width, nSignSize.Height);
            decimal tempZoom;
            int newWidth = 0, newHeight = 0;
            int widthOffset = 0, heightOffset = 0;
            if (oldSizeRatio <= newSizeRatio)
            {
                tempZoom = decimal.Divide(nSignSize.Height, this.SignSize.Height);
                newWidth = (int)Math.Round(this.SignSize.Width * tempZoom);
                widthOffset = (int)Math.Round((double)(nSignSize.Width - newWidth) / 2);
            }
            else
            {
                tempZoom = decimal.Divide(nSignSize.Width, this.SignSize.Width);
                newHeight = (int)Math.Round(this.SignSize.Height * tempZoom);
                heightOffset = (int)Math.Round((double)(nSignSize.Height - newHeight) / 2);
            }
            return new Size(widthOffset, heightOffset);
        }


        public void SetVirtualBoundsNew(Point sp, Point dp)
        {
            if (sp.Equals(dp))
                dp += new Size(Zoom, Zoom);

            //sp.X = Convert.ToInt32(sp.X);
            //sp.Y = Convert.ToInt32(sp.Y);
            //dp.X = Convert.ToInt32(dp.X);
            //dp.Y = Convert.ToInt32(dp.Y);

            CreateObjects(sp, dp);

            Rectangle adjRect = Rectangle.Round(areaPath.GetBounds());
            adjRect = ExtendBoundsByZoom(adjRect, Zoom);

            _virtualBounds = adjRect;
        }

        public void SetVirtualBounds(int lineWidth)
        {
            if (_startSignPoint.Equals(_endSignPoint))
                _startSignPoint += new Size(1, 1);

            if (_startSignPoint.X == _endSignPoint.X || _startSignPoint.Y == _endSignPoint.Y)
            {
                CreateObjects(VirtualStart, VirtualEnd);
                Rectangle adjRect = Rectangle.Round(areaPath.GetBounds());
                adjRect = ExtendBoundsByZoom(adjRect, Zoom);
                _virtualBounds = adjRect;
            }
            else
            {
                SetVirtualBoundsNew(VirtualStart, VirtualEnd);
            }
        }

        public override void SetVirtualBounds()
        {
            SetVirtualBoundsNew(VirtualStart, VirtualEnd);
        }

        public override void Normalize()
        {
            if (_startSignPoint.Equals(_endSignPoint))
                if (handerNum == 2)
                    _endSignPoint.Offset(1, 1);
                else
                    _startSignPoint.Offset(1, 1);
        }

        public override ShapeType Type
        {
            get { return ShapeType.Line; }
        }

        public override LayerType LayerType
        {
            get { return LayerType.Paint; }
        }

        public override ShapeBase NewInstance()
        {
            return new ShapeLine();
        }

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);

            ShapeLine other = shape as ShapeLine;
            if (other != null)
            {
                _startSignPoint = other._startSignPoint;
                _endSignPoint = other._endSignPoint;
            }
        }

        #endregion

        #region Protected Method

        protected override bool PointInObject(Point point)
        {
            CreateObjects();
            return areaRegion.IsVisible(point);
        }

        // Create graphic objects used for hit test.
        protected void CreateObjects()
        {
            CreateObjects(VirtualStart, VirtualEnd);
        }

        // Create graphic objects used for hit test.
        protected void CreateObjects(Point start, Point end)
        {
            Invalidate();
            // Create path which contains wide line for easy mouse selection
            areaPath = new GraphicsPath();
            // Take into account the width of the pen used to draw the actual object
            areaPen = new Pen(Color.Black, BorderWidth * Zoom < Zoom ? Zoom : BorderWidth * Zoom);

            // Prevent Out of Memory crash when startPoint == endPoint
            if (start.Equals(end))
            {
                end.X += BorderWidth * Zoom;
                end.Y += BorderWidth * Zoom;
            }

            if (start.X < 0) start.X = 0;
            if (start.Y < 0) start.Y = 0;
            if (end.X < 0) end.X = 0;
            if (end.Y < 0) end.Y = 0;

            
            areaPath.AddLine(start.X, start.Y, end.X, end.Y);

            Point leftPoint  ;
            Point rightPoint ;
            Point leftPoint2 ;
            Rectangle rec = Rectangle.Round(areaPath.GetBounds());

            if (start.Y == end.Y)
            {
                rec.Height = BorderWidth * Zoom;
                leftPoint = new Point(start.X, start.Y + BorderWidth * Zoom / 2);
                rightPoint = new Point(end.X, end.Y + BorderWidth * Zoom / 2);
                leftPoint2 = new Point(start.X, start.Y - BorderWidth * Zoom / 2);
            }
            else if (start.X == end.X)
            {
                rec.Width = BorderWidth * Zoom;
                leftPoint = new Point(start.X - BorderWidth * Zoom / 2, start.Y);
                rightPoint = new Point(start.X + BorderWidth * Zoom /2, start.Y);
                leftPoint2 = new Point(end.X - BorderWidth * Zoom / 2, end.Y); ;
            }
            else
            {
                rec.Width += BorderWidth * Zoom;
                rec.Height += BorderWidth * Zoom;

                leftPoint = new Point(rec.Left - BorderWidth * Zoom / 2, rec.Y + BorderWidth * Zoom / 2);
                rightPoint = new Point(rec.Right + BorderWidth * Zoom / 2, rec.Y + BorderWidth * Zoom / 2);
                leftPoint2 = new Point(rec.Left - BorderWidth * Zoom / 2, rec.Bottom + BorderWidth * Zoom / 2);
            }


            Matrix matrix = null; //= new Matrix(rec, new Point[] { leftPoint, rightPoint, leftPoint2 });
            try
            {
                GetCloneObject(matrix, rec, new Point[] { leftPoint, rightPoint, leftPoint2 });
                areaPath.Widen(areaPen, matrix);
            }
            finally
            {
                if (matrix != null)
                    matrix.Dispose();
            }

            // Rotate the path about it's center if necessary
            if (Rotation != 0)
            {
                RectangleF pathBounds = areaPath.GetBounds();
                Matrix m = new Matrix();
                m.RotateAt(Rotation, new PointF(pathBounds.Left + (pathBounds.Width / 2), pathBounds.Top + (pathBounds.Height / 2)), MatrixOrder.Append);
                areaPath.Transform(m);
                m.Dispose();
            }

            areaRegion = new Region(areaPath);
        }

        private void GetCloneObject(Matrix getCopy, Rectangle rec, Point[] points)
        {
            Matrix matrix = new Matrix(rec, points);
            getCopy = matrix.Clone();
            matrix.Dispose();
        }

        /// <summary>
        /// Invalidate object.
        /// When object is invalidated, path used for hit test
        /// is released and should be created again.
        /// </summary>
        protected void Invalidate()
        {
            if (areaPath != null) areaPath.Dispose();

            if (areaPen != null)  areaPen.Dispose();
          
            if (areaRegion != null) areaRegion.Dispose();
        }

        #endregion

        #region Private Function
        private Image GenerateLineImage()
        {
            int w = VirtualBounds.Width / Zoom;
            int h = VirtualBounds.Height / Zoom;

            using (Image lineImg = new Bitmap(w==0?1:w, h==0?1:h))
            {
                
                using (Graphics gh = Graphics.FromImage(lineImg))
                {
                    gh.Clear(Color.Transparent);
                    Point start = RelationStart;
                    Point end = RelationEnd;

                    PenAlignment pl = PenAlignment.Inset;

                    using (var pen = _cache.GetPen(DrawingColor, BorderWidth, pl, LineDashStyle))
                    {
                        gh.DrawLine(pen
                                , start
                                , end);
                    }
                }

                return FormatImage(lineImg, VirtualBounds);
            }
        }

        /// <summary>
        /// 调整Rectangle的四个定点放大到格线上
        /// </summary>
        public Rectangle ExtendBoundsByZoom(Rectangle bounds, int zoom)
        {
            int x=bounds.X;
            int y = bounds.Y;
            int r = bounds.Right;
            int b = bounds.Bottom;

            if (bounds.X / zoom != 0)
                x = ((int)Math.Floor(bounds.X * 1d / zoom)) * zoom - zoom;

            if (bounds.X / zoom != 0)
                y = ((int)Math.Floor(bounds.Y * 1d / zoom)) * zoom - zoom;

            if(bounds.Right / zoom != 0)
               r = ((int)Math.Floor(bounds.Right * 1d / zoom)) * zoom + zoom;

            if (bounds.Bottom / zoom != 0)
                b = ((int)Math.Floor(bounds.Bottom * 1d / zoom)) * zoom + zoom;

            return new Rectangle(x, y, r - x, b - y);
        }
        #endregion

        #region IEquatable<ShapeLine> Members

        public bool Equals(ShapeLine other)
        {
            if (other == null)
                return false;
            if (other._endSignPoint != _endSignPoint)
                return false;
            if (other._startSignPoint != _startSignPoint)
                return false;

            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ShapeLine);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        #endregion

        protected override void Dispose(bool disposing)
        {
            Invalidate();
            base.Dispose(disposing);
        }
    }

    [Serializable]
    public struct MovePoints
    {
        public Point MStart;
        public Point MEnd;
        public Rectangle VBound;
        public MovePoints(Point start, Point end, Rectangle vbound)
        {
            MStart = start;
            MEnd = end;
            VBound = vbound;
        }

        public static bool operator ==(MovePoints s1, MovePoints s2)
        {
            if (s1.MEnd == s2.MEnd && s1.MStart == s2.MStart && s1.VBound == s2.VBound) return true;
            return false;
        }
        public static bool operator !=(MovePoints s1, MovePoints s2)
        {
            if (s1.MEnd == s2.MEnd && s1.MStart == s2.MStart && s1.VBound == s2.VBound) return false;
            return true;
        }

        public bool IsEmpty
        {
            get
            {
                if (MStart.IsEmpty && MEnd.IsEmpty && VBound.IsEmpty) return true;
                return false;
            }
        }
    }
}