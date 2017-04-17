using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.DataProviders;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using ProWrite.DES;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class CreateVideoMessage : Form
    {
        public CreateVideoMessage()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DataProvider provider = new DataProvider();
            ProjectInfo project = provider.Get();
            MessageInfo msg = project.LibraryGroups[0].Messages.GetByName("s");
            string fileName = "d:\\1.mpg";
            if (DESHelper.CreateVideo(msg, fileName))
                MessageBox.Show("successful!");
        }
    }
}
