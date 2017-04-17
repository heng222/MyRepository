//---------------------------------------------------------------------
//
// File: ShapeTextBase.cs
//
// Description:
// ShapeTextBase entity classes:include some method to operate the ShapeTextBase.
//
// Author: 
// Date  : 
//
// Modify history:
//      Jerry Xu 2008-8-2  Add the method:DrawText
//      Jerry Xu 2008-8-2  Update the method:DrawString
//      Jerry Xu 2008-8-2  Add the property:Zoom
//      Jerry Xu 2008-8-4  Delete property:Zoom,move Zoom define to ShapeBase class
//      Jerry Xu 2008-8-4  Update method:DrawString(Graphics g):_zoom(this)->Zoom(ShapeBase)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.ComponentModel;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Shape
{
	[Serializable]
	public abstract class ShapeTextBase:ShapeFontBase,IEquatable<ShapeTextBase>
    {
        #region Non Serialized Fields
        [NonSerialized]
        protected StringFormat _stringFormat;
        #endregion

        #region Serialized Fields
        protected string _text;
        #endregion

        #region Serialized Fields Version 2
        #endregion

		public ShapeTextBase():this(SignType.RGB)
		{
		}

		public ShapeTextBase(SignType signType)
			: base(signType)
		{
			_text = string.Empty;
			_stringFormat = new StringFormat();
		}

        //[Browsable(false)]
        public virtual Align TextAlignment { get; set; }
        //[Browsable(false)]
        public virtual Valign TextVAlignment { get; set; }
        //[Browsable(false)]
        public virtual int KernAmount { get; set; }
        //[Browsable(false)]
        public virtual int LeadAmount { get; set; }

		public virtual string Text
		{
			get { return _text; }
			set
			{
				if (value != _text)
				{
                    string old = _text;
					_text = value;
                    OnPropertyChanged("Text", value, old);
				}
			}
		}

		[Browsable(false)]
		public StringFormat StringFormat
		{
			get { return _stringFormat; }
		}

        public override void Move(int deltaX, int deltaY)
        {
            base.Move(deltaX, deltaY);
            IsChanged = false;
        }

		public Font GetMeasuredFont(Graphics g)
		{
			return RichTextDrawing.GetFontMeasureStringSize(_text, Font.ToFont(), base.VirtualInnerBounds, _stringFormat, false, g); 
		}


        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);
            ShapeTextBase other = shape as ShapeTextBase;
            if (other != null)
            {
                _text = other._text;
                if (other._stringFormat != null)
                    _stringFormat = other._stringFormat.Clone() as StringFormat;
            }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _text = null;
            if (_stringFormat != null)
                _stringFormat.Dispose();
            _stringFormat = null;
        }
		#region IEquatable<ShapeTextBase> Members

		public bool Equals(ShapeTextBase other)
		{
			if (other == null)
				return false;
			if (!string.Equals(other._text, _text))
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeTextBase);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion
	}
}