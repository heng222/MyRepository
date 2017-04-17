//---------------------------------------------------------------------
//
// File: TemplateGroups.cs
//      
// Description:
//      Template Groups class
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
using ProWrite.Entity.Settings;
using ProWrite.Core;

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Template Groups class
	/// </summary>
	[Serializable]
	public class TemplateGroups:ListSet<TemplateGroup>
	{
		[OnDeserialized]
		private void Deserialized(StreamingContext ctx)
		{
			AddDefaultItem();
		}

        
		internal void AddDefaultItem()
		{
			bool hasDefault = false;
			foreach (TemplateGroup item in this)
			{
				if (item.IsDefault)
				{
					hasDefault = true;
					if (item.Sign == null)
						item.Sign = new SignTemplateInfo();
					break;
				}
			}

			if (!hasDefault)
			{
				TemplateGroup.Current = TemplateGroup.Default;
				Add(TemplateGroup.Current);
			}
		}
	}
}