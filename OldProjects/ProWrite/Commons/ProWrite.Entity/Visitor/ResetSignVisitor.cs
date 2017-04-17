using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using System.Drawing;

namespace ProWrite.Entity.Shape.Visitor
{
    public interface IResetSignVisitor : IVisitor
    {
        SignInfo Sign { get; set; }
        void VisitMessage(MessageInfo message);
    }

    public class ResetSignVisitor : VisitorAdapter,IResetSignVisitor
    {
        public SignInfo Sign { get; set; }
        private MessageInfo Message;
        private int zoom;

        private ResetSignVisitor() { }

        public static readonly ResetSignVisitor Instance = new ResetSignVisitor();

        private Rectangle GetVirtualBoundsBySign(ShapeBase shape, Size signSize, int Zoom)
        {
            int width = signSize.Width / 4;
            int height = signSize.Height / 8;
            System.Drawing.Point location = System.Drawing.Point.Empty;

            decimal oldSizeRatio = decimal.Divide(shape.SignSize.Width, shape.SignSize.Height);
            decimal newSizeRatio = decimal.Divide(signSize.Width, signSize.Height);
            decimal tempZoom;
            int newWidth = 0, newHeight = 0;
            int widthOffset = 0, heightOffset = 0;
            if (oldSizeRatio <= newSizeRatio)
            {
                tempZoom = decimal.Divide(signSize.Height, shape.SignSize.Height);
                newWidth = (int)Math.Round(shape.SignSize.Width * tempZoom * Zoom);
                widthOffset = (int)Math.Round((double)(signSize.Width * Zoom - newWidth) / 2);
                location = new System.Drawing.Point(widthOffset + (int)(shape.LocationX * tempZoom * Zoom), (int)(shape.LocationY * tempZoom * Zoom));
            }
            else
            {
                tempZoom = decimal.Divide(signSize.Width, shape.SignSize.Width);
                newHeight = (int)Math.Round(shape.SignSize.Height * tempZoom * Zoom);
                heightOffset = (int)Math.Round((double)(signSize.Height * Zoom - newHeight) / 2);
                location = new System.Drawing.Point((int)(shape.LocationX * tempZoom * Zoom), heightOffset + (int)(shape.LocationY * tempZoom * Zoom));
            }
            width = (int)(shape.Width * tempZoom * Zoom);
            height = (int)(shape.Height * tempZoom * Zoom);
            return new Rectangle(location, new Size(width, height));
        }

        public void VisitMessage(MessageInfo message)
        {
            Check.Assert(message != null);
            Check.Assert(Sign != null);

            int wn = (int)Math.Round(message.Size.Width * 1.0f / Sign.Width);
            int hn = (int)Math.Round(message.Size.Height * 1.0f / Sign.Height);
            zoom = 1;
            zoom = wn < hn ? wn : hn;
            zoom = zoom < 1 ? 1 : zoom;

            if (zoom == message.Zoom)
                return;

            Message = message;

            foreach (var sl in message.Items)
                sl.Shape.Accept(this);
            message.Zoom = zoom;
        }

        public override void VisitShapeDraw(ShapeDraw shapeDraw)
        {
            VisitShape(shapeDraw);

            foreach (var s in shapeDraw.Childs)
                s.Accept(this);
        }

        private Size GetOffsetSizeBySign(Size nSignSize)
        {
            decimal oldSizeRatio = decimal.Divide(Message.Size.Width, Message.Size.Height);
            decimal newSizeRatio = decimal.Divide(nSignSize.Width, nSignSize.Height);
            decimal tempZoom;
            int newWidth = 0, newHeight = 0;
            int widthOffset = 0, heightOffset = 0;
            if (oldSizeRatio <= newSizeRatio)
            {
                tempZoom = decimal.Divide(nSignSize.Height, Message.Size.Height);
                newWidth = (int)Math.Round(Message.Size.Width * tempZoom);
                widthOffset = (int)Math.Round((double)(nSignSize.Width - newWidth) / 2);
            }
            else
            {
                tempZoom = decimal.Divide(nSignSize.Width, Message.Size.Width);
                newHeight = (int)Math.Round(Message.Size.Height * tempZoom);
                heightOffset = (int)Math.Round((double)(nSignSize.Height - newHeight) / 2);
            }
            return new Size(widthOffset, heightOffset);
        }

        public override void VisitLine(ShapeLine line)
        {
            var signSize = new Size(Sign.Width,Sign.Height);

            Size nsize = GetOffsetSizeBySign(signSize);

            double wrate = 1d * signSize.Width / Message.Size.Width;
            double hrate = 1d * signSize.Height / Message.Size.Height;
            double rate = wrate <= hrate ? wrate : hrate;

            line.Start = new Point((int)Math.Round(line.Start.X * rate), (int)Math.Round(line.Start.Y * rate));
            line.End =  new Point((int)Math.Round(line.End.X * rate),(int)Math.Round(line.End.Y * rate));
            line.Start = line.Start + nsize;
            line.End = line.End + nsize;

            VisitShape(line);
        }

        public override void VisitDownArrow(ShapeDownArrow downArrow)
        {
            VisitShape(downArrow);
        }

        public override void VisitEllipse(ShapeEllipse ellipse)
        {
            VisitShape(ellipse);
        }

        public override void VisitLeftArrow(ShapeLeftArrow leftArrow)
        {
            VisitShape(leftArrow);
        }

        public override void VisitRectangle(ShapeRectangle rectangle)
        {
            VisitShape(rectangle);
        }

        public override void VisitRightArrow(ShapeRightArrow rightArrow)
        {
            VisitShape(rightArrow);
        }

        public override void VisitUpArrow(ShapeUpArrow upArrow)
        {
            VisitShape(upArrow);
        }

        public override void VisitDynamicText(ShapeDynamicText dynamicText)
        {
            VisitShape(dynamicText);
        }

        public override void VisitDynamicVideo(ShapeDynamicVideo dynamicVideo)
        {
            VisitShape(dynamicVideo);
        }

        public override void VisitLabel(ShapeLabel shape)
        {
            VisitShape(shape);
        }

        public override void VisitTemp(ShapeTemp temp)
        {
            VisitShape(temp);
        }

        public override void VisitTime(ShapeTime time)
        {
            VisitShape(time);
        }

        public override void VisitImage(ShapeImage image)
        {
            VisitShape(image);
            image.ComputeDestBound();
        }

        public override void VisitVideo(ShapeVideo video)
        {
            VisitShape(video);
            video.ComputeDestBound();
        }

        private void VisitShape(ShapeBase shape)
        {
            var signSize = new Size(Sign.Width, Sign.Height);
            shape.VirtualBounds = GetVirtualBoundsBySign(shape,signSize, zoom);

            shape.SignType = Sign.Type;
            shape.SignSize = signSize;
            shape.Zoom = zoom;
        }


    }
}
