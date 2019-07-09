/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
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

        #endregion

        #region "Constructor"
        public TopMemuItemProvider(ILoginVerification verify)
        {
            if (verify == null) throw new ArgumentException("��¼��֤�ӿڲ���Ϊ�����á�");

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
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnLogoff(object sender, EventArgs e)
        {
            try
            {
                this.Verify.Logoff();

                MessageBox.Show("ע���ɹ���", "��ʾ", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
            miUserChange.Text = "�û��л�(&S)...";
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

            var miUserLogoff = new ToolStripMenuItem();
            miUserLogoff.Name = "miUserLogoff";
            //miUserLogoff.Tag = UserManagementCommands.Logoff;
            miUserLogoff.Text = "ע��(&X)";
            miUserLogoff.Image = Resources.Logout;
            miUserLogoff.Click += new EventHandler(OnLogoff);
            userMenuItem.DropDownItems.Add(miUserLogoff);

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
