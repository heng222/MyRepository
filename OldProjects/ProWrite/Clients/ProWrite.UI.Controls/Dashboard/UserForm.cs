//---------------------------------------------------------------------
//
// File: UserForm.cs
//
// Description:
// The control of User list Form
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
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.UFE.Entity;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using DevExpress.XtraEditors;
using ProWrite.UFE;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// The control of User list Form
    /// </summary>
    public partial class UserForm : XtraForm
    {
        User user = new User();
        SignInfo sign = ControlService.SignCombo.Current;
        User currentUser;
        public UserForm()
        {
            InitializeComponent();
            if (sign != null)
            {
                //bool isGetUserList = true;
                currentUser = sign.Controller.Connection.User;
                gridControl1.DataSource = null;

                sign.Controller.UserManager.DeleteUserSuccessed += new ReceivedHandler(OnUserChanged);
                sign.Controller.UserManager.CreateUserSuccessed += new ReceivedHandler(OnUserChanged);
                sign.Controller.UserManager.UpdateUserRoleSuccessed += new ReceivedHandler(OnUserChanged);

                
                InitGrid();

              
                if (currentUser != null)
                {
                    if (currentUser.Role >= Role.Administrator||currentUser.Role == Role.Default)
                    {

                    }
                    else //if (currentUser.Role == Role.All)
                    {
                        btnAdd.Enabled = false;
                        btnDelete.Enabled = false;
                        btnEdit.Enabled = false;
                        List<User> list = new List<User>();
                        list.Add(currentUser);
                        this.gridControl1.DataSource = list;

                    }                    
                }
            }

        }

        void OnChangePasswordSuccessed(UFEPacket resp)
        {
            int lockUserId = resp.Content.GetProperty<int>("OwnerId");
            int currentUserId = resp.UserId;
            if (lockUserId == currentUserId)
                MsgBox.Warning("Set password successed!");
        }

        void OnUserChanged(UFEPacket resp)
        {
            InitGrid();
        }


        private void InitGrid()
        {
            gridControl1.DataSource = null;
            if (currentUser.Role >= Role.Administrator)
            {
                this.gridControl1.DataSource = sign.Controller.Connection.Users;
            }
            else
            {
                List<User> list = new List<User>();
                list.Add(currentUser);
                this.gridControl1.DataSource = list;
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            UserDetailForm detail = new UserDetailForm(null);
            detail.ShowModalDialog();
            if (detail.IsRefresh)
                InitGrid();
        }

        void btnEdit_Click(object sender, System.EventArgs e)
        {
            UserDetailForm detail;
            User current = new User();

            if (currentUser.Role == Role.Administrator)
            {
                current = (User)((gridView1.GetFocusedRow()));
            }
            else
            {
                current = currentUser;
            }
            detail = new UserDetailForm(current);

            detail.ShowModalDialog();
            if (detail.IsRefresh)
                InitGrid();
        }

        void btnDelete_Click(object sender, System.EventArgs e)
        {
            Delete();
        }

        /// <summary>
        /// Delete user
        /// </summary>
        private void Delete()
        {
            if (gridView1.GetFocusedRow() == null)
                return;
            if (MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.No)
                return;
            User current = new User();
            current = gridView1.GetFocusedRow() as User;
            
            sign.Controller.UserManager.DeleteUser(current.Id, p =>
                {
                    if (p.IsSuccessed)
                        InitGrid();
                    else
                        MsgBox.Warning("Sorry,delete failed,please try again");
                });
        }

        /// <summary>
        /// Edit menu event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void propertiesToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Edit();
        }

        /// <summary>
        /// Set right button menu item state
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void contextMenuStrip_Opening(object sender, System.ComponentModel.CancelEventArgs e)
        {
            User currentSignUser = sign.Controller.Connection.User;

            if (currentSignUser.Role != Role.Administrator
                &&currentSignUser.Role!=Role.Default)
            {
                contextMenuStrip.Items[1].Visible = false;
                contextMenuStrip.Items[2].Visible = false;
                
            }
            else
            {
                contextMenuStrip.Items[1].Visible = true;
                contextMenuStrip.Items[2].Visible = true;
                contextMenuStrip.Items[0].Visible = true;
            }
        }

        /// <summary>
        /// Edit event
        /// </summary>
        private void Edit()
        {
            UserDetailForm detail;
            User current = new User();
            if (currentUser.Role == Role.Commands
                || currentUser.Role == Role.FileTransfer
                || currentUser.Role== Role.All)
                return;
            if (currentUser.Role == Role.Administrator
                ||currentUser.Role== Role.Default)
            {
                current = (User)((gridView1.GetFocusedRow()));
            }
            else
            {
                current = currentUser;
            }
            detail = new UserDetailForm(current);

            detail.ShowModalDialog();
            if (detail.IsRefresh)
                InitGrid();
        }

        /// <summary>
        /// Delete menu event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void deleteToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Delete();
        }

        /// <summary>
        /// Set password menu event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void setPasswordToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            User current = new User();

            if (currentUser.Role == Role.Administrator
                ||currentUser.Role == Role.Default)
            {
                current = (User)((gridView1.GetFocusedRow()));
            }
            else
            {
                current = currentUser;
            }
            UserChangePassword pwd = new UserChangePassword(current);
            pwd.ShowModalDialog();
            if (pwd.IsRefresh)
                InitGrid();
        }


        void gridControl1_DoubleClick(object sender, System.EventArgs e)
        {
            if (gridView1.GetFocusedRow() != null)
            {
                Edit();
            }
        }

        /// <summary>
        /// Right button menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gridControl1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                User currentSignUser = sign.Controller.Connection.User;
                if (currentSignUser.Role == Role.Commands
                        || currentSignUser.Role == Role.FileTransfer)
                    this.gridControl1.ContextMenuStrip = null;
                else
                {
                    gridControl1.ContextMenuStrip = contextMenuStrip;
                }
            }
        }

    }
}
