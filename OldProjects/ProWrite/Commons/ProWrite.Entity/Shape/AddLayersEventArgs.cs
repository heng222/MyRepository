//---------------------------------------------------------------------
//
// File: AddLayersEventArgs.cs
//
// Description:
// AddLayersEventArgs class
//
// Author: Jerry Xu
// Date  : 2008-8-3
//
//Modify History:
//      Jerry Xu  2008-8-3  Add method:DrawText
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
    /// <summary>
    /// Add layers event args
    /// </summary>
    public class AddLayersEventArgs:EventArgs
    {
        public readonly ShapeLabel Shape;
        public readonly List<ShapeLabel> Items;

        public AddLayersEventArgs(ShapeLabel shape,List<ShapeLabel> items)
        {
            Shape = shape;
            Items = items;
        }
    }

    public class NetSelecetedShapesEventArgs : EventArgs
    {
        public readonly ShapeBase[] SelectedShapes;

        public NetSelecetedShapesEventArgs(ShapeBase[] shapes)
        {
            SelectedShapes = shapes;
        }
    }

    /// <summary>
    /// Shape event for add shape or remove shape. 
    /// </summary>
    public class AddRemoveShapeEventArgs : EventArgs
    {
        public ShapeBase Shape;
        public EventType Event;
        public int  ShapeIndex;
        
        public enum EventType
        {
            Add,
            Delete,
            Insert
        }

        public AddRemoveShapeEventArgs(ShapeBase shape, EventType eventType, int shapeIndex)
        {
            Shape = shape;
            Event = eventType;
            ShapeIndex = shapeIndex;
        }
    }
}
