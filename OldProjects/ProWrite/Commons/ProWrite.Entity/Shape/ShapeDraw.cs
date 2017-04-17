//---------------------------------------------------------------------
//
// File: DefaultShape.cs
//
// Description:
// Default Shape class
//
// Author: 
//
// Modify History:
//      Kevin 2008-6-27 Refactor
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using ProWrite.Core;
using System.Collections.Generic;
using System.Drawing.Design;

using PaintUFE = ProWrite.UFE.Entity;
using ProWrite.Entity.Library;
using ProWrite.Unsafe;
using ProWrite.UFE;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// Shape draw class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class ShapeDraw : ShapeBase,IEquatable<ShapeDraw>
    {
        #region Non Serialized Fields
        [NonSerialized]
        private EventHandler _childShapeSeleceted;
        [NonSerialized]
        private EventHandler _selectedChanged;
        [NonSerialized]
        private bool _isChildSelected;
        #endregion

        #region Serialized Fields
        private Color _backColor;
        private Color _foreColor;
        private List<ShapeBase> _childs;
        private List<ShapeBase> childs
        {
            get
            {
                if (_childs == null)
                    _childs = new List<ShapeBase>();
                return _childs;
            }
        }
		#endregion //Fields

        #region Methods

        public ShapeDraw()
        {
            _isVisible = true;
        }

		public void AddChildShape(ShapeBase shape)
		{
			if (shape != null)
			{
                if (childs.Contains(shape)) return;

                shape.BoundsChanged += new EventHandler(OnBoundsChanaged);
				shape.SelectedChanged += new EventHandler(OnSelectedChanaged);
                childs.Add(shape);
				ComputerBounds();
			}
		}

		public void DeleteChildShape(ShapeBase shape)
		{
			if (shape != null)
			{
				shape.BoundsChanged -= new EventHandler(OnBoundsChanaged);
				shape.SelectedChanged -= new EventHandler(OnSelectedChanaged);
				childs.Remove(shape);
				ComputerBounds();
			}
		}

        public override void Move(Point point)
        {
            base.Move(point);
            foreach (ShapeBase s in _childs)
                s.Move(point);
            
        }
        
        public void Clear()
        {
            
            for(int i = _childs.Count-1; i>=0;i--)
            {
                DeleteChildShape(_childs[i]);
            }
               
        }

        public override ShapeBase NewInstance()
        {
            return new ShapeDraw();
        }

        public override void FromTo(ShapeBase shape)
        {
            if (shape == null)
                return;
            base.FromTo(shape);

            ShapeDraw other = shape as ShapeDraw;
            if (other == null)
                return;

            _backColor = other._backColor;
            _foreColor = other._foreColor;
            _isSelected = other._isSelected;
            _isVisible = other._isVisible;
            if (other.childs.Count > 0)
            {
                foreach (ShapeBase item in other.childs)
                    childs.Add(item.Copy());
            }
        }
        
        #endregion //End Methods

        #region Properties Setting
        
        public bool IsChildSelected
        {
            get { return _isChildSelected; }
        }

        //private bool _isSelected = false;
        public override bool IsSelected
        {
            get
            {
                return _isSelected;
            }
            set
            {
                if (_isSelected != value)
                {
                    _isSelected = value;
                    if(IsEdit)
                        foreach (ShapeBase item in childs)
                        {
                            item.BeginEdit();
                            item.IsSelected = value;
                            item.EndEdit();
                        }
                    else
                        foreach (ShapeBase item in childs)
                            item.IsSelected = value;

                    if (_selectedChanged != null)
                        _selectedChanged(this, EventArgs.Empty);
                }
            }
        }

        //private bool _isVisible;
        public override bool IsVisible
        {
            get
            {
                if (childs.Count < 1)
                    return false;
                bool vis = false;
                foreach (ShapeBase item in childs)
                {
                    vis |= item.IsVisible;
                }
                if (!vis)
                    return vis;
                 return _isVisible;
            }
            set
            {
                if (_isVisible != value)
                {
                    _isVisible = value;
                    if (IsEdit)
                    {
                        foreach (ShapeBase item in childs)
                        {
                            item.BeginEdit();
                            item.IsVisible = value;
                            item.EndEdit();
                        }
                    }
                    else
                    {
                        foreach (ShapeBase item in childs)
                           item.IsVisible = value;
                    }

                }
            }
        }

        [Browsable(false)]
        public int Count
        {
            get { return childs.Count; }
        }

        [ReadOnly(true)]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public ShapeBase[] Childs
        {
            get { return childs.ToArray(); }
        }

        [Browsable(false)]
        public ShapeBase[] SelectedShapes
        {
            get
            {
                List<ShapeBase> shapes = new List<ShapeBase>();
                foreach (ShapeBase item in childs)
                    if (item.IsSelected)
                        shapes.Add(item);
                return shapes.ToArray();
            }
        }

        [Category("Layer")]
        public Color ForeColor
        {
            get { return _foreColor; }
            set { _foreColor = value; }
        }

        [Category("Layer")]
        public Color BackColor
        {
            get { return _backColor; }
            set { _backColor = value; }
        }

        [Browsable(false)]
        public override ShapeType Type
        {
            get { return ShapeType.ShapeDraw; }
        }

        [Browsable(false)]
        public override LayerType LayerType
        {
            get { return LayerType.Paint; }
        }

        public event EventHandler ChildShapeSelected
        {
            add { _childShapeSeleceted += value; }
            remove { _childShapeSeleceted -= value; }
        }

        public new event EventHandler SelectedChanged
        {
            add { _selectedChanged += value; }
            remove { _selectedChanged -= value; }
        }

        #endregion

        public override void Accept(IVisitor visitor)
        {
            visitor.VisitShapeDraw(this);
            foreach (var item in childs)
                item.Accept(visitor);
        }

        public void PopulateSignInfo(SignType signType, Size signSize, int zoom)
        {
            SignType = signType;
            SignSize = signSize;
            Zoom = zoom;
        }

        #region Private Method
        
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (childs != null)
                childs.Clear();
            _childs = null;
            _selectedChanged = null;
            _childShapeSeleceted = null;
        }

        private void OnBoundsChanaged(object sender, EventArgs e)
        {
            ComputerBounds();
        }

        private void OnSelectedChanaged(object sender, EventArgs e)
        {
            ShapeBase shape = sender as ShapeBase;
            if (shape != null
                && shape.LayerType == LayerType.Paint
                && shape.Type != ShapeType.ShapeDraw)
            {
                _isChildSelected = shape.IsSelected;
                if (_childShapeSeleceted != null)
                    _childShapeSeleceted(shape, EventArgs.Empty);
            }
        }

        //计算包含所有图形的最小的矩形
        internal void ComputerBounds()
        {
            int left = 0;
            int top = 0;
            int right = 0;
            int bottom = 0;
            int count = 0;

            foreach (ShapeBase shape in childs)
            {
                if (shape.VirtualBounds.Left <= left || (0 == left && count == 0))
                    left = shape.VirtualBounds.Left;

                if (shape.VirtualBounds.Top <= top || (0 == top && count == 0))
                    top = shape.VirtualBounds.Top;

                if (shape.VirtualBounds.Right > right || (0 == right && count == 0))
                    right = shape.VirtualBounds.Right;

                if (shape.VirtualBounds.Bottom > bottom || (0 == bottom && count == 0))
                    bottom = shape.VirtualBounds.Bottom;
                count++;
            }

            VirtualBounds = Rectangle.FromLTRB(left, top, right, bottom);
        }

        #endregion

		#region IEquatable<ShapeDraw> Members

		public bool Equals(ShapeDraw other)
		{
			if (other == null)
				return false;
			if (other._backColor != _backColor)
				return false;
			if (other.childs != childs)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as ShapeDraw);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		#endregion

        protected override void UpdateSignType()
        {
            base.UpdateSignType();

            _backColor = SignTypeHandler.ConvertColor(_backColor, SignType);
            _foreColor = SignTypeHandler.ConvertColor(_foreColor, SignType);

            foreach(var item in _childs)
                item.SignType = SignType;
        }
	}
}
