//---------------------------------------------------------------------
//
// File: ShapeCopyAction.cs
//
// Description:
//      Shape Copy Action class
//
// Author: Kevin 2008-8-11
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Playlist;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.Core;

namespace ProWrite.UI.Controls.CopyPaste
{
    /// <summary>
    /// Shape Copy Action class
    /// </summary>
    public class ShapeCopyAction : CopyAction<MessageInfo,MessageControl>
    {
        private static readonly Type clipboardType = typeof(CopyItem[]);
        private CopyItem[] items = null;

        public ShapeCopyAction()
        {
        }

        [Serializable]
        private class CopyItem
        {
            public CopyItem() { }
            public CopyItem(ShapeBase shape, IShapeLayer layer)
            {
                Shape = shape;
                Layer = layer;
            }

            public ShapeBase Shape;
            public IShapeLayer Layer;
        }
        
        /// <summary>
        /// do copy
        /// </summary>
        /// <returns></returns>
        protected override bool DoCopy()
        {
            if (innerControl == null)
                return false;

            ShapeBase[] sources = innerControl.ShapeControl.Document.SelectedShapes;
            if (sources != null && sources.Length > 0)
            {
                int length = sources.Length;
                var clones = new CopyItem[length];
                for (int i = 0; i < length; i++)
                {
                    if (sources[i].LayerType != LayerType.Paint)
                    {
                        var source = sources[i].Tag as IShapeLayer;
                        if (source == null)
                            source = innerControl.GetLayerControl(sources[i]).Layer;
                        var target = source.Copy();
                        clones[i] = new CopyItem(target.Shape, target);
                    }
                    else
                    {
                        var source = innerControl.GetLayerControl(sources[i]).Layer.Copy();
                        var target = sources[i].Copy();
                        clones[i] = new CopyItem(target, source);
                    }
                    
                    clones[i].Shape.ID = sources[i].ID;
                }

                ClipboardService.Set(clones);
                return true;
            }
            return false;
        }

        /// <summary>
        /// can copy
        /// </summary>
        public override bool CanCopy
        {
            get
            {
                ShapeBase[] selectedShapes = innerControl.ShapeControl.Document.SelectedShapes;
                bool canCopy = selectedShapes != null && selectedShapes.Length > 0;
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Copy, canCopy));
                return canCopy;
            }
        }

        /// <summary>
        /// can paste
        /// </summary>
        public override bool CanPaste
        {
            get
            {
                if (innerControl == null)
                    return false;
                if (ClipboardService.ContainsImage())
                    return true;
                if (!ClipboardService.Contains<CopyItem[]>())
                    return false;
                items = ClipboardService.Get<CopyItem[]>();
                if (items == null || items.Length < 1)
                    return false;
                return true;
            }
        }

        

        protected override bool DoPaste()
        {
            if (ClipboardService.ContainsImage())
            {
                var img = ClipboardService.GetImage();
                var imgFile = Constance.LibraryImageDir + Constance.DirectorySeparator + DateTime.Now.Ticks.ToString() + ".jpg";
                IOHelper.SaveImage(img, imgFile);
                innerControl.AddImageLayer(imgFile);
                return true;
            }

            foreach (var item in items)
            {
                if (item.Layer.Shape.LayerType == LayerType.Paint)
                {
                    LayerControl lc = innerControl.GetLayerControl(item.Shape);
                    
                    if (lc != null || innerControl.IsExistShapeDraw)
                    {
                        ShapeBase pastedShape = item.Shape;
                        pastedShape.ID = KeyGenerator.Shape;
                        pastedShape.Move(Point.Empty);
                        innerControl.AddLayer(pastedShape, ShapeAddMode.Clone);
                    }
                    else
                    {
                        IShapeLayer sl = item.Layer.Copy();
                        if (sl.Shape.Type == ShapeType.ShapeDraw)
                        {
                            ShapeDraw sd = sl.Shape as ShapeDraw;
                            sd.Clear();
                            sd.AddChildShape(item.Shape);
                            //sl.Shape = sd;
                        }
                        sl.Shape.Move(Point.Empty);
                        LayerControl tmlayer = innerControl.NewLayerControl(sl as ShapeLayer, true);
                        innerControl.AddLayer(tmlayer, ShapeAddMode.Clone);
                        tmlayer.Shape.Zoom = item.Shape.Zoom;
                    }
                }
                else
                {
                    //LayerControl layerControl = innerControl.GetLayerControl(item.Shape);
                    
                    //if (layerControl != null)
                    //{
                    //    bool isBackGround = layerControl.Shape.IsBackground;
                    //    ShapeLayer item = layerControl.Layer.Copy();
                    //    item.Shape = item.Shape.Copy();
                    //    item.Shape.Move(Point.Empty);
                    //    if (isBackGround)
                    //    {
                    //        item.Shape.BeginEdit();
                    //        item.Shape.IsBackground = false;
                    //        item.Shape.EndEdit();
                    //    }
                    //    innerControl.AddLayer(innerControl.NewLayerControl(item, true), ShapeAddMode.Clone);
                    //    if(isBackGround)
                    //        item.Shape.IsBackground = isBackGround;
                    //}
                    //else
                    //{
                        bool isBackGround = item.Layer.Shape.IsBackground;
                        if (isBackGround)
                        {
                            item.Layer.Shape.BeginEdit();
                            item.Layer.Shape.IsBackground = false;
                            item.Layer.Shape.EndEdit();
                        }
                        var sl = item.Layer.Copy();
                        sl.Shape.Move(Point.Empty);
                        innerControl.AddLayer(innerControl.NewLayerControl(sl as ShapeLayer, true), ShapeAddMode.Clone);
                        
                        if(isBackGround)
                            item.Layer.Shape.IsBackground = isBackGround;
                    //}
                }
            }
            innerControl.ShapeControl.Invalidate();
            return true;
        }
    }
}
