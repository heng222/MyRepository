using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
//using ProWrite.

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmImageButton : Form
    {
        public frmImageButton()
        {
            InitializeComponent();
            btnPlay.NormalImage = Resources.Resource.GetImage(Resources.Resource.Images.PlayNormal);
            btnPlay.HoverImage = Resources.Resource.GetImage(Resources.Resource.Images.PlayHover);
            btnPlay.PushedImage = Resources.Resource.GetImage(Resources.Resource.Images.PlayPush);
            btnPlay.DisabledImage = Resources.Resource.GetImage(Resources.Resource.Images.PlayDisable);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            btnPlay.Enabled = !btnPlay.Enabled;
            
        }        
    }
}