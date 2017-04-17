//---------------------------------------------------------------------
//
// File: ShapeAddedAction.cs
//
// Description:
//      Shape to paint added uploadAction class
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
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Editor;
using ProWrite.Core;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    public class ShapeAddedAction : UndoAction
    {
        private ShapeBase _shape;
        private MessageControl _messageControl;
        public ShapeAddedAction(ShapeBase shape)
        {
            _shape = shape;
            _messageControl = MessageControl.Current;
            Name = string.Format("add <{0}> shape ", _shape.Type);
        }

        public override void Undo()
        {
            _messageControl.RemoveLayer(_shape);
        }

        public override void Redo()
        {
            _messageControl.AddLayer(_shape, ShapeAddMode.Clone);
        }
    }
}
