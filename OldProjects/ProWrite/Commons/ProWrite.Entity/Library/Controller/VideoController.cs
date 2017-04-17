// File: ImageController.cs
//      
// Description:
//      Video conterller class
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
using ProWrite.Core;
using ProWrite.Entity.Library.Controller;
using System.IO;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Library.Controller
{
	[Serializable]
	public class VideoController : FileLibraryController<VideoInfo>
	{
        protected override string LibraryDir
        {
            get
            {
                return Constance.LibraryVideoDir;
            }
        }

        public override bool Rename(string newName, string oldName)
        {
            return Rename(newName, oldName, ShapeType.Video);
        }
	}
}