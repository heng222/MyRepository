using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Shape.Visitor
{
    public class VisitorAdapter:IVisitor
    {
        #region IVisitor Members

        public virtual void VisitLabel(ShapeLabel shape)
        {
        }

        public virtual void VisitDownArrow(ShapeDownArrow downArrow)
        {
        }

        public virtual void VisitShapeDraw(ShapeDraw shapeDraw)
        {
        }

        public virtual void VisitDynamicText(ShapeDynamicText dynamicText)
        {
        }

        public virtual void VisitDynamicVideo(ShapeDynamicVideo dynamicVideo)
        {
        }

        public virtual void VisitEllipse(ShapeEllipse ellipse)
        {
        }

        public virtual void VisitImage(ShapeImage image)
        {
            throw new NotImplementedException();
        }

        public virtual void VisitLeftArrow(ShapeLeftArrow leftArrow)
        {
        }

        public virtual void VisitLine(ShapeLine line)
        {
        }

        public virtual void VisitRectangle(ShapeRectangle rectangle)
        {
        }

        public virtual void VisitRightArrow(ShapeRightArrow rightArrow)
        {
        }

        public virtual void VisitTemp(ShapeTemp temp)
        {
        }

        public virtual void VisitTime(ShapeTime time)
        {
        }

        public virtual void VisitUpArrow(ShapeUpArrow upArrow)
        {
        }

        public virtual void VisitVideo(ShapeVideo video)
        {
        }

        #endregion
    }
}
