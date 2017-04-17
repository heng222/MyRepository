//---------------------------------------------------------------------
//
// File: UserDetailForm.cs
//
// Description:
// The control of UserDetailForm
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
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls.Common;
using ProWrite.UFE.Entity;
using ProWrite.UFE;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// The control of UserDetailForm
    /// Add/Edit user info
    /// </summary>
    public partial class UserDetailForm : XtraForm
    {
        bool _isEdit = false;
        User current;
        User currentSignUser;
        SignInfo sign = ControlService.SignCombo.Current;
        public bool IsRefresh;
        public UserDetailForm(User user)
        {
            InitializeComponent();
            currentSignUser = sign.Controller.Connection.User;
            if (currentSignUser.Role < Role.Administrator)
            {
                rdgRole.Enabled = false;
            }
            if (user != null)
            {
                current = user;
                _isEdit = true;
                txtName.Text = current.Account;
                txtName.Enabled = false;
                btnSave.Visible = false;
                //txtPWD.Text = current.Password;
                rdgRole.EditValue = current.Role.ToString();
                //for (int i = 0; i < rdgRole.Properties.Items.Count; i++)
                //{
                //    if (rdgRole.Properties.Items[i].Value.ToString() == current.Role.ToString())
                //        rdgRole.SelectedIndex = i;
                //}
            }
            else
            {
                current = new User();
                _isEdit = false;
            }
            if (currentSignUser.Role < Role.Administrator)
            {
                rdgRole.Enabled = false;
                btnSave.Visible = false;
            }
            else
                btnSave.Visible = true;
            //rdgRole.Properties.Items.AddRange(Enum.GetValues(typeof(Role)));
        }

        private void Save()
        {
            string rdgSeleteText = rdgRole.EditValue.ToString();//.Properties.Items[rdgRole.SelectedIndex].ToString();
            Role role =  (Role)Enum.Parse(typeof(Role), rdgSeleteText);

            if (_isEdit)
            {
                sign.Controller.UserManager.UpdateUserRole(current.Id, role, p =>
                    {
                        IsRefresh = p.IsSuccessed;
                        if (!IsRefresh)
                            MessageBox.Show(p.Packet.ActionError.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        //MsgBox.Warning("Sorry,update user failed,please try again");
                    });
            }
            else
            {
                sign.Controller.UserManager.CreateUser(txtName.Text.Trim(), "1", role, p =>
                    {
                        IsRefresh = p.IsSuccessed;
                        if (!IsRefresh)
                            MessageBox.Show(p.Packet.ActionError.Message,"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);//"Sorry,create user failed,please try again.");
                    });
            }
            this.Close();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (txtName.Text.Trim() == "")
            {
                MsgBox.Warning("Sorry,the name can't be empty");
                return;
            }
            //if (txtPWD.Text.Trim() == "")
            //{
            //    MsgBox.Warning("Sorry,the password can't be empty");
            //    return;
            //}
            //if (this.txtRePWD.Text.Trim() == "")
            //{
            //    MsgBox.Warning("Sorry,the repeat password can't be empty");
            //    return;
            //}
            //if (txtPWD.Text != txtRePWD.Text)
            //{
            //    MsgBox.Warning("Sorry,the repeat password and the password are disaffinity");
            //    return;
            //}
            Save();
        }

        void btnCancel_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }
    }
}
