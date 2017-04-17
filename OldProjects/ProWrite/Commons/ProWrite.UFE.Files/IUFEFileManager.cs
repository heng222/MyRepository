//---------------------------------------------------------------------
//
// File: IUFEFileManager.cs
//
// Description:
// IUFEFileManager class and LocalFilePathMapping class
//
// Author: 
//
//Modify History:
//      Jerry Xu  2008-12-1 

//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using System.IO;
using ProWrite.Entity.Dashboard;
using System.Drawing;
using ProWrite.Entity.Library;

namespace ProWrite.UFE.Files
{
    
    public interface IUFEFileSaver<TLibrary>
    {
        SignInfo Sign { get; set; }
        TLibrary Item { get; set; }

        List<UfeFile> NeedUpdatedItems { get; }
        List<UfeFile> Files { get;}
        List<UfeFile> DeletedItems { get; }

        bool IsSaveSucessed { get; }
        void Populate();

        void Save();
    }

   
}
