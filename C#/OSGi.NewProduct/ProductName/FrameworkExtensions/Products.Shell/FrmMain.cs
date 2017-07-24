using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Platform.Presentation;

namespace Products.Shell
{
    partial class FrmMain : Form, IControlOptimizer
    {
        protected List<IControlOptimizer> _controlOptimizers = new List<IControlOptimizer>();

        public FrmMain()
        {
            InitializeComponent();
        }

        #region "Protected methods"
        protected override void OnLoad(EventArgs e)
        {
            try
            {
                base.OnLoad(e);

                if (!DesignMode)
                {
                    // 设置主窗口标题
                    //Text = string.Format("ATS-SIL2 - {0}", NodeContextManager.Current.Name);
                    Text = string.Format("ProductName");
                    LogUtility.Info("-={0}已启动，欢迎使用=-", Workbench.MainForm.Text);
                }

                BuildOptimizerControl();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                DialogResult rc = MessageBox.Show(this, "确定退出？", this.Text,
                    MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (rc == DialogResult.No)
                {
                    e.Cancel = true;
                }
                else
                {
                    e.Cancel = false;
                }
            }

            LogUtility.Warning(string.Format("CloseReason={0}，Cancel={1}.", e.CloseReason, e.Cancel));
        }
        #endregion


        #region "Private methods"

        private void BuildOptimizerControl()
        {
            _controlOptimizers = Workbench.MainWorkspace.SmartParts.OfType<IControlOptimizer>().ToList();
        }
        #endregion


        #region "public methods"
        public void OptimizeIdle()
        {
            try
            {
                foreach (var item in _controlOptimizers)
                {
                    item.OptimizeIdle();
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion
    }
}
