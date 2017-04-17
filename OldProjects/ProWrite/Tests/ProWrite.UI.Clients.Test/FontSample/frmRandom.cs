using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmRandom : Form
    {
        public frmRandom()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int max = 10;
            int current;
            Random ran =  new Random();
            current = ran.Next(max);
            textBox1.Text = current.ToString();
        }
    }
}