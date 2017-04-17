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

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class SSHLogin : XtraForm
    {
        private SignInfo _sign;
        public SSHLogin(SignInfo sign)
        {
            _sign = sign;
            InitializeComponent();
            if (string.IsNullOrEmpty(sign.LoginInfomation.ConnectionUserName))
            {
                if (sign.LoginInfomation.ConnectionUserName == null)
                    sign.LoginInfomation = new LoginInfo();
                sign.LoginInfomation.ConnectionUserName = "root";
                sign.LoginInfomation.ConnectionPassword = "123456";
            }
            txtAcount.Text = sign.LoginInfomation.ConnectionUserName;
            txtPwd.Text = sign.LoginInfomation.ConnectionPassword;

        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            if (txtAcount.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the SSH Acount can't be empty.");
                return;
            }
            //if (txtPwd.Text.Trim() == "")
            //{
            //    MsgBox.Warning("Sorry,the password can't be empty.");
            //    return;
            //}

            _sign.LoginInfomation.ConnectionUserName = this.txtAcount.Text.Trim();
            _sign.LoginInfomation.ConnectionPassword = this.txtPwd.Text.Trim();
            MsgBox.Warning("Set SSH Account successed.");
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}
