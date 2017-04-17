//---------------------------------------------------------------------
//
// File: FileItem.cs
//      
// Description:
//      File item class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2008-12-29 Import message:File handle
//                          Add new method:Copy
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library.ImportExport
{
    /// <summary>
    /// File item class:Import or Export message
    /// </summary>
    [Serializable]
    public class FileItem
    {
        public string Id;
        public string Name;
        public string Path;
        public LibraryType Type;
        public byte[] Content;

        /// <summary>
        /// Function: Clone a FileItem
        /// Author  : Jerry Xu
        /// Date    : 2008-12-29
        /// </summary>
        /// <returns>FileItem</returns>
        public FileItem Copy()
        {
            FileItem item = new FileItem();
            item.Id = Id;
            item.Name = Name;
            item.Path = Path;
            item.Type = Type;
            return item;
        }
    }
}
