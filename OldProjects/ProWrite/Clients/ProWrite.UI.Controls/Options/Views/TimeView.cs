using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class TimeView : ViewBase<ProWrite.Entity.Settings.ShapeTimeTemplate>
    {
        public TimeView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Time", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            txtHeight.Text = _data.Height.ToString();
            txtWidth.Text = _data.Width.ToString();
            ddlDisplayFormat.SelectedItem = _data.DisplayFormat;
            ddlFitToSign.SelectedItem = _data.FitToSign;
            colorFore.Color = _data.ForeColor;
        }

        protected override void DoUpdateData()
        {
            _data.Height = Convert.ToInt32(txtHeight.Text);
            _data.Width = Convert.ToInt32(txtWidth.Text);
            _data.DisplayFormat = (TimeFormat)Enum.Parse(typeof(TimeFormat), ddlDisplayFormat.SelectedItem.ToString());
            _data.FitToSign = Boolean.Parse(ddlFitToSign.Text);
            _data.ForeColor = colorFore.Color;
        }
    }
}
