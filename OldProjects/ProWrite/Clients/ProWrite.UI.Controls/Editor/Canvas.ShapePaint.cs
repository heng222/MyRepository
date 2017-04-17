using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

using ProWrite.UI.Controls.ShapeTools;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;


namespace ProWrite.UI.Controls.Editor
{
    public partial class Canvas
    {
        private Point lastPoint = Point.Empty;
        private bool _panning = false;
        private float _rotation = 0f;
        private float _zoom = 1f;
        private int _panX = 0;
        private int _panY = 0;
        private ShapeTool[] tools;

        private void InitShapePaints()
        {
            tools = new ShapeTool[(int)ShapeToolType.NumberOfShapeTools];
            tools[(int)ShapeToolType.ToolPointer] = new ShapeToolPointer();
            tools[(int)ShapeToolType.ToolLine] = new ShapeToolLine();
            tools[(int)ShapeToolType.ToolRectangle] = new ShapeToolRectangle();
            tools[(int)ShapeToolType.ToolEllipse] = new ShapeToolEllipse();            //tools[(int)ShapeToolType.ToolPolyLine] = new ShapePolyLine();
            tools[(int)ShapeToolType.ToolUpArrow] = new ShapeToolUpArrow();
            tools[(int)ShapeToolType.ToolDownArrow] = new ShapeToolDownArrow();
            tools[(int)ShapeToolType.ToolLeftArrow] = new ShapeToolLeftArrow();
            tools[(int)ShapeToolType.ToolRightArrow] = new ShapeToolRightArrow();
            tools[(int)ShapeToolType.ToolText] = new ShapeToolText();
            tools[(int)ShapeToolType.ToolImage] = new ShapeToolImage();
            tools[(int)ShapeToolType.ToolVideo] = new ShapeToolVideo();
            
            tools[(int)ShapeToolType.ToolDynamicText] = new ShapeToolDynamicText();
            tools[(int)ShapeToolType.ToolDynamicVideo] = new ShapeToolDynamicVideo();
            tools[(int)ShapeToolType.ToolTemp] = new ShapeToolDynamicText();
            tools[(int)ShapeToolType.ToolTime] = new ShapeToolDynamicText();
           
            //this.MouseDown += new MouseEventHandler(DrawArea_MouseDown);
            //this.MouseMove += new MouseEventHandler(DrawArea_MouseMove);
            //this.MouseUp += new MouseEventHandler(DrawArea_MouseUp);
            //this.KeyDown += new KeyEventHandler(DrawArea_KeyDown);
        }
       
        private ShapeToolType  _ActiveTool = ShapeToolType.ToolPointer;
        public ShapeToolType ActiveTool
        {
            get { return _ActiveTool; }
            set { _ActiveTool = value; }
        }

        public ShapeBase Current
        {
            get { return _ActiveShape; }
            set { _ActiveShape = value; }
        }
        
        // Flag is set to true if group selection rectangle should be drawn.
        private bool drawNetRectangle = false;
        public bool DrawNetRectangle
        {
            get { return drawNetRectangle; }
            set { drawNetRectangle = value; }
        }

        // Group selection rectangle. Used for drawing.
        private Rectangle netRectangle = Rectangle.Empty;
        public Rectangle NetRectangle
        {
            get { return netRectangle; }
            set { netRectangle = value; }
        }

        public MessageControl MessageControl
        {
            get { return MessageControl.Current;}
        }

        public void AddShape(MessageControl messageCtrl, ShapeBase shape)
        {
            if (messageCtrl != null)
                messageCtrl.AddLayer(shape,ShapeAddMode.Menu);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            DrawArea_MouseDown(this, e);
            
            bool canCopy = _document.SelectedCount > 0;
            ControlService.EnableCopyMenu(canCopy);
            base.OnMouseDown(e);
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            DrawArea_MouseUp(this, e);
            

            if (_document.SelectedShape != null)
            {
                ControlService.RefreshPropertyGrid(_document.SelectedShape);
            }
            else
            {
                MessageControl.Current.LoadModelInfo();
                ControlService.RefreshPropertyGrid(MessageControl.Current.Model);
            }
            base.OnMouseUp(e);
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            DrawArea_MouseMove(this, e);
            
            base.OnMouseMove(e);
        }

        public Point BackTrackMouse(Point p)
        {
            // Backtrack the mouse...
            Point[] pts = new Point[] { p };
            using (Matrix mx = new Matrix())
            {
                mx.Translate(-ClientSize.Width / 2, -ClientSize.Height / 2, MatrixOrder.Append);
                mx.Rotate(_rotation, MatrixOrder.Append);
                mx.Translate(ClientSize.Width / 2 + _panX, ClientSize.Height / 2 + _panY, MatrixOrder.Append);
                mx.Scale(_zoom, _zoom, MatrixOrder.Append);
                mx.Invert();
                mx.TransformPoints(pts);
            }
            // pts[0] = AdjustPoint(pts[0]);
            return pts[0];
        }

        // Draw group selection rectangle
        public void DrawNetSelection(Graphics g)
        {
            if (!DrawNetRectangle)
                return;

            ControlPaint.DrawFocusRectangle(g, NetRectangle, Color.WhiteSmoke, Color.Transparent);
        }

        #region Private Method
        // Left button down event is passed to active tool.
        // Right button down event is handled in this class.
        private void DrawArea_MouseDown(object sender, MouseEventArgs e)
        {
            lastPoint = BackTrackMouse(e.Location);
            if (e.Button == MouseButtons.Right)
            {
                if (_panning)
                    _panning = false;
                ActiveTool = ShapeToolType.ToolPointer;
            }
            tools[(int)ActiveTool].OnMouseDown(this, e);
        }

        // Moving without button pressed or with left button pressed
        // is passed to active tool.
        private void DrawArea_MouseMove(object sender, MouseEventArgs e)
        {
        	//track current mouse location 
        	Point curLoc = BackTrackMouse(e.Location);
        	if (e.Button == MouseButtons.Left || e.Button == MouseButtons.None)
        	{
                if (e.Button == MouseButtons.Left && _panning)
                {
                    if (curLoc.X != lastPoint.X)
                        _panX += curLoc.X - lastPoint.X;
                    if (curLoc.Y != lastPoint.Y)
                        _panY += curLoc.Y - lastPoint.Y;
                    Invalidate();
                }
                else
                {
                    int index = (int)ActiveTool;
                    if(index >= 0) tools[(int)ActiveTool].OnMouseMove(this, e);
                }
	        }
			else
				Cursor = Cursors.Default;
        
			lastPoint = BackTrackMouse(e.Location);
        }

        // Left button up event is passed to active tool.
        private void DrawArea_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                tools[(int)ActiveTool].OnMouseUp(this, e);
            }
            LocalMessageBus.Send(null, new SetDefaultDrawingIcon());
            ActiveTool = ShapeToolType.ToolPointer;
            Cursor = Cursors.Default;
        }
        #endregion

        protected override void Dispose(bool disposing)
        {
            _HScrollBar.Dispose();
            _VScrollBar.Dispose();
            _document.Dispose();
            base.Dispose(disposing);
        }
    }
}