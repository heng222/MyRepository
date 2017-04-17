//---------------------------------------------------------------------
//
// File: MessageAction.cs
//
// Description:
//      Message uploadAction abstract class
//
// Author: Kevin 2008-8-4
// 
// Modify History:
//      Jerry Xu 2008-8-22 Update undo/redo move item
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.UI.Controls.Editor;
using ProWrite.Core;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    public class LayerMoveActionNew : UndoAction
    {
        private LayerControl source;
        private LayerControl dest;
        private MessageControl layerContainer;
        public LayerMoveActionNew(MessageControl layerContainer, LayerControl source, LayerControl dest)
        {
            this.layerContainer = layerContainer;
            this.source = source;
            this.dest = dest;
            Name = "item move";
        }

        public override void Undo()
        {
            layerContainer.MoveLayers(dest, source);
        }

        public override void Redo()
        {
            layerContainer.MoveLayers(source, dest);
        }
    }
}
