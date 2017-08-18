using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ImgDlgSample
{
    public partial class Form1 : CoolImageDlg.TransparentForm
    {
        public Form1()
        {
            base.BackgroundImage = ImgDlgSample.Properties.Resources.desktopmasks_bk;
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 dlg = new Form2();
            dlg.ShowDialog();
        }

    }
}