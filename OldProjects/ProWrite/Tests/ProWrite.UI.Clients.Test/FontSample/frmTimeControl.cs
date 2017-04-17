using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmTimeControl : Form
    {
        public frmTimeControl()
        {
            InitializeComponent();
            InitListBox();
        }
        private void InitListBox()
        {
            ColumnHeader header;
            //header = new ColumnHeader();
            //header.Text = "Ãû³Æ";
            //header.Width = 100;
            
            lvRole.Items.Add("ACTIVE");

            header = new ColumnHeader();
            header.Text = "±¸×¢";
            header.Width = lvRole.Size.Width - 100;
            lvRole.Items.Add(header);
        }
    }
}