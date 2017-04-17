//---------------------------------------------------------------------
//
// File: Commands.cs
//
// Description:
// Command constance class
//
// Author: Kevin
// 
// Modify History:
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;

namespace ProWrite.UFE
{
    

    public enum Role
    {
        None = -1,
        Default = 5,
        Administrator = 4,
        All = 3,
        Commands = 2,
        FileTransfer = 1,
    }

    public enum TestPatternType
    {
        // PATTERNDISABLE = Turn off patterns / also a NULL type
        PATTERNDISABLE = 0,
        // FILL = Fill the screen with a color
        //    color defined as a long RGB
        FILL,
        // HRAMP = Fill sign with horizontal ramp incremented by an 
        //         indicated number of pixels
        HRAMP,
        // VRAMP = Fill sign with vertical ramp incremented by an 
        //         indicated number of pixels
        VRAMP,
        // CROSS = Fill sign with a cross pattern
        CROSS,
        // DIAGONAL = Fill sign with a diagonal pattern
        DIAGONAL,
        // VERTICAL = Fill sign with a vertical pattern
        VERTICAL,
        // COLORBAR = Fill sign with color bars (canned colors)
        COLORBAR,
        // COLORGRID = Fill sign with color grid (canned colors)
        COLORGRID,
        // CUSTOM = Load a specific image and tile as pattern
        CUSTOM
    }

    public enum PlayLevel
    {
        Immediate = 1,
        Next = 2,
        Normal = 3,
    }

    public enum UserStatus
    {
        Unkonwn = -1,
        Offline = 0,
        Online = 1,
    }
}
