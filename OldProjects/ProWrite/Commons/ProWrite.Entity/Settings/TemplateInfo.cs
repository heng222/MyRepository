//---------------------------------------------------------------------
//
// File: TemplateInfo.cs
//      
// Description:
//      Template  base class
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
using System.Runtime.Serialization;
using System.Collections;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Template  base class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract class TemplateInfo:DictionaryEntity,IOptionViewable, IEnumerable<TemplateInfo>
	{
		
		//[Browsable(false)]
		//public abstract TemplateType Type { get;}

        public abstract string Caption();
        public abstract string View();

		public abstract IEnumerator<TemplateInfo> GetEnumerator();
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator() as IEnumerator;
        }

        public override string ToString()
        {
            //return EnumHelper.GetEnumDescription(Type);
            return Caption();
        }
	}


}