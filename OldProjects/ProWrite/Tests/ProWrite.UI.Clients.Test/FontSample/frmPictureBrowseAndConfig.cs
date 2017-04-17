using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls; 

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmPictureBrowseAndConfig : Form
    {

        private string strfilename = "E:\\xuming\\Jpg\\DCIM\\183CANON\\IMG_8390.JPG";




        public frmPictureBrowseAndConfig()
        {
            InitializeComponent();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            
label1.Refresh();




        }

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            label1.Refresh();

        }

        private void numericUpDown3_ValueChanged(object sender, EventArgs e)
        {
            label1.Refresh();

        }

        private void numericUpDown4_ValueChanged(object sender, EventArgs e)
        {
            label1.Refresh();

        }

        private void numericUpDown5_ValueChanged(object sender, EventArgs e)
        {
            label1.Refresh();

        }

        private void label1_Paint(object sender, PaintEventArgs e)
        {
            
            if (this.strfilename.Trim()=="") 
                return ; 
            try 
            { 
                Bitmap mybitmap = new Bitmap(strfilename); 
                Graphics g = e.Graphics; 
                TextureBrush mybrush = new TextureBrush(mybitmap); 
                float x = (float)(numericUpDownS1.Value / 100); 
                float y = (float)(numericUpDownS2.Value / 100); 
                mybrush.ScaleTransform(x, y); 
                g.FillRectangle(mybrush, 0, 0, ClientRectangle.Width, ClientRectangle.Height); 
                float r = (float)(numericUpDownR1.Value); 
                mybrush.RotateTransform(r); 
                g.FillRectangle(mybrush, 0, 0, ClientRectangle.Width, ClientRectangle.Height); 
                float tx = (float)(numericUpDownT1.Value); 
                float ty = (float)(numericUpDownT2.Value); 
                mybrush.TranslateTransform(tx, ty); 
                g.FillRectangle(mybrush, 0, 0, ClientRectangle.Width, ClientRectangle.Height); 
            } 
            catch (Exception Err) 
            { 
                MessageBox.Show("Open File Error. ","Informatin .", MessageBoxButtons.OK, MessageBoxIcon.Information); 
            } 




        }

        private void button1_Click(object sender, EventArgs e)
        {

            openFileDialog1.ShowDialog();// ShowModalDialog(); 
strfilename=openFileDialog1.FileName; 
label1.Refresh(); 




        }
    }
}