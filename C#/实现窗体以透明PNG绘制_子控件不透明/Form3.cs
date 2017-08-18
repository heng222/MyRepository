using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CoolImageDlg;
using ImgDlgSample.Properties;

namespace ImgDlgSample
{
    public partial class Form3 : TransparentForm
    {
        public Form3()
        {
            InitializeComponent();

            label1.BorderStyle = BorderStyle.None;
        }

        private void label1_Click(object sender, EventArgs e)
        {
            label1.Text += DateTime.Now.ToString();

            label1.Left = (this.ClientRectangle.Width - label1.Width) / 2;
            label1.BringToFront();
        }

        private void Form3_Resize(object sender, EventArgs e)
        {
            label1.Left = (this.ClientRectangle.Width - label1.Width) / 2;
            label1.BringToFront();
        }
    }
}
