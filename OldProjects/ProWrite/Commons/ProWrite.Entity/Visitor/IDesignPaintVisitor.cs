using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
    public interface IDesignPaintVisitor : IVisitor
    {
        Graphics Graphics { get; set; }
    }
}
