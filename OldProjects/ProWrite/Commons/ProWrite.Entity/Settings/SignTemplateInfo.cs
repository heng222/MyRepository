//---------------------------------------------------------------------
//
// File: SignTemplateInfo.cs
//      
// Description:
//      Sign template info class
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
using System.Drawing;
using System.ComponentModel;
using ProWrite.Core;
using ProWrite.Entity.Settings;
using System.Drawing.Design;
using System.Xml.Serialization;
using ProWrite.Core.Validation;

namespace ProWrite.Entity.Settings
{
    /// <summary>
    /// Sign template info class
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.Sign)]
    public class SignTemplateInfo : TemplateInfo
    {
        public SignTemplateInfo()
        {
            Width = 96;
            Height = 32;
            AutoLogin = false;
            //Image = Resource.Images.Default;
        }
        //[Category("Type")]
        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.Sign; }
        //}

        [Category("Size")]
        [RangeValidator(8, 1000)]
        public int Width
        {
            get { return Get<int>("Width"); }
            set
            {
                if (value >= 8 && value <= 1000)
                    Set<int>("Width", System.Math.Abs(value));
            }
        }

        [Category("Size")]
        [RangeValidator(8, 1000)]
        public int Height
        {
            get { return Get<int>("Height"); }
            set
            {
                if (value >= 8 && value <= 1000)
                    Set<int>("Height", System.Math.Abs(value));
            }
        }
        [DisplayName("Sign Type")]
        public SignType SignType
        {
            get { return Get<SignType>("SignType"); }
            set
            {
                Set<SignType>("SignType", value);
            }
        }
        [DisplayName("Auto Login")]
        [Browsable(false)]
        public bool AutoLogin { get; set; }

        [Editor(Constance.Designers.Image, typeof(UITypeEditor))]
        [XmlIgnore]
        public string Image
        {
            get { return Get<string>("Image"); }
            set { Set<string>("Image", value); }
        }

        public override string Caption()
        {
            return SR.Type.Sign;
        }

        public override string View()
        {
            return SR.View.Sign;
        }

        public override IEnumerator<TemplateInfo> GetEnumerator()
        {
            yield return null;
        }
        
    }
}