using System;
using System.ComponentModel;
using System.Drawing;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.UI.Texts;
using System.Collections.Generic;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Summary description for ShapeTemp.
	/// // 2008-6-19, Kevin 迁移
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    public partial class ShapeTemp : ShapeDynamicTextBase, IEquatable<ShapeTemp>
    {
        #region Non Serialized Fields
        private TempFormat _displayFormat = TempFormat.Farenheit;
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public ShapeTemp():this(SignType.RGB)
		{
		}

        public ShapeTemp(SignType signType)
            : base(signType)
        {
            Text = "TTT";
        }

        public ShapeTemp(SignType signType, bool isBitMapFontOnly)
            : this(signType)
        {
            IsBitMapFontOnly = isBitMapFontOnly;
        }

		#region Properties Setting

		

		[Category("Temp")]
        public TempFormat DisplayFormat
		{
			get { return _displayFormat; }
			set
			{
				if (_displayFormat != value)
				{
					var old = _displayFormat;
					_displayFormat = value;
                    if (_displayFormat == 0)
                        _displayFormat = TempFormat.Farenheit;
                    Text = GetTempByFormat(_displayFormat);
					OnPropertyChanged("DisplayFormat", value, old);
				}
			}
		}

        [Browsable(false)]
        public override Align TextAlignment
        {
            get
            {
                return base.TextAlignment;
            }
            set
            {
                base.TextAlignment = value;
            }
        }

        [Browsable(false)]
        public override Valign TextVAlignment
        {
            get
            {
                return base.TextVAlignment;
            }
            set
            {
                base.TextVAlignment = value;
            }
        }

        [Browsable(false)]
        public override int KernAmount
        {
            get
            {
                return base.KernAmount;
            }
            set
            {
                base.KernAmount = value;
            }
        }

        [Browsable(false)]
        public override int LeadAmount
        {
            get
            {
                return base.LeadAmount;
            }
            set
            {
                base.LeadAmount = value;
            }
        }
        [NonSerialized]
        static TextMgr _FontMgr;

        private Align _Align = Align.CENTER;
        private Valign _Valign = Valign.MIDDLE;

        //[NonSerialized]
        private bool FrameSizeFixed = true;
        //[NonSerialized]
        private bool FontSizeFixed = false;

        Image bitmapOverlay = null;
        private static TextMgr FontMgr
        {
            get
            {
                if (_FontMgr != null)
                    return _FontMgr;
                _FontMgr = new TextMgr();
                return _FontMgr;
            }
        }


        private void DrawString(bool isPlay)
        {
            FontMgrSetup(FrameSizeFixed, FontSizeFixed, isPlay);
            List<Image> imagesActual = new List<Image>();
            List<Image> images = new List<Image>();
            List<string> strings = new List<string>();

            FontMgr.GenerateBmps(imagesActual, images, strings);

            if (images.Count > 0)
            {
                bitmapOverlay = images[0];
                base.InnerImage = new Bitmap(bitmapOverlay);
            }
        }
        private void FontMgrSetup(bool frameSizeFixed, bool fontSizeFixed, bool isPlay)
        {
            FontMgr.ShowGrid = !isPlay;
            FontMgr.ScaleIndex = Zoom;
            FontMgr.SetStyle(frameSizeFixed, fontSizeFixed);
            FontMgr.TextColor = ForeColor;
            FontMgr.BackColor = BackColor;
            FontMgr.FontName = Font.Name;
            FontMgr.FontHeight = int.Parse((Font.Size * Zoom).ToString());
            FontMgr.Alignment = Align;
            FontMgr.LineAlignment = Valign;
            FontMgr.Bold = (Font.Style & FontStyle.Bold) == FontStyle.Bold;
            FontMgr.Italic = (Font.Style & FontStyle.Italic) == FontStyle.Italic;
            FontMgr.SignSize = new Size(SignSize.Width * Zoom - 2, SignSize.Height * Zoom - 2);
            FontMgr.FrameSize = base.VirtualBounds.Size;
            FontMgr.Text = GetTempByFormatString(DisplayFormat);
        }
        //public override void DrawAndSaveImage()
        //{
        //    if (!IsDrawImage)
        //        return;
        //    BeginEdit();
        //    DrawString(true);
        //    EndEdit();
        //    if (bitmapOverlay != null)
        //        InnerImagePath = SaveImage(bitmapOverlay);
        //    IsChanged = true;
        //}

        public static string GetTempByFormatString(TempFormat tempFormat)
        {
            string strTemp = "";
            switch (tempFormat)
            {
                case TempFormat.Celsius:
                    strTemp = " 22";
                    break;
                case TempFormat.Celsius_w_degree:
                    strTemp = " 22°";
                    break;
                case TempFormat.Celsius_w_degree_and_C:
                    strTemp = " 22°C";
                    break;
                case TempFormat.Farenheit:
                    strTemp = " 72";
                    break;
                case TempFormat.Farenheit_w_degree:
                    strTemp = " 72°";
                    break;
                case TempFormat.Farenheit_w_degree_and_F:
                    strTemp = " 72°F";
                    break;
            }
            return strTemp;
        }

        public static string GetTempByFormat(TempFormat tempFormat)
        {
            string strTemp = "";
            switch (tempFormat)
            {
                case TempFormat.Celsius:
                    strTemp = "TTT";
                    break;
                case TempFormat.Celsius_w_degree:
                    strTemp = "TTT°";
                    break;
                case TempFormat.Celsius_w_degree_and_C:
                    strTemp = "TTT°C";
                    break;
                case TempFormat.Farenheit:
                    strTemp = "TTT";
                    break;
                case TempFormat.Farenheit_w_degree:
                    strTemp = "TTT°";
                    break;
                case TempFormat.Farenheit_w_degree_and_F:
                    strTemp = "TTT°F";
                    break;
            }
            return strTemp;
        }

        [Browsable(false)]
        public override string Text
        {
            get
            {
                return base.Text;
            }
        }
		#endregion

		public override ShapeType Type
		{
			get { return ShapeType.Temperature; }
		}

		public override LayerType LayerType
		{
			get { return LayerType.Temp; }
		}

		public override ShapeBase NewInstance()
		{
			return new ShapeTemp();
		}

		public override void FromTo(ShapeBase shape)
		{
			base.FromTo(shape);
			ShapeTemp other = shape as ShapeTemp;

            if (other != null)
            {
                _displayFormat = other.DisplayFormat;
                if (_displayFormat == 0)
                    _displayFormat = TempFormat.Farenheit;
                Text = other.Text;
            }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitTemp(this);
        }

		#region IEquatable<ShapeTemp> Members

		public bool Equals(ShapeTemp other)
		{
			if (other == null)
				return false;
			if (_displayFormat != other._displayFormat)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeTemp);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		#endregion
	}
}