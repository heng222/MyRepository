//---------------------------------------------------------------------
//
// File: UserManagerAction.cs
//
// Description:
// The uploadAction class of UserManager
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
    class UserManagerAction : IRequestAction
    {
        public void Perform()
        {
            using(var user = new UserForm())
                user.ShowModalDialog();
        }
    }
}
