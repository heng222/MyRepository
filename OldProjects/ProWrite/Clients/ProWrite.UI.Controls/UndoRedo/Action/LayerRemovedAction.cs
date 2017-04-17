//---------------------------------------------------------------------
//
// File: ShapeRemovedAction.cs
//
// Description:
//      Shape removed uploadAction class
//
// Author: Kevin 2008-8-4
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

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    /// <summary>
    /// remove shape and item uploadAction
    /// </summary>
    public class LayerRemovedActionNew : LayerAction
    {
        public LayerRemovedActionNew(LayerControl frameLayer)
            : base(frameLayer)
        {
            Name = string.Format("remove <{0}> shape ", _frameLayerCtrl.Shape.Type);
        }

        /// <summary>
        /// undo
        /// </summary>
        public override void Undo()
        {
            AddControl();
        }

        /// <summary>
        /// redo
        /// </summary>
        public override void Redo()
        {
            RemoveControl();
        }
    }
}
