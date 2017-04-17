using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmFontZoom0 : Form
    {
        public frmFontZoom0()
        {
            InitializeComponent();
        }

        private void panel1_Click(object sender, EventArgs e)
        {
            //richTextBox1.HideSelection = true;
            //richTextBox1.Focus();
            //richTextBox1.CanFocus = false; 
            //richTextBox1.DeselectAll();
            //richTextBox1.Enabled = false;
            //richTextBox1
            //richTextBox1.d
        }

        
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Brush brush = new SolidBrush(Color.Black);
            string _durationTxt = "A";
            Font font = new Font("PL 07 Donna", 6.0f, FontStyle.Regular, GraphicsUnit.Point);
            e.Graphics.CompositingQuality = CompositingQuality.HighQuality;
            e.Graphics.ScaleTransform(8, 8);
            
            //e.Graphics.SmoothingMode = SmoothingMode.None;
            //e.Graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
            //e.Graphics.
            e.Graphics.DrawString(_durationTxt, font, brush, 0, 0); 
            //e.Graphics.
            //e.Graphics.DrawImage(
            //Bitmap bitmap = new Bitmap(width, height);   
            //panel1.Font.Unit = GraphicsUnit.Pixel;
            //reg
            //e.Graphics.
        }

        //private void button1_Click(object sender, EventArgs e)
        //{
        //    DrawVerticalText(float.Parse(textBox2.Text));
        //}

        //private void DrawVerticalText(float zoom)
        //{
        //    System.Drawing.Graphics formGraphics = this.CreateGraphics();
        //    string drawString = textBox1.Text;
        //    System.Drawing.Font drawFont = new System.Drawing.Font("Arial", 16);
        //    System.Drawing.SolidBrush drawBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Black);
        //    float x = 150.0f;
        //    float y = 50.0f;
        //    System.Drawing.StringFormat drawFormat = new System.Drawing.StringFormat(StringFormatFlags.DirectionVertical);
        //    formGraphics.ScaleTransform(zoom, zoom);
        //    //formGraphics.p
        //    formGraphics.DrawString(drawString, drawFont, drawBrush, x, y, drawFormat);
        //    drawFont.Dispose();
        //    drawBrush.Dispose();
        //    formGraphics.Dispose();
        //}
    }
}