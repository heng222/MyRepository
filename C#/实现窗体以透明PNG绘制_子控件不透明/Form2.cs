﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CoolImageDlg;

namespace ImgDlgSample
{
    public partial class Form2 : TransparentForm
    {
        public Form2()
        {
            base.BackgroundImage = ImgDlgSample.Properties.Resources.DemoDlgBg2;
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
