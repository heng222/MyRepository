//---------------------------------------------------------------------
//
// File: DashboardTree.cs
//
// Description:
// The control of dashboardtree for connection
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using System.Threading;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.UI.Controls.Actions.UFE;
using System.Net;
using ProWrite.Core;
using System.Windows.Forms;
using System.Net.Tcp;
using System.ComponentModel;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class DashboardTree
    {
        private bool _IsDisconnection = false;
        void disConnectToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            _IsDisconnection = true;
            SignInfo sign = treeList.FocusedNode.Tag as SignInfo;

            Action successCallback = null;
            Action failCallback = null;
            var action = new LogoffAction(sign, successCallback, failCallback);
            action.Perform();
        }

        void ConnectToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            SignInfo sign = treeList.FocusedNode.Tag as SignInfo;
            bool isLiveSign = sign.DashboardType == ProWrite.Core.DashboardType.Sign;
            if (isLiveSign
                && sign.Controller.Connection.State != System.Communication.ConnectionState.Opened)
            {
                if (!CheckLiveInfo(sign))
                    EditDashboardItem(true);

                DoConnect(sign);
                return;
            }
        }

        /// <summary>
        /// Check live sign info is valide
        /// </summary>
        /// <param name="sign"></param>
        /// <returns></returns>
        private bool CheckLiveInfo(SignInfo sign)
        {
            return !string.IsNullOrEmpty(sign.LoginInfomation.IpAddress)
                && !string.IsNullOrEmpty(sign.LoginInfomation.ConnectionUserName)
                //&& !string.IsNullOrEmpty(sign.LoginInfomation.ConnectionPassword)
                && !string.IsNullOrEmpty(sign.LoginInfomation.Port.ToString());
        }

        /// <summary>
        /// Connect
        /// </summary>
        /// <param name="Current"></param>
        public void DoConnect(SignInfo Current)
        {
            if (string.IsNullOrEmpty(Current.LoginInfomation.UserName))
            {
                Current.LoginInfomation.UserName = "adm";
                Current.LoginInfomation.Password = "123";
            }
            Cursor = Cursors.WaitCursor;
            _currentSign = ControlService.SignCombo.Current;
            _IsDisconnection = false;

            LoginAction login = new LoginAction();
            login.Perform();
            Cursor = Cursors.Default;
        }

        /// <summary>
        /// Login
        /// </summary>
        /// <param name="sign"></param>
        /// <param name="password"></param>
        private void DoLogin(SignInfo sign, string password)
        {            
            if (password.Trim() == "")
                password = "1";

            sign.Controller.UserManager.Login(sign.LoginInfomation.UserName, password, p =>
            {
                if (p.IsSuccessed)
                {
                    int h = sign.Height;
                    int w = sign.Width;
                    sign.Height = 10000;
                    sign.Width = 10000;
                    LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                    LocalMessageBus.Send(this, new ActiveChange(sign, false));

                    sign.Height = h;
                    sign.Width = w;
                    PopulateTree();
                    treeList.FocusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                    var focusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                    if (focusedNode != null)
                    {
                        focusedNode.ImageIndex = _.SignConnectImageIndex;
                    }
                    ControlService.SignCombo.Current = sign;
                    ActionHelper.OnAfterLogin(sign.Controller.Connection.User);
                    if (focusedNode != null)
                    {

                        focusedNode.ImageIndex = _.SignConnectImageIndex;
                    }
                }
                else
                {
                    Action successCallback = null;
                    Action failCallback = null;
                    var action = new LogoffAction(sign, successCallback, failCallback, false);
                    action.Perform();
                    OnLoginFailed(p.Packet);
                }
            });
            Cursor = Cursors.Default;
        }

        protected void OnLoginFailed(UFEPacket resp)
        {
            Cursor = Cursors.Default;
            const string ftpError = "Auth fail";
            if (resp.ActionError.Message.Contains(ftpError))
            {
                MsgBox.Warning("SSH server auth fail. Disconnect the connection.");
            }
            else
            {
                MsgBox.Warning(resp.ActionError.Message + " Please try again.");
            }
        }


        void Connection_ConnectionClosed(object sender, EventArgs e)
        {
            SetSignImageIndex(sender);
            ActionHelper.OnDisconnected(true);
        }

        void Connection_ExceptionFired(object sender, EventArgs<Exception> e)
        {
            Cursor = Cursors.Default;
            if (FormHelper.ActiveForm != null)
                FormHelper.ActiveForm.Enabled = true;

            SetSignImageIndex(sender);

            ActionHelper.OnDisconnected(true);
            if (!_IsDisconnection)
            {
                var action = new ConnectionExceptionAction(e.First);
                action.Perform();
            }
            _IsDisconnection = false;
        }

        /// <summary>
        /// Set sign shape index of dashboard tree
        /// </summary>
        /// <param name="sender"></param>
        private void SetSignImageIndex(object sender)
        {
            IUFEConnection conn = sender as IUFEConnection;
            if (conn != null)
            {
                var sign = conn.Sign as SignInfo;
                if (sign != null)
                {
                    var focusedNode = treeList.FindNodeByFieldValue(_.Name, sign.Name);
                    if (focusedNode != null)
                        focusedNode.ImageIndex = DashboardTree._.SignImageIndex;
                    treeList.Focus();
                    treeList.Refresh();
                    treeList.Invalidate();
                }
            }
        }
    }
}
