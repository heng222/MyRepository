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
using ProWrite.UI.Controls.Common;
using System.Net;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class ConnectWebCam : XtraForm
    {
        SignInfo sign;
        public ConnectWebCam(SignInfo item)
        {
            InitializeComponent();

            sign = item;
            if (!string.IsNullOrEmpty(sign.WebCamAddress))
            {
                txtAddress.Text = sign.WebCamAddress;
                if (!string.IsNullOrEmpty(sign.WebPortNum))
                    txtAddress.Text += ":" + sign.WebPortNum;
            }
            if (!string.IsNullOrEmpty(sign.WebCamUserName))
                txtUserName.Text = sign.WebCamUserName;
            if (!string.IsNullOrEmpty(sign.WebCamPwd))
                txtPwd.Text = sign.WebCamPwd;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtAddress.Text))
            {
                MsgBox.Warning("Ip address can't be empty");
                return;
            }

            if (string.IsNullOrEmpty(txtUserName.Text))
            {
                MsgBox.Warning("User name can't be empty");
                return;
            }

            if (string.IsNullOrEmpty(txtPwd.Text))
            {
                MsgBox.Warning("Password can't be empty");
                return;
            }

            IPAddress address = null;
            string ip =txtAddress.Text;
            string port = "";
            if (txtAddress.Text.Contains(":"))
            {
                ip = txtAddress.Text.Substring(0, ip.LastIndexOf(":"));
                int start =txtAddress.Text.LastIndexOf(":")+1;
                int length =txtAddress.Text.Length - start;
                port = txtAddress.Text.Substring(start,length);
            }
            string[] sIp = ip.Split('.');
            if (sIp.Length != 4 || !IPAddress.TryParse(ip, out address))
            {
                MsgBox.Warning("Sorry,the ip address is invalid");
                return;
            }

            sign.WebCamAddress = ip;
            sign.WebPortNum = port;
            sign.WebCamUserName = txtUserName.Text;
            sign.WebCamPwd = txtPwd.Text;
            Close();
        }

        private void txtAddress_KeyPress(object sender, KeyPressEventArgs e)
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
