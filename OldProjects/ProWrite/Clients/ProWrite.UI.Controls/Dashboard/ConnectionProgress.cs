//---------------------------------------------------------------------
//
// File: ConnectionProgress.cs
//
// Description:
// The control of Connection Progress
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using System.Communication;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using System.Net;
using ProWrite.Core;
using ProWrite.UFE;
using System.Net.Sockets;
using System.Net.Tcp;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Threading;
using System.Threading.Tasks;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Connection Progress
    /// </summary>
    public partial class ConnectionProgress : XtraForm
    {

        public bool Result
        { get; set; }
        private SignInfo Current;
        Task ftpOpenTask = null;
        private string IpAddress;
        private string PortNo;
        private string ServerName;
        private string Pwd;
        private bool _isUseProxy;
        private bool IsTreeList;


        public ConnectionProgress(SignInfo sign, bool isTreelist, string pwd)//,string ipAddress,string portNo,string serverName,string pwd,bool isUserProxy)
        {
            InitializeComponent();
            Current = sign;
            IsTreeList = isTreelist;
            Pwd = pwd;
            this.labelControl5.Visible = false;// Current.IsWebCam;
            picWebCam.Visible = false;// Current.IsWebCam;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = 200;
            timer.Start();
        }

        void timer_Tick(object sender, EventArgs e)
        {
            DoConnect();
            (sender as System.Windows.Forms.Timer).Stop();
        }

        /// <summary>
        /// Connect
        /// </summary>
        private void DoConnect()
        {
            Init();

            this.Cursor = Cursors.WaitCursor;
            if (IsTreeList)
                ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.WaitCursor;
            if (IsCancel)
            {
                if (connStatus != null)
                {
                    if (connStatus.Connection != null)
                        connStatus.Connection.Cancel();
                    else if (connStatus.Login != null)
                        connStatus.Login.Cancel();
                    connStatus = null;

                    ControlService.DashboardTree.DashboardTreeList.FocusedNode.ImageIndex = 1;
                    ActionHelper.OnDisconnected(true);

                    ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                }
                return;
            }

            ConnectionExceptionAction.IsCancel = false;
            IPEndPoint endPoint = null;
            IPEndPoint proxyEndPoint = null;

            endPoint = new IPEndPoint(IPAddress.Parse(Current.LoginInfomation.IpAddress), Current.LoginInfomation.Port);
            Current.Controller.Connection.FtpUser.Account = Current.LoginInfomation.ConnectionUserName;
            Current.Controller.Connection.FtpUser.NoSecurityPWD = Pwd;// Current.LoginInfomation.ConnectionPassword;

            TcpUFEConnection tcpConn = Current.Controller.Connection as TcpUFEConnection;
            if (tcpConn != null)
            {
                var connParams = new TcpConnectionParams(endPoint, proxyEndPoint, Current.LoginInfomation.ProxyType, Current.LoginInfomation.PorxyUserName, Current.LoginInfomation.PorxyPassword);
                tcpConn.Params = connParams;
            }
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(Current);
            ActionHelper.OnCancelConnect();
            DataGate.Log.Info("Start connect.");
            IFtpManager ftpMgr = Current.Controller.Connection.FtpManager;


            //Connect task
            ftpOpenTask = Task.Create(p =>
                {
                    try
                    {
                        //Connect ftp
                        Log.Info("Start connect ftp");
                        ftpMgr.Open();
                        if (ftpOpenTask.IsCanceled)
                        {
                            Log.Info("Cancel connect ftp");
                            return;
                        }
                        picCommunication.InvokeProperty("Image", Resources.Resource.GetImage(Resources.Resource.Images.Pass));
                        Log.Info("Connect ftp successful.");
                        ftpMgr.IsConnected = true;
                    }
                    catch (Exception ex)
                    {
                        DataGate.Log.Error("Connect ftp failed.");
                        if (!ftpOpenTask.IsCanceled)
                        {
                            this.InvokeMethod(delegate
                            {
                                picError.Visible = true;
                                lblError.Visible = true;
                                this.btnRetry.Enabled = true;
                                this.Cursor = Cursors.Default;
                                ftpMgr.IsConnected = false;
                                SocketException inner = ex.InnerException as SocketException;
                                if (inner != null && inner.SocketErrorCode == SocketError.TimedOut)
                                {
                                }
                                else
                                {
                                    this.lblError.Text = "Sorry,connection failed,please check your user name or password.";
                                }
                                ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                            });
                        }
                        return;
                    }

                    connStatus = new ConnectionEntity();
                    if (ftpOpenTask.IsCanceled)
                        return;
                    //Start connect
                    connStatus.Connection = Current.Controller.Connection.OpenAsync(p2 =>
                    {
                        ControlService.DashboardTree.Cursor = Cursors.Default;
                        if (ftpOpenTask.IsCanceled)
                            return;
                        if (p2.IsSuccessed)
                        {
                            DataGate.Log.Info("Connect successed.");
                            picNetWork.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                            Thread.Sleep(100);
                            picConnection.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                            Thread.Sleep(200);
                            if (ftpOpenTask.IsCanceled)
                                return;

                            //Start login
                            DoLogin(Current, Current.LoginInfomation.Password);
                        }
                        else
                        {
                            if (ftpOpenTask.IsCanceled)
                                return;
                            DataGate.Log.Error("Connect failed.");
                            picError.Visible = true;
                            lblError.Visible = true;
                            //picError.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
                            this.btnRetry.Enabled = true;
                            this.Cursor = Cursors.Default;
                            connStatus = null;
                            //_isCancelConnect = false;
                            if (!IsCancel)
                                new ConnectionExceptionAction(p2.Exception).Perform();
                            ActionHelper.OnDisconnected(true);
                            ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                        }
                    });
                });

        }

        /// <summary>
        /// Initialize UI
        /// </summary>
        private void Init()
        {
            this.lblError.Visible = false;
            this.picError.Visible = false;
            this.btnRetry.Enabled = false;
            this.lblMsg.Visible = false;
            picCommunication.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
            picConnection.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
            picNetWork.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
            picSuccess.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
        }

        /// <summary>
        /// Login
        /// </summary>
        /// <param name="sign"></param>
        /// <param name="password"></param>
        private void DoLogin(SignInfo sign, string password)
        {
            if (string.IsNullOrEmpty(password) || password.Trim() == "")
                password = "1";
            DataGate.Log.Info("Start logon.");
            connStatus.Login = sign.Controller.UserManager.Login("adm", "123", p =>
            {
                if (ftpOpenTask.IsCanceled)
                    return;
                if (p.IsSuccessed)
                {
                    DataGate.Log.Info("Logon successed.");

                    

                    this.picSuccess.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                    System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
                    timer.Tick += new EventHandler(timer_tick2);
                    timer.Interval = 200;
                    timer.Start();
                    Thread.Sleep(1000);
                    this.Result = true;
                    if (IsTreeList)
                    {
                        int h = sign.Height;
                        int w = sign.Width;
                        sign.Height = 10000;
                        sign.Width = 10000;
                        LocalMessageBus.Send(this, new DataChangedMessage(PWDataType.Dashboard));
                        LocalMessageBus.Send(this, new ActiveChange(sign, false));

                        sign.Height = h;
                        sign.Width = w;

                        ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                        ControlService.DashboardTree.PopulateTree();
                        ControlService.DashboardTree.DashboardTreeList.FocusedNode = ControlService.DashboardTree.DashboardTreeList.FindNodeByFieldValue("Name", sign.Name);
                        var focusedNode = ControlService.DashboardTree.DashboardTreeList.FindNodeByFieldValue("Name", sign.Name);
                        if (focusedNode != null)
                        {
                            focusedNode.ImageIndex = 2;
                        }
                        ControlService.SignCombo.Current = sign;
                        ActionHelper.OnAfterLogin(sign.Controller.Connection.User);

                    }

                    //Close();
                }
                else
                {
                    DataGate.Log.Error("Logon failed.");
                    Result = false;
                    picError.Visible = true;
                    lblError.Visible = true;
                    this.btnRetry.Enabled = true;
                    this.Cursor = Cursors.Default;

                    Action successCallback = null;
                    Action failCallback = null;
                    var action = new LogoffAction(sign, successCallback, failCallback, false);
                    action.Perform();
                    OnLoginFailed(p.Packet);
                }
                connStatus = null;
            });
            if (IsTreeList)
                ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
        }

        void timer_tick2(object sender, EventArgs e)
        {
            this.picSuccess.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
            (sender as System.Windows.Forms.Timer).Stop();
        }

        private void DoLogin(string password)
        {

            if (password.Trim() == "")
                password = "1";

            connStatus.Login = Current.Controller.UserManager.Login("adm", "123", p =>
            {
                if (p.IsSuccessed)
                {
                    Result = true;
                }
                else
                {
                    Result = false;
                }

                connStatus = null;
            });
        }

        /// <summary>
        /// Login failed
        /// </summary>
        /// <param name="resp"></param>
        protected void OnLoginFailed(UFEPacket resp)
        {
            //Cursor = Cursors.Default;
            Result = false;
            lblError.Visible = true;
            if (IsTreeList)
            {
                ControlService.DashboardTree.Cursor = Cursors.Default;
                ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
            }
            //CloseConnection();

            if (IsCancel)
                return;
            const string ftpError = "Auth fail";
            if (resp.ActionError.Message.Contains(ftpError))
            {

                lblError.Text = "SSH server auth fail. Disconnect the connection.";
                //MsgBox.Warning("SSH server auth fail. Disconnect the connection.");
            }
            else
            {
                string msg = " Please try again.";
                if (resp.ActionError.Message.Contains("logged"))
                    msg = " Please try again later.";
                lblError.Text = resp.ActionError.Message;
                lblMsg.Text = msg;
                lblMsg.Visible = true;

                //this.picError.Location = new System.Drawing.Point(12, 223);
                //this.lblError.Location = new System.Drawing.Point(50, 242);
            }

        }

        private void ConnectWebCam()
        {
            //PTZ cam = new PTZ();
            //cam.AmcPlay();
        }

        /// <summary>
        /// Connection status
        /// </summary>
        private ConnectionEntity connStatus;

        private class ConnectionEntity
        {
            public IAsyncFuture Connection;
            public IAsyncFuture Login;
        }

        public bool IsCancel { get; set; }

        private void btnRetry_Click(object sender, EventArgs e)
        {
            Init();
            System.Windows.Forms.Timer timer1 = new System.Windows.Forms.Timer();
            timer1.Tick += new EventHandler(timer1_Tick);
            timer1.Interval = 200;
            timer1.Start();

        }

        void timer1_Tick(object sender, EventArgs e)
        {
            DoConnect();
            (sender as System.Windows.Forms.Timer).Stop();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            try
            {
                Result = false;
                IsCancel = true;
                if (connStatus != null
                    && connStatus.Connection != null
                    && !connStatus.Connection.IsCompleted)
                    connStatus.Connection.Cancel();
                if (connStatus != null
                    && connStatus.Login != null
                    && !connStatus.Login.IsCompleted)
                {
                    connStatus.Login.Cancel();
                    if (Current.Controller.Connection.State == System.Communication.ConnectionState.Opening)
                    {
                        connStatus.Connection.Cancel();
                        //var closeTask = Current.Controller.Connection.Close();
                        //if (!closeTask.IsCompleted)
                        //    closeTask.Wait();
                    }
                }

                CancelConnect();

                ftpOpenTask.Cancel();
            }
            catch { }

            Close();
        }

        protected override void OnClosed(EventArgs e)
        {
            Cursor = Cursors.Default;
            ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
            try
            {
                if (connStatus != null)
                {
                    if (connStatus.Connection != null)
                        connStatus.Connection.Cancel();
                    else if (connStatus.Login != null)
                        connStatus.Login.Cancel();
                    connStatus = null;
                }

                if (ftpOpenTask != null)
                {
                    if (!ftpOpenTask.IsCompleted && !ftpOpenTask.IsCanceled)
                    {
                        ftpOpenTask.Cancel();
                        Result = false;
                    }
                    if (ftpOpenTask.IsCanceled)
                        CancelConnect();
                    //ftpOpenTask.Dispose();
                }
            }
            catch { }
        }

        private void CancelConnect()
        {
            Action successCallback = null;
            Action failCallback = null;
            var action = new LogoffAction(Current, successCallback, failCallback, false);
            action.Perform();
        }

        private void picSuccess_ImageChanged(object sender, EventArgs e)
        {
            if (Result)
                Close();

        }

        void picWebCam_ImageChanged(object sender, System.EventArgs e)
        {
            Thread.Sleep(200);
            Close();
        }
    }
}
