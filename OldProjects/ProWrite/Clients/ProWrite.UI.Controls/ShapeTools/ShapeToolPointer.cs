using System.Drawing;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using System;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using System.Linq;

namespace ProWrite.UI.Controls.ShapeTools
{
	/// <summary>
	/// Pointer tool
	/// </summary>
	internal class ShapeToolPointer : ShapeToolObject
	{
		private enum SelectionMode
		{
			None,
			NetSelection,   // group selection is active
			Move,           // object(s) are moves
			Size,           // object is resized
            MulitSelection
		}

		private SelectionMode selectMode = SelectionMode.None;

		// Object which is currently resized:
		private ShapeBase resizedObject;
		private int resizedObjectHandle;

		// Keep state about last and current point (used to move and resize objects)
        private Point startPoint = new Point(0, 0);
        private Point lastPoint = new Point(0, 0);
		private bool wasMove = false;

		public override void OnMouseDown(Canvas drawArea, MouseEventArgs e)
		{
            Point point = drawArea.BackTrackMouse(new Point(e.X, e.Y));
            if (e.Button == MouseButtons.Left)
            {
                if (e.Button == MouseButtons.Left)
                {
                    if (drawArea.ShortcutKey == Keys.Control
                        || drawArea.ShortcutKey == Keys.Shift)
                    {
                        selectMode = SelectionMode.MulitSelection;
                        for (int i = drawArea.Document.Count - 1; i >= 0; i--)
                        {
                            int handleNumber = drawArea.Document[i].HitTest(point);
                            if (handleNumber == 0)
                            {
                                drawArea.Document[i].IsSelected = !drawArea.Document[i].IsSelected;
                                break;
                            }
                        }
                        return;
                    }
                } 

                wasMove = false;
                selectMode = SelectionMode.None;

                    // Test for resizing
                    for (int i = drawArea.Document.Count - 1; i >= 0; i--)
                    {
                        int handleNumber = drawArea.Document[i].HitTest(point);
                        if (handleNumber > 0)
                        {
                            selectMode = SelectionMode.Size;
                            UndoService.BeginTransaction("Resize the shape");
                            resizedObject = drawArea.Document[i];

                            resizedObjectHandle = handleNumber;

                            drawArea.Document.CancelSelect();
                            drawArea.Document[i].IsSelected = true;
                            break;
                        }
                    }
                

                // Test for move
                if (selectMode == SelectionMode.None)
                {
                    ShapeBase so = null;
                    for (int i = drawArea.Document.Count-1; i >= 0; i--)
                    {
                        if (drawArea.Document[i].HitTest(point) == 0)
                        {
                            so = drawArea.Document[i];
                            break;
                        }
                    }

                    if (so != null)
                    {
                        UndoService.BeginTransaction("Move the shape");
                        selectMode = SelectionMode.Move;
                        // Unselect all if Ctrl is not pressed and clicked object is not selected yet
                        if ((Control.ModifierKeys & Keys.Control) == 0 && !so.IsSelected)
                            drawArea.Document.CancelSelect(true);

                        // Select clicked object
                        int paintcount = drawArea.Document.ShapeDraw.SelectedShapes.Length;
                        int textcount = (from shape in drawArea.Document
                                         where
                                             shape.IsSelected &&
                                             (shape.Type == ShapeType.Text 
                                             || shape.Type == ShapeType.Time
                                             || shape.Type == ShapeType.Temperature 
                                             || shape.Type == ShapeType.DynamicText)
                                         select shape).Count();

                        LayerControl lc = null;
                        if (so is ShapePaint && paintcount > 0)
                        {
                            so.BeginEdit();

                            //foreach (ShapeBase sb in drawArea.Document.ShapeDraw.SelectedShapes)
                            //    sb.IsSelected = false;

                            so.IsSelected = true;
                            so.EndEdit();
                            lc = drawArea.MessageControl.GetLayerControl(so);
                            if (lc != null) lc.IsSelected = so.IsSelected;
                        }
                        else if((so.Type == ShapeType.Text 
                            || so.Type == ShapeType.Time
                            || so.Type == ShapeType.Temperature 
                            || so.Type == ShapeType.DynamicText) && textcount > 0)
                        {
                            so.BeginEdit();
                            so.IsSelected = true;
                            so.EndEdit();
                            lc = drawArea.MessageControl.GetLayerControl(so);
                            if (lc != null) lc.IsSelected = so.IsSelected;
                        }
                        else
                            so.IsSelected = true;
                        
                        drawArea.Cursor = Cursors.SizeAll;
                    }
                }

                // Net selection
                if (selectMode == SelectionMode.None)
                {
                    //click on background
                    if ((Control.ModifierKeys & Keys.Control) == 0)
                        drawArea.Document.CancelSelect(true);

                    selectMode = SelectionMode.NetSelection;
                    UndoService.BeginTransaction("Select some shapes");
                    drawArea.DrawNetRectangle = true;
                }

    


                lastPoint = point;
                startPoint = point;
            }
            else if (e.Button == MouseButtons.Right)
            {
                //drawArea.Document.CancelSelect(true);
                //for (int i = drawArea.Document.Count -1; i >= 0; i--)
                //{
                //    if (drawArea.Document[i].HitTest(point) >= 0)
                //    {
                //        drawArea.Document[i].IsSelected = true;
                //        break;
                //    }
                //}
                bool emptyInsect = false;
                foreach (ShapeBase s in drawArea.Document)
                    if (s.HitTest(point) >= 0)
                    {
                        emptyInsect = true;
                        break;
                    }
                if (!emptyInsect)
                    drawArea.Document.CancelSelect(true);
            }

			drawArea.Capture = true;
            drawArea.NetRectangle = ShapeControlPaintNew.GetNormalizedRectangle(startPoint, lastPoint);
			drawArea.Refresh();
		}

		// Mouse is moved.
		// None button is pressed, ot left button is pressed.
		public override void OnMouseMove(Canvas drawArea, MouseEventArgs e)
		{
			Point point = drawArea.BackTrackMouse(new Point(e.X, e.Y));
			wasMove = true;
			if (e.Button ==	MouseButtons.None)
			{
                Cursor cursor = Cursors.Default;
                for (int i = drawArea.Document.Count - 1; i >= 0; i--)
          		{
                    int n = drawArea.Document[i].HitTest(point);
					if (n > 0)
					{
                        cursor = drawArea.Document[i].GetHandleCursor(n);
						break;
					}
				}

				drawArea.Cursor = cursor;
				return;
			}

			if (e.Button != MouseButtons.Left)
				return;

            if (point.X < 0) point.X = 0;
            if (point.X > drawArea.Width) point.X = drawArea.Width;

            if (point.Y < 0) point.Y = 0;
            if (point.Y > drawArea.Height) point.Y = drawArea.Height;

            if (lastPoint.X < 0) lastPoint.X = 0;
            if (lastPoint.X > drawArea.Width) lastPoint.X = drawArea.Width;

            if (lastPoint.Y < 0) point.Y = 0;
            if (lastPoint.Y > drawArea.Height) lastPoint.Y = drawArea.Height;


			// Left button is pressed
			// Find difference between previous and current position
            int dx = point.X - lastPoint.X;
            int dy = point.Y - lastPoint.Y;


            //加快移动速度
            int zoom = drawArea.MessageControl != null ?drawArea.MessageControl.Zoom : 6;
            if (Math.Abs(dx) < zoom && Math.Abs(dy) < zoom)
                return;

            int xOffset = dx % zoom;
            int yOffset = dy % zoom;
            if (xOffset != 0 || yOffset % zoom != 0)
            {
                dx -= xOffset;
                dy -= yOffset;
            }

            if(!ClampCanvas(drawArea, point)) return;
            lastPoint = point;

		    xOffset = point.X%zoom;
		    yOffset = point.Y%zoom;
            if(xOffset != 0 || yOffset != 0)
            {
                if (xOffset <= zoom / 2)
                    point.X -= xOffset;
                else
                    point.X = point.X + zoom - xOffset;

                if (yOffset <= zoom / 2)
                    point.Y -= yOffset;
                else
                    point.Y = point.Y + zoom - yOffset;
            }


            // resize
			if (selectMode == SelectionMode.Size)
			{
				if (resizedObject != null)
				{
                    //if (resizedObject.Type == ShapeType.Text)
                    //{
                    //    ((ShapeLabel)resizedObject).FrameSizeFixed = true;
                    //}

                    if (resizedObject.Type != ShapeType.Line)
                    {
                        switch(resizedObjectHandle)
                        {
                            case 1:
                                if (point.X >= resizedObject.VirtualBounds.Right)
                                    point.X = resizedObject.VirtualBounds.Right - zoom;
                                if (point.Y >= resizedObject.VirtualBounds.Bottom)
                                    point.Y = resizedObject.VirtualBounds.Bottom - zoom;
                                break;
                            case 2:
                                if (point.Y >= resizedObject.VirtualBounds.Bottom)
                                    point.Y = resizedObject.VirtualBounds.Bottom - zoom;
                                break;
                            case 3:
                                if (point.X <= resizedObject.VirtualBounds.Left)
                                    point.X = resizedObject.VirtualBounds.Left + zoom;
                                if (point.Y >= resizedObject.VirtualBounds.Bottom)
                                    point.Y = resizedObject.VirtualBounds.Bottom - zoom;
                                break;
                            case 4:
                                if (point.X < resizedObject.VirtualBounds.Left)
                                    point.X = resizedObject.VirtualBounds.Left + zoom;
                                break;
                            case 5:
                                if (point.X <= resizedObject.VirtualBounds.Left)
                                    point.X = resizedObject.VirtualBounds.Left + zoom;
                                if (point.Y <= resizedObject.VirtualBounds.Top)
                                    point.Y = resizedObject.VirtualBounds.Top + zoom;
                                break;
                            case 6:
                                if (point.Y <= resizedObject.VirtualBounds.Top)
                                    point.Y = resizedObject.VirtualBounds.Top + zoom;
                                break;
                            case 7:
                                if (point.X >= resizedObject.VirtualBounds.Right)
                                    point.X = resizedObject.VirtualBounds.Right - zoom;
                                if (point.Y < resizedObject.VirtualBounds.Top)
                                    point.Y = resizedObject.VirtualBounds.Top + zoom;
                                break;
                            case 8:
                                if (point.X >= resizedObject.VirtualBounds.Right)
                                    point.X = resizedObject.VirtualBounds.Right - zoom;
                                break;
                            default:
                                break;
                        }   
                        lastPoint = point;
                    }

                    resizedObject.MoveHandleTo(point, resizedObjectHandle);

                    drawArea.Document.ChangedService.MarkChanged();

                    if(resizedObject is ShapeLine)
                        lastPoint = resizedObject.GetHandle(resizedObjectHandle);
                    
                    drawArea.Refresh();
				}
			}
            
			// move
			if (selectMode == SelectionMode.Move)
			{
                int movecount = 0;
                foreach(ShapeBase sb in drawArea.Document.SelectedShapes)
                {
					if (sb.IsBackground)
						continue;
                    movecount++;
                    sb.Move(dx, dy);
                }
                if(movecount >0)
                    drawArea.Document.ChangedService.MarkChanged();

          		drawArea.Cursor = Cursors.SizeAll;
				drawArea.Refresh();
			}

            if (selectMode == SelectionMode.NetSelection)
            {
                drawArea.NetRectangle = ShapeControlPaintNew.GetNormalizedRectangle(startPoint, lastPoint);
                drawArea.Refresh();
                return;
            }
		}

		//mouse button is released
		public override void OnMouseUp(Canvas drawArea, MouseEventArgs e)
		{
            if (selectMode == SelectionMode.MulitSelection)
                return;

            int zoom = drawArea.Document.Zoom;
            if (selectMode == SelectionMode.NetSelection)
            {
                // Group selection
                drawArea.Document.SelectInRectangle(drawArea.NetRectangle);

                selectMode = SelectionMode.None;
                drawArea.DrawNetRectangle = false;

                UndoService.Commit();
            }
            if (resizedObject != null
                || selectMode == SelectionMode.Size
                )
            {
                // after resizing
                if (resizedObject != null)
                {
                    resizedObject.BeginEdit();
                    if (resizedObject is ShapePaint)
                        ; // resizedObject.SetVirtualBounds();
                    else
                        resizedObject.VirtualBounds = resizedObject.FormatBoundsByZoom(resizedObject.VirtualBounds, zoom);

                    resizedObject.EndEdit();
                    resizedObject = null;
                }

                selectMode = SelectionMode.None;
                UndoService.Commit();
            }

            if (selectMode == SelectionMode.Move)
            {
                foreach (ShapeBase sb in drawArea.Document.SelectedShapes)
                {
                    sb.BeginEdit();
                    if (sb is ShapeFigure
                        //|| sb is ShapeLine
                        )
                        sb.SetVirtualBounds();
                    else if (sb.Type != ShapeType.Line)
                        sb.VirtualBounds = sb.FormatBoundsByZoom(sb.VirtualBounds, zoom);

                    sb.EndEdit();
                }
                selectMode = SelectionMode.None;

                Point point = drawArea.BackTrackMouse(new Point(e.X, e.Y));
                for (int i = drawArea.Document.Count - 1; i >= 0; i--)
                {
                    if (drawArea.Document[i].HitTest(point) == 0)
                    {
                        ShapeBase so = drawArea.Document[i];
                        if (so != null)
                        {
                            // Unselect all if Ctrl is not pressed and clicked object is not selected yet
                            if ((Control.ModifierKeys != Keys.Control || Control.ModifierKeys != Keys.Shift) && so.IsSelected && startPoint == lastPoint)
                            {
                                drawArea.Document.CancelSelect(true);
                                so.IsSelected = true;
                            }
                        }
                        break;
                    }
                }               

                 UndoService.Commit();
            }

            drawArea.Capture = false;
            drawArea.Refresh();
            lastPoint = drawArea.BackTrackMouse(e.Location);
		}

        public Point AdjustPoint(Canvas drawArea, Point p)
        {
            int zoom = drawArea.Document.Zoom;
            Rectangle rect = drawArea.DisplayRectangle;
            p.X = p.X <=1 ? 1:p.X;
            p.Y = p.Y <=1 ? 1:p.Y;
            p.X = p.X > rect.Width ? rect.Width - 1 : p.X;
            p.Y = p.Y > rect.Height ? rect.Height - 1 : p.Y;
            
            return p;
        }

        private Rectangle AdjustShapeLocation(Canvas drawArea, Rectangle rect)
        {
            if (rect.IsEmpty) return Rectangle.Empty;
            
            int zoom = drawArea.Document.Zoom;
            int left = rect.Left;
            int top = rect.Top;
            
            AdjustMoveDistance(zoom, ref left, ref top);
            

            return new Rectangle(left, top, rect.Width, rect.Height);
        }

        private Size AdjustMoveDistance(int gridScale,ref int dx, ref int dy)
        {
            int remainder = dx % gridScale;
            if (dx >= 0)
            {
                if (remainder != 0)
                {
                    if (remainder < gridScale / 2)
                        dx = dx - remainder;
                    else
                        dx = dx + gridScale - remainder;
                }
            }
            else
            {
                remainder = Math.Abs(remainder);
                if (remainder != 0)
                {
                    if (remainder < gridScale / 2)
                        dx = dx + remainder;
                    else
                        dx = dx + remainder - gridScale;
                }
            }

            remainder = dy % gridScale;
            if (dy >= 0)
            {
                if (remainder != 0)
                {
                    if (remainder < gridScale / 2)
                        dy = dy - remainder;
                    else
                        dy = dy + gridScale - remainder;
                }
            }
            else
            {
                remainder = Math.Abs(remainder);
                if (remainder != 0)
                {
                    if (remainder < gridScale / 2)
                        dy = dy + remainder;
                    else
                        dy = dy + remainder - gridScale;
                }
            }

            return new Size(dx, dy);
        }

        private bool ClampCanvas(Canvas drawArea, Point p)
        {
            Rectangle rect = drawArea.DisplayRectangle;
            bool result = p.X >= 0 && p.X <= rect.Right;
            result = result && p.Y >= 0 && p.Y <= rect.Bottom;
            return result;
        }
	}
}