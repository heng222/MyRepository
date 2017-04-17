//---------------------------------------------------------------------
//
// File: UpdateTotalWidthEventArgs.cs
//
// Description:
// UpdateTotalWidthEventArgs class
//
// Author: Jerry Xu
// Date  : 2008-9-17
//
//Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.UI.Controls.Playlist
{
    /// <summary>
    /// Update total width event args
    /// </summary>
    public class UpdateTotalWidthEventArgs:EventArgs
    {
        public readonly int AddWidth;

        public UpdateTotalWidthEventArgs(int addWidth)
        {
            AddWidth = addWidth;
        }
    }
}
