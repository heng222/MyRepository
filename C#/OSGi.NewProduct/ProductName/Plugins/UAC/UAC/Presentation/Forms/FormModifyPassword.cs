﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Products.UAC.Properties;
using Products.UAC.Domain;

namespace Products.UAC.Presentation.Forms
{
    partial class FormModifyPassword : Form
    {
        private IUserManagement _userManager;
        private string _oldUserName;

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
            }
            catch (System.Exception ex)
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