//---------------------------------------------------------------------
//
// File: VideoFileLibraryItem.cs
//
// Description:
// The class of VideoFileLibraryItem
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
	public class VideoInfo :FileLibraryItem
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public override LibraryType Type
		{
			get { return LibraryType.Video; }
		}

		public VideoInfo() { }

		public VideoInfo(string path) : base(path) { }
	}
}