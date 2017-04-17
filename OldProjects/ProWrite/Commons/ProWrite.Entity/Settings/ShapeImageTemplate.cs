//---------------------------------------------------------------------
//
// File: ShapeImageTemplate.cs
//      
// Description:
//      Shape Image Template  class
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
using ProWrite.Entity.Shape;
using System.Windows.Forms;
using ProWrite.Core.Validation;
using ProWrite.Core;
using System.Drawing.Design;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// Shape Image Template class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.ImageLayer)]
    public class ShapeImageTemplate : ShapeTemplate
    {

        public ShapeImageTemplate()
        {
            Width = 48;
            Height = 16;

        }
        private int _frame;
        private ImageSizeMode _sizeMode = ImageSizeMode.Zoom;


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
                if (!FitToSign&&value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
                else if (Sign != null && FitToSign)
                    Set<int>("Height", System.Math.Abs(Sign.Height));
                if (Sign == null && value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
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
        [Browsable(false)]
        public virtual int Frame
        {
            get { return _frame; }
            set { _frame = value; }
        }
        [DisplayName("Size Mode")]
        public ImageSizeMode SizeModeType
        {
            get { return _sizeMode; }
            set
            {
                _sizeMode = value;
            }
        }


        [Browsable(false)]
        public PictureBoxSizeType SizeMode
        {
            get { return (PictureBoxSizeType)SizeModeType; }
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
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.ImageLayer; }
        //}
        
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

        public override string Caption()
        {
            return SR.Type.Image;
        }

        public override string View()
        {
            return SR.View.Image;
        }

    }


    [Editor(Constance.Designers.Enum, typeof(UITypeEditor))]
    [TypeConverter(typeof(EnumTypeConverter))]
    public enum ImageSizeMode
    {
        [EnumDescription]
        Normal = 0,
        [EnumDescription("Stretch Image")]
        StretchImage = 1,
        //[EnumDescription("Auto Size")]
        //AutoSize = 2,
        [EnumDescription("CENTER Image")]
        CenterImage = 3,
        [EnumDescription]
        Zoom = 4,

    }
}