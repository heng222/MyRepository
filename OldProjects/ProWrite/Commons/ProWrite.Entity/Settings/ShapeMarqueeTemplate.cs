//---------------------------------------------------------------------
//
// File: ShapeMarqueeTemplate.cs
//      
// Description:
//      Shape Marquee Template class
//
// Author: Kevin 2008-7-28
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
using ProWrite.Core;
using ProWrite.Core.Validation;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// Shape Marquee Template class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.DynamicTextLayer)]
    public class ShapeMarqueeTemplate : ShapeTemplate
    {
        public ShapeMarqueeTemplate()
        {
            Width = 48;
            Height = 16;
            BackGroundColor = Color.Transparent;
            ForeColor = Color.White;
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
        protected override void OnSignSizeChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
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

        private Color _backColor;
        /// <summary>
        /// Text background
        /// </summary>
        [DisplayName("BackGround Color")]
        public Color BackGroundColor
        {
            get { return _backColor; }
            set { _backColor = value; }
        }

        private int _RollRate = 3;
        [Category("Scroll")]
        [RangeValidator(1, 1000)]
        [DisplayName("Roll Rate")]
        public int RollRate
        {
            get { return _RollRate; }
            set
            {
                if (value>=1&&value<=1000&&value != RollRate)
                {
                    _RollRate = value;
                }
            }
        }

        private RollWay _RollWay = RollWay.RightToLeft;
        [Category("Scroll")]
        [DisplayName("Roll Way")]
        public RollWay RollWay
        {
            get { return _RollWay; }
            set
            {
                if (value != RollWay)
                {
                    _RollWay = value;
                }
            }
        }

        private Valign _Valign = Valign.MIDDLE;
        [Browsable(false)]
        public Valign Valign
        {
            get { return _Valign; }
            set
            {
                if (value != Valign)
                {
                    _Valign = value;
                }
            }
        }

        private Align _Align = Align.LEFT;
        public Align Align
        {
            get { return _Align; }
            set
            {
                if (value != Align)
                {
                    _Align = value;
                }
            }
        }
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.DynamicTextLayer; }
        //}

        public override string Caption()
        {
            return SR.Type.DynamicText;
        }

        public override string View()
        {
            return SR.View.DynamicText;
        }
    }
}