/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 13:40:50 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
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
        /// �ؼ������˵��б�
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
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion

        #region "private methods"
        /// <summary>
        /// ��ʼ���˵���
        /// </summary>
        private void InitializeMenu()
        {
            //��ʼ���˵��б���
            var userMenuItem = new ToolStripMenuItem("�û�(&U)");

            var miUserChange = new ToolStripMenuItem();
            //miUserChange.Tag = UserManagementCommands.SwitchUser;
            miUserChange.Text = "�û��л�(&S)";
            miUserChange.Image = Resources.UserSwitch;
            miUserChange.Click += new EventHandler(OnUserSwitch);
            userMenuItem.DropDownItems.Add(miUserChange);

            //miChangePwd = new ToolStripMenuItem();
            //miChangePwd.Enabled = false;
            //miChangePwd.Tag = UserManagementCommands.UpdatePassword;
            //miChangePwd.Text = "�޸�����(&M)";
            //miChangePwd.Image = Resources.ModifyPassword;
            //miChangePwd.Click += new EventHandler(OnUpdatePassword);
            //userMenuItem.DropDownItems.Add(miChangePwd);

            //miUserLogoff = new ToolStripMenuItem();
            //miUserLogoff.Enabled = false;
            //miUserLogoff.Name = "miUserLogoff";
            //miUserLogoff.Tag = UserManagementCommands.Logoff;
            //miUserLogoff.Text = "ע��(&X)";
            //miUserLogoff.Image = Resources.Logout;
            //miUserLogoff.Click += new EventHandler(OnLogoff);
            //userMenuItem.DropDownItems.Add(miUserLogoff);

            _topMenuItems.Add(userMenuItem);
        }
        #endregion


        #region ITopMenuItemProvider ��Ա
        /// <summary>
        /// ��ȡ�����˵���λ�á�-1��ʾ��ָ��λ�ã��ɿ���Զ����䡣
        /// </summary>
        public int Position { get { return 0; } }
        /// <summary>
        /// ��ȡ���ؼ��ṩ�Ķ����˵��б�
        /// </summary>
        public IEnumerable<ToolStripItem> GetTopMenu()
        {
            return _topMenuItems;
        }
        #endregion
    }
}
