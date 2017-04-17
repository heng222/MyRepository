//---------------------------------------------------------------------
//
// File: ShapeLabelTemplate.cs
//      
// Description:
//      Shape Label Template class
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
using System.Drawing;
using ProWrite.Core.Validation;
using ProWrite.Entity.Shape;
using ProWrite.UI.Texts;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// Shape Label Template class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.TextLayer)]
    public class ShapeLabelTemplate : ShapeTemplate
    {
        public ShapeLabelTemplate()
		{
			Width = 96;
			Height = 32;
            BackGroundColor = Color.Black;
            ForeColor = Color.White;
            FitToSign = true;
			//Image = Resource.Images.Default;
		}
        private Font _textFont;
        /// <summary>
        /// Text font
        /// </summary>
        [Browsable(false)]
        public Font TextFont
        {
            get { return _textFont; }
            set { _textFont = value; }
        }
        [Category("FrameSize")]
        [RangeValidator(8, 1000)]
        public int Width
        {
            get { return Get<int>("Width"); }
            set
            {
                if (Sign == null&&FitToSign)
                    Set<int>("Width", System.Math.Abs(96));
                if (Sign == null && !FitToSign)
                    Set<int>("Width", System.Math.Abs(48));
                if (!FitToSign && value >= 8 && value <= 1000)
                    Set<int>("Width", System.Math.Abs(value));
                else if (Sign!=null&&FitToSign)
                    Set<int>("Width", System.Math.Abs(Sign.Width));
            }
        }

        [Category("FrameSize")]
        [RangeValidator(8, 1000)]
        public int Height
        {
            get { return Get<int>("Height"); }
            set
            {
                if(Sign==null && FitToSign)
                    Set<int>("Height", System.Math.Abs(32));
                if (Sign == null && !FitToSign)
                    Set<int>("Height", System.Math.Abs(16));
                if (!FitToSign && value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
                else if (Sign != null && FitToSign)
                    Set<int>("Height", System.Math.Abs(Sign.Height));
            }
        }
        private bool _fitToSign = true;
        public override bool FitToSign
        {
            get
            {
                return _fitToSign;
            }
            set
            {
                _fitToSign = value;
                if (Sign == null && value)
                {
                    Width = 96;
                    Height = 32;
                }
                if (Sign == null && !value)
                {
                    Height = 16;
                    Width = 48;
                }
                if (Sign!=null&&value)
                {
                    Height = Convert.ToInt32(Sign.Height);
                    Width = Convert.ToInt32(Sign.Width);
                }
                if (Sign != null && !value)
                {
                    Height = Convert.ToInt32(Sign.Height) / 2;
                    Width = Convert.ToInt32(Sign.Width) / 2;
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

        //private int _height;
        //private int _width;
        //[LocationValidatorAttribute(ValidatorType.Height)]
        //[Category("FrameSize")]
        //public virtual int Height
        //{
        //    get { return _height; }
        //    set
        //    {
        //        _height = value;
        //    }
        //}

        //[LocationValidatorAttribute(ValidatorType.Width)]
        //[Category("FrameSize")]
        //public virtual int Width
        //{
        //    get { return _width; }
        //    set { _width = value; }
        //}
        private Color _foreColor;
        /// <summary>
        /// Text background
        /// </summary>
        [DisplayName("Fore Color")]
        public Color ForeColor
        {
            get { return _foreColor; }
            set { _foreColor=value; }
        }

        private Color _backColor;
        /// <summary>
        /// Text background
        /// </summary>
        [DisplayName("BackGround Color")]
        public Color BackGroundColor
        {
            get { return _backColor; }
            set {_backColor= value; }
        }

        private bool _pwFontsOnly;
        [Browsable(false)]
        public virtual bool BitmapFontOnly
        {
            get { return _pwFontsOnly; }
            set { _pwFontsOnly = value; }
        }
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.TextLayer; }
        //}

        public override string Caption()
        {
            return SR.Type.Text;
        }

        public override string View()
        {
            return SR.View.Text;
        }
    }
}