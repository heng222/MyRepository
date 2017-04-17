using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmFontZoom1 : Form
    {
        Bitmap memBmp = new Bitmap(150, 50);

        public frmFontZoom1()
        {
            //FontFamily.Families
            //memBmp.MakeTransparent(Color.Red);

            InitializeComponent();
            // 准备一个字符串图形
            //
            using (Graphics g = Graphics.FromImage(memBmp))
            {
                g.DrawString("A", new Font("Times New Roman", 16), Brushes.Black, 10, 10);
            }

        }

        private void FontZoomForm1_Paint(object sender, PaintEventArgs e)
        {
            using (Graphics g = e.Graphics)
            {
                // 原样画图
                //
                g.DrawImageUnscaled(memBmp, 0, 0);

                // 放大，采用最近点取样，突出失真的效果
                //
                GraphicsUnit old = e.Graphics.PageUnit;
                e.Graphics.PageUnit = GraphicsUnit.Pixel;
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;                       //<---
                g.DrawImage(memBmp, new Rectangle(0, 50, 600, 200), new Rectangle(0, 0, 150, 50), GraphicsUnit.Pixel);  //<---
            }

        }
    }
}