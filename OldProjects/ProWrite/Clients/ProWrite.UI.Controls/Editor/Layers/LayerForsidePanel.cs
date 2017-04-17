using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.Entity.Shape;
using ProWrite.Resources;

namespace ProWrite.UI.Controls.Editor.Layers
{
    public class LayerForsidePanel : Control
    {
        private ShapeLayer _layer;

        private class _
        {
            public const int Height = 27;
            public static readonly Rectangle IsVisible = new Rectangle(1, 1, 30, 23);
            public static readonly Rectangle LayerType = new Rectangle(32, 1, 30, 23);
            public static readonly Rectangle LayerName = new Rectangle(64, 1, 136, 23);
        }

        public LayerForsidePanel(ShapeLayer layer)
        {
            _layer = layer;
            this.AllowDrop = true;
            this.Height = _.Height;
            this.Dock = DockStyle.Top;
            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            Graphics g = e.Graphics;

            if (_layer.IsVisible)
                g.DrawImage(LayerControl.Images.ImageList[LayerControl.Images.Visible], _.IsVisible);
            else
                g.DrawRectangle(Pens.Black, _.IsVisible);

            g.DrawImage(LayerControl.Images.ImageList[(int)_layer.Shape.LayerType], _.LayerType);
            g.DrawRectangle(Pens.Black, _.LayerName);
            SizeF sf = g.MeasureString(_layer.Name, Font);

            StringFormat stringFmt = new StringFormat();
            stringFmt.Alignment = StringAlignment.Center;
            stringFmt.LineAlignment = StringAlignment.Center;

            g.DrawString(_layer.Name, Font, new SolidBrush(Color.ForestGreen), new Rectangle(_.LayerName.Location, sf.ToSize()), stringFmt);
        }


        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);

            if (e.Button == MouseButtons.Left)
            {
                if (_.IsVisible.Contains(e.Location))
                {
                    _layer.IsVisible = !_layer.IsVisible;
                    Invalidate(_.IsVisible);
                }
            }
        }
    }
}
