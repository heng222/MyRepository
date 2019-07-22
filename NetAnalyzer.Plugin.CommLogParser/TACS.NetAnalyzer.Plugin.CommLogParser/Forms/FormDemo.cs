using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TACS.CommLogParser.Plugin4NetAnalyzer.Forms
{
    partial class FormDemo : Form
    {
        public FormDemo()
        {
            InitializeComponent();

            this.FormClosing += FormDemo_FormClosing;
        }

        void FormDemo_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }
    }
}
