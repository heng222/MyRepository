using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.UndoRedo.Action;
using ProWrite.Core;
using System.Diagnostics;
using DevExpress.XtraEditors;
using PropertyChangedEventArgs=ProWrite.Entity.PropertyChangedEventArgs;

namespace ProWrite.UI.Controls.Editor
{
    [DebuggerDisplay("Name={lblLayerName.Text},Start={_layer.StartTime},EntryWidth={_Layer.EntryEffect.Width},EmphasisWidth={_Layer.EmphasisEffect.Width},ExitWidth={_Layer.EntryEffect.Width},End={_Layer.ExitEffect.Width},Duration={_layer.Duration}")]
    public partial class LayerControl
    {
        private Panel plLeft;
        private Panel plRight;
        private Splitter splitter1;
        private Splitter splitter2;
        private Splitter splitter3;
        private Splitter splitter4;

        public EffectLabel ctlEntryEffect;
        public EffectLabel ctlExitEffect;
        public EffectLabel ctlEmphasis;

        private Dictionary<EffectType, KeyValuePair<Splitter, EffectLabel>> _effects;

        private EffectMouseEventHook effectHook;

        public void AddNewLayerControlByShapeLayer(ShapeLayer layer)
        {
            AddNewLayerControlByShapeLayer(layer, false);
           
        }

        public void AddNewLayerControl()
        {
            _effects = new Dictionary<EffectType, KeyValuePair<Splitter, EffectLabel>>(3);

            AddNewLayerControlByShapeLayer(_shapeLayer, true);
        }

        public void AddNewLayerControlByShapeLayer(ShapeLayer layer, bool isCreateNewCtl)
        {
            //_effects = new Dictionary<EffectType, KeyValuePair<Splitter, EffectLabel>>(3);

            InitControl(isCreateNewCtl);


            EffectContainerAddEffectCtls();

            if (_layer != null)
                _layer.InitEffectAdapter(layer);
            if (isCreateNewCtl)
            {
                lblLayerName.Text = _layer.Name;
                lblLayerType.EditValue = Images.ImageList[(int) _layer.Shape.LayerType];
                if (_layer.Shape.LayerType == LayerType.Temp)
                    lblLayerType.ToolTip = "Temperature";
                else if (_layer.Shape.LayerType == LayerType.Image)
                    lblLayerType.ToolTip = "Picture";
                else
                    lblLayerType.ToolTip = _layer.Shape.LayerType.ToString();
            }
          
            AdjustEffectCtlProperties();
        }



        private void InitControl(bool createNewControl)
        {

            if (createNewControl)
            {
                this.plLeft = new PlaceHoldePanel();
                this.plRight = new PlaceHoldePanel();
                this.ctlEntryEffect = new EntryEffectLabel(this);
                this.ctlExitEffect = new ExitEffectLabel(this);
                this.ctlEmphasis = new EmphasisEffectLabel(this);
                this.effectHook = new EffectMouseEventHook(this);
                this.splitter1 = new EffectSplitterControl(this, plLeft);
                this.splitter2 = new EffectSplitterControl(this, ctlEntryEffect);
                this.splitter3 = new EffectSplitterControl(this, ctlEmphasis);
                this.splitter4 = new EffectSplitterControl(this, ctlExitEffect);
            }

            _.OrgiTimePanelLeft = this.EffectContainer.Left;
            this.EffectContainer.Width = ((this.ClientRectangle.Width - this.lblLayerName.Width - this.lblLayerType.Width - this.lblVisible.Width) / Constance.TrackBar.UnitWidth + 1) * Constance.TrackBar.UnitWidth;// +4;
            
            #region Init
            // 
            // plLeft
            // 
            this.plLeft.BackColor = EffectContainer.BackColor;
            this.plLeft.ForeColor = EffectContainer.ForeColor;
            this.plLeft.Dock = System.Windows.Forms.DockStyle.Left;
            this.plLeft.Location = new System.Drawing.Point(0, 0);
            this.plLeft.Name = "plLeft";
            this.plLeft.Size = new System.Drawing.Size(Constance.Effect.PlaceHolderWidth, 23);
            this.plLeft.TabIndex = 0;
            // 
            // splitter1
            // 
            this.splitter1.Name = "splitter1";
            this.splitter1.Dock = DockStyle.Left;
            this.splitter1.TabIndex = 1;

            // 
            // ctlEntryEffect
            // 
            this.ctlEntryEffect.Dock = System.Windows.Forms.DockStyle.Left;
            this.ctlEntryEffect.Location = new System.Drawing.Point(2, 0);
            this.ctlEntryEffect.Name = "ctlEntryEffect";
            this.ctlEntryEffect.Size = new System.Drawing.Size(0, 23);
            this.ctlEntryEffect.TabIndex = 4;
            this.ctlEntryEffect.Visible = false;
            // 
            // splitter2
            // 
            this.splitter2.Name = "splitter2";
            this.splitter2.Dock = DockStyle.Left;
            this.splitter2.TabIndex = 5;
            this.splitter2.Visible = false;
            // 
            // ecExit
            // 
            this.ctlExitEffect.Dock = System.Windows.Forms.DockStyle.Right;
            this.ctlExitEffect.Location = new System.Drawing.Point(148, 0);
            this.ctlExitEffect.Name = "ctlExitEffect";
            this.ctlExitEffect.Size = new System.Drawing.Size(0, 23);
            this.ctlExitEffect.TabIndex = 6;
            this.ctlExitEffect.Visible = false;
            // 
            // splitter3
            // 
            this.splitter3.Name = "splitter3";
            this.splitter3.Dock = DockStyle.Right;
            this.splitter3.TabIndex = 7;
            // 
            // TimeSpan
            // 
            this.ctlEmphasis.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ctlEmphasis.Location = new System.Drawing.Point(27, 0);
            this.ctlEmphasis.Name = "ctlEmphasis";
            //long ctlWidth = Shape.Type == ShapeType.Video
            //                   ? (Shape as ShapeVideo).VideoDuration
            //                   : ControlService.SignCombo.Current.Template.Message.DisplayTime;
            long ctlWidth;
            if(Shape.Type == ShapeType.Video)
            {
                long videoDuration = (Shape as ShapeVideo).VideoDuration;
                ctlWidth = (Shape.Type == ShapeType.Video && videoDuration != 0)
                                   ? (Shape as ShapeVideo).VideoDuration
                                   : ControlService.SignCombo.Current.Template.Message.DisplayTime;
            }
            else
            {
                ctlWidth =  ControlService.SignCombo.Current.Template.Message.DisplayTime; 
            }
            this.ctlEmphasis.Size = new System.Drawing.Size((int)ctlWidth * Constance.TrackBar.UnitWidth - splitter1.Width * 2, 23);
            this.ctlEmphasis.TabIndex = 8;
            
            // 
            // splitter4
            // 
            this.splitter4.Name = "splitter4";
            this.splitter4.Dock = DockStyle.Right;
            this.splitter4.TabIndex = 3;
            this.splitter4.Visible = false;

            //
            // plRight
            //
            this.plRight.BackColor = Color.WhiteSmoke;
            this.plRight.Dock = DockStyle.Right;
            this.plRight.Name = "plRight";
            int plRightWidth = this.EffectContainer.Width - (int)ctlWidth * Constance.TrackBar.UnitWidth;
            this.plRight.Size = new System.Drawing.Size(plRightWidth, 23);
            this.plRight.TabIndex = 2;
            #endregion
        }

        private void EffectContainerAddEffectCtls()
        {
            EffectContainer.Controls.Add(this.ctlEmphasis);
            EffectContainer.Controls.Add(this.splitter3);
            EffectContainer.Controls.Add(this.ctlExitEffect);
            EffectContainer.Controls.Add(this.splitter2);
            EffectContainer.Controls.Add(this.ctlEntryEffect);
            EffectContainer.Controls.Add(this.splitter4);
            EffectContainer.Controls.Add(this.plRight);
            EffectContainer.Controls.Add(this.splitter1);
            EffectContainer.Controls.Add(this.plLeft);
        }

        //Update effect data
        private static void ComputeEffectWidth(LayerControl ctl)
        {
            if (ctl.ctlEntryEffect.Visible)
            {
                ctl.EntryEffect.Left = ctl.ctlEntryEffect.Left - Constance.Effect.SplitterWidth;
                ctl.EntryEffect.Duration = (ctl.ctlEntryEffect.Width + Constance.Effect.SplitterWidth) / Constance.Effect.UnitWidth;                
            }

            if (ctl.ctlExitEffect.Visible)
            {
                ctl.ExitEffect.Duration = (ctl.ctlExitEffect.Width + Constance.Effect.SplitterWidth) / Constance.Effect.UnitWidth;
            }
            ctl.EmphasisEffect.Left = ctl.ctlEmphasis.Left - Constance.Effect.SplitterWidth;
            ctl.EmphasisEffect.Duration = (ctl.ctlEmphasis.Width + Constance.Effect.SplitterWidth + Constance.Effect.SplitterWidth) / Constance.Effect.UnitWidth;
        }

        //Update effect control
        private static void ComputeEffectWidth(LayerControl layerControl,EffectSplitterControl ctlsplit)
        {
            int errorWidth = ctlsplit.OffSet % Constance.Effect.UnitWidth;
            if (ctlsplit.OffSet < Constance.Effect.UnitWidth)
                errorWidth = ctlsplit.OffSet;
            bool isRight = ctlsplit.IsRight;
            if (ctlsplit.Name == "splitter1")
            {
                if (isRight)
                    layerControl.plLeft.Width -= errorWidth;
                else
                    layerControl.plLeft.Width += errorWidth;
            }
            else if (ctlsplit.Name == "splitter4")
            {
                if (isRight)
                    layerControl.plRight.Width += errorWidth;
                else
                    layerControl.plRight.Width -= errorWidth;
            }
            else if (ctlsplit.Name == "splitter2")
            {
                if (isRight)
                {
                    layerControl.ctlEntryEffect.Width -= errorWidth;

                }
                else
                {
                    layerControl.ctlEntryEffect.Width += errorWidth;
                }
            }
            else if (ctlsplit.Name == "splitter3")
            {
                if (layerControl.ctlExitEffect.Visible)
                {
                    if (isRight)
                    {
                        layerControl.ctlExitEffect.Width += errorWidth;
                    }
                    else
                    {
                        layerControl.ctlExitEffect.Width -= errorWidth;
                    }
                }
                else
                {
                    if (isRight)
                        layerControl.plRight.Width += errorWidth;
                    else
                        layerControl.plRight.Width -= errorWidth;
                }
            }
        }

        private static void ComputerCritical(LayerControl layerControl, EffectSplitterControl ctlsplit)
        {
            //computer critical value
            if (ctlsplit.Name == "splitter1")
            {
                if (layerControl.ctlEmphasis.Width < Constance.Effect.UnitWidth)
                    layerControl.plLeft.Width -= Constance.Effect.UnitWidth;
            }
            else if (ctlsplit.Name == "splitter4")
            {
                if (layerControl.ctlEmphasis.Width < Constance.Effect.UnitWidth)
                    layerControl.plRight.Width -= Constance.Effect.UnitWidth;
            }
            else if (ctlsplit.Name == "splitter2")
            {
                if (layerControl.ctlEntryEffect.Width < Constance.Effect.SplitterWidth)
                    layerControl.ctlEntryEffect.Width = Constance.Effect.SplitterWidth;
                if (layerControl.ctlEmphasis.Width < Constance.Effect.UnitWidth)
                    layerControl.ctlEntryEffect.Width -= Constance.Effect.UnitWidth;
            }
            else if (ctlsplit.Name == "splitter3")
            {
                if (layerControl.ctlExitEffect.Visible)
                {
                    if (layerControl.ctlExitEffect.Width < Constance.Effect.SplitterWidth)
                        layerControl.ctlExitEffect.Width = Constance.Effect.SplitterWidth;
                    if (layerControl.ctlEmphasis.Width < Constance.Effect.UnitWidth)
                        layerControl.ctlExitEffect.Width -= Constance.Effect.UnitWidth;
                }
                else
                {
                    if (layerControl.ctlEmphasis.Width < Constance.Effect.UnitWidth)
                        layerControl.plRight.Width -= Constance.Effect.UnitWidth;
                }
            }
        }

        private void SubscribeChildShapeEvent()
        {
            if (_layer.Shape.Type == ShapeType.ShapeDraw)
                (_layer.Shape as ShapeDraw).ChildShapeSelected += ChildShape_SelectedChanged;
        }

        private void UnSubscribeChildShapeEvent()
        {
            if (_layer.Shape != null
                && _layer.Shape.Type == ShapeType.ShapeDraw)
                (_layer.Shape as ShapeDraw).ChildShapeSelected -= ChildShape_SelectedChanged;
        }

        void Shape_SelectedChanged(object sender, EventArgs e)
        {
            if (_layer.Shape.IsSelected != IsSelected)
                IsSelected = _layer.Shape.IsSelected;
        }

        void ChildShape_SelectedChanged(object sender, EventArgs e)
        {
            ShapeDraw shape = _layer.Shape as ShapeDraw;
            if (shape.IsChildSelected != IsSelected)
                IsSelected = shape.IsChildSelected;
        }

        void layer_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.Name == ShapeLayer._.Name)
            {
                lblLayerName.Text = _layer.Name;
                this.lblLayerName.Text = _layer.Name;
            }
            if (e.Name == ShapeLayer._.IsVisible)
            {
                this.Layer.IsVisible = Convert.ToBoolean(e.NewValue);
            }
            UndoService.AddPropertyChangedAction(sender, e.Name, e.NewValue, e.OldValue);

        }

        [DebuggerDisplay("Width={Size.Width}")]
        private class EffectContinerControl : PanelControl
        {
        }

        [DebuggerDisplay("Width={Size.Width}")]
        private class PlaceHoldePanel : Panel { }

        [DebuggerDisplay("Width={Size.Width}")]
        internal class EffectSplitterControl : Splitter
        {
            private LayerControl _layerCtrl;
            private Control _relatedControl;
            private int _lastLeft = 0;
            public bool IsRight = true;
            public int OffSet = 0;
            public EffectSplitterControl(LayerControl layerCtrl, Control tag)
            {
                BackColor = SystemColors.ControlDarkDark;
                MinSize = MinExtra = 0;
                Size = new Size(Constance.Effect.SplitterWidth, 23);
                _relatedControl = tag;
                _layerCtrl = layerCtrl;

                var effectCtrl = _relatedControl as EffectLabel;
                if (effectCtrl != null)
                {
                    _layerCtrl._effects[effectCtrl.EffectType] = new KeyValuePair<Splitter, EffectLabel>(this, effectCtrl);
                    if(effectCtrl.EffectType == EffectType.Emphasis)
                        _layerCtrl._effects[EffectType.None] = _layerCtrl._effects[EffectType.Emphasis];
                    ;
                }
            }

            protected override void OnMouseDown(MouseEventArgs e)
            {
                base.OnMouseDown(e);
                _lastLeft = this.Left;
            }

            //protected override void OnMouseUp(MouseEventArgs e)
            //{
            //    base.OnMouseUp(e);
            //    if (e.X >= _lastLeft)
            //    {
            //        IsRight = true;
            //    }
            //    else
            //        IsRight = false;

            //}
            
            protected override void OnSplitterMoved(SplitterEventArgs sevent)
            {

                


                base.OnSplitterMoved(sevent);
                if (this.Left >= _lastLeft)
                {
                    OffSet = this.Left - _lastLeft;
                    IsRight = true;
                }
                else
                {
                    OffSet = _lastLeft - this.Left;
                    IsRight = false;
                }

                //Update effect control
                LayerControl.ComputeEffectWidth(_layerCtrl, this);
                //computer critical value
                LayerControl.ComputerCritical(_layerCtrl, this);
                //Update effect data
                LayerControl.ComputeEffectWidth(_layerCtrl);

                var msgCtrl = MessageControl.Current;
                msgCtrl.SetShapeVisible(_layerCtrl);
                msgCtrl.ChangedService.MarkChanged();
                msgCtrl.ShapeControl.Invalidate();

                ControlService.RefreshPropertyGrid(_layerCtrl._layer);

                _layerCtrl.SetMaxWidth(30);
            }
        }

        [DebuggerDisplay("Width={Width},Left={Left},Type={EffectType},Durtion={Effect.Duration}")]
        public abstract class EffectLabel : ControlBase
        {
            protected internal class EffectAdapter : ILayerEffect
            {
                private LayerEffect _layerEffect;
                private EffectLabel _effectLabel;
                private LayerControl _layerControl;

                private int OldLeft;
                private int OldWidth;

                public EffectAdapter(LayerEffect layerEffect, EffectLabel effectLabel, LayerControl layerControl)
                {
                    _layerEffect = layerEffect as LayerEffect;
                    _effectLabel = effectLabel;
                    _layerControl = layerControl;

                    OldLeft = layerEffect.Left;
                    OldWidth = layerEffect.Width;

                    LoadEffect();

                    //_effectLabel.LocationChanged += new EventHandler(_effectLabel_LocationChanged);
                    //_effectLabel.SizeChanged += new EventHandler(_effectLabel_SizeChanged);
                }

                void _effectLabel_SizeChanged(object sender, EventArgs e)
                {
                    OnPropertyChanged("Width", _effectLabel.Width, OldWidth);
                }

                void _effectLabel_LocationChanged(object sender, EventArgs e)
                {
                    OnPropertyChanged("Left", _effectLabel.Left, OldLeft);
                }

                private void LoadEffect()
                {
                    try
                    {
                        BeginEdit();

                        Duration = _layerEffect.Duration;
                        if (_layerEffect.Width == 0)
                            return;

                        switch (_layerEffect.Type)
                        {
                            case Core.EffectType.Entry:
                                if (_layerControl.plLeft.Width == _layerEffect.Left) _layerControl.plRight.Width -= _layerEffect.Width;
                                _layerControl.plLeft.Width = _layerEffect.Left;
                                _effectLabel.Left = _layerEffect.Left + Constance.Effect.SplitterWidth;
                                _effectLabel.Width = _layerEffect.Width - Constance.Effect.SplitterWidth;
                                break;
                            case Core.EffectType.Exit:
                                _effectLabel.Width = _layerEffect.Width - Constance.Effect.SplitterWidth;
                                _layerControl.plRight.Width -= _layerEffect.Width;
                                break;
                            default:
                                _layerControl.plLeft.Width = _layerEffect.Left;
                                _layerControl.plRight.Width = _layerControl.EffectContainer.Width - _layerControl.plLeft.Width
                                    - _layerEffect.Width;
                                _effectLabel.Left = _layerEffect.Left + Constance.Effect.SplitterWidth;
                                _effectLabel.Width = _layerEffect.Width - 2 * Constance.Effect.SplitterWidth;
                                break;
                        }
                    }
                    finally
                    {
                        EndEdit();
                    }
                }

                public string Name
                {
                    get { return _layerEffect.Name; }
                    set
                    {
                        _layerEffect.Name = value;
                    }
                }

                public long StartTime
                {
                    get { return Left / Constance.Effect.UnitWidth; }
                }

                public long EndTime
                {
                    get { return StartTime + Duration; }
                }

                public long Duration
                {
                    get
                    {
                        if (IsEmpty && (Type == EffectType.Entry || Type == EffectType.Exit))
                        {
                            return 0;
                        }
                        else
                        {
                            if (Width == 0)
                                return 0;
                            else
                                return (long) (Width)/Constance.Effect.UnitWidth;
                        }
                    }
                    set
                    {
                        long old = Duration;
                        if (value == 0)
                            _effectLabel.Width = 0;
                        else
                            Width = (int)value * Constance.Effect.UnitWidth;

                        OnPropertyChanged(ShapeLayer._.Duration, value, old);
                    }
                }

                public EffectType Type
                {
                    get
                    {
                        return _layerEffect.Type;
                    } 
                    set
                    {
                        _layerEffect.Type = value;
                    }
                }

                public Guid GUID
                {
                    get
                    {
                        return _layerEffect.GUID;
                    } 
                    set
                    {
                        _layerEffect.GUID = value;
                    }
                }

                public bool IsEmpty
                {
                    get { return string.IsNullOrEmpty(Name) || Name == "None"; }
                }

                public int Left
                {
                    get { return _effectLabel.Left - Constance.Effect.SplitterWidth; }
                    set
                    {
                        if (value != _effectLabel.Left)
                        {
                            OldLeft = _effectLabel.Left;
                            _effectLabel.Left = value + Constance.Effect.SplitterWidth;
                            OnPropertyChanged("Left", value, OldLeft);
                        }
                    }
                }

                public int Width
                {
                    get
                    {
                        switch (this.Type)
                        {
                            case Core.EffectType.Entry:
                            case EffectType.Exit:
                                return _effectLabel.Width + Constance.Effect.SplitterWidth;
                            default:
                                return _effectLabel.Width + 2 * Constance.Effect.SplitterWidth;
                        }
                    }
                    set
                    {
                        int temp;
                        switch (this.Type)
                        {
                            case Core.EffectType.Entry:
                            case EffectType.Exit:
                                temp = value - Constance.Effect.SplitterWidth;
                                break;
                            default:
                                temp = value - 2 * Constance.Effect.SplitterWidth;
                                break;
                        }
                        if (temp != _effectLabel.Width)
                        {
                            OldWidth = _effectLabel.Width;
                            if (this.Type == Core.EffectType.Emphasis)
                                this._layerControl.plRight.Width += (_effectLabel.Width - temp);
                            //_effectLabel.Width = temp;
                            OnPropertyChanged("Width", temp, OldWidth);
                        }
                    }
                }

                #region ILayerEffect Members

                [NonSerialized]
                public EventHandler<PropertyChangedEventArgs> PropertyChanged;

                /// <summary>
                /// Update frame item control
                /// </summary>
                /// <param name="propertyName">property name</param>
                private void OnPropertyChanged(string propertyName, object newValue, object oldValue)
                {
                    //if (IsEdit)
                    //    return;
                    //if (PropertyChanged != null)
                    //    PropertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
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


                public LayerEffect Copy(bool isAddNewEffect)
                {
                    StoreEffect();

                    return _layerEffect.Copy(isAddNewEffect);
                }

                public LayerEffect Copy()
                {
                    StoreEffect();

                    return _layerEffect.Copy();
                }

                public void FromTo(LayerEffect effect)
                {
                    bool isAddNewEffect = _layerEffect.IsEmpty;
                    _layerEffect = effect.Copy(isAddNewEffect);
                    _layerEffect.Left = this.Left;
                    if(isAddNewEffect)
                        LoadEffect();
                }

                private  void StoreEffect()
                {
                    _layerEffect.Width = Width;
                    _layerEffect.Left = Left;
                    _layerEffect.Duration = Duration;
                    
                }
                public LayerEffect Real
                {
                    get
                    {
                        StoreEffect();
                        return _layerEffect;
                    }
                }

                #endregion
            }

            private LayerAdapter _layer;
            protected LayerControl _ctlLayer;

            public EffectLabel(LayerControl ctllayer)
            {
                AllowDrop = true;
                BackColor = Color.FromArgb(163, 213, 153);
                ForeColor = Color.FromArgb(131, 192, 115);
                _ctlLayer = ctllayer;
                _layer = ctllayer._layer;
            }

            public override void SubscribeEvent()
            {
                (_layer as LayerAdapter).PropertyChanged += OnLayerPropertyChanged;
                if (Effect != null)
                    (Effect as EffectLabel.EffectAdapter).PropertyChanged += OnEffectPropertyChanged;
            }

            protected abstract string EffectPropertyName { get; }

            public abstract EffectType EffectType { get; }
           
            public bool IsDragEffect = true;
            internal EffectAdapter Effect
            {
                get
                {
                    return _layer[EffectType];
                }
                set
                {
                    _layer.SetEffect(value.Real, IsDragEffect);
                }
            }

            private void OnLayerPropertyChanged(object sender, PropertyChangedEventArgs e)
            {
                if (e.Name == EffectPropertyName)
                {
                    if (Effect.IsEmpty)
                        _ctlLayer.RemoveEffect(Effect.Type);
                    else
                        _ctlLayer.AppendEffect(Effect.Type);
                    UndoService.AddPropertyChangedAction(sender, new PropertyItem(e.Name, e.NewValue, e.OldValue));
                }
            }

            public override void UnSubscribeEvent()
            {
                _layer.PropertyChanged -= OnLayerPropertyChanged;
                if (Effect != null)
                    Effect.PropertyChanged -= OnEffectPropertyChanged;
            }

            void OnEffectPropertyChanged(object sender, ProWrite.Entity.PropertyChangedEventArgs e)
            {
                UndoService.BeginTransaction("Changed the " + e.Name + " Property");
                UndoService.AddPropertyChangedAction(sender, e.Name, e.NewValue, e.OldValue);
                UndoService.Commit();
            }

            //protected override void SetBoundsCore(int x, int y, int width, int height, BoundsSpecified specified)
            //{
            //    //TODO:Bounds Changed Hook
               
            //    var oldLeft = Location.X;
            //    var oldWidth = Size.Width;

            //    if (oldLeft == x && oldWidth == width)
            //        return;

            //    UndoManager.Current.BeginTransaction("Effect Bounds Changed.");
            //    if (x != Location.X)
            //        UndoManager.Current.AddAction("Effect Left property Changed.", () => UndoLeft(y, oldLeft), () => RedoLeft(x, y));
            //    if (width != Size.Width)
            //        UndoManager.Current.AddAction("Effect Width property Changed.", () => UndoWidth(height, oldWidth), () => RedoWidth(width, height));

            //    base.SetBoundsCore(x, y, width, height, specified);

            //    UndoManager.Current.Commit();
            //}

            private void RedoWidth(int width, int height)
            {
                Size = new Size(width, height);
                Invalidate();
            }

            private void UndoWidth(int height, int oldWidth)
            {
                Size = new Size(oldWidth, height);
                Invalidate();
            }

            private void RedoLeft(int x, int y)
            {
                Location = new Point(x, y);
                Invalidate();
            }

            private void UndoLeft(int y, int oldLeft)
            {
                Location = new Point(oldLeft, y);
                Invalidate();
            }

            protected override void OnResize(EventArgs e)
            {
                base.OnResize(e);
                Invalidate();
            }

            /// <summary>
            /// paint entry or exit 
            /// </summary>
            /// <param name="e"></param>
            /// <param name="enter"></param>
            protected void PaintEntryExitEffect(PaintEventArgs e, bool enter)
            {
                if (base.Width > 0 && Height > 0)
                {
                    Image image = new Bitmap(base.Width, base.Height);
                    Graphics g = Graphics.FromImage(image);
                    g.SmoothingMode = SmoothingMode.HighQuality;
                    SolidBrush blueBrush = new SolidBrush(this.ForeColor);
                    PointF[] point;

                    if (enter)
                        point = new PointF[] { new Point(base.Width, 0), new Point(0, base.Height), new Point(base.Width, base.Height) };
                    else
                        point = new PointF[] { new Point(0, 0), new Point(0, base.Height), new Point(base.Width, base.Height) };

                    g.FillPolygon(blueBrush, point);
                    e.Graphics.SmoothingMode = SmoothingMode.HighQuality;
                    e.Graphics.DrawImage(image, 0, 0, image.Width, image.Height);
                    g.Dispose();
                }
            }
        }

        private class EntryEffectLabel : EffectLabel
        {
            public EntryEffectLabel(LayerControl ctllayer) : base(ctllayer) { }

            public override EffectType EffectType
            {
                get { return EffectType.Entry; }
            }
           
            protected override string EffectPropertyName
            {
                get { return ShapeLayer._.EntryEffect; }
            }

            protected override void OnPaint(PaintEventArgs e)
            {
                base.OnPaint(e);
                PaintEntryExitEffect(e, true);
            }
        }

        private class ExitEffectLabel : EffectLabel
        {
            public ExitEffectLabel(LayerControl ctllayer) : base(ctllayer) { }
            public override EffectType EffectType
            {
                get { return EffectType.Exit; }
            }
            
            protected override string EffectPropertyName
            {
                get { return ShapeLayer._.ExitEffect; }
            }

            protected override void OnPaint(PaintEventArgs e)
            {
                base.OnPaint(e);
                PaintEntryExitEffect(e, false);
            }
        }

        private class EmphasisEffectLabel : EffectLabel
        {
            public EmphasisEffectLabel(LayerControl ctllayer) : base(ctllayer) { }
            public override EffectType EffectType
            {
                get { return EffectType.Emphasis; }
            }

            protected override string EffectPropertyName
            {
                get { return ShapeLayer._.EmphasisEffect; }
            }

            protected override void OnPaint(PaintEventArgs e)
            {
                base.OnPaint(e);
                if(Effect == null)
                    return;
                int width = base.Width;
                int height = base.Height;
                using (Graphics g = e.Graphics)
                {
                    Brush brush = new SolidBrush(Color.FromArgb(163, 213, 153));

                    g.FillRectangle(brush, 0, 0, width, height);
                    if (!Effect.IsEmpty)
                    {
                        //Graphics g = e.Graphics;
                        g.SmoothingMode = SmoothingMode.HighQuality;
                        g.DrawLine(Pens.Black, new Point(0, 0), new Point(width, height));
                        g.DrawLine(Pens.Black, new Point(0, height), new Point(width, 0));
                    }
                }
            }

        }
    }
}
