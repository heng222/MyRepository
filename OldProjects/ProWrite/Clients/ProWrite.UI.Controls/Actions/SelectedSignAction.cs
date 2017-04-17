//---------------------------------------------------------------------
//
// File: SelectedSignAction.cs
//
// Description:
// The Action class of SelectedSign
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
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UFE;
using System.Communication;

namespace ProWrite.UI.Controls.Actions
{
    /// <summary>
    /// The Action class of Current Sign changed
    /// </summary>
    class SelectedSignAction:RequestActionBase
    {
        private SignInfo _sign;
        public SelectedSignAction(SignInfo sign)
        {
            _sign = sign;
        }

        public override void Perform()
        {
            bool state = _sign.Controller.Connection != null
                           && _sign.Controller.Connection.State == ConnectionState.Opened;
            if (state)
            {
                bool online = _sign.Controller.Connection.User.Status == UserStatus.Online;
                _sign.IsConnected = "Connected";
                if (online)
                    ActionHelper.OnAfterLogin(_sign.Controller.Connection.User);
                else
                    ActionHelper.OnConnected();
            }
            else if (_sign.Controller.Connection.State == ConnectionState.Opening)
                ActionHelper.OnCancelConnect();
            else
            {
                _sign.IsConnected = "Disconnected";
                ActionHelper.OnDisconnected(_sign.DashboardType == ProWrite.Core.DashboardType.Sign);
            }
            ControlService.DashboardTree.PopulateTree();
        }
    }
}
