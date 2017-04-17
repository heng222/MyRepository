using System;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Shape;
using System.Reflection;

namespace ProWrite.UI.Controls.ShapeTools
{
	// Base class for all tools which create new graphic object
	public abstract class ShapeToolObject : ShapeTool
	{
		private Cursor cursor;

        protected class _Cursors
        {
            private static readonly Assembly asm = Assembly.GetExecutingAssembly();
            public static readonly Cursor Line = new Cursor(asm.GetManifestResourceStream( "ProWrite.UI.Controls.ShapeTools.Line.cur"));
            public static readonly Cursor Ellipse = new Cursor(asm.GetManifestResourceStream( "ProWrite.UI.Controls.ShapeTools.Ellipse.cur"));
            public static readonly Cursor Pencil = new Cursor(asm.GetManifestResourceStream( "ProWrite.UI.Controls.ShapeTools.Pencil.cur"));
            public static readonly Cursor Rectangle = new Cursor(asm.GetManifestResourceStream( "ProWrite.UI.Controls.ShapeTools.Rectangle.cur"));
            public static readonly Cursor Text = null;//new Cursor(asm.GetManifestResourceStream("ProWrite.UI.Controls.ShapeTools.TextTool.cur"));
        }
		// ShapeTool cursor.
		protected Cursor Cursor
		{
			get { return cursor; }
			set { cursor = value; }
		}

		// Left mouse is released and a newew object is created and resized.
		public override void OnMouseUp(Canvas drawArea, MouseEventArgs e)
		{
            foreach (ShapeBase o in drawArea.Document.SelectedShapes)
            {
                o.Normalize();
            }

            drawArea.ActiveTool = ShapeToolType.ToolPointer;
            //drawArea.Current = null;
     		drawArea.Capture = false;
			drawArea.Refresh();
		}

        public override void OnMouseMove(Canvas drawArea, MouseEventArgs e)
        {
            drawArea.Cursor = Cursor;

            if (e.Button == MouseButtons.Left)
            {
               
                Point p = e.Location;
                if (p.X <= drawArea.Current.VirtualLocation.X)
                    p.X = drawArea.Current.VirtualLocation.X + drawArea.Document.Zoom;
                if (p.Y <= drawArea.Current.VirtualLocation.Y)
                    p.Y = drawArea.Current.VirtualLocation.Y + drawArea.Document.Zoom;
                
                e = new MouseEventArgs(e.Button, e.Clicks, p.X, p.Y, e.Delta);

                Point point = ClampCanvas(drawArea, e);

                drawArea.Current.MoveHandleTo(point, 5);
           
                drawArea.Refresh();
            }
        }
       
		// Add new object to draw area.
		// Function is called when user left-clicks draw area,
		// and one of ToolObject-derived tools is active.
		protected void AddNewObject(Canvas drawArea, ShapeBase o)
		{
            if (MessageControl.Current != null)
                MessageControl.Current.AddLayer(o, ShapeAddMode.Menu);

            drawArea.Current = o;
			drawArea.Capture = true;
			drawArea.Refresh();
		}

        protected Point ClampCanvas(Canvas drawArea, MouseEventArgs e)
        {
            Point point = drawArea.BackTrackMouse(e.Location);

            Rectangle workBound = drawArea.DisplayRectangle;
            point.X = point.X < 0 ? 0 : point.X;
            point.X = point.X > workBound.Right ? workBound.Right : point.X;
            point.Y = point.Y < 0 ? 0 : point.Y;
            point.Y = point.Y > workBound.Bottom ? workBound.Bottom : point.Y;
            
            return point;
        }



	}
}