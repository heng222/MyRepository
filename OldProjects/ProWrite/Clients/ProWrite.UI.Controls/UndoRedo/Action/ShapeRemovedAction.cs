//---------------------------------------------------------------------
//
// File: ShapeRemovedAction.cs
//
// Description:
//      Shape to paint removed uploadAction class
//
// Author: Kevin 2008-8-29
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    public class ShapeRemovedAction:UndoAction
    {
        private ShapeBase _shape;
        private MessageControl _messageControl;
        public ShapeRemovedAction(ShapeBase shape)
        {
            _shape = shape;
            _messageControl = MessageControl.Current;
            Name = string.Format("remove <{0}> shape ", _shape.Type);
        }

        public override void Undo()
        {
            _messageControl.AddLayer(_shape, ShapeAddMode.Clone);
        }

        public override void Redo()
        {
            _messageControl.RemoveLayer(_shape);
        }
    }
}
