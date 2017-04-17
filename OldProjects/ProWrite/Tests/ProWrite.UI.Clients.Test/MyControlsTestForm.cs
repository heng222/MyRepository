using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls;
using ProWrite.Entity.Settings;
using ProWrite.Core;

namespace ProWrite.UI.Clients.Test
{
	public partial class MyControlsTestForm : DevExpress.XtraEditors.XtraForm
	{
		public MyControlsTestForm()
		{
			InitializeComponent();
		}

		private void simpleButton1_Click(object sender, EventArgs e)
		{
            TemplateGroup test = new TemplateGroup();
            test = CloneManager.Clone<TemplateGroup>(TemplateGroup.Default);
            test.Sign.Height = 210;
            //List<string> names = new List<string>();
            //names.Add("AAAA");
            //names.Add("BBBB");
            //names.Add("CCCC");
            //names.Add("DDDD");
            //names.Add("EEEE");
            //names.Add("FFFFF");
            //names.Add("GGGGG");
            //ListForm listForm = new ListForm("NameList", names);
            //if(listForm.ShowDialog() == DialogResult.OK)
            //{
            //    labelControl1.Text = listForm.SelectedName; 
            //}

		}
	}
}