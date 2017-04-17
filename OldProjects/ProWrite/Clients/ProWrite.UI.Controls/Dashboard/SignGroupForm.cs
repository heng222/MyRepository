//---------------------------------------------------------------------
//
// File: SignGroupForm.cs
//
// Description:
// Implements my Class. 
//
// Author: terry
//
// Copyright (C) 2008 by Trans-Lux  All rights reserved.
// 
//Modify history:   
// terry  2008-6-19 修改内容：代码注释，国际化
//  terry 2008-6-26 添加region和部分注释
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Add or edit sign group
    /// </summary>
    public partial class SignGroupForm : DashboardForm<SignGroupInfo>
    {
        #region Variable
        private SignInfo _sign;
        SignGroupOld old = new SignGroupOld();
        #endregion

        #region Constants
        string groupName = "Group1";
        #endregion

        #region Constructors
        /// <summary>
        /// Add
        /// </summary>
        /// <param name="parent"></param>
        public SignGroupForm(SignGroupInfo parent)
            : base(parent)
        {
            InitializeComponent();
        }

        /// <summary>
        /// Add
        /// </summary>
        /// <param name="parent"></param>
        public SignGroupForm(SignInfo sign)
            : base(sign.Parent)
        {
            InitializeComponent();
            _sign = sign;
        }
        /// <summary>
        /// Add
        /// </summary>
        public SignGroupForm()
            : this(DataGate.Project.RootGroup)
        {
        }

        /// <summary>
        /// Edit
        /// </summary>
        /// <param name="group">Current group</param>
        /// <param name="parent">Current</param>
        public SignGroupForm(SignGroupInfo group, SignGroupInfo parent)
            : base(group, parent)
        {
            InitializeComponent();
            old.Name = group.Name;
            old.Parent = group.Parent;
        }
        #endregion

        #region Initialization

        /// <summary>
        /// 初始化资源
        /// </summary>
        public override void InitializeResource()
        {
            base.InitializeResource();
            if (_IsEdit)
                this.Text = Resources.Resource.GetString(Resources.Resource.Strings.EditSignGroup);
            else
                this.Text = Resources.Resource.GetString(Resources.Resource.Strings.AddSignGroup);
            this.lblParent.Text = Resources.Resource.GetString(Resources.Resource.Strings.DashboardForm_lblParent);
            this.lblGroupName.Text = Resources.Resource.GetString(Resources.Resource.Strings.DashboardForm_lblGroupName);
            
        }

        protected override void Init()
        {
            //为ddlParent添加空项（[No Group]）
            //ddlParent.Properties.Items.Add(SignGroupInfo.Empty);//new SignGroupInfo(true)
            ddlParent.Properties.Items.Add(new SignGroupInfo(true));

            SignGroupInfo[] groups = SignGroupTree.AllGroups;
            if (groups != null && groups.Length > 0)
            {
                ddlParent.Properties.Items.AddRange(groups);
            }
            ddlParent.Text = _Parent.Name;
            ddlParent.SelectedItem = _Parent;

            //数据绑定
            //this.txtGroupName.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.bindingSource1, "Name", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged, null, "N0"));
            //this.ddlParent.DataBindings.Add(new System.Windows.Forms.Binding("SelectedItem", this.bindingSource1, "ParentName", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged, null, "N0"));
            //this.ddlParent.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.bindingSource1, "ParentName", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged, null, "N0"));
            bindingSource1.DataSource = Current;
            txtGroupName.Text = Current.Name;
            //根据当前操作状态来设定ddlParent当前选中项
            if (_IsEdit)
            {
                ddlParent.SelectedItem = Current.Parent;
                try
                {
                    ddlParent.Properties.Items.Remove(Current);
                }
                catch
                { }
                List<SignGroupInfo> list = SignGroupInfo.GetAllChildGroups(Current);
                foreach (SignGroupInfo group in list)
                {
                    ddlParent.Properties.Items.Remove(group);
                }

                if (_Parent != null && !_Parent.IsRoot)
                    ddlParent.SelectedItem = Current.Parent;
                else
                    ddlParent.SelectedIndex = 0;
            }
            else
            {
                if (_Parent != null && !_Parent.IsRoot)
                {
                    ddlParent.Text = _Parent.Name;
                    ddlParent.SelectedItem = _Parent;
                }
                else
                    ddlParent.SelectedIndex = 0;
                ;

                int _autoId = 1;

                while (IsSameName(groupName))
                {
                    _autoId++;
                    groupName = "Group" + _autoId.ToString();
                }
                txtGroupName.Text = groupName;
                Current.Name = groupName;
            }
        }
        #endregion

        #region Function
        /// <summary>
        /// Save
        /// </summary>
        protected override void OnSave()
        {
            base.OnSave();
            if (txtGroupName.Text == null || txtGroupName.Text.Trim() == "")
            {
                MsgBox.Warning("Group name can't be empty");
                return;
            }

            Current.Name = txtGroupName.Text.Trim();
            //判断是否选中了“[No Group]”
            if (ddlParent.Text != SelectText)
            {
                _Parent = ddlParent.SelectedItem as SignGroupInfo;
                //if (SignGroupInfo.IsSignCountValid(_Parent))
                //{
                //    MsgBox.Warning(Resource.GetString(Resource.Strings.SignsCountMoreThanTwenty));
                //    return;
                //}
                if (SignGroupInfo.GetChildCountByGroup(Current) + SignGroupInfo.GetRootChildCountByGroup(ddlParent.SelectedItem as SignGroupInfo) > 20)
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                    return;
                }
            }
            else
                //将_Parent设置为根
                _Parent = DataGate.Project.RootGroup;
            if (_Parent!=null&&!_Parent.AddGroup(Current))
            {
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.DashBoard_SaveGroupRepeat));
                return;
            }

            this.IsRefresh = true;
            if (_sign != null && !_sign.IsEmpty)
                _sign.Parent = Current;
           /*To do
           * 
           * Add Template
           * 
           */
            DataGate.Update();
            this.Close();

        }
        private bool IsSameName(string name)
        {
            bool result = false;

            foreach (SignInfo item in DashboardItem.AllSigns)
            {
                if (item.Name == name)
                    result = true;
            }
            foreach (SignGroupInfo item in DashboardItem.AllGroups)
            {
                if (item.Name == name)
                    result = true;
            }

            return result;
        }

        /// <summary>
        /// 编辑
        /// </summary>
        protected override bool OnEdit()
        {
            if (txtGroupName.Text.Trim() == null || txtGroupName.Text.Trim() == "")
            {
                MsgBox.Warning("Group name can't be empty");
                return false;
            }
            if (this.ddlParent.Text != SelectText
                && ddlParent.Text != Current.ParentName)
            {
                /////判断被拖入的Group的sign个数是否超过20
                //if (SignGroupInfo.IsSignCountValid(ddlParent.SelectedItem as SignGroupInfo))
                //{
                //    MsgBox.Warning(Resource.GetString(Resource.Strings.SignsCountMoreThanTwenty));
                //    return false;
                //}
                if (!SignGroupInfo.IsTwoGroupSameRoot(Current, ddlParent.SelectedItem as SignGroupInfo))
                {
                    if (SignGroupInfo.GetChildCountByGroup(Current) + SignGroupInfo.GetRootChildCountByGroup(ddlParent.SelectedItem as SignGroupInfo) > 20)
                    {
                        MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SignsCountMoreThanTwenty));
                        return false;
                    }
                }
            }
            if (Current.Name != txtGroupName.Text.Trim())
            {
                if (DashboardItem._allGroups.Contains(txtGroupName.Text.Trim()) || DashboardItem._allSigns.Contains(txtGroupName.Text.Trim()))
                {
                    MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.DashBoard_SaveSignRepeat));
                    return false;
                }
            }
            Current.Name = txtGroupName.Text.Trim();
            //如果SignParent选择的是“No Group”，则该Sign的Parent为树根
            DashboardItem item = Current as DashboardItem;
            if (this.ddlParent.Text == SelectText)
            {
                item.Parent = DataGate.Project.RootGroup;
            }
            else
                item.Parent = ddlParent.SelectedItem as SignGroupInfo;
            /*To do
             * 
             * Add Template
             * 
             */
           
            DataGate.Update();
            return true;
        }

        /// <summary>
        /// btnCancel事件
        /// </summary>
        protected override void OnCancel()
        {
            Current.Name = old.Name1;
            Current.Parent = old.Parent;
        }
        #endregion
    }
}
