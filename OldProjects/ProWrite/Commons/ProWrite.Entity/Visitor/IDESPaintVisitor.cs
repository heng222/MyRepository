using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
    public interface IDESPaintVisitor : IVisitor
    {
        void VisitLayer(ShapeLayer layer);
    }
}
