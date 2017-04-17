//---------------------------------------------------------------------
//
// File: DimmingAction.cs
//
// Description:
// The uploadAction class of Dimming
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
using ProWrite.Core;
using System.Communication;
using ProWrite.UI.Controls.Dashboard;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of Dimming
    /// </summary>
    class DimmingAction : RequestActionBase
    {
        public override void Perform()
        {
            using(Dimming dlg = new Dimming())
                dlg.ShowModalDialog();
        }
    }
}
