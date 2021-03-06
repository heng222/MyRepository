﻿using System;
using System.Windows.Forms;

using Products.UAC.Domain;
using Products.UAC.Properties;

namespace Products.UAC.Presentation.Forms
{
    partial class FormModifyPassword : Form
    {
        private readonly IUserManagement _userManager;
        private readonly string _oldUserName;

        public FormModifyPassword(string oldUserName, IUserManagement userMgr)
        {
            _userManager = userMgr;
            _oldUserName = oldUserName;

            InitializeComponent();

            this.Text = string.Format("修改 {0} 密码", oldUserName);
            this.Icon = Resources.Password;
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            try
            {
                _userManager.ModifyPassword(_oldUserName, txtOldPwd.Text, txtNewPwd.Text);

                MessageBox.Show("修改成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);

                this.Close();
                this.DialogResult = DialogResult.OK;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnCancle_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
