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
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Products.Presentation;
using Products.UAC.Properties;
using Products.UAC.Presentation.Forms;
using Products.UAC.Domain;
using Products.Infrastructure.Specification;

namespace Products.UAC.Presentation
{
    class TopMemuItemProvider : ITopMenuItemProvider
    {
        #region "Field"
        /// <summary>
        /// 控件顶级菜单列表
        /// </summary>
        private List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();
        private IUserManagement _userManager;

        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification loginVerify, IUserManagement userManagement)
        {
            if (loginVerify == null) throw new ArgumentException("登录验证接口不能为空引用。");

            _userManager = userManagement;
            this.LoginVerify = loginVerify;

            this.InitializeMenu();
        }
        #endregion

        #region "Properties"
        public ILoginVerification LoginVerify { get; private set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        /// <summary>
        /// 初始化菜单项
        /// </summary>
        private void InitializeMenu()
        {
            //初始化菜单列表项
            var userMenuItem = new ToolStripMenuItem("用户(&U)");
            _topMenuItems.Add(userMenuItem);

            var newMenuItem = new ToolStripMenuItem() { Text = "用户切换(&S)...", Image = Resources.UserSwitch };
            //miUserChange.Tag = UserManagementCommands.SwitchUser;
            newMenuItem.Click += OnUserSwitch;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "修改密码(&M)...", Image = Resources.ModifyPassword };
            newMenuItem.Click += OnModifyPassword;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "注销(&X)", Image = Resources.Logout };
            newMenuItem.Click += OnLogoff;
            userMenuItem.DropDownItems.Add(newMenuItem);
        }

        private void OnUserSwitch(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormLogin(this.LoginVerify) { Text = "用户切换" };
                frmLogin.ShowDialog();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnModifyPassword(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormModifyPassword(GlobalServices.UAC.CurrentUserName, _userManager);

                if (frmLogin.ShowDialog() == DialogResult.OK)
                {
                    MessageBox.Show("修改成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnLogoff(object sender, EventArgs e)
        {
            try
            {
                this.LoginVerify.Logoff();

                MessageBox.Show("注销成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region ITopMenuItemProvider 成员
        /// <summary>
        /// 获取顶级菜单的位置。-1表示不指定位置，由框架自动分配。
        /// </summary>
        public int Position { get { return 0; } }
        /// <summary>
        /// 获取主控件提供的顶级菜单列表
        /// </summary>
        public IEnumerable<ToolStripItem> GetTopMenu()
        {
            return _topMenuItems;
        }
        #endregion
    }
}
