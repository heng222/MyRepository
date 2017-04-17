using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmCCOM : Form
    {
        public frmCCOM()
        {
            InitializeComponent();
        }

        private void Form15_Load(object sender, EventArgs e)
        {
            
        }

        private void Form15_Paint(object sender, PaintEventArgs e)
        {
            //Image image = null;
            //FONTBMPLib.GenerateBmpClass a = new FONTBMPLib.GenerateBmpClass();
            //image = Image.FromHbitmap(a.GenerateBmp("ABC"));
            //Graphics g = e.Graphics;
            //g.DrawImage(image, new Point(0, 0));
            //g.Dispose();
            Image image = null;
			//FONTBMPLib.GenerateBmpClass a = new FONTBMPLib.GenerateBmpClass();
			//image = Image.FromHbitmap(a.GenerateBmp("ABC"));
            Graphics g = e.Graphics;
            g.DrawImage(image, new Point(0, 0));
            g.Dispose();
        }
    }
}
