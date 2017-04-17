//---------------------------------------------------------------------
//
// File: ShapeDynamicTextBase.cs
//
// Description:
// ShapeDynamicTextBase class
//
// Author: Kevin
//
// Modify history:
//      Jerry Xu 2009-2-27 Update method:DrawAndSaveImage()
//      Jerry Xu 2009-5-8  Update method:DrawString(bool hideGrid)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Design;
using ProWrite.Core;
using ProWrite.Entity.DES.Effect;
using ProWrite.UI.Texts;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Shape
{
    internal enum SizeFixedMode
    {
        Frame,
        Font,
    }

    [Serializable]
    public abstract class ShapeDynamicTextBase : ShapeTextBase
    {
        #region Non Serialized Fields
        [NonSerialized]
        TextMgr _FontMgr;
        [NonSerialized]
        internal Image BitmapOverlay = null;

       
        //[NonSerialized]
        //private int _BitCount = 16;
        #endregion

        #region Serialized Fields
        private Align _Align = Align.CENTER;
        private Valign _Valign = Valign.MIDDLE;
        private RollWay _RollWay = RollWay.None;
        private int _RollRate = _.RollRate;
        private bool FrameSizeFixed = true;
        private bool FontSizeFixed = false;
        #endregion

        [Browsable(false)]
        public bool IsFrameSizeFixed
        {
            get { return FrameSizeFixed; }
        }

        [Browsable(false)]
        public bool IsFontSizeFixed
        {
            get { return FontSizeFixed; }
        }

        internal TextMgr FontMgr
        {
            get
            {
                if (_FontMgr != null)
                    return _FontMgr;
                _FontMgr = new TextMgr();
                return _FontMgr;
            }
        }

        
        
        internal SizeFixedMode FixedMode
        {
            get
            {
                if (FrameSizeFixed)
                    return SizeFixedMode.Frame;
                return SizeFixedMode.Font;
            }
        }

        private class _
		{
			public const string Text = "No Source";
			public const int BitCount = 16;
			public const int RollRate = 3;
		}

		public ShapeDynamicTextBase():this(SignType.RGB)
		{
		}

        public ShapeDynamicTextBase(SignType signType)
			: base(signType)
		{
            _font.Name = FontManager.GetProWriteFonts()[0];
            _font.Size = 7;
            Text = _.Text;
		}

        [Category("TextLayout")]
		public Align Align
		{
			get { return _Align; }
			set
			{
				if (value != Align)
				{
                    var old = _Align;
                    _Align = value;
                    OnPropertyChanged("Align", value, old);
				}
			}
		}

		

        [Category("TextLayout")]
		public Valign Valign
		{
			get { return _Valign; }
			set
			{
				if (value != Valign)
				{
                    var old = _Valign;
					_Valign = value;
                    OnPropertyChanged("Valign", value, old);
				}
			}
		}

		

        [Category("Scroll")]
		public RollWay RollWay
		{
			get { return _RollWay; }
			set
			{
				if (value != RollWay)
				{
                    RollWay old = _RollWay;
                    _RollWay = value;
                    OnPropertyChanged("RollWay", value, old);
				}
			}
		}

		
        [Category("Scroll")]
		public int RollRate
		{
			get { return _RollRate; }
			set
			{
				if (value != RollRate)
				{
                    int old = _RollRate;
                    _RollRate = value;
                    OnPropertyChanged("RollRate", value, old);
				}
			}
		}

		#region override property, method

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);
            ShapeDynamicTextBase other = shape as ShapeDynamicTextBase;
            if (other != null)
            {
                _Align = other._Align;
                //_BitCount = other._BitCount;
                _RollRate = other._RollRate;
                _RollWay = other._RollWay;
                _Valign = other._Valign;
                FrameSizeFixed = other.FrameSizeFixed;
                FontSizeFixed = other.FontSizeFixed;
            }
        }

        internal void DrawString(bool hideGrid)
        {
            FontMgrSetup(FrameSizeFixed, FontSizeFixed, hideGrid);
            List<Image> imagesActual = new List<Image>();
            List<Image> images = new List<Image>();
            List<string> strings = new List<string>();

            FontMgr.GenerateBmps(imagesActual, images, strings);
            

            if (images.Count > 0)
            {
                BitmapOverlay = images[0];
                base.InnerImage = new Bitmap(BitmapOverlay);
            }
        }

        private void FontMgrSetup(bool frameSizeFixed, bool fontSizeFixed, bool hideGrid)
        {
            FontMgr.ShowGrid = !hideGrid;
            FontMgr.ScaleIndex = Zoom;
            FontMgr.SetStyle(frameSizeFixed, fontSizeFixed);
            FontMgr.TextColor = ForeColor;
            FontMgr.BackColor = BackColor;
            FontMgr.FontName = Font.Name;
            FontMgr.FontHeight = int.Parse((Font.Size * Zoom).ToString());
            FontMgr.Alignment = _Align;
            FontMgr.LineAlignment = _Valign;
            FontMgr.Bold = (Font.Style & FontStyle.Bold) == FontStyle.Bold;
            FontMgr.Italic = (Font.Style & FontStyle.Italic) == FontStyle.Italic;
            FontMgr.SignSize = new Size(SignSize.Width * Zoom - 2, SignSize.Height * Zoom - 2);
            FontMgr.FrameSize = base.VirtualBounds.Size;
            FontMgr.Text = Text;
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (BitmapOverlay != null)
            {
                BitmapOverlay.Dispose();
                BitmapOverlay = null;
            }
            if (_FontMgr != null)
            {
                _FontMgr.Dispose();
                _FontMgr = null;
            }
        }
		#endregion

    }

    [Serializable]
    public partial class ShapeDynamicText : ShapeDynamicTextBase, IEquatable<ShapeDynamicText>
    {
        private string _DataSource = null;
        public string DataSource
        {
            get { return _DataSource; }
            set
            {
                if (value != _DataSource)
                {
                    _DataSource = value;
                }
            }
        }

        public ShapeDynamicText()
        {

        }

        public ShapeDynamicText(SignType type)
            : base(type)
        {
        }

        public ShapeDynamicText(SignType type, bool isBitMapFontOnly)
            : this(type)
        {
            IsBitMapFontOnly = isBitMapFontOnly;
        }

        public override ShapeType Type
        {
            get { return ShapeType.DynamicText; }
        }

        public override LayerType LayerType
        {
            get { return LayerType.DynamicText; }
        }

        public override ShapeBase NewInstance()
        {
            return new ShapeDynamicText(); 
        }

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitDynamicText(this);
        }

		#region IEquatable<ShapeDynamicText> Members

		public bool Equals(ShapeDynamicText other)
		{
			if (other == null)
				return false;
            if (other._DataSource != _DataSource)
                return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeDynamicText);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion
    }
}
