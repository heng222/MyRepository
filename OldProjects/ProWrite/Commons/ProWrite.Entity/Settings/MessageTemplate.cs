//---------------------------------------------------------------------
//
// File: MessageTemplate.cs
//      
// Description:
//      Message Template class
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
using ProWrite.Entity.Shape;
using ProWrite.Core.Validation;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// Message template class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.Message)]
    public class MessageTemplate : TemplateInfo
    {
        #region Fields
        private ShapeFigureTemplate _paintLayer;
        private ShapeImageTemplate _image;
        private ShapeLabelTemplate _label;
        private ShapeLineTemplate _line;
        private ShapeMarqueeTemplate _marquee;
        private ShapeTemperatureTemplate _temperature;
        private ShapeTimeTemplate _time;
        private ShapeVideoTemplate _video;
        private int _height;
        private int _width;
        private int _locationX;
        private int _locationY;
        private bool _isShowGrid = true;
        private float _excursion;
        private int _zoom = 1;
        #endregion

        public MessageTemplate()
        {
            _paintLayer = new ShapeFigureTemplate();
            _image = new ShapeImageTemplate();
            _label = new ShapeLabelTemplate();
            _line = new ShapeLineTemplate();
            _marquee = new ShapeMarqueeTemplate();
            _temperature = new ShapeTemperatureTemplate();
            _time = new ShapeTimeTemplate();
            _video = new ShapeVideoTemplate();
            BackGroundColor = Color.Black;
            DisplayTime = 8;
        }
        /// <summary>
        /// 
        /// </summary>
        [DisplayName("BackGround Color")]
        public Color BackGroundColor
        {
            get { return Get<Color>("BackGround"); }
            set { Set<Color>("BackGround", value); }
        }

        /// <summary>
        /// get or set marquee template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        [DisplayName("Dynamic Text Layer")]
        public ShapeMarqueeTemplate DynamicTextLayer { get { return _marquee; } set { _marquee = value; } }
        /// <summary>
        /// get or set figure template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeFigureTemplate PaintLayer { get { return _paintLayer; } set { _paintLayer = value; } }
        /// <summary>
        /// get or set shape template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeImageTemplate ImageLayer { get { return _image; } set { _image = value; } }
        /// <summary>
        /// get or set line template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeLineTemplate Line
        {
            get { return _line; }
            set { _line = value; }
        }
        /// <summary>
        /// get or set temperature template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeTemperatureTemplate TemperatureLayer { get { return _temperature; } set { _temperature = value; } }
        /// <summary>
        /// get or set label template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeLabelTemplate TextLayer
        {
            get { return _label; }
            set { _label = value; }
        }
        /// <summary>
        /// get or set time template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeTimeTemplate TimeLayer { get { return _time; } set { _time = value; } }

        /// <summary>
        /// get or set video template
        /// </summary>
        [Category("Shape")]
        [Browsable(false)]
        public ShapeVideoTemplate VideoLayer { get { return _video; } set { _video = value; } }
        [RangeValidator(1, 100)]
        //[Category("Layout")]
        [Browsable(false)]
        public virtual int Height
        {
            get { return _height; }
            set
            {
                if (value >= 1 && value <= 100 && value != _height)
                    _height = value;
            }
        }

        [RangeValidator(1, 100)]
        [Browsable(false)]
        public virtual int Width
        {
            get { return _width; }
            set
            {
                if (value >= 1 && value <= 100 && value != _width)
                    _width = value;
            }
        }

        [RangeValidator(1, 100)]
        [Browsable(false)]
        public virtual int LocationX
        {
            get { return _locationX; }
            set
            {
                if (value >= 1 && value <= 100 && value != _locationX)
                    _locationX = value;
            }
        }

        [RangeValidator(1, 100)]
        [Browsable(false)]
        public virtual int LocationY
        {
            get { return _locationY; }
            set
            {
                if (value >= 1 && value <= 100 && value != _locationY)
                    _locationY = value;
            }
        }
        [Browsable(false)]
        public virtual float Excursion
        {
            get { return _excursion; }
            set { _excursion = value; }
        }
        [DisplayName("Is Show Grid")]
        public virtual bool IsShowGrid
        {
            get { return _isShowGrid; }
            set { _isShowGrid = value; }
        }

        [RangeValidator(1, 999)]
        [DisplayName("Display Time(s)")]
        public int DisplayTime
        {
            get { return Get<int>("DefaultLength"); }
            set
            {
                if (value >= 1 && value <= 999)
                    Set<int>("DefaultLength", System.Math.Abs(value));
            }
        }
        [Browsable(false)]
        public int Zoom
        {
            get { return _zoom; }
            set
            {
                _zoom = value;
            }
        }

        #region override method and property
        ///// <summary>
        ///// get template type
        ///// </summary>
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.Message; }
        //}

        public override string Caption()
        {
            return SR.Type.Message;
        }

        public override string View()
        {
            return SR.View.Message;
        }


        public override IEnumerator<TemplateInfo> GetEnumerator()
        {
            //yield return _marquee;
            yield return _image;
            yield return _paintLayer;
            yield return _temperature;
            yield return _label;
            yield return _time;
            yield return _video;
            //yield return _line;
        }
        #endregion

        
    }
}
