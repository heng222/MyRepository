using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ProWrite.UI.Controls; 
namespace ProWrite.UI.Clients.Test
{
    public partial class FrmImageTest : Form
    {
        public FrmImageTest()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();//.ShowModalDialog();
            if (result == DialogResult.OK || result == DialogResult.Yes)
            {
                using (Stream stream = openFileDialog1.OpenFile())
                {
                    Image image = Image.FromStream(stream);
                    if (pictureBox1.Image != null)
                    {
                        pictureBox1.Image.Dispose();
                        pictureBox1.Image = null;
                    }
                    pictureBox1.Image = image;
                }
            }
        }
    }
}
