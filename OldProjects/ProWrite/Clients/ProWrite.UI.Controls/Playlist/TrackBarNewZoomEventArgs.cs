//---------------------------------------------------------------------
//
// File: TrackBarNewZoomEventArgs.cs
//
// Description:
// TrackBarNewZoomEventArgs class
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
using ProWrite.Core;


namespace ProWrite.UI.Controls.Playlist
{
    /// <summary>
    /// TrackBarNew zoom event args
    /// </summary>
    public class TrackBarNewZoomEventArgs:EventArgs
    {
        public readonly ZoomType Zoom;

        public TrackBarNewZoomEventArgs(ZoomType zoom)
        {
            Zoom = zoom;
        }
    }
}
