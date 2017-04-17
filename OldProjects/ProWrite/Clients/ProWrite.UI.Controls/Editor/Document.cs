//---------------------------------------------------------------------
//
// File: ShapeCollection.cs
//
// Description:
// Shape collection class
//
// Author: 
//
//Modify History:
//      Kevin   2008-6-19 Kevin 迁移
//      Kevin   2008-6-25 移除冒泡排序，用系统排序代替
//      Kevin   2008-6-25 解除ShapeCollection 对MessageTab control 和UndoManager的强依赖
//      Kevin   2008-6-25 恢复冒泡排序
//      Kevin   2008-6-26 移除ShapeCollection 对EditorLayers control 的强依赖
//      Michael 2008-9-1 重构完此类，删除所有与sort和zsort有关的属性和方法。
//      Michael 2008-9-3 修改shape的MOVE操作，控制shape不会发生越界和溢出。
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Editor
{
    /// <summary>
    /// Summary description for Containers.
    /// </summary>
    [Serializable]
    public partial class Document : List<ShapeBase>, IChangedServiceProvider, IDisposable
    {
        private int m_DirectionOffset;
        private ChangedService _changedService;

        public Document()
            : base()
        {
            m_DirectionOffset = 0;
            _changedService = new ChangedService();
            this.AddRemoveShape += new EventHandler<AddRemoveShapeEventArgs>(Document_AddRemoveShape);
        }

        public ChangedService ChangedService
        {
            get { return _changedService; }
        }

        public int SelectedCount
        {
            get
            {
                int selectedCount = 0;
                foreach (ShapeBase shape in this)
                {
                    if (shape.IsSelected)
                    {
                        selectedCount++;
                    }
                }
                return selectedCount;
            }
        }

        public ShapeBase SelectedShape
        {
            get
            {
                if (Count < 1) return null;
                for(int i = Count -1; i >=0; i--)
                {
                    if (this[i].IsSelected)
                        return this[i];
                }
                return null;
            }
        }

        public ShapeBase[] SelectedShapes
        {
            get
            {
                List<ShapeBase> alst = new List<ShapeBase>();
                foreach (ShapeBase shape in this)
                {
                    if (shape.IsSelected)
                    {
                        alst.Add(shape);
                    }
                }
                return alst.ToArray();
            }
        }

        [NonSerialized]
        [XmlIgnore]
        private EventHandler<PropertyChangedEventArgs> _shapePropertyChanged;
        public event EventHandler<PropertyChangedEventArgs> ShapePropertyChanged
        {
            add { _shapePropertyChanged += value; }
            remove { _shapePropertyChanged -= value; }
        }

        [NonSerialized]
        private EventHandler _shapeBackgroundChanged;
        public event EventHandler ShapeBackgroundChanged
        {
            add { _shapeBackgroundChanged += value; }
            remove { _shapeBackgroundChanged -= value; }
        }

        [NonSerialized]
        private EventHandler _shapeSelectedChanged;
        public event EventHandler ShapeSelectedChanged
        {
            add { _shapeSelectedChanged += value; }
            remove { _shapeSelectedChanged -= value; }
        }

        [NonSerialized]
        private EventHandler<RemoveBackgroundEventArgs> _shapeRemoveBackground;
        public event EventHandler<RemoveBackgroundEventArgs> ShapeRemoveBackground
        {
            add { _shapeRemoveBackground += value; }
            remove { _shapeRemoveBackground -= value; }
        }

        [NonSerialized]
        private EventHandler<AddLayersEventArgs> _shapeAddLayers;
        public event EventHandler<AddLayersEventArgs> ShapeAddLayers
        {
            add { _shapeAddLayers += value; }
            remove { _shapeAddLayers -= value; }
        }

        [NonSerialized]
        private EventHandler<NetSelecetedShapesEventArgs> _netSelectedShapes;
        public event EventHandler<NetSelecetedShapesEventArgs> NetSelectedShapes
        {
            add { _netSelectedShapes += value; }
            remove { _netSelectedShapes += value; }
        }

        [NonSerialized]
        private EventHandler<AddRemoveShapeEventArgs> _addRemoveShape;
        public event EventHandler<AddRemoveShapeEventArgs> AddRemoveShape
        {
            add { _addRemoveShape += value; }
            remove { _addRemoveShape += value; }
        }

        private void OnNetSelectedShapes(object sender, NetSelecetedShapesEventArgs e)
        {
            if (_netSelectedShapes != null)
                _netSelectedShapes(sender, e);
        }

        private void OnPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            _changedService.MarkChanged();
            if (_shapePropertyChanged != null)
                _shapePropertyChanged(sender, e);
        }

        private void OnBackgroundChanged(object sender, EventArgs e)
        {
            _changedService.MarkChanged();
            if (_shapeBackgroundChanged != null)
                _shapeBackgroundChanged(sender, e);
        }

        private void OnShapeSelectedChanged(object sender, EventArgs e)
        {
            if (_shapeSelectedChanged != null)
                _shapeSelectedChanged(sender, e);
        }

        private void OnShapeRemoveBackground(object sender, RemoveBackgroundEventArgs e)
        {
            if (_shapeRemoveBackground != null)
                _shapeRemoveBackground(sender, e);
        }

        private void OnShapeAddLayers(object sender, AddLayersEventArgs e)
        {
            if (_shapeAddLayers != null)
                _shapeAddLayers(sender, e);
        }

        /// <summary>
        /// 用来控制控件resize后区域翻转后的鼠标状态
        /// </summary>
        public void ResetDirectionOffset()
        {
            m_DirectionOffset = 0;
        }

        private void AddEvent(ShapeBase shape)
        {
            shape.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(OnPropertyChanged);
            shape.ValidateExistBackGround = ValidateExistBackGround;
            shape.BackgroundChanged += new EventHandler(OnBackgroundChanged);
            shape.SelectedChanged += OnShapeSelectedChanged;

            if (shape.Type == ShapeType.Text)
            {
                (shape as ShapeLabel).BackgroundRemove += OnShapeRemoveBackground;
                (shape as ShapeLabel).AddLayers += OnShapeAddLayers;
            }
            else if (shape.Type == ShapeType.Image)
                (shape as ShapeImage).BackgroundRemove += OnShapeRemoveBackground;

            else if (shape.Type == ShapeType.Video)
                (shape as ShapeVideo).BackgroundRemove += OnShapeRemoveBackground;

        }

        private void RemoveEvent(ShapeBase shape)
        {
            shape.PropertyChanged -= OnPropertyChanged;
            shape.ValidateExistBackGround = null;
            shape.BackgroundChanged -= OnBackgroundChanged;
            shape.SelectedChanged -= OnShapeSelectedChanged;

            if (shape.Type == ShapeType.Text)
            {
                (shape as ShapeLabel).BackgroundRemove -= OnShapeRemoveBackground;
                (shape as ShapeLabel).AddLayers -= OnShapeAddLayers;
            }
        }

        private ShapeDraw _shapeDraw;
        public ShapeDraw ShapeDraw
        {
            get
            {
                if (_shapeDraw == null)
                {
                    _shapeDraw = new ShapeDraw();
                }
                return _shapeDraw;
            }
            set
            {
                if (value == null && _shapeDraw != null)
                {
                    _shapeDraw = null;
                }
            }
        }

        private int _zoom = 1;
        public int Zoom
        {
            get { return _zoom; }
            set
            {
                if (_zoom != value)
                {
                    int old = _zoom;
                    _zoom = value;
                    if (_shapeDraw != null)
                        _shapeDraw.Zoom = value; 
                    foreach (ShapeBase item in this)
                    {
                        item.BeginEdit();
                        item.Zoom = value;
                        item.EndEdit();
                    }
                     
                    // OnPropertyChanged(this,new PropertyChangedEventArgs("Zoom",value,_zoom));
                }
            }
        }

        public new void Add(ShapeBase shape)
        {
            if (shape != null && !Contains(shape))
            {
                shape.Zoom = Zoom;

                if (shape.Index > -1)
                {
                    Insert(shape.Index, shape);
                }
                else
                {
                    if (shape.Type == ShapeType.ShapeDraw)
                    {
                        ShapeDraw tmp = null;
                        if (_shapeDraw == null)
                        {
                            _shapeDraw = shape as ShapeDraw;
                            tmp = _shapeDraw;
                            foreach (ShapeBase item in _shapeDraw.Childs)
                                Add(item);
                        }
                        else
                        {
                            tmp = shape as ShapeDraw;
                            foreach (ShapeBase item in tmp.Childs)
                            {
                                _shapeDraw.AddChildShape(item);
                                Add(item);
                            }

                        }
                    }
                    else
                    {
                        AddEvent(shape);
                        base.Add(shape);
                        if (shape.LayerType == LayerType.Paint)
                            ShapeDraw.AddChildShape(shape);
                        _changedService.MarkChanged();
                    }

                    Document_AddRemoveShape(this, new AddRemoveShapeEventArgs(shape, AddRemoveShapeEventArgs.EventType.Add, this.IndexOf(shape)));
                }

                
            }
        }

        public new bool Remove(ShapeBase shape)
        {
            if (shape == null)
                return false;
            if (shape.Type == ShapeType.ShapeDraw)
            {
                bool flg = true;
                foreach (ShapeBase item in _shapeDraw.Childs)
                {
                    if (!Remove(item))
                        flg = false;
                }
                return flg;
            }

            int index = shape.Index;
            RemoveEvent(shape);
            
            if (Contains(shape))
            {
                _changedService.MarkChanged();
                if (shape.LayerType == LayerType.Paint)
                    _shapeDraw.DeleteChildShape(shape); 
                bool flag = base.Remove(shape);
                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand(MenuCommands.Delete, SelectedShape != null)));

                Document_AddRemoveShape(this, new AddRemoveShapeEventArgs(shape, AddRemoveShapeEventArgs.EventType.Delete, index));

                return flag;
            }
            return false;
        }

        public new void Insert(int index, ShapeBase shape)
        {
            if (shape != null && !Contains(shape))
            {
                if (shape.Type == ShapeType.ShapeDraw)
                {
                    ShapeDraw tmp = null;
                    if (_shapeDraw == null)
                    {
                        _shapeDraw = shape as ShapeDraw;
                        tmp = _shapeDraw;
                        foreach (ShapeBase item in _shapeDraw.Childs)
                            Insert(index,item);
                    }
                    else
                    {
                        tmp = shape as ShapeDraw;
                        foreach (ShapeBase item in tmp.Childs)
                        {
                            _shapeDraw.AddChildShape(item);
                            Insert(index, item);
                        }
                    }
                }
                else
                {
                    AddEvent(shape);
                    base.Insert(index, shape);
                    if (shape.LayerType == LayerType.Paint)
                        ShapeDraw.AddChildShape(shape);
                    _changedService.MarkChanged();
                }

                Document_AddRemoveShape(this, new AddRemoveShapeEventArgs(shape, AddRemoveShapeEventArgs.EventType.Insert, index));
            }

        }
        public void ItemMove(int oldIndex, int newIndex)
        {
            ShapeBase shape = this[oldIndex];
            this.RemoveAt(oldIndex);
            this.Insert(newIndex, shape);

            for (int i = 0; i < this.Count; i++)
            {
                ShapeBase s = this[i] as ShapeBase;
                s.Index = i;
            }

            _changedService.MarkChanged();
        }

        //public void Move(Point pos)
        //{
        //    foreach (ShapeBase shape in this)
        //    {
        //        if (shape.IsBackground)//backgroud can not be moved edit by louis
        //            continue;
        //        if (shape.IsSelected)
        //        {
        //            Rectangle bounds = shape.VirtualBounds;
        //            bounds.Offset(pos);

        //            if (bounds.X < 0 || bounds.Y < 0)
        //            {
        //                return;
        //            }
        //            shape.VirtualBounds = bounds;
        //        }
        //    }
        //}

        public void Move(Point pos, Size size)
        {
            foreach (ShapeBase shape in this)
            {
				if(shape.IsBackground) //backgroud can not be moved edit by louis
					continue;
                if (shape.IsSelected)
                {
                    Rectangle bounds = shape.VirtualBounds;
                    bounds.Offset(pos);
                    if (bounds.X < Constance.ShapeOffset - bounds.Width || bounds.Y < Constance.ShapeOffset - bounds.Height
                        || (bounds.X > size.Width - Constance.ShapeOffset)
                        || (bounds.Y > size.Height - Constance.ShapeOffset))
                    {
                        return;
                    }
                    if (shape.Type == ShapeType.Line)
                    shape.Move(pos.X, pos.Y);
                    else
                    shape.VirtualBounds = bounds;
                }
            }
            
        }

        public void Grow(int inc, Keys key)
        {
            foreach (ShapeBase shape in this)
            {
                if (shape.IsSelected)
                {
                    Rectangle bounds = shape.VirtualBounds;
                    switch (key)
                    {
                        case Keys.Left:
                            bounds.Width -= inc;
                            break;
                        case Keys.Up:
                            bounds.Height -= inc;
                            break;
                        case Keys.Right:
                            bounds.Width += inc;
                            break;
                        case Keys.Down:
                            bounds.Height += inc;
                            break;
                    }
                    shape.VirtualBounds = GetSurroundRectangle(bounds);
                }
            }
        }

        public void Grow(int inc, Keys key, Size size)
        {
            foreach (ShapeBase shape in this)
            {
                if (shape.IsSelected)
                {
                    if (shape.Type == ShapeType.Line)
                    {
                        int changeSize = inc * Zoom;
                        ShapeLine sl = ((ShapeLine)(shape));
                        Point endPoint = sl.VirtualEnd;
                        switch (key)
                        {
                            case Keys.Left:
                                endPoint.X -= changeSize;
                                if (endPoint.X < 0)
                                    return;
                                break;
                            case Keys.Up:
                                endPoint.Y -= changeSize;
                                if (endPoint.Y < 0)
                                    return;
                                break;
                            case Keys.Right:
                                endPoint.X += changeSize;
                                if (endPoint.X > size.Width)
                                    return;
                                break;
                            case Keys.Down:
                                endPoint.Y += changeSize;
                                if (endPoint.Y > size.Height)
                                    return;
                                break;
                        }

                        sl.ChangeEndPoint(endPoint);
                    }
                    else
                    {
                        Rectangle bounds = shape.VirtualBounds;
                        int changeSize = inc * Zoom;
                        switch (key)
                        {
                            case Keys.Left:
                                bounds.Width -= changeSize;
                                break;
                            case Keys.Up:
                                bounds.Height -= changeSize;
                                break;
                            case Keys.Right:
                                bounds.Width += changeSize;
                                if (bounds.Right > size.Width)
                                    return;
                                break;
                            case Keys.Down:
                                bounds.Height += changeSize;
                                if (bounds.Bottom > size.Height)
                                    return;
                                break;
                        }
                        shape.VirtualBounds = GetSurroundRectangle(bounds);
                    }
                }
            }
        }

        private void Document_AddRemoveShape(object sender, AddRemoveShapeEventArgs e)
        {
            switch (e.Event)
            {
                case AddRemoveShapeEventArgs.EventType.Add:
                    e.Shape.Index = e.ShapeIndex;
                    break;

                case AddRemoveShapeEventArgs.EventType.Delete:
                    if (e.ShapeIndex > -1)
                        goto default;
                    break;

                case AddRemoveShapeEventArgs.EventType.Insert:
                    goto default;
                    break;

                default:
                    if (e.ShapeIndex < 0) e.ShapeIndex = 0;
                    for (int i = e.ShapeIndex; i < this.Count; i++)
                    {
                        this[i].Index = this.IndexOf(this[i]);
                    }
                    break;
            }
        }


        private Rectangle GetSurroundRectangle(Rectangle rectF)
        {
            rectF.Location = new Point(Math.Min(rectF.Left, rectF.Right), Math.Min(rectF.Top, rectF.Bottom));
            rectF.Width = Math.Abs(rectF.Width);
            rectF.Height = Math.Abs(rectF.Height);
            return rectF;
        }

        public ShapeBase Select(PointF point)
        {
            return SelectShape(point, true);
        }

        public ShapeBase TestSelect(PointF point)
        {
            return SelectShape(point, false);
        }

        private ShapeBase SelectShape(PointF point, bool select)
        {
            bool IsContains = false;
            RectangleF bounds;
            ShapeBase selectedShape = null;
            ShapeBase shape = null;

            for (int i = this.Count - 1; i >= 0; i--)
            {
                shape = this[i];
                if (!shape.IsVisible)
                    continue;

                bounds = shape.VirtualBounds;
                if (shape.IsSelected)
                {
                    float halfBorder = shape.BorderWidth / 2;
                    bounds.Inflate(halfBorder, halfBorder);
                }
                if (bounds.Contains(point))
                {
                    IsContains = true;
                    break;
                }
            }

            if (IsContains)
            {
                if (select)
                {
                    CancelSelect();
                    shape.IsSelected = true;
                }
                selectedShape = shape;
            }
            return selectedShape;
        }

        public void Select(RectangleF region)
        {
            ShapeBase curShape = null;

            foreach (ShapeBase shape in this)
            {
                RectangleF intersect = region;
                intersect.Intersect(shape.VirtualBounds);
                float squareShape = shape.VirtualBounds.Width * shape.VirtualBounds.Height;
                float squareIntersect = intersect.Width * intersect.Height;
                if (squareShape / 3 < squareIntersect)
                {
                    curShape = shape;
                }
            }

            if (curShape != null)
            {
                CancelSelect();
                curShape.IsSelected = true;
            }
        }

        public void Select(ShapeBase shape)
        {
            if (shape != null)
            {
                CancelSelect();
                if (shape.LayerType == LayerType.Paint)
                {
                    ShapeDraw.BeginEdit();
                    ShapeDraw.IsSelected = true;
                    ShapeDraw.EndEdit();
                }
                else
                    shape.IsSelected = true;
            }
        }

        public bool CancelSelect()
        {
            return CancelSelect(false);
        }
        /// <summary>
        /// cancel the shapes selected
        /// </summary>
        /// <returns>if all selectd shapes are canceled, return true</returns>
        public bool CancelSelect(bool isOpenEvent)
        {
            bool cancelAll = true;
            
            foreach (ShapeBase shape in this)
            {
                if (isOpenEvent)
                {
                    shape.IsSelected = false;
                }
                else
                {
                    shape.BeginEdit();
                    shape.IsSelected = false;
                    shape.EndEdit();
                }
            }

            if (isOpenEvent)
                ShapeDraw.IsSelected = false;
            else
            {
                ShapeDraw.BeginEdit();
                ShapeDraw.IsSelected = false;
                ShapeDraw.EndEdit();
            }
            
            return cancelAll;
        }


        private static Rectangle ExchangeRectangle(Point inc, Rectangle rect)
        {
            int L, T, R, B;
            L = Math.Min(rect.Left, rect.Right);
            T = Math.Min(rect.Top, rect.Bottom);
            R = Math.Max(rect.Left, rect.Right);
            B = Math.Max(rect.Top, rect.Bottom);
            return Rectangle.FromLTRB(L, T, R, B);
        }

        public ShapeBase ValidateExistBackGround(long id)
        {
            if (Count < 1)
                return null;

            foreach (ShapeBase shape in this)
            {
                if (shape.ID != id && shape.IsBackground)
                {
                    return shape;
                }
            }
            return null;
        }

        public void Dispose()
        {
            int length = Count;
            if (length > 0)
            {
                for (int i = 0; i < length; i++)
                {
                    if (this[i] != null)
                    {
                        this[i].Dispose();
                        this[i] = null;
                    }
                }
                if (_changedService != null)
                    _changedService.Dispose();
                _changedService = null;
                if(_shapeDraw != null)
                    _shapeDraw.Dispose();
                _shapeDraw = null;
                _shapePropertyChanged = null;
                _shapeBackgroundChanged = null;
            }
        }
    }
}