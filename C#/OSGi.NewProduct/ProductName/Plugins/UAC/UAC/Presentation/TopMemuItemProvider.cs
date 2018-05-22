/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/22 13:40:50 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
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

        //private ToolStripMenuItem miUserLogoff;
        //private ToolStripMenuItem miChangePwd;
        #endregion

        #region "Constructor"
        public TopMemuItemProvider()
        {
            this.InitializeMenu();
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void OnUserSwitch(object sender, EventArgs e)
        {
            try
            {
                var verifObj = new LocalLoginVerification();
                var frmLogin = new FormLogin(verifObj);

                frmLogin.ShowDialog();
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
            miUserChange.Text = "用户切换(&S)";
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

            //miUserLogoff = new ToolStripMenuItem();
            //miUserLogoff.Enabled = false;
            //miUserLogoff.Name = "miUserLogoff";
            //miUserLogoff.Tag = UserManagementCommands.Logoff;
            //miUserLogoff.Text = "注销(&X)";
            //miUserLogoff.Image = Resources.Logout;
            //miUserLogoff.Click += new EventHandler(OnLogoff);
            //userMenuItem.DropDownItems.Add(miUserLogoff);

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
