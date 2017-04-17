using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ProWrite.Core;
using System.Configuration;


namespace ProWrite.UI.Controls
{
    public partial class ShowAgreement : Form
    {
        public ShowAgreement()
        {
            InitializeComponent();
            Init();
        }
        private void Init()
        {
            try
            {
                //var config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
                //config.AppSettings.Settings.Add("A", "123");
                //config.Save();

                richTextBox1.LoadFile(Constance.AppPath + ConfigurationManager.AppSettings["PWLicense"]);//("../Clients/ProWrite.App/PWLicense.rtf");
            }
            catch { }
        }
    }
}
