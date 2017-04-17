//---------------------------------------------------------------------
//
// File: UserChangePassword.cs
//
// Description:
// The control of UserChangePassword
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
using ProWrite.UFE.Entity;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// The control of UserChangePassword
    /// </summary>
    public partial class UserChangePassword : XtraForm
    {
        public bool IsRefresh;
        User current;
        SignInfo sign = ControlService.SignCombo.Current;
        public UserChangePassword(User user)
        {
            InitializeComponent();
            current = user;
        }

        void btnCancel_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        void btnSave_Click(object sender, System.EventArgs e)
        {
            if (txtPWD.Text != this.txtRePWD.Text)
            {
                MsgBox.Warning("Sorry,the password you entered is inconsistent.");
                return;
            }
            string pwd = txtPWD.Text;
            if (string.IsNullOrEmpty(pwd))
                pwd = "1";
            sign.Controller.UserManager.ChangePassword(current.Id, pwd, p =>
            {
                IsRefresh = p.IsSuccessed;
                if (IsRefresh)
                    Close();
                else
                    MsgBox.Warning("Sorry,set password failed,please try again.");
            });
        }
    }
}
