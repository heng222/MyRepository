
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Scheduler
{
    public partial class DeleteRecurrenceConfirmDialog : XtraForm
    {
        private int _deleteRecurrence = 1;
        /// <summary>
        /// 0:cancel
        /// 1:update
        /// 2:delete
        /// </summary>
        public int DeleteRecurrence
        {
            get { return _deleteRecurrence; }
            set { _deleteRecurrence = value; }
        }
        public DeleteRecurrenceConfirmDialog()
        {
            InitializeComponent();
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            CheckChanged();
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            _deleteRecurrence = 0;
            Close();
        }

        private void rbtnUpdate_CheckedChanged(object sender, EventArgs e)
        {
            CheckChanged();
        }

        private void rbtnDelete_CheckedChanged(object sender, EventArgs e)
        {
            CheckChanged();
        }

        private void CheckChanged()
        {
            if (rbtnUpdate.Checked)
                _deleteRecurrence = 1;
            else
                _deleteRecurrence = 2;
        }
    }
}
