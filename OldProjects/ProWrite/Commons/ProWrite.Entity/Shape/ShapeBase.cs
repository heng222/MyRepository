//---------------------------------------------------------------------
//
// File: ShapeBase.cs
//
// Description:
// Shape base class
//
// Author: 
//
//Modify History:
//      Kevin     2008-6-19 Kevin 迁移
//      Kevin     2008-6-25 implement interface IComparable<ShapeBase> and IComparable 
//      Kevin     2008-6-25 解除ShapeBase 对MessageTab control 和UndoManager的强依赖
//      Jerry Xu  2008-8-6  Add properties:VirtualLocation,VirtualSize
//      Jerry Xu  2008-8-6  Update properties:Location,Size
//      Jerry Xu  2008-8-20 Add property:VirtualInnerBound,VirtualInnerSize,InnerSize,InnerLocatio nF,InnerLocation,VirtualInnerLocation
//      Jerry Xu  2009-1-20 Update property:DestBounds
//      Jerry Xu  2009-2-19 Update property:DestBounds
//      Jerry Xu  2009-3-13 Update method:FromTo(ShapeBase shape)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Runtime.Serialization;
using System.Windows.Forms;
using System.Xml.Serialization;
using log4net;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Unsafe;
using System.Reflection;
using ProWrite.Core.Validation;
using System.Diagnostics;
using ProWrite.Entity.Settings;

namespace ProWrite.Entity.Shape
{
    /// <summary>
    /// Summary description for ShapeBase.
    /// </summary>
    [Serializable]
    [XmlInclude(typeof(ShapeFigure))]
    [XmlInclude(typeof(ShapeImage))]
    [XmlInclude(typeof(DefaultShape))]
    [XmlInclude(typeof(ShapeLabel))]
    [XmlInclude(typeof(ShapeLine))]
    [XmlInclude(typeof(ShapeTemp))]
    [XmlInclude(typeof(ShapeTime))]
    [XmlInclude(typeof(ShapeVideo))]
    [XmlInclude(typeof(Bitmap))]
    //[XmlInclude(typeof (ShapeMarquee))]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    /// <summary>
    /// 
    /// </summary>
    [DebuggerDisplay("Type={Type},Visible={_isVisible},Selected={_isSelected}")]
    public abstract partial class ShapeBase : DisposableObject, IEquatable<ShapeBase>, IEditableObject, IErrorInfo
    {
        #region Non Serialized Fields
        [NonSerialized]
        public static int DragBlockSize = 6;
        [NonSerialized]
        protected static readonly ILog _log = LogManager.GetLogger("Shape");
        [NonSerialized]
        protected bool _isChanged = true;
        [NonSerialized]
        private object tag = null;
        [NonSerialized]
        private Rectangle[] _dragBlocks;
        [NonSerialized]
        private Image _innerImage;
        [NonSerialized]
        protected bool _isSelected;
        [NonSerialized]

        protected Rectangle _virtualBounds;
        [NonSerialized]
        protected Rectangle _virtualInnerBounds;
        [NonSerialized]
        private int _editLevel = 0;
        [NonSerialized]
        private ErrorProperty _error;
        [NonSerialized]
        private string _videoFileID;
        [NonSerialized]
        private EventHandler _backgroundChanged;
        [NonSerialized]
        private EventHandler<RemoveBackgroundEventArgs> _backgroundRemove;
        [NonSerialized]
        [XmlIgnore]
        private EventHandler _boundsChanged;
        [NonSerialized]
        [XmlIgnore]
        private EventHandler<PropertyChangedEventArgs> _propertyChanged;
        [XmlIgnore]
        [NonSerialized]
        private EventHandler _selectChanged;
        /// <summary>
        /// Validate background exists event
        /// </summary>
        [NonSerialized]
        [XmlIgnore]
        public ValidateExistBackGroundDelegate ValidateExistBackGround;

        [NonSerialized]
        private bool _isMoving = false;

        [NonSerialized]
        protected static ResourceCache _cache = ResourceCache.DefaultCache;

        [NonSerialized]
        protected const int PlayWindowsWidthPixel = 455;
        [NonSerialized]
        protected const int PlayWindowsHeightPixel = 415;

        public delegate ShapeBase ValidateExistBackGroundDelegate(long id);
        #endregion

        #region Serialized Fields
        protected Color _borderColor;
        protected int _borderWidth;
        private long _id;
        private int _index;

        //[NonSerialized]
        protected string _innerImagePath = "";
        protected bool _isVisible = true;
        private Rectangle _selectedBounds;
        private bool _isBackground;
        private Rectangle _orgiBackBounds = Rectangle.Empty;
        private Size _signSize;
        private SignType _signType = SignType.RGB;
        protected int _zoom = 1;
        //screen 
        protected Rectangle _bounds;
        protected Rectangle _innerBounds;
        protected Rectangle _destBounds = Rectangle.Empty;
        
        #endregion //End Fields

        protected ShapeBase()
            : this(SignType.RGB)
        {
        }

        protected ShapeBase(SignType signType)
        {
            _id = KeyGenerator.Shape;
            _signType = signType;
            _index = -1;
            _virtualBounds = new Rectangle(0, 0, 100, 30);
            _borderWidth = 1;
            _borderColor = SystemColors.ControlLight;
            _dragBlocks = null;
            //_borderColor = SignTypeHandler.ConvertColor(_borderColor, signType);
        }

        protected ShapeBase(SignType? signType)
            : this(signType ?? SignType.RGB)
        {
        }

        public virtual void InitEvent()
        {

        }

        public virtual void PopulateDefaultProperty()
        {
        }

        public virtual void InitializeByTemplate(MessageTemplate template)
        {
            
        }
        #region Properties Setting

        [Browsable(false)]
        public ErrorProperty Error { get { return _error; } set { _error = value; } }

        [Browsable(false)]
        public bool IsDynamicLayer
        {
            get { return LayerType >= LayerType.DynamicText; }
        }

        [Browsable(false)]
        public bool IsChanged
        {
            get { return _isChanged; }
            set { _isChanged = value; }
        }


        /// <summary>
        /// Onlay be used by uploaded video.
        /// </summary>
        [Browsable(false)]
        public string VideoFileID
        {
            get { return _videoFileID; }
            set { _videoFileID = value; }
        }

        [Browsable(false)]
        public Rectangle OldVirtualBound
        {
            //get { return _orgiBackBounds; }
            set { _orgiBackBounds = value; }
        }


        /// <summary>
        /// get shape type
        /// </summary>
        [Browsable(false)]
        public abstract ShapeType Type { get; }

        /// <summary>
        /// get layer type
        /// </summary>
        [Browsable(false)]
        public abstract LayerType LayerType { get; }

        //[Browsable(false)]
        //public virtual bool IsDrawImage
        //{
        //    get { return false; }
        //}

        /// <summary>
        /// get or set sign type
        /// </summary>
        [Browsable(false)]
        public SignType SignType
        {
            get { return _signType; }
            set
            {
                if (_signType != value)
                {
                    _signType = value;
                    UpdateSignType();
                }
            }
        }

        protected virtual void UpdateSignType()
        {
            _borderColor = SignTypeHandler.ConvertColor(_borderColor, _signType);
        }

        /// <summary>
        /// get or set is visible
        /// </summary>
        [Browsable(false)]
        public virtual bool IsVisible
        {
            get { return _isVisible; }
            set
            {
                if (_isVisible != value)
                {
                    bool old = _isVisible;
                    _isVisible = value;
                    OnPropertyChanged("IsVisible", value, old);
                }
            }
        }

        /// <summary>
        /// get or set id
        /// </summary>
        [Browsable(false)]
        public long ID
        {
            get { return _id; }
            set { _id = value; }
        }

        /// <summary>
        /// get or set index
        /// </summary>
        [Browsable(false)]
        public int Index
        {
            get { return _index; }
            set { _index = value; }
        }

        [Browsable(false)]
        public Rectangle DestBounds
        {
            get
            {
                if (_destBounds == Rectangle.Empty)
                    return _virtualBounds;
                if (this.Type == ShapeType.Video || this.Type == ShapeType.Image)
                    return _destBounds;
                //if (this.Type != ShapeType.Image /*&& this.Type != ShapeType.Video*/)
                return _virtualBounds;
                //return _destBounds;
            }
            set
            {
                _destBounds = value;
            }
        }

        /// <summary>
        /// get or set bounds
        /// </summary>
        [Browsable(false)]
        public virtual Rectangle VirtualBounds
        {
            get { return _virtualBounds; }
            set
            {
                if (_virtualBounds != value)
                {
                    Rectangle old = _virtualBounds;

                    if (value.Width == 0)
                    {
                        value.Width = _zoom;
                    }
                    if (value.Height == 0)
                    {
                        value.Height = _zoom;
                    }
                    _virtualBounds = value;
                    //_virtualInnerBounds = VirtualInnerBounds;
                    OnPropertyChanged("VirtualBounds", value, old);
                    OnBoundsChanged();
                }
            }
        }

        /// <summary>
        /// get or set inner bounds
        /// 除掉边框宽度之后，内部的矩形区域
        /// </summary>
        [Browsable(false)]
        public Rectangle VirtualInnerBounds
        {
            get
            {
                int halfBorder = _borderWidth;
                int L = _virtualBounds.Left + halfBorder;
                int T = _virtualBounds.Top + halfBorder;
                int R = _virtualBounds.Right - halfBorder;
                int B = _virtualBounds.Bottom - halfBorder;
                _virtualInnerBounds = Rectangle.FromLTRB(L, T, R, B);
                _virtualInnerBounds = ShapePaintHelper.GetNormalizedRectangle(_virtualInnerBounds);
                return _virtualInnerBounds;
            }
            set { _virtualInnerBounds = value; }
        }

        [Browsable(false)]
        public Rectangle Rect
        {
            get
            {
                Rectangle rect = new Rectangle
                                {
                                    Height = DestBounds.Height / _zoom,
                                    Width = DestBounds.Width / _zoom,
                                    X = DestBounds.X / _zoom,
                                    Y = DestBounds.Y / _zoom
                                };
                return rect;
            }
        }

        /// <summary>
        /// get or set VirtualLocation
        /// </summary>
        [Category("Layout")]
        [Browsable(false)]
        public Point VirtualLocation
        {
            get { return _virtualBounds.Location; }
            set
            {
                if (_virtualBounds.Location != value)
                {
                    Point old = _virtualBounds.Location;
                    _virtualBounds.X = value.X;
                    _virtualBounds.Y = value.Y;
                    OnPropertyChanged("VirtualLocation", value, old);
                }
            }
        }

        /// <summary>
        /// get or set location
        /// </summary>
        [Category("Layout")]
        [Browsable(false)]
        public virtual Point Location
        {
            get { return Point.Round(new Point(_virtualBounds.Location.X / _zoom, _virtualBounds.Location.Y / _zoom)); }
            set { VirtualLocation = new Point(value.X * _zoom, value.Y * _zoom); }
        }

        /// <summary>
        /// get or set VirtualSize
        /// </summary>
        [Browsable(false)]
        public virtual Size VirtualSize
        {
            get { return _virtualBounds.Size; }
            set
            {
                if (_virtualBounds.Size != value)
                {
                    Size old = VirtualSize;
                    _virtualBounds.Size = value;
                    OnPropertyChanged("VirtualSize", value, old);
                }
            }
        }

        /// <summary>
        /// get or set size
        /// </summary>
        [Category("Layout")]
        [Browsable(false)]
        public virtual Size Size
        {
            get { return new Size(VirtualSize.Width / Zoom, VirtualSize.Height / Zoom); }
            set { VirtualSize = new Size(value.Width * Zoom, value.Height * Zoom); }
        }

        [Category("Size")]
        [RangeValidator(0, 1000)]
        public virtual int Height
        {
            get { return Convert.ToInt32(VirtualSize.Height / Zoom); }
            set
            {
                int old = Height;
                if (value > 0 && value <= 400)
                    VirtualSize = new Size(Width * Zoom, value * Zoom);
            }
        }

        //[LocationValidatorAttribute(ValidatorType.Width)]
        [Category("Size")]
        [RangeValidator(1, 1000)]
        public virtual int Width
        {
            get { return Convert.ToInt32(VirtualSize.Width / Zoom); }
            set
            {
                int old = Width;
                if (value > 0 && value <= 400)
                    VirtualSize = new Size(value * Zoom, Height * Zoom);
            }
        }

        [LocationValidatorAttribute(ValidatorType.X)]
        [Category("Location")]
        public virtual int LocationX
        {
            get { return Convert.ToInt32(_virtualBounds.Location.X / _zoom); }
            set
            {
                if (!IsBackground && value > -1000 && value <= 1000)
                    VirtualLocation = new Point(value * _zoom, LocationY * _zoom);
            }
        }

        [LocationValidatorAttribute(ValidatorType.Y)]
        [Category("Location")]
        public virtual int LocationY
        {
            get { return Convert.ToInt32(_virtualBounds.Location.Y / _zoom); }
            set
            {
                if (!IsBackground && value > -1000 && value <= 1000)
                    VirtualLocation = new Point(LocationX * _zoom, value * _zoom);
            }
        }

        /// <summary>
        /// get or set size
        /// </summary>
        [Category("Layout")]
        [Browsable(false)]
        public virtual Size InnerSize
        {
            get
            {
                return new Size(VirtualInnerBounds.Size.Width / Zoom, VirtualInnerBounds.Size.Height / Zoom);
            }
        }

        /// <summary>
        /// Sign size
        /// </summary>
        [Browsable(false)]
        public Size SignSize
        {
            get { return _signSize; }
            set { _signSize = value; }
        }


        /// <summary>
        /// get or set is selected property
        /// </summary>
        [Browsable(false)]
        public virtual bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                if (_isSelected != value)
                {
                    _isSelected = value;

                    OnSelectedChanged();
                }
            }
        }

        /// <summary>
        /// get drag blocks property
        /// </summary>
        [Browsable(false)]
        public Rectangle[] DragBlocks
        {
            get { return _dragBlocks; }
        }

        /// <summary>
        /// get or set border width
        /// </summary>
        [Browsable(false)]
        public virtual int BorderWidth
        {
            get { return _borderWidth; }
            set
            {
                if (_borderWidth != value)
                {
                    int old = _borderWidth;
                    _borderWidth = value;
                    OnPropertyChanged("BorderWidth", value, old);
                }
            }
        }

        /// <summary>
        /// get or set border color
        /// </summary>
        [Browsable(false)]
        public virtual Color BorderColor
        {
            get { return _borderColor; }
            set
            {
                //value = SignTypeHandler.ConvertColor(value, _signType);
                if (value != _borderColor)
                {
                    Color old = _borderColor;
                    _borderColor = value;
                    OnPropertyChanged("BorderColor", value, old);
                }
            }
        }

        /// <summary>
        /// get or set inner Image
        /// </summary>
        [XmlIgnore]
        [Browsable(false)]
        public Image InnerImage
        {
            get
            {
                return _innerImage;
            }
            set
            {
                if (_innerImage != value)
                {
                    if (_innerImage != null)
                        _innerImage.Dispose();
                    _innerImage = value;
                }
            }
        }

        /// <summary>
        /// get or set backgound
        /// </summary>
        [Category("Layer")]
        [Browsable(false)]
        public virtual bool IsBackground
        {
            get { return _isBackground; }
            set
            {
                //_isBackground = value;
                //SetBackground(value);
            }
        }

        /// <summary>
        /// get or set shape path
        /// </summary>
        [Browsable(false)]
        public virtual string InnerImagePath
        {
            get
            {
                //DrawAndSaveImage();
                return _innerImagePath;
            }
            set { _innerImagePath = value; }
        }

        [Browsable(false)]
        public virtual int Zoom
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
                    _zoom = value;
                    _isChanged = true;
                }
                else
                {
                    _isChanged = false;
                }
            }
        }

        #endregion

        #region events
        /// <summary>
        /// Bounds changed event
        /// </summary>
        public event EventHandler BoundsChanged
        {
            add { _boundsChanged += value; }
            remove { _boundsChanged -= value; }
        }

        protected virtual void OnBoundsChanged()
        {
            if (_boundsChanged != null)
            {
                _boundsChanged(this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// Property changed event
        /// </summary>
        public event EventHandler<PropertyChangedEventArgs> PropertyChanged
        {
            add { _propertyChanged += value; }
            remove { _propertyChanged -= value; }
        }

        protected virtual void OnPropertyChanged(string propertyName, object newValue, object oldValue)
        {
            _isChanged = true;
            if (IsEdit)
                return;
            if (_propertyChanged != null)
                _propertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));

        }

        protected virtual void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            _isChanged = true;
            if (IsEdit)
                return;
            if (_propertyChanged != null)
                _propertyChanged(sender, e);
        }

        /// <summary>
        /// Selected changed event
        /// </summary>
        public event EventHandler SelectedChanged
        {
            add { _selectChanged += value; }
            remove { _selectChanged -= value; }
        }

        protected virtual void OnSelectedChanged()
        {
            if (IsEdit)
                return;
            if (_selectChanged != null)
            {
                _selectChanged(this, EventArgs.Empty);
            }
        }

        public event EventHandler BackgroundChanged
        {
            add { _backgroundChanged += value; }
            remove { _backgroundChanged -= value; }
        }

        public event EventHandler<RemoveBackgroundEventArgs> BackgroundRemove
        {
            add { _backgroundRemove += value; }
            remove { _backgroundRemove -= value; }
        }

        protected virtual void OnBackgroundRemove(ShapeBase item)
        {
            if (IsEdit)
                return;
            if (_backgroundRemove != null)
                _backgroundRemove(this, new RemoveBackgroundEventArgs(item));
        }

        protected virtual void OnBackgroundChanged()
        {
            if (IsEdit)
                return;
            if (_backgroundChanged != null)
            {
                _backgroundChanged(this, EventArgs.Empty);
            }
        }

        #endregion //end events

        #region Methods

        [Browsable(false)]
        public LayerType VideoType
        {
            get
            {
                switch (Type)
                {
                    case ShapeType.Default:
                    case ShapeType.DownArrow:
                    case ShapeType.Ellipse:
                    case ShapeType.Image:
                    case ShapeType.LeftArrow:
                    case ShapeType.Line:
                    case ShapeType.Rectangle:
                    case ShapeType.RightArrow:
                    case ShapeType.ShapeDraw:
                    case ShapeType.UpArrow:
                    case ShapeType.Text:
                    case ShapeType.Time:
                    case ShapeType.DynamicText:
                    case ShapeType.DynamicVideo:
                    case ShapeType.Temperature:
                        return LayerType.Image;
                    case ShapeType.Video:
                        return LayerType.Video;
                    //case ShapeType.Marquee:
                    //	return LayerType.Marquee;
                    default:
                        return LayerType.Image;
                }
            }
        }

        public virtual void Populate(Point location, Size size, SignType signType, Size signSize, int zoom)
        {
            _signType = signType;
            _signSize = signSize;
            _zoom = zoom;

            size.Width = size.Width == 0 ? 1 : size.Width;
            size.Height = size.Height == 0 ? 1 : size.Height;
            _virtualBounds.Location = location;
            _virtualBounds.Size = size;
        }

        //设置图形为背景图片
        //true：设置为背景
        //false：取消背景状态
        protected void SetBackground(bool value)
        {
            UndoManager.Current.BeginTransaction("Set background.");

            var old = _isBackground;
            const string propertyName = "IsBackground";
            if (!value)
            {
                if (_orgiBackBounds != Rectangle.Empty)
                {
                    BeginEdit();
                    VirtualBounds = _orgiBackBounds;
                    EndEdit();
                    _orgiBackBounds = Rectangle.Empty;
                }
                else
                {
                    BeginEdit();
                    VirtualBounds = new Rectangle(0, 0, 100, 30);
                    EndEdit();
                }
                _isBackground = false;
                OnBackgroundChanged();
                OnPropertyChanged(propertyName, value, old);
                return;
            }


            if (ValidateExistBackGround != null)
            {
                ShapeBase prev = ValidateExistBackGround(ID);
                if (prev != null && prev._isBackground)
                {

                    SetBackGround setBackGrond = new SetBackGround();
                    MessageBus.Send(this, setBackGrond);
                    if (!setBackGrond.YesOrNo)
                        return;
                    OnBackgroundRemove(prev);

                }
            }

            _isBackground = true;
            _orgiBackBounds = VirtualBounds;
            VirtualBounds = new Rectangle(Point.Empty, new Size(SignSize.Width * Zoom, SignSize.Height * Zoom));
            //OnPropertyChanged();
            OnBackgroundChanged();

            OnPropertyChanged(propertyName, value, old);

            UndoManager.Current.Commit();
        }

        /// <summary>
        /// Format shape by SignSize
        /// add by Michael 2008-10-27
        /// </summary>
        public Rectangle FormatBoundsByZoom(Rectangle bounds, int zoom)
        {
            int x, y, width, height;
            if (bounds.X >= 0)
            {
                if (bounds.X % zoom > zoom / 2)
                    x = bounds.X % zoom == 0 ? bounds.X : bounds.X + (zoom - bounds.X % zoom);
                else
                    x = bounds.X % zoom == 0 ? bounds.X : bounds.X - bounds.X % zoom;
            }
            else
            {
                if (-bounds.X % zoom > zoom / 2)
                    x = bounds.X - (bounds.X % zoom + zoom);
                else
                    x = bounds.X - bounds.X % zoom;
            }

            if (bounds.Y >= 0)
            {
                if (bounds.Y % zoom > zoom / 2)
                    y = bounds.Y % zoom == 0 ? bounds.Y : bounds.Y + (zoom - bounds.Y % zoom);
                else
                    y = bounds.Y % zoom == 0 ? bounds.Y : bounds.Y - bounds.Y % zoom;
            }
            else
            {
                if (-bounds.Y % zoom > zoom / 2)
                    y = bounds.Y - (bounds.Y % zoom + zoom);
                else
                    y = bounds.Y - bounds.Y % zoom;
            }

            if (bounds.Width % zoom > zoom / 2)
                width = bounds.Width % zoom == 0 ? bounds.Width : bounds.Width + (zoom - bounds.Width % zoom);
            else
                width = bounds.Width % zoom == 0 ? bounds.Width : bounds.Width - bounds.Width % zoom;

            if (bounds.Height % zoom > zoom / 2)
                height = bounds.Height % zoom == 0 ? bounds.Height : bounds.Height + (zoom - bounds.Height % zoom);
            else
                height = bounds.Height % zoom == 0 ? bounds.Height : bounds.Height - bounds.Height % zoom;

            return new Rectangle(x, y, width, height);
        }

        /// <summary>
        /// Format shape by SignSize
        /// add by Michael 2008-10-15
        /// 转化图片大小到适合的canvas
        /// </summary>
        public Image FormatImage(Image image)
        {
            float imgW = Zoom;
            float imgH = Zoom;
            if (image.Width > SignSize.Width * Zoom || image.Height > SignSize.Height * Zoom)
            {
                if (image.Width > image.Height)
                {
                    imgW = SignSize.Width * Zoom;
                    imgH = image.Height * (SignSize.Width * Zoom * 1.0f / image.Width);
                }
                else
                {
                    imgH = SignSize.Height * Zoom;
                    imgW = image.Width * (SignSize.Height * Zoom * 1.0f / image.Height);
                }
            }
            else
            {
                imgW = image.Width;
                imgH = image.Height;
            }
            Bitmap img = new Bitmap((int)imgW, (int)imgH);
            using(var g = Graphics.FromImage(img))
                g.DrawImage(image, new Rectangle(0, 0, (int)imgW, (int)imgH), new Rectangle(0, 0, image.Width, image.Height), GraphicsUnit.Pixel);
            return img;
        }

        /// <summary>
        /// Formate shape to fit dest size with pixel
        /// </summary>
        /// <param name="shape">srcImage</param>
        /// <param name="destBounds">dest shape's size</param>
        /// <returns></returns>
        public Image FormatImage(Image image, Rectangle destBounds)
        {

            Image s1 = ImageHelper.ReSizeImage( image,
                                                destBounds.Width / Zoom == 0 ? (Zoom < 1 ? 1 : Zoom) : destBounds.Width / Zoom,
                                                destBounds.Height / Zoom == 0 ? (Zoom < 1 ? 1 : Zoom) : destBounds.Height / Zoom);

            Image s2 = ImageHelper.ReSizeImage(s1, destBounds.Width, destBounds.Height);
            s1.Dispose();
            return s2;
        }

        public Image FormatImage(Image image, Rectangle innerBounds, Rectangle frameBounds)
        {
            Image i = new Bitmap(frameBounds.Width, frameBounds.Height);
            Graphics g = Graphics.FromImage(i);
            g.DrawImage(image 
                ,new Rectangle((frameBounds.Width - innerBounds.Width)/ 2 , (frameBounds.Height - innerBounds.Height)/2, innerBounds.Width, innerBounds.Height)
                ,new Rectangle(0,0, image.Width, image.Height)
                ,GraphicsUnit.Pixel);

            return FormatImage(i, frameBounds);
        }

        //限制矩形的长宽最小为一个Zoom
        public Rectangle FormatBounds(Rectangle destBounds)
        {
            Rectangle rc;
            int w = destBounds.Width < Zoom ? Zoom : destBounds.Width;
            int h = destBounds.Height < Zoom ? Zoom : destBounds.Height;
            rc = new Rectangle(destBounds.Location, new Size(w, h));
            return rc;
        }

        /// <summary>
        /// save shape
        /// </summary>
        /// <param name="shape"></param>
        /// <returns></returns>
        protected internal string SaveImage(Image image)
        {
            _innerImagePath = IOHelper.SaveTempImage(image, Guid.NewGuid().ToString());
            return _innerImagePath;
        }

        /// <summary>
        /// save shape
        /// </summary>
        /// <param name="shape"></param>
        /// <returns></returns>
        protected string SaveTextImage(Image image)
        {
            _innerImagePath = IOHelper.SaveTextImage(image, Guid.NewGuid().ToString());
            return _innerImagePath;
        }

        public virtual void Accept(IVisitor visitor)
        {
        }


        [OnSerializing]
        private void Serializing(StreamingContext ctx)
        {
            _bounds = new Rectangle(
                _virtualBounds.X / _zoom
                , _virtualBounds.Y / _zoom
                , _virtualBounds.Width / _zoom
                , _virtualBounds.Height / _zoom);
            _innerBounds = new Rectangle(
                _virtualInnerBounds.X / _zoom
                , _virtualInnerBounds.Y / _zoom
                , _virtualInnerBounds.Width / _zoom
                , _virtualInnerBounds.Height / _zoom);
        }

        [OnDeserialized]
        private void Deserialized(StreamingContext ctx)
        {
            _virtualBounds = new Rectangle(
                _bounds.X * _zoom
                , _bounds.Y * _zoom
                , _bounds.Width * _zoom
                , _bounds.Height * _zoom);
            _virtualInnerBounds = new Rectangle(
                _innerBounds.X * _zoom
                , _innerBounds.Y * _zoom
                , _innerBounds.Width * _zoom
                , _innerBounds.Height * _zoom);
        }

        /// <summary>
        /// clone a shape 
        /// </summary>
        /// <returns></returns>
        public virtual ShapeBase Copy()
        {
            ShapeBase shape = NewInstance();
            shape.FromTo(this);
            return shape;
        }

        /// <summary>
        /// new a instance of this object
        /// </summary>
        /// <returns></returns>
        public abstract ShapeBase NewInstance();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="shape"></param>
        public virtual void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            //_id = shape._id;
            _signType = shape._signType;
            _borderColor = shape._borderColor;
            _borderWidth = shape._borderWidth;
            _virtualBounds = shape._virtualBounds;
            _destBounds = shape._destBounds; //shape.DestBounds;
            _bounds = shape._bounds;
            _dragBlocks = shape._dragBlocks;
            //_isSelected = shape._isSelected;
            _isVisible = shape._isVisible;
            _signSize = shape._signSize;
            _signType = shape._signType;
            _virtualInnerBounds = shape._virtualInnerBounds;
            _zoom = shape._zoom;
            //if (shape._innerImage != null)
            //    _innerImage = shape._innerImage;
            //if (shape.VideoFileID != null)
            //    _videoFileID = shape._videoFileID;
            _innerImagePath = shape._innerImagePath;
            _isBackground = shape._isBackground;
            _orgiBackBounds = shape._orgiBackBounds;


        }

        public Rectangle ComputePlayerBound(Rectangle rec, Size signSize)
        {
            float ajustValue, wAjustValue, hAjustValue;

            wAjustValue = PlayWindowsWidthPixel * 1f / rec.Width * 1f;
            hAjustValue = PlayWindowsHeightPixel * 1f / rec.Height * 1f;

            ajustValue = wAjustValue > hAjustValue ? hAjustValue : wAjustValue;

            float width = rec.Width;
            float height = rec.Height;
            width *= ajustValue;
            height *= ajustValue;
            rec.Width = Convert.ToInt32(width);
            rec.Height = Convert.ToInt32(height);

            return rec;
        }

        #endregion

        #region IEquatable<ShapeBase> Members

        public bool Equals(ShapeBase other)
        {
            if (other == null)
                return false;
            if (other.ID != ID)
                return false;
            if (other.Type != Type)
                return false;
            if (other.LayerType != LayerType)
                return false;
            if (other.SignType != SignType)
                return false;
            //if (other.IsDrawImage != IsDrawImage)
            //    return false;
            if (other.IsBackground != IsBackground)
                return false;
            if (other.IsSelected != IsSelected)
                return false;
            if (other.IsVisible != IsVisible)
                return false;
            if (other.BorderColor != BorderColor)
                return false;
            if (other.BorderWidth != BorderWidth)
                return false;
            if (other.VirtualBounds != VirtualBounds)
                return false;
            if (other._innerImagePath != _innerImagePath)
                return false;
            if (other._orgiBackBounds != _orgiBackBounds)
                return false;

            return true;
        }

        #endregion

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _backgroundChanged = null;
            _backgroundRemove = null;
            _boundsChanged = null;
            _propertyChanged = null;
            _selectChanged = null;
            ValidateExistBackGround = null;
            if (_innerImage != null)
                _innerImage.Dispose();
            _innerImage = null;
            _innerImagePath = null;
            _dragBlocks = null;
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ShapeBase);
        }

        public override int GetHashCode()
        {
            return (int)_id;
        }

        public override string ToString()
        {
            return Type.ToString();
        }

        [Browsable(false)]
        public bool IsEdit
        {
            get { return _editLevel > 0; }
        }

        [Browsable(false)]
        public bool CanTrickEvent
        {
            get { return !IsEdit; }
        }

        #region IEditableObject Members

        public void BeginEdit()
        {
            _editLevel++;
        }

        public void CancelEdit()
        {
            _editLevel--;
        }

        public void EndEdit()
        {
            _editLevel--;
        }

        #endregion
    }

    public class RemoveBackgroundEventArgs : EventArgs
    {
        public readonly ShapeBase Shape;

        public RemoveBackgroundEventArgs(ShapeBase shape)
        {
            Shape = shape;
        }
    }
    /// <summary>
    /// 当TreeList的当前选中Sign改变后，Current Sign的选择项也应相应改变
    /// </summary>
    public class SetBackGround : PWMessage
    {
        public bool YesOrNo;
        public SetBackGround()//SignInfo currentSign)
        {

        }
    }
}
