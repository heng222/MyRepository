//---------------------------------------------------------------------
//
// File: ILibraryTreeController.cs
//      
// Description:
//      Library tree conterller interface
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


using ProWrite.Entity.Library.Controller;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Library tree conterller interface
    /// </summary>
    public interface ILibraryTreeController:ILibraryController
    {
        /// <summary>
        /// get or set library type to show in ui
        /// </summary>
        LibraryType Type { get;set;}
        /// <summary>
        /// load liabrary tree
        /// </summary>
        void Populate();
        /// <summary>
        /// open library item event
        /// </summary>
        event EventHandler<OpenLibraryEventArgs> OpenLibraryItem;
    }
}
