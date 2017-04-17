using System;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.ShapeTools
{
    public class ShapeToolRightArrow : ShapeToolObject
    {
        public ShapeToolRightArrow()
        {
            //Cursor = new Cursor(GetType(), "Rectangle.cur");
            Cursor = _Cursors.Rectangle;
        }

        public override void OnMouseDown(Canvas drawArea, MouseEventArgs e)
        {
            UndoService.BeginTransaction("Add a rigth Arrow");

            Point p = drawArea.BackTrackMouse(new Point(e.X, e.Y));
            ShapeRightArrow shape = new ShapeRightArrow(
                drawArea.Document.Zoom
                , p.X
                , p.Y
                , 1
                , 1
                , drawArea.Document.CurrentShapePaintInfo
                , drawArea.MessageControl.Sign.Type);

            AddNewObject(drawArea, shape);
        }

        public override void OnMouseUp(Canvas drawArea, MouseEventArgs e)
        {
            UndoService.Commit();
        }
    }
}
