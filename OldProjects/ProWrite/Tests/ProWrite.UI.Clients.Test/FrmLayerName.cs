using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.Core;

namespace ProWrite.UI.Clients.Test
{
    public partial class FrmLayerName : Form
    {
        private LayerNameControlNew lblLayerName;
        public FrmLayerName()
        {
            InitializeComponent();
            lblLayerName = new LayerNameControlNew();
            lblLayerName.Location = Point.Empty;
            lblLayerName.Parent = this;
        }

        private void FrmLayerName_Load(object sender, EventArgs e)
        {
            
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            SignInfo sign = new SignInfo();
            textEdit2.Text = TemplateGroup.Default.Sign.Height.ToString();
            sign.Template = CloneManager.Clone<TemplateGroup>(TemplateGroup.Default);
            sign.Template.Sign.Height = Convert.ToInt32(textEdit1.Text);
            bool b =sign.Template==TemplateGroup.Default;
            int i = TemplateGroup.Default.Sign.Height;
        }
    }
}