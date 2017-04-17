//---------------------------------------------------------------------
//
// File: ShapeTimeTemplate.cs
//      
// Description:
//      Shape Time Template class
//
// Author: Kevin 2008-8-1
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using ProWrite.Entity.Settings;
using System.Drawing;
using ProWrite.Core;
using ProWrite.Core.Validation;

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Shape Time Template class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.TimeLayer)]
	public class ShapeTimeTemplate:ShapeTemplate
    {
        public ShapeTimeTemplate()
        {
            ForeColor = Color.White;
            BackGroundColor = Color.Transparent;
            Width = 48;
            Height = 16;
            DisplayFormat = TimeFormat.Twelve_hour_time_w_AMPM;
        }
       
        #region Property
        private Font _Font;
        /// <summary>
        /// Text font
        /// </summary>
        [Browsable(false)]
        public Font Font
        {
            get { return _Font; }
            set { _Font = value; }
        }
        private Color _foreColor;
        /// <summary>
        /// Text background
        /// </summary>
        [DisplayName("Fore Color")]
        public Color ForeColor
        {
            get { return _foreColor; }
            set { _foreColor = value; }
        }
        private TimeFormat _timeFormat;
        [DisplayName("Display Format")]
        public TimeFormat DisplayFormat
        {
            get { return _timeFormat; }
            set { _timeFormat = value; }
        }
        private Color _backColor;
        /// <summary>
        /// Text background
        /// </summary>
        [Browsable(false)]
        public Color BackGroundColor
        {
            get { return _backColor; }
            set { _backColor = value; }
        }

        [Category("FrameSize")]
        [RangeValidator(8, 1000)]
        public int Width
        {
            get { return Get<int>("Width"); }
            set
            {
                if (!FitToSign && value >= 8 && value <= 1000)
                    Set<int>("Width", System.Math.Abs(value));
                else if (Sign != null && FitToSign)
                    Set<int>("Width", System.Math.Abs(Sign.Width));
                if (Sign == null && value >= 8 && value <= 1000)
                    Set<int>("Width", System.Math.Abs(value));
            }
        }

        [Category("FrameSize")]
        [RangeValidator(8, 1000)]
        public int Height
        {
            get { return Get<int>("Height"); }
            set
            {
                if (!FitToSign && value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
                else if (Sign != null && FitToSign)
                    Set<int>("Height", System.Math.Abs(Sign.Height));
                if (Sign == null && value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
            }
        }
        public override bool FitToSign
        {
            get
            {
                return base.FitToSign;
            }
            set
            {
                base.FitToSign = value;
                if (Sign != null && value)
                {
                    Height = Convert.ToInt32(Sign.Height);
                    Width = Convert.ToInt32(Sign.Width);
                }
                if (Sign != null && !value)
                {
                    Height = Convert.ToInt32(Sign.Height) / 2;
                    Width = Convert.ToInt32(Sign.Width) / 2;
                }
                if (Sign == null && value)
                {
                    Height = 32;
                    Width = 96;
                }
                if (Sign == null && !value)
                {
                    Height = 16;
                    Width = 48;
                }
            }
        }

        protected override void OnSignSizeChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            base.OnSignSizeChanged(sender, e);
            if (FitToSign)
            {
                if (e.PropertyName == "Height")
                    Height = Convert.ToInt32(Sign.Height);
                if (e.PropertyName == "Width")
                    Width = Convert.ToInt32(Sign.Width);
            }
            else
            {
                if (e.PropertyName == "Height")
                    Height = Convert.ToInt32(Sign.Height / 2);
                if (e.PropertyName == "Width")
                    Width = Convert.ToInt32(Sign.Width / 2);
            }
        }

        #endregion

        #region override method and property
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.TimeLayer; }
        //}

        public override string Caption()
        {
            return SR.Type.Time;
        }

        public override string View()
        {
            return SR.View.Time;
        }
        #endregion
    }
}