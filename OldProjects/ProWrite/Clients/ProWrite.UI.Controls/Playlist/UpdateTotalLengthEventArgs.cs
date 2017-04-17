//---------------------------------------------------------------------
//
// File: UpdateTotalLengthEventArgs.cs
//
// Description:
// UpdateTotalLengthEventArgs class
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
    /// Update total length event args
    /// </summary>
    public class UpdateTotalLengthEventArgs:EventArgs
    {
        public readonly string TotalLength;

        public UpdateTotalLengthEventArgs(string length)
        {
            TotalLength = length;
        }
    }
}
