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
    public partial class frmFontZoom3 : Form
    {
        public frmFontZoom3()
        {
            InitializeComponent();
        }

        private void FontZoomForm3_Load(object sender, EventArgs e)
        {
            Graphics g = this.pictureBox1.CreateGraphics();
            g.SmoothingMode = SmoothingMode.HighQuality;
            GraphicsPath path = new GraphicsPath();

            StringFormat strformat = new StringFormat();
            strformat.Alignment = StringAlignment.Center;
            strformat.LineAlignment = StringAlignment.Center;
            path.AddString("Ðù", new FontFamily("ºÚÌå"), (int)this.Font.Style, 400f, new Point(250, 250), strformat);

            g.FillPath(new SolidBrush(Color.Red), path);
            
        }
    }
}