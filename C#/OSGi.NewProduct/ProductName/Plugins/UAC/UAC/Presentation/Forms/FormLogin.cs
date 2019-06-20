﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;
using Products.Infrastructure;
using Products.Resource;
using Products.UAC.Domain;
using Products.UAC.Utilities;

namespace Products.UAC.Presentation.Forms
{
    partial class FormLogin : Form, IUserLogOn
    {
        #region "Filed"
        public ILoginVerification Verification { get; private set; }
        #endregion

        /// <summary>
        /// 构造函数
        /// </summary>
        public FormLogin(ILoginVerification verify)
        {
            if (verify == null) throw new ArgumentException("登录验证接口不能为空引用。");

            this.Verification = verify;

            InitializeComponent();

            this.Initialize();
        }

        private void Initialize()
        {
            this.txtUserName.Focus();
            this.Icon = ProductResources.ApplicationIcon;
            this.picLogo.Image = ProductResources.CompanyLogoImage;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                var actualPwd = HelperTool.BuildMd5(txtPassword.Text);
                this.Verification.LogOn(txtUserName.Text, actualPwd);

                this.Close();

                this.DialogResult = DialogResult.OK;
            }
            catch (System.Exception ex)
            {
                this.DialogResult = DialogResult.No;
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        #region IUserLogOn 成员

        public UserLogOnResult ShowLogOnDialog()
        {
            var rc = this.ShowDialog();

            if (rc == DialogResult.OK)
            {
                return UserLogOnResult.Successful;
            }
            else if (rc == DialogResult.Cancel)
            {
                return UserLogOnResult.Canceled;
            }
            else 
            {
                return UserLogOnResult.Failure;
            }
        }

        #endregion
    }
}
