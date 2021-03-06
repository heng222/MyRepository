﻿/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 15:46:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System.Windows.Forms;

using Acl.Presentation.Options;

using Products.Presentation;

namespace Products.Plugin1.Controls
{
    /// <summary>
    /// Plugin1配置页面。
    /// </summary>
    [Option(ConfigNodeNames.Plugins.Plugin1.General, "Plugin1 Config Title")]
    partial class CtrlConfigPage : UserControl, IOptionControl
    {
        #region "Field"
        #endregion

        #region "Properties"
        public Control View { get { return this; } }
        #endregion

        #region "Constructor"
        public CtrlConfigPage()
        {
            InitializeComponent();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        public void ApplyChanges()
        {

        }
        #endregion

        #region "控件事件处理函数"
        #endregion


    }
}
