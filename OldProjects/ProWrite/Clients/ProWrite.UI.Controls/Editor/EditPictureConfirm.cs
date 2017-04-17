using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Editor
{
    public partial class EditPictureConfirm : XtraForm
    {
        public int Result
        { get; set; }

        public EditPictureConfirm()
        {
            InitializeComponent();
        }

        private void btnSaveLibrary_Click(object sender, EventArgs e)
        {
            Result = 1;
        }

        private void btnSaveMessage_Click(object sender, EventArgs e)
        {
            Result = 2;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Result = 0;
        }
    }
}
