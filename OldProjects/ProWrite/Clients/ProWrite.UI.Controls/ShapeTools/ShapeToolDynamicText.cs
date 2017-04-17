using System.Drawing;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.ShapeTools
{
    public class ShapeToolDynamicText : ShapeToolObject
    {
        public ShapeToolDynamicText()
        {
            //Cursor = new Cursor(GetType(), "Rectangle.cur");
            Cursor = _Cursors.Text;
        }

        public override void OnMouseDown(Canvas drawArea, MouseEventArgs e)
        {
            
        }

        public override void OnMouseMove(Canvas drawArea, MouseEventArgs e)
        {
            drawArea.Cursor = Cursor;
            if (e.Button == MouseButtons.Left)
            {
                Point point = drawArea.BackTrackMouse(new Point(e.X, e.Y));
                if (drawArea.Current != null)
                {
                    drawArea.Current.MoveHandleTo(point, 5);
                    drawArea.Refresh();
                }
            }
        }
    }
}