//---------------------------------------------------------------------
//
// File: ImportExportBase.cs
//      
// Description:
//      ImportExportBase class
//
// Author: Kevin 2009-3-27
//
// Modify History:
//      Jerry Xu 2009-4-1 Update method:MemoryLibraryItem OnImportOpen(string fileName)
//      Jerry Xu 2009-4-22 Add class:TimeSliceGroupImportExport
//                         Update class:ImportExportBase
//      Jerry Xu 2009-4-29 Update method:OnImportOpen(string fileName)
//      Jerry Xu 2009-4-30 Update method:ImportPlaylistRename(List<MessageFileItem> listFiles, List<MessageItem> listMessages, List<TimeSliceGroupItem> listTimesliceGroups, List<PlaylistItem> listPlaylists, PlaylistItem playlistItem)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Entity.Library;
using ProWrite.Entity.Library.ImportExport;
using ProWrite.Entity.Library.Controller;
using System.IO;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ImportExportFactoryAttribute : Attribute
    {
    }

    public interface IImportExportFactory
    {
        IImportExport Create(string fileName);
        string Extension { get; }
        string ModuleName { get; }
    }

    public interface IImportExport
    {
        void OnImport(string fileName);
        void OnExport(string fileName, LibraryItem item);
        MemoryLibraryItem OnImportOpen(string fileName);
        void OnExportOpen(string fileName);

    }

   

}
