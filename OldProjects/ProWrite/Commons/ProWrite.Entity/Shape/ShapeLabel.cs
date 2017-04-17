//---------------------------------------------------------------------
//
// File: ShapeLabel.cs
//
// Description:
// Shape label class
//
// Author: 
//
//Modify History:
//      Jerry Xu  2008-8-3  Add method:DrawText
//      Jerry Xu  2008-8-4  Update method:DrawString
//      Jerry Xu  2008-8-15 Add properties:Align,Valign
//      Jerry Xu  2008-8-18 Add property:PaintActionType,Font
//      Jerry Xu  2008-9-18 Update method:DrawString(Add FontChange)
//      Jerry Xu  2008-9-2  Add properties:ShadowColor,UpDown,LeftRight,OutLineColor,BubbleSurroundColor,
//          TopHeight,BottomHeight,LeftWidth,RightWidth           
//      Jerry Xu  2008-9-2  Add method:PaintShadow,PaintOutLine,PaintBubbleSurround
//      Jerry Xu  2008-9-2  Update method:SetOutlineShadow,DrawString
//      Jerry Xu  2008-9-9  Add properties:FitToSign,OldVirtualLocation,OldVirtualSize
//      Jerry Xu  2009-6-19 Update method:Deserialized(StreamingContext ctx)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Library;
using ProWrite.UI.Texts;
using System.Collections.Generic;
using ProWrite.Unsafe;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Summary description for ShapeLebel.
	/// // 2008-6-19, Kevin Ç¨ÒÆ
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public partial class ShapeLabel : ShapeTextBase,IEquatable<ShapeLabel>
    {
        #region Non Serialized Fields
        [NonSerialized]
        Image _labelImage = null;
        [NonSerialized]
        internal Image _labelImageActual = null;
        [NonSerialized]
        private TextMgr _FontMgr = null;
        //[NonSerialized]
        //static int _refCount;

        [NonSerialized]
        private bool IsUpload = false;

        [NonSerialized]
        private EventHandler<AddLayersEventArgs> _AddLayers;
        #endregion

        #region Serialized Fields
        private OutlineShadowType _outlineshadow = OutlineShadowType.NONE;
        private int _kernAmount = 0;
        private int _leadAmount = 0;
        private bool _wordWrap = true;
        private string _oldText = string.Empty;
        private Align _textAlign = Align.CENTER;
        private Valign _textVAlign = Valign.MIDDLE;
        private bool _frameSizeFixed = true;
        private bool _fontSizeFixed = false;
        private PaintActionType _paintAction;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        #region Fields
        private const string DefaultText = "Text";//"<Enter Message Here>";

       

        internal TextMgr FontMgr
        {
            get
            {
                if (_FontMgr != null)
                    return _FontMgr;
                _FontMgr = new TextMgr();
                //_refCount = 1;
                return _FontMgr;
            }
        }        
		#endregion

		public ShapeLabel():this(SignType.RGB)
		{
		}

		public ShapeLabel(SignType signType):base(signType)
		{
            //_refCount++;
            _paintAction = PaintActionType.FrameFontSizeStyle;
			_text = DefaultText;
			_stringFormat.FormatFlags = StringFormatFlags.DisplayFormatControl;
			_stringFormat.Alignment = StringAlignment.Center;
			_foreColor = SignTypeHandler.ConvertColor(Color.BlueViolet, SignType);
            //_backColor = SignTypeHandler.ConvertColor(Color.Transparent, SignType);
            
            _font.Name = FontManager.GetProWriteFonts()[0];
            _font.Size = 7;
        }

        public ShapeLabel(SignType signType, bool isBitMapFontOnly)
            : this(signType)
        {
            IsBitMapFontOnly = isBitMapFontOnly;
        }

        public override void InitializeByTemplate(ProWrite.Entity.Settings.MessageTemplate template)
        {
            base.InitializeByTemplate(template);

            _backColor = template.BackGroundColor;
        }

	    #region Properties define  

		public override ShapeType Type
        {
            get { return ShapeType.Text; }
        }

        public override LayerType LayerType
        {
            get { return LayerType.Text; }
        }

        public override string Text
        {
            get { return _text; }
            set
            {
                if (value != _text)
                {
                    string old = _text;
                    //_paintAction = PaintActionType.BorderFitText;
                    _paintAction = PaintActionType.FrameFontSizeStyle;
                    _text = value;
                    OnPropertyChanged("Text", value, old);
                }
            }
        }
 
        /// <summary>
        /// get or set label Image
        /// </summary>
        [XmlIgnore]
        [Browsable(false)]
        public Image LabelImage
        {
            get { return _labelImage; }
            set { _labelImage = value; }
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

        
        [Category("TextLayout")]
        [Browsable(false)]
        public bool FrameSizeFixed
        {
            get { return _frameSizeFixed; }
            set
            {
                if (value != _frameSizeFixed)
                {
                    bool old = _frameSizeFixed;
                    _frameSizeFixed = value;
                    _paintAction = PaintActionType.FrameFontSizeStyle;
                    OnPropertyChanged("FrameSizeFixed", _frameSizeFixed, old);
                }
            }
        }

        

        [Category("TextLayout")]
        [Browsable(false)]
        public bool FontSizeFixed
        {
            get { return _fontSizeFixed; }
            set
            {
                if (value != _fontSizeFixed)
                {
                    bool old = _fontSizeFixed;
                    _fontSizeFixed = value;
                    _paintAction = PaintActionType.FrameFontSizeStyle;
                    OnPropertyChanged("FontSizeFixed", _fontSizeFixed, old);
					IsChanged = true;
                }
            }
        }

        [Browsable(false)]
        public OutlineShadowType OutlineShadow
        {
            get { return _outlineshadow; }
            set
            {
                if (_outlineshadow == value)
                    return;
                
                OutlineShadowType old = _outlineshadow;

                _outlineshadow = value;

                SetOutlineShadow();
                
                OnPropertyChanged("OutlineShadow", _outlineshadow, old);
                //SetOutlineShadow();
            }
        }

        [Category("TextLayout")]
        [Browsable(false)]
        public bool WordWrap
        {
            get { return _wordWrap; }
            set
            {
                if (_wordWrap == value)
                    return;

                bool old = _wordWrap;
                _wordWrap = value;

                if (!_wordWrap)
                {
                    _stringFormat.FormatFlags = StringFormatFlags.NoWrap;
                }
                else
                {
                    _stringFormat.FormatFlags = StringFormatFlags.FitBlackBox;
                }


                OnPropertyChanged("WordWrap", value, old);
            }
        }

        [Category("TextLayout")]
        //[Browsable(false)]
        public override int KernAmount
        {
            get { return _kernAmount; }
            set
            {
                if (_kernAmount == value
                    ||value<0)
                    return;
                int old = _kernAmount;
                _kernAmount = value;
                OnPropertyChanged("KernAmount", value, old);
            }
        }

        [Category("TextLayout")]
        //[Browsable(false)]
        public override int LeadAmount
        {
            get { return _leadAmount; }
            set
            {
                if (_leadAmount == value
                    ||value<0)
                    return;
                int old = _leadAmount;
                _leadAmount = value;
                OnPropertyChanged("LeadAmount", value, old);
            }
        }

        //[NotifyParentProperty(true)]
        public override FontWrapper Font
        {
            get
            {
                return base.Font;
            }
            set
            {
                if (_font != value)
                {
                    _paintAction = PaintActionType.FontChange;
                    base.Font = value;
                }
            }
        }

        
        [Browsable(false)]
        public PaintActionType PaintAction
        {
            get { return _paintAction; }
            set
            {
                _paintAction = value;
            }
        }

        [Category("TextLayout")]
        //[Browsable(false)]
        public override Align TextAlignment
        {
            get { return _textAlign; }
            set
            {
                if (_textAlign == value)
                    return;
                Align old = _textAlign;
                _textAlign = value;
                OnPropertyChanged("TextAlignment", value, old);
            }
        }

        [Category("TextLayout")]
        //[Browsable(false)]
        public override Valign TextVAlignment
        {
            get { return _textVAlign; }
            set
            {
                if (_textVAlign == value)
                    return;
                Valign old = _textVAlign;
                _textVAlign = value;
                OnPropertyChanged("TextVAlignment", value, old);

            }
        }
        #endregion

        #region override methods


        public override ShapeBase NewInstance()
		{
			return new ShapeLabel();
		}

		public override void FromTo(ShapeBase shape)
		{
			base.FromTo(shape);

			ShapeLabel other = shape as ShapeLabel;
			if (other != null)
			{
                _text = other._text;
                //_autofittype = other._autofittype;
                _kernAmount = other._kernAmount;
                _leadAmount = other._leadAmount;
                _outlineshadow = other._outlineshadow;
                _paintAction = other._paintAction;
                _textAlign = other._textAlign;
                _textVAlign = other._textVAlign;
                _wordWrap = other._wordWrap;
                _paintAction = PaintActionType.None;
                if (other._labelImage != null)
                {
                    if (other._innerImagePath != null && other._innerImagePath != string.Empty)
                    {
                        IOHelper.RemoveFile(other._innerImagePath);
                    }
                    _labelImage = other._labelImage.Clone() as Image;
                    other._innerImagePath = SaveTextImage(_labelImage);
                    _innerImagePath = other._innerImagePath;
                }
                else
                {
                    _innerImagePath = other._innerImagePath;
                }
                _frameSizeFixed = other.FrameSizeFixed;
                _fontSizeFixed = other.FontSizeFixed;

                _backColor = other.BackColor;
			}
		}

       
        public override void Accept(IVisitor visitor)
        {
            visitor.VisitLabel(this);
        }


        public enum DrawMode
        {
            Normal,
            Play,
            Upload,
        }

        #endregion

        #region Function define
        internal void PaintImageInShape(Graphics g)
        {
            List<Image> imagesActual = new List<Image>();
			List<Image> images = new List<Image>();
			List<string> strings = new List<string>();

            bool isReturnImage = FontMgr.GenerateBmps(imagesActual, images, strings);
            if (!isReturnImage)
                return;
			//Create shape
			Image image;
			image = images[0];
            //shape.Save("C:\\a.png",ImageFormat.Png);
            Font.FontFileName = FontMgr.FontFileName;
            if (FrameSizeFixed)
                Font.Size = FontMgr.FontHeight / Zoom;

            if (FontMgr.Bold)
                Font.Style = Font.Style|FontStyle.Bold;
            else
                Font.Style = Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline)^ FontStyle.Bold);
            
            if (FontMgr.Italic)
                Font.Style = FontStyle.Italic;
            else
                Font.Style = Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline)^ FontStyle.Italic);
			//Label shape
			_labelImage = image;
		    _labelImageActual = imagesActual[0];

            if (g == null) //get _labelImage, and _labelImageActual then exit
                return;
			Rectangle imageRectangle = new Rectangle(VirtualBounds.X, VirtualBounds.Y, image.Width, image.Height );
            VirtualBounds = imageRectangle;
            g.DrawImage(image, new Rectangle(VirtualBounds.X, VirtualBounds.Y, image.Width, image.Height));
			this._paintAction = PaintActionType.None;
		}

        internal void FontMgrSetup(bool frameSizeFixed, bool fontSizeFixed, DrawMode isPlay)
		{
            var tmpZoom = isPlay == DrawMode.Upload ? 1 : Zoom;
        	FontMgr.ShowGrid = false;
			//Zoom       
            FontMgr.ScaleIndex = tmpZoom;
            //Paint type
            FontMgr.SetStyle(frameSizeFixed, fontSizeFixed);
			//Font info
			FontMgr.TextColor = IsUpload ? SourceForeColor: ForeColor;
			FontMgr.BackColor = IsUpload ? SourceBackColor: BackColor;            
			FontMgr.FontName = Font.Name;
            FontMgr.FontHeight = int.Parse((Font.Size * tmpZoom).ToString());
			FontMgr.Alignment = _textAlign; ;
			FontMgr.LineAlignment = _textVAlign;
			FontMgr.Bold = (Font.Style & FontStyle.Bold)== FontStyle.Bold;
			FontMgr.Italic = (Font.Style & FontStyle.Italic) == FontStyle.Italic;
            FontMgr.KernAmount = KernAmount * tmpZoom;
            FontMgr.LeadAmount = LeadAmount * tmpZoom;
            //FontMgr.ShowGrid = hideGrid ? false : true;
            
            if (isPlay == DrawMode.Upload)
                FontMgr.FrameSize = new Size(Math.Abs(base.VirtualBounds.Size.Width.PopulatePixel(-Zoom)), Math.Abs(base.VirtualBounds.Size.Height.PopulatePixel(-Zoom)));
            else
                FontMgr.FrameSize = new Size(Math.Abs(base.VirtualBounds.Size.Width), Math.Abs(base.VirtualBounds.Size.Height));
            //FontMgr.FrameSize = new Size(base.VirtualInnerBounds.Width + base.BorderWidth, base.VirtualInnerBounds.Height + base.BorderWidth);
            //FontMgr.FrameSize = base.VirtualInnerBounds.Size;// InnerSize.ToSize();
            //Text
			FontMgr.Text = Text;

            switch(TextEffect.Effect)
		    {
                case OutlineShadowType.SHADED:
                    FontMgr.SetShadowAttri(this.TextEffect.EffectColor , this.TextEffect.ShadowLateralShift * Zoom, this.TextEffect.ShadowVerticalShift * Zoom);
                    //FontMgr.SetShadowAttri(IsUpload ? this.TextEffect.EffectColor : SignTypeHandler.ConvertColor(this.TextEffect.EffectColor, SignType), this.TextEffect.ShadowLateralShift * Zoom, this.TextEffect.ShadowVerticalShift * Zoom);
                    break;
                case OutlineShadowType.OUTLINE:
                    FontMgr.SetOutlineAttri(this.TextEffect.EffectColor, (ushort)(this.TextEffect.OutlineWidth * Zoom));
                    //FontMgr.SetOutlineAttri(IsUpload ? this.TextEffect.EffectColor : SignTypeHandler.ConvertColor(this.TextEffect.EffectColor, SignType), (ushort)(this.TextEffect.OutlineWidth * Zoom));
                    break;
				case OutlineShadowType.NONE:
					FontMgr.CancelTextEffect();
		    		break;
		    }
		}


		/// <summary>
        /// Function: Set text outline or shadow or BubbleSurround or none
		/// Author  : Jerry Xu
		/// Date    : 2008-8-12
		/// </summary>
		private void SetOutlineShadow()
		{
			if (_outlineshadow == OutlineShadowType.NONE)
			{
                _paintAction = PaintActionType.None;
			}
            else if (_outlineshadow == OutlineShadowType.OUTLINE)
			{
                _paintAction = PaintActionType.OutLine;
			}
            else if (_outlineshadow == OutlineShadowType.SHADED)
			{
                _paintAction = PaintActionType.Shadow;
			}
            else if (_outlineshadow == OutlineShadowType.BubbleSurround)
            {
                _paintAction = PaintActionType.BubbleSurround;
            }
		}

	    #endregion
        private static object lockOjbect = new object();
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_labelImage != null)
            {
                _labelImage.Dispose();
                _labelImage =null;
            }
            _oldFont = null;
            _oldText = null;
           
            //_refCount--;
            //if (_refCount == 0)
            //{
            if (_FontMgr != null)
            {
                _FontMgr.Dispose();
                _FontMgr = null;
            }
            //}
           
        }

		#region IEquatable<ShapeLabel> Members

		public bool Equals(ShapeLabel other)
		{
			if (other == null)
				return false;			
			if (other._kernAmount != _kernAmount)
				return false;
			if (other._leadAmount != _leadAmount)
				return false;
			if (other._wordWrap != _wordWrap)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeLabel);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion        

        
        public event EventHandler<AddLayersEventArgs> AddLayers
        {
            add { _AddLayers += value; }
            remove { _AddLayers -= value; }
        }

        private void OnAddLayers(ShapeLabel shape,List<ShapeLabel> items)
        {
            if (items == null|| items.Count==0)
                return;

            if (_AddLayers != null)
                _AddLayers(this, new AddLayersEventArgs(shape,items));
        
        }        
	}   
    
}
