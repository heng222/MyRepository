//---------------------------------------------------------------------
//
// File: ImageController.cs
//      
// Description:
//      Image conterller class
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
using ProWrite.Entity.Library;
using System.IO;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Library.Controller
{
	/// <summary>
	/// Image conterller class
	/// </summary>
	[Serializable]
	public class ImageController : FileLibraryController<ImageInfo>
	{
        protected override string LibraryDir
        {
            get
            {
                return Constance.LibraryImageDir;
            }
        }

        public override bool Rename(string newName, string oldName)
        {
            return base.Rename(newName, oldName, ShapeType.Image);
        }
	}
}