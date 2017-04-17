using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmFontZoom : Form
    {
        public frmFontZoom()
        {
            InitializeComponent();
        }

        public Bitmap CreateFontBmp(Font font, string text, float zoom)
        {
            if (string.IsNullOrEmpty(text))
                return null;
            Size size = TextRenderer.MeasureText(text, font);
            Rectangle rect = new Rectangle(0, 0, size.Width, size.Height);
            Bitmap bmp = new Bitmap(size.Width, size.Height);
            Graphics graphics = Graphics.FromImage(bmp);
            TextRenderer.DrawText(
                graphics,
                text,
                font,
                rect,
                SystemColors.ControlText);

            if (zoom > 0 && zoom != 1)
            {
                int width = (int)Math.Ceiling(size.Width * zoom);
                int height = (int)Math.Ceiling(size.Height * zoom);
                Rectangle tmpRect = new Rectangle(0, 0, width, height);
                Bitmap tmpBmp = new Bitmap(width, height);
                graphics = Graphics.FromImage(tmpBmp);
                graphics.DrawImage(
                    bmp,
                    tmpRect,
                    rect,
                    GraphicsUnit.Pixel);
                graphics.Flush();
                graphics.Dispose();
                bmp.Dispose();
                return tmpBmp;
            }
            graphics.Flush();
            graphics.Dispose();
            return bmp;
        }

        private void FontZoomForm2_Load(object sender, EventArgs e)
        {
            
        }

        private void FontZoomForm2_Paint(object sender, PaintEventArgs e)
        {
            Font font = new Font("ËÎÌו", 10.0f, FontStyle.Italic, GraphicsUnit.Pixel);

            e.Graphics.DrawImage(CreateFontBmp(font, "Hello", 10f), 0, 0);
        }

    }
}