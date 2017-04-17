//---------------------------------------------------------------------
//
// File: MessageControlNew.LayerContainer.cs
//
// Description:
// The control is MessageControlNew.LayerContainer.
//
// Author: 
//
// DateTime:
//
// Modify history:
//      Jerry Xu 2008-8-27 Update method:InternalAddLayer->frameLayer.TrackBarCtrl.TimeEnd = totalTimeLen;
//      Jerry Xu 2009-5-22 Update method:AutomaticSnapLayers()
//      Jerry Xu 2009-6-1  Update method:SnapLayers(Control layerContainer)
//      Jerry Xu 2009-6-4  Update method:SetShapeVisible(LayerControl frameLayer)
//      Jerry Xu 2009-6-9  Update method:SnapLayers(Control layerContainer)
//      Jerry Xu 2009-6-23 Add method:SetEffectOnSelectedLayer(EffectType type)
//      Jerry Xu 2009-6-24 Update method:SetEffectOnSelectedLayer(EffectType type)
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraNavBar;
using System.ComponentModel;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using System.Windows.Forms;
using System.Drawing;

namespace ProWrite.UI.Controls.Editor
{
    public partial class MessageControl
    {
        private int _id = 0;
        private Dictionary<int, int> _timeLens;
        private bool _IsShowAllLayers = false;
        private LayerControlContextMenu mnuControl;
        //private MasterLayerControlContextMenu mnuMasterControl;

        #region Properties define
        private int totalTimeLen;
        /// <summary>
        /// get or set the total message playing time
        /// edir by Michael 2008-10-14
        /// </summary>
        public int TotalTimeLen
        {
            get
            {
                int messageLen = 0;

                foreach (LayerControl frameLayer in _dynamicContainer.Controls)
                {
                    if (frameLayer.Layer.IsVisible && frameLayer.EndTime > messageLen)
                        messageLen = (int)frameLayer.Layer.EndTime;
                }

                foreach (LayerControl frameLayer in _staticContainer.Controls)
                {
                    if (frameLayer.Layer.IsVisible && frameLayer.EndTime > messageLen)
                        messageLen = (int)frameLayer.EndTime;
                }

                //if (MessageControl.Current.MasterLayerControl.EndTime > messageLen)
                //    messageLen = (int)MessageControl.Current.MasterLayerControl.EndTime;

                return messageLen;
            }
        }

        public ShapeLayer[] Layers
        {
            get
            {
                List<ShapeLayer> layers = new List<ShapeLayer>();
                for (int k = _dynamicContainer.Controls.Count - 1; k >= 0; k--)
                {
                    layers.Add((_dynamicContainer.Controls[k] as LayerControl).Layer.Copy() as ShapeLayer);
                }
                for (int i = _staticContainer.Controls.Count - 1; i >= 0; i--)
                {
                    layers.Add((_staticContainer.Controls[i] as LayerControl).Layer.Copy() as ShapeLayer);
                }
                return layers.ToArray();
            }
        }

        
        public bool IsShowAllLayers
        {
            get
            {
                return _IsShowAllLayers;
            }
            set
            {
                _IsShowAllLayers = value;
            }
        }
        #endregion

        #region Function define
        private void InitLayerContainer()
        {
            _timeLens = new Dictionary<int, int>();
            mnuControl = new LayerControlContextMenu(this);
            //mnuControl.Left = this.Left + 197;
            //mnuMasterControl = new MasterLayerControlContextMenu(this);
        }

        public int GetLayerIndex(LayerControl frameLayer)
        {
            Check.Require(frameLayer, "frameLayer", Check.NotNull);
            Control container = frameLayer.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            if (container.Controls.Contains(frameLayer))
                return container.Controls.GetChildIndex(frameLayer);
            else
                return container.Controls.Count;
        }

        public int GetLayerCount(LayerControl frameLayer)
        {
            Control container = frameLayer.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            return container.Controls.Count;
        }

        private void AllocateId()
        {
            while (_timeLens.ContainsKey(++_id))
                _id++;
        }

        public List<LayerControl> SelectedLayers
        {
            get
            {
                List<LayerControl> items = new List<LayerControl>();
                foreach (Control item in _staticContainer.Controls)
                {
                    LayerControl frame = item as LayerControl;
                    if (frame != null && frame.IsSelected)
                        items.Add(frame);
                }
                foreach (Control item in _dynamicContainer.Controls)
                {
                    LayerControl frame = item as LayerControl;
                    if (frame != null && frame.IsSelected)
                        items.Add(frame);
                }
                return items;
            }
        }

        public LayerControl GetLayerControl(ShapeBase shape)
        {
            if (shape == null)
                return null;
            Control container = shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;

            foreach (LayerControl frame in container.Controls)
            {
                if (frame.Shape == null)
                    continue;
                if (frame.Shape.ID == shape.ID)
                    return frame;
                else if (shape.LayerType == LayerType.Paint
                    && frame.Shape.LayerType == LayerType.Paint)
                {
                    if (frame.Shape.Type == ShapeType.ShapeDraw)
                    {
                       ShapeDraw sd = frame.Shape as ShapeDraw;
                       foreach (var s in sd.Childs)
                           if (s.ID == shape.ID)
                               return frame;
                       return null;
                    }
                }
            }
            return null;
        }

        public bool IsExistShapeDraw
        {
            get
            {
                bool isExist = false;
                foreach (LayerControl frame in _staticContainer.Controls)
                    isExist |= frame.Shape.Type == ShapeType.ShapeDraw;
                return isExist;
            }
        }

        internal LayerControl NewLayerControl(ShapeLayer layer, bool isAllocateId)
        {
            AllocateId();
            if (isAllocateId)
            {
                layer.ID = _id;
                layer.Name = "Layer " + _id.ToString();
            }
           //ControlService.SignCombo.Current.Template.Message.DisplayTime
            LayerControl frameLayer = new LayerControl(layer, isAllocateId);
            frameLayer.Dock = DockStyle.Top;
            frameLayer.TrackBarCtrl = trackBar1;
            frameLayer.HScrollBarCtrl = hScrollBar;
            SubscribeLayControlEvent(frameLayer);
            frameLayer.Layer.IsVisible = layer.IsVisible;
            if (layer.Shape.Type == ShapeType.DynamicText || layer.Shape.Type == ShapeType.Temperature || layer.Shape.Type == ShapeType.Time || layer.Shape.Type == ShapeType.DynamicVideo)
            {
                this.dynamicGroup.Expanded = true;
            }


            return frameLayer;
        }

        private void SubscribeLayControlEvent(LayerControl frameLayer)
        {         
            frameLayer.SetCtrlSelectedLayer += new EventHandler(SetCtrlSelectedLayer);
            frameLayer.SetShiftSelectedLayer += new EventHandler(SetShiftSelectedLayer);

            frameLayer.SetEntryOnSelectedLayer += SetEffectOnSelectedLayer;
            frameLayer.SetEmphasisOnSelectedLayer += SetEffectOnSelectedLayer;
            frameLayer.SetExitOnSelectedLayer += SetEffectOnSelectedLayer;
            frameLayer.PopulateTimeLength += new LayerControl.PopulateTimeLengthHandler(frameLayer_PopulateTimeLength);
            frameLayer.DragLayer += new LayerControl.DragLayerHandler(frameLayer_DragLayer);
            frameLayer.LayerMouseUp += new LayerControl.LayerMouseUpHandler(frameLayer_LayerMouseUp);
            frameLayer.UpdateShapeVisible += UpdateShapeVisible;
        }

        //private void SubscribeMasterLayerEvent(MasterLayerControl masterLayer)
        //{
        //    masterLayer.SetCtrlSelectedLayer += new EventHandler(SetCtrlSelectedLayer);
        //    masterLayer.LayerMouseUp += new MasterLayerMouseUpHandler(masterLayer_LayerMouseUp);
        //}
        
        //void masterLayer_LayerMouseUp(MasterLayerControl owner, Control sender, MouseEventArgs e)
        //{
        //    if (e.Button == MouseButtons.Right)
        //    {
        //        owner.IsSelected = true;
        //        mnuMasterControl.FrameLayer = owner;
        //        mnuMasterControl.Target = sender;
        //        this.mnuMasterControl.Show( MessageControl.Current.MasterLayerControl.PointToScreen(e.Location) );
        //    }
        //}

        void frameLayer_LayerMouseUp(LayerControl owner, Control sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                owner.IsSelected = true;
                mnuControl.FrameLayer = owner;
                mnuControl.Target = sender;
                this.mnuControl.Show(lblNew.PointToScreen(e.Location));
            }
            else if (e.Button == MouseButtons.Left)
            {
                //owner.StartTime = owner.
            }
        }


        bool frameLayer_PopulateTimeLength(int layerId, int pos)
        {
            if (!_timeLens.ContainsKey(layerId))
                return false;
            _timeLens[layerId] = pos;

            if (pos > totalTimeLen)
                totalTimeLen = pos;

            trackBar1.TimeEnd = totalTimeLen;

            return true;
        }

        void frameLayer_DragLayer(LayerControl target, LayerControl data)
        {
            MoveLayers(data, target);
            shapeControl.Invalidate();
        }

        
        public bool SetFrameLayerFocus(ShapeBase shape)
        {
            LayerControl frameLayer = GetLayerControl(shape);
            if (frameLayer != null)
            {
                frameLayer.IsSelected = true;
                return true;
            }
            return false;
        }

        public void UpdateScrollBar()
        {
           
        }


        #endregion

        #region Event define
        /// <summary>
        /// 当按住"Ctrl"键时，来选择不同的层
        /// add by Michael
        /// </summary>
        private void SetCtrlSelectedLayer(object o, EventArgs e)
        {
            foreach (LayerControl frameLayer in _dynamicContainer.Controls)
            {
                frameLayer.IsSelected = false;
            }
            foreach (LayerControl frameLayer in _staticContainer.Controls)
            {
                frameLayer.IsSelected = false;
            }

            //((MasterLayerControl)(_masterLayerContainer.Controls[0])).IsSelected = false;

            Invalidate();
        }

        /// <summary>
        /// 当按住"Shift"键时，来选择不同的层
        /// add by Michael
        /// </summary>
        private void SetShiftSelectedLayer(object o, EventArgs e)
        {
            if (LayerControl.CurrentShif.Shape.IsDynamicLayer != LayerControl.Current.Shape.IsDynamicLayer)
                return;
            int shifLayerIndex = GetLayerIndex(LayerControl.CurrentShif);
            int curLayerIndex = GetLayerIndex(LayerControl.Current);
            Control container = LayerControl.CurrentShif.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;

            foreach (LayerControl frameLayer in container.Controls)
            {
                int layerIndex = GetLayerIndex(frameLayer);

                if (layerIndex >= shifLayerIndex &&
                    layerIndex <= curLayerIndex)
                {
                    frameLayer.IsSelected = true;
                    SetShapeSelectedWithShift(frameLayer.Shape, true);
                }
                else if (layerIndex <= shifLayerIndex &&
                         layerIndex >= curLayerIndex)
                {
                    frameLayer.IsSelected = true;
                    SetShapeSelectedWithShift(frameLayer.Shape, true);
                }
                else
                {
                    frameLayer.IsSelected = false;
                    SetShapeSelectedWithShift(frameLayer.Shape, false);
                }
            }

            shapeControl.Invalidate();
        }

        private void SetShapeSelectedWithShift(ShapeBase shape,bool selected)
        {
            shape.BeginEdit();
            shape.IsSelected = selected;
            shape.EndEdit();
        }

        private void SetLayerControlByNetSelected(ShapeBase[] selectedShapes)
        {
            foreach (LayerControl frame in _dynamicContainer.Controls)
                frame.IsSelected = frame.Shape.IsSelected;
            
            foreach (LayerControl frame in _staticContainer.Controls)
            {
                frame.IsSelected = frame.Shape.IsSelected;
            }
            
            Invalidate();
        }

        /// <summary>
        /// 对已选择的层进行效果设置
        /// add by Kevin
        /// </summary>
        private void SetEffectOnSelectedLayer(EffectType type)
        {
            foreach (LayerControl frameLayer in _staticContainer.Controls)
            {
                if (frameLayer.IsSelected)
                {
                    if (!frameLayer.CurrentDragLayer)
                    {
                        frameLayer.SetEffectOnSelected(type);
                        frameLayer.MoveUpdateEffect();
                    }
                    //else
                        //frameLayer.CurrentDragLayer = false;
                }
            }
            foreach (LayerControl frameLayer in _dynamicContainer.Controls)
            {
                if (frameLayer.IsSelected)
                {
                    if (!frameLayer.CurrentDragLayer)
                    {
                        frameLayer.SetEffectOnSelected(type);
                        frameLayer.MoveUpdateEffect();
                    }
                    else
                        frameLayer.CurrentDragLayer = false;
                }
            }
        }

        private static void SnapLayers1(Control layerContainer)
        {
            int preID = -1;
            int count = 0;
            //Snap static Layers
            foreach (LayerControl frameLayer in layerContainer.Controls)
            {
                if (frameLayer.IsSelected)
                    count++;
            }

            for (int i = 0; i < layerContainer.Controls.Count; i++)
            {
                LayerControl item = layerContainer.Controls[i] as LayerControl;

                if (item.IsSelected)
                {
                    if (count == 1 && i > 0)
                        preID = i - 1;
                    if (preID > -1)
                    {
                        LayerControl prev = layerContainer.Controls[preID] as LayerControl;
                        int offset = prev.LayerRight - item.LayerLeft;
                        item.SetMaxWidth(offset);
                        item.PlRightWidth -= offset; ;
                        item.LayerLeft = prev.LayerRight;
                    }
                    preID = i;
                }


            }
        }

        private static void SnapLayers(Control layerContainer)
        {
            List<LayerControl> layers = new List<LayerControl>();
            LayerControl lastlayer = null;
            //Snap static Layers
            foreach (LayerControl frameLayer in layerContainer.Controls)
            {
                if (frameLayer.IsSelected)
                    layers.Add(frameLayer);
            }

            foreach (LayerControl item in layers)
            {
                if (lastlayer!=null)
                {
                    int offset = lastlayer.LayerRight - item.LayerLeft;
                    item.SetMaxWidth(offset);
                    item.PlRightWidth -= offset; 
                    item.LayerLeft = lastlayer.LayerRight;

                    item.MoveUpdateEffect();
                }
                lastlayer = item;
            }
            
        }

        /// <summary>
        /// 设置所选择层之间的对接状态
        /// add by michael
        /// </summary>
        public void AutomaticSnapLayers()
        {
            SnapLayers(_staticContainer);
            SnapLayers(_dynamicContainer);
            ChangedService.MarkChanged();
            UpdateShapeVisible();            
        }

        /// <summary>
        /// 当tracbar移动时设置shape是否显示
        /// add by michael
        /// </summary>
        public void UpdateShapeVisible()
        {
            foreach (LayerControl frameLayer in _staticContainer.Controls)
            {
                SetShapeVisible(frameLayer);
            }

            foreach (LayerControl frameLayer in _dynamicContainer.Controls)
            {
                SetShapeVisible(frameLayer);
            }
            shapeControl.Invalidate();
        }

        /// <summary>
        /// 设置当前层里的shape对象是否显示
        /// add by michael
        /// </summary>
        internal void SetShapeVisible(LayerControl frameLayer)
        {
            ShapeBase shape = frameLayer.Layer.Shape;
            shape.BeginEdit();
            if (_IsShowAllLayers)
            {
                if (frameLayer.Layer.IsVisible)
                {
                    //frameLayer.Layer.IsVisible = true;
                    frameLayer.Shape.IsVisible = true;
                    shape.IsVisible = true;
                }
                //return;
            }

            //else if (this.trackBar1.PlayValue < frameLayer.Layer.StartTime || this.trackBar1.PlayValue > frameLayer.Layer.EndTime)
            else if (frameLayer.StartTime <= this.trackBar1.PlayValue && frameLayer.EndTime > this.trackBar1.PlayValue)
            {
                if (frameLayer.Layer.IsVisible)
                {
                    //frameLayer.Layer.IsVisible = frameLayer.LayerVisible;
                    frameLayer.Shape.IsVisible = frameLayer.Layer.IsVisible;
                    shape.IsVisible = frameLayer.Layer.IsVisible;
                }
            }
            else if (frameLayer.StartTime > this.trackBar1.PlayValue || frameLayer.EndTime <= this.trackBar1.PlayValue)
            {
                if (frameLayer.Layer.IsVisible)
                {
                    //frameLayer.Layer.IsVisible = false;
                    frameLayer.Shape.IsVisible = false;
                    shape.IsVisible = false;
                }
            }

            shape.EndEdit();
            shapeControl.Invalidate();
        }
        #endregion
    }

    [Flags]
    public enum LayerDirection:byte
    {
        None = 1,
        First = 2,
        Forward = 4,
        Back = 8,
        Last = 16,
    }
}
