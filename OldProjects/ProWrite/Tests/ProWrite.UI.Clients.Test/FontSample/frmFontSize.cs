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
    public partial class frmFontSize : Form
    {
        public frmFontSize()
        {
            InitializeComponent();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            // Create transform matrix.
            Matrix transformMatrix = new Matrix();

            // Translate matrix, prepending translation vector.
            transformMatrix.Translate(500.0F, 500.0F);

            // Rotate transformation matrix of graphics object,

            // prepending rotation matrix.
            e.Graphics.RotateTransform(30.0F);

            // Multiply (prepend to) transformation matrix of

            // graphics object to translate graphics transformation.
            e.Graphics.MultiplyTransform(transformMatrix);

            // Draw rotated, translated ellipse.
            //e.Graphics.DrawEllipse(new Pen(Color.Blue, 3), -80, -40, 160, 80);

            Brush brush = new SolidBrush(Color.Black);
            string _durationTxt = "A";
            Font font = new Font(this.Font.Name, 10.0f, FontStyle.Regular, GraphicsUnit.Pixel);

            e.Graphics.DrawString("1", font, brush, 0, 0);

        }
    }
}