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
            // ׼��һ���ַ���ͼ��
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
                // ԭ����ͼ
                //
                g.DrawImageUnscaled(memBmp, 0, 0);

                // �Ŵ󣬲��������ȡ����ͻ��ʧ���Ч��
                //
                GraphicsUnit old = e.Graphics.PageUnit;
                e.Graphics.PageUnit = GraphicsUnit.Pixel;
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;                       //<---
                g.DrawImage(memBmp, new Rectangle(0, 50, 600, 200), new Rectangle(0, 0, 150, 50), GraphicsUnit.Pixel);  //<---
            }

        }
    }
}