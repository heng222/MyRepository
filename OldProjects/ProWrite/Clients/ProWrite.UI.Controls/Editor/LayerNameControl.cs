//---------------------------------------------------------------------
//
// File: LayerNameControl.cs
//
// Description:
// 
//
// Author: Terry 2008-9-4
//
// Modify History:
// 
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Editor
{
    /// <summary>
    /// LayerNameControl
    /// </summary>
    public partial class LayerNameControl : UserControl
    {
        public LayerNameControl()
        {
            InitializeComponent();
        }

        public string LayerText
        {
            get { return label.Text; }
            set { label.Text = value; }
        }

        public Color LayerBackColor
        {
            get { return label.BackColor; }
            set { label.BackColor = value; }
        }

        private void label_DoubleClick(object sender, EventArgs e)
        {
            label.Visible = false;
            richTextBox.Text = label.Text;
            richTextBox.Visible = true;
        }

        private void richTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                label.Text = richTextBox.Text;
                richTextBox.Visible = false;
                label.Visible = true;
                e.Handled = true;
            }
            if (e.KeyCode == Keys.Escape)
            {
                label.Visible = true;
                richTextBox.Visible = false;
                richTextBox.Text = label.Text;
            }
        }

        private void richTextBox_TextChanged(object sender, EventArgs e)
        {
            label.Text = richTextBox.Text;
        }
    }
}
