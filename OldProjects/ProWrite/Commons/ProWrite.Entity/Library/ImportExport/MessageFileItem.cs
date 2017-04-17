//---------------------------------------------------------------------
//
// File: MessageFileItem.cs
//      
// Description:
//      MessageInfo file item class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2008-12-29 Import message:File handle
//                          Add property:OldItem(FileItem)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Library.ImportExport
{
    /// <summary>
    /// MessageInfo import and export file class
    /// </summary>
    public class MessageFileItem
    {
        public FileItem Item { get; set; }
        public FileItem OldItem { get; set; }
        public bool IsValid { get; set; }
    }
}
