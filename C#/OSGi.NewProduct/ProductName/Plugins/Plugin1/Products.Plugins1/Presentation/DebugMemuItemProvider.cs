/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Windows.Forms;

using Products.Presentation.Specification;

namespace Products.Plugin1.Presentation
{
    class DebugMemuItemProvider : Acl.CompositeDisposable, IDebugMenuItemProvider
    {
        #region "Field"
        private List<ToolStripMenuItem> _menuItems = new List<ToolStripMenuItem>();

        #endregion

        #region "Constructor"
        public DebugMemuItemProvider()
        {
            this.InitializeMenu();
        }
        #endregion

        #region "Properties"

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        /// <summary>
        /// 初始化菜单项
        /// </summary>
        private void InitializeMenu()
        {
            var debugMenu = new ToolStripMenuItem("Plugin1调试(&U)");
            _menuItems.Add(debugMenu);
            this.AddDisposable(debugMenu);

            var newMenuItem = new ToolStripMenuItem() { Text = "调试菜单项1(&S)..." };
            newMenuItem.Click += OnDebug1_Click;
            debugMenu.DropDownItems.Add(newMenuItem);
            this.AddDisposable(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "调试菜单项2(&M)..." };
            newMenuItem.Click += OnDebug2_Click;
            debugMenu.DropDownItems.Add(newMenuItem);
            this.AddDisposable(newMenuItem);
        }

        private void OnDebug1_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show("OnDebug1_Click");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnDebug2_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show("OnDebug2_Click");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region IDebugMenuItemProvider 成员
        /// <inheritdoc/>
        public IEnumerable<ToolStripItem> GetMenuItems()
        {
            return _menuItems;
        }
        #endregion
    }
}
