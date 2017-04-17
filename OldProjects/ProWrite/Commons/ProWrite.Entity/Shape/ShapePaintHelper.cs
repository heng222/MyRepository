using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using ProWrite.Entity.Shape;
using System.Runtime.InteropServices;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Summary description for ShapePaint.
	/// // 2008-6-19, Kevin Ç¨ÒÆ
	/// </summary>
	public class ShapePaintHelper
	{
		private ShapePaintHelper()
		{
		}

		/// <summary>
		/// Draw Selected Border
		/// </summary>
		/// <param name="g"></param>
		/// <param name="rect"></param>
		/// <param name="showPoints">if show the showPoints</param>
		/// <returns></returns>
        public static Rectangle[] DrawSelectedBorder(Graphics g, Rectangle rect, bool showPoints)
        {
            Rectangle[] blocks = new Rectangle[8];
            Matrix m = g.Transform;
            g.ResetTransform();
            Pen pen = ResourceCache.DefaultCache.GetPen(SystemColors.Highlight, 2, PenAlignment.Inset, DashStyle.Dot);
            DrawRectangle(g, pen, rect);

            // draw drag blocks
            Rectangle rectBlock = rect;
            int halfSize = ShapeBase.DragBlockSize / 2;
            rectBlock.Inflate(halfSize, halfSize);

            if (showPoints)
            {
                Point[] points = new Point[8];
                points[0] = rectBlock.Location;
                points[1] = new Point(rectBlock.Left + rectBlock.Width / 2, rectBlock.Top);
                points[2] = new Point(rectBlock.Right, rectBlock.Top);
                points[3] = new Point(rectBlock.Right, rectBlock.Top + rectBlock.Height / 2);
                points[4] = new Point(rectBlock.Right, rectBlock.Bottom);
                points[5] = new Point(points[1].X, rectBlock.Bottom);
                points[6] = new Point(rectBlock.Left, rectBlock.Bottom);
                points[7] = new Point(rectBlock.Left, points[3].Y);

                var brush = ResourceCache.DefaultCache.GetSolidBrush(SystemColors.ControlText);
                var borderPen = ResourceCache.DefaultCache.GetPen(SystemColors.Highlight, 2);
                for (int i = 0; i < points.Length; ++i)
                {
                    Point point = points[i];
                    blocks[i] = new Rectangle(new Point(point.X - halfSize, point.Y - halfSize),
                                               new Size(ShapeBase.DragBlockSize, ShapeBase.DragBlockSize));
                    g.FillRectangle(brush, blocks[i]);
                    DrawRectangle(g, borderPen, blocks[i]);
                }
            }

            DrawRectangle(g, pen, rect);
            g.Transform = m;

            return blocks;
        }

		private static SizeF GetPixelSizeF(Graphics g)
		{
			Matrix matrix = g.Transform;
			float zoomX = matrix.Elements[0];
			float zoomY = matrix.Elements[3];

			return new SizeF(1/zoomX, 1/zoomY);
		}

		public static void DrawRectangle(Graphics g, Pen pen, Rectangle rect)
		{
#if DEBUG
			g.DrawRectangle(pen, rect.X, rect.Y, rect.Width, rect.Height);
#else
			try
			{
				g.DrawRectangle(pen, rect.X, rect.Y, rect.Width, rect.Height);
			}
			catch
			{
			}
#endif
			
		}

		public static void FillRectangle(Graphics g, Brush brush, Rectangle rect)
		{
			g.FillRectangle(brush, rect.X, rect.Y, rect.Width, rect.Height);
		}

        public static Rectangle GetNormalizedRectangle(int x1, int y1, int x2, int y2)
        {
            if (x2 < x1)
            {
                int tmp = x2;
                x2 = x1;
                x1 = tmp;
            }

            if (y2 < y1)
            {
                int tmp = y2;
                y2 = y1;
                y1 = tmp;
            }
            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }

        public static Rectangle GetNormalizedRectangle(Point p1, Point p2)
        {
            return GetNormalizedRectangle(p1.X, p1.Y, p2.X, p2.Y);
        }

        public static Rectangle GetNormalizedRectangle(Rectangle r)
        {
            return GetNormalizedRectangle(r.X, r.Y, r.X + r.Width, r.Y + r.Height);
        }

        public static Rectangle GetRectangleFromTwoPoins(Point start, Point end)
        {
            return new Rectangle(start, new Size(end.X - start.X, end.Y - start.Y));
        }

       
  }
}