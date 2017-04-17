using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;
using System.Drawing;
using System.ComponentModel;
using System.Drawing.Design;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.UI.Texts;

namespace ProWrite.Entity.Shape
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract class ShapeFontBase : ShapeBase,IEquatable<ShapeFontBase>
    {
        #region Non Serialized Fields
        [NonSerialized]
        protected FontWrapper _oldFont;
        [NonSerialized]
        private TextEffect _oldTextEffect;
        /// <summary>
        /// get or set Show bit map font only
        /// </summary>
        [XmlIgnore]
        //[Browsable(false)]
        [NonSerialized]
        public bool IsBitMapFontOnly;
        #endregion

        #region Serialized Fields
        protected FontWrapper _font;
        protected Color _foreColor;
        protected Color _backColor = Color.Transparent;
        private TextEffect _textEffect = new TextEffect();
        #endregion

        public ShapeFontBase():this(SignType.RGB)
		{
		}

		public ShapeFontBase(SignType signType)
			: base(signType)
		{
			_font = new FontWrapper();
			_textEffect = new TextEffect();
			_font.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_font_PropertyChanged);
			_textEffect.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_textEffect_PropertyChanged);
            _foreColor = SignTypeHandler.ConvertColor(Color.BlueViolet, SignType);
            //_foreColor = Color.BlueViolet;
		}

		void _textEffect_PropertyChanged(object sender, PropertyChangedEventArgs e)
		{
            if(e.Name.IndexOf("TextEffect.") == -1)
                e.Name = "TextEffect."+e.Name;
            _textEffect = sender as TextEffect;
			base.OnPropertyChanged(this, e);
		}

		void _font_PropertyChanged(object sender, PropertyChangedEventArgs e)
		{
            if(e.Name.IndexOf("Font.") == -1)
                e.Name = "Font." + e.Name;
            _font = sender as FontWrapper;
			base.OnPropertyChanged(this, e);
		}

        public override void InitEvent()
        {
            if (_font == null)
                _font = new FontWrapper();
            _font.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_font_PropertyChanged);
            if (_textEffect == null)
                _textEffect = new TextEffect();
            _textEffect.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_textEffect_PropertyChanged);
        }

		
        [Browsable(false)]
		[NotifyParentProperty(true)]
		public virtual FontWrapper Font
		{
			get
			{
				if (string.IsNullOrEmpty(_font.Name))
				{
                    if (IsBitMapFontOnly)
                        _font.Name = FontManager.GetRasterFonts()[0];
                    else
                        _font.Name = FontManager.GetSystemFonts()[0];
                    _font.Size = FontManager.GetSpecifiedFontHeight(_font.Name)[0];
				}
                _font.IsTrueTypeFont = FontManager.IsTrueType(_font.Name);
			    _font.FontFileName = _font.FontFileName;
				return _font;
			}
			set
			{
				if (_font != value)
				{
					_oldFont = _font.Copy();
					_font = value;
					_font.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_font_PropertyChanged);
					OnPropertyChanged("Font", value, _oldFont);
				}
			}
		}
        
        [Browsable(false)]
        public Color SourceForeColor
        {
            get { return _foreColor; }
        }

        [Browsable(false)]
        public Color ConveredForeColor(SignType signType)
        {
            return SignTypeHandler.ConvertToMonoColor(_foreColor, signType); 
        }
        
        [Browsable(false)]
        public Color ConveredBackColor(SignType signType)
        {
            return SignTypeHandler.ConvertToMonoColor(_backColor, signType);
        }

        [Browsable(false)]
		public Color ForeColor
		{
            get
            {
                return _foreColor;
            }
			set
			{
				if (value != _foreColor)
				{
					Color old = _foreColor;
                    _foreColor = value;
					OnPropertyChanged("ForeColor", _foreColor, old);
				}
			}
		}

        [Browsable(false)]
        public Color SourceBackColor
        {
            get { return _backColor; }
        }
		
        [Browsable(false)]
		public Color BackColor
		{
            get
            {
                return _backColor;
            }
			set
			{
                if (_backColor != value)
                {
                    Color old = _backColor;
                    _backColor = value;
                    OnPropertyChanged("BackColor", _backColor, old);
                }
			}
		}

		#region Text Effect Properties
		
        
		[Category("TextEffect")]
        [Browsable(false)]
        public TextEffect TextEffect
		{
			get { return _textEffect; }
			set
			{
				if (_textEffect != value)
				{
					_oldTextEffect = _textEffect.Copy();
					_textEffect = value;
					_textEffect.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_textEffect_PropertyChanged);
					OnPropertyChanged("TextEffect", value, _oldTextEffect);
				}
			}
		}

       #endregion

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);

            ShapeFontBase shapeFont = shape as ShapeFontBase;
            if (shapeFont != null)
            {
                FontWrapper oldFont = _font;
                if (_font.IsHasEvent)
                {
                    _font = shapeFont._font.Copy();
                    _font.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_font_PropertyChanged);
                }
                else
                   _font = shapeFont._font.Copy();

                _backColor = shapeFont._backColor;
                _foreColor = shapeFont._foreColor;
                if (shapeFont.TextEffect.IsHasEvent)
                {
                    _textEffect = shapeFont.TextEffect.Copy();
                    _textEffect.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_textEffect_PropertyChanged);
                }
                else
                    _textEffect = shapeFont.TextEffect.Copy();
            }
        }

        protected override void UpdateSignType()
        {
            base.UpdateSignType();
            _backColor = SignTypeHandler.ConvertColor(_backColor, SignType);
            _foreColor = SignTypeHandler.ConvertColor(_foreColor, SignType);
            _textEffect.UpdateEffectColor(SignType);
        }

		[OnDeserialized]
		private void Deserialized(StreamingContext ctx)
		{
            if (_font == null)
            {
                _font = new FontWrapper();
                _textEffect = new TextEffect();
                _font.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_font_PropertyChanged);
                _textEffect.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(_textEffect_PropertyChanged);
            }
            InitEvent();
		}

		#region IEquatable<ShapeFontBase> Members

		public bool Equals(ShapeFontBase other)
		{
			if (other == null)
				return false;
			if (other.Font != Font)
				return false;
			if (other._foreColor != _foreColor)
				return false;
			if (other._backColor != _backColor)
				return false;
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

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if(_font != null)
            {
            	_font.PropertyChanged -= this._font_PropertyChanged;
            	_textEffect.PropertyChanged -= this._textEffect_PropertyChanged;
                _font.Name = null;
                _font = null;
				_textEffect = null;

            }
           
        }
	}
}