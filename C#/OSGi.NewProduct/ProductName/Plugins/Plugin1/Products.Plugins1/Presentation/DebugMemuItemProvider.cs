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
        /// ��ʼ���˵���
        /// </summary>
        private void InitializeMenu()
        {
            var debugMenu = new ToolStripMenuItem("Plugin1����(&U)");
            _menuItems.Add(debugMenu);
            this.AddDisposable(debugMenu);

            var newMenuItem = new ToolStripMenuItem() { Text = "���Բ˵���1(&S)..." };
            newMenuItem.Click += OnDebug1_Click;
            debugMenu.DropDownItems.Add(newMenuItem);
            this.AddDisposable(newMenuItem);

            newMenuItem = new ToolStripMenuItem() { Text = "���Բ˵���2(&M)..." };
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
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                MessageBox.Show(ex.Message, "����", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region IDebugMenuItemProvider ��Ա
        /// <inheritdoc/>
        public IEnumerable<ToolStripItem> GetMenuItems()
        {
            return _menuItems;
        }
        #endregion
    }
}
