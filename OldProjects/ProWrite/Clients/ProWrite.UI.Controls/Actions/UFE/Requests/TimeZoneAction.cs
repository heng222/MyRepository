//---------------------------------------------------------------------
//
// File: TimeZoneAction.cs
//
// Description:
// The uploadAction class of set TimeZone
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UI.Controls.Dashboard;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of set TimeZone
    /// </summary>
    class TimeZoneAction : RequestActionBase
    {
        public override void Perform()
        {
            using (ProWrite.UI.Controls.Dashboard.TimeZone dlg = new ProWrite.UI.Controls.Dashboard.TimeZone())
                dlg.ShowModalDialog();
        }
    }
}
