using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using System.Net.Sockets;
using System.IO;
using ProWrite.UFE.Responses;
using System.Net;
using ProWrite.UI.Controls.Common.Messages;
using System.Text.RegularExpressions;
using DevExpress.XtraEditors;
using System.Net.Tcp;
using Org.Mentalis.Network.ProxySocket;
using System.Communication;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using System.Threading;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class ConnectTcpIpForm :ConnectionForm
    {

        bool isUseProxy = false;
        SignInfo sign = ControlService.SignCombo.Current;
        int timeCount=0;
        public ConnectTcpIpForm()
        {
            InitializeComponent();
            timer.Tick += new EventHandler(timer_Tick);
            ddlProxyType.Properties.Items.Clear();
            ddlProxyType.Properties.Items.AddRange(Enum.GetValues(typeof(ProxyTypes)));
            ddlProxyType.SelectedIndex = 0;
            SetProxyControlState(false);
            txtProxyUserName.TextChanged += new EventHandler(txtUserNameUser_TextChanged);
            LoginInfo loginInfo = sign.LoginInfomation;
            //this.Height = 360;
            this.Height = 170;


            txtUserNameLogin.Text = "adm";
            txtPasswordLogin.Text = "123";


            if (sign.Template.Sign.AutoLogin
                || sign.LoginInfomation.CanSaveLoginInfo)
            {
                txtUserNameLogin.Text = sign.LoginInfomation.UserName;
                txtPasswordLogin.Text = sign.LoginInfomation.Password;
                if (sign.Template.Sign.AutoLogin)
                    chkAutoLogin.Checked = true;
                chkStoreUserIfo.Checked = true;
                if (sign.Template.Sign.AutoLogin)//.LoginInfomation.AutoLogin)
                {
                    DoLogin(txtPasswordLogin.Text.Trim());
                }
            }
        }

        void timer_Tick(object sender, EventArgs e)
        {
            timeCount++;
            if (timeCount == 3)
            {
                timer.Stop();
            }
        }

        private void DoLogin(string password)
        {
            lblState.Text = "Is validating the user info......";
            btnLogin.Enabled = false;
            txtUserNameLogin.Enabled = false;
            txtPasswordLogin.Enabled = false;
            if (password.Trim() == "")
                password = "1";
            
            sign.Controller.UserManager.Login(txtUserNameLogin.Text.Trim(), password, p =>
            {
                if (p.IsSuccessed)
                {
                    LocalMessageBus.Send(sign, new LoginSuccessMessage());
                    ActionHelper.OnAfterLogin(sign.Controller.Connection.User);
                    
                    Close();
                }
                else
                {
                    OnLoginFailed(p.Packet);
                    lblState.Text = "";
                    btnLogin.Enabled = true;
                    txtUserNameLogin.Enabled = true;
                    txtPasswordLogin.Enabled = true;
                }
            });
        }

        void txtUserNameUser_TextChanged(object sender, EventArgs e)
        {
            if (txtProxyUserName.Text.Trim() != ""
                && txtProxyPortNumber.Text.Trim() != "")
                btnTestProxy.Enabled = true;
        }

        private void btnUseProxy_Click(object sender, EventArgs e)
        {
            if (!isUseProxy)
            {
                this.panProxy.Visible = true;
                this.Height = 513;
            }
            else
            {
                this.Height = 360;
                this.panProxy.Visible = false;
            }
            isUseProxy = !isUseProxy;
            //this.Location = System.Windows.Forms.FormStartPosition.CenterParent;
        }


        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;

            Close();
        }

        private void btnLoginCancel_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Default;
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Delete}    
                }));
            var getCurrentTask = AsyncFuture<UFEPacket>.Current;

            if (getCurrentTask != null
                && getCurrentTask.Packet != null
                && getCurrentTask.Packet.Command == Commands.Login)
            {
                getCurrentTask.Cancel(p =>
                    {
                        if (sign.Controller.Connection.User.Status == UserStatus.Online)
                            sign.Controller.UserManager.Logoff();
                        Close();
                    }, null);
            }
            
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (txtUserNameLogin.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the user name can't be empty");
                return;
            }

            lblState.Text = "Is validating the user info......";

            string password = txtPasswordLogin.Text;
            if (txtPasswordLogin.Text.Trim() == "")
            {
                password = "1";
                //MsgBox.Warning("Sorry,The password can't be empty");
                //return;
            }
            IsAutoLoginOrStore();

            DoLogin(password);
        }

        private void IsAutoLoginOrStore()
        {
            if (chkAutoLogin.Checked || this.chkStoreUserIfo.Checked)
            {
                if (chkAutoLogin.Checked)
                    sign.Template.Sign.AutoLogin = true;
                else
                    sign.Template.Sign.AutoLogin = false;
                sign.LoginInfomation.UserName = txtUserNameLogin.Text;
                sign.LoginInfomation.Password = txtPasswordLogin.Text;
                sign.LoginInfomation.CanSaveLoginInfo = true;
            }
            else
            {
                sign.LoginInfomation.CanSaveLoginInfo = false;
                sign.Template.Sign.AutoLogin = false;
            }
            DataGate.Update();
        }

        void btnTestProxy_Click(object sender, System.EventArgs e)
        {
            if (txtProxyIpAddress.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the IP address can't be empty");
                return;
            }
            if (this.txtProxyUserName.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the user name can't be empty");
                return;
            }
            if (this.txtProxyPortNumber.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the port number can't be empty");
                return;
            }

            using (var cursor = new WaitCursor())
            {
                using (ProxySocket socket = new ProxySocket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    IPEndPoint endPoint = new IPEndPoint(IPAddress.Parse(txtIpAddress.Text), Convert.ToInt32(txtPortNumber.Text));
                    IPEndPoint proxyEndPoint = new IPEndPoint(IPAddress.Parse(this.txtProxyIpAddress.Text), Convert.ToInt32(this.txtProxyPortNumber.Text));
                    ProxyTypes proxyType = (ProxyTypes)Enum.Parse(typeof(ProxyTypes), ddlProxyType.SelectedItem.ToString());
                    TcpConnectionParams Params = new TcpConnectionParams(endPoint, proxyEndPoint, proxyType, txtProxyUserName.Text, txtProxyPassword.Text);
                    socket.ProxyEndPoint = Params.ProxyEndPoint;
                    socket.ProxyType = Params.ProxyType;
                    socket.ProxyUser = Params.ProxyUser;
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
                        try
                        {
                            socket.Shutdown(SocketShutdown.Both);
                            socket.Close();
                        }
                        catch
                        {
                        }
                    }

                }
            }
        }

        private void ddlProxyType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ddlProxyType.SelectedIndex != 0)
            {
                SetProxyControlState(true);
                //btnTestProxy.Enabled = true;
            }
            else
            {
                SetProxyControlState(false);
                btnTestProxy.Enabled = false;
            }
        }


        void chkAutoLogin_CheckedChanged(object sender, System.EventArgs e)
        {
            IsAutoLoginOrStore();
        }

        void chkStoreUserIfo_CheckedChanged(object sender, System.EventArgs e)
        {
            IsAutoLoginOrStore();
        }


        private void SetProxyControlState(bool state)
        {
            txtProxyPassword.Enabled = state;
            txtProxyUserName.Enabled = state;
            txtProxyPortNumber.Enabled = state;
            txtProxyIpAddress.Enabled = state;
        }


        
        private void txtPortNumber_KeyPress(object sender, KeyPressEventArgs e)
        {
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v <= 59) || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void txtIpAddressUser_KeyPress(object sender, KeyPressEventArgs e)
        {
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v <= 59) || v == 46 || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

    }
}
