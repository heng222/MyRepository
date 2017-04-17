//---------------------------------------------------------------------
//
// File: ContainerPaint.cs
//
// Description:
// Container Paint class 
//
// Author: Kevin
//
// Modify history:
//      Kevin  2008-6-19 Ç¨ÒÆ
//      Kevin  2008-6-23 Add comments
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Editor
{
	/// <summary>
	/// Summary description for ContainerDrawer.
	/// </summary>
	public class ShapeControlPaintNew
	{
		public static void DrawActiveBorder(Graphics g, Canvas ctrl)
		{
			DrawContainerBorder(g, ctrl, SystemColors.Highlight);
		}

		public static void EraseActiveBorder(Graphics g, Canvas ctrl)
		{
			DrawContainerBorder(g, ctrl, ctrl.BackColor);
		}

		public static void DrawReversibleBorder(Canvas ctrl)
		{
			DrawContainerBorder(null, ctrl, Color.Empty);
		}

		private static void DrawContainerBorder(Graphics g, Canvas ctrl, Color borderColor)
		{
			int borderWidth = 0;
			float orgiZoom = 1.0f;

			borderWidth = Canvas.FocusBorderWidth;
			//orgiZoom = container.Zoom;


			if (g == null && borderColor == Color.Empty)
			{
				Color backColor = SystemColors.HighlightText;
				int halfBoderWidth = borderWidth/2;
				Point tl = new Point(halfBoderWidth, halfBoderWidth);
				Point tr = new Point(ctrl.Width - halfBoderWidth, halfBoderWidth);
				Point bl = new Point(halfBoderWidth, ctrl.Height - halfBoderWidth);
				Point br = new Point(ctrl.Width - halfBoderWidth, ctrl.Height - halfBoderWidth);
				tl = ctrl.PointToScreen(tl);
				tr = ctrl.PointToScreen(tr);
				bl = ctrl.PointToScreen(bl);
				br = ctrl.PointToScreen(br);
				ControlPaint.DrawReversibleLine(tl, tr, backColor);
				ControlPaint.DrawReversibleLine(tl, bl, backColor);
				ControlPaint.DrawReversibleLine(tr, br, backColor);
				ControlPaint.DrawReversibleLine(bl, br, backColor);
				return;
			}

			GraphicsUnit oldGU = g.PageUnit;
			g.PageUnit = GraphicsUnit.Pixel;
			float zoom = 1f/orgiZoom;
			g.ScaleTransform(zoom, zoom);

			if (borderColor != Color.Empty)
			{
				using (Pen pen = new Pen(borderColor, borderWidth))
				{
					pen.DashStyle = DashStyle.Dot;
					pen.DashStyle = DashStyle.Dot;
					g.DrawRectangle(pen, borderWidth/2, borderWidth/2,
					                ctrl.Width - borderWidth, ctrl.Height - borderWidth);
				}
			}

			g.PageUnit = oldGU;
			g.ScaleTransform(orgiZoom, orgiZoom);
		}

		public static void DrawReversibleRectangle(Rectangle rect)
		{
			Point tl = rect.Location;
			Point tr = new Point(rect.Right, rect.Top);
			Point bl = new Point(rect.Left, rect.Bottom);
			Point br = new Point(rect.Right, rect.Bottom);
			Color backColor = SystemColors.ControlText;
			int spacing = 3;
			DrawReversibleLineEx(tl, tr, backColor, spacing);
			DrawReversibleLineEx(tl, bl, backColor, spacing);
			DrawReversibleLineEx(tr, br, backColor, spacing);
			DrawReversibleLineEx(bl, br, backColor, spacing);
		}

		private static void DrawReversibleLineEx(Point A, Point B, Color backColor, int spacing)
		{
			float offsetX, offsetY;
			offsetX = B.X - A.X;
			offsetY = B.Y - A.Y;
			float distance = (float) Math.Sqrt(offsetX*offsetX + offsetY*offsetY);
			float deltaX, deltaY;
			deltaX = offsetX/distance*spacing;
			deltaY = offsetY/distance*spacing;

			for (int i = 0; i < distance/spacing; ++i)
			{
				if (i/2*2 != i) continue;
				PointF a, b;
				a = new PointF(A.X + deltaX*i, A.Y + deltaY*i);
				b = new PointF(A.X + deltaX*(i + 1), A.Y + deltaY*(i + 1));

				ControlPaint.DrawReversibleLine(Point.Round(a), Point.Round(b), backColor);
			}
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
		
	}

}