//---------------------------------------------------------------------
//
// File: SignForm.cs
//
// Description:
// The control of Add/Edit sign for connection
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
using System.Text.RegularExpressions;
using System.Net;
using ProWrite.Entity.Dashboard;
using Org.Mentalis.Network.ProxySocket;
using ProWrite.UFE;
using System.Net.Tcp;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using Point = System.Drawing.Point;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using System.Net.Sockets;
using ProWrite.Resources;
using ProWrite.UI.Controls.Actions;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Actions.UFE;
using System.Communication;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Sign form for connection
    /// </summary>
    public partial class SignForm// : DashboardForm<SignInfo>
    {
        /// <summary>
        /// Check LiveSign info if valide
        /// </summary>
        /// <returns></returns>
        private bool CheckLiveInfo()
        {
            if (txtConnectIpAddress.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the IP address can't be empty");
                return false;
            }
            if (this.txtServerName.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the user name can't be empty");
                return false;
            }
            if (this.txtConnectPortNo.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the port number can't be empty");
                return false;
            }
            Regex re = new Regex(@"^0|[0-9]*[1-9][0-9]*$");

            if (!re.IsMatch(txtConnectPortNo.Text))
            {
                MsgBox.Warning("Sorry,the port number is invalid");
                return false;
            }
            //if (txtConnectPWD.Text.Trim() == "")
            //{
            //    MsgBox.Warning("Sorry,the connection password can't be empty");
            //    return false;
            //}

            IPAddress address = null;
            string[] sIp = txtConnectIpAddress.Text.Split('.');
            if (sIp.Length != 4 || !IPAddress.TryParse(txtConnectIpAddress.Text.Trim(), out address))
            {
                MsgBox.Warning("Sorry,the ip address is invalid");
                return false;
            }

            int port = int.Parse(txtConnectPortNo.Text);
            if (port < IPEndPoint.MinPort || port > IPEndPoint.MaxPort)
            {
                MsgBox.Warning("Sorry,the port number is invalid");
                return false;
            }

            if (!NetHelper.InternetConnectedState)
            {
                MsgBox.Warning("Sorry,the network is offline");
                return false;
            }
            return true;
        }

        /// <summary>
        /// Connect
        /// </summary>
        private void DoConnect()
        {
            if (connStatus != null)
                return;
            if (isUseProxy && ddlProxyType.SelectedIndex != 0)
            {
                if (txtProxyIpAdd.Text.Trim() == "")
                {
                    MsgBox.Warning("Sorry,the proxy IP address can't be empty");
                    return;
                }
                if (this.txtProxyPortNo.Text.Trim() == "")
                {
                    MsgBox.Warning("Sorry,the proxy port number can't be empty");
                    return;
                }
            }
            Cursor = Cursors.WaitCursor;
            ConnectionExceptionAction.IsCancel = false;
            
            IsDisconnection = false;
            DashboardTree._currentSign = Current;
            IPEndPoint endPoint = null;
            IPEndPoint proxyEndPoint = null;
            LoginInfo info = new LoginInfo();
            if (Current.Template.Sign.AutoLogin
                || Current.LoginInfomation.CanSave
                || Current.LoginInfomation.CanSaveLoginInfo)
                info = CloneManager.Clone<LoginInfo>(Current.LoginInfomation);
            if (chkStorePWD.Checked)
                info.CanSave = true;
            else
                info.CanSave = false;
            info.IpAddress = txtConnectIpAddress.Text.Trim();
            info.Port = Convert.ToInt32(txtConnectPortNo.Text);

            info.ConnectionUserName = txtServerName.Text.Trim();
            info.ConnectionPassword = txtConnectPWD.Text.Trim();
            Current.LoginInfomation.ConnectionUserName = txtServerName.Text.Trim();
            Current.LoginInfomation.ConnectionPassword = txtConnectPWD.Text.Trim();


            endPoint = new IPEndPoint(IPAddress.Parse(info.IpAddress), info.Port);

            if (isUseProxy && ddlProxyType.SelectedIndex != 0)
            {
                info.PorxyUserName = txtProxyUserName.Text;
                info.ProxyPort = Convert.ToInt32(txtProxyPortNo.Text);
                info.PorxyAddress = txtProxyIpAdd.Text;
                info.ProxyType = (ProxyTypes)Enum.Parse(typeof(ProxyTypes), ddlProxyType.SelectedItem.ToString());

                info.PorxyPassword = txtProxyPWD.Text;

                proxyEndPoint = new IPEndPoint(IPAddress.Parse(this.txtProxyIpAdd.Text), Convert.ToInt32(this.txtProxyPortNo.Text));
            }
            else
                info.ProxyType = ProxyTypes.None;

            Current.LoginInfomation = info;

            Current.Controller.Connection.FtpUser.Account = info.ConnectionUserName;
            Current.Controller.Connection.FtpUser.NoSecurityPWD = info.ConnectionPassword;

            TcpUFEConnection tcpConn = Current.Controller.Connection as TcpUFEConnection;
            if (tcpConn != null)
            {
                var connParams = new TcpConnectionParams(endPoint, proxyEndPoint, info.ProxyType, info.PorxyUserName, info.PorxyPassword);
                tcpConn.Params = connParams;
            }
            ProWrite.UI.Controls.Actions.UFE.Responses.UFEResponseService.Init(Current);
            this.Hide();

            ConnectionProgress progress = new ConnectionProgress(Current, false, info.ConnectionPassword);
            progress.ShowModalDialog();
            if (!chkStorePWD.Checked)
            {
                Current.LoginInfomation.ConnectionPassword = "";
            }
            if (progress.Result)
            {
                LiveImageAction liveImageAction = new LiveImageAction();
                liveImageAction.Sign = Current;
                liveImageAction.Perform();

                StatusAction statusAction = new StatusAction(false);
                statusAction.Sign = Current;
                statusAction.Perform();

                GetStatusAction getStatus = new GetStatusAction();
                getStatus.sign = Current;
                getStatus.Perform();

                LogViewAction logviewAction = new LogViewAction();
                logviewAction.sign = Current;
                logviewAction.Perform();
                if (Current.IsWebCam)
                    IsConnectWebCam = true;

                UpdateSignInfo();
            }
            else
            {
                ActionHelper.OnDisconnected(false);
                this.Show();
                this.Cursor = Cursors.Default;
            }            
        }

        /// <summary>
        /// Login
        /// </summary>
        /// <param name="password"></param>
        private void DoLogin(string password)
        {
            //lblState.Text = "Is validating the user info......";
            btnSave.Enabled = false;
            txtServerName.Enabled = false;
            txtConnectPWD.Enabled = false;
            if (password.Trim() == "")
                password = "1";

            connStatus.Login = Current.Controller.UserManager.Login("adm", "123", p =>
            {
                if (p.IsSuccessed)
                    UpdateSignInfo();
                else
                {
                    OnLoginFailed(p.Packet);
                    btnSave.Enabled = true;
                    txtServerName.Enabled = true;
                    txtConnectPWD.Enabled = true;
                }

                connStatus = null;
            });
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

        protected override void OnCancel()
        {
            Current.Name = signOld.Name1;
            Current.Parent = signOld.Parent;
            Current.Width = signOld.Width;
            Current.Height = signOld.Height;
            Current.SignInfomation = signOld.SignInfomation;
            if (Current.DashboardType != DashboardType.Sign)
                Current.SignInfomation = Current.Height.ToString() + " x " + Current.Width.ToString();
                //Current.SignInfomation = Current.Name + "  :  " + Current.Height.ToString() + " x " + Current.Width.ToString() + "  :  " + Current.Type.ToString();
            Current.Template.Sign.Height = signOld.Height;
            Current.Template.Sign.Width = signOld.Width;
            IsRefresh = true;
            DataGate.Update();
            
            if (connStatus != null)
            {
                if (connStatus.Connection != null)
                    connStatus.Connection.Cancel();
                else if (connStatus.Login != null)
                    connStatus.Login.Cancel();
                connStatus = null;
            }
        }

        /// <summary>
        /// Login failed
        /// </summary>
        /// <param name="resp"></param>
        protected void OnLoginFailed(UFEPacket resp)
        {
            Cursor = Cursors.Default;
            //CloseConnection();
            Action successCallback = null;
            Action failCallback = null;
            var action = new LogoffAction(Current, successCallback, failCallback, false);
            action.Perform();

            const string ftpError = "Auth fail";
            if (resp.ActionError.Message.Contains(ftpError))
            {
                MsgBox.Warning("SSH server auth fail. Disconnect the connection.");
                Close();
            }
            else
            {
                string msg = " Please try again.";
                if (resp.ActionError.Message.Contains("logged"))
                    msg = " Please try again later.";
                MsgBox.Warning(resp.ActionError.Message + msg);
            }
        }

        /// <summary>
        /// Disconnect
        /// </summary>
        private void DoDisconnect()
        {
            IsDisconnection = true;
            Action successCallback = delegate { isSaveClose = true; Close(); };
            Action failCallback = delegate { isSaveClose = true; Close(); };

            var action = new LogoffAction(Current, successCallback, failCallback);
            action.Perform();
            this.btnSave.Enabled = true;
        }

        /// <summary>
        /// Update sign info when Connect success
        /// </summary>
        void UpdateSignInfo()
        {
            //判断是否添加新项成功
            if (!_IsEdit)
            {

                if (!_Parent.AddSign(Current))
                {
                    Action successCallback = null;
                    Action failCallback = null;
                    var action = new LogoffAction(Current, successCallback, failCallback, false);
                    action.Perform();

                    btnSave.Enabled = true;
                    txtServerName.Enabled = true;
                    txtConnectPWD.Enabled = true;

                    MsgBox.Warning(Resource.GetString(Resource.Strings.DashBoard_SaveSignRepeat));
                    return;
                }
            }

            if (this.ddlSignParent.Text == SelectText)
                Current.Parent = DataGate.Project.RootGroup;
            else
            {

                Current.Parent = ddlSignParent.SelectedItem as SignGroupInfo;
            }
            //判断是否需要上传图片
            if (btSignImage.Text.Length > 0)
            {
                //DataGate.Upload(btSignImage.Text);
                UpLoad();
                Current.Image = Current.Template.Sign.Image = strImageFullName;
            }
            Current.IsWebCam = rdbWebCam.Checked;

            DataGate.Update();
            this.IsRefresh = true;
            LocalMessageBus.Send(Current, new LoginSuccessMessage());
            //ActionHelper.OnAfterLogin(Current.Controller.Connection.User);

            //Close();
            isSaveClose = true;

            this.Close();
        }

        private void btnUseProxy_Click(object sender, EventArgs e)
        {
            ddlProxyType.SelectedIndex = 0;
            if (!isUseProxy)
            {
                this.panProxy.Visible = true;
                grConncet.Height = 269;
                this.Height = ClientHeight("3");
                btnSignDetail.Location = new Point(9, BtnSaveHeight(true));
                this.btnSave.Location = new Point(176, BtnSaveHeight(true));
                this.btnCancel.Location = new Point(249, BtnSaveHeight(true));
                if (isLiveSign)
                {
                    if (isConnect)
                    {
                        this.btnSave.Location = new System.Drawing.Point(156, BtnSaveHeight(true));
                        btnSave.Width = 87;

                    }
                    else
                    {
                        this.btnSave.Location = new System.Drawing.Point(166, BtnSaveHeight(true));
                        btnSave.Width = 77;
                    }
                }
            }
            else
            {
                grConncet.Height = 143;
                this.Height = ClientHeight("1");
                this.panProxy.Visible = false;
                btnSignDetail.Location = new Point(9, BtnSaveHeight(false));
                this.btnSave.Location = new Point(176, BtnSaveHeight(false));
                this.btnCancel.Location = new Point(249, BtnSaveHeight(false));
                if (isLiveSign)
                {
                    if (isConnect)
                    {
                        this.btnSave.Location = new System.Drawing.Point(156, BtnSaveHeight(false));
                        btnSave.Width = 87;

                    }
                    else
                    {
                        this.btnSave.Location = new System.Drawing.Point(166, BtnSaveHeight(false));
                        btnSave.Width = 77;
                    }
                }
            }
            isUseProxy = !isUseProxy;

        }

        private void btnTestProxy_Click(object sender, EventArgs e)
        {
            if (txtProxyIpAdd.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the proxy IP address can't be empty");
                return;
            }

            IPAddress address = null;
            if (!IPAddress.TryParse(txtProxyIpAdd.Text, out address))
            {
                MsgBox.Warning("Sorry,the ip address is invalid");
                return;
            }
            if (this.txtProxyPortNo.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the proxy port number can't be empty");
                return;
            }

            using (var cursor = new WaitCursor())
            {
                using (ProxySocket socket = new ProxySocket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(txtConnectIpAddress.Text), Convert.ToInt32(txtConnectPortNo.Text));
                    IPEndPoint proxyEndPoint = new IPEndPoint(IPAddress.Parse(this.txtProxyIpAdd.Text), Convert.ToInt32(this.txtProxyPortNo.Text));
                    ProxyTypes proxyType = (ProxyTypes)Enum.Parse(typeof(ProxyTypes), ddlProxyType.SelectedItem.ToString());
                    TcpConnectionParams Params = new TcpConnectionParams(endPoint, proxyEndPoint, proxyType, txtProxyUserName.Text, txtProxyPWD.Text);
                    socket.ProxyEndPoint = Params.ProxyEndPoint;
                    socket.ProxyType = Params.ProxyType;
                    if (!string.IsNullOrEmpty(Params.ProxyUser))
                        socket.ProxyUser = Params.ProxyUser;
                    if (!string.IsNullOrEmpty(Params.ProxyPassword))
                        socket.ProxyPass = Params.ProxyPassword;

                    try
                    {
                        socket.Connect(Params.EndPoint);
                        MsgBox.Warning("Test successful");
                    }
                    catch
                    {
                        MsgBox.Warning("Sorry,test failed,please try again");
                    }
                    finally
                    {

                        if (socket.Connected)
                        {
                            try
                            {
                                socket.Shutdown(SocketShutdown.Both);
                                socket.Close();
                            }
                            catch
                            { }
                        }
                    }

                }
            }
        }

        private void rdbLiveSign_CheckedChanged(object sender, EventArgs e)
        {
            if (_isAddToGroup)
                return;
            isLiveSign = rdbLiveSign.Checked;
            grConncet.Visible = rdbLiveSign.Checked;
            grSign.Visible = !rdbLiveSign.Checked;
            if (isLiveSign)
            {
                btnSave.Text = "Connect";
                this.btnSave.Location = new System.Drawing.Point(166, BtnSaveHeight(false));
                btnSave.Width = 77;
            }
            if (isUseProxy)
            {
                grConncet.Height = 269;
                this.Height = ClientHeight("3");
                btnSignDetail.Location = new Point(9, BtnSaveHeight(true));
                this.btnSave.Location = new Point(176, BtnSaveHeight(true));
                this.btnCancel.Location = new Point(249, BtnSaveHeight(true));
                if (isLiveSign)
                {
                    this.btnSave.Location = new System.Drawing.Point(166, BtnSaveHeight(true));
                    btnSave.Width = 77;
                }
            }
        }

        void rdbModem_CheckedChanged(object sender, System.EventArgs e)
        {
            if (rdbModem.Checked)
            {
                ConnectModemForm modem = new ConnectModemForm();
                modem.ShowModalDialog();
            }
        }


        void rdbSerial_CheckedChanged(object sender, System.EventArgs e)
        {
            if (rdbSerial.Checked)
            {
                ConnectRS232Form rs = new ConnectRS232Form();
                rs.ShowModalDialog();
            }
        }
    }

    /*
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class PTZ
    {
        private AxAXISMEDIACONTROLLib.AxAxisMediaControl AMC;


        public PTZ()
        {
            this.AMC = new AxAXISMEDIACONTROLLib.AxAxisMediaControl();
            this.AMC.Name = "AMC";
        }

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void Initialize()
        {
            //// 
            //// AMC
            //// 
            //this.AMC.Enabled = true;
            //this.AMC.Location = new System.Drawing.Point(8, 8);
            //this.AMC.Name = "AMC";
            //this.AMC.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("AMC.OcxState")));
            //this.AMC.Size = new System.Drawing.Size(552, 424);
            //this.AMC.TabIndex = 0;            
        }

        public void AmcPlay()
        {
            try
            {
                //Stops possible streams
                AMC.Stop();

                // Set the PTZ properties
                AMC.PTZControlURL = "http://10.10.65.72/axis-cgi/com/ptz.cgi";
                AMC.UIMode = "ptz-absolute";

                // Show the status bar and the tool bar in the AXIS Media Control
                AMC.ShowStatusBar = true;
                AMC.ShowToolbar = true;
                AMC.StretchToFit = true;
                AMC.EnableContextMenu = true;
                AMC.ToolbarConfiguration = "default,+ptz";

                // Set the media URL and the media type
                AMC.MediaURL = "http://10.10.65.72/axis-cgi/mjpg/video.cgi";
                AMC.MediaType = "mjpeg";

                // Start the download of the mjpeg stream from the Axis camera/video server
                AMC.Play();

            }
            catch (ArgumentException ArgEx)
            {
                MessageBox.Show(ArgEx.Message, "Error");
            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.Message, "Error");
            }
        }
    }*/
}
