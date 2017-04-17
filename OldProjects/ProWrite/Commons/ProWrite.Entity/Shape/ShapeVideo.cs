using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.Serialization;
using System.Windows.Forms;
using ProWrite.Core;
using System.Drawing.Design;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library;
using ProWrite.UFE;

namespace ProWrite.Entity.Shape
{
    /// <summary>
    /// Summary description for ShapeVideo.
    /// // 2008-6-19, Kevin 迁移
    /// Modify history:
    /// Michael 2008-7-28 增加ImageUrl、Image属性并修改PaintImage方法
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public partial class ShapeVideo : ShapeBase, IEquatable<ShapeVideo>, IFileHandle
    {
        #region Non Serialized Fields
        [NonSerialized]
        private string _fileHandle;
        [NonSerialized]
        private Image _image;
        #endregion

        #region Serialized Fields
        private string _imageUrl = null;
        private Rectangle orgiBounds = Rectangle.Empty;
        private PictureBoxSizeType _sizeMode = PictureBoxSizeType.Zoom;
        private Rectangle _orgiBounds = Rectangle.Empty;
        private Rectangle imageBounds = Rectangle.Empty;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public ShapeVideo()
        {
        }

        #region Properties

#if DEBUG
        [Browsable(true)]
#else
        [Browsable(false)]
#endif
        [Editor(Constance.Designers.Video, typeof(UITypeEditor))]
        [XmlIgnore]
        public string VideoUrl
        {
            get { return _innerImagePath; }
            set
            {
                if (string.Equals(value, _innerImagePath, StringComparison.OrdinalIgnoreCase))
                    return;
                string old = _innerImagePath;

                _innerImagePath = value;
                OnPropertyChanged("VideoUrl", value, old);
            }
        }
        #endregion

        #region overrides
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

        /// <summary>
        /// get shape type
        /// </summary>
        public override ShapeType Type
        {
            get { return ShapeType.Video; }
        }

        /// <summary>
        /// get layer type
        /// </summary>
        public override LayerType LayerType
        {
            get { return LayerType.Video; }
        }

        [Browsable(false)]
        [XmlIgnore]
        public string FileHandle
        {
            get { return _fileHandle; }
            set { _fileHandle = value; }
        }

        [Browsable(false)]
        [XmlIgnore]
        string IFileHandle.FileUrl
        {
            get { return VideoUrl; }
            set { VideoUrl = value; }
        }

        [Browsable(false)]
        [XmlIgnore]
        public long VideoDuration{ get; set;}

        [Browsable(false)]
        public string ImageUrl
        {
            get { return _imageUrl; }
            set
            {
                string old = _imageUrl;
                _imageUrl = value;
                if (string.IsNullOrEmpty(_imageUrl) && this.Image != null)
                {
                    this.Image.Dispose();
                    this.Image = null;
                }
                OnPropertyChanged("ImageUrl", value, old);
            }
        }

        [XmlIgnore]
        [Category("Image")]
        public Image Image
        {
            get { return _image; }
            set
            {
                _image = value;
            }
        }

        [Category("Image")]
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

        public void ComputeDestBoundBatchLoad()
        {
            _image = Image;
            ComputeDestBound();
        }

        //auto snap some imagelayer
        public void ComputeDestBound()
        {
            Rectangle bounds = base.VirtualBounds;
            Rectangle _destBounds = Rectangle.Empty;

            if (_image != null)
                switch (_sizeMode)
                {
                    //case PictureBoxSizeType.Normal:
                    //    //PaintNormal(g, ref bounds, ref imageBounds, ref _destBounds); ;
                    //    int width;
                    //    int height;
                    //    if (_orgiBounds != Rectangle.Empty)
                    //    {
                    //        bounds = _orgiBounds;
                    //        _orgiBounds = Rectangle.Empty;
                    //    }
                    //    width = bounds.Width < _image.Width ? bounds.Width : _image.Width;
                    //    height = bounds.Height < _image.Height ? bounds.Height : _image.Height;
                    //    _destBounds = new Rectangle(bounds.Location, new Size(width, height));
                    //    imageBounds = new Rectangle(0, 0, width, height);
                    //    break;
                    //case PictureBoxSizeType.AutoSize:
                    //    //PaintAutoSize(g, ref bounds);
                    //    if (_orgiBounds == Rectangle.Empty)
                    //        _orgiBounds = bounds;
                    //    bounds = new Rectangle(_orgiBounds.Location, _image.Size);
                    //    break;
                    case PictureBoxSizeType.StretchImage:
                        //PaintStretchImage(g, ref bounds);
                        if (_orgiBounds != RectangleF.Empty)
                        {
                            bounds = _orgiBounds;
                            _orgiBounds = Rectangle.Empty;
                        }
                        break;
                    case PictureBoxSizeType.CenterImage:
                        //PaintCenterImage(g, ref bounds, ref destBounds);
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
                        //PaintZoom(g, ref bounds, ref imageBounds, ref _destBounds);
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

        /// <summary>
        /// Move object
        /// </summary>
        public override void Move(int deltaX, int deltaY)
        {
            Point old = _virtualBounds.Location;
            Rectangle moveRect = _virtualBounds;
            moveRect.Offset(deltaX, deltaY);

            //SetVirtualBounds();
            VirtualBounds = FormatBoundsByZoom(moveRect, Zoom);
            if (_orgiBounds != Rectangle.Empty)
                _orgiBounds.Offset(_virtualBounds.Location.X - old.X, _virtualBounds.Y - old.Y);
            ComputeDestBound();
            IsChanged = true;
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

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitVideo(this);
        }

        public Rectangle PaintImage(Graphics g, ref Rectangle bounds, bool isDrawToBmp)
        {
            Rectangle imageBounds = Rectangle.Empty;
            Rectangle destBounds = Rectangle.Empty;
            int width;
            int height;
            int x;
            int y;

            //GraphicsUnit gu = GraphicsUnit.Pixel;
            if (_image != null)
            {
                switch (_sizeMode)
                {
                    //case PictureBoxSizeType.Normal:
                    //    if (_orgiBounds != Rectangle.Empty)
                    //    {
                    //        bounds = _orgiBounds;
                    //        _orgiBounds = Rectangle.Empty;
                    //    }
                    //    width = bounds.Width < _image.Width ? bounds.Width : _image.Width;
                    //    height = bounds.Height < _image.Height ? bounds.Height : _image.Height;
                    //    destBounds = new Rectangle(bounds.Location, new Size(width, height));
                    //    destBounds = FormatBoundsByZoom(destBounds, Zoom);
                    //    imageBounds = new Rectangle(0, 0, width, height);
                    //    break;
                    //case PictureBoxSizeType.AutoSize:
                    //    _orgiBounds = bounds;
                    //    bounds = new Rectangle(_orgiBounds.Location, _image.Size);
                    //    break;
                    case PictureBoxSizeType.StretchImage:
                        if (_orgiBounds != RectangleF.Empty)
                        {
                            bounds = _orgiBounds;
                            _orgiBounds = Rectangle.Empty;
                        }
                        destBounds = bounds;
                        break;
                    case PictureBoxSizeType.CenterImage:
                        {
                            Point loc = new Point();
                            if (_orgiBounds != Rectangle.Empty)
                            {
                                bounds = _orgiBounds;
                                _orgiBounds = Rectangle.Empty;
                            }

                            width = bounds.Width < _image.Width ? bounds.Width : _image.Width;
                            height = bounds.Height < _image.Height ? bounds.Height : _image.Height;
                            loc.X = (_image.Width - width) / 2;
                            loc.Y = (_image.Height - height) / 2;
                            x = bounds.Location.X;
                            y = bounds.Location.Y;

                            if (bounds.Width > _image.Width)
                                x += (bounds.Width - _image.Width) / 2;

                            if (bounds.Height > _image.Height)
                                y += (bounds.Height - _image.Height) / 2;

                            destBounds = new Rectangle(x, y, width, height);
                            destBounds = FormatBoundsByZoom(destBounds, Zoom);
                            imageBounds = new Rectangle(loc, new Size(width, height));
                            break;
                        }
                    case PictureBoxSizeType.Zoom:
                        {
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
                            break;
                        }
                    default:
                        break;
                }
                //DrawImage(g, bounds);
                DrawImage(g, ref destBounds);
			}
			else
			{
				Color c = SignTypeHandler.ConvertColor(Color.White, SignType);
				g.DrawString("Video", ShapeImage.Tahoma_Font, _cache.GetSolidBrush(c), bounds);
			}
			return destBounds;
		}

        /// <summary>
        /// Draw Image
        /// add by Michael
        /// </summary>
        private void DrawImage(Graphics g, ref Rectangle destBounds)
        {
            if (_image == null)
                return;
            destBounds = FormatBounds(destBounds);
            using (Image image = FormatImage(_image, new Rectangle(destBounds.X, destBounds.Y, destBounds.Width, destBounds.Height)))
                SignTypeHandler.SetOutChannel(g, image, SignType, destBounds, new Rectangle(new Point(0, 0), new Size(destBounds.Width, destBounds.Height)));
        }

        public void SaveUploadedFile()
        {
            if (VirtualBounds.Size == SizeF.Empty)
                return;

            string targetFile = LocalFilePathMapping.GetPath(ProWrite.UFE.Entity.FileType.Video) + Constance.DirectorySeparator + LocalFilePathMapping.GetExtension(ProWrite.UFE.Entity.FileType.Video);
        }

        public override ShapeBase NewInstance()
        {
            return new ShapeVideo();
        }

        public override void FromTo(ShapeBase shape)
        {
            base.FromTo(shape);

            ShapeVideo other = shape as ShapeVideo;
            if (other != null)
            {
                _sizeMode = other._sizeMode;
                _imageUrl = other._imageUrl;
                _fileHandle = other._fileHandle;
                //_destBounds = other._destBounds;

                if (other._image != null)
                    _image = other._image.Clone() as Image;
            }
        }
        #endregion

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            if (_image == null && !string.IsNullOrEmpty(_imageUrl))
            {
                _image = IOHelper.GetImageFromFile(_imageUrl);
            }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_image != null)
            {
                _image.Dispose();
                _image = null;
            }
            _imageUrl = null;
        }

        #region IEquatable<ShapeVideo> Members

        public bool Equals(ShapeVideo other)
        {
            if (other == null)
                return false;
            //if (other.SizeMode != SizeMode)
            //    return false;
            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ShapeVideo);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        #endregion
    }
}
