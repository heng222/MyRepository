using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using Products.Presentation;

namespace Products.Shell
{
    partial class DockContentEx : DockContent
    {
        #region "Properites"
        public DockState DefaultDockState { get; set; }

        public DockContent DefaultParentContent { get; set; }
        public DockAlignment DefaultAlignment { get; set; }
        public double DefaultProportion { get; set; }

        public string PersistString { get; set; }

        public ProductPartAttribute PartAttribute { get; set; }

        public Control ChildPart { get; set; }
        #endregion

        #region "Constructors"
        public DockContentEx()
        {
            InitializeComponent();
        }

        public DockContentEx(Control control, string title)
            : this()
        {
            if (control != null)
            {
                if (string.IsNullOrWhiteSpace(control.Text))
                {
                    this.Text = title;
                }
                else
                {
                    this.Text = control.Text;
                }

                SetPersistString();

                control.Dock = DockStyle.Fill;
                this.Controls.Add(control);
                this.ChildPart = control;

                control.TextChanged += OnDockContentTextChanged;
            }
        }

        public DockContentEx(Control control, string title, Icon icon)
            : this(control, title)
        {
            if (icon != null)
            {
                this.Icon = icon;
            }
        }
        #endregion


        #region "private methods"

        private void OnDockContentTextChanged(object sender, EventArgs e)
        {
            try
            {
                base.Text = this.ChildPart.Text;
            }
            catch (System.Exception /*ex*/)
            {

            }
        }

        private void SetPersistString()
        {
            this.DockHandler.GetPersistStringCallback = () =>
            {
                 return this.Text;
            };
        }
        #endregion


        #region "Public methods"
        public void RemoveATSPart()
        {
            this.Controls.Remove(this.ChildPart);
            this.ChildPart = null;
        }
        #endregion


        #region "菜单事件"
        private void OnContextMenuStripOpening(object sender, CancelEventArgs e)
        {
            if (this.DockPanel.AllowEndUserDocking)
            {
                this.hideToolStripMenuItem.Enabled = this.CloseButtonVisible;
                this.floatToolStripMenuItem.Enabled = !this.IsFloat;
                this.dockToolStripMenuItem.Enabled = this.IsFloat;
            }
            else
            {
                this.hideToolStripMenuItem.Enabled = false;
                this.floatToolStripMenuItem.Enabled = false;
                this.dockToolStripMenuItem.Enabled = false;
            }
        }

        private void floatToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Show(this.DockPanel, DockState.Float);
        }

        private void dockToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Pane.RestoreToPanel();
        }

        private void hideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
        #endregion
    }
}
