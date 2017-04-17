//---------------------------------------------------------------------
//
// File: LogoffAction.cs
//
// Description:
// The uploadAction class of Logoff
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
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;
using System.Threading;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraTreeList.Nodes;
using ProWrite.UI.Controls.Dashboard;
using ProWrite.UFE.Entity;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The uploadAction class of Logoff
    /// </summary>
    class LogoffAction : RequestActionBase
    {
        public LogoffAction()
        {
        }
        public LogoffAction(bool isDisConnect)
        { 
        }

        private SignInfo _sign;
        private Action _successCallback;
        private Action _failCallback;
        private bool _isConfirm=true;
        public LogoffAction(SignInfo sign, Action successCallback, Action failCallback)
        {
            _sign = sign;
            _successCallback = successCallback;
            _failCallback = failCallback;
            _isConfirm = true;
        }

        public LogoffAction(SignInfo sign, Action successCallback, Action failCallback,bool isConfirm)
        {
            _sign = sign;
            _successCallback = successCallback;
            _failCallback = failCallback;
            _isConfirm = isConfirm;
        }

        public override void Perform()
        {
            if (_isConfirm && MsgBox.Confirm("Confirm Sign Disconnect?") == System.Windows.Forms.DialogResult.No)
                return;
            var sign = _sign == null ? ControlService.SignCombo.Current : _sign;

            var controller = sign.Controller;
            var libFiles = new List<UfeFile>();
            if (controller.Connection.State  != System.Communication.ConnectionState.Opened)
                return;

            if (controller.Connection.User.Status == UserStatus.Online)
            {
                DataGate.Log.Info("Start logoff.");
                //Do Logoff
                controller.SendAsync(Commands.Logoff, p =>
                {
                    var closeTask = controller.Connection.Close();
                    if (!closeTask.IsCompleted)
                        closeTask.Wait();

                    if (closeTask.IsSuccessed)
                    {
                        DataGate.Log.Info("Logoff successed");
                        if (_successCallback != null)
                            _successCallback();
                    }
                    else
                    {
                        DataGate.Log.Error("Logoff failed. ");
                        if (_failCallback != null)
                            _failCallback();
                    };
                });               
            }
            else
            {
                DataGate.Log.Info("Start disconnect.");
                var closeTask = controller.Connection.Close();
                if (!closeTask.IsCompleted)
                    closeTask.Wait();

                if (closeTask.IsSuccessed)
                {
                    DataGate.Log.Info("Disconnect successed");
                    if (_successCallback != null)
                        _successCallback();
                }
                else
                {
                    DataGate.Log.Error("Disconnect failed.");
                    if (_failCallback != null)
                        _failCallback();
                }
            }
            var focusedNode = ControlService.DashboardTree.FocusedNode;
            if (focusedNode != null)
                focusedNode.ImageIndex = DashboardTree._.SignImageIndex;
            sign.IsBlankSign = true;
            sign.IsConnected = "Disconnected";
            ActionHelper.OnDisconnected(false);
            ControlService.DashboardTree.PopulateTree();
        }      
    }
}
