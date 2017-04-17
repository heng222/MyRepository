using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class GetStatus : XtraForm
    {
        public GetStatus(SignInfo sign)
        {
            InitializeComponent();
            string filePath = Constance.AppPath + sign.Name + ".xml";
            this.webBrowser1.Url = new System.Uri(filePath, System.UriKind.Absolute);
        }
    }
}
