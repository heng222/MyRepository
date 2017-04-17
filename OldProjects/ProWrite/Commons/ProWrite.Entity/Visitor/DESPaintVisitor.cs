using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using ProWrite.Unsafe;
using ProWrite.Core;
using ProWrite.Entity.Shape.Visitor;

namespace ProWrite.Entity.Shape
{
    //DES 播放时绘制访问器
    public class DESPaintVisitor : VisitorAdapter,IDESPaintVisitor
    {
        private ShapeLayer Layer;
        private int Zoom; 

        public void VisitLayer(ShapeLayer layer)
        {
            Layer = layer;

            if (!layer.IsVisible)
                return;

            if (layer.StartTime > layer.EndTime)
                return;

            if (layer.Shape != null)
            {
                Zoom = layer.Shape.Zoom;

                //TODO:
                //DrawMode = DESDrawMode;

                layer.Shape.Accept(this);
            }
        }

        protected virtual Graphics GetGraphics()
        {
            ShapeBase shape = Layer.Shape;
            int width = shape.VirtualBounds.Width;
            int height = shape.VirtualBounds.Height;
            if (DrawMode == DESDrawMode.Sign)
            {
                width = shape.SignSize.Width * Zoom;
                height = shape.SignSize.Height * Zoom;
            }

            shape.InnerImage  = new Bitmap(width, height);

            return Graphics.FromImage(shape.InnerImage);
        }

        private Rectangle GetFrameBounds(ShapeImage shape)
        {
            int width = shape.VirtualBounds.Width;
            int height = shape.VirtualBounds.Height;
            if (DrawMode == DESDrawMode.Sign)
            {
                width = shape.SignSize.Width * Zoom;
                height = shape.SignSize.Height * Zoom;
            }

            return new Rectangle(0, 0, width, height);
        }

        private enum DESDrawMode
        {
            Layer,
            Sign,
        }

        private DESDrawMode DrawMode = DESDrawMode.Layer;

        public override void VisitLabel(ShapeLabel shape)
        {
            if ( !shape.IsChanged
                || string.IsNullOrEmpty(shape.Text))
                return;

            if (shape.LabelImage == null) //has new text paint shape
            {
                if (shape.FrameSizeFixed)
                    shape.FontMgrSetup(true, false, ProWrite.Entity.Shape.ShapeLabel.DrawMode.Play);
                else
                    shape.FontMgrSetup(true, true, ProWrite.Entity.Shape.ShapeLabel.DrawMode.Play);

                using(var g = GetGraphics())
                    shape.PaintImageInShape(g);
                shape.IsChanged = false;
            }
            else
            {
                using(var g = GetGraphics())
                    g.DrawImage(shape.LabelImage, new Rectangle(shape.VirtualInnerBounds.X - shape.BorderWidth, shape.VirtualInnerBounds.Y - shape.BorderWidth, shape.LabelImage.Width, shape.LabelImage.Height));
            }

            if (shape.LabelImage != null)
            {
                using (Bitmap bit = new Bitmap(shape.LabelImage))
                    shape.InnerImagePath = shape.SaveImage(bit);
            }
            shape.IsChanged = true;
        }

        public override void VisitShapeDraw(ShapeDraw shapeDraw)
        {
            shapeDraw.ComputerBounds();
            using (Graphics innerGraphics = GetGraphics())
            {
                innerGraphics.Clear(Color.Transparent);
                foreach (ShapePaint shape in shapeDraw.Childs)
                    shape.PaintFigure(innerGraphics, shapeDraw.VirtualBounds);
            };

            int w = shapeDraw.InnerImage.Width / Zoom;
            int h = shapeDraw.InnerImage.Height / Zoom;
            w = w < 1 ? 1 : w;
            h = h < 1 ? 1 : h;

            Image smallImg = ImageHelper.ReSizeImage(shapeDraw.InnerImage, w, h);
            shapeDraw.InnerImage.Dispose();
            shapeDraw.InnerImage = null;
            shapeDraw.InnerImage = ImageHelper.ReSizeImage(smallImg, shapeDraw.Width, shapeDraw.Height);

            smallImg.Dispose();
            smallImg = null;
            shapeDraw.InnerImagePath = shapeDraw.SaveImage(shapeDraw.InnerImage);

            shapeDraw.InnerImage.Dispose();
            shapeDraw.InnerImage = null;
        }

        private void VisitDynamic(ShapeDynamicTextBase dynamic)
        {
            if (string.IsNullOrEmpty(dynamic.Text))
                return;

            var hideGrid = true;
            var FontMgr = dynamic.FontMgr;

            FontMgr.ShowGrid = !hideGrid;
            FontMgr.ScaleIndex = Zoom;
            FontMgr.SetStyle(dynamic.IsFrameSizeFixed, dynamic.IsFontSizeFixed);
            FontMgr.TextColor = dynamic.ConveredForeColor(Layer.Shape.SignType);//.ForeColor;
            FontMgr.BackColor = dynamic.ConveredBackColor(Layer.Shape.SignType);//.BackColor;
            FontMgr.FontName = dynamic.Font.Name;
            FontMgr.FontHeight = dynamic.Font.Size * Zoom;
            FontMgr.Alignment = dynamic.Align;
            FontMgr.LineAlignment = dynamic.Valign;
            FontMgr.Bold = (dynamic.Font.Style & FontStyle.Bold) == FontStyle.Bold;
            FontMgr.Italic = (dynamic.Font.Style & FontStyle.Italic) == FontStyle.Italic;
            FontMgr.SignSize = new Size(dynamic.SignSize.Width * Zoom - 2, dynamic.SignSize.Height * Zoom - 2);
            FontMgr.FrameSize = DrawMode == DESDrawMode.Sign ? FontMgr.SignSize : dynamic.VirtualBounds.Size;
            FontMgr.Text = dynamic.Text;

            List<Image> imagesActual = new List<Image>();
            List<Image> images = new List<Image>();
            List<string> strings = new List<string>();

            FontMgr.GenerateBmps(imagesActual, images, strings);


            if (images.Count > 0)
            {
                dynamic.BitmapOverlay = images[0];
                dynamic.InnerImage = new Bitmap(dynamic.BitmapOverlay);
            }

            if (dynamic.BitmapOverlay != null)
                dynamic.InnerImagePath = dynamic.SaveImage(dynamic.BitmapOverlay);
            dynamic.IsChanged = true;
        }

        public override void VisitDynamicText(ShapeDynamicText dynamicText)
        {
            VisitDynamic(dynamicText);
        }

        public override void VisitImage(ShapeImage shape)
        {

            if (shape.DestBounds.Size == SizeF.Empty) return;

            if (shape._Image == null) shape._Image = IOHelper.GetImageFromFile(shape.ImageUrl);

            if (shape._Image != null)
            {
                shape.UpdateDestBounds();
                shape.DestBounds = new Rectangle(shape.DestBounds.X, shape.DestBounds.Y, shape.DestBounds.Width + 2, shape.DestBounds.Height);

                shape.InnerImage = shape.FormatImage(shape._Image, shape.DestBounds, GetFrameBounds(shape));
            }
            using (var g = Graphics.FromImage(shape.InnerImage))
                SignTypeHandler.SetOutChannel(g, shape.InnerImage, shape.SignType, new RectangleF(PointF.Empty, new SizeF(shape.InnerImage.Width, shape.InnerImage.Height)), new RectangleF(PointF.Empty, new SizeF(shape.InnerImage.Width, shape.InnerImage.Height)));

            shape.InnerImagePath = shape.SaveImage(shape.InnerImage);
        }

        public override void VisitTemp(ShapeTemp temp)
        {
            VisitDynamic(temp);
        }

        public override void VisitTime(ShapeTime time)
        {
            VisitDynamic(time);
        }
    }
}
