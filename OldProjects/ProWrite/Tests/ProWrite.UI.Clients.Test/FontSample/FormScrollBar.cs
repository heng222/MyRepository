using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Drawing.Drawing2D;
using ProWrite.UI.Controls; 





namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class FormScrollBar : Form
    {
        public FormScrollBar()
        {
            InitializeComponent();
        }

        private void buttonOpenFile_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();//.ShowModalDialog(); 
            if (openFileDialog1.FileName.Trim() == "") 
            return; 
            try 
            { 
            Bitmap mybitmap = new Bitmap(openFileDialog1.FileName); 
            pictureBox1.Image = mybitmap; 
            } 
            catch (Exception Err) 
            { 
            MessageBox.Show("打开文件错误!", "信息提示", MessageBoxButtons.OK, MessageBoxIcon.Information); 
            } 
        }
    }
}