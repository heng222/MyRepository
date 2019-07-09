using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Products.Shell
{
    partial class CompanyContactsForm : Form
    {
        /// <summary>
        /// 构造函数。
        /// </summary>
        public CompanyContactsForm()
        {
            InitializeComponent();
        }

        private void CompanyContactsForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                this.Close();
            }
        }
    }
}
