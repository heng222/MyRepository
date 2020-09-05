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
        /// �ؼ������˵��б�
        /// </summary>
        private readonly List<ToolStripMenuItem> _topMenuItems = new List<ToolStripMenuItem>();
        private readonly IUserManagement _userManager;

        /// <summary>
        /// �˵��ע����
        /// </summary>
        private ToolStripMenuItem _menuItemLogOff;
        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification loginVerify, IUserAccessControl uac, IUserManagement userManagement)
        {
            this.LoginVerify = loginVerify ?? throw new ArgumentException("��¼��֤�ӿڲ���Ϊ�����á�");
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
        /// ��ʼ���˵���
        /// </summary>
        private void InitializeMenu()
        {
            //��ʼ���˵��б���
            var userMenuItem = new ToolStripMenuItem("�û�(&U)");
            this.AddDisposable(userMenuItem);
            _topMenuItems.Add(userMenuItem);

            var newMenuItem = new ToolStripMenuItem() { Text = "�û��л�(&S)...", Image = Resources.UserSwitch };
            this.AddDisposable(newMenuItem);
            newMenuItem.Click += UserSwitch_Click;
            userMenuItem.DropDownItems.Add(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "�޸�����(&M)...", Image = Resources.ModifyPassword };
            this.AddDisposable(newMenuItem);
            newMenuItem.Click += ModifyPassword_Click;
            userMenuItem.DropDownItems.Add(newMenuItem);

            _menuItemLogOff = new ToolStripMenuItem() { Text = "ע��(&X)", Image = Resources.Logout };
            this.AddDisposable(_menuItemLogOff);
            _menuItemLogOff.Visible = this.UAC.CurrentUserCode != UserInfo.Guest;
            _menuItemLogOff.Click += Logoff_Click;
            userMenuItem.DropDownItems.Add(_menuItemLogOff);
        }

        private void UserSwitch_Click(object sender, EventArgs e)
        {
            try
            {
                var frmLogin = new FormLogin(this.LoginVerify) { Text = "�û��л�" };
                frmLogin.ShowDialog();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Logoff_Click(object sender, EventArgs e)
        {
            try
            {
                this.LoginVerify.Logoff();

                MessageBox.Show("ע���ɹ���", "��ʾ", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
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
