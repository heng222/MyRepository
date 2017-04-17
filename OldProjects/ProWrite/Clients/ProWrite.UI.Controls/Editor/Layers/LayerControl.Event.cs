using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.DES;

namespace ProWrite.UI.Controls.Editor
{
	public partial class LayerControl
	{
        public override void SubscribeEvent()
        {
            base.SubscribeEvent();

            (_layer as LayerAdapter).PropertyChanged += layer_PropertyChanged;
            _layer.Shape.SelectedChanged += Shape_SelectedChanged;
            lblLayerName.DoubleClick += new EventHandler(OnLayerNameDoubleClick);
            _nameEditor.KeyDown += new KeyEventHandler(OnNameEditorKeyDown);
            _nameEditor.MouseLeave += new EventHandler(OnNameEditorLeave);
            SubscribeChildShapeEvent();
            effectHook.SubscribeEvent();

            ctlEntryEffect.SubscribeEvent();
            ctlEmphasis.SubscribeEvent();
            ctlExitEffect.SubscribeEvent();

            RegisterEvent(
                EventMode.Click
                | EventMode.KeyUp
                | EventMode.DragEnter
                | EventMode.DragDrop
                | EventMode.MouseHover
                | EventMode.MouseLeave
                | EventMode.MouseDown
                | EventMode.MouseUp
                , this
                , lblVisible
                , lblLayerType
                , lblLayerName
                , EffectContainer
                , this.plLeft
                , plRight
                , ctlEmphasis
                , ctlEntryEffect
                , ctlExitEffect
                );

            RegisterEvent(
                EventMode.MouseMove
                //, lblVisible
                //, lblLayerType
                , lblLayerName
                );
        }


        public override void UnSubscribeEvent()
        {
            base.UnSubscribeEvent();

            (_layer as LayerAdapter).PropertyChanged -= layer_PropertyChanged;
            if (_layer.Shape != null)
                _layer.Shape.SelectedChanged -= Shape_SelectedChanged;
            UnSubscribeChildShapeEvent();

            if(effectHook != null)
                effectHook.UnSubscribeEvent();
            if(ctlEntryEffect != null)
                ctlEntryEffect.UnSubscribeEvent();
            if(ctlEmphasis != null)
                ctlEmphasis.UnSubscribeEvent();
            if(ctlExitEffect != null)
                ctlExitEffect.UnSubscribeEvent();

            SetCtrlSelectedLayer = null;
            SetEmphasisOnSelectedLayer = null;
            SetEntryOnSelectedLayer = null;
            SetExitOnSelectedLayer = null;
            SetShiftSelectedLayer = null;

            //RegisterEvent(
            //   EventMode.Click
            //   | EventMode.KeyUp
            //   | EventMode.DragEnter
            //   | EventMode.DragDrop
            //   | EventMode.MouseHover
            //   | EventMode.MouseLeave
            //   | EventMode.MouseDown
            //   | EventMode.MouseUp
            //   , this
            //   , lblVisible
            //   , lblLayerType
            //   , lblLayerName
            //   , EffectContainer
            //   , this.plLeft
            //   , plRight
            //   , ctlEmphasis
            //   , ctlEntryEffect
            //   , ctlExitEffect
            //   );

            //RegisterEvent(
            //    EventMode.MouseMove
            //    //, lblVisible
            //    //, lblLayerType
            //    , lblLayerName
            //    );
        }

        private void RegisterEvent(EventMode events, params Control[] ctrs)
        {
            foreach (Control ctr in ctrs)
            {
                if ((events & EventMode.Click) == EventMode.Click)
                    ctr.Click += OnLayerClick;
                if ((events & EventMode.DragEnter) == EventMode.DragEnter)
                    ctr.DragEnter += OnLayerDragEnter;
                if ((events & EventMode.DragDrop) == EventMode.DragDrop)
                    ctr.DragDrop += OnLayerDragDrop;
                if ((events & EventMode.MouseMove) == EventMode.MouseMove)
                    ctr.MouseMove += OnLayerMouseMove;
                if ((events & EventMode.MouseDown) == EventMode.MouseDown)
                    ctr.MouseDown += OnLayerMouseDown;
                if ((events & EventMode.MouseUp) == EventMode.MouseUp)
                    ctr.MouseUp += OnLayerMouseUp;
                if ((events & EventMode.MouseHover) == EventMode.MouseHover)
                    ctr.MouseHover += OnLayerMouseHover;
                if ((events & EventMode.MouseLeave) == EventMode.MouseLeave)
                    ctr.MouseLeave += OnLayerMouseLeave;

                if ((events & EventMode.KeyUp) == EventMode.KeyUp)
                    ctr.KeyUp += OnLayerKeyUp;
            }
        }

        private void UnRegisterEvent(EventMode events, params Control[] ctrs)
        {
            foreach (Control ctr in ctrs)
            {
                if ((events & EventMode.Click) == EventMode.Click)
                    ctr.Click -= OnLayerClick;
                if ((events & EventMode.DragEnter) == EventMode.DragEnter)
                    ctr.DragEnter -= OnLayerDragEnter;
                if ((events & EventMode.DragDrop) == EventMode.DragDrop)
                    ctr.DragDrop -= OnLayerDragDrop;
                if ((events & EventMode.MouseMove) == EventMode.MouseMove)
                    ctr.MouseMove -= OnLayerMouseMove;
                if ((events & EventMode.MouseDown) == EventMode.MouseDown)
                    ctr.MouseDown -= OnLayerMouseDown;
                if ((events & EventMode.MouseUp) == EventMode.MouseUp)
                    ctr.MouseUp -= OnLayerMouseUp;
                if ((events & EventMode.MouseHover) == EventMode.MouseHover)
                    ctr.MouseHover -= OnLayerMouseHover;
                if ((events & EventMode.MouseLeave) == EventMode.MouseLeave)
                    ctr.MouseLeave -= OnLayerMouseLeave;

                if ((events & EventMode.KeyUp) == EventMode.KeyUp)
                    ctr.KeyUp -= OnLayerKeyUp;
            }
        }

        [Flags]
        private enum EventMode : ushort
        {
            Click = 1,

            MouseHover = Click * 2,
            MouseLeave = MouseHover * 2,
            MouseMove = MouseLeave * 2,
            MouseDown = MouseMove * 2,
            MouseUp = MouseDown * 2,

            DragEnter = MouseUp * 2,
            DragDrop = DragEnter * 2,

            KeyUp = MouseUp * 2,
        }

        private void OnLayerClick(object sender, EventArgs e)
        {
            ControlService.RefreshPropertyGrid(_layer);


            if (sender == lblVisible)
            {
                this.Shape.BeginEdit();
                Layer.IsVisible = !Layer.IsVisible;
                this.Shape.EndEdit();
            }

            Focus();
        }

        private void OnLayerMouseMove(object sender, MouseEventArgs e)
        {
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                this.DoDragDrop(this, DragDropEffects.Copy | DragDropEffects.All | DragDropEffects.Move);
            }
        }

        private void OnLayerMouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (ModifierKeys == Keys.Control)
                {
                    IsSelected = !IsSelected;
                    Shape.BeginEdit();
                    Shape.IsSelected = IsSelected;
                    Shape.EndEdit();

                    MessageControl.Current.ShapeControl.Invalidate();
                }
                else if (ModifierKeys != Keys.Shift)
                {
                    if (SetCtrlSelectedLayer != null)
                        SetCtrlSelectedLayer(this, null);
                    IsSelected = true;
                    Current = this;
                }
                else if (ModifierKeys == Keys.Shift && Current != null)
                {
                    CurrentShif = this;
                    if (SetShiftSelectedLayer != null)
                        SetShiftSelectedLayer(this, null);
                }
                else
                {
                    Current = this;
                }
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (this.Shape.IsSelected)
                    return;
                else
                {
                    if (SetCtrlSelectedLayer != null)
                        SetCtrlSelectedLayer(this, null);
                    IsSelected = true;
                    Current = this;
                }
            }
        }

        private void OnLayerMouseUp(object sender, MouseEventArgs e)
        {
            if (_layerMouseUp != null)
                _layerMouseUp(this, sender as Control, e);
            ControlService.RefreshPropertyGrid(_layer);
        }

        private void OnLayerMouseLeave(object sender, EventArgs e)
        {
            lblLayerName.BackColor = lblLayerName.BackColor == ControlService.MouseDownColor ? ControlService.MouseDownColor : ControlService.MouseLeaveColor;
            Cursor = Cursors.Default;
            //if (_layerMouseLeave != null)
            //    _layerMouseLeave(this, sender as Control, e);
            //ControlService.RefreshPropertyGrid(_layer);
        }

        private void OnLayerKeyUp(object sender, KeyEventArgs e)
        {
            EffectLabel effectCtr = sender as EffectLabel;
            if (effectCtr != null)
            {
                if (e.KeyCode == Keys.Delete || e.KeyCode == Keys.Back)
                {
                    RemoveEffect(effectCtr.Effect.Type);
                }
            }
        }

        private void OnLayerMouseHover(object sender, EventArgs e)
        {
            lblLayerName.BackColor = lblLayerName.BackColor == ControlService.MouseDownColor ? ControlService.MouseDownColor : ControlService.MouseOverColor;
        }

        private void OnLayerDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data != null)
                e.Effect = DragDropEffects.Copy;
            else
                e.Effect = DragDropEffects.Move;
        }

        private void OnLayerDragDrop(object sender, DragEventArgs e)
        {
            if (e.Effect != DragDropEffects.Copy)
                return;

            var fmts = e.Data.GetFormats();
            if (fmts == null || fmts.Length != 1)
                return;

            LayerEffect effect = e.Data.GetData(fmts[0]) as LayerEffect;
            CurrentDragLayer = true;
            CurrentDrag = this;
            if (effect != null)
            {
                //effect.Layer = this._layer.Shape
                switch(effect.Type)
                {
                    case EffectType.Entry:
                        effect.Duration = this.ctlEntryEffect.Width == 0 ? 2 : ctlEntryEffect.Effect.Duration;
                        break;
                    case EffectType.Exit:
                        effect.Duration = this.ctlExitEffect.Width == 0 ? 2 : ctlExitEffect.Effect.Duration;
                        break;
                    default:
                        effect.Duration = this.ctlEmphasis.Width == 0 ? 8 : ctlEmphasis.Effect.Duration;
                        break;
                }
                //if (effect.Duration == 0)
                //    effect.Duration = 2;//ControlService.SignCombo.Current.Template.Message. 2;
                ////else
                ////    effect.Duration++;
                UndoService.BeginTransaction(String.Format("Add a {0} effect", effect.Type));
                UndoService.AddLayerEffectAddedAction(effect);

                AddEffectFromDragDrop(effect);

                UndoService.Commit();
                ControlService.RefreshPropertyGrid(_layer);
                CurrentDragLayer = false;
                return;
            }

            LayerControl frameLayer = e.Data.GetData(typeof(LayerControl)) as LayerControl;
            if (frameLayer != null)
                OnDragLayer(frameLayer);

            EffectContainer.Invalidate();
        }
        //private static readonly LayerControl Instance = new LayerControl(null,false);
        //public static void RefreshEffect()
        //{
        //    Instance.EffectContainer.Invalidate();
        //}

        void OnLayerNameDoubleClick(object sender, EventArgs e)
        {
            lblLayerName.Visible = false;
            this._nameEditor.Text = lblLayerName.Text;
            this._nameEditor.Focus();
            _nameEditor.Visible = true;
        }


        void OnNameEditorKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (_nameEditor.Text.Trim() == "")
                {
                    _nameEditor.Text = "*";
                    e.Handled = false;
                    return;
                }
                lblLayerName.Text = this._nameEditor.Text;
                _nameEditor.Visible = false;
                lblLayerName.Visible = true;
                _layer.Name = lblLayerName.Text;
                e.Handled = true;
            }
            if (e.KeyCode == Keys.Escape)
            {
                lblLayerName.Visible = true;
                _nameEditor.Visible = false;
                e.Handled = true;
            }
        }

        void OnNameEditorLeave(object sender, EventArgs e)
        {
            if (_nameEditor.Text.Trim() == "")
            {
                _nameEditor.Text = "*";
                return;
            }
            if (_nameEditor.Text == "*")
            {
                lblLayerName.Visible = true;
                _nameEditor.Visible = false;
                return;
            }
            lblLayerName.Visible = true;
            _nameEditor.Visible = false;
            lblLayerName.Text = _nameEditor.Text;
            _layer.Name = lblLayerName.Text;
        }

	}
}
