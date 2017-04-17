//---------------------------------------------------------------------
//
// File: IDataProvider.cs
//
// Description:
// 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Library;

namespace ProWrite.Entity
{
    public interface IFileHandle
    {
        string FileHandle { get; set; }
        string FileUrl { get; set; }
    }

    public class FileLibraryRenameMessage : PWMessage
    {
        public readonly FileLibraryItem Item;
        public FileLibraryRenameMessage(FileLibraryItem item)
        {
            Item = item;
        }
    }
}
