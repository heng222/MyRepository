using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Settings;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class SignView : ViewBase<SignTemplateInfo>
    {
       
        public SignView()
        {
            InitializeComponent();
        }

        protected override bool ValidateData()
        {
            return base.ValidateData();
        }

        protected override void DoBind()
        {
            btSignImage.Text = _data.Image;
            txtWidth.Text = _data.Width.ToString();
            txtHeight.Text = _data.Height.ToString();
            ddlSignType.SelectedItem = _data.SignType;
        }

        protected override void DoUpdateData()
        {
            _data.Image = btSignImage.Text;
            _data.Width = int.Parse(txtWidth.Text);
            _data.Height = int.Parse(txtHeight.Text);
            _data.SignType = EnumHelper.Parse<SignType>(ddlSignType.SelectedItem as string);
        }

        private void btSignImage_Click(object sender, EventArgs e)
        {

        }
       
    }
}
