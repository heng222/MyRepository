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

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class SignFormNew : XtraForm
    {
        public bool Result
        { get; set; }
        private SignInfo Current;

        private bool IsTreeList;
        public SignFormNew(SignInfo sign, bool isTreelist)//,string ipAddress,string portNo,string serverName,string pwd,bool isUserProxy)
        {
            InitializeComponent();
            Current = sign;
            IsTreeList = isTreelist;
            //this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
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
        private void DoConnect()
        {
            this.lblError.Visible = false;
            this.picError.Visible = false;
            this.btnRetry.Enabled = false;
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

            //SignInfo Current = ControlService.SignCombo.Current;

            ConnectionExceptionAction.IsCancel = false;
            IPEndPoint endPoint = null;
            IPEndPoint proxyEndPoint = null;

            endPoint = new IPEndPoint(IPAddress.Parse(Current.LoginInfomation.IpAddress), Current.LoginInfomation.Port);
            Current.Controller.Connection.FtpUser.Account = Current.LoginInfomation.ConnectionUserName;
            Current.Controller.Connection.FtpUser.NoSecurityPWD = Current.LoginInfomation.ConnectionPassword;

            TcpUFEConnection tcpConn = Current.Controller.Connection as TcpUFEConnection;
            if (tcpConn != null)
            {
                var connParams = new TcpConnectionParams(endPoint, proxyEndPoint, Current.LoginInfomation.ProxyType, Current.LoginInfomation.PorxyUserName, Current.LoginInfomation.PorxyPassword);
                tcpConn.Params = connParams;
            }
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(Current);
            ActionHelper.OnCancelConnect();

            IFtpManager ftpMgr = Current.Controller.Connection.FtpManager;
            try
            {
                ftpMgr.Open();
                picCommunication.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                Thread.Sleep(200);
                ftpMgr.IsConnected = true;
            }

            catch (Exception ex)
            {
                picError.Visible = true;
                lblError.Visible = true;
                this.btnRetry.Enabled = true;
                this.Cursor = Cursors.Default;
                //picError.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
                ftpMgr.IsConnected = false;
                SocketException inner = ex.InnerException as SocketException;
                if (inner != null && inner.SocketErrorCode == SocketError.TimedOut)
                {
                    //MsgBox.Warning("Unable to connect ¨C connection timed out after multiple attempts");
                }
                else
                {
                    //MsgBox.Warning("Sorry,connection failed,please check your user name or password.");
                }
                ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                return;
            }

            connStatus = new ConnectionEntity();

            connStatus.Connection = Current.Controller.Connection.OpenAsync(p =>
            {
                ControlService.DashboardTree.Cursor = Cursors.Default;
                if (p.IsSuccessed)
                {
                    picNetWork.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                    Thread.Sleep(100);
                    picConnection.Image = Resources.Resource.GetImage(Resources.Resource.Images.Pass);
                    Thread.Sleep(200);
                    DoLogin(Current, Current.LoginInfomation.Password);
                }
                else
                {
                    picError.Visible = true;
                    lblError.Visible = true;
                    //picError.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);
                    this.btnRetry.Enabled = true;
                    this.Cursor = Cursors.Default;
                    connStatus = null;
                    //_isCancelConnect = false;
                    if (!IsCancel)
                        new ConnectionExceptionAction(p.Exception).Perform();
                    ActionHelper.OnDisconnected(true);
                    ControlService.DashboardTree.DashboardTreeList.Cursor = Cursors.Default;
                }
            });

        }
        private void DoLogin(SignInfo sign, string password)
        {
            //lblState.Text = "Is validating the user info......";
            //btnSave.Enabled = false;
            //txtServerName.Enabled = false;
            //txtConnectPWD.Enabled = false;
            if (string.IsNullOrEmpty(password) || password.Trim() == "")
                password = "1";

            connStatus.Login = sign.Controller.UserManager.Login("adm", "123", p =>
            {


                if (p.IsSuccessed)
                {
                    //sign.LoginInfomation.UserName = sign.LoginInfomation.UserName;
                    //sign.LoginInfomation.Password = password;
                    //UpdateSignInfo();
                    
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
                    Result = false;
                    picError.Visible = true;
                    lblError.Visible = true;
                    this.btnRetry.Enabled = true;
                    this.Cursor = Cursors.Default;
                    //picError.Image = Resources.Resource.GetImage(Resources.Resource.Images.Baffle);

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
                lblError.Text = resp.ActionError.Message + msg;

                //MsgBox.Warning(resp.ActionError.Message + msg);
            }

        }
        private ConnectionEntity connStatus;
        private class ConnectionEntity
        {
            public IAsyncFuture Connection;
            public IAsyncFuture Login;
        }
        public bool IsCancel { get; set; }
        private void btnRetry_Click(object sender, EventArgs e)
        {
            DoConnect();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Result = false;
            Close();
        }

        protected override void OnClosed(EventArgs e)
        {
            if (connStatus != null)
            {
                if (connStatus.Connection != null)
                    connStatus.Connection.Cancel();
                else if (connStatus.Login != null)
                    connStatus.Login.Cancel();
                connStatus = null;
            }
        }

        private void picSuccess_ImageChanged(object sender, EventArgs e)
        {
            if (Result)
            {
                Thread.Sleep(200);
                Close();
            }
        }
    }
}
