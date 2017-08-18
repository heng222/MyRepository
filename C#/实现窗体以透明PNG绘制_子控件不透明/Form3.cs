using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using CoolImageDlg;

namespace ImgDlgSample
{
    public partial class Form3 : TransparentForm
    {
        public Form3()
        {
            InitializeComponent();
            base.BackgroundImage = ImgDlgSample.Properties.Resources.DemoDlgBg2;
        }
    }
}
