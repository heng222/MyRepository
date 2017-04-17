//---------------------------------------------------------------------
//
// File: DragDropPanel.cs
//
// Description:
// User Control of FrameLayerNew 
//
// Author: Jerry Xu
//
// Date:2008-8-22
//
// Modify history:
//      Jerry Xu 2008-8-14 Add method:InsertLibrary,Insert,MoveMessage,RefreshView,RemoveAt
//      Jerry Xu 2008-8-22 Add item move up and down
//      Jerry Xu 2008-8-27 Update method:SetCtrlForExitEffect->Drag forward(Time label) 
//      Jerry Xu 2008-8-28 Update method:CompareToMaxTimeLen(int pos)->
//                else
//                {
//                    if (_trackBarCtrl != null)
//                    {
//                        _trackBarCtrl.TimeEnd = pos;
//                    }
//                }
//      Jerry Xu 2008-8-28 Add method:SetTimeEnd
//      Jerry Xu 2009-4-10 Update event:TimeSpan_Move(object sender, EventArgs e)
//      Jerry Xu 2009-4-14 Add method:SetCtrlForEnryEffectImport(),SetCtrlForTimeSpanImport
//      Jerry Xu 2009-5-18 Update method:LoadEffect()
//      Jerry Xu 2009-5-18 Update method:RemoveEffect(EffectType effectType)
//      Jerry Xu 2009-5-19 Update method:AddEffect(LayerEffect effect),AddEffectFromDragDrop(LayerEffect effect)
//      Jerry Xu 2009-5-20 Update method:CompareToMaxTimeLen(int pos, int timePanelWidth)
//      Jerry Xu 2009-5-21 Update method:AppendEffect(EffectType effectType)
//                         CompareToMaxTimeLen(int pos, int timePanelWidth) 
//      Jerry Xu 2009-5-22 Update method:CompareToMaxTimeLen(int pos, int timePanelWidth)
//      Jerry Xu 2009-5-25 Add method:MoveUpdateEffect(),UpdateEffect(EffectType effectType)
//                                      SetMaxWidth(),SetMaxWidth(int width)
//      Jerry Xu 2009-5-26 Update method:RemoveEffect(EffectType effectType),AddEffect(LayerEffect effect)
//                         Update method:AddEffectFromDragDrop(LayerEffect effect)
//      Jerry Xu 2009-6-1  Update method:CompareToMaxTimeLen(int pos, int timePanelWidth)
//      Jerry Xu 2009-6-2  Update method:MoveLayerToPlayValue(int playValue)
//      Jerry Xu 2009-6-3  Update method:AddEffectFromDragDrop(LayerEffect effect)
//      Jerry Xu 2009-6-4  Update method:AppendEffect(EffectType effectType),SetEffectOnSelected(EffectType type)
//      Jerry Xu 2009-6-5  Update method:AddEffectFromDragDrop(LayerEffect effect)
//      Jerry Xu 2009-6-5  Update method:AddEffect(LayerEffect effect)
//      Jerry Xu 2009-6-5  Update method:RemoveEffect(EffectType effectType)
//      Jerry Xu 2009-6-16 Update method:RemoveEffect(EffectType effectType)
//      Jerry Xu 2009-6-23 Add method:AddEffectFromMultiSelected(LayerEffect effect)
//                         Add property:CurrentDragLayer
//      Jerry Xu 2009-6-24 Update method:SetEffectOnSelected(EffectType type)
// 
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
//using System.ComponentModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Data;
using System.IO;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using DesEffect = ProWrite.Entity.DES.Effect;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Editor
{
    public partial class LayerControl : ControlBase
    {
        internal class _
        {
            public const int Height = 27;
            public const int DefaultWidth = 20;
            public static int OrgiTimePanelLeft = 198;
            public const int DefaultScrollWidth = 50;
            public const int ScrollWidth = 512;
        }

        public int Index;
        public bool CurrentDragLayer = false;
        public LayerControl(ShapeLayer m_layer, bool isNewLayer)
        {
            Check.Require(m_layer, "item", Check.NotNull);
            Index = -1;
            InitializeComponent();
            foresidePanel.Controls.Add(_nameEditor);
            _nameEditor.Visible = false;
            BorderStyle = BorderStyle.FixedSingle;
            _isNewLayer = isNewLayer;
            _shapeLayer = m_layer;
            _layer = new LayerAdapter(this, m_layer);
        }

        #region Fields

        private ShapeLayer _shapeLayer;

        private static LayerControl _current;
        private static LayerControl _currentdrag;
        private static LayerControl _currentshif;
        private bool _IsSelected = false;
        private LayerAdapter _layer;
        private bool _isNewLayer;

        private TrackBarNew _trackBarCtrl = null;
        private DevExpress.XtraEditors.HScrollBar hScrollBarCtrl = null;

        //public event EventHandler SetEntryOnSelectedLayer = null;
        //public event EventHandler SetEmphasisOnSelectedLayer = null;
        //public event EventHandler SetExitOnSelectedLayer = null;

        public event EventHandler SetCtrlSelectedLayer = null;
        public event EventHandler SetShiftSelectedLayer = null;
        public event Action<EffectType> SetEntryOnSelectedLayer = null;
        public event Action<EffectType> SetEmphasisOnSelectedLayer = null;
        public event Action<EffectType> SetExitOnSelectedLayer = null;
        public event Action UpdateShapeVisible;

        private NameEditor _nameEditor = new NameEditor();
        #endregion

        #region 层操作事件

        private void SetInputFocus()
        {
            //BorderStyle = BorderStyle.FixedSingle;
            lblLayerName.BackColor = ControlService.MouseDownColor;
            ControlService.EnableCopyMenu(true);
        }

        private void LostInputFocus()
        {
            //BorderStyle = BorderStyle.None;
            lblLayerName.BackColor = ControlService.MouseLeaveColor;
            ControlService.EnableCopyMenu(false);
        }

        #endregion

        #region Layer Name Set
        public void ChangeName()
        {
            string title = Resource.GetString(Resource.Strings.MessageChangeLayerName);
            string newName = InputDialog.GetInputValue(title, lblLayerName.Text);
            if (string.IsNullOrEmpty(newName))
                return;

            lblLayerName.Text = newName;
        }


        #endregion

        #region 层设置

        public void SetMaxWidth()
        {
            SetMaxWidth(0);
        }

        public void SetMaxWidth(int width)
        {
            if (ctlExitEffect.Visible)
                CompareToMaxTimeLen(ctlExitEffect.Right + Constance.Effect.SplitterWidth + width);
            else
                CompareToMaxTimeLen(ctlEmphasis.Right + Constance.Effect.SplitterWidth + width);
        }

        public void CompareToMaxTimeLen(int pos)
        {
            CompareToMaxTimeLen(pos, this.Width - foresidePanel.Width);
        }



        public void CompareToMaxTimeLen(int pos, int timePanelWidth)
        {
            int timeLength = 0;
            if (_populateTimeLength == null)
                return;
            if (!_populateTimeLength(_layer.ID, pos))
                return;

            if (pos >= EffectContainer.ClientRectangle.Right - _.DefaultWidth)
            {
                timeLength = EffectContainer.Width + timePanelWidth + _.ScrollWidth;
                effectHook._lastEffectContainerWidth += timePanelWidth + _.ScrollWidth;
                EffectContainer.Width += timePanelWidth + _.ScrollWidth;
                this.plRight.Width += timePanelWidth + _.ScrollWidth;
                //EffectContainer.Width += _.ScrollWidth;
                //this.Width += timePanelWidth + _.ScrollWidth;

                if (_trackBarCtrl != null)
                {
                    _trackBarCtrl.Width += timePanelWidth + _.ScrollWidth;
                }

                if (hScrollBarCtrl != null)
                {
                    hScrollBarCtrl.Maximum = timeLength - hScrollBarCtrl.Width;
                    hScrollBarCtrl.Minimum = 0;
                }
            }
            else
            {

                //EffectContainer.Width = pos;
                if (_trackBarCtrl != null)
                {
                    SetTimeEnd(pos);
                }
            }
        }

        public void AdjustMaxTimeLen(int timepanelWidth)
        {
            if (ctlExitEffect.Visible)
                CompareToMaxTimeLen(ctlExitEffect.Right, timepanelWidth);
            else
                CompareToMaxTimeLen(ctlEmphasis.Right, timepanelWidth); //CompareToMaxTimeLen(AfterTimeSpan.Right, timepanelWidth);
        }

        /// <summary>
        /// Function: Set trackbar time end
        /// Author  : Jerry Xu
        /// Date    : 2008-8-28
        /// </summary>
        /// <param name="pos">int</param>
        private void SetTimeEnd(int pos)
        {
            _trackBarCtrl.TimeEnd = pos;
        }


        public void AddEffectFromDragDrop(LayerEffect effect)
        {
            _effects[effect.Type].Value.IsDragEffect = true;
            //TODO:
            switch (effect.Type)
            {
                case EffectType.Entry:

                    if (ctlEntryEffect.Visible == false)
                    {
                        splitter2.Visible = true;
                        ctlEntryEffect.Width = effect.Width -Constance.Effect.SplitterWidth;
                        ctlEntryEffect.Visible = true;
                        //plRight.Width -= effect.Width;
                    }

                    ctlEntryEffect.Effect.FromTo( effect);

                    //effect.Left = ctlEntryEffect.Left;
                    //effect.Width = ctlEntryEffect.Width;

                    if (this.IsSelected)
                        if (SetEntryOnSelectedLayer != null)
                            SetEntryOnSelectedLayer(EffectType.Entry);
                    ctlEntryEffect.Invalidate();
                    break;
                case EffectType.Emphasis:
                    ctlEmphasis.Effect.FromTo(effect);
                    var width = ctlEmphasis.Width;
                    effect.Left = ctlEmphasis.Left;
                    effect.Width = ctlEmphasis.Width;
                    ctlEmphasis.Width = width; //-Constance.Effect.SplitterWidth - Constance.Effect.SplitterWidth;
                    if (this.IsSelected)
                        if (SetEmphasisOnSelectedLayer != null)
                            SetEmphasisOnSelectedLayer(EffectType.Emphasis);
                    ctlEmphasis.Invalidate();
                    break;
                case EffectType.Exit:

                    if (ctlExitEffect.Visible == false)
                    {
                        ctlExitEffect.Visible = true;
                        ctlExitEffect.Width = effect.Width -Constance.Effect.SplitterWidth;
                        splitter4.Visible = true;
                        //plRight.Width -= effect.Width;
                    }

                    ctlExitEffect.Effect.FromTo(effect);
                    //effect.Left = ctlExitEffect.Left;
                    //effect.Width = ctlExitEffect.Width;
                    if (this.IsSelected)
                        if (SetExitOnSelectedLayer != null)
                            SetExitOnSelectedLayer(EffectType.Exit);
                    ctlExitEffect.Invalidate();
                    break;
            }
            MessageControl.Current.ChangedService.MarkChanged();
        }

        public void AddEffectFromMultiSelected(LayerEffect effect)
        {
            _effects[effect.Type].Value.IsDragEffect = true;
            //TODO:
            switch (effect.Type)
            {
                case EffectType.Entry:

                    if (ctlEntryEffect.Visible == false)
                    {
                        splitter2.Visible = true;
                        ctlEntryEffect.Width = effect.Width -Constance.Effect.SplitterWidth;
                        ctlEntryEffect.Visible = true;
                        //plRight.Width -= effect.Width;
                    }

                    ctlEntryEffect.Effect.FromTo(effect);

                    effect.Left = ctlEntryEffect.Left;
                    effect.Width = ctlEntryEffect.Width;

                    ctlEntryEffect.Invalidate();
                    break;
                case EffectType.Emphasis:
                    ctlEmphasis.Effect.FromTo(effect);
                    var width = ctlEmphasis.Width;
                    effect.Left = ctlEmphasis.Left;
                    effect.Width = ctlEmphasis.Width;
                    ctlEmphasis.Width = width; //-Constance.Effect.SplitterWidth - Constance.Effect.SplitterWidth;

                    ctlEmphasis.Invalidate();
                    break;
                case EffectType.Exit:

                    if (ctlExitEffect.Visible == false)
                    {
                        ctlExitEffect.Visible = true;
                        ctlExitEffect.Width = effect.Width -Constance.Effect.SplitterWidth;
                        splitter4.Visible = true;
                        //plRight.Width -= effect.Width;
                    }

                    ctlExitEffect.Effect.FromTo(effect);
                    effect.Left = ctlExitEffect.Left;
                    effect.Width = ctlExitEffect.Width;

                    ctlExitEffect.Invalidate();
                    break;
            }
        }

        public void AddEffect(LayerEffect effect)
        {
            long effectRight = effect.Left + effect.Duration * Constance.TrackBar.UnitWidth;
            if (effectRight >= this.EffectContainer.Width)
            {
                this.SetMaxWidth((int)effectRight);
            }

            _effects[effect.Type].Value.IsDragEffect = false;
            switch (effect.Type)
            {
                case EffectType.Entry:
                    ctlEntryEffect.Effect.FromTo(effect);
                    if (ctlEntryEffect.Visible == false)
                    {
                        splitter2.Visible = true;
                        ctlEntryEffect.Width = effect.Width -Constance.Effect.SplitterWidth;
                        ctlEntryEffect.Visible = true;
                    }
                    ctlEntryEffect.Invalidate();
                    break;
                case EffectType.Emphasis:
                    ctlEmphasis.Effect.FromTo(effect);
                    ctlEmphasis.Invalidate();
                    break;

                case EffectType.Exit:
                    ctlExitEffect.Effect.FromTo(effect);
                    if (ctlExitEffect.Visible == false)
                    {
                        ctlExitEffect.Width = effect.Width - Constance.Effect.SplitterWidth;
                        ctlExitEffect.Visible = true;
                        splitter4.Visible = true;
                    }
                    ctlExitEffect.Invalidate();
                    break;
            }
            //plRight.Width = EffectContainer.Width - plLeft.Width - this.EntryEffect.Width - this.EmphasisEffect.Width -
            //this.ExitEffect.Width;
        }



        /// <summary>
        /// 删除效果
        /// add by Michael
        /// </summary>
        public void RemoveEffect(EffectType effectType)
        {
            const string none = LayerEffect.NoneString;
            if (effectType == EffectType.Entry)
            {
                splitter2.Visible = false;
                ctlEntryEffect.Visible = false;
                plRight.Width += ctlEntryEffect.Effect.Width;
                //ctlEntryEffect.Effect.BeginEdit();
                ctlEntryEffect.Effect.Name = none;
                ctlEntryEffect.Effect.GUID = Guid.Empty;
                ctlEntryEffect.Effect.Width = 0;
                ctlEntryEffect.Width = 0;
                //ctlEntryEffect.Effect.EndEdit();
            }
            else if (effectType == EffectType.Emphasis || effectType == EffectType.None)
            {
                //ctlEmphasis.Effect.BeginEdit();
                ctlEmphasis.Effect.Type = EffectType.None;
                ctlEmphasis.Effect.Name = none;
                ctlEmphasis.Effect.GUID = Guid.Empty;
                //ctlEmphasis.Effect.EndEdit();
                ctlEmphasis.Invalidate();
            }
            else if (effectType == EffectType.Exit)
            {
                splitter4.Visible = false;
                ctlExitEffect.Visible = false;
                plRight.Width += ctlExitEffect.Effect.Width;
                //ctlExitEffect.Effect.BeginEdit();
                ctlExitEffect.Effect.Name = none;
                ctlExitEffect.Effect.Width = 0;
                ctlExitEffect.Width = 0;
                ctlExitEffect.Effect.GUID = Guid.Empty;
                //ctlExitEffect.Effect.EndEdit();

                SetMaxWidth();
                //if (ctlExitEffect.Visible)
                //    CompareToMaxTimeLen(ctlExitEffect.Right);
                //else
                //    CompareToMaxTimeLen(ctlEmphasis.Right);
            }
            MessageControl.Current.ChangedService.MarkChanged();
            MoveUpdateEffect();
            //Invalidate();
            ControlService.PropertyGrid.Refresh();
        }

        /// <summary>
        /// 在加载一个层时判断是否需要对效果进行设置
        /// add by Michael
        /// </summary>
        private void AdjustEffectCtlProperties()
        {
            if (_layer.Duration > 0)
            {
                plLeft.Width = (int)_layer.StartTime * Constance.TrackBar.UnitWidth;

                if (!ctlEntryEffect.Effect.IsEmpty)
                    AddEffect(_layer.EntryEffect);
                //if (!ctlEmphasis.Effect.IsEmpty)
                AddEffect(_layer.EmphasisEffect);
                if (!ctlExitEffect.Effect.IsEmpty)
                    AddEffect(_layer.ExitEffect);
            }
        }

        /// <summary>
        /// 设置效果控件的偏移量和宽度
        /// add by Michael
        /// </summary>
        private void AppendEffect(EffectType effectType)
        {
            if (effectType == EffectType.Entry)
            {
                if (ctlEntryEffect.Visible == false)
                {
                    splitter2.Visible = true;
                    ctlEntryEffect.Visible = true;
                    ctlEntryEffect.Width = 2 * Constance.Effect.UnitWidth - Constance.Effect.SplitterWidth;
                    //plRight.Width -= ctlEntryEffect.EffectWidth;
                }
            }
            else if (effectType == EffectType.None)
            {
                ctlEmphasis.Effect.Type = EffectType.Emphasis;
                //plRight.Width -= ctlEmphasis.Effect.Width;
                ctlEmphasis.Refresh();
            }
            else if (effectType == EffectType.Emphasis)
            {
                ctlEmphasis.Refresh();
                //ctlEmphasis.Width = 8 * Constance.Effect.UnitWidth - Constance.Effect.SplitterWidth - Constance.Effect.SplitterWidth;
            }
            else if (effectType == EffectType.Exit)
            {
                if (ctlExitEffect.Visible == false)
                {
                    ctlExitEffect.Width = 2 * Constance.Effect.UnitWidth - Constance.Effect.SplitterWidth;
                    ctlExitEffect.Visible = true;
                    splitter4.Visible = true;
                    //plRight.Width -= ctlExitEffect.EffectWidth;
                }
            }

        }

        public void MoveUpdateEffect()
        {
            if (!ctlEntryEffect.Effect.IsEmpty)
                UpdateEffect(EffectType.Entry);
            //if (!ctlEmphasis.Effect.IsEmpty)
            UpdateEffect(EffectType.Emphasis);
            if (!ctlExitEffect.Effect.IsEmpty)
                UpdateEffect(EffectType.Exit);
        }

        /// <summary>
        /// 设置效果控件的偏移量和宽度
        /// add by Michael
        /// </summary>
        private void UpdateEffect(EffectType effectType)
        {
            switch (effectType)
            {
                case EffectType.Entry:
                    _layer.EntryEffect.Left = ctlEntryEffect.Left - Constance.Effect.SplitterWidth;
                    break;
                case EffectType.Emphasis:
                    _layer.EmphasisEffect.Left = ctlEmphasis.Left - Constance.Effect.SplitterWidth;
                    break;
                case EffectType.Exit:
                    _layer.ExitEffect.Left = ctlExitEffect.Left - Constance.Effect.SplitterWidth;
                    break;
            }
        }

        /// <summary>
        /// 设置滚动条状态
        /// add by Michael
        /// </summary>
        private void SetScrollBar(EffectLabel ctr)
        {
            if (_trackBarCtrl != null)
            {
                _layer.Shape.IsVisible = true;
            }

            if (hScrollBarCtrl != null)
            {

                if (ctr.Left < _.OrgiTimePanelLeft - ctlEmphasis.Left + _.DefaultScrollWidth)
                {
                    if (hScrollBarCtrl.Value - _.DefaultScrollWidth < 0)
                    {
                        hScrollBarCtrl.Value = 0;
                    }
                    else
                    {
                        hScrollBarCtrl.Value -= _.DefaultScrollWidth;
                    }
                }

                if (ctr.Right > _.OrgiTimePanelLeft - ctlEmphasis.Left + hScrollBarCtrl.Width - _.DefaultScrollWidth)
                {
                    if (hScrollBarCtrl.Value + _.DefaultScrollWidth > hScrollBarCtrl.Maximum)
                    {
                        hScrollBarCtrl.Value = hScrollBarCtrl.Maximum;
                    }
                    else
                    {
                        hScrollBarCtrl.Value += _.DefaultScrollWidth;
                    }
                }
            }
        }

        public void MoveLayerToPlayValue(int playValue)
        {
            //移动EntryEffect
            if (plLeft.Width == 0)
                plLeft.Width = playValue * Constance.TrackBar.UnitWidth;
            plRight.Width -= playValue * Constance.TrackBar.UnitWidth;

            if (ctlExitEffect.Visible)
                CompareToMaxTimeLen(ctlExitEffect.Right);
            else
                CompareToMaxTimeLen(ctlEmphasis.Right);

            if (UpdateShapeVisible != null)
                UpdateShapeVisible();
        }

        /// <summary>
        /// 对已选择的层进行效果设置
        /// add by Kevin
        /// </summary>
        public void SetEffectOnSelected(EffectType type)
        {
            //TODO:
            if (CurrentDrag != null)
            {
                EffectLabel effectLabel = _effects[type].Value;
                if (effectLabel.Effect.Width == 0)
                    effectLabel.Effect.Width = 2 * Constance.TrackBar.UnitWidth;
                AppendEffect(type);

                LayerEffect dragEffect = CurrentDrag._effects[type].Value.Effect.Real;
                //LayerEffect effect = effectLabel.Effect;
                LayerEffect effect = dragEffect.Create();
                effect.GUID = dragEffect.GUID;
                effect.Name = dragEffect.Name;
                effect.Type = type;

                AddEffectFromMultiSelected(effect);
            }
        }

        #endregion


        public class NameEditor : RichTextBox
        {
            public NameEditor()
            {
                this.AllowDrop = true;
                this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
                this.ForeColor = System.Drawing.Color.ForestGreen;
                this.Location = new System.Drawing.Point(62, 2);
                this.Margin = new System.Windows.Forms.Padding(0);
                this.Size = new System.Drawing.Size(136, 25);
                this.Text = "";
                this.Visible = false;
            }
            public static readonly NameEditor Instance = new NameEditor();

        }

        public bool IsVisible
        {
            get { return lblVisible.Visible; }
            set { lblVisible.Visible = value;}
        }

        protected internal class LayerAdapter : IShapeLayer
        {  
            private LayerControl _layerControl;
            private ShapeLayer _shapeLayer;
            private EffectLabel.EffectAdapter _emphasisEffect;
            private EffectLabel.EffectAdapter _entryEffect;
            private EffectLabel.EffectAdapter _exitEffect;

            public bool HasEmphasisEffect { get { return _emphasisEffect != null; } }
            public bool HasEntryEffect { get { return _entryEffect != null; } }
            public bool HasExitEffect { get { return _exitEffect != null; } }

            private void storeLayer()
            {
                _shapeLayer.Name = _layerControl.lblLayerName.Text;
                _shapeLayer.IsVisible = _layerControl.lblVisible.EditValue != null;
                if (_emphasisEffect != null)
                {
                    _shapeLayer.SetEffect(_layerControl.ctlEmphasis.Effect.Real, false);
                    _shapeLayer.SetEffect(_layerControl.ctlEntryEffect.Effect.Real, false);
                    _shapeLayer.SetEffect(_layerControl.ctlExitEffect.Effect.Real, false);
                }
            }

            public LayerAdapter (LayerControl layerControl, ShapeLayer shapeLayer)
            {
                this._layerControl = layerControl;
                _shapeLayer = shapeLayer;
                _layerControl.lblLayerName.Text = shapeLayer.Name;
                _layerControl.lblVisible.EditValue = (shapeLayer.IsVisible ? Resource.GetImage(Resource.Images.VisiableLayer) : null);
                //LoadEffect(shapeLayer);
            }

            internal void InitEffectAdapter(ShapeLayer shapeLayer)
            {
                if (_emphasisEffect == null)
                {
                    _emphasisEffect = new EffectLabel.EffectAdapter(shapeLayer.EmphasisEffect, _layerControl.ctlEmphasis, _layerControl);
                    _entryEffect = new EffectLabel.EffectAdapter(shapeLayer.EntryEffect, _layerControl.ctlEntryEffect, _layerControl);
                    _exitEffect = new EffectLabel.EffectAdapter(shapeLayer.ExitEffect, _layerControl.ctlExitEffect, _layerControl);
                }
            }

            //internal void LoadEffect()
            //{
            //    InitEffectAdapter(_shapeLayer);
            //}

            public int ID
            {
                get { return _shapeLayer.ID;}
            }

            public IShapeLayer Real
            {
                get
                {
                    storeLayer();
                    return _shapeLayer;
                }
            }

            public IShapeLayer Copy()
            {
                //_shapeLayer.Name = Name;
                //_shapeLayer.IsVisible = IsVisible;
                ////_shapeLayer.StartTime = 0;
                storeLayer();
                return _shapeLayer.Copy();

            }

            internal EffectLabel.EffectAdapter this[EffectType effectType]
            {
                get
                {
                    switch (effectType)
                    {
                        case EffectType.Exit:
                            return _exitEffect;
                        case EffectType.Entry:
                            return _entryEffect;
                        default:
                            return _emphasisEffect;
                    }
                }
            }

            public void SetEffect(LayerEffect effect, bool isDragDrop)
            {
                _shapeLayer.SetEffect(effect, isDragDrop);
            }

            public ShapeBase Shape
            {
                get
                { return _shapeLayer.Shape; }
                set { _shapeLayer.Shape = value; }
            }

            public bool IsDynamicLayer
            {
                get { return _shapeLayer.IsDynamicLayer; }
            }

            public string Name
            {
                get { return _layerControl.lblLayerName.Text; }
                set { _layerControl.lblLayerName.Text = value; }
            }

            public float Duration
            {
                get { return EndTime - StartTime; }
            }

            public float StartTime
            {
                get
                {
                    if (_layerControl.ctlEntryEffect.Width == 0)
                        return (int)(_layerControl.ctlEmphasis.Left - Constance.Effect.SplitterWidth) / Constance.TrackBar.UnitWidth;
                    else
                        return (int)(_layerControl.ctlEntryEffect.Left - Constance.Effect.SplitterWidth) / Constance.TrackBar.UnitWidth;
                }
            }

            public float EndTime
            {
                get
                {
                    if (_layerControl.ctlEmphasis.Width == 0)
                        return 0;
                    int temp = (int)StartTime + (int)(_layerControl.ctlEmphasis.Width + 2 * Constance.Effect.SplitterWidth) / Constance.TrackBar.UnitWidth;
                    if (_layerControl.ctlEntryEffect.Width != 0)
                        temp += (int)(_layerControl.ctlEntryEffect.Width + Constance.Effect.SplitterWidth) / Constance.TrackBar.UnitWidth;
                    if (_layerControl.ctlExitEffect.Width != 0)
                        temp += (int)(_layerControl.ctlExitEffect.Width + Constance.Effect.SplitterWidth) / Constance.TrackBar.UnitWidth;
                    return temp;

                    //return (int)(_layerControl.LayerRight / Constance.TrackBar.UnitWidth);
                }
            }

            public bool IsVisible
            {
                get { return _layerControl.lblVisible.EditValue != null; }
                set
                {
                    _layerControl.lblVisible.EditValue = (value ? Resource.GetImage(Resource.Images.VisiableLayer) : null);
                    _layerControl.UpdateShapeVisible();
                }
            }

            public LayerEffect EmphasisEffect
            {
                get { return _emphasisEffect.Real; }
                set { _emphasisEffect.FromTo(value); }
            }

            public LayerEffect EntryEffect
            {
                get { return _entryEffect.Real; }
                set { _entryEffect.FromTo(value); }
            }

            public LayerEffect ExitEffect
            {
                get { return _exitEffect.Real; }
                set { _exitEffect.FromTo(value); }
            }

            [NonSerialized]
            public EventHandler<ProWrite.Entity.PropertyChangedEventArgs> PropertyChanged;

            /// <summary>
            /// Update frame item control
            /// </summary>
            /// <param name="propertyName">property name</param>
            private void OnPropertyChanged(string propertyName, object newValue, object oldValue)
            {
                if (IsEdit)
                    return;
                if (PropertyChanged != null)
                    PropertyChanged(this, new ProWrite.Entity.PropertyChangedEventArgs(propertyName, newValue, oldValue));
            }

            [NonSerialized]
            private int _editLevel = 0;
            [Browsable(false)]
            public bool IsEdit
            {
                get { return _editLevel > 0; }
            }

            #region IEditableObject Members

            public void BeginEdit()
            {
                _editLevel++;
            }

            public void CancelEdit()
            {
                _editLevel--;
            }

            public void EndEdit()
            {
                _editLevel--;
            }

            #endregion


        }
    }
}
