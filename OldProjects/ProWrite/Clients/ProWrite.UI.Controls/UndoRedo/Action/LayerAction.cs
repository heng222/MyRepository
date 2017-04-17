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
    /// <summary>
    /// abstract class for message undo uploadAction
    /// </summary>
    public abstract class LayerAction : UndoAction
    {
        /// <summary>
        /// frame item control
        /// </summary>
        protected LayerControl _frameLayerCtrl = null;

        /// <summary>
        /// message control
        /// </summary>
        protected MessageControl _messageTab = null;

        protected LayerAction(LayerControl frameLayer)
        {
            _messageTab = MessageControl.Current;
            _frameLayerCtrl = frameLayer;
        }

        /// <summary>
        /// remove shape and item control
        /// </summary>
        public virtual void RemoveControl()
        {
            if (_frameLayerCtrl != null)
                _messageTab.RemoveLayer(_frameLayerCtrl);
        }

        /// <summary>
        /// add shape and item control
        /// </summary>
        public virtual void AddControl()
        {
            if (_frameLayerCtrl != null)
                _messageTab.AddLayerByRedo(_frameLayerCtrl, ShapeAddMode.Clone);
                //_messageTab.AddLayer(_frameLayerCtrl , ShapeAddMode.Clone);
        }
    }
}
