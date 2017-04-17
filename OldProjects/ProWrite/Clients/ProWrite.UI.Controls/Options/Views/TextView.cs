using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class TextView : ViewBase<ProWrite.Entity.Settings.ShapeLabelTemplate>
    {
        public TextView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Text", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            txtHeight.Text= _data.Height.ToString();
            txtWidth.Text = _data.Width.ToString();
            colorBackGround.Color = _data.BackGroundColor;
            ddlFitToSign.SelectedItem = _data.FitToSign;
            colorFore.Color = _data.ForeColor;
        }

        protected override void DoUpdateData()
        {
            _data.Height = Convert.ToInt32(txtHeight.Text);
            _data.Width = Convert.ToInt32(txtWidth.Text);
            _data.BackGroundColor = colorFore.Color;
            _data.FitToSign = Boolean.Parse(ddlFitToSign.Text);
            _data.ForeColor = colorFore.Color;
        }
    }
}
