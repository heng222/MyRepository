//---------------------------------------------------------------------
//
// File: TempOfferAction.cs
//
// Description:
// The uploadAction class of TempOffer
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
    /// The uploadAction class of TempOffer
    /// </summary>
    class TempOfferAction : IRequestAction
    {
        public void Perform()
        {
            using(var temp = new TempOffset())
                temp.ShowModalDialog();
        }
    }
}
