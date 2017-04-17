//---------------------------------------------------------------------
//
// File: TrackBarValueChangeEventArgs.cs
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
    /// Track bar value change event args
    /// </summary>
    public class TrackBarValueChangeEventArgs:EventArgs
    {
        public readonly int PlayValue;

        public TrackBarValueChangeEventArgs(int playValue)
        {
            PlayValue = playValue;
        }
    }
}
