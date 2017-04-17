using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace ProWrite.UI.Controls.Playlist
{
    public partial class DragDropLine : Label
    {
        public DragDropLine()
        {
            InitializeComponent();
            this.AutoSize = false;
            //this.BackColor = Color.Black;
            //this.Height = 48;
        }

        public DragDropLine(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
        }

        private void DrawLine(Graphics g)
        {
            //Pen pen = new Pen(Color.Black, 2f);

            //g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            ////g.DrawRectangle(p, lb);

            ////source = new Rectangle(50, 50, 1,1);
            ////lb = new Rectangle(40, 40, 1, 1)
            //Point source = Point.Empty;
            //Point target = Point.Empty;


            ////
            //source = new Point(3, 10);
            //target = new Point(0, 0);
            //g.DrawLine(pen, source, target);

            ////
            //source = new Point(3, 10);
            //target = new Point(6, 0);
            //g.DrawLine(pen, source, target);

            ////
            //source = new Point(3, 70);
            //target = new Point(0, 80);
            //g.DrawLine(pen, source, target);

            ////
            //source = new Point(3, 70);
            //target = new Point(6, 80);
            //g.DrawLine(pen, source, target);

            ////pen = new Pen(Color.Black, 1);
            ////height 64 width:4
            //source = new Point(3, 10);
            //target = new Point(3, 70);
            //g.DrawLine(pen, source, target);
            

            int h = Height;

            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            //g.DrawRectangle(p, lb);

            //source = new Rectangle(50, 50, 1,1);
            //lb = new Rectangle(40, 40, 1, 1)
            Point source = Point.Empty;
            Point target = Point.Empty;

            using (Pen pen = new Pen(Color.Black, 1f))
            {
                //
                source = new Point(3, 10);
                target = new Point(0, 0);
                g.DrawLine(pen, source, target);

                //
                source = new Point(3, 10);
                target = new Point(6, 0);
                g.DrawLine(pen, source, target);

                //
                source = new Point(3, h - 10);
                target = new Point(0, h);
                g.DrawLine(pen, source, target);

                //
                source = new Point(3, h - 10);
                target = new Point(6, h);
                g.DrawLine(pen, source, target);

                //pen = new Pen(Color.Black, 1);
                //height 64 width:4
                source = new Point(3, 10);
                target = new Point(3, h - 10);
                g.DrawLine(pen, source, target);
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            DrawLine(e.Graphics);
        }
    }
}
