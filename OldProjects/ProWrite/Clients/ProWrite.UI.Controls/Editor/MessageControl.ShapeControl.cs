//---------------------------------------------------------------------
//
// File: MessageControl.ShapeControlcs
//
// Description:
// Shape control class
//
// Author: 
//
// Modify History:
//      Jerry Xu 2008-12-30 Add functions: SetNewShapeImage(ShapeBase shape),SetNewShapeImage(ShapeImage shapeImage, string file),RenameShapeImage(ShapeImage shapeImg, string file)
//                                         SetNewShapeVideo(ShapeVideo shapeVideo),SetNewShapeVideo(ShapeVideo shapeVideo, string file),RenameShapeVideo(ShapeVideo shapeVideo, string file)
//                          Update event : OnShapeControlDoubleClick
//      Jerry Xu 2009-1-4   Add method:    IsLockFile(string file, LibraryType type)
//      Jerry Xu 2009-1-4   Update method: RenameShapeImage(ShapeImage shapeImg, string file),RenameShapeVideo(ShapeVideo shapeVideo, string file)
//      Jerry Xu 2009-1-20  Update method: SetNewShapeImage(ShapeBase shape),SetNewShapeVideo(ShapeVideo shapeVideo, bool propertyChanged)
//      Jerry Xu 2009-2-16  Add method   : ShapeNewFile()
//      Jerry Xu 2009-2-16  Update event : OnShapeControlDragDrop(object sender, DragEventArgs e)
//      Jerry Xu 2009-3-3   Update event : void OnShapeControlDragDrop(object sender, DragEventArgs e)
//      Jerry Xu 2009-6-3   Update method: RenameShapeImage(ShapeImage shapeImg, string file)
//      Jerry Xu 2009-7-6   Update event:  OnShapeControlDragDrop(object sender, DragEventArgs e) about merge message
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraNavBar;
using ProWrite.Entity.Shape;
using System.Drawing;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using System.IO;
using ProWrite.UI.Texts;
using ProWrite.UI.Controls.Settings;
using ProWrite.UI.Controls.Common;
using ProWrite.DES;
using ProWrite.Entity.DES;
using DesEffect = ProWrite.Entity.DES.Effect;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Library;
using ProWrite.Core;


namespace ProWrite.UI.Controls.Editor
{
    public partial class MessageControl
    {
        private static readonly Type NodeType = typeof(LibraryNode);
        private static readonly Type NavBarItemType = typeof(NavBarItemLink);

        #region Events
        void OnShapeControlDragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(NodeType)
                || e.Data.GetDataPresent(NavBarItemType))
                e.Effect = DragDropEffects.Copy;

        }

        void OnShapeControlDragDrop(object sender, DragEventArgs e)
        {
            shapeControl.ReverseReverseBorder();
            shapeControl.Focus();

            if (e.Effect != DragDropEffects.Copy)
                return;

            UndoService.BeginTransaction("Drag drop");

            if (e.Data.GetDataPresent(NodeType))
            {
                LibraryNode node = e.Data.GetData(NodeType) as LibraryNode;
                if (node.Library != null)
                {
                    LibraryItem item = node.Library;
                    switch (item.Type)
                    {
                        case LibraryType.Image:
                            AddImageLayer((item as FileLibraryItem).Path);
                            break;
                        case LibraryType.Video:
                            AddVideoLayer((item as FileLibraryItem).Path);
                            break;
                        case LibraryType.Message:
                            ControlService.CancelPoistions();
                            MergeMessage(item as MessageInfo);
                            ControlService.RestorePoistions();
                            break;
                    }
                    ILockLibraryItem locker = item as ILockLibraryItem;
                    if (locker != null && locker.Type != LibraryType.Message)
                        locker.IsLock = true;
                }
               
            }
            else if (e.Data.GetDataPresent(NavBarItemType))
            {
                ToolBoxNarBarItem link = (e.Data.GetData(NavBarItemType) as NavBarItemLink).Item as ToolBoxNarBarItem;
                if (link != null)
                    AddLayerDragDrop(link.ShapeType, ShapeAddMode.ToolBox);
                ShapeNewFile();
            }
           
            shapeControl.Invalidate();
            UndoService.Commit();
        }

        void OnShapeControlKeyUp(object sender, KeyEventArgs e)
        {
            Point offset = Point.Empty;
            Document _Shapes = shapeControl.Document;
            int _GridScale = _Shapes.Zoom;
            if (e.KeyData == Keys.Delete)
            {
                if (MessageControl.Current != null
                && MessageControl.Current.SelectedLayers.Count > 0)
                {
                    if (MessageControl.Current.SelectedLayers.Count == 1)
                    {
                        string msg = MessageControl.Current.SelectedLayers[0].Shape.Type.ToString().ToLower();//.Replace("shape", "picture");
                        if (msg == ShapeType.ShapeDraw.ToString().ToLower())
                            msg = "shape";
                        if (MsgBox.Confirm("Are you sure you want to delete this " + msg + "?") != DialogResult.Yes)
                            return;
                    }
                    else
                    {
                        if (MsgBox.Confirm("Are you sure you want to delete these " + MessageControl.Current.SelectedLayers.Count.ToString() + " items?") != DialogResult.Yes)
                            return;
                    }
                    RemoveLayer();
                }
            }
            switch (e.KeyData)
            //switch (e.KeyCode)
            {
                case Keys.Left | Keys.Control:
                    //offset = new Point(-1, 0);
                    //_Shapes.Move(offset);
                    _Shapes.Grow(_GridScale / _Zoom, Keys.Left, shapeControl.DisplayRectangle.Size);

                    break;
                case Keys.Up | Keys.Control:
                    //offset = new Point(0, -1);
                    //_Shapes.Move(offset);

                    _Shapes.Grow(_GridScale / _Zoom, Keys.Up, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Right | Keys.Control:

                    //offset = new Point(1, 0);
                    //_Shapes.Move(offset, shapeControl.DisplayRectangle.Size);

                    _Shapes.Grow(_GridScale / _Zoom, Keys.Right, shapeControl.DisplayRectangle.Size);

                    break;
                case Keys.Down | Keys.Control:
                    //offset = new Point(0, 1);
                    //_Shapes.Move(offset, shapeControl.DisplayRectangle.Size);

                    _Shapes.Grow(_GridScale / _Zoom, Keys.Down, shapeControl.DisplayRectangle.Size);

                    break;
                case Keys.Left:
                    offset = new Point(-1 * _GridScale, 0);
                    _Shapes.Move(offset, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Up:
                    offset = new Point(0, -1 * _GridScale);
                    _Shapes.Move(offset, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Right:
                    offset = new Point(_GridScale, 0);
                    _Shapes.Move(offset, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Down:
                    offset = new Point(0, _GridScale);
                    _Shapes.Move(offset, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Left | Keys.Shift | Keys.Control:
                    _Shapes.Grow(1 / _Zoom, Keys.Left);
                    break;
                case Keys.Up | Keys.Shift | Keys.Control:
                    _Shapes.Grow(1 / _Zoom, Keys.Up);
                    break;
                case Keys.Right | Keys.Shift | Keys.Control:
                    _Shapes.Grow(1 / _Zoom, Keys.Right, shapeControl.DisplayRectangle.Size);
                    break;
                case Keys.Down | Keys.Shift | Keys.Control:
                    _Shapes.Grow(1 / _Zoom, Keys.Down, shapeControl.DisplayRectangle.Size);
                    break;
                //case Keys.Left | Keys.Shift:
                //    _Shapes.Grow(_GridScale / _Zoom, Keys.Left, shapeControl.DisplayRectangle.Size);
                //    break;
                //case Keys.Up | Keys.Shift:
                //    _Shapes.Grow(_GridScale / _Zoom, Keys.Up, shapeControl.DisplayRectangle.Size);
                //    break;
                //case Keys.Right | Keys.Shift:
                //    _Shapes.Grow(_GridScale / _Zoom, Keys.Right, shapeControl.DisplayRectangle.Size);
                //    break;
                //case Keys.Down | Keys.Shift:
                //    _Shapes.Grow(_GridScale / _Zoom, Keys.Down, shapeControl.DisplayRectangle.Size);
                //    break;
            }

            if (_Shapes.SelectedCount > 0)
            {
                shapeControl.Invalidate(true);
            }
        }

        void shape_AddLayers(object sender, AddLayersEventArgs e)
        {
            if (MsgBox.Confirm(Resource.GetString(Resource.Strings.EditerShapeLabelIsAddNewLayer)) != DialogResult.Yes)
                return;
            //throw new Exception("The method or operation is not implemented.");
            ShapeLabel shape = e.Shape;
            UndoService.BeginTransaction("Add layers");
            LayerControl frameLayer = GetLayerControl(shape);
            var layer = frameLayer.Layer;

            List<ShapeLayer> layers = new List<ShapeLayer>();

            List<ShapeLabel> items = e.Items;

            ShapeLayer item;
            for (int i = 0; i < items.Count; i++)
            {
                item = new ShapeLayer(items[i]);
                if (i == 0)
                {
                    item.PartialFromTo(layer.Copy() as ShapeLayer);
                }
                else
                {
                    item.PartialFromTo(layers[i - 1]);
                }
                layers.Add(item);
                AddLayer(NewLayerControl(item, true), ShapeAddMode.Clone);
            }
            UndoService.Commit();
        }

        void layer_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            try
            {
                if (_changedService != null)
                    _changedService.MarkChanged();
                if (e.Name == "Name")
                {
                    ShapeLayer layer = sender as ShapeLayer;
                    if (layer == null)
                        return;

                    Control container = layer.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
                    if (container.Controls.Count > 0)
                    {
                        foreach (LayerControl layerControl in container.Controls)
                        {

                            if (layerControl.Layer != layer)
                            {
                                if (e.NewValue.ToString() == layerControl.Layer.Name)// container.Controls[i].Controls[0].Controls[0].Text.ToString())
                                {
                                    layer.Name = e.OldValue.ToString();
                                    MsgBox.Warning("Sorry,Layer name can't repeat");
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            catch
            { }
        }

        public void shape_SelectedChanged(object sender, EventArgs e)
        {
            ShapeBase shape = sender as ShapeBase;
            if (shape != null)
            {
                if (shape.IsMoving) return;

                var isSelected = shape.IsSelected;
                LayerControl frameLayer = GetLayerControl(shape);
                if (frameLayer != null) frameLayer.IsSelected = isSelected;

                bool isDynamicText = shape.Type == ShapeType.DynamicText || shape.Type == ShapeType.Time || shape.Type == ShapeType.Temperature;
                if (shape.Type == ShapeType.Image)
                    LocalMessageBus.Send(this, new IsSelectShapImage(true));
                else
                    LocalMessageBus.Send(this, new IsSelectShapImage(false));
                switch (shape.Type)
                {
                    case ShapeType.Text:
                        var center = new MenuCommand(MenuCommands.TextAlignCenter, isSelected);
                        var left = new MenuCommand(MenuCommands.TextAlignLeft, isSelected);
                        var right = new MenuCommand(MenuCommands.TextAlignRight, isSelected);
                        var textBackGroundColor = new MenuCommand(MenuCommands.TextBackgroundColor, isSelected);
                        var textForeColor = new MenuCommand(MenuCommands.TextFontColor, isSelected);
                        var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                        var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
                        var textLead = new MenuCommand(MenuCommands.TextLead, isSelected);
                        var textKern = new MenuCommand(MenuCommands.TextKern, isSelected);
                        var textFont = new MenuCommand(MenuCommands.TextFont, isSelected);
                        var textEffect = new MenuCommand(MenuCommands.TextEffect, isSelected);
                        var textFrameFixed = new MenuCommand(MenuCommands.TextFrameFixed, isSelected);

                        //var textFontFixed = new MenuCommand(MenuCommands.TextFontSizeFixed, isSelected);
                        MenuCommand textSize = null;// = new MenuCommand(MenuCommands.TextFontSize, !((ShapeLabel) shape).FrameSizeFixed);
                        textSize = new MenuCommand(MenuCommands.TextFontSize, !((ShapeLabel)shape).FrameSizeFixed && isSelected);

                        ShapeLabel label = shape as ShapeLabel;
                        label.IsBitMapFontOnly = ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly;
                        bool isPWFont = label.Font.Name == FontManager.GetProWriteFonts()[0];

                        if (isSelected)
                        {
                            center.PropertyName = "Down";
                            center.PropertyValue = label.TextAlignment == Align.CENTER;

                            left.PropertyName = "Down";
                            left.PropertyValue = label.TextAlignment == Align.LEFT;

                            right.PropertyName = "Down";
                            right.PropertyValue = label.TextAlignment == Align.RIGHT;

                            textBold.PropertyName = "Down";
                            textBold.PropertyValue = (label.Font.Style & FontStyle.Bold) == FontStyle.Bold;

                            textItalic.PropertyName = "Down";
                            textItalic.PropertyValue = (label.Font.Style & FontStyle.Italic) == FontStyle.Italic;

                            textLead.PropertyName = "EditValue";
                            textLead.PropertyValue = label.LeadAmount;

                            textKern.PropertyName = "EditValue";
                            textKern.PropertyValue = label.KernAmount;

                            textSize.PropertyName = "EditValue";
                            textSize.PropertyValue = label.Font.Size;

                            textFont.PropertyName = "EditValue";
                            textFont.PropertyValue = label.Font.Name;

                            textEffect.PropertyName = "EditValue";
                            textEffect.PropertyValue = label.TextEffect;

                            textBackGroundColor.PropertyName = "SelectedColor";
                            //textBackGroundColor.PropertyValue = this.BackColor; //label.BackColor;
                            textBackGroundColor.PropertyValue = label.SourceBackColor; //label.BackColor;

                            textForeColor.PropertyName = "SelectedColor";
                            textForeColor.PropertyValue = label.SourceForeColor; //label.ForeColor;
                            //textForeColor.PropertyValue = this.ForeColor; //label.ForeColor;

                            textFrameFixed.PropertyName = "Down";
                            textFrameFixed.PropertyValue = label.FrameSizeFixed;

                            //textFontFixed.PropertyName = "Down";
                            //textFontFixed.PropertyValue = label.FontSizeFixed;
                            if (isPWFont)
                            {
                                textSize.Enabled = !label.FrameSizeFixed;
                                textBold.Enabled = !label.FrameSizeFixed;
                                textItalic.Enabled = !label.FrameSizeFixed;

                                TextMenuMessage_PropertyChanged(label, isSelected, textBold, textItalic, isPWFont, (bool)(textFrameFixed.PropertyValue));
                            }
                        }
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
					        center, 
					        left,
					        right,
					        textBackGroundColor,
					        textBold, 
					        textFont, 
					        textForeColor,
                            textEffect,
                            textFrameFixed,
                            //textFontFixed,
					        textItalic, 
					        textSize, 
                            textKern,
                            textLead }));
                        break;
                    case ShapeType.DynamicText:
                    case ShapeType.Time:
                    case ShapeType.Temperature:
                        var dCenter = new MenuCommand(MenuCommands.TextAlignCenter, isSelected);
                        var dLeft = new MenuCommand(MenuCommands.TextAlignLeft, isSelected);
                        var dRight = new MenuCommand(MenuCommands.TextAlignRight, isSelected);
                        var dTextBackGroundColor = new MenuCommand(MenuCommands.TextBackgroundColor, isSelected);
                        var dTextForeColor = new MenuCommand(MenuCommands.TextFontColor, isSelected);
                        var dTextBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                        var dTextItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
                        var dTextFont = new MenuCommand(MenuCommands.TextFont, isSelected);
                        var dTextFrameFixed = new MenuCommand(MenuCommands.TextFrameFixed, isSelected);
                        var dTextSize = new MenuCommand(MenuCommands.TextFontSize, false);

                        ShapeDynamicTextBase dynamicText = shape as ShapeDynamicTextBase;

                        //textFrameFixed.Enabled = false;

                        if (isSelected)
                        {
                            dCenter.PropertyName = "Down";
                            dCenter.PropertyValue = false;
                            dCenter.PropertyValue = dynamicText.Align == Align.CENTER;

                            dLeft.PropertyName = "Down";
                            dLeft.PropertyValue = false;
                            dLeft.PropertyValue = dynamicText.Align == Align.LEFT;

                            dRight.PropertyName = "Down";
                            dRight.PropertyValue = false;
                            dRight.PropertyValue = dynamicText.Align == Align.RIGHT;

                            dTextBold.Enabled = false;
                            dTextItalic.Enabled = false;

                            dTextBackGroundColor.PropertyName = "SelectedColor";
                            dTextBackGroundColor.PropertyValue = dynamicText.SourceBackColor;

                            dTextForeColor.PropertyName = "SelectedColor";
                            dTextForeColor.PropertyValue = dynamicText.SourceForeColor; //dynamicText.ForeColor;

                            dTextFont.PropertyName = "EditValue";
                            dTextFont.PropertyValue = dynamicText.Font.Name;
                            dTextFont.Enabled = false;

                            dTextSize.PropertyName = "EditValue";
                            dTextSize.PropertyValue = dynamicText.Font.Size;
                            dTextSize.Enabled = false;
                        }
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
					        dCenter, 
					        dLeft,
					        dRight,
					        dTextBackGroundColor,
					        //dTextBold, 
					        dTextFont, 
					        dTextForeColor,
					        //dTextItalic, 
					        dTextSize}));
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
					        dTextBold, 
					        dTextItalic}));
                        break;
                    case ShapeType.Line:
                        var lineColor = new MenuCommand(MenuCommands.LineColor, isSelected);
                        var lineThickness = new MenuCommand(MenuCommands.LineThickness, isSelected);
                        var lineDash = new MenuCommand(MenuCommands.LineDash, isSelected);

                        ShapeLine line = shape as ShapeLine;
                        if (isSelected && ModifierKeys != Keys.Control && ModifierKeys != Keys.Shift)
                        {
                            lineColor.PropertyName = "SelectedColor";
                            lineColor.PropertyValue = line.BorderColor;

                            lineThickness.PropertyName = "EditValue";
                            lineThickness.PropertyValue = line.BorderWidth;

                            lineDash.PropertyName = "EditValue";
                            lineDash.PropertyValue = line.LineDashStyle;
                        }
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                            lineDash,
                            lineColor,
                            lineThickness }));
                        break;
                    case ShapeType.Rectangle:
                    case ShapeType.Ellipse:
                    case ShapeType.UpArrow:
                    case ShapeType.DownArrow:
                    case ShapeType.LeftArrow:
                    case ShapeType.RightArrow:
                        var figureLineColor = new MenuCommand(MenuCommands.LineColor, isSelected);
                        var figureLineThickness = new MenuCommand(MenuCommands.LineThickness, isSelected);
                        var figureLineDash = new MenuCommand(MenuCommands.LineDash, isSelected);
                        var figureColorFill = new MenuCommand(MenuCommands.ColorFill, isSelected);

                        ShapeFigure figure = shape as ShapeFigure;
                        if (isSelected && ModifierKeys != Keys.Control && ModifierKeys != Keys.Shift)
                        {
                            figureLineColor.PropertyName = "SelectedColor";
                            figureLineColor.PropertyValue = figure.BorderColor;

                            figureLineThickness.PropertyName = "EditValue";
                            figureLineThickness.PropertyValue = figure.BorderWidth;

                            figureLineDash.PropertyName = "EditValue";
                            figureLineDash.PropertyValue = figure.LineDashStyle;

                            figureColorFill.PropertyName = "SelectedColor";
                            figureColorFill.PropertyValue = figure.FillColor;
                        }
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                            figureLineThickness,
                            figureLineColor,
                            figureLineDash,
                            figureColorFill }));
                        break;
                    default:
                        return;
                }
                
            }
            ControlService.RefreshPropertyGrid(shape);
        }

        private void DownSend_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            ShapeBase shape = sender as ShapeBase;
            if (shape != null)
            {
                if (shape.IsMoving) return;
                var isSelected = shape.IsSelected;
                LayerControl frameLayer = GetLayerControl(shape);
                if (frameLayer != null) frameLayer.IsSelected = isSelected;

                bool isDynamicText = shape.Type == ShapeType.DynamicText || shape.Type == ShapeType.Time || shape.Type == ShapeType.Temperature;
                MenuMessage menuMessage = null;
                MenuCommand command = null;
                bool isPWFont = false;


                switch (shape.Type)
                {
                    #region Text
                    case ShapeType.Text:
                        ShapeLabel label = shape as ShapeLabel;
                        label.IsBitMapFontOnly = ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly;
                        isPWFont = label.Font.Name == FontManager.GetProWriteFonts()[0];

                        if (e.Name == "TextAlignment")
                        {
                            var center = new MenuCommand(MenuCommands.TextAlignCenter, isSelected);
                            var left = new MenuCommand(MenuCommands.TextAlignLeft, isSelected);
                            var right = new MenuCommand(MenuCommands.TextAlignRight, isSelected);

                            center.PropertyName = "Down";
                            center.PropertyValue = label.TextAlignment == Align.CENTER;

                            left.PropertyName = "Down";
                            left.PropertyValue = label.TextAlignment == Align.LEFT;

                            right.PropertyName = "Down";
                            right.PropertyValue = label.TextAlignment == Align.RIGHT;

                            menuMessage = new MenuMessage(center, left, right);
                        }
                        else if (e.Name == "BackColor")
                        {
                            command = new MenuCommand(MenuCommands.TextBackgroundColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = label.SourceBackColor;
                            //command.PropertyValue = label.BackColor;
                            menuMessage = new MenuMessage(command);
                        }
                        else if (e.Name == "ForeColor")
                        {
                            command = new MenuCommand(MenuCommands.TextFontColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = label.SourceForeColor;
                            //command.PropertyValue = this.ForeColor;
                            menuMessage = new MenuMessage(command);
                        }
                        else if (e.Name == "Font.Style")
                        {
                            var autoSizeText = new MenuCommand(MenuCommands.TextFrameFixed, isSelected);
                            var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                            textBold.PropertyName = "Down";
                            textBold.PropertyValue = (label.Font.Style & FontStyle.Bold) == FontStyle.Bold;

                            var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
                            textItalic.PropertyName = "Down";
                            textItalic.PropertyValue = (label.Font.Style & FontStyle.Italic) == FontStyle.Italic;

                            bool autoSizeTextEnable = true;
                            if (autoSizeText.Enabled != null)
                                autoSizeTextEnable = (bool)(autoSizeText.Enabled);
                            if (autoSizeText.PropertyValue != null)
                                autoSizeTextEnable = (bool)(autoSizeText.PropertyValue);
                            else
                                autoSizeTextEnable = false;
                            TextMenuMessage_PropertyChanged(label, isSelected, textBold, textItalic, isPWFont, autoSizeTextEnable);
                        }
                        else if (e.Name == "LeadAmount")
                        {
                            var textLead = new MenuCommand(MenuCommands.TextLead, isSelected);
                            textLead.PropertyName = "EditValue";
                            textLead.PropertyValue = label.LeadAmount;
                            menuMessage = new MenuMessage(textLead);
                        }
                        else if (e.Name == "KernAmount")
                        {
                            var textKern = new MenuCommand(MenuCommands.TextKern, isSelected);
                            textKern.PropertyName = "EditValue";
                            textKern.PropertyValue = label.KernAmount;

                            menuMessage = new MenuMessage(textKern);
                        }
                        else if (e.Name == "Font.Size")
                        {
                            var autoSizeText = new MenuCommand(MenuCommands.TextFrameFixed, isSelected);
                            var textSize = new MenuCommand(MenuCommands.TextFontSize, !((ShapeLabel)shape).FrameSizeFixed && isSelected);
                            textSize.PropertyName = "EditValue";
                            textSize.PropertyValue = label.Font.Size;

                            var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                            var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);

                            bool autoSizeTextEnable = true;
                            if (autoSizeText.Enabled != null)
                                autoSizeTextEnable = (bool)(autoSizeText.Enabled);
                            if (autoSizeText.PropertyValue != null)
                                autoSizeTextEnable = (bool)(autoSizeText.PropertyValue);
                            else
                                autoSizeTextEnable = false;

                            TextMenuMessage_PropertyChanged(label, isSelected, textBold, textItalic, isPWFont, autoSizeTextEnable);

                            menuMessage = new MenuMessage(textSize);
                        }
                        else if (e.Name == "Font.Name")
                        {
                            var textFont = new MenuCommand(MenuCommands.TextFont, isSelected);
                            textFont.PropertyName = "EditValue";
                            textFont.PropertyValue = label.Font.Name;

                            menuMessage = new MenuMessage(textFont);
                        }
                        else if (e.Name == "TextEffect")
                        {
                            var textEffect = new MenuCommand(MenuCommands.TextEffect, isSelected);
                            textEffect.PropertyName = "EditValue";
                            textEffect.PropertyValue = label.TextEffect;

                            menuMessage = new MenuMessage(textEffect);
                        }
                        else if (e.Name == "FrameSizeFixed")
                        {
                            var textFrameFixed = new MenuCommand(MenuCommands.TextFrameFixed, isSelected);
                            textFrameFixed.PropertyName = "Down";
                            textFrameFixed.PropertyValue = label.FrameSizeFixed;

                            var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                            var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
                            TextMenuMessage_PropertyChanged(label, isSelected, textBold, textItalic, isPWFont, (bool)(textFrameFixed.PropertyValue));

                            menuMessage = new MenuMessage(textFrameFixed);
                        }

                        break;
                    #endregion

                    #region DynamicText Time Temperature
                    case ShapeType.DynamicText:
                    case ShapeType.Time:
                    case ShapeType.Temperature:
                        ShapeDynamicTextBase dynamictext = shape as ShapeDynamicTextBase;
                        if (e.Name == "Align")
                        {
                            var center = new MenuCommand(MenuCommands.TextAlignCenter, isSelected);
                            var left = new MenuCommand(MenuCommands.TextAlignLeft, isSelected);
                            var right = new MenuCommand(MenuCommands.TextAlignRight, isSelected);

                            center.PropertyName = "Down";
                            center.PropertyValue = dynamictext.Align == Align.CENTER;

                            left.PropertyName = "Down";
                            left.PropertyValue = dynamictext.Align == Align.LEFT;

                            right.PropertyName = "Down";
                            right.PropertyValue = dynamictext.Align == Align.RIGHT;

                            menuMessage = new MenuMessage(center, left, right);
                        }
                        else if (e.Name == "BackColor")
                        {
                            command = new MenuCommand(MenuCommands.TextBackgroundColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = dynamictext.SourceBackColor;
                            menuMessage = new MenuMessage(command);
                        }
                        else if (e.Name == "ForeColor")
                        {
                            command = new MenuCommand(MenuCommands.TextFontColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = dynamictext.SourceForeColor;

                            menuMessage = new MenuMessage(command);
                        }
                        else if (e.Name == "Font.Style")
                        {
                            var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
                            textBold.PropertyName = "Down";
                            textBold.PropertyValue = (dynamictext.Font.Style & FontStyle.Bold) == FontStyle.Bold;

                            var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
                            textItalic.PropertyName = "Down";
                            textItalic.PropertyValue = (dynamictext.Font.Style & FontStyle.Italic) == FontStyle.Italic;

                            textBold.Enabled = false;
                            textItalic.Enabled = false;

                            menuMessage = new MenuMessage(textBold, textItalic);
                        }
                        else if (e.Name == "Font.Size")
                        {
                            var textSize = new MenuCommand(MenuCommands.TextFontSize, false); textSize.PropertyName = "EditValue";
                            textSize.PropertyValue = dynamictext.Font.Size;

                            menuMessage = new MenuMessage(textSize);
                        }
                        else if (e.Name == "Font.Name")
                        {
                            var textFont = new MenuCommand(MenuCommands.TextFont, isSelected);
                            textFont.PropertyName = "EditValue";
                            textFont.PropertyValue = dynamictext.Font.Name;

                            menuMessage = new MenuMessage(textFont);
                        }
                        break;
                    #endregion

                    #region Line
                    case ShapeType.Line:
                        ShapeLine line = shape as ShapeLine;
                        if (e.Name == "BorderColor")
                        {
                            command = new MenuCommand(MenuCommands.LineColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = line.BorderColor;
                        }
                        else if (e.Name == "BorderWidth")
                        {
                            command = new MenuCommand(MenuCommands.LineThickness, isSelected);
                            command.PropertyName = "EditValue";
                            command.PropertyValue = line.BorderWidth;
                        }
                        else if (e.Name == "LineDashKind")
                        {
                            command = new MenuCommand(MenuCommands.LineDash, isSelected);
                            command.PropertyName = "EditValue";
                            command.PropertyValue = line.LineDashStyle;
                        }
                        break;
                    #endregion

                    #region Rectangle Ellipse UpArrow LeftArrow RightArrow
                    case ShapeType.Rectangle:
                    case ShapeType.Ellipse:
                    case ShapeType.UpArrow:
                    case ShapeType.DownArrow:
                    case ShapeType.LeftArrow:
                    case ShapeType.RightArrow:
                        ShapeFigure figure = shape as ShapeFigure;
                        if (e.Name == "BorderColor")
                        {
                            command = new MenuCommand(MenuCommands.LineColor, isSelected);
                            command.PropertyName = "SelectedColor";
                            command.PropertyValue = figure.BorderColor;
                        }
                        else if (e.Name == "BorderWidth")
                        {
                            command = new MenuCommand(MenuCommands.LineThickness, isSelected);
                            command.PropertyName = "EditValue";
                            command.PropertyValue = figure.BorderWidth;
                        }
                        else if (e.Name == "LineDashKind")
                        {
                            command = new MenuCommand(MenuCommands.LineDash, isSelected);
                            command.PropertyName = "EditValue";
                            command.PropertyValue = figure.LineDashKind;
                        }
                        else if (e.Name == "FillColor")
                        {
                            command = new MenuCommand(MenuCommands.ColorFill, isSelected);
                            command.PropertyName = "EditValue";
                            command.PropertyValue = figure.LineDashStyle;
                        }
                        break;
                    #endregion

                    default:
                        return;
                }

                if (menuMessage != null)
                    LocalMessageBus.Send(null, menuMessage);
            }
            ControlService.RefreshPropertyGrid(shape);
        }

        private void TextMenuMessage_PropertyChanged(ShapeLabel label, bool isSelected, MenuCommand textBold,
                                                            MenuCommand textItalic, bool isPWFont, bool autoSizeText)
        {
            if (autoSizeText)
            {
                //textItalic.PropertyName = textBold.PropertyName = "Down";
                //textItalic.PropertyValue = textBold.PropertyValue = false;

                textBold.Enabled = false;
                textItalic.Enabled = false;
            }
            else
            {
                textBold.Enabled = true;
                textItalic.Enabled = true;

                if (isPWFont)
                {
                    switch (label.Font.Size)
                    {
                        case 6:
                            textItalic.PropertyName = textBold.PropertyName = "Down";
                            textItalic.PropertyValue = textBold.PropertyValue = false;

                            textBold.Enabled = false;
                            textItalic.Enabled = false;
                            break;
                        case 8:
                            textBold.Enabled = true;
                            textItalic.Enabled = true;
                            break;
                        case 13:
                        case 17:
                            textBold.Enabled = true;

                            textItalic.PropertyName = "Down";
                            textItalic.PropertyValue = false;
                            textItalic.Enabled = false;
                            break;
                        default:
                            textBold.Enabled = true;
                            textItalic.Enabled = true;
                            break;
                    }
                }
            }
            
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { textBold, textItalic }));
            this.Invalidate();
        }

        //private void TextMenuMessage_PropertyChanged(ShapeLabel label)
        //{
        //    var isSelected = label.IsSelected;
        //    var textBold = new MenuCommand(MenuCommands.TextBold, isSelected);
        //    var textItalic = new MenuCommand(MenuCommands.TextItalic, isSelected);
        //    bool isPWFont = label.Font.Name == FontManager.GetProWriteFonts()[0];

        //    TextMenuMessage_PropertyChanged(label, isSelected, textBold, textItalic, isPWFont);
        //}

        void shape_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.Name == "IsVisible")
                shapeControl.Invalidate();

            UndoService.AddPropertyChangedAction(sender, e.Name, e.NewValue, e.OldValue);

            ShapeBase shape = sender as ShapeBase;
            if (shape.Type == ShapeType.Video && e.Name == "VideoUrl")
            {
                SetNewShapeVideo(shape as ShapeVideo, true);
                return;
            }
            //shape_SelectedChanged(sender, e);
            DownSend_PropertyChanged(sender, e);
        }

        void shape_deleteEvent(object sender, RemoveBackgroundEventArgs e)
        {
            RemoveLayer(e.Shape);
        }

        void Shapes_ShapeBackgroundChanged(object sender, EventArgs e)
        {
            MoveLast(sender as ShapeBase);
        }
        #endregion
        ShapeTextBase shapeText = null;
        ShapeTime shapeTime = null;
        ShapeTemp shapeTemp = null;
        private void SetShapeText(ShapeBase shape)
        {
            shapeText = (ShapeTextBase)shape;
            TextInputForm frm = new TextInputForm(shapeText.Text);
            frm.UpdateShapeText += SetShapeText;
            frm.ShowDialog();
            this.shapeControl.Invalidate();
        }

        private void SetTimeText(ShapeBase shape)
        {
            shapeTime = (ShapeTime)shape;
            shapeText = (ShapeTime)shape;
            DynamicLayerFormatSelectionForm frm = new DynamicLayerFormatSelectionForm(true, shapeTime.Text, shapeTime.DisplayFormat);
            //TextInputForm frm = new TextInputForm(shapeText.Text);
            frm.UpdateShapeText += SetTimeText;
            frm.ShowDialog();
            this.shapeControl.Invalidate();
        }

        private void SetTimeText(string text, TimeFormat timeFormat)
        {
            //if(string.IsNullOrEmpty(text))
            //    return;
            UndoService.BeginTransaction("Set Date Time");
            shapeText.Text = text;
            shapeTime.DisplayFormat = timeFormat;
            UndoService.Commit();
            this.Refresh();
        }

        private void SetTempText(ShapeBase shape)
        {
            shapeTemp = (ShapeTemp)shape;
            shapeText = (ShapeTemp)shape;
            DynamicLayerFormatSelectionForm frm = new DynamicLayerFormatSelectionForm(false, shapeTemp.Text, shapeTemp.DisplayFormat);
            //TextInputForm frm = new TextInputForm(shapeText.Text);
            frm.UpdateShapeTempText += SetTempText;
            frm.ShowDialog();
            this.shapeControl.Invalidate();
        }

        private void SetTempText(string text, TempFormat tempFormat)
        {
            //if(string.IsNullOrEmpty(text))
            //    return;
            UndoService.BeginTransaction("Set Date Time");
            shapeText.Text = text;
            shapeTemp.DisplayFormat = tempFormat;
            UndoService.Commit();
            this.Refresh();

        }

        /// <summary>
        /// 设置动态文字数据源
        /// add by Michael 2008-11-12
        /// </summary>
        private void SetDataSource(ShapeBase shape, ShapeType type)
        {
            shapeText = (ShapeTextBase)shape;
            TextInputForm frm = new TextInputForm(shapeText.Text);
            frm.UpdateShapeText += SetShapeText;
            frm.ShowModalDialog();
            this.shapeControl.Invalidate();
        }

        private void SetShapeText(string text)
        {
            //if(string.IsNullOrEmpty(text))
            //    return;
            UndoService.BeginTransaction("Set Text");
            shapeText.Text = text;
            UndoService.Commit();
            //this.Refresh();
            FormHelper.InvokeMethod(shapeControl, () => shapeControl.Invalidate());
        }


        private void SetShapeImage(ShapeBase shape)
        {
            ShapeImage shapeImage = (ShapeImage)shape;
            string file = MsgBox.OpenFile(Constance.FileFilter.Image);
            if (string.IsNullOrEmpty(file))
                return;

            UndoService.BeginTransaction("Set Image");

            SetShapeImage(shapeImage, file);

            UndoService.Commit();
        }

        #region SetNewShapeImage(DoubleClick shape select shape functions)
        /// <summary>
        /// Function: Set new ShapeImage
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30
        /// </summary>
        /// <param name="shape">ShapeBase</param>
        private void SetNewShapeImage(ShapeBase shape)
        {
            ShapeImage shapeImage = (ShapeImage)shape;
            string file = MsgBox.OpenFile(Constance.FileFilter.Image);
            if (string.IsNullOrEmpty(file))
                return;

            UndoService.BeginTransaction("Set Image");
            if (!string.IsNullOrEmpty(shapeImage.ImageUrl))
            {
                ImageInfo imgInfo = LibraryGroup.Images.GetByPath(shapeImage.ImageUrl);
                ILockLibraryItem locker = null;
                if (imgInfo != null)
                    locker = imgInfo as ILockLibraryItem;
                if (locker != null && locker.IsLock)
                    locker.IsLock = false;
            }
            SetNewShapeImage(shapeImage, file);

            UndoService.Commit();
        }

        /// <summary>
        /// Function: Set new ShapeImage
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30
        /// </summary>
        /// <param name="shapeImage">ShapeImage</param>
        /// <param name="file">Source file path</param>
        private void SetNewShapeImage(ShapeImage shapeImage, string file)
        {
            Image img = GetImageFromFile(file);

            if (img != null)
            {
                if (RenameShapeImage(shapeImage, file))
                {
                    SetVirtualBounds(shapeImage);//add by Michael
                    this.Invalidate();
                }
                else
                    return;
            }
            //add by Michael
            shapeImage.IsGif = Common.CommonHelper.GetMediaLength(file) > 0;
        }

        /// <summary>
        /// Function: File is lock
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4
        /// </summary>
        /// <param name="file">Full file path</param>
        /// <param name="type">LibraryType:enum</param>
        /// <returns>bool</returns>
        private bool IsLockFile(string file, LibraryType type)
        {
            if (type == LibraryType.Image)
            {
                ImageInfo imgInfo = LibraryGroup.Images.GetByPath(file);
                ILockLibraryItem locker = null;
                if (imgInfo != null)
                    locker = imgInfo as ILockLibraryItem;
                if (locker != null && locker.IsLock)
                    return true;
            }
            if (type == LibraryType.Video)
            {
                VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(file);
                ILockLibraryItem locker = null;
                if (videoInfo != null)
                    locker = videoInfo as ILockLibraryItem;
                if (locker != null && locker.IsLock)
                    return true;
            }
            return false;
        }

        /// <summary>
        /// Function: Rename ShapeImage
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30 
        /// </summary>
        /// <param name="shapeImg">ShapeImage</param>
        /// <param name="file">Source file path</param>
        /// <returns>bool:Success(true),Failure(false)</returns>
        private bool RenameShapeImage(ShapeImage shapeImg, string file)
        {
            Image img = GetImageFromFile(file);

            if (img != null)
            {
                //File is exist in library images
                if (IOHelper.IsExist(file, "", LibraryType.Image) == FileExistType.Yes)
                {
                    string filepath = IOHelper.GetLibraryFileName(file, "", LibraryType.Image);

                    //Exist and was locked
                    if (IsLockFile(filepath, LibraryType.Image))
                    {
                        MsgBox.Information(Resource.GetFormatString(Resource.Strings.EditerInsertFileLock, LibraryType.Image.ToString().ToLower(), Path.GetFileName(file)));
                        //Rename file
                        string libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewFileName, LibraryType.Image.ToString().ToLower()), Path.GetFileNameWithoutExtension(file));

                        //libraryName += Path.GetExtension(file);
                        if (InputDialog.Result == DialogResult.Cancel)
                            return false;
                        if (string.IsNullOrEmpty(libraryName))
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                            return false;
                        }

                        string path = IOHelper.GetLibraryFileName(file, libraryName, LibraryType.Image);
                        ImageInfo imgInfo = LibraryGroup.Images.GetByPath(path);
                        if (imgInfo != null)
                        {
                            MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, LibraryType.Image.ToString().ToLower(), libraryName));
                            return false;
                        }
                        else
                        {
                            shapeImg.ImageUrl = file;
                            shapeImg.Image = img;
                            LibraryGroup.Images.AddFile(shapeImg, path, true);
                            return true;
                        }
                    }

                    DialogResult result = MsgBox.Confirm(Resource.GetFormatString(Resource.Strings.EditerInsertFileExist, LibraryType.Image.ToString().ToLower(), Path.GetFileName(file)), MessageBoxButtons.YesNo);
                    //Overwrite file
                    if (result == DialogResult.Yes)
                    {
                        string path = IOHelper.GetLibraryFileName(file, "", LibraryType.Image);

                        if (File.Exists(path))
                        {
                            IOHelper.RemoveFile(path);
                        }
                        File.Copy(file, path, false);
                        IOHelper.SetFileAttribute(path, FileAttributes.Normal);
                        ImageInfo imgInfo = LibraryGroup.Images.GetByPath(path);
                        ILockLibraryItem locker = imgInfo as ILockLibraryItem;
                        if (locker != null)
                            locker.IsLock = true;
                        shapeImg.Image = img;
                        shapeImg.ImageUrl = path;

                        //Update database
                        ControlService.LibraryTree.Update(imgInfo);

                        return true;
                    }
                    else
                    {
                        //Rename file
                        string libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewFileName, LibraryType.Image.ToString().ToLower()), Path.GetFileNameWithoutExtension(file));

                        //libraryName += Path.GetExtension(file);
                        if (InputDialog.Result == DialogResult.Cancel)
                            return false;
                        if (string.IsNullOrEmpty(libraryName))
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                            return false;
                        }

                        string path = IOHelper.GetLibraryFileName(file, libraryName, LibraryType.Image);
                        ImageInfo imgInfo = LibraryGroup.Images.GetByPath(path);
                        if (imgInfo != null)
                        {
                            MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, LibraryType.Image.ToString().ToLower(), libraryName));
                            return false;
                        }
                        else
                        {
                            shapeImg.ImageUrl = file;
                            shapeImg.Image = img;
                            LibraryGroup.Images.AddFile(shapeImg, path, true);
                            return true;
                        }
                    }
                }
                else
                {
                    shapeImg.ImageUrl = file;
                    shapeImg.Image = img;
                    LibraryGroup.Images.AddFile(shapeImg, true);
                    return true;
                }
            }
            return false;
        }

        #endregion

        #region SetNewShapeVideo(DoubleClick shape select video functions)
        /// <summary>
        /// Function: Set new ShapeVideo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30
        /// </summary>
        /// <param name="shapeVideo">ShapeVideo</param>
        private void SetNewShapeVideo(ShapeVideo shapeVideo)
        {
            SetNewShapeVideo(shapeVideo, false);
        }

        private void SetNewShapeVideo(ShapeVideo shapeVideo, bool propertyChanged)
        {
            string file = string.Empty;

            if (!propertyChanged)
            {
                file = MsgBox.OpenFile(Constance.FileFilter.Video);
                if (string.IsNullOrEmpty(file) || !Common.CommonHelper.IsVideoSource(file))
                    //a
                    return;
            }

            UndoService.BeginTransaction("Set Video");

            if (!string.IsNullOrEmpty(shapeVideo.VideoUrl))
            {
                VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(shapeVideo.VideoUrl);
                ILockLibraryItem locker = null;
                if (videoInfo != null)
                    locker = videoInfo as ILockLibraryItem;
                if (locker != null && locker.IsLock)
                    locker.IsLock = false;
            }

            SetNewShapeVideo(shapeVideo, file);

            //shapeVideo.VideoUrl = file;
            SetVideoImage(shapeVideo);
            //LibraryGroup.Videos.AddFile(shapeVideo, true);

            UndoService.Commit();
            shapeControl.Invalidate();

        }

        /// <summary>
        /// Function: Set new ShapeVideo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30
        /// </summary>
        /// <param name="shapeVideo">ShapeVideo</param>
        /// <param name="file">Source file path</param>
        private void SetNewShapeVideo(ShapeVideo shapeVideo, string file)
        {
            //Image img = GetImageFromFile(file);

            if (File.Exists(file))
            {
                if (RenameShapeVideo(shapeVideo, file))
                {
                    SetVirtualBounds(shapeVideo);//add by Michael
                    this.Invalidate();
                }
                else
                    return;
            }
            //add by Michael
            //shapeVideo.IsGif = Common.CommonHelper.GetMediaLength(file) > 0;
        }

        /// <summary>
        /// Function: Rename ShapeVideo
        /// Author  : Jerry Xu
        /// Date    : 2008-12-30 
        /// </summary>
        /// <param name="shapeVideo">ShapeVideo</param>
        /// <param name="file">Source file path</param>
        /// <returns>bool:Success(true),Failure(false)</returns>
        private bool RenameShapeVideo(ShapeVideo shapeVideo, string file)
        {
            if (File.Exists(file))
            {
                //File is exist in library videos
                if (IOHelper.IsExist(file, "", LibraryType.Video) == FileExistType.Yes)
                {
                    string filepath = IOHelper.GetLibraryFileName(file, "", LibraryType.Video);

                    //Exist and was locked
                    if (IsLockFile(filepath, LibraryType.Video))
                    {
                        MsgBox.Information(Resource.GetFormatString(Resource.Strings.EditerInsertFileLock, LibraryType.Video.ToString().ToLower(), Path.GetFileName(file)));
                        //Rename file
                        string libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewLibraryName, LibraryType.Video.ToString().ToLower()), Path.GetFileName(file));

                        if (InputDialog.Result == DialogResult.Cancel)
                            return false;
                        if (string.IsNullOrEmpty(libraryName))
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                            return false;
                        }

                        string path = IOHelper.GetLibraryFileName(file, libraryName, LibraryType.Video);
                        VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(path);
                        if (videoInfo != null)
                        {
                            MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, LibraryType.Video.ToString().ToLower(), libraryName));
                            return false;
                        }
                        else
                        {
                            shapeVideo.VideoUrl = file;
                            //shapeVideo.Image = img;
                            SetVideoImage(shapeVideo);
                            LibraryGroup.Videos.AddFile(shapeVideo, path, true);
                            return true;
                        }
                    }

                    DialogResult result = MsgBox.Confirm(Resource.GetFormatString(Resource.Strings.EditerInsertFileExist, LibraryType.Video.ToString().ToLower(), Path.GetFileName(file)), MessageBoxButtons.YesNo);
                    //Overwrite file
                    if (result == DialogResult.Yes)
                    {
                        string path = IOHelper.GetLibraryFileName(file, "", LibraryType.Video);

                        if (File.Exists(path))
                        {
                            //if (!IOHelper.FileIsUsed(path))
                            IOHelper.RemoveFile(path);
                            //else
                            //    return false;
                        }
                        if (File.Exists(path))
                            File.Copy(file, path, true);
                        else
                            File.Copy(file, path, false);
                        IOHelper.SetFileAttribute(path, FileAttributes.Normal);
                        VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(path);
                        ILockLibraryItem locker = videoInfo as ILockLibraryItem;
                        if (locker != null)
                            locker.IsLock = true;
                        //shapeVideo.Image = img;
                        shapeVideo.VideoUrl = path;
                        SetVideoImage(shapeVideo);
                        //Update database
                        ControlService.LibraryTree.Update(videoInfo);

                        return true;
                    }
                    else
                    {
                        //Rename file
                        string libraryName = InputDialog.GetInputValue(Resource.GetFormatString(Resource.Strings.NewLibraryName, LibraryType.Video.ToString().ToLower()), Path.GetFileName(file));

                        if (InputDialog.Result == DialogResult.Cancel)
                            return false;
                        if (string.IsNullOrEmpty(libraryName))
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.NameEmpty));
                            return false;
                        }

                        string path = IOHelper.GetLibraryFileName(file, libraryName, LibraryType.Video);
                        VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(path);
                        if (videoInfo != null)
                        {
                            MsgBox.Warning(Resource.GetFormatString(Resource.Strings.NameAlreadyExist, LibraryType.Video.ToString().ToLower(), libraryName));
                            return false;
                        }
                        else
                        {
                            shapeVideo.VideoUrl = file;
                            //shapeVideo.Image = img;
                            SetVideoImage(shapeVideo);
                            LibraryGroup.Videos.AddFile(shapeVideo, path, true);
                            return true;
                        }
                    }
                }
                else
                {
                    shapeVideo.VideoUrl = file;
                    //shapeVideo.Image = img;
                    SetVideoImage(shapeVideo);
                    LibraryGroup.Videos.AddFile(shapeVideo, true);
                    return true;
                }
            }
            return false;
        }


        #endregion

        private void SetShapeImage(ShapeImage shapeImage, string file)
        {
            Image img = GetImageFromFile(file);

            if (img != null)
            {
                shapeImage.ImageUrl = file;
                shapeImage.Image = img;
                LibraryGroup.Images.AddFile(shapeImage, true);

                SetVirtualBounds(shapeImage);//add by Michael
                this.Invalidate();
            }
            //add by Michael
            shapeImage.IsGif = Common.CommonHelper.GetMediaLength(file) > 0;
        }

        private void SetShapeVideo(ShapeVideo shapeVideo)
        {
            string file = MsgBox.OpenFile(Constance.FileFilter.Video);
            if (string.IsNullOrEmpty(file) || !Common.CommonHelper.IsVideoSource(file))
                return;

            UndoService.BeginTransaction("Set Video");

            shapeVideo.VideoUrl = file;
            SetVideoImage(shapeVideo);
            LibraryGroup.Videos.AddFile(shapeVideo, true);

            UndoService.Commit();
            shapeControl.Invalidate();
        }

        private void SetVideoImage(ShapeVideo shape)
        {
            //Check.Require(shape.VideoUrl, "shape.VideoUrl", Check.NotNullOrEmpty);

            if ((!string.IsNullOrEmpty(shape.VideoUrl)) && CommonHelper.IsVideoSource(shape.VideoUrl))
            {
                shape.ImageUrl = IOHelper.GenerateTempImagePath();
                //CommonHelper.GetImageFromMedia(shape.VideoUrl, shape.ImageUrl, 200, 200, 0);
                CommonHelper.GetImageFromMedia(shape.VideoUrl, shape.ImageUrl, 0);
                Image image = IOHelper.GetImageFromFile(shape.ImageUrl);
                if (image != null)
                {
                    shape.Image = shape.FormatImage(image);
                    image.Dispose();
                    image = null;
                }

                //LayerControl frameLayer = GetLayerControl(shape);
                //if (frameLayer != null)
                //{
                //    frameLayer.ctlEmphasis.Effect.Width = (int)(CommonHelper.GetMediaLength(shape.VideoUrl) / 10000000) * Constance.TrackBar.UnitWidth;
                //}
            }
        }

        /// <summary>
        /// 调整图形的起点位置在以Zoom为单位的刻度上
        /// 调整图形的长、宽为Zoom的整数倍数关系
        /// add by Michael 2008-9-26
        /// </summary>
        private void SetVirtualBounds(ShapeBase shape)
        {
            int x, y, width, height;
            if (shape.VirtualBounds.X >= 0)
            {
                if (shape.VirtualBounds.X % _Zoom > _Zoom / 2)
                    x = shape.VirtualBounds.X % _Zoom == 0 ? shape.VirtualBounds.X : shape.VirtualBounds.X + (_Zoom - shape.VirtualBounds.X % _Zoom);
                else
                    x = shape.VirtualBounds.X % _Zoom == 0 ? shape.VirtualBounds.X : shape.VirtualBounds.X - shape.VirtualBounds.X % _Zoom;
            }
            else
            {
                if (-shape.VirtualBounds.X % _Zoom > _Zoom / 2)
                    x = shape.VirtualBounds.X - _Zoom - shape.VirtualBounds.X % _Zoom;
                else
                    x = shape.VirtualBounds.X - shape.VirtualBounds.X % _Zoom;
            }

            if (shape.VirtualBounds.Y >= 0)
            {
                if (shape.VirtualBounds.Y % _Zoom > _Zoom / 2)
                    y = shape.VirtualBounds.Y % _Zoom == 0 ? shape.VirtualBounds.Y : shape.VirtualBounds.Y + (_Zoom - shape.VirtualBounds.Y % _Zoom);
                else
                    y = shape.VirtualBounds.Y % _Zoom == 0 ? shape.VirtualBounds.Y : shape.VirtualBounds.Y - shape.VirtualBounds.Y % _Zoom;
            }
            else
            {
                if (-shape.VirtualBounds.Y % _Zoom > _Zoom / 2)
                    y = shape.VirtualBounds.Y - _Zoom - shape.VirtualBounds.Y % _Zoom;
                else
                    y = shape.VirtualBounds.Y - shape.VirtualBounds.Y % _Zoom;
            }

            if (shape.VirtualBounds.Width % _Zoom > _Zoom / 2)
                width = shape.VirtualBounds.Width % _Zoom == 0 ? shape.VirtualBounds.Width : shape.VirtualBounds.Width + (_Zoom - shape.VirtualBounds.Width % _Zoom);
            else
                width = shape.VirtualBounds.Width % _Zoom == 0 ? shape.VirtualBounds.Width : shape.VirtualBounds.Width - shape.VirtualBounds.Width % _Zoom;

            if (shape.VirtualBounds.Height % _Zoom > _Zoom / 2)
                height = shape.VirtualBounds.Height % _Zoom == 0 ? shape.VirtualBounds.Height : shape.VirtualBounds.Height + (_Zoom - shape.VirtualBounds.Height % _Zoom);
            else
                height = shape.VirtualBounds.Height % _Zoom == 0 ? shape.VirtualBounds.Height : shape.VirtualBounds.Height - shape.VirtualBounds.Height % _Zoom;

            shape.Populate(new Point(x, y), new Size(width, height), _sign.Type, _signSize, _Zoom);
        }

        /// <summary>
        /// 根据System Default里设置的值来更新VirtualBounds的大小
        /// add by Michael 2008-12-18
        /// </summary>
        private void SetVirtualBoundsBySystemDefault(ShapeBase shape)
        {
            int _width = 0;
            int _height = 0;
            var info = _sign.Template.Message;
            Point virtualLocation = shape.VirtualBounds.Location;

            switch (shape.Type)
            {
                case ShapeType.Image:
                    _width = info.ImageLayer.Width;
                    _height = info.ImageLayer.Height;
                    if (info.ImageLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
                case ShapeType.Video:
                    _width = info.VideoLayer.Width;
                    _height = info.VideoLayer.Height;
                    if (info.VideoLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
                case ShapeType.Temperature:
                    _width = info.TemperatureLayer.Width;
                    _height = info.TemperatureLayer.Height;
                    if (info.TemperatureLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
                case ShapeType.DynamicText:
                    _width = info.DynamicTextLayer.Width;
                    _height = info.DynamicTextLayer.Height;
                    if (info.DynamicTextLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
                case ShapeType.Time:
                    _width = info.TimeLayer.Width;
                    _height = info.TimeLayer.Height;
                    if (info.TimeLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
                case ShapeType.Text:
                    _width = info.TextLayer.Width;
                    _height = info.TextLayer.Height;
                    if (info.TextLayer.FitToSign)
                    {
                        _width = _sign.Width;
                        _height = _sign.Height;
                        virtualLocation = new Point(0, 0);
                    }
                    break;
            }
            if (_width > _Zoom && _height > _Zoom)
            {
                shape.Populate(virtualLocation, new Size(_width * _Zoom, _height * _Zoom), _sign.Type, _signSize, _Zoom);
            }
        }

        /// <summary>
        /// 根据System Default里设置的值来更新shape的属性信息
        /// add by Michael 2008-12-18
        /// </summary>
        private void SetPropertyBySystemDefault(ShapeBase shape)
        {
            var template = _sign.Template.Message;
            if (shape.Type == ShapeType.DynamicText)
            {
                ShapeDynamicText _shape = shape as ShapeDynamicText;

                var info = template.DynamicTextLayer;
                _shape.Align = info.Align;
                _shape.BackColor = SignTypeHandler.ConvertColor(info.BackGroundColor, _sign.Type);
                _shape.ForeColor = SignTypeHandler.ConvertColor(info.ForeColor, _sign.Type);
                _shape.Font.FromFont(info.TextFont);
                _shape.RollRate = info.RollRate;
                _shape.RollWay = info.RollWay;
            }

            if (shape.Type == ShapeType.Text)
            {
                ShapeLabel _shape = shape as ShapeLabel;
                
                var info = template.TextLayer;
                _shape.BackColor = SignTypeHandler.ConvertColor(info.BackGroundColor, _sign.Type);
                _shape.ForeColor = SignTypeHandler.ConvertColor(info.ForeColor, _sign.Type);
                _shape.Font.FromFont(info.TextFont);
            }

            if (shape.Type == ShapeType.Image)
            {
                ShapeImage _shape = shape as ShapeImage;
                
                var info = template.ImageLayer;
                _shape.SizeMode = info.SizeMode;
            }

            if (shape.Type == ShapeType.Temperature)
            {
                ShapeTemp _shape = shape as ShapeTemp;
                
                var info = template.TemperatureLayer;
                _shape.DisplayFormat = info.DisplayFormat;
                _shape.ForeColor = SignTypeHandler.ConvertColor(info.ForeColor, _sign.Type);
                _shape.Font.FromFont(info.Font);
            }

            if (shape.Type == ShapeType.Time)
            {
                ShapeTime _shape = shape as ShapeTime;
                
                var info = template.TimeLayer;
                _shape.DisplayFormat = info.DisplayFormat;
                _shape.ForeColor = SignTypeHandler.ConvertColor(info.ForeColor, _sign.Type);
                _shape.Font.FromFont(info.Font);
            }

            if (shape.Type == ShapeType.Line)
            {
                ShapeLine _shape = shape as ShapeLine;
                var info = template.PaintLayer;
                //_shape.BorderColor = info.LineColor;
                _shape.BorderWidth = info.LineWidth;
                _shape.LineDashKind = info.LineDashKind;
            }

            if (shape is ShapeFigure)
            {
                ShapeFigure _shape = shape as ShapeFigure;
                var info = template.PaintLayer;
                //_shape.BorderColor = info.LineColor;
                _shape.BorderWidth = info.LineWidth;
                _shape.LineDashKind = info.LineDashKind;
            }
        }

        private static Image GetImageFromFile(string imagePath)
        {
            try
            {
                if (File.Exists(imagePath))
                {
                    IOHelper.SetFileAttribute(imagePath, FileAttributes.Normal);
                    using (FileStream stream = new FileStream(imagePath, FileMode.Open))
                    {
                        Image image = Image.FromStream(stream);
                        stream.Dispose();
                        IOHelper.SetFileAttribute(imagePath, FileAttributes.ReadOnly);
                        return image;
                    }
                }
            }
            catch (Exception ex)
            {
                MsgBox.Warning("Invalid format file");
            }

            return null;
        }

        /// <summary>
        /// Function: New Shape select file
        /// Author  : Jerry Xu
        /// Date    : 2009-2-16
        /// </summary>
        private void ShapeNewFile()
        {
            ShapeBase[] selectedShapes = shapeControl.Document.SelectedShapes;

            if (selectedShapes.Length == 1)
            {
                ShapeBase shape = selectedShapes[0];
                //if (!shape.IsVisible
                //    &&shape.Type!= ShapeType.Time
                //    && shape.Type!= ShapeType.Temperature)
                //{
                //    return;
                //}
                //UndoService.Rollback();
                UndoService.BeginTransaction("Set shape Url");
                ShapeType type = shape.Type;
                switch (type)
                {
                    case ShapeType.Image:
                        SetNewShapeImage(shape);
                        break;
                    case ShapeType.Video:
                        SetNewShapeVideo(shape as ShapeVideo);
                        break;
                    case ShapeType.Text:
                        SetShapeText(shape);
                        break;
                    case ShapeType.Time:
                        SetTimeText(shape);
                        break;
                    case ShapeType.Temperature:
                        SetTempText(shape);
                        break;
                    //case ShapeType.DynamicText:
                    //    SetDataSource(shape, ShapeType.DynamicText);
                    //    break;
                    //case ShapeType.DynamicVideo:
                    //    SetDataSource(shape, ShapeType.DynamicVideo);
                    //    break;
                }

                UndoService.Commit();
            }
        }

        void OnShapeControlDoubleClick(object sender, EventArgs e)
        {
            ShapeBase[] selectedShapes = shapeControl.Document.SelectedShapes;

            if (selectedShapes.Length == 1)
            {
                ShapeBase shape = selectedShapes[0];
                if (!shape.IsVisible)
                {
                    return;
                }
                //UndoService.Rollback();
                UndoService.BeginTransaction("Set shape Url");
                ShapeType type = shape.Type;
                switch (type)
                {
                    case ShapeType.Image:
                        SetNewShapeImage(shape);
                        break;
                    case ShapeType.Video:
                        SetNewShapeVideo(shape as ShapeVideo);
                        break;
                    case ShapeType.Text:
                        SetShapeText(shape);
                        break;
                    case ShapeType.DynamicText:
                        SetDataSource(shape, ShapeType.DynamicText);
                        break;
                    case ShapeType.DynamicVideo:
                        SetDataSource(shape, ShapeType.DynamicVideo);
                        break;
                    case ShapeType.Time:
                        SetTimeText(shape);
                        break;
                    case ShapeType.Temperature:
                        SetTempText(shape);
                        break;
                }

                UndoService.Commit();
            }
        }

        private void MergeMessage(MessageInfo msg)
        {
            Check.Require(msg, "msg", Check.NotNull);
            ShapeLayer[] layers = msg.Items;
            if (layers == null || layers.Length < 1)
                return;

            if (msg.SignType.HasValue && msg.SignType.Value != _sign.Type)
                msg.UpdateSignType(_sign.Type);

            List<ShapeBase> mergedShapes = new List<ShapeBase>();
            foreach (ShapeLayer layer in layers)
            {
                if (layer.Shape != null)
                {
                    var item = layer.Copy() as ShapeLayer;
                    item.Shape.InitEvent();

                    if (item.Shape.Type == ShapeType.ShapeDraw)
                    {
                        if (shapeControl.Document.ShapeDraw.Count > 0)
                            AddShape(item.Shape, ShapeAddMode.Clone);
                        else
                            AddLayer(item, ShapeAddMode.Clone);
                        mergedShapes.Add(item.Shape);
                    }
                    else
                    {
                        LayerControl lc = NewLayerControl(item, true);
                        AddLayer(lc, ShapeAddMode.Clone);
                        if (lc.Shape.IsBackground)
                        {
                            lc.Shape.BeginEdit();
                            lc.Shape.IsBackground = false;
                            lc.Shape.EndEdit();

                            lc.Shape.IsBackground = true;
                        }
                        mergedShapes.Add(item.Shape);
                    }
                }
            }
            foreach (ShapeBase shape in mergedShapes)
            {
                shape.BeginEdit();
                shape.IsSelected = true;
                shape.EndEdit();
            }
            SetLayerControlByNetSelected(null);
            ControlService.EnableCopyMenu(true);
        }

        private void OpenMessage(MessageInfo msg)
        {
            Check.Require(msg, "msg", Check.NotNull);
            ShapeLayer[] layers = msg.Items;
            if (layers == null || layers.Length < 1)
                return;

            foreach (ShapeLayer layer in layers)
            {
                if (layer.Shape != null)
                {
                    var item = layer;
                    item.Shape.InitEvent();

                    if (item.Shape.Type == ShapeType.ShapeDraw)
                    {
                        if (shapeControl.Document.ShapeDraw.Count > 0)
                            AddShape(item.Shape, ShapeAddMode.Clone);
                        else
                            AddLayer(item, ShapeAddMode.Clone);
                    }
                    else
                    {
                        AddLayer(NewLayerControl(item, false), ShapeAddMode.Clone);
                    }
                }
            }

            ControlService.EnableCopyMenu(true);
        }
    }

    public enum ShapeAddMode
    {
        ToolBox,
        Menu,
        Clone,
    }
}
