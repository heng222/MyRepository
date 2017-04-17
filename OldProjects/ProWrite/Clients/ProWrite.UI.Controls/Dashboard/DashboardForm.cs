//---------------------------------------------------------------------
//
// File: DashboardForm.cs
//
// Description:
// Dashboard form base class
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// terry 2008-6-26 添加部分注释 并修改在编辑Sign和Group 时点击Cancel也能保存数据的问题
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
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Settings;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Base class of dashBoard form 
    /// </summary>
    public partial class DashboardForm : DialogForm
    {
        /// <summary>
        /// 保存修改前dashboard的基本信息
        /// </summary>
        protected class DashboardOld
        {
            public string Name;
            public string ParentName;
        }

        /// <summary>
        /// 保存修改前的Sign Group信息
        /// </summary>
        protected class SignGroupOld : DashboardOld
        {
            public string Name1
            {
                get { return Name; }
                set { Name = value; }
            }
            private SignGroupInfo parent;

            public SignGroupInfo Parent
            {
                get { return parent; }
                set { parent = value; }
            }
        }


        /// <summary>
        /// 保存修改前的Sign信息
        /// </summary>
        protected class SignOld : DashboardOld
        {
            public string Name1
            {
                get { return Name; }
                set { Name = value; }
            }
            private SignGroupInfo parent;

            public SignGroupInfo Parent
            {
                get { return parent; }
                set { parent = value; }
            }
            private SignType _type;
            public SignType Type
            {
                get { return _type; }
                set
                {
                    if (value != _type)
                    {
                        _type = value;
                    }
                }
            }

            private int _width;
            public int Width
            {
                get { return _width; }
                set
                {
                    if (value != _width)
                    {
                        _width = value;
                    }
                }
            }

            private int _height;
            public int Height
            {
                get { return _height; }
                set
                {
                    if (value != _height)
                    {
                        _height = value;
                    }
                }
            }

            public string SignInfomation
            {
                get;
                set;
            }

            private string image;
            public string Image
            {
                get { return image; }
                set
                {
                    if (value != image)
                    {
                        image = value;
                    }
                }
            }
            private TemplateGroup _template;
            public TemplateGroup Template
            {
                get { return _template ?? CloneManager.Clone<TemplateGroup>(TemplateGroup.Default); }
                set { _template = CloneManager.Clone<TemplateGroup>(value); }
            }

        }
        /// <summary>
        /// parent
        /// </summary>
        protected SignGroupInfo _Parent;
        protected bool _IsEdit;
        protected bool isRefresh = false;
        public bool IsDisconnection = false;
        protected bool _isAddToGroup = false;
        protected int SelectIndex = 0;
        protected string SelectText = "[No Group]";
        /// <summary>
        /// Is refresh
        /// </summary>
        public bool IsRefresh
        {
            get { return isRefresh; }
            protected set { isRefresh = value; }
        }

        protected bool isConnectWebCam = false;
        public bool IsConnectWebCam
        {
            get { return isConnectWebCam; }
            protected set { isConnectWebCam = value; }
        }

        protected DashboardItem dashBoard;

        public DashboardItem DashBoard
        {
            get { return dashBoard; }
            set
            {
                dashBoard = value;
            }
        }
    }

    /// <summary>
    /// Base class of dashborad item
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public partial class DashboardForm<T> : DashboardForm where T : DashboardItem, new()
    {
        private T _current;

        public T Current
        {
            get { return _current; }
            protected set { _current = value; }
        }

        /// <summary>
        /// Add
        /// </summary>
        /// <param name="parent"></param>
        public DashboardForm(SignGroupInfo parent)
        {
            if (!DesignMode)
            {
                _current = new T();
                _Parent = parent;
            }
        }

        /// <summary>
        /// Add
        /// </summary>
        public DashboardForm()
            : this(DataGate.Project.RootGroup)
        {
        }

        /// <summary>
        /// Edit
        /// </summary>
        /// <param name="current">Current group</param>
        /// <param name="parent">Current</param>
        public DashboardForm(T current, SignGroupInfo parent)
        {
            if (!DesignMode)
            {
                _IsEdit = true;
                _Parent = parent;
                _current = current;
                DashboardOld dashboardOld = new DashboardOld();
                dashboardOld.Name = current.Name;
                dashboardOld.ParentName = current.ParentName;
            }
        }

        /// <summary>
        /// Save
        /// </summary>
        protected override void OnOk()
        {
            if (!this._current.IsEmpty)
            {
                _current.Name = _current.Name.Replace("/", "//").Replace("\'", "\"");
                dashBoard = _current as DashboardItem;
                if (!_IsEdit)
                {
                    if (_current.DashboardType != DashboardType.Sign)
                        _current.Active = true;
                        
                    OnSave();
                }
                else
                {
                    if (OnEdit())
                    {
                        UpLoad();
                        DataGate.Update();
                        isRefresh = true;
                            
                        if (_isAddToGroup||Current.DashboardType != DashboardType.Sign)
                            Close();
                    }
                }
            }
        }

        /// <summary>
        /// Save
        /// </summary>
        protected virtual void OnSave()
        {

        }

        /// <summary>
        /// UpLoad shape
        /// </summary>
        protected virtual void UpLoad()
        {

        }

        /// <summary>
        /// Edit
        /// </summary>
        protected virtual bool OnEdit()
        {
            return true;
        }
    }
}
