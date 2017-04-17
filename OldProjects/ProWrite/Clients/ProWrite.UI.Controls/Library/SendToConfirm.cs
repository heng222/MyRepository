using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Library
{
    public partial class SendToConfirm : XtraForm
    {
        public SendToConfirm(LibraryType AddType,LibraryType ToType)
        {
            InitializeComponent();
            DialogResult = 2;
            this.labelControl1.Text = "Create a new "+ToType.ToString().ToLower()+" or add " + AddType.ToString().ToLower() + " to existing "+ToType.ToString().ToLower()+".";
            this.Text = "Create New "+ToType.ToString();
        }
        /// <summary>
        /// 0:New;
        /// 1:Existing;
        /// 2:Cancel;
        /// </summary>
        public int DialogResult
        {
            get;
            set;
        }

        private void btnNew_Click(object sender, EventArgs e)
        {
            DialogResult = 0;
            Close();
        }

        private void btnExisting_Click(object sender, EventArgs e)
        {
            DialogResult = 1;
            Close();
        }

        private void BtnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = 2;
            Close();
        }
    }
}
