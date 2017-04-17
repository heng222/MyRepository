//---------------------------------------------------------------------
//
// File: UFERequestService.cs
//
// Description:
// The class of UFE Request Service
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
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The class of UFE Request Service
    /// </summary>
    public class UFERequestService:IDisposable
    {
        private Dictionary<MenuCommands, IRequestAction> _actions; 
        public UFERequestService()
        {
            _actions = new Dictionary<MenuCommands, IRequestAction>();
            _actions[MenuCommands.Connect] = new LoginAction();
            _actions[MenuCommands.DisConnect]=  new LogoffAction();
            _actions[MenuCommands.Dimming] = new DimmingAction();
            _actions[MenuCommands.ResetTime] = new SetDateTimeAction();
            _actions[MenuCommands.TempOffset] = new TempOfferAction();
            _actions[MenuCommands.UserManager] = new UserManagerAction();
            _actions[MenuCommands.BlankSign] = new BlankSignAction();
            _actions[MenuCommands.UnBlankSign] = new UnBlankSignAction();
            _actions[MenuCommands.TestPattern] = new  TestPatternAction();
            _actions[MenuCommands.LiveImage] = new LiveImageAction();
            _actions[MenuCommands.RebootCXC] = new RebootAction();
            _actions[MenuCommands.TimeZone] = new TimeZoneAction();
            _actions[MenuCommands.GoLive] = new GoLiveAction();
            _actions[MenuCommands.CancelConnect] = _actions[MenuCommands.Connect];

            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += Update;
        }

        private void Update(object sender, PWMessage<MenuCommands> msg)
        {
            IRequestAction action = null;
            _actions.TryGetValue(msg.Content, out action);
            if (action != null)
            {
                LoginAction loginAction = action as LoginAction;
                if (loginAction != null)
                {
                    loginAction.IsCancel = msg.Content == MenuCommands.CancelConnect;
                }
                
                action.Perform();
            }
        }

        public void Dispose()
        {
            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers -= Update;
        }
    }
}
