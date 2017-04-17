using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Shape
{
    /// <summary>
	/// Summary description for ShapeBase.
	/// // 2008-11-11, Added by Jay
	/// </summary>
    public partial class ShapeBase
    {
        #region Properties
        [Browsable(false)]
        public bool IsMoving
        {
            get { return _isMoving; }
            set { _isMoving = value; }
        }
        /// <summary>
        /// Number of handles
        /// </summary>
        [Browsable(false)]
        public virtual int HandleCount
        {
            get { return 8; }
        }

        [Browsable(false)]
        public object Tag
        {
            get { return tag; }
            set { tag = value; }
        }

        //决定是否触发图形对象的属性改变事件。
        //public bool CanTrickEvent = true;

        #endregion Properties
        
        #region Virtual Functions

        public virtual void Move(Point point)
        {
            Rectangle rect = this.VirtualBounds;
            rect.Location = point;
            VirtualBounds = rect;
        }

        public virtual Point GetHandle(int handleNumber)
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

        /// <summary>
        /// Get handle rectangle by 1-based number
        /// setting the size of hander's rectangle
        /// </summary>
        /// <param name="handleNumber"></param>
        /// <returns></returns>
        public virtual Rectangle GetHandleRectangle(int handleNumber)
        {
            // Take into account width of pen
            Point point = GetHandle(handleNumber);
            int z = Zoom < 8 ? 8 : Zoom;
            return new Rectangle(point.X- z/2, point.Y - z/2, z, z);
        }

        // Draw tracker for selected object
        public virtual void DrawTracker(Graphics g)
        {
            if (!IsSelected)
                return;

            int width = Zoom > 2 ? 2 : Zoom;
            using(var pen = _cache.GetPen(Color.LightBlue, width, PenAlignment.Inset))
                for (int i = 1; i <= HandleCount; i++)
                    g.DrawRectangle(pen, GetHandleRectangle(i));
        }

        /// <summary>
        /// Hit test.
        /// Return value:  <= -1 - no hit
        ///                 = 0 - hit anywhere
        ///                 > 1 - handle number
        public virtual int HitTest(Point point)
        {
            if (!IsVisible) return -1;
            if (IsSelected)
            {
                for (int i = 1; i <= HandleCount; i++)
                {
                    if (GetHandleRectangle(i).Contains(point))
                        return i;
                }
            }

            if (PointInObject(point))
                return 0;

            return -1;
        }

        /// <summary>
        /// Test whether point is inside of the object
        /// </summary>
        protected virtual bool PointInObject(Point point)
        {
            return _virtualBounds.Contains(point);
        }

        /// <summary>
        /// Get cursor for the handle
        /// </summary>
        public virtual Cursor GetHandleCursor(int handleNumber)
        {
            switch (handleNumber)
            {
                case 1:
                    return Cursors.SizeNWSE;
                case 2:
                    return Cursors.SizeNS;
                case 3:
                    return Cursors.SizeNESW;
                case 4:
                    return Cursors.SizeWE;
                case 5:
                    return Cursors.SizeNWSE;
                case 6:
                    return Cursors.SizeNS;
                case 7:
                    return Cursors.SizeNESW;
                case 8:
                    return Cursors.SizeWE;
                default:
                    return Cursors.Default;
            }
        }

        /// <summary>
        /// Test whether object intersects with rectangle
        /// </summary>
        /// <param name="rectangle"></param>
        /// <returns></returns>
        public virtual bool IntersectsWith(Rectangle rectangle)
        {
            return IsVisible ? VirtualBounds.IntersectsWith(rectangle) : false;
        }

        /// <summary>
        /// Move object
        /// </summary>
        public virtual void Move(int deltaX, int deltaY)
        {
            IsMoving = true;
            //_virtualBounds.X += deltaX;
            //_virtualBounds.Y += deltaY;
            Rectangle moveRect = _virtualBounds;
            moveRect.Offset(deltaX, deltaY);

            //SetVirtualBounds();
            VirtualBounds = FormatBoundsByZoom(moveRect, Zoom);
            IsChanged = true;
            IsMoving = false;
        }

        /// <summary>
        /// Move handle to the point
        /// </summary>
        public virtual void MoveHandleTo(Point point, int handleNumber)
        {
            int left = VirtualBounds.Left;
            int top = VirtualBounds.Top;
            int right = VirtualBounds.Right;
            int bottom = VirtualBounds.Bottom;

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
            
            IsChanged = true;
            VirtualBounds = FormatBoundsByZoom(new Rectangle(left, top, right - left, bottom - top), Zoom);
            //SetRectangle(left, top, right - left, bottom - top);
        }

        public virtual void SetVirtualBounds()
        {
            int x, y, width, height;
            if (_virtualBounds.X >= 0)
            {
                if (_virtualBounds.X % Zoom > Zoom / 2)
                    x = _virtualBounds.X % _zoom == 0 ? _virtualBounds.X : _virtualBounds.X + (_zoom - _virtualBounds.X % _zoom);
                else
                    x = _virtualBounds.X % _zoom == 0 ? _virtualBounds.X : _virtualBounds.X - _virtualBounds.X % _zoom;
            }
            else
            {
                if (-_virtualBounds.X % _zoom > _zoom / 2)
                    x = _virtualBounds.X - _zoom - _virtualBounds.X % _zoom;
                else
                    x = _virtualBounds.X - _virtualBounds.X % _zoom;
            }

            if (_virtualBounds.Y >= 0)
            {
                if (_virtualBounds.Y % _zoom > _zoom / 2)
                    y = _virtualBounds.Y % _zoom == 0 ? _virtualBounds.Y : _virtualBounds.Y + (_zoom - _virtualBounds.Y % _zoom);
                else
                    y = _virtualBounds.Y % _zoom == 0 ? _virtualBounds.Y : _virtualBounds.Y - _virtualBounds.Y % _zoom;
            }
            else
            {
                if (-_virtualBounds.Y % _zoom > _zoom / 2)
                    y = _virtualBounds.Y - _zoom - _virtualBounds.Y % _zoom;
                else
                    y = _virtualBounds.Y - _virtualBounds.Y % _zoom;
            }

            if (_virtualBounds.Width % _zoom > _zoom / 2)
                width = _virtualBounds.Width % _zoom == 0 ? _virtualBounds.Width : _virtualBounds.Width + (_zoom - _virtualBounds.Width % _zoom);
            else
                width = _virtualBounds.Width % _zoom == 0 ? _virtualBounds.Width : _virtualBounds.Width - _virtualBounds.Width % _zoom;

            if (_virtualBounds.Height % _zoom > _zoom / 2)
                height = _virtualBounds.Height % _zoom == 0 ? _virtualBounds.Height : _virtualBounds.Height + (_zoom - _virtualBounds.Height % _zoom);
            else
                height = _virtualBounds.Height % _zoom == 0 ? _virtualBounds.Height : _virtualBounds.Height - _virtualBounds.Height % _zoom;

            _virtualBounds.X = x;
            _virtualBounds.Y = y;
            _virtualBounds.Width = width == 0 ? 1 : width;
            _virtualBounds.Height = height == 0 ? 1 : height;
        }

        //public virtual void DrawOutputImage(Graphics g)
        //{
        //}
        
        /// <summary>
        /// Normalize object.
        /// Call this function in the end of object resizing.
        /// </summary>
        public virtual void Normalize()
        {
        }

        protected virtual void Initialize()
        {
        }
        #endregion Virtual Functions

        protected virtual void SetRectangle(int x, int y, int width, int height)
        {
            //VirtualBounds.X = x;
            //rectangle.Y = y;
            //rectangle.Width = width;
            //rectangle.Height = height;

            _virtualBounds.X = x;
            _virtualBounds.Y = y;

            _virtualBounds.Width = width == 0 ? 1 : width;
            _virtualBounds.Height = height == 0 ? 1 : height;
        }
    }

}
