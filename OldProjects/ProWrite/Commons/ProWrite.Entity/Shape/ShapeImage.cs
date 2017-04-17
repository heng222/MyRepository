//---------------------------------------------------------------------
//
// File: ShapeImage.cs
//
// Description:
// Shape shape class
//
// Author: 
//
// Modify History:
//      Kevin 2008-6-19 Ç¨ÒÆ
//      Kevin 2008-6-27 Refactor
//      Jerry Xu 2009-2-20 Update property:IsGif Serializable
//      Jerry Xu 2009-5-5 Update method:GenerateUploadImage(string ImageFile)
//      Jerry Xu 2009-5-26 Update method:UpdateDestBounds()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Runtime.Serialization;
using System.Windows.Forms;
using ProWrite.Core;
using System.Xml.Serialization;
using ProWrite.Unsafe;
using System.IO;
using ProWrite.Entity.Library;
using ProWrite.UFE;
using System.Threading.Tasks;

namespace ProWrite.Entity.Shape
{
    /// <summary>
    /// Summary description for ShapeImage.
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public partial class ShapeImage : ShapeBase, IEquatable<ShapeImage>, IFileHandle
    {
        #region Non Serialized Fields
        [NonSerialized]
        private string _fileHandle;
        [NonSerialized]
        private Bitmap _icon;
        [NonSerialized]
        private Image _image;
        [NonSerialized]
        internal static readonly Font Tahoma_Font = new Font("Tahoma", 16);
        /// <summary>
        /// 
        /// </summary>

        public bool IsGif;
        #endregion

        #region Serialized Fields
        private string _imageUrl = "";
        private PictureBoxSizeType _sizeMode = PictureBoxSizeType.Zoom;
        private Rectangle _orgiBounds = Rectangle.Empty;
        private Rectangle imageBounds = Rectangle.Empty;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public ShapeImage()
        {
        }

        #region Properties

        internal Image _Image
        {
            get { return _image; }
            set { _image = value; }
        }

        [Category("Layer")]
        [Browsable(true)]
        public override bool IsBackground
        {
            get { return base.IsBackground; }
            set
            {
                SetBackground(value);
            }
        }

#if DEBUG
        [Browsable(true)]
#else
        [Browsable(false)]
#endif
        public string ImageUrl
        {
            get { return _imageUrl; }
            set
            {
                if (string.Equals(value, _imageUrl, StringComparison.OrdinalIgnoreCase))
                    return;
                string old = _imageUrl;
                _imageUrl = value;
                if (string.IsNullOrEmpty(value))
                    this.Image = null;

                OnPropertyChanged("ImageUrl", value, old);
            }
        }

        [Browsable(false)]
        [XmlIgnore]
        string IFileHandle.FileUrl
        {
            get { return ImageUrl; }
            set { ImageUrl = value; }
        }

        [Browsable(false)]
        [XmlIgnore]
        public string FileHandle
        {
            get { return _fileHandle; }
            set { _fileHandle = value; }
        }


        [XmlIgnore]
        [Category("Picture")]
        [DisplayName("Picture")]
        public Image Image
        {
            get
            {
                if (_icon != null)
                {
                    return _icon;
                }
                GetImage();
                return _image;
            }
            set
            {
                if (_image == value)
                    return;
                Image old = _image;

                if (value != null)
                {
                    _image = FormatImage(value);
                    _icon = (Bitmap)_image;
                    ImageChanged = true;
                    value.Dispose();
                    value = null;
                }
                else
                {
                    _image = null;
                    _icon.Dispose();
                    _icon = null;
                }

                OnPropertyChanged("Image", _image, old);
            }
        }

        [Browsable(false)]
        public bool ImageChanged
        { get; set; }

        [Category("Picture")]
        public PictureBoxSizeType SizeMode
        {
            get { return _sizeMode; }
            set
            {
                if (_sizeMode != value)
                {
                    PictureBoxSizeType old = _sizeMode;
                    _sizeMode = value;
                    ComputeDestBound();
                    OnPropertyChanged("SizeMode", value, old);

                }
            }
        }
        #endregion

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            GetImage();
        }

        private void GetImage()
        {
            if (_image == null && !string.IsNullOrEmpty(_imageUrl) && File.Exists(_imageUrl))
            {
                Image image = IOHelper.GetImageFromFile(_imageUrl);
                _image = FormatImage(image);
                if (image != null)
                {
                    image.Dispose();
                    image = null;
                }
            }
        }

      
        #region override
        public override ShapeType Type
        {
            get { return ShapeType.Image; }
        }

        public override LayerType LayerType
        {
            get { return LayerType.Image; }
        }

        [Browsable(false)]
        public override int Zoom
        {
            get { return _zoom == 0 ? 1 : _zoom; }
            set
            {
                if (value != _zoom)
                {
                    if (_virtualBounds != Rectangle.Empty)
                    {
                        _virtualBounds.Location = new Point(_virtualBounds.Location.X / Zoom * value, _virtualBounds.Location.Y / Zoom * value);
                        _virtualBounds.Size = new Size(_virtualBounds.Size.Width / Zoom * value, _virtualBounds.Size.Height / Zoom * value);
                    }
                    if(_destBounds != Rectangle.Empty)
                    {
                        UpdateDestBounds();
                    }
                    _zoom = value;
                    _isChanged = true;
                }
                else
                {
                    _isChanged = false;
                }
            }
        }

	    internal void UpdateDestBounds()
	    {
            int x;
            int y;
            if (_image == null)
                return;
	        switch (_sizeMode)
	        {
                case PictureBoxSizeType.CenterImage:
                    Rectangle imageBounds = Rectangle.Empty;
                    //Rectangle destBounds = Rectangle.Empty;
                    int width;
                    int height;


                    Point loc = new Point();

                    width = _virtualBounds.Width < _image.Width ? _virtualBounds.Width : _image.Width;
                    height = _virtualBounds.Height < _image.Height ? _virtualBounds.Height : _image.Height;
                    loc.X = _image.Width / 2 - width / 2;
                    loc.Y = _image.Height / 2 - height / 2;
                    x = _virtualBounds.Location.X;
                    y = _virtualBounds.Location.Y;

                    if (_virtualBounds.Width > _image.Width)
                    {
                        x += (_virtualBounds.Width - _image.Width) / 2;
                    }

                    if (_virtualBounds.Height > _image.Height)
                    {
                        y += (_virtualBounds.Height - _image.Height) / 2;
                    }

                    imageBounds = new Rectangle(loc, new Size(width, height));
                    _destBounds = new Rectangle(x, y, width, height);
                    _destBounds = FormatBoundsByZoom(_destBounds, Zoom);

                    break;
                case PictureBoxSizeType.Zoom:

                    //GraphicsUnit gu = GraphicsUnit.Pixel;

                    float wn = _virtualBounds.Width * 1f / _image.Width * 1f;
                    float hn = _virtualBounds.Height * 1f / _image.Height * 1f;
                    float n = wn < hn ? wn : hn;
                    x = _virtualBounds.Location.X + _virtualBounds.Width / 2 - (int)(n * _image.Width) / 2;
                    y = _virtualBounds.Location.Y + _virtualBounds.Height / 2 - (int)(n * _image.Height) / 2;

                    _destBounds = new Rectangle(x, y, (int)(n * _image.Width), (int)(n * _image.Height));
                    if (VirtualBounds.X % Zoom == 0 && VirtualBounds.Y % Zoom == 0 && VirtualBounds.Width % Zoom == 0 && VirtualBounds.Height % Zoom == 0)
                    {
                        _destBounds = FormatBoundsByZoom(_destBounds, Zoom);
                    }
                    ComputePlayerBound(_destBounds, SignSize);
                    //if (_destBounds.Width < PlayWindowsWidthPixel && _destBounds.Height < PlayWindowsHeightPixel)
                    //{
                    //    int virtualBoundsWidth = VirtualBounds.Width;
                    //    int virtualBoundsHeight = VirtualBounds.Height;
                    //    while (virtualBoundsWidth < PlayWindowsWidthPixel && virtualBoundsHeight < PlayWindowsHeightPixel)
                    //    {
                    //        virtualBoundsWidth += virtualBoundsWidth;
                    //        virtualBoundsHeight += virtualBoundsHeight;
                    //    }
                    //    _destBounds.Width = virtualBoundsWidth;
                    //    _destBounds.Height = virtualBoundsHeight;
                    //}
                    
                    break;
                default:
                    _destBounds = _virtualBounds;
                    break;
	        }
	    }

        public void ComputeDestBound()
        {
            Rectangle bounds = base.VirtualBounds;
            Rectangle _destBounds = Rectangle.Empty;

            if (_image != null)
                switch (_sizeMode)
                {
                    case PictureBoxSizeType.StretchImage:
                        if (_orgiBounds != RectangleF.Empty)
                        {
                            bounds = _orgiBounds;
                            _orgiBounds = Rectangle.Empty;
                        }
                        break;
                    case PictureBoxSizeType.CenterImage:
                        int centerW;
                        int centerH;
                        int ix;
                        int iy;

                        Point loc = new Point();
                        if (_orgiBounds != Rectangle.Empty)
                        {
                            bounds = _orgiBounds;
                            _orgiBounds = Rectangle.Empty;
                        }

                        centerW = bounds.Width < _image.Width ? bounds.Width : _image.Width;
                        centerH = bounds.Height < _image.Height ? bounds.Height : _image.Height;
                        loc.X = _image.Width / 2 - centerW / 2;
                        loc.Y = _image.Height / 2 - centerH / 2;
                        ix = bounds.Location.X;
                        iy = bounds.Location.Y;

                        if (bounds.Width > _image.Width)
                        {
                            ix += (bounds.Width - _image.Width) / 2;
                        }

                        if (bounds.Height > _image.Height)
                        {
                            iy += (bounds.Height - _image.Height) / 2;
                        }

                        _destBounds = new Rectangle(ix, iy, centerW, centerH);
                        imageBounds = new Rectangle(loc, new Size(centerW, centerH));
                        break;
                    case PictureBoxSizeType.Zoom:
                        int x, y;
                        if (_orgiBounds != Rectangle.Empty)
                        {
                            bounds = _orgiBounds;
                            _orgiBounds = Rectangle.Empty;
                        }
                        float wn = bounds.Width * 1f / _image.Width * 1f;
                        float hn = bounds.Height * 1f / _image.Height * 1f;
                        float n = wn < hn ? wn : hn;
                        x = bounds.Location.X + bounds.Width / 2 - (int)(n * _image.Width) / 2;
                        y = bounds.Location.Y + bounds.Height / 2 - (int)(n * _image.Height) / 2;
                        _destBounds = new Rectangle(x, y, (int)(n * _image.Width), (int)(n * _image.Height));
                        if (VirtualBounds.X % Zoom == 0 && VirtualBounds.Y % Zoom == 0 && VirtualBounds.Width % Zoom == 0 && VirtualBounds.Height % Zoom == 0)
                        {
                            _destBounds = FormatBoundsByZoom(_destBounds, Zoom);
                        }
                        break;
                }

            base.DestBounds = _destBounds;

            _virtualBounds = bounds;
        }

        public void ComputeDestBoundBatchLoad()
        {
            _image = Image;
            ComputeDestBound();
        }

        public Rectangle PaintImage(Graphics g, ref Rectangle bounds, bool isDrawToBmp)
        {
            Rectangle _destBounds = Rectangle.Empty;
            if (_image != null)
            {
                switch (_sizeMode)
                {
                    case PictureBoxSizeType.StretchImage:
                        PaintStretchImage(g, ref bounds);
                        break;
                    case PictureBoxSizeType.CenterImage:
                        PaintCenterImage(g, ref bounds, ref _destBounds);
                        break;
                    case PictureBoxSizeType.Zoom:
                        PaintZoom(g, ref bounds, ref imageBounds, ref _destBounds);
                        break;
                    default:
                        PaintDefault(g, ref bounds);
                        break;
                }
                if (_destBounds.Height == 0 || _destBounds.Width == 0)
                    CreateEditImage(bounds);
                else
                    CreateEditImage(_destBounds);
            }
            else
            {
                Color c = SignTypeHandler.ConvertColor(Color.White, SignType);
                g.DrawString("Picture", Tahoma_Font, _cache.GetSolidBrush(c), bounds);
            }
            base.DestBounds = _destBounds;
            return _destBounds;
        }

        private void CreateEditImage(Rectangle bounds)
        {
            _icon = new Bitmap(Math.Abs(bounds.Width), Math.Abs(bounds.Height));
            using (Graphics gh = Graphics.FromImage(_icon))
                DrawImage(gh, new Rectangle(0, 0, bounds.Width, bounds.Height));
        }

        /// <summary>
        /// Draw Image
        /// Updated by Louis
        /// </summary>
        private void DrawImage(Graphics g, Rectangle destRect)
        {
            destRect = FormatBounds(destRect);
            using (Image image = FormatImage(_image, destRect))
                SignTypeHandler.SetOutChannel(g, image, SignType, destRect, new Rectangle(new Point(0, 0), image.Size));//g.DrawImage(shape, destRect, new Rectangle(new Point(0, 0), shape.Size), GraphicsUnit.Pixel);
        }

        /// <summary>
        /// Normal Paint
        /// add by Michael
        /// </summary>
        private void PaintNormal(Graphics g, ref Rectangle bounds, ref Rectangle imageBounds, ref Rectangle destBounds)
        {
            int width;
            int height;

            if (_orgiBounds != Rectangle.Empty)
            {
                bounds = _orgiBounds;
                _orgiBounds = Rectangle.Empty;
            }
            width = bounds.Width < _image.Width ? bounds.Width : _image.Width;
            height = bounds.Height < _image.Height ? bounds.Height : _image.Height;
            destBounds = new Rectangle(bounds.Location, new Size(width, height));
            destBounds = FormatBoundsByZoom(destBounds, Zoom);
            imageBounds = new Rectangle(0, 0, width, height);

            DrawImage(g, destBounds);
        }

        /// <summary>
        /// AutoSize Paint
        /// add by Michael
        /// </summary>
        private void PaintAutoSize(Graphics g, ref Rectangle bounds)
        {
            if (_orgiBounds == Rectangle.Empty)
                _orgiBounds = bounds;
            bounds = new Rectangle(_orgiBounds.Location, _image.Size);
            DrawImage(g, bounds);
        }

        /// <summary>
        /// StretchImage Paint
        /// add by Michael
        /// </summary>
        private void PaintStretchImage(Graphics g, ref Rectangle bounds)
        {
            if (_orgiBounds != RectangleF.Empty)
            {
                bounds = _orgiBounds;
                _orgiBounds = Rectangle.Empty;
            }

            DrawImage(g, bounds);
        }

        /// <summary>
        /// CenterImage Paint
        /// add by Michael
        /// </summary>
        private void PaintCenterImage(Graphics g, ref Rectangle bounds, ref Rectangle destBounds)
        {
            Rectangle imageBounds = Rectangle.Empty;
            //Rectangle destBounds = Rectangle.Empty;
            int width;
            int height;
            int x;
            int y;

            Point loc = new Point();
            if (_orgiBounds != Rectangle.Empty)
            {
                bounds = _orgiBounds;
                _orgiBounds = Rectangle.Empty;
            }

            width = bounds.Width < _image.Width ? bounds.Width : _image.Width;
            height = bounds.Height < _image.Height ? bounds.Height : _image.Height;
            loc.X = _image.Width / 2 - width / 2;
            loc.Y = _image.Height / 2 - height / 2;
            x = bounds.Location.X;
            y = bounds.Location.Y;

            if (bounds.Width > _image.Width)
            {
                x += (bounds.Width - _image.Width) / 2;
            }

            if (bounds.Height > _image.Height)
            {
                y += (bounds.Height - _image.Height) / 2;
            }

            imageBounds = new Rectangle(loc, new Size(width, height));
            destBounds = new Rectangle(x, y, width, height);
            destBounds = FormatBoundsByZoom(destBounds, Zoom);
            DrawImage(g, destBounds);
        }

        /// <summary>
        /// Move object
        /// </summary>
        public override void Move(int deltaX, int deltaY)
        {
            //IsGif = true;
            //_virtualBounds.X += deltaX;
            //_virtualBounds.Y += deltaY;
            Point old = _virtualBounds.Location;
            Rectangle moveRect = _virtualBounds;
            moveRect.Offset(deltaX, deltaY);

            //SetVirtualBounds();
            VirtualBounds = FormatBoundsByZoom(moveRect, Zoom);
            if (_orgiBounds != Rectangle.Empty)
                _orgiBounds.Offset(_virtualBounds.Location.X - old.X, _virtualBounds.Y - old.Y);
            ComputeDestBound();
            IsChanged = true;
            //IsGif = false;
        }

        /// <summary>
        /// Move handle to the point
        /// </summary>
        public override void MoveHandleTo(Point point, int handleNumber)
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
            Rectangle rect = FormatBoundsByZoom(new Rectangle(left, top, right - left, bottom - top), Zoom);
            VirtualBounds = rect;
            ComputeDestBound();
        }

        /// <summary>
        /// Zoom Paint
        /// add by Michael
        /// </summary>
        private void PaintZoom(Graphics g, ref Rectangle bounds, ref Rectangle imageBounds, ref Rectangle destBounds)
        {
            int x;
            int y;
            //GraphicsUnit gu = GraphicsUnit.Pixel;

            if (_orgiBounds != Rectangle.Empty)
            {
                bounds = _orgiBounds;
                _orgiBounds = Rectangle.Empty;
            }
            float wn = bounds.Width * 1f / _image.Width * 1f;
            float hn = bounds.Height * 1f / _image.Height * 1f;
            float n = wn < hn ? wn : hn;
            x = bounds.Location.X + bounds.Width / 2 - (int)(n * _image.Width) / 2;
            y = bounds.Location.Y + bounds.Height / 2 - (int)(n * _image.Height) / 2;
            destBounds = new Rectangle(x, y, (int)(n * _image.Width), (int)(n * _image.Height));
            if (VirtualBounds.X % Zoom == 0 && VirtualBounds.Y % Zoom == 0 && VirtualBounds.Width % Zoom == 0 && VirtualBounds.Height % Zoom == 0)
            {
                destBounds = FormatBoundsByZoom(destBounds, Zoom);
            }

            DrawImage(g, destBounds);
        }

        /// <summary>
        /// default Paint
        /// add by Michael
        /// </summary>
        private void PaintDefault(Graphics g, ref Rectangle bounds)
        {
            DrawImage(g, bounds);
        }

        public override ShapeBase NewInstance()
        {
            return new ShapeImage();
        }

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;

            base.FromTo(shape);

            ShapeImage other = shape as ShapeImage;
            if (other != null)
            {
                _imageUrl = other._imageUrl;
                DestBounds = other.DestBounds;
                IsGif = other.IsGif;
                _fileHandle = other._fileHandle;
                _sizeMode = other._sizeMode;
            }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _imageUrl = null;
            if (_image != null)
                _image.Dispose();
            _image = null;
        }

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitImage(this);
        }
        #endregion

        #region IEquatable<ShapeImage> Members

        public bool Equals(ShapeImage other)
        {
            if (other == null)
                return false;
            if (!string.Equals(other.ImageUrl, other.ImageUrl))
                return false;
            if (other.SizeMode != SizeMode)
                return false;
            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ShapeImage);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        #endregion
    }


}
