//---------------------------------------------------------------------
//
// File: SetDateTimeAction.cs
//
// Description:
// The uploadAction class of SetDateTime
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
using ProWrite.UI.Controls.Dashboard;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of SetDateTime
    /// </summary>
    class SetDateTimeAction : IRequestAction
    {
        public void Perform()
        {
            using(var dateTime = new DateTimeSet())
                dateTime.ShowModalDialog();
        }
    }
}
