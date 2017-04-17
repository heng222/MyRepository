//---------------------------------------------------------------------
//
// File: LoginAction.cs
//
// Description:
// The uploadAction class of Login
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
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using System.Windows.Forms;
using ProWrite.UFE;
using ProWrite.UI.Controls.Dashboard;
using System.Net;
using System.Net.Tcp;
using System.Communication;
using ProWrite.UI.Controls.Common.Messages;
//using Tamir.SharpSsh.jsch;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of Login
    /// </summary>
    public class LoginAction : RequestActionBase
    {
        private Dictionary<ConnectionMode, Func<Form>> _map;

        //static bool _isCancelConnect = false;
        public LoginAction()
        {
            _map = new Dictionary<ConnectionMode, Func<Form>>();
            _map[ConnectionMode.Tcp] = () => { return new ConnectTcpIpForm(); };
            //_map[ConnectionMode.Modem] = () => { return new ConnectModemForm(); };
            //_map[ConnectionMode.RS232] = () => { return new ConnectRS232Form(); };
            ////_map[ConnectionMode.Mock] = () => { return null; };
            //_map[ConnectionMode.None] = () => { return null; };

        }

        public bool IsCancel { get; set; }


        public override void Perform()
        {
            string pwd = "";
            if (ControlService.SignCombo.Current.LoginInfomation.ConnectionPassword != null
                && ControlService.SignCombo.Current.LoginInfomation.ConnectionPassword != "")
                pwd = ControlService.SignCombo.Current.LoginInfomation.ConnectionPassword;
            else
                pwd = InputDialog.GetInputValue("Enter Password");
            if (InputDialog.Result == DialogResult.Cancel)
            {
               
                ActionHelper.OnDisconnected(true);
                return;
            }
            if (pwd == null)
                pwd = "";
            var sign =ControlService.SignCombo.Current;
            ConnectionProgress progerss = new ConnectionProgress(sign, true, pwd);
            progerss.ShowModalDialog();

            if (!progerss.Result)
                ActionHelper.OnDisconnected(true);
            else
            {
                LiveImageAction liveImageAction = new LiveImageAction();
                liveImageAction.Sign = sign;
                liveImageAction.Perform();

                StatusAction statusAction = new StatusAction(false);
                statusAction.Sign = sign;
                statusAction.Perform();

                GetStatusAction getStatus = new GetStatusAction();
                getStatus.sign = sign;
                getStatus.Perform();

                LogViewAction logviewAction = new LogViewAction();
                logviewAction.sign = sign;
                logviewAction.Perform();
                if (sign.IsWebCam)
                {
                    
                    this.InvokeMethod(() => ControlService.SignImage.RefreshImageCamera(sign));
                    
                }

                ControlService.SignCombo.Current.IsConnected = "Connected";
                ControlService.DashboardTree.PopulateTree();
//#if VERSION_2
//                AuthenticateService auth = new ProWriteAuthenticateService();
//                if (auth.IsShowLivePage())
//                    ModuleManager.DisplayModule(ModuleNames.Live);
//#endif
            }
            return;
        }
    }
}
