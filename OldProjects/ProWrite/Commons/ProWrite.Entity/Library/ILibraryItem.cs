//---------------------------------------------------------------------
//
// File: ILibraryItem.cs
//
// Description:
//      Library item  interface
//
// Author: Kevin 2008-7-22
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
	/// <summary>
	/// library item interface
	/// </summary>
	public interface ILibraryItem:IKeyInfo
	{
		/// <summary>
		/// get library type
		/// </summary>
		LibraryType Type { get;}
		object[] ToArray();
	}

    public interface ILockLibraryItem:ILibraryItem
    {
        bool IsLock { get;set;}
        int LockCount { get; }
        void FromTo(ILockLibraryItem item, int lockCounter);
    }
}