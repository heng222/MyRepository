using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;

namespace ProWrite.UI.Controls.Options.Views
{
    public partial class PaintView :ViewBase<ProWrite.Entity.Settings.ShapeFigureTemplate>
    {
        public PaintView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Paint", Font, Brushes.Red, new PointF(200, 200));
        }

        protected override void DoBind()
        {
            colorLine.Color = _data.LineColor;
            ddlDashStyle.SelectedItem = _data.LineDashKind;
            spinWidth.Value = _data.LineWidth;
        }

        protected override void DoUpdateData()
        {
            _data.LineWidth = Convert.ToInt32(spinWidth.Value);
            _data.LineDashKind = (DashKind)Enum.Parse(typeof(DashKind), ddlDashStyle.SelectedItem.ToString());
            _data.LineColor = colorLine.Color;
        }
    }
}
