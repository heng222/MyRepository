//---------------------------------------------------------------------
//
// File: FontWrapper.cs
//
// Description:
// Font wrapper class
//
// Author: Kevin 2008-7-16
//
// Modify history:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing.Design;
using System.Drawing;
using System.Xml.Serialization;
using ProWrite.Core;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Font wrraper class
	/// </summary>
	[Serializable]
	[Editor(Constance.Designers.Font, typeof(UITypeEditor))]
	public class FontWrapper:IEquatable<FontWrapper>
	{
		[NonSerialized]
		[XmlIgnore]
		private EventHandler<PropertyChangedEventArgs> _propertyChanged;

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
			if (_propertyChanged != null)
				_propertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
		}
		/// <summary>
		/// constance class
		/// </summary>
		private class _
		{
			/// <summary>
			/// default Font 
			/// </summary>
			public const string Font = "Arial";
			/// <summary>
			/// default size
			/// </summary>
			public const int FontSize = 8;
			/// <summary>
			/// default style
			/// </summary>
			public const FontStyle Style = FontStyle.Regular;
		}

		private string _Name = string.Empty;// = _.Font;
		/// <summary>
		/// get or set font name
		/// </summary>
		[Browsable(false)]
		public string Name
		{
			get { return _Name; }
			set
			{
				if (value != _Name)
				{
					string old = _Name;
					_Name = value;
					OnPropertyChanged("Name", value, old);
				}
			}
		}

	    private bool _isTrueTypeFont;

        [Browsable(false)]
        public bool IsTrueTypeFont 
        { 
            get{ return _isTrueTypeFont;}  
            set
            {
                if (value != _isTrueTypeFont)
                {
                    bool old = _isTrueTypeFont;
                    _isTrueTypeFont = value;
                }

            }
        }

        private string _fontFileName;

        [Browsable(false)]
        public string FontFileName
        {
            get { return _fontFileName; }
            set
            {
                if (value != _fontFileName)
                {
                    string old = _fontFileName;
                    _fontFileName = value;
                    OnPropertyChanged("FontFileName", value, old);
                }

            }
        }

        private int _FontSize;// = _.FontSize;
		/// <summary>
		/// get or set font size
		/// </summary>
		[Browsable(false)]
		public int Size
		{
			get { return _FontSize; }
			set
			{
				if (value != _FontSize)
				{
					int old = _FontSize;
					_FontSize = value;
					OnPropertyChanged("Size", value, old);
				}
			}
		}

		private FontStyle _FontStyle = FontStyle.Regular;//_.Style;
		/// <summary>
		/// get or set font style
		/// </summary>
		[Browsable(false)]
		public FontStyle Style
		{
			get { return _FontStyle; }
			set
			{
				if (value != _FontStyle)
				{
					FontStyle old = _FontStyle;
					_FontStyle = value;
					OnPropertyChanged("Style", value, old);
				}
			}
		}

        public bool IsHasEvent
        {
            get {return _propertyChanged != null && _propertyChanged.GetInvocationList().Length > 0;}
        }

		/// <summary>
		/// convert to gdi font
		/// </summary>
		/// <returns></returns>
		public Font ToFont()
		{
			try
			{
				if (!string.IsNullOrEmpty(_Name))
					return new Font(_Name, (float)_FontSize, _FontStyle);
			}
			finally
			{
			}

			return new Font(_.Font, _.FontSize, _.Style);
		}

		/// <summary>
		/// from gdi font to font wrapper
		/// </summary>
		/// <param name="font"></param>
		public void FromFont(Font font)
		{
			if (font != null)
			{
				_Name = font.Name;
				_FontSize = (int)font.Size;
				_FontStyle = font.Style;
			    _isTrueTypeFont = true;
			}
		}

		#region IEquatable<FontWrapper> Members

		public bool Equals(FontWrapper other)
		{
			if (other == null)
				return false;
			if (!string.Equals(other.Name, Name, StringComparison.OrdinalIgnoreCase))
				return false;
			if (other.Size != Size)
				return false;
			if (other.Style != Style)
				return false;
			return true;
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as FontWrapper);
		}
        
		public override int GetHashCode()
		{
			return Name.GetHashCode();
		}

		public static bool Equals(FontWrapper a, FontWrapper b)
		{
			if (object.Equals(null, a))
			{
				if (object.Equals(null, b))
					return true;
				return false;
			}

			return a.Equals(b);
		}

		public static bool operator == (FontWrapper a, FontWrapper b)
		{
			return Equals(a,b);
		}

		public static bool operator !=(FontWrapper a, FontWrapper b)
		{
			return !Equals(a, b);
		}
		#endregion

		/// <summary>
		/// override to string 
		/// </summary>
		/// <returns></returns>
		public override string ToString()
		{
			return string.Format("{0},{1},{2}",_Name,_FontSize,_FontStyle);
		}

		/// <summary>
		/// Function: Clone data
		/// Author  : Jerry Xu
		/// Date    : 2008-8-19 
		/// </summary>
		/// <returns>FontWrapper</returns>
		public FontWrapper Copy()
		{
			FontWrapper clone = new FontWrapper();
			//target.Caption = Caption;
			clone.Name = Name;
			clone.Size = Size;
			clone.Style = Style;
		    clone.IsTrueTypeFont = IsTrueTypeFont;
		    clone.FontFileName = FontFileName;
            return clone;
		}
	}
}