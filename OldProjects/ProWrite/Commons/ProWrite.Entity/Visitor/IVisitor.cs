using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
    public interface IVisitor
    {
        void VisitLabel(ShapeLabel shape);
        void VisitDownArrow(ShapeDownArrow downArrow);
        void VisitShapeDraw(ShapeDraw shapeDraw);
        void VisitDynamicText(ShapeDynamicText dynamicText);
        void VisitDynamicVideo(ShapeDynamicVideo dynamicVideo);
        void VisitEllipse(ShapeEllipse ellipse);
        void VisitImage(ShapeImage image);
        void VisitLeftArrow(ShapeLeftArrow leftArrow);
        void VisitLine(ShapeLine line);
        void VisitRectangle(ShapeRectangle rectangle);
        void VisitRightArrow(ShapeRightArrow rightArrow);
        void VisitTemp(ShapeTemp temp);
        void VisitTime(ShapeTime time);
        void VisitUpArrow(ShapeUpArrow upArrow);
        void VisitVideo(ShapeVideo video);
    }
}