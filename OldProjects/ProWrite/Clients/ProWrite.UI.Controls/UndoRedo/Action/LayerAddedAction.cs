//---------------------------------------------------------------------
//
// File: LayerAddedAction.cs
//
// Description:
//      ShapeLayer added uploadAction class
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
    /// Add shape and item uploadAction
    /// </summary>
    public class LayerAddedAction : LayerAction
    {
        protected IShapeLayer _layer = null;

        public LayerAddedAction(LayerControl frameLayer)
            : base(frameLayer)
        {
            Name = string.Format("add <{0}> shape ", frameLayer.Shape.Type);
            if (frameLayer.Layer != null)
            {
                //_layer = frameLayer.Layer.Copy();
                _layer = frameLayer.Layer;
            }
        }

        /// <summary>
        /// undo
        /// </summary>
        public override void Undo()
        {
            //RemoveControl();
            if (_frameLayerCtrl != null)
            {
                if (_frameLayerCtrl.Shape != null)
                {
                    _frameLayerCtrl.Shape.BeginEdit();
                    _frameLayerCtrl.Shape.IsSelected = true;
                    _frameLayerCtrl.Shape.EndEdit();
                }
                _messageTab.RemoveLayer(_frameLayerCtrl);
            }
        }

        /// <summary>
        /// redo
        /// </summary>
        public override void Redo()
        {
            //AddControl();
            if (_frameLayerCtrl != null)
            {
                //_frameLayerCtrl = _messageTab.NewLayerControl(_layer.Copy(), true);
                _frameLayerCtrl = _messageTab.NewLayerControl(_layer as ShapeLayer, true);
                bool selected = _frameLayerCtrl.Shape.IsSelected;
                _frameLayerCtrl.Shape.IsSelected  = false;
                _messageTab.AddLayer(_frameLayerCtrl, ShapeAddMode.Clone);
                _frameLayerCtrl.Shape.IsSelected = selected;
            }
        }
    }
}
