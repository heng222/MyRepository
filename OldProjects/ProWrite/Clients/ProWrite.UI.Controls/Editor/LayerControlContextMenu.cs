//---------------------------------------------------------------------
//
// File: LayerControlContextMenu.cs
//
// Description:
// 
//
// Author: Terry 2008-8-27
//
// Modify History:
//      Jerry Xu 2009-5-20 Update method:OnOpening(CancelEventArgs e)
//      Jerry Xu 2009-5-26 Update method: OnOpening(CancelEventArgs e)
// 
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Resources;
using ProWrite.Core;
using System.Drawing;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.CopyPaste;
using System.ComponentModel;
using ProWrite.UI.Controls.Editor.Layers;
using ProWrite.Entity.DES;

namespace ProWrite.UI.Controls.Editor
{
    public class LayerControlContextMenu : ContextMenuStrip
    {
        private ToolStripMenuItem mnuChangeName;
        private ToolStripMenuItem mnuBringToFront;
        private ToolStripMenuItem mnuSendToBack;
        private ToolStripMenuItem mnuDelEmphasisEffect;
        private ToolStripMenuItem mnuDelEntryEffect;
        private ToolStripMenuItem mnuDelExitEffect;
        private ToolStripMenuItem mnuSetEmphasisEffect;
        private ToolStripMenuItem mnuSetEntryEffect;
        private ToolStripMenuItem mnuSetExitEffect;
        private ToolStripMenuItem mnuDeleteLayer;
        private ToolStripMenuItem mnuProperties;
        private ToolStripMenuItem mnuMoveLayerForward;
        private ToolStripMenuItem mnuMoveLayerBackwards;
        private ToolStripMenuItem mnuSnap;
        private ToolStripMenuItem mnuOpenShowAllLayers;
        private ToolStripMenuItem mnuCloseShowAllLayers;

        private MessageControl _messageControl;

        internal Control Target;
        internal LayerControl FrameLayer;

        public LayerControlContextMenu(MessageControl messageControl)
        {
           
            _messageControl = messageControl;
            if (!DesignMode)
            {
                mnuChangeName = ChangeName();

                mnuMoveLayerForward = MoveLayerForward();
                mnuMoveLayerBackwards = MoveLayerBackwards();
                mnuBringToFront = BringLayertoFront();
                mnuSendToBack = SendtoBack();
                AddSeparator();
                mnuDeleteLayer = AddMenuItem("Delete Layer", Resource.Images.Delete16, delegate 
                {
                    //Resource.GetString(Resource.Strings.ConfirmDeleteLayer))
                    if (MsgBox.Confirm(_messageControl.GetDeleteTipMessage()) == DialogResult.Yes)
                        _messageControl.RemoveLayer(); 
                    //_messageControl.RemoveLayer(FrameLayer);
 
                });
                mnuDelEntryEffect = DeleteEntryEffect();
                mnuDelEmphasisEffect = DeleteEmphasisEffect();
                mnuDelExitEffect = DeleteExitEffect();
                AddSeparator();
                mnuSetEntryEffect = SetEntryEffect();
                mnuSetEmphasisEffect = SetEmphasisEffect();
                mnuSetExitEffect = SetExitEffect();
                AddSeparator();
                mnuProperties = AddMenuItem("Properties", Resource.Images.Properties16, (s,e)=> WindowManager.ShowPanel(Docks.Properties));
                AddSeparator();
                mnuSnap = AddMenuItem("Automatic Snap Layers", Resource.Images.SnapAllLayers, delegate { _messageControl.AutomaticSnapLayers(); });
                mnuOpenShowAllLayers = AddMenuItem("Show All Layers", Resource.Images.ShowAllLayers, delegate
                {
                    _messageControl.IsShowAllLayers = true;
                    _messageControl.UpdateShapeVisible();
                    mnuOpenShowAllLayers.Enabled = false;
                    mnuCloseShowAllLayers.Enabled = true;
                });
                mnuCloseShowAllLayers = AddMenuItem("Close Show All Layers", Resource.Images.CloseShowAllLayers, delegate
                {
                    _messageControl.IsShowAllLayers = false;
                    _messageControl.UpdateShapeVisible();
                    mnuOpenShowAllLayers.Enabled = true;
                    mnuCloseShowAllLayers.Enabled = false;
                });
            }
        }

        protected override void OnOpening(CancelEventArgs e)
        {
            this.Left = this.Left + Target.Left;
            
            for (int i = 0; i < Items.Count; i++)
            {
                Items[i].Enabled = false;
            }
            int layersSelected = _messageControl.SelectedLayers.Count;
            Canvas shapeControl = _messageControl.ShapeControl;
            if (FrameLayer != null && Target != null)
            {

                ShapeBase shape = FrameLayer.Shape;
                mnuChangeName.Enabled = layersSelected==1;
                mnuDeleteLayer.Enabled = layersSelected >= 0;
                mnuSnap.Enabled = layersSelected > 0;
                if (FrameLayer.EmphasisEffect.Type != EffectType.None && FrameLayer.EmphasisEffect.Name.ToLower()!="none" && FrameLayer.EmphasisEffect.Duration > 0)
                {
                    mnuDelEmphasisEffect.Enabled = layersSelected == 1;
                    mnuSetEmphasisEffect.Enabled = layersSelected == 1;
                }
                if (!FrameLayer.EntryEffect.IsEmpty && FrameLayer.EntryEffect.Duration > 0)
                {
                    mnuDelEntryEffect.Enabled = layersSelected == 1;
                    mnuSetEntryEffect.Enabled = layersSelected == 1;
                }
                if (!FrameLayer.ExitEffect.IsEmpty && FrameLayer.ExitEffect.Duration > 0)
                {
                    mnuDelExitEffect.Enabled = layersSelected == 1;
                    mnuSetExitEffect.Enabled = layersSelected == 1;
                }
                mnuProperties.Enabled = layersSelected == 1;
                mnuOpenShowAllLayers.Enabled = !_messageControl.IsShowAllLayers;
                mnuCloseShowAllLayers.Enabled = _messageControl.IsShowAllLayers;

                if (!shape.IsBackground)
                {
                    bool isbackgourd = _messageControl.ShapeControl.Document.Exists(
                    delegate(ShapeBase s) { return s.IsBackground == true; });
                    
                    int index = _messageControl.GetLayerIndex(FrameLayer);

                    int maxIndex = _messageControl.GetLayerCount(FrameLayer);
                    if (index != 0 && isbackgourd && index != 1)
                    {
                        mnuSendToBack.Enabled = layersSelected == 1;
                        mnuMoveLayerBackwards.Enabled = layersSelected == 1;
                    }
                    else if (index != 0 && !isbackgourd)
                    {
                        mnuSendToBack.Enabled = layersSelected == 1;
                        mnuMoveLayerBackwards.Enabled = layersSelected == 1;
                    }
                    
                    if (index != maxIndex - 1)
                    {
                        mnuBringToFront.Enabled = layersSelected == 1;
                        mnuMoveLayerForward.Enabled = layersSelected == 1;
                    }
                }
            }
            //this.Left  = 
        }

        private void AddSeparator()
        {
            Items.Add(new ToolStripSeparator());
        }


        private ToolStripMenuItem ChangeName()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Rename";
            item.Image = Resource.GetImage(Resource.Images.Rename);
            item.Click += delegate
            {
                FrameLayer.ChangeName();
            };
            Items.Add(item);
            return item;
        }

        private ToolStripMenuItem AddMenuItem(string name, string imageFile, EventHandler onClick)
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = name;
            item.Image = Resource.GetImage(imageFile);
            item.Click += onClick;
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Bring to Front
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem BringLayertoFront()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Bring to Front";
            item.Image = Resource.GetImage(Resource.Images.BringToFront);
            item.Click += delegate
            {
                MessageControl.Current.MoveFirst(FrameLayer);//.MoveForward(FrameLayer, true);
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Send to Back
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem SendtoBack()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Send to Back";
            item.Image = Resource.GetImage(Resource.Images.SendToBack);
            item.Click += delegate
            {
                MessageControl.Current.MoveLast(FrameLayer) ;
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// MoveLayerForward
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem MoveLayerForward()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Move Layer Forward";
            item.Image = Resource.GetImage(Resource.Images.MoveLayerForward);
            item.Click += delegate
            {
                _messageControl.MoveForward(FrameLayer);
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// MoveLayerBackwards
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem MoveLayerBackwards()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Move Layer Backwards";
            item.Image = Resource.GetImage(Resource.Images.MoveLayerBackwards);
            item.Click += delegate
            {
                _messageControl.MoveBack(FrameLayer);
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Delete Entry Effect
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem DeleteEntryEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Delete Entry Effect";
            item.Image = Resource.GetImage(Resource.Images.DeleteEntryEffect);
            item.Click += delegate
            {
                UndoService.BeginTransaction("Delete a entry effect");
                var effect = FrameLayer.EntryEffect.Real.Copy();

                //FrameLayer.EntryEffect.Name = null;
                FrameLayer.RemoveEffect(effect.Type);
                
                UndoService.AddLayerEffectRemovedAction(FrameLayer, effect);
				FrameLayer.Invalidate();
                UndoService.Commit();
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Delete Emphasis Effect
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem DeleteEmphasisEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Delete Emphasis Effect";
            item.Image = Resource.GetImage(Resource.Images.DeleteEmphasisEffect);
            item.Click += delegate
            {
                UndoService.BeginTransaction("Delete a emphasis effect");
                var effect = FrameLayer.EmphasisEffect.Real.Copy();

                //FrameLayer.EmphasisEffect.Name = null;
                //FrameLayer.EmphasisEffect.Type = EffectType.None;
                FrameLayer.RemoveEffect(effect.Type);

                UndoService.AddLayerEffectRemovedAction(FrameLayer, effect);
				FrameLayer.Invalidate();

                UndoService.Commit();
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Delete Exit Effect
        /// add by Terry
        /// </summary>
        private ToolStripMenuItem DeleteExitEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Delete Exit Effect";
            item.Image = Resource.GetImage(Resource.Images.DeleteExitEffect);
            item.Click += delegate
            {
                UndoService.BeginTransaction("Delete a exit effect");
                LayerEffect effect = FrameLayer.ExitEffect.Real.Copy();

            	//FrameLayer.ExitEffect.Name = null;
                FrameLayer.RemoveEffect(effect.Type);
                UndoService.AddLayerEffectRemovedAction(FrameLayer, effect);

				FrameLayer.Invalidate();
                UndoService.Commit();
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Set Entry Effect
        /// add by Michael 2008-11-14
        /// </summary>
        private ToolStripMenuItem SetEntryEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Set Entry Effect";
            item.Image = Resource.GetImage(Resource.Images.SetentryEffect);
            item.Click += delegate
            {
                
                EffectSetForm frm = new EffectSetForm(FrameLayer.EntryEffect.Real);
                frm.ShowModalDialog();
                FrameLayer.EntryEffect.FromTo(frm.Effect);
            };
            Items.Add(item);

            return item;
        }

        /// <summary>
        /// Delete Emphasis Effect
        /// add by Michael 2008-11-14
        /// </summary>
        private ToolStripMenuItem SetEmphasisEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Set Emphasis Effect";
            item.Image = Resource.GetImage(Resource.Images.SetEmphasisEffect);
            item.Click += delegate
            {
                EffectSetForm frm = new EffectSetForm(FrameLayer.EmphasisEffect.Real);
                frm.ShowModalDialog();
                FrameLayer.EmphasisEffect.FromTo(frm.Effect);
            };
            Items.Add(item);
            return item;
        }

        /// <summary>
        /// Delete Exit Effect
        /// add by Michael 2008-11-14
        /// </summary>
        private ToolStripMenuItem SetExitEffect()
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Text = "Set Exit Effect";
            item.Image = Resource.GetImage(Resource.Images.SetExitEffect);
            item.Click += delegate
            {
                EffectSetForm frm = new EffectSetForm(FrameLayer.ExitEffect.Real);
                frm.ShowModalDialog();
                FrameLayer.ExitEffect.FromTo(frm.Effect);
            };
            Items.Add(item);
            return item;
        }
    }
}
