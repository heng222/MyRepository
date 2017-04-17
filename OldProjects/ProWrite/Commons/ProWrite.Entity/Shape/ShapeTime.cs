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
	/// Summary description for ShapeTime.
	/// // 2008-6-19, Kevin Ç¨ÒÆ
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    public partial class ShapeTime : ShapeDynamicTextBase, IEquatable<ShapeTime>
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private TimeFormat _displayFormat = TimeFormat.Twelve_hour_time_w_AMPM;
        #endregion

        #region Serialized Fields Version 2
        #endregion

		public ShapeTime():this(SignType.RGB)
		{
		}

        public ShapeTime(SignType signType)
            : base(signType)
        {
            base.Text = GetTimeString();
            ForeColor = SystemColors.HighlightText;
        }

        public ShapeTime(SignType signType, bool isBitMapFontOnly)
            : this(signType)
        {
            IsBitMapFontOnly = isBitMapFontOnly;
        }

		#region Properties Setting
		/// <summary>
		/// get or set display format
		/// </summary>
		[Category("Time")]
		public TimeFormat DisplayFormat
		{
			get { return _displayFormat; }
			set
			{
				if (_displayFormat != value)
				{
					var old = _displayFormat;
					_displayFormat = value;
                    base.Text = GetTimeString();
					OnPropertyChanged("DisplayFormat", _displayFormat, old);
				}
			}
		}


        [Browsable(false)]
        public override string Text
        {
            get
            {
                return base.Text;
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
		public override ShapeType Type
		{
			get { return ShapeType.Time; }
		}

		public override LayerType LayerType
		{
			get { return LayerType.Time; }
		}

        //public override bool IsDrawImage
        //{
        //    get
        //    {
        //        return true;
        //    }
        //}

        //[Browsable(false)]
        //public override string Text
        //{
        //    get
        //    {
        //        return base.Text;
        //    }
        //}
        #endregion

        private string GetTimeString()
        {
            string str = "";
            DateTime date = DateTime.Now;



            if (_displayFormat==0)
                _displayFormat=TimeFormat.Twelve_hour_time_w_AMPM;
            //else
            //{
            //    //if (_displayFormat == TimeFormat.Twelve_hour_time_w_AMPM)
                    str =GetTimeByTimeFormat(_displayFormat);// date.GetDateTimeFormats()[67].ToString();
                //else
                //    str = date.GetDateTimeFormats()[69].ToString();
            //}
                //str = DateTime.Now.GetDateTimeFormats()[67].ToString();// DateTime.Today.ToString("yyyy-MM-dd") + DateTime.Now.ToString("HH:mm:ss");
            if (string.IsNullOrEmpty(base.Text))
                str = base.Text;
            
            return str;
        }

        private static string DeleteZero(string str)
        {
            string strTime = str;
            if (strTime.Substring(0, 1) == "0")
                strTime = strTime.Substring(1);
            return strTime;
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
            //Font.FontFileName = FontMgr.FontFileName;

            //if (FrameSizeFixed)
            //    Font.Size = FontMgr.FontHeight / Zoom;

            //if (FontMgr.Bold)
            //    Font.Style = Font.Style | FontStyle.Bold;
            //else
            //    Font.Style = Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline) ^ FontStyle.Bold);

            //if (FontMgr.Italic)
            //    Font.Style = FontStyle.Italic;
            //else
            //    Font.Style = Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline) ^ FontStyle.Italic);


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
            FontMgr.Text = GetTimeByTimeFormatString(DisplayFormat);
        }
        

        public static string GetTimeByTimeFormatString(ProWrite.Core.TimeFormat timeFormat)
        {
            string strTime = "";
            switch (timeFormat)
            {
                case ProWrite.Core.TimeFormat.Date_US:
                    strTime = DateTime.Now.ToString("MM/dd/yy");// DateTime.Now.GetDateTimeFormats()[2];
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Date_US_Full_Yr:
                    strTime = DateTime.Now.ToString("MM/dd/yyyy");// DateTime.Now.GetDateTimeFormats()[3];
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_1:
                    strTime = DateTime.Now.ToString("dd/MM/yy");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_1FullYr:
                    strTime = DateTime.Now.ToString("dd/MM/yyyy");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_2:
                    strTime = DateTime.Now.ToString("yy/MM/dd");
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_2FullYr:
                    strTime = DateTime.Now.ToString("yyyy/MM/dd");
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Month:
                    strTime = DateTime.Now.ToString("dd");//.Day.ToString();
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Week:
                    strTime = DateTime.Now.DayOfWeek.ToString();
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Week_Abbr:
                    strTime = DateTime.Now.DayOfWeek.ToString().Substring(0, 3);
                    break;
                case ProWrite.Core.TimeFormat.Hours_12hour:
                    strTime = DateTime.Now.ToString("hh");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Hours_24hour:
                    strTime = DateTime.Now.ToString("HH");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Minutes:
                    strTime = DateTime.Now.ToString("mm");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Month:
                    strTime = GetMonth(DateTime.Now.Month);// DateTime.Now.GetDateTimeFormats()[132].Substring(0, DateTime.Now.GetDateTimeFormats()[132].IndexOf(","));
                    break;
                case ProWrite.Core.TimeFormat.Month_Abbr:
                    strTime = GetMonth(DateTime.Now.Month).Substring(0,3);// DateTime.Now.GetDateTimeFormats()[132].Substring(0, DateTime.Now.GetDateTimeFormats()[132].IndexOf(",")).Substring(0, 3);
                    break;
                case ProWrite.Core.TimeFormat.Month_of_Year:
                    strTime = DateTime.Now.ToString("MM");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Seconds:
                    strTime = DateTime.Now.ToString("ss");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_AMPM:
                    strTime = DateTime.Now.ToString("hh:mm tt");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_o_AMPM:
                    strTime = DateTime.Now.ToString("hh:mm");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_seconds:
                    strTime = DateTime.Now.ToString("hh:mm:ss");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Twenty_Four_Hour_Time:
                    strTime = DateTime.Now.ToString("HH:mm");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Twenty_Four_hour_time_w_seconds:
                    strTime = DateTime.Now.ToString("HH:mm:ss");
                    strTime = DeleteZero(strTime);
                    break;
                case ProWrite.Core.TimeFormat.Year:
                    strTime = DateTime.Now.ToString("yyyy");
                    break;
                case ProWrite.Core.TimeFormat.Year_short:
                    strTime = DateTime.Now.ToString("yy");
                    break;
            }
            return strTime;

        }

        public static string GetTimeByTimeFormat(ProWrite.Core.TimeFormat timeFormat)
        {
            string strTime = "";
            switch (timeFormat)
            {
                case ProWrite.Core.TimeFormat.Date_US:
                    strTime = "MM/DD/YY";
                    break;
                case ProWrite.Core.TimeFormat.Date_US_Full_Yr:
                    strTime = "MM/DD/YYYY";
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_1:
                    strTime = "DD/MM/YY";
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_1FullYr:
                    strTime = "DD/MM/YYYY";
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_2:
                    strTime = "YY/MM/DD";
                    break;
                case ProWrite.Core.TimeFormat.DateIntl_2FullYr:
                    strTime = "YYYY/MM/DD";
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Month:
                    strTime = "DD";//.Day.ToString();
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Week:
                    strTime = "DayOfWeek";
                    break;
                case ProWrite.Core.TimeFormat.Day_of_Week_Abbr:
                    strTime = "DAY";
                    break;
                case ProWrite.Core.TimeFormat.Hours_12hour:
                    strTime = "HH";
                    break;
                case ProWrite.Core.TimeFormat.Hours_24hour:
                    strTime ="HH";
                    break;
                case ProWrite.Core.TimeFormat.Minutes:
                    strTime = "MM";
                    break;
                case ProWrite.Core.TimeFormat.Month:
                    strTime = "--Month--";//GetMonth(DateTime.Now.Month);// DateTime.Now.GetDateTimeFormats()[132].Substring(0, DateTime.Now.GetDateTimeFormats()[132].IndexOf(","));
                    break;
                case ProWrite.Core.TimeFormat.Month_Abbr:
                    strTime = "MTH";//GetMonth(DateTime.Now.Month).Substring(0, 3);// DateTime.Now.GetDateTimeFormats()[132].Substring(0, DateTime.Now.GetDateTimeFormats()[132].IndexOf(",")).Substring(0, 3);
                    break;
                case ProWrite.Core.TimeFormat.Month_of_Year:
                    strTime = "MM";
                    break;
                case ProWrite.Core.TimeFormat.Seconds:
                    strTime = "SS";
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_AMPM:
                    strTime = "HH:MM "+DateTime.Now.ToString("tt");
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_o_AMPM:
                    strTime = "HH:MM";
                    break;
                case ProWrite.Core.TimeFormat.Twelve_hour_time_w_seconds:
                    strTime = "HH:MM:SS";
                    break;
                case ProWrite.Core.TimeFormat.Twenty_Four_Hour_Time:
                    strTime = "HH:MM";
                    break;
                case ProWrite.Core.TimeFormat.Twenty_Four_hour_time_w_seconds:
                    strTime = "HH:MM:SS";
                    break;
                case ProWrite.Core.TimeFormat.Year:
                    strTime = "YYYY";
                    break;
                case ProWrite.Core.TimeFormat.Year_short:
                    strTime = "YY";
                    break;
            }
            return strTime;

        }
        private static string GetMonth(int month)
        {
            string item = "" ;
            switch (month)
            {
            	case 1:
            		item= "January";
            		break;
                case 2:
            		item= "February";
            		break;
                case 3:
            		item= "March";
            		break; 
                case 4:
            		item= "April";
            		break; 
                case 5:
            		item= "May";
            		break; 
                case 6:
            		item= "June";
            		break; 
                case 7:
            		item= "July";
            		break; 
                case 8:
            		item= "August";
            		break; 
                case 9:
            		item= "September";
            		break; 
                case 10:
            		item= "October";
            		break; 
                case 11:
            		item= "November";
            		break; 
                case 12:
            		item= "December";
            		break; 

            }
            return item;
        }

        public override ShapeBase NewInstance()
		{
			return new ShapeTime();
		}

		public override void FromTo(ShapeBase shape)
		{
            if (shape == null)
                return;
			base.FromTo(shape);
            ShapeTime other = shape as ShapeTime;
            if (other != null)
            {
                _displayFormat = other._displayFormat;
                _Align = other._Align;

                _Valign = other._Valign;
                FrameSizeFixed = other.FrameSizeFixed;
                FontSizeFixed = other.FontSizeFixed;
            }
		}

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitTime(this);
        }
        
		#region IEquatable<ShapeTime> Members

		public bool Equals(ShapeTime other)
		{
			if (other == null)
				return false;
			if (other._displayFormat != _displayFormat)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeTime);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion
	}
}
