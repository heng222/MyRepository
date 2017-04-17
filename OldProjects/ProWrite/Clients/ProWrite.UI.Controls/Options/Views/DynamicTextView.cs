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
    public partial class DynamicTextView :ViewBase<ProWrite.Entity.Settings.ShapeMarqueeTemplate>
    {
        public DynamicTextView()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            e.Graphics.DrawString("Dynamic text", Font, Brushes.Red, new PointF(200, 200));
        }
    }
}
