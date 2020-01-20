/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        /// �ؼ������˵��б�
        /// </summary>
        private List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();
        private IUserManagement _userManager;

        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification loginVerify, IUserManagement userManagement)
        {
            if (loginVerify == null) throw new ArgumentException("��¼��֤�ӿڲ���Ϊ�����á�");

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
        /// ��ʼ���˵���
        /// </summary>
        private void InitializeMenu()
        {
            //��ʼ���˵��б���
            var userMenuItem = new ToolStripMenuItem("�û�(&U)");
            _topMenuItems.Add(userMenuItem);

            var newMenuItem = new ToolStripMenuItem() { Text = "�û��л�(&S)...", Image = Resources.UserSwitch };
            //miUserChange.Tag = UserManagementCommands.SwitchUser;
            newMenuItem.Click += OnUserSwitch;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "�޸�����(&M)...", Image = Resources.ModifyPassword };
            newMenuItem.Click += OnModifyPassword;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "ע��(&X)", Image = Resources.Logout };
            newMenuItem.Click += OnLogoff;
            userMenuItem.DropDownItems.Add(newMenuItem);
        }

        private void OnUserSwitch(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormLogin(this.LoginVerify) { Text = "�û��л�" };
                frmLogin.ShowDialog();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnModifyPassword(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormModifyPassword(GlobalServices.UAC.CurrentUserName, _userManager);

                if (frmLogin.ShowDialog() == DialogResult.OK)
                {
                    MessageBox.Show("�޸ĳɹ���", "��ʾ", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnLogoff(object sender, EventArgs e)
        {
            try
            {
                this.LoginVerify.Logoff();

                MessageBox.Show("ע���ɹ���", "��ʾ", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
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
