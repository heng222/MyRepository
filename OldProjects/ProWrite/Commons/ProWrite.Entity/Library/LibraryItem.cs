//---------------------------------------------------------------------
//
// File: LibraryItem.cs
//
// Description:
// The abstract class of LibraryItem
//
// Author: Louis
//
// Date:2008-7-04
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;
using ProWrite.Entity.Library;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract class LibraryItem : KeyInfo,ILibraryItem
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion
        
        [Browsable(false)]
		public abstract LibraryType Type { get;}		

		public virtual object[] ToArray()
		{
			return new object[] { Name, Type, null };
		}

		public virtual bool IsReferenceLibrary(LibraryItem library)
		{
			return false;
		}

		[Browsable(false)]
		public virtual LibraryType AcceptType
		{
			get { return LibraryType.None; }
		}

	}
}