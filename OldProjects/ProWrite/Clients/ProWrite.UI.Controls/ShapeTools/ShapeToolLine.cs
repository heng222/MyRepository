using System.Drawing;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Core;

namespace ProWrite.UI.Controls.ShapeTools
{
	/// <summary>
	/// Line tool
	/// </summary>
	public class ShapeToolLine : ShapeToolObject
	{
        public ShapeToolLine()
		{
			//Cursor = new Cursor(GetType(), "Line.cur");
            Cursor = _Cursors.Line;
		}

		public override void OnMouseDown(Canvas drawArea, MouseEventArgs e)
		{
            UndoService.BeginTransaction("Add a line");

            Point p = drawArea.BackTrackMouse(new Point(e.X, e.Y));
            SignType sign = drawArea.MessageControl.Sign.Type;
            int zoom = drawArea.Document.Zoom;
            Point s = p.PointMultiplyDouble(1d / zoom);

            ShapeLine line = new ShapeLine(zoom, s, new Point(s.X + 1, s.Y + 1), drawArea.Document.CurrentShapePaintInfo, sign);
            AddNewObject(drawArea, line);
        }

		public override void OnMouseMove(Canvas drawArea, MouseEventArgs e)
		{
			drawArea.Cursor = Cursor;
			if (e.Button ==  MouseButtons.Left)
			{
                Point point = ClampCanvas(drawArea,e);
                
				drawArea.Current.MoveHandleTo(point, 2);
				
                drawArea.Refresh();
			}
		}

        public override void OnMouseUp(Canvas drawArea, MouseEventArgs e)
        {
            UndoService.Commit();
        }
	}
}