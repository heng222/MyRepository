using System;
using System.Windows.Forms;

using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class NewCategoryForm : Form
    {
        private const string ErrorTip = "The category library has a same item.";

        public NewCategoryForm()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (txtCategoryName.Text.Trim() != string.Empty && CheckName(txtCategoryName.Text))
            {
                CategoryName = txtCategoryName.Text;
                this.DialogResult = DialogResult.OK;
            }
            else
            {
                //...
            }
        }

        public string _categoryName = string.Empty;
        public string CategoryName
        {
            get { return _categoryName; }
            set { _categoryName = value; }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        private void NewCategoryForm_Activated(object sender, EventArgs e)
        {
            txtCategoryName.Focus();
        }

        private bool CheckName(string name)
        {
            bool checkResult = true;
            foreach (LiveCategory category in LibraryCategoryControl.Categories)
            {
                if (category.Name == name)
                {
                    checkResult = false;
                    SetErrorToolTip();
                    break;
                }
            }
            return checkResult;
        }

        private void SetErrorToolTip()
        {
            defaultToolTipController1.SetToolTip(txtCategoryName, ErrorTip);
            defaultToolTipController1.SetToolTipIconType(txtCategoryName, DevExpress.Utils.ToolTipIconType.Error);
        }

        private void txtCategoryName_TextChanged(object sender, EventArgs e)
        {
            SetErrorToolTip();
        }
        
    }
}
