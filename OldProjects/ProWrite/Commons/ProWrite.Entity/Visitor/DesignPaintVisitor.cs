using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using ProWrite.Unsafe;
using System.Drawing.Drawing2D;
using ProWrite.Core;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Communication;

namespace ProWrite.Entity.Shape
{
    //设计时绘制访问器
    public class DesignPaintVisitor:IDesignPaintVisitor
    {
        public System.Drawing.Graphics Graphics { get; set; }
        public int Zoom { get; set; }

        protected virtual Graphics GetGraphics(ShapeBase shape)
        {
            return Graphics;
        }

        public void VisitLabel(ShapeLabel shape)
        {
            if (shape.Text != null && shape.Text.Length > 0)
            {
                if (shape.IsChanged || shape.LabelImage == null) //has new text paint shape
                {
                    if (shape.FrameSizeFixed)
                        shape.FontMgrSetup(true, false, ShapeLabel.DrawMode.Normal);
                    else
                        shape.FontMgrSetup(true, true, ShapeLabel.DrawMode.Normal);

                    shape.PaintImageInShape(Graphics);
                    shape.IsChanged = false;
                }
                else
                {
                    Graphics.DrawImage(shape.LabelImage, new Rectangle(shape.VirtualInnerBounds.X - shape.BorderWidth, shape.VirtualInnerBounds.Y - shape.BorderWidth, shape.LabelImage.Width, shape.LabelImage.Height));
                }
            }

        }

        public void VisitDownArrow(ShapeDownArrow downArrow)
        {
            PaintFigure(downArrow);
        }

        public void VisitShapeDraw(ShapeDraw shapeDraw)
        {
            if (shapeDraw.BackColor != Color.Empty)
                ShapePaintHelper.FillRectangle(Graphics, ResourceCache.DefaultCache.GetSolidBrush(shapeDraw.BackColor), shapeDraw.VirtualBounds);
        }

        #region Paint

        private void PaintFigure(ShapeFigure shape)
        {
            InterpolationMode oldmode = Graphics.InterpolationMode;
            Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;

            using (Image smallImg = CreateShapeImage(shape, shape.VirtualBounds, shape.BorderWidth * shape.Zoom))
            using (Image virtualImg = ImageHelper.ReSizeImage(smallImg, shape.VirtualBounds.Width, shape.VirtualBounds.Height))
            using (ImageAttributes imgAttri = new ImageAttributes())
            {
                imgAttri.SetColorKey((Color)shape.TranColor, (Color)shape.TranColor);
                Graphics.DrawImage(virtualImg, shape.VirtualBounds, 0, 0, shape.VirtualBounds.Width, shape.VirtualBounds.Height, GraphicsUnit.Pixel, imgAttri);
                Graphics.InterpolationMode = oldmode;
            }
        }

        private static Image CreateShapeImage(ShapeFigure shape, Rectangle innbounds, int borderwidth)
        {
            innbounds.Width = innbounds.Width < shape.Zoom ? shape.Zoom : innbounds.Width;
            innbounds.Height = innbounds.Height < shape.Zoom ? shape.Zoom : innbounds.Height;
            Rectangle adjRect = new Rectangle(0, 0, innbounds.Width, innbounds.Height);
            int w = adjRect.Width / shape.Zoom < 1 ? 1 : adjRect.Width / shape.Zoom;
            int h = adjRect.Height / shape.Zoom < 1 ? 1 : adjRect.Height / shape.Zoom;

            using (Image img = new Bitmap(innbounds.Width + 1, innbounds.Height + 1))
            {
                using (Graphics g = Graphics.FromImage(img))
                    PaintFigure(g, adjRect, shape, borderwidth);
                return ImageHelper.ReSizeImage(img, w, h);
            }
        }

        private static void PaintFigure(Graphics g, RectangleF innbounds, ShapeFigure shape, int borderwidth)
        {
            using (GraphicsPath gp = new GraphicsPath())
            {
                switch (shape.Type)
                {
                    case ShapeType.Rectangle:
                        gp.AddRectangle(ShapePaintHelper.GetNormalizedRectangle(Rectangle.Round(innbounds)));
                        break;
                    case ShapeType.Ellipse:
                        gp.AddEllipse(ShapePaintHelper.GetNormalizedRectangle(Rectangle.Round(innbounds)));
                        break;
                    case ShapeType.UpArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Up));
                        break;
                    case ShapeType.DownArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Down));
                        break;
                    case ShapeType.RightArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Right));
                        break;
                    case ShapeType.LeftArrow:
                        gp.AddPolygon(Rect2PointFArray(Rectangle.Round(innbounds), ArrowDirection.Left));
                        break;
                    default:
                        return;
                }
                if (shape.Filled)
                    g.FillPath(ResourceCache.DefaultCache.GetSolidBrush(shape.FillColor), gp);

                using (Pen pen = ResourceCache.DefaultCache.GetPen(shape.BorderColor, borderwidth, PenAlignment.Inset, shape.LineDashStyle))
                    g.DrawPath(pen, gp);
            }
        }


        protected static PointF[] Rect2PointFArray(RectangleF rectf, ArrowDirection arrowDirection)
        {
            List<PointF> list = new List<PointF>();

            switch (arrowDirection)
            {
                case ArrowDirection.Up:
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Bottom));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Bottom));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    break;
                case ArrowDirection.Down:
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.Right - rectf.Width / 4, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 4, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    break;
                case ArrowDirection.Left:
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.Right, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    break;
                case ArrowDirection.Right:
                    list.Add(new PointF(rectf.Right, rectf.Y + rectf.Height / 2));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X, rectf.Y + rectf.Height / 4));
                    list.Add(new PointF(rectf.X, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom - rectf.Height / 4));
                    list.Add(new PointF(rectf.X + rectf.Width / 2, rectf.Bottom));
                    break;
            }

            PointF[] array = new PointF[list.Count];
            list.CopyTo(array);

            return array;
        }
       
        #endregion

        public void VisitDynamicText(ShapeDynamicText dynamicText)
        {
            VisitDynamic(dynamicText);
        }

        private void VisitDynamic(ShapeDynamicTextBase dynamicText)
        {
            try
            {
                if (dynamicText.IsChanged)
                {
                    dynamicText.BeginEdit();
                    dynamicText.DrawString(false);
                    dynamicText.EndEdit();

                    dynamicText.Font.FontFileName = dynamicText.FontMgr.FontFileName;
                    if (dynamicText.FixedMode == SizeFixedMode.Frame)
                        dynamicText.Font.Size = dynamicText.FontMgr.FontHeight / Zoom;

                    if (dynamicText.FontMgr.Bold)
                        dynamicText.Font.Style = dynamicText.Font.Style | FontStyle.Bold;
                    else
                        dynamicText.Font.Style = dynamicText.Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline) ^ FontStyle.Bold);

                    if (dynamicText.FontMgr.Italic)
                        dynamicText.Font.Style = FontStyle.Italic;
                    else
                        dynamicText.Font.Style = dynamicText.Font.Style & ((FontStyle.Bold | FontStyle.Italic | FontStyle.Strikeout | FontStyle.Underline) ^ FontStyle.Italic);
                    dynamicText.IsChanged = false;
                }
                if (dynamicText.BitmapOverlay == null)
                {
                    dynamicText.DrawString(false);
                }
                else
                {
                    Graphics.DrawImage(dynamicText.BitmapOverlay, dynamicText.VirtualBounds);
                }
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
        }

        public void VisitDynamicVideo(ShapeDynamicVideo dynamicVideo)
        {
            Color c = SignTypeHandler.ConvertColor(Color.White, dynamicVideo.SignType);
            string str = string.IsNullOrEmpty(dynamicVideo.DataSource) ? "No Source" : dynamicVideo.DataSource;
            using (Brush b = new SolidBrush(c))
            {
                Graphics.DrawString(str, new Font("Tahoma", 16), b, dynamicVideo.VirtualBounds);
            }
        }

        public void VisitEllipse(ShapeEllipse ellipse)
        {
            PaintFigure(ellipse);
        }

        public void VisitImage(ShapeImage image)
        {
            Rectangle bounds = image.VirtualBounds;
            var result = image.PaintImage(Graphics, ref bounds, false);

            if (image.SizeMode == PictureBoxSizeType.StretchImage)
                image.DestBounds = bounds;
            image.VirtualBounds = bounds;
        }

        public void VisitLeftArrow(ShapeLeftArrow leftArrow)
        {
            PaintFigure(leftArrow);
        }

        public void VisitLine(ShapeLine line)
        {
             int w = line.BorderWidth * Zoom;
            Color drawColor = line.BorderColor;
            if (drawColor == Color.Black)
                drawColor = Color.FromArgb(255, 1,255, 1);

            using (Image tmpimg = GenerateLineImage(line))
            {
                InterpolationMode oldmode = Graphics.InterpolationMode;
                Graphics.InterpolationMode = InterpolationMode.NearestNeighbor;
                Graphics.DrawImage(tmpimg, line.VirtualBounds, 0, 0, tmpimg.Width, tmpimg.Height, GraphicsUnit.Pixel);
                Graphics.InterpolationMode = oldmode;
            }
        }

        private Image GenerateLineImage(ShapeLine line)
        {
            int w = line.VirtualBounds.Width / Zoom;
            int h = line.VirtualBounds.Height / Zoom;

            using (Image lineImg = new Bitmap(w == 0 ? 1 : w, h == 0 ? 1 : h))
            using (Graphics gh = Graphics.FromImage(lineImg))
            using (var pen = ResourceCache.DefaultCache.GetPen(line.DrawingColor, line.BorderWidth, PenAlignment.Inset, line.LineDashStyle))
            {
                gh.Clear(Color.Transparent);
                gh.DrawLine(pen, line.RelationStart, line.RelationEnd);
                return line.FormatImage(lineImg, line.VirtualBounds);
            }
        }


        public void VisitRectangle(ShapeRectangle rectangle)
        {
            PaintFigure(rectangle);
        }

        public void VisitRightArrow(ShapeRightArrow rightArrow)
        {
            PaintFigure(rightArrow);
        }

        public void VisitTemp(ShapeTemp temp)
        {
            VisitDynamic(temp);
        }

        public void VisitTime(ShapeTime time)
        {
            VisitDynamic(time);
        }

        public void VisitUpArrow(ShapeUpArrow upArrow)
        {
            PaintFigure(upArrow);
        }

        public void VisitVideo(ShapeVideo video)
        {
            Rectangle bounds = video.VirtualBounds;
            video.DestBounds = video.PaintImage(Graphics, ref bounds, false);
            video.VirtualBounds = bounds;
        }
    }
}
