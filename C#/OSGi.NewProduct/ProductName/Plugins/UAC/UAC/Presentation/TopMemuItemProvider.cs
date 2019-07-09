/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
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

namespace Products.UAC.Presentation
{
    class TopMemuItemProvider : ITopMenuItemProvider
    {
        #region "Filed"
        /// <summary>
        /// 控件顶级菜单列表
        /// </summary>
        private List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();

        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification verify)
        {
            if (verify == null) throw new ArgumentException("登录验证接口不能为空引用。");

            this.Verify = verify;
            this.InitializeMenu();
        }
        #endregion

        #region "Properties"
        public ILoginVerification Verify { get; private set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void OnUserSwitch(object sender, EventArgs e)
        {
            try
            {                
                var frmLogin = new FormLogin(this.Verify);
                frmLogin.ShowDialog();
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
                this.Verify.Logoff();

                MessageBox.Show("注销成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion

        #region "private methods"
        /// <summary>
        /// 初始化菜单项
        /// </summary>
        private void InitializeMenu()
        {
            //初始化菜单列表项
            var userMenuItem = new ToolStripMenuItem("用户(&U)");

            var miUserChange = new ToolStripMenuItem();
            //miUserChange.Tag = UserManagementCommands.SwitchUser;
            miUserChange.Text = "用户切换(&S)...";
            miUserChange.Image = Resources.UserSwitch;
            miUserChange.Click += new EventHandler(OnUserSwitch);
            userMenuItem.DropDownItems.Add(miUserChange);

            //miChangePwd = new ToolStripMenuItem();
            //miChangePwd.Enabled = false;
            //miChangePwd.Tag = UserManagementCommands.UpdatePassword;
            //miChangePwd.Text = "修改密码(&M)";
            //miChangePwd.Image = Resources.ModifyPassword;
            //miChangePwd.Click += new EventHandler(OnUpdatePassword);
            //userMenuItem.DropDownItems.Add(miChangePwd);

            var miUserLogoff = new ToolStripMenuItem();
            miUserLogoff.Name = "miUserLogoff";
            //miUserLogoff.Tag = UserManagementCommands.Logoff;
            miUserLogoff.Text = "注销(&X)";
            miUserLogoff.Image = Resources.Logout;
            miUserLogoff.Click += new EventHandler(OnLogoff);
            userMenuItem.DropDownItems.Add(miUserLogoff);

            _topMenuItems.Add(userMenuItem);
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
