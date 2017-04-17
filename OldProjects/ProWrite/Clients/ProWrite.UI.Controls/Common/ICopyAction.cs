//---------------------------------------------------------------------
//
// File: ICopyAction.cs
//
// Description:
//      Copy paste uploadAction interface
//
// Author: Kevin 2008-8-11
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.UI.Controls.Common
{
	/// <summary>
	/// Copy paste uploadAction interface
	/// </summary>
	public interface ICopyAction
	{
		/// <summary>
		/// Can copy
		/// </summary>
		bool CanCopy { get;}
		/// <summary>
		/// Copy
		/// </summary>
		void Copy();
		/// <summary>
		/// Can paste
		/// </summary>
		bool CanPaste { get;}
		/// <summary>
		/// Paste
		/// </summary>
		void Paste();
	}
}