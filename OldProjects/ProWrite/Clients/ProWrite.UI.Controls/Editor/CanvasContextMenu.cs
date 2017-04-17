//---------------------------------------------------------------------
//
// File: ShapeControlContextMenu.cs
//
// Description:
// 
//
// Author: 
//
// Modify History:
//      Kevin 2008-7-2 remove SplitContainer property,propertyGridCtrl 
//          field, add comments, ÃüÃû¹æ·¶
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
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Editor
{
    public class CanvasContextMenu : ContextMenuStrip
    {
        private ToolStripMenuItem mnuBringToFront;
        private ToolStripMenuItem mnuSendToBack;
        private ToolStripMenuItem mnuCopy;
        private ToolStripMenuItem mnuPaste;
        private ToolStripMenuItem mnuUndo;
        private ToolStripMenuItem mnuRedo;
        private ToolStripMenuItem mnuDelete;
        private ToolStripMenuItem mnuProperties;
        private ToolStripMenuItem mnuNailImage;
        //private ToolStripMenuItem mnuSnap;
        private ToolStripMenuItem mnuOpenShowAllLayers;
        private ToolStripMenuItem mnuCloseShowAllLayers;
        private ToolStripMenuItem mnuFitToSign;
		private ToolStripMenuItem mnuBackground;
        private ToolStripMenuItem mnuCancelBackground;
		private ToolStripMenuItem mnuShowAllLayers;
		private MessageControl _messageControl;

        private EventHandler onBringToFront;
        private EventHandler onSendToBack;
        private EventHandler onCopy;
        private EventHandler onPaste;
        private EventHandler onUndo;
        private EventHandler onRedo;
        private EventHandler onDelete;
        private EventHandler onProperties;
        private EventHandler onNailImage;
        //private EventHandler onSnap;
        private EventHandler onFitToSign;
		private EventHandler onSetBackground;
        private EventHandler onCancelBackground;
		private EventHandler onShowAllLayers;
		private static int intClose = 0;

        public static int IntClose
        {
            get { return intClose; }
            set { intClose = value; }
        }
        public CanvasContextMenu(MessageControl messageControl)
        {
            if (!DesignMode)
            {
                _messageControl = messageControl;
                onBringToFront = delegate { _messageControl.MoveFirst(); };
                onSendToBack = delegate { _messageControl.MoveLast(); };
                onSetBackground = delegate { _messageControl.SetBackground(true); };
                onCancelBackground = delegate { _messageControl.SetBackground(false); };
                onCopy = delegate { if (CopyAction.Current != null) { CopyAction.Current.Copy(); } };
                onPaste = delegate { if (CopyAction.Current != null) { CopyAction.Current.Paste(); } };
                onUndo = delegate { UndoService.Undo(); };
                onRedo = delegate { UndoService.Redo(); };
                onDelete = delegate
                {
                    if (_messageControl.SelectedLayers.Count < 0)
                        return;
                    if (_messageControl.SelectedLayers.Count == 1)
                    {
                        string msg = _messageControl.SelectedLayers[0].Shape.Type.ToString().ToLower();//.Replace("shape", "picture");
                        if (msg == ShapeType.ShapeDraw.ToString().ToLower())
                            msg = "shape";
                        if (MsgBox.Confirm("Are you sure you want to delete this " + msg+"?") != DialogResult.Yes)
                            return;
                    }
                    else
                    {
                        if (MsgBox.Confirm("Are you sure you want to delete these " + _messageControl.SelectedLayers.Count.ToString() + " items?") != DialogResult.Yes)
                            return;
                    }
                     _messageControl.RemoveLayer();
                    
                };
                onProperties = (s, e) =>
                               	{
                               		WindowManager.ShowPanel(Docks.Properties);

                               	};
                onNailImage = delegate {
                    try
                    {
                        IOHelper.RemoveFile(messageControl.Model.ImagePath);
                    }
                    catch { }
                    _messageControl.GenerateNailImageNoWaitCursor();
                    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.Save));
                };//.SetCreateNailImageTime(); };
                //onSnap = delegate
                //{
                //    _messageControl.SnapAllLayers();
                //};

                onFitToSign = delegate
                {
                    _messageControl.ShapeControl.FitToSign();
                };

                mnuBringToFront= AddMenuItem("Bring to Front", Resource.Images.BringToFront, onBringToFront);
                //mnuBackground.ShortcutKeys = Keys.F;
                mnuSendToBack = AddMenuItem("Send to Back", Resource.Images.SendToBack, onSendToBack);
                mnuBackground = AddMenuItem("Set Background", Resource.Images.SetBackground, onSetBackground);
                mnuCancelBackground = AddMenuItem("Cancel Background", Resource.Images.CancelBackground, onCancelBackground);
                AddSeparator();
                mnuCopy = AddMenuItem("Copy", Resource.Images.Copy16, onCopy);
                mnuPaste = AddMenuItem("Paste", Resource.Images.Paste16, onPaste);
                mnuDelete = AddMenuItem("Delete", Resource.Images.Delete16, onDelete);
                //mnuUndo = AddMenuItem("Undo", Resource.Images.Undo16, onUndo);
                //mnuRedo = AddMenuItem("Redo", Resource.Images.Redo16, onRedo);
                AddSeparator();
                mnuProperties = AddMenuItem("Properties", Resource.Images.Properties16, onProperties);
                AddSeparator();
                mnuNailImage = AddMenuItem("Set Thumbnail Image", Resource.Images.GeneraleNailImage, onNailImage);
                AddSeparator();
                //mnuSnap = AddMenuItem("Snap All Layers", Resource.Images.SnapAllLayers, onSnap);
                mnuOpenShowAllLayers = AddMenuItem("Show All Layers", Resource.Images.ShowAllLayers, delegate {
                    _messageControl.IsShowAllLayers = true;
                    _messageControl.UpdateShapeVisible();
                    mnuOpenShowAllLayers.Enabled = false;
                    mnuCloseShowAllLayers.Enabled = true;
                });
                mnuCloseShowAllLayers = AddMenuItem("Close Show All Layers", Resource.Images.CloseShowAllLayers, delegate {
                    _messageControl.IsShowAllLayers = false;
                    _messageControl.UpdateShapeVisible();
                    mnuOpenShowAllLayers.Enabled = true;
                    mnuCloseShowAllLayers.Enabled = false;
                });
                AddSeparator();
                mnuFitToSign = AddMenuItem("Fit to Sign", Resource.Images.FitToSign, onFitToSign);
                //mnuShowAllLayers = AddMenuItem("&Show all layers", Resource.Images.ShowAllLayers, onShowAllLayers);
                //mnuBringToFront.ShowShortcutKeys = false;
                //mnuSendToBack.ShowShortcutKeys = false;
                //mnuCopy.ShowShortcutKeys = false;
                //mnuPaste.ShowShortcutKeys = false;
                //mnuUndo.ShowShortcutKeys = false;
                //mnuRedo.ShowShortcutKeys = false;
                //mnuDelete.ShowShortcutKeys = false;
                //mnuProperties.ShowShortcutKeys = false;
                //mnuNailImage.ShowShortcutKeys = false;
                //mnuSnap.ShowShortcutKeys = false;
                //mnuOpenShowAllLayers.ShowShortcutKeys = false;
                //mnuCloseShowAllLayers.ShowShortcutKeys = false;
                //mnuFitToSign.ShowShortcutKeys = false;
                //mnuBackground.ShowShortcutKeys = false;
                //mnuCancelBackground.ShowShortcutKeys = false;

            }
        }

        protected override void OnOpening(System.ComponentModel.CancelEventArgs e)
        {
            base.OnOpening(e);
            for (int i = 0; i < Items.Count; i++)
            {
                Items[i].Enabled = false;
            }
            Canvas shapeControl = MessageControl.Current.ShapeControl;
            if (shapeControl != null)
            {
                if (CopyAction.Current != null)
                {
                    mnuPaste.Enabled = CopyAction.Current.CanPaste;
                    mnuCopy.Enabled = CopyAction.Current.CanCopy;
                }
                Document shapes = shapeControl.Document;
                if (shapes.Count < 1)
                {
                    return;
                }
                mnuNailImage.Enabled = true;
                //mnuSnap.Enabled = true;
                mnuOpenShowAllLayers.Enabled = !_messageControl.IsShowAllLayers;
                mnuCloseShowAllLayers.Enabled = _messageControl.IsShowAllLayers;
                ShapeBase[] selectedShapes = shapes.SelectedShapes;
                mnuDelete.Enabled = selectedShapes.Length >=1;
                if (selectedShapes == null || selectedShapes.Length < 1)
                {
                }
                else
                {
                    if (selectedShapes.Length == 1)
                    {
                        ShapeBase shape = selectedShapes[0];
                        mnuProperties.Enabled = true;
                        mnuFitToSign.Enabled = !(shape is ShapePaint);
                        if (!shape.IsBackground)
                        {
                            LayerControl frameLayer = MessageControl.Current.GetLayerControl(shape);
                            int index = MessageControl.Current.GetLayerIndex(frameLayer);
                            int maxIndex = MessageControl.Current.GetLayerCount(frameLayer);
                            if (index != 0)
                            {
                                if (index == 1 && shapes.Count > 0 && shapes[0].IsBackground)
                                    mnuSendToBack.Enabled = false;
                                else
                                    mnuSendToBack.Enabled = true;
                            }
                            if (index != maxIndex - 1)
                            {
                                mnuBringToFront.Enabled = true;
                            }

                            if (shape.Type == ShapeType.Image || shape.Type == ShapeType.Video || shape.Type == ShapeType.Text)
                                mnuBackground.Enabled = true;
                        }
                        else
                            mnuCancelBackground.Enabled = true;
                    }
                    else
                    {
                        if (selectedShapes.Length >= 1 && MessageControl.Current.Layers.Length > 1)
                        {
                            ShapeBase shape = selectedShapes[0];
                            LayerControl frameLayer = MessageControl.Current.GetLayerControl(shape);

                            int index = MessageControl.Current.GetLayerIndex(frameLayer);
                            int maxIndex = MessageControl.Current.GetLayerCount(frameLayer);

                            if (index != 0)
                            {
                                if (index == 1 && shapes.Count > 0 && shapes[0].IsBackground)
                                    mnuSendToBack.Enabled = false;
                                else
                                    mnuSendToBack.Enabled = true;
                            }
                            if (index != maxIndex - 1)
                            {
                                mnuBringToFront.Enabled = true;
                            }
                        }
                    }
                }

            }
        }

        protected override void OnClosed(ToolStripDropDownClosedEventArgs e)
        {
            base.OnClosed(e);
            intClose = 1;
        }

        private void AddSeparator()
        {
            Items.Add(new ToolStripSeparator());
        }

        ///// <summary>
        ///// MoveLayerForward
        ///// add by Terry
        ///// </summary>
        //private ToolStripMenuItem SetBackground()
        //{
        //    ToolStripMenuItem item = new ToolStripMenuItem();
        //    item.Text = "Set Background";
        //    item.Image = Resource.GetImage(Resource.Images.Default);
        //    item.Click += delegate
        //    {
        //        //FrameLayer.Shape.IsBackground = true;
        //        _messageControl.MoveForward(FrameLayer);
        //    };
        //    Items.Add(item);
        //    return item;
        //}
        private ToolStripMenuItem AddMenuItem(string name, string imageFile, EventHandler onClick)
        {
            ToolStripMenuItem item = new ToolStripMenuItem(name, Resource.GetImage(imageFile), onClick);
            Items.Add(item);
            return item;
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            onBringToFront = null;
            onSendToBack = null;
            onCopy = null;
            onPaste = null;
            onUndo = null;
            onRedo = null;
            onDelete = null;
            onProperties = null;
            onNailImage = null;
            //onSnap = null;
            onFitToSign = null;
        }
    }
}
