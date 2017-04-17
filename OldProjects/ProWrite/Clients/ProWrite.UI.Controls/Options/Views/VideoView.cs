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
    public partial class VideoView : ViewBase<ProWrite.Entity.Settings.ShapeVideoTemplate>
    {
        public VideoView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Video", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            txtHeight.Text = _data.Height.ToString();
            txtWidth.Text = _data.Width.ToString();
            ddlFitToSign.SelectedItem = _data.FitToSign;
        }

        protected override void DoUpdateData()
        {
            _data.FitToSign = Boolean.Parse(ddlFitToSign.Text);
            _data.Height = Convert.ToInt32(txtHeight.Text);
            _data.Width = Convert.ToInt32(txtWidth.Text);
        }
    }
}
