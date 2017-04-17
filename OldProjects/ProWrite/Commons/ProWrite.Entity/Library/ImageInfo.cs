//---------------------------------------------------------------------
//
// File: ImageFileLibraryItem.cs
//
// Description:
// The class of ImageFileLibraryItem
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
using System.Drawing;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
	[Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
	public class ImageInfo: FileLibraryItem
	{
		public override LibraryType Type
		{
			get { return LibraryType.Image; }
		}

        public ImageInfo() { }

        public ImageInfo(string path) : base(path) { }
	}
}