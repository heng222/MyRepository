//---------------------------------------------------------------------
//
// File: ShapeFigureTemplate.cs
//      
// Description:
//      Shape figure template class
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
using System.Drawing.Drawing2D;
using ProWrite.Core.Validation;
using ProWrite.Core;
using System.Drawing.Design;

namespace ProWrite.Entity.Settings
{
    [Editor(Constance.Designers.Enum, typeof(UITypeEditor))]
    [TypeConverter(typeof(EnumTypeConverter))]
    public enum DashKind
    {
        [EnumDescription]
        Solid = 0,
        [EnumDescription]
        Dash = 1,
        [EnumDescription]
        Dot = 2,
        [EnumDescription("Dash Dot")]
        DashDot = 3,
        [EnumDescription("Dash Dot Dot")]
        DashDotDot = 4,
       
    }

    /// <summary>
    /// Shape figure template class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.PaintLayer)]
    public class ShapeFigureTemplate : ShapeTemplate
    {
        public ShapeFigureTemplate()
        {
            LineWidth = 1;
            LineDashKind = DashKind.Solid;
            LineColor = Color.White;
        }

        private int _lineWidth;
        //[Category("Layout")]
        [RangeValidator(1, 10)]
        [DisplayName("Line Width")]
        public virtual int LineWidth
        {
            get { return _lineWidth; }
            set
            {
                if (value >= 1 && value <= 10)
                    _lineWidth = value;
            }
        }

        private DashKind _lineDashKind;
        [DisplayName("Line Dash Style")]
        public DashKind LineDashKind
        {
            get { return _lineDashKind; }
            set { _lineDashKind = value; }
        }

        [Browsable(false)]
        public DashStyle LineDashStyle
        {
            get { return (DashStyle)_lineDashKind; }
        }

        private Color _lineColor;
        /// <summary>
        /// 
        /// </summary>
        [DisplayName("Line Color")]
        public Color LineColor
        {
            get { return _lineColor; }
            set { _lineColor = value; }
        }
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.PaintLayer; }
        //}
        [Browsable(false)]
        public override bool FitToSign
        {
            get
            {
                return base.FitToSign;
            }
            set
            {
                base.FitToSign = value;
            }
        }
        public override string Caption()
        {
            return SR.Type.Paint;
        }

        public override string View()
        {
            return SR.View.Paint;
        }
        
    }
}