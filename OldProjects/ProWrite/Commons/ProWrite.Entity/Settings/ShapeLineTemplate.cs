//---------------------------------------------------------------------
//
// File: ShapeLineTemplate.cs
//      
// Description:
//      Shape Line Template class
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

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Shape Line Template class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class ShapeLineTemplate:ShapeTemplate
	{
        private int _thickness;
        //[Category("Layout")]
        public virtual int Thickness
        {
            get { return _thickness; }
            set
            {
                _thickness = value;
            }
        }

        //[Browsable(false)]
        //public override TemplateType Type
        //{
        //    get { return TemplateType.Line; }
        //}

        public override string Caption()
        {
            return SR.Type.Line;
        }

        public override string View()
        {
            return SR.View.Line;
        }
        
	}
}