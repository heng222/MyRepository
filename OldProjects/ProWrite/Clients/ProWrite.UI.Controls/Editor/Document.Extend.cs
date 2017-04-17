using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.CopyPaste;

namespace ProWrite.UI.Controls.Editor
{
    public partial class Document
    {
        private bool _IsChanged = false;
        private ShapePaintPropertyInfo currentShapeInfo = 
            new ShapePaintPropertyInfo(
                ControlService.SignCombo.Current.Template.Message.PaintLayer.LineWidth
                ,ControlService.SignCombo.Current.Template.Message.PaintLayer.LineColor
                ,Color.Transparent
                ,ControlService.SignCombo.Current.Template.Message.PaintLayer.LineDashStyle 
                ,false);

        private DesignPaintVisitor Visitor = new DesignPaintVisitor();

        public ShapePaintPropertyInfo CurrentShapePaintInfo
        {
            get { return currentShapeInfo;}
        }

        public Color BorderColor
        {
            get { return currentShapeInfo.BorderColor; }
            set { currentShapeInfo.BorderColor = value; }
        }

        public Color FilledColor
        {
            get { return currentShapeInfo.FilledColor; }
            set
            {
                currentShapeInfo.FilledColor = value;
                currentShapeInfo.Filled = true;
            }
        }

        public DashStyle LineDashStyle 
        {
            get { return currentShapeInfo.LineDashStyle; }
            set { currentShapeInfo.LineDashStyle = value; }
        }

        public int BorderWidth
        {
            get { return currentShapeInfo.BorderWidth; }
            set { currentShapeInfo.BorderWidth = value; }
        }

        EventHandler<EventArgs<ShapeBase>> _ShapePaintByNetSelected = null;
        public EventHandler<EventArgs<ShapeBase>> ShapePaintByNetSelected
        {
            get { return _ShapePaintByNetSelected; }
            set 
            {
                if (_ShapePaintByNetSelected != null)
                    _ShapePaintByNetSelected = null;
                _ShapePaintByNetSelected = value;     
            }
        }

        public void Paint(Graphics g, Size size)
        {
            LocalMessageBus.Send(null,
               new MenuMessage(
                   new MenuCommand[]
                    {
                        new MenuCommand{ Command = MenuCommands.Delete,Enabled = SelectedCount > 0 }
                        ,new MenuCommand{Command = MenuCommands.Copy, Enabled = !(Count < 1 || SelectedCount < 1)}
                        ,new MenuCommand{Command = MenuCommands.Paste, Enabled = CopyAction.Current.CanPaste}
                    }
                   ));
           if(Count<1||SelectedCount<1)
                   LocalMessageBus.Send(this, new IsSelectShapImage(false));
           else if (SelectedCount==1&&SelectedShape.Type == ShapeType.Image)
           {
               LocalMessageBus.Send(this, new IsSelectShapImage(true));
           }
           else
                 LocalMessageBus.Send(this, new IsSelectShapImage(false));

            if (Count < 1)
                return;

            Visitor.Graphics = g;
            Visitor.Zoom = Zoom;

            UndoService.Suspend();
            //paint background Layer
            ShapeBase backItem = Find(delegate(ShapeBase item)
            {
                return item.IsBackground && item.IsVisible;
            });

            if (backItem != null)
            {
                if (backItem.VirtualBounds.Size != size)
                {
                    backItem.BeginEdit();
                    backItem.VirtualBounds = new Rectangle(Point.Empty, size);
                    backItem.EndEdit();
                }
                //backItem.Paint(g);
                backItem.Accept(Visitor);
            }

            ShapeBase[] shapes = this.ToArray();
            
            bool drawSpecialShape = false;

            //paint all layers except dynamic layers
            foreach (ShapeBase shape in shapes)
            {
                if (!shape.IsVisible
                    || shape.IsBackground
                    //|| shape.Type == ShapeType.DynamicText
                    //|| shape.Type == ShapeType.DynamicVideo
                    )
                    continue;

                if (   shape.Type == ShapeType.DownArrow
                    || shape.Type == ShapeType.Ellipse
                    || shape.Type == ShapeType.LeftArrow
                    || shape.Type == ShapeType.Line
                    || shape.Type == ShapeType.Rectangle
                    || shape.Type == ShapeType.RightArrow
                    || shape.Type == ShapeType.UpArrow)
                {
                    if (!drawSpecialShape)
                    {
                        DrawSpecialShape(shapes, g);
                        drawSpecialShape = true;
                    }
                }
                else
                {
                    shape.Accept(Visitor); //shape.Paint(g);
                }
            }

            //paint dynamic layers
            //将DynamicText层永远显示在最上面 add by Michael
            foreach (ShapeBase shape in shapes)
            {
                if (shape.IsVisible && shape.IsDynamicLayer /*(shape.Type == ShapeType.DynamicText)*/)
                    shape.Accept(Visitor);//shape.Paint(g);
            }

            //paint selected layers' frame
            foreach (ShapeBase shape in shapes)
            {
                if (!shape.IsVisible || !shape.IsSelected)
                    continue;
                //shape.PaintSelect(g, true);
                shape.DrawTracker(g);
            }
            
            UndoService.Resume();
        }

        private void DrawSpecialShape(ShapeBase[] specialShapes, Graphics g)
        {
            foreach (ShapeBase shape in specialShapes)
            {
                if (shape.Type == ShapeType.DownArrow
                    || shape.Type == ShapeType.Ellipse
                    || shape.Type == ShapeType.LeftArrow
                    || shape.Type == ShapeType.Line
                    || shape.Type == ShapeType.Rectangle
                    || shape.Type == ShapeType.RightArrow
                    || shape.Type == ShapeType.UpArrow)
                    shape.Accept(Visitor);//shape.Paint(g);
            }
        }
       
        //select the all shapes that interact with destRectangle
        public void SelectInRectangle(Rectangle destRectangle)
        {
            CancelSelect();

            bool line = false;
            bool figure = false;
            bool text = false;
            bool dynammic = false;
            bool isSetShapePaint = false;
            foreach (ShapeBase o in this)
            {
                if (o.IntersectsWith(destRectangle))
                {
                    //o.IsSelected = true;
                    if (o is ShapeFigure && !figure)
                    {
                        if (line)
                        {
                            var figureColorFill = new MenuCommand(MenuCommands.ColorFill, true);
                            figureColorFill.PropertyName = "SelectedColor";
                            figureColorFill.PropertyValue = (o as ShapeFigure).FillColor;

                            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                          figureColorFill }));
                            o.BeginEdit();
                            o.IsSelected = true;
                            o.EndEdit();
                        }
                        else
                        {
                            o.IsSelected = true;
                        }
                        //ShapeDraw.BeginEdit();
                        //ShapeDraw.IsSelected = true;
                        //ShapeDraw.EndEdit();
                        isSetShapePaint = true;
                        figure = true;
                    }
                    else if (o.Type == ShapeType.Line && !line)
                    {
                        if (figure)
                        {
                            o.BeginEdit();
                            o.IsSelected = true;
                            o.EndEdit();
                        }
                        else
                        {
                            o.IsSelected = true;
                        }
                        //ShapeDraw.BeginEdit();
                        //ShapeDraw.IsSelected = true;
                        //ShapeDraw.EndEdit();
                        isSetShapePaint = true;
                        line = true;
                    }
                    else if (o.Type == ShapeType.Text && !text)
                    {
                        SetShapeSelected(o);
                        text = true;
                    }
                    else if ((o.Type == ShapeType.DynamicText
                        || o.Type == ShapeType.Time
                        || o.Type == ShapeType.Temperature)
                        && !dynammic)
                    {
                        SetShapeSelected(o);
                        dynammic = true;
                    }
                    else
                    {
                        o.BeginEdit();
                        o.IsSelected = true;
                        o.EndEdit();
                    }
                }
            }

            OnNetSelectedShapes(this, new NetSelecetedShapesEventArgs(this.SelectedShapes));
            if (isSetShapePaint && _ShapePaintByNetSelected != null)
                _ShapePaintByNetSelected(this, new EventArgs<ShapeBase>(ShapeDraw));

        }

        private void SetShapeSelected(ShapeBase o)
        {
            ShapeBase[] shapes = this.SelectedShapes;
            this.CancelSelect();
            o.IsSelected = true;
            foreach (ShapeBase s in shapes)
            {
                s.BeginEdit();
                s.IsSelected = true;
                s.EndEdit();
            }
        }
        
        // Delete selected items
        // true if at least one object is deleted
        public bool DeleteSelection()
        {
            bool result = false;
            int len = SelectedCount;
            foreach(ShapeBase shape in SelectedShapes)   
            {
                Remove(shape);
                result = true;
            }
            if (result) _IsChanged = true;
            return result;
        }

    }

    
}
