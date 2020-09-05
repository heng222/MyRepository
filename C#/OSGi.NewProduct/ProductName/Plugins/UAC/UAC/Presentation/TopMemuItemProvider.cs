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

using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Presentation.Specification;
using Products.UAC.Domain;
using Products.UAC.Presentation.Forms;
using Products.UAC.Properties;

namespace Products.UAC.Presentation
{
    class TopMemuItemProvider : Acl.CompositeDisposable, ITopMenuItemProvider
    {
        #region "Field"
        /// <summary>
        /// 控件顶级菜单列表
        /// </summary>
        private readonly List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();
        private readonly IUserManagement _userManager;

        /// <summary>
        /// 菜单项：注销。
        /// </summary>
        private ToolStripMenuItem _menuItemLogOff;
        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification loginVerify, IUserAccessControl uac, IUserManagement userManagement)
        {
            this.LoginVerify = loginVerify ?? throw new ArgumentException("登录验证接口不能为空引用。");
            this.UAC = uac;
            _userManager = userManagement;

            this.InitializeMenu();

            this.AddDisposable(GlobalMessageBus.SubscribeUserChanged(OnUserChanged));
        }
        #endregion

        #region "Properties"
        public ILoginVerification LoginVerify { get; private set; }

        public IUserAccessControl UAC { get; private set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void OnUserChanged(object sender, EventArgs args)
        {
            try
            {
                _menuItemLogOff.Visible = this.UAC.CurrentUserCode != UserInfo.Guest;
            }
            catch (Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        /// <summary>
        /// 初始化菜单项
        /// </summary>
        private void InitializeMenu()
        {
            //初始化菜单列表项
            var userMenuItem = new ToolStripMenuItem("用户(&U)");
            this.AddDisposable(userMenuItem);
            _topMenuItems.Add(userMenuItem);

            var newMenuItem = new ToolStripMenuItem() { Text = "用户切换(&S)...", Image = Resources.UserSwitch };
            this.AddDisposable(newMenuItem);
            newMenuItem.Click += UserSwitch_Click;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "修改密码(&M)...", Image = Resources.ModifyPassword };
            this.AddDisposable(newMenuItem);
            newMenuItem.Click += ModifyPassword_Click;
            userMenuItem.DropDownItems.Add(newMenuItem);

            _menuItemLogOff = new ToolStripMenuItem() { Text = "注销(&X)", Image = Resources.Logout };
            this.AddDisposable(_menuItemLogOff);
            _menuItemLogOff.Visible = this.UAC.CurrentUserCode != UserInfo.Guest;
            _menuItemLogOff.Click += Logoff_Click;
            userMenuItem.DropDownItems.Add(_menuItemLogOff);
        }

        private void UserSwitch_Click(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormLogin(this.LoginVerify) { Text = "用户切换" };
                frmLogin.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ModifyPassword_Click(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormModifyPassword(GlobalServices.UAC.CurrentUserName, _userManager);
                frmLogin.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Logoff_Click(object sender, EventArgs e)
        {
            try
            {
                this.LoginVerify.Logoff();

                MessageBox.Show("注销成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
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
