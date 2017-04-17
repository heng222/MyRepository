using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using ProWrite.DES;
using ProWrite.Entity.Shape;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.Entity;
using DevExpress.XtraNavBar;
using ProWrite.Core;
using System.IO;
using ProWrite.Resources;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using DevExpress.XtraBars;

namespace ProWrite.UI.Controls.Editor
{
    public partial class MessageControl
    {
        public void AddImageLayer(string filePath)
        {
            if (filePath != string.Empty && File.Exists(filePath))
            {
                //SetFileLock(filePath, ShapeType.Image, true);
                ShapeImage shapeImage = new ShapeImage();
                //shapeImage.BeginEdit();
                UndoService.BeginTransaction("Add Image");
                AddLayer(shapeImage, ShapeAddMode.ToolBox);
                shapeImage.BeginEdit();
                SetShapeImage(shapeImage, filePath);
                shapeImage.FileHandle = LibraryGroup.Images.GetByName(Path.GetFileName(filePath)).Id;
                UndoService.Commit();
                shapeImage.EndEdit();
            }
            else
            {
                MsgBox.Error(Resource.GetString(Resource.Strings.ErrorUnableToLocateFile));
            }
        }

        private static void SetFileLock(string filePath, ShapeType type, bool lockType)
        {
            if (type == ShapeType.Image)
            {
                ImageInfo imageInfo = LibraryGroup.Images.GetByPath(filePath);
                if (imageInfo != null)
                    imageInfo.IsLock = lockType;
            }
            if (type == ShapeType.Video)
            {
                VideoInfo videoInfo = LibraryGroup.Videos.GetByPath(filePath);
                if (videoInfo != null)
                    videoInfo.IsLock = lockType;
            }

        }

        private void AddVideoLayer(string filePath)
        {
            if (filePath != string.Empty && File.Exists(filePath))
            {
                //SetFileLock(filePath, ShapeType.Video, true);
                ShapeVideo shapeVideo = new ShapeVideo();

                shapeVideo.BeginEdit();
                UndoService.BeginTransaction("Add Video");
                shapeVideo.VideoUrl = filePath;
                shapeVideo.FileHandle = LibraryGroup.Videos.GetByName(Path.GetFileName(filePath)).Id;
                shapeVideo.VideoDuration = Common.CommonHelper.GetMediaLength(filePath) / DESConsts.UNITS;
                AddLayer(shapeVideo, ShapeAddMode.ToolBox);
                SetVideoImage(shapeVideo);

                UndoService.Commit();
                shapeVideo.EndEdit();
            }
            else
            {
                MsgBox.Error(Resource.GetString(Resource.Strings.ErrorUnableToLocateFile));
            }
        }

        public void AddLayerDragDrop(ShapeType shapeType, ShapeAddMode mode)
        {
            ShapeBase shape = null;
            SignType _signType = _sign.Type;

            UndoService.BeginTransaction("Add a " + shapeType.ToString());
            switch (shapeType)
            {
                case ShapeType.Text:
                    shape = new ShapeLabel(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.Image:
                    shape = new ShapeImage();
                    break;
                case ShapeType.Line:
                    shape = new ShapeLine();
                    break;
                case ShapeType.Rectangle:
                    shape = new ShapeRectangle(_signType);
                    break;
                case ShapeType.Ellipse:
                    shape = new ShapeEllipse(_signType);
                    break;
                case ShapeType.UpArrow:
                    shape = new ShapeUpArrow(_signType);
                    break;
                case ShapeType.DownArrow:
                    shape = new ShapeDownArrow(_signType);
                    break;
                case ShapeType.RightArrow:
                    shape = new ShapeRightArrow(_signType);
                    break;
                case ShapeType.LeftArrow:
                    shape = new ShapeLeftArrow(_signType);
                    break;
                case ShapeType.Video:
                    shape = new ShapeVideo();
                    break;
                //case ShapeType.Marquee:
                //    shape = new ShapeMarquee();
                //    break;
                case ShapeType.Time:
                    shape = new ShapeTime(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.Temperature:
                    shape = new ShapeTemp(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.DynamicText:
                    shape = new ShapeDynamicText(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.DynamicVideo:
                    shape = new ShapeDynamicVideo(_signType);
                    break;
            }

            shape.InitializeByTemplate(_sign.Template.Message);
            AddLayer(shape, mode);

            UndoService.Commit();

        }

        public void AddLayer(ShapeType shapeType, ShapeAddMode mode)
        {
            ShapeBase shape = null;
            SignType _signType = _sign.Type;

            UndoService.BeginTransaction("Add a " + shapeType.ToString());
            switch (shapeType)
            {
                case ShapeType.Text:
                    shape = new ShapeLabel(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.Image:
                    shape = new ShapeImage();
                    break;
                case ShapeType.Line:
                    shape = new ShapeLine();
                    break;
                case ShapeType.Rectangle:
                    shape = new ShapeRectangle(_signType);
                    break;
                case ShapeType.Ellipse:
                    shape = new ShapeEllipse(_signType);
                    break;
                case ShapeType.UpArrow:
                    shape = new ShapeUpArrow(_signType);
                    break;
                case ShapeType.DownArrow:
                    shape = new ShapeDownArrow(_signType);
                    break;
                case ShapeType.RightArrow:
                    shape = new ShapeRightArrow(_signType);
                    break;
                case ShapeType.LeftArrow:
                    shape = new ShapeLeftArrow(_signType);
                    break;
                case ShapeType.Video:
                    shape = new ShapeVideo();
                    break;
                //case ShapeType.Marquee:
                //    shape = new ShapeMarquee();
                //    break;
                case ShapeType.Time:
                    shape = new ShapeTime(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.Temperature:
                    shape = new ShapeTemp(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.DynamicText:
                    shape = new ShapeDynamicText(_signType, ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly);
                    break;
                case ShapeType.DynamicVideo:
                    shape = new ShapeDynamicVideo(_signType);
                    break;
            }

            shape.InitializeByTemplate(_sign.Template.Message);

            AddLayer(shape, mode);
            UndoService.Commit();

            ShapeNewFile();
            this.shapeControl.Invalidate();
        }

        public void AddLayer(ShapeLayer layer, ShapeAddMode mode)
        {
            AddLayer(layer, layer.Shape, mode, true);
            //masterLayerCtl.CheckLayersTime();
        }

        public void AddLayer(ShapeBase shape, ShapeAddMode mode)
        {
            AddLayer(shape, mode, true);
            //masterLayerCtl.CheckLayersTime();
        }


        public void AddLayerByRedo(LayerControl frameLayer, ShapeAddMode mode)
        {
            UndoService.BeginTransaction("Add Layer");

            frameLayer.Controls[1].Controls.Clear();
            frameLayer.AddNewLayerControlByShapeLayer(frameLayer.Layer.Copy() as ShapeLayer);

            //frameLayer.Layer.PropertyChanged += new EventHandler<PropertyChangedEventArgs>(layer_PropertyChanged);

            NavBarGroup group = frameLayer.Layer.IsDynamicLayer ? dynamicGroup : staticGroup;
            group.ControlContainer.Controls.Add(frameLayer);
            group.GroupClientHeight += (LayerControl._.Height + 2);

            ShapeBase shape = frameLayer.Layer.Shape;
            PopulateShape(shape, mode);
            shapeControl.Document.Add(shape);

            frameLayer.SubscribeEvent();
            SubscribeLayControlEvent(frameLayer);

            frameLayer.Invalidate(true);
            shapeControl.Invalidate(true);

            UndoService.AddLayerAddedAction(frameLayer);
            UpdateShapeVisible();
            UndoService.Commit();
            ControlService.RefreshPropertyGrid(frameLayer.Shape);
            MessageControl_AddLayerEvent(frameLayer, group);
        }

        public void AddLayer(LayerControl frameLayer, ShapeAddMode mode)
        {
            if (frameLayer == null)
                return;

            if (frameLayer.Shape.Type == ShapeType.ShapeDraw
                && GetLayerControl(frameLayer.Shape) != null)
                return;

            UndoService.BeginTransaction("Add Layer");

            var layer = frameLayer.Layer;
            ShapeBase shape = layer.Shape;


            NavBarGroup group = layer.IsDynamicLayer ? dynamicGroup : staticGroup;
            var layerIndex = frameLayer.Index;
            group.ControlContainer.Controls.Add(frameLayer);

            PopulateShape(shape, mode);
            shapeControl.Document.Add(shape);
            //fixed the bug of pasting the painter shape
            if (shape.Type == ShapeType.ShapeDraw)
                layer.Shape = shapeControl.Document.ShapeDraw;

            frameLayer.AddNewLayerControl();

            if (shape.Type == ShapeType.Video)
                SetVideoImage(shape as ShapeVideo);

            int layerLength = (int)(layer.Duration * Constance.TrackBar.UnitWidth);
            //int layerLength = (int)(layer.Real.Duration * Constance.TrackBar.UnitWidth);
            _timeLens[layer.ID] = layerLength;
            if (layerLength > totalTimeLen)
                totalTimeLen = layerLength;
            frameLayer.TrackBarCtrl.TimeEnd = totalTimeLen;

            if (layerIndex != -1)
                group.ControlContainer.Controls.SetChildIndex(frameLayer, layerIndex);
            else      
                layerIndex = group.ControlContainer.Controls.IndexOf(frameLayer);

            //var index = group.ControlContainer.Controls.IndexOf(frameLayer);
            //frameLayer.IsSelected = true;
            //frameLayer.LoadLayerControl();

            frameLayer.SubscribeEvent();
            SubscribeLayControlEvent(frameLayer);
            //if (((LayerControl)_staticContainer.Controls[i - 1]).ctlExitEffect.Visible)

            //shape.IsSelected = true;

            group.GroupClientHeight += (LayerControl._.Height + 2);
            //int layerLength = (int)(item.Duration * Constance.TrackBar.UnitWidth);
            //_timeLens[item.ID] = layerLength;
            //if (layerLength > totalTimeLen)
            //    totalTimeLen = layerLength;
            //frameLayer.TrackBarCtrl.TimeEnd = totalTimeLen;
            //edit by Louist, -7: the label width is 5, for add new item can be seen
            if (ControlService.IsCancelPositions)
                frameLayer.MoveLayerToPlayValue(frameLayer.TrackBarCtrl.CurrentPos/Constance.TrackBar.UnitWidth);

            UpdateScrollBar();
            UndoService.AddLayerAddedAction(frameLayer);
            shapeControl.Invalidate();
            //add by miachael
            UpdateShapeVisible();
            //shape.EndEdit();
            ControlService.RefreshPropertyGrid(shape);
            UndoService.Commit();

            MessageControl_AddLayerEvent(frameLayer, group);
        }

        void MessageControl_AddLayerEvent(LayerControl layerControl, NavBarGroup group)
        {
            if (group != null)
            {
                foreach (LayerControl layerCtr in group.ControlContainer.Controls)
                {
                    layerCtr.Index = group.ControlContainer.Controls.IndexOf(layerCtr);
                }
            }
        }

        void MessageControl_RemoveLayerEvent(LayerControl layerControl, NavBarGroup group)
        {
            if (group != null)
            {
                foreach (LayerControl layerCtr in group.ControlContainer.Controls)
                {
                    layerCtr.Index = group.ControlContainer.Controls.IndexOf(layerCtr);
                }
            }
        }

        private void AddLayer(ShapeBase shape, ShapeAddMode mode, bool enabledCopyMenu)
        {
            AddLayer(null, shape, mode, enabledCopyMenu);

            this.Refresh();

            shape.IsSelected = true;
        }

        private void AddLayer(ShapeLayer layer, ShapeBase shape, ShapeAddMode mode, bool enabledCopyMenu)
        {
            if (shape == null)
                return;

            UndoService.BeginTransaction("Add shape");

            if (shape.LayerType == LayerType.Paint)
            {
                ShapeDraw shapeDraw = shapeControl.Document.ShapeDraw;
                if (shapeDraw.Count > 0)
                {
                    AddShape(shape, mode);
                    ControlService.RefreshPropertyGrid(shape);
                }
                else
                {
                    AddShape(shape, mode);

                    if (layer != null)
                    {
                        layer.Shape = shapeControl.Document.ShapeDraw;
                        AddLayer(NewLayerControl(layer, false), mode);
                    }
                    else
                    {
                        AddLayer(NewLayerControl(new ShapeLayer(shapeControl.Document.ShapeDraw), true), mode);
                    }
                }
            }
            else
            {
                AddLayer(NewLayerControl(new ShapeLayer(shape), true), mode);
            }

            ChangeNewStaticLayerIndex(shape);

            if (enabledCopyMenu)
                ControlService.EnableCopyMenu(enabledCopyMenu);
            UndoService.Commit();
        }

        private void ChangeNewStaticLayerIndex(ShapeBase shape)
        {
            Document shapes = this.shapeControl.Document;

            //Dynamic Shape
            if (   shape.LayerType == LayerType.Temp
                || shape.LayerType == LayerType.Time)
            {
                return;
            }
            else if(shapes.Count >= 1)   //Staitc Shape
            {
                int dynamicShapeStartIndex = -1;

                for (int i = 0; i < shapes.Count; i++)
                {
                    if (shapes[i].LayerType == LayerType.Time
                        || shapes[i].LayerType == LayerType.Temp)
                    {
                        dynamicShapeStartIndex = i;
                        break;
                    }
                }

                if (dynamicShapeStartIndex >= 0)
                {
                    ShapeBase tmpShape = shape;
                    shapes.Remove(shape);
                    shapes.Insert(dynamicShapeStartIndex, tmpShape);

                    for (int i = dynamicShapeStartIndex; i < shapes.Count; i++)
                    {
                        shapes[i].Index = i;
                    }
                }
            }
        }

        private void AddShape(ShapeBase shape, ShapeAddMode mode)
        {
            UndoService.BeginTransaction("Add Shape");

            PopulateShape(shape, mode);
            shapeControl.Document.Add(shape);
            //shape.IsSelected = true;
            LayerControl frameLayer = GetLayerControl(shape);
            if (frameLayer != null)
            {
                //fixed a bug
                if (!frameLayer.Shape.Equals(shapeControl.Document.ShapeDraw))
                    frameLayer.Shape = shapeControl.Document.ShapeDraw;
                frameLayer.IsSelected = true;
            }

            if (shape.Type == ShapeType.ShapeDraw)
            {
                foreach (ShapeBase tmpShape in ((ShapeDraw)(shape)).Childs)
                    UndoService.AddShapeAddedAction(tmpShape);
            }
            else
            {
                UndoService.AddShapeAddedAction(shape);
            }

            if (shape.LayerType == LayerType.Paint)
                MoveLayersLastNew(shape);

            ChangeNewStaticLayerIndex(shape);
            
            UndoService.Commit();
            shapeControl.Invalidate();
        }

        private void PopulateShape(ShapeBase shape, ShapeAddMode mode)
        {
            bool isShapeDraw = false;
            if (shape is ShapeDraw)
            {
                isShapeDraw = true;
                if (shape.SignSize == Size.Empty)
                    (shape as ShapeDraw).PopulateSignInfo(_sign.Type, _signSize, _Zoom);
            }

            int width = _signSize.Width / 4;
            int height = _signSize.Height / 8;

            Document shapes = shapeControl.Document;
            shapes.CancelSelect(true);

            Point location = Point.Empty;

            switch (mode)
            {
                case ShapeAddMode.Clone:	//message drage to message // with ratio change by louis
                    //edit by michael
                    Rectangle rc = Common.CommonHelper.GetVirtualBoundsBySign(shape, _signSize, _Zoom);
                    location = rc.Location;
                    width = rc.Width;
                    height = rc.Height;
                    break;
                case ShapeAddMode.ToolBox:	//drage from toolbox
                    location = shapeControl.PointToClient(Control.MousePosition);
                    if (!_signSize.IsEmpty)
                        width = height = (_signSize.Width > _signSize.Height ? _signSize.Height : _signSize.Width) * _Zoom / 2;
                    break;
                case ShapeAddMode.Menu:		//drage from ribbon
                    if (!_signSize.IsEmpty)
                        width = height = (_signSize.Width > _signSize.Height ? _signSize.Height : _signSize.Width) * _Zoom / 2;
                    break;
            }

            //add by michael
            if (location.X < Constance.ShapeOffset - shapeControl.Bounds.Width)
                location.X = 2 * Constance.ShapeOffset - shapeControl.Bounds.Width;
            if (location.Y < Constance.ShapeOffset - shapeControl.Bounds.Height)
                location.Y = 2 * Constance.ShapeOffset - shapeControl.Bounds.Height;
            if (location.X > shapeControl.Bounds.Width - Constance.ShapeOffset)
                location.X = shapeControl.Bounds.Width - Constance.ShapeOffset;
            if (location.Y > shapeControl.Bounds.Height - Constance.ShapeOffset)
                location.Y = shapeControl.Bounds.Height - Constance.ShapeOffset;
            //add by Louis, located the default location at the center of editor viewer.
            if (location.X == 0 && location.Y == 0 && mode == ShapeAddMode.Menu)
            {
                location.X = _sign.Width / 4 * Zoom;
                location.Y = _sign.Height / 4 * Zoom;
            }

            if (shape is ShapePaint && mode != ShapeAddMode.Clone)
                (shape as ShapePaint).PopulateSignInfo(_sign.Type, _signSize, _Zoom);
            else
                shape.Populate(location, new Size(width, height), _sign.Type, _signSize, _Zoom);

            //if (shape.Type == ShapeType.Video)
            //    SetVideoImage(shape as ShapeVideo);
            //add by kevin
            if ((mode == ShapeAddMode.ToolBox || mode == ShapeAddMode.Menu) && (shape.Type == ShapeType.Text || shape.Type == ShapeType.Time || shape.Type == ShapeType.Temperature || shape.Type == ShapeType.DynamicText))
                shape.Populate(new Point(shape.VirtualBounds.X, shape.VirtualBounds.Y), new Size(shapeControl.Bounds.Width / 2, shapeControl.Height / 4), _sign.Type, _signSize, _Zoom);
            SetVirtualBounds(shape);

            //处理双击克隆生成Mesage的情况
            if (isShapeDraw && ShapeAddMode.Clone == mode)
                foreach (ShapeBase item in (shape as ShapeDraw).Childs)
                    PopulateShape(item, mode);

            //根据System Default里设置的值来更新shape属性
            if (mode == ShapeAddMode.Menu || mode == ShapeAddMode.ToolBox)
            {
                SetVirtualBoundsBySystemDefault(shape);
                SetPropertyBySystemDefault(shape);
            }
        }

        public void RemoveLayer()
        {
            List<LayerControl> items = SelectedLayers;
            if (items.Count > 0)
            {
                UndoService.BeginTransaction("Remove Layers");
                foreach (LayerControl item in items)
                    RemoveLayer(item);

                //masterLayerCtl.CheckLayersTime();

                UndoService.Commit();
            }

        }

        public void RemoveLayer(ShapeBase shape)
        {
            if (shape == null)
                return;

            UndoService.BeginTransaction("Remove Shape");

            if (shape.LayerType != LayerType.Paint)
            {
                RemoveLayer(GetLayerControl(shape));
            }
            else if (shape.Type != ShapeType.ShapeDraw)
            {
                ShapeDraw shapeDraw = shapeControl.Document.ShapeDraw;

                int count = shapeDraw.Count;

                if (count < 1)
                {
                    UndoService.Commit();
                    return;
                }

                if (count == 1)
                {
                    //RemoveLayer(shapeDraw);
                    shapeDraw.BeginEdit();
                    shapeDraw.IsSelected = true;
                    shapeDraw.EndEdit();
                    RemoveLayer(GetLayerControl(shapeDraw));
                }
                else
                {
                    shapeControl.Document.Remove(shape);

                    UndoService.AddShapeRemovedAction(shape);
                    shapeControl.Invalidate();
                }

            }
            //masterLayerCtl.CheckLayersTime();
            UndoService.Commit();
        }

        public void RemoveLayer(LayerControl frameLayer)
        {
            if (frameLayer == null)
                return;

            UndoService.BeginTransaction("Remove Layer");

            Document shapes = shapeControl.Document;
            ShapeBase shape = frameLayer.Shape;
            Control container = shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;

            if (shape.LayerType != LayerType.Paint)
            {
                InternalRemoveLayer(frameLayer, shapes, container, shape);
                SetToolBarDisabled();
            }
            else if (shape.Type == ShapeType.ShapeDraw && (shape as ShapeDraw).Count == (shape as ShapeDraw).SelectedShapes.Length)
            {
                InternalRemoveShapes(shapes.ShapeDraw.Childs);
                if (shapes.ShapeDraw.Count == 0)
                {
                    InternalRemoveLayer(frameLayer, shapes, container, shapes.ShapeDraw);
                }
            }
            else
            {
                ShapeBase[] deletedShapes = shapes.ShapeDraw.SelectedShapes;
                if (deletedShapes != null && deletedShapes.Length > 0)
                {
                    InternalRemoveShapes(deletedShapes);
                }

                if (shapes.ShapeDraw.Count == 0)
                {
                    InternalRemoveLayer(frameLayer, shapes, container, shapes.ShapeDraw);
                }
            }

            UpdateScrollBar();
            shapeControl.Invalidate();
            ControlService.PropertyGrid.SelectedObject = null;
            //masterLayerCtl.CheckLayersTime();

            UndoService.Commit();

            

            btnThumbNailImage.Enabled = shapeControl.Document.Count > 0;
            //if (shapeControl.Document.Count <= 0)
            //{
            //    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
            //     new MenuCommand{Command= MenuCommands.Save, Enabled = false, Visibility = BarItemVisibility.Always}
            //    ,new MenuCommand{Command= MenuCommands.SaveAs, Enabled = false, Visibility = BarItemVisibility.Always}
            //    }));
            //    this.ChangedService.AcceptChanged();
            //}
          RemoveLayerEvent(frameLayer, null);
        }

        private void SetToolBarDisabled()
        {
            bool IsEnable = false;
            var center = new MenuCommand(MenuCommands.TextAlignCenter, IsEnable);
            var left = new MenuCommand(MenuCommands.TextAlignLeft, IsEnable);
            var right = new MenuCommand(MenuCommands.TextAlignRight, IsEnable);
            var textBackGroundColor = new MenuCommand(MenuCommands.TextBackgroundColor, IsEnable);
            var textForeColor = new MenuCommand(MenuCommands.TextFontColor, IsEnable);
            var textBold = new MenuCommand(MenuCommands.TextBold, IsEnable);
            var textItalic = new MenuCommand(MenuCommands.TextItalic, IsEnable);
            var textLead = new MenuCommand(MenuCommands.TextLead, IsEnable);
            var textKern = new MenuCommand(MenuCommands.TextKern, IsEnable);
            var textSize = new MenuCommand(MenuCommands.TextFontSize, IsEnable);
            var textFont = new MenuCommand(MenuCommands.TextFont, IsEnable);
            var textEffect = new MenuCommand(MenuCommands.TextEffect, IsEnable);
            var textFrameFixed = new MenuCommand(MenuCommands.TextFrameFixed, IsEnable);
            var textFontFixed = new MenuCommand(MenuCommands.TextFontSizeFixed, IsEnable);
            var lineColor = new MenuCommand(MenuCommands.LineColor, IsEnable);
            var lineThickness = new MenuCommand(MenuCommands.LineThickness, IsEnable);
            var colorFill = new MenuCommand(MenuCommands.ColorFill, IsEnable);
            var lineDash = new MenuCommand(MenuCommands.LineDash, IsEnable);

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
                        textFontFixed,
						textItalic, 
						textSize, 
                        textKern,
                        textLead,
                        lineDash,
                        lineColor,
                        colorFill,
                        lineThickness, 
                }));
        }

        private void InternalRemoveShapes(ShapeBase[] deletedShapes)
        {
            UndoService.BeginTransaction("Remove Shapes");
            foreach (ShapeBase item in deletedShapes)
            {
                if (item != null)
                {
                    shapeControl.Document.Remove(item);
                    UndoService.AddShapeRemovedAction(item);
                }
            }
            UndoService.Commit();
        }

        private void InternalRemoveLayer(LayerControl frameLayer, Document shapes, Control container, ShapeBase shape)
        {
            //shape.PropertyChanged -= shape_PropertyChanged;
            //shape.BackgroundRemove -= shape_deleteEvent;

            if (shape.Type != ShapeType.ShapeDraw)
            {
                if (shape.Type == ShapeType.Image)
                {
                    string path = (shape as ShapeImage).ImageUrl;
                    SetFileLock(path, ShapeType.Image, false);

                }
                if (shape.Type == ShapeType.Video)
                {
                    string path = (shape as ShapeVideo).VideoUrl;
                    SetFileLock(path, ShapeType.Video, false);

                }
                if (shape.Type == ShapeType.Text)
                {
                    string path = (shape as ShapeLabel).InnerImagePath;
                    if (path != null && path != string.Empty)
                        IOHelper.RemoveFile(path);

                }
                shapes.Remove(shape);
            }
            else
            {
                ShapeBase clone = shape.Copy();
                clone.ID = shape.ID;

                shapes.Remove(shape);
                frameLayer.Shape = clone;
            }
            if (container.Controls.Contains(frameLayer))
                container.Controls.Remove(frameLayer);
            else
            {
                foreach (LayerControl lay in container.Controls)
                    if (lay.Shape.ID == shape.ID)
                    {
                        container.Controls.Remove(lay);
                        break;
                    }

            }
            frameLayer.UnSubscribeEvent();
            UndoService.AddLayerRemovedAction(frameLayer);

            // add by Michael 2008/8/27
            if (shape.IsDynamicLayer)
                layerEditor.Groups[0].GroupClientHeight -= (LayerControl._.Height + 2);
            else
                layerEditor.Groups[1].GroupClientHeight -= (LayerControl._.Height + 2);
        }

        public void MoveLayers(LayerControl source, LayerControl dest, int selectedShapeIndex, int destShapeIndex)
        {
            if (source == null || dest == null || source == dest)
                return;

            Document shapes = this.shapeControl.Document;
            bool isBackGround = shapeControl.Document[0].IsBackground;

            Control container = dest.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int sourceLayerIndex = container.Controls.GetChildIndex(source);
            int destLayerIndex =   container.Controls.GetChildIndex(dest);
            container.Controls.SetChildIndex(source, destLayerIndex);

            if (selectedShapeIndex == -1 || destShapeIndex == -1)
            {
                selectedShapeIndex = source.Shape.Index;
                destShapeIndex = dest.Shape.Index;
            }

            if (isBackGround && destShapeIndex == 0)
                destShapeIndex = 1;

            //移动层是绘图层
            if (source.Shape.LayerType == LayerType.Paint)
            {
                List<ShapeBase> lstShape = new List<ShapeBase>();

                //绘图层从下往上移动
                if (sourceLayerIndex < destLayerIndex)
                {
                    for (int i = 0; i < shapes.Count; i++)
                    {
                        if (shapes[i] is ShapePaint)
                        {
                            ShapeBase shape = shapes[i];
                            shapes.Remove(shapes[i]);
                            lstShape.Insert(0, shape);
                            i--;
                            destShapeIndex++;
                        }
                    }

                    if (destShapeIndex > shapes.Count)
                        destShapeIndex = shapes.Count;

                    for (int i = lstShape.Count - 1; i >= 0; i--)
                    {
                        shapes.Insert(destShapeIndex, lstShape[i]);
                        destShapeIndex++;
                    }
                }
                else   //绘图层从上往下移动
                {
                    for (int i = 0; i < shapes.Count; i++)
                    {
                        if (shapes[i] is ShapePaint)
                        {
                            ShapeBase shape = shapes[i];
                            shapes.Remove(shapes[i]);
                            lstShape.Insert(0, shape);
                            i--;
                        }
                    }

                    for (int i = lstShape.Count - 1; i >= 0; i--)
                    {
                        shapes.Insert(destShapeIndex, lstShape[i]);
                        destShapeIndex++;
                    }
                }                
            }
            else //非绘图层移动
            {                
                #region 如果目标层是绘图层则进行判断源层是向上还是向下移动
                if (dest.Shape.LayerType == LayerType.Paint && destShapeIndex == -1)
                {
                    bool foundPaint = false;
                    int paintStartIndex = -1;
                    int paintEndIndex = -1;

                    for (int i = 0; i < shapes.Count; i++)
                    {
                        if (shapes[i] is ShapePaint)
                        {
                            if (paintStartIndex == -1)
                                paintEndIndex = paintStartIndex = shapes[i].Index;
                            else
                                paintEndIndex = shapes[i].Index;
                            foundPaint = true;
                        }
                        else
                        {
                            if (foundPaint) break;
                        }
                    }

                    if (sourceLayerIndex > destLayerIndex)
                        destShapeIndex = paintStartIndex;
                    else if (sourceLayerIndex < destLayerIndex)
                        destShapeIndex = paintEndIndex;
                }

                ShapeBase shape = source.Shape;
                shapes.RemoveAt(selectedShapeIndex);
                shapes.Insert(destShapeIndex, shape);
                #endregion
            }

            for (int i = 0; i < shapes.Count; i++)
                shapes[i].Index = i;

            ChangedService.MarkChanged();
            UndoService.AddLayerMoveAction(this, source, dest);
            shapeControl.Invalidate();
            container.Invalidate();
        }

        public void MoveLayers(LayerControl source, LayerControl dest)
        {
            MoveLayers(source, dest, -1, -1);
        }

        public void MoveLayers(LayerControl source, LayerDirection direction)
        {
            int sourceindex = shapeControl.Document.IndexOf(shapeControl.Document.SelectedShape);
            if (sourceindex < 0)
                sourceindex = shapeControl.Document.IndexOf(source.Shape);
            LayerControl dest = null;
            int destindex = -1;
            switch (direction)
            {
                case LayerDirection.First:
                    dest = GetLayerControl(source, LayerDirection.Last);
                    destindex = shapeControl.Document.Count - 1;
                    MoveLayers(source, dest, sourceindex, destindex);
                    break;
                case LayerDirection.Forward:
                    MoveLayers(source, GetLayerControl(source, LayerDirection.Back));
                    break;
                case LayerDirection.Back:
                    MoveLayers(source, GetLayerControl(source, LayerDirection.Forward));
                    break;
                case LayerDirection.Last:
                    dest = GetLayerControl(source, LayerDirection.First);
                    destindex = 0;
                    MoveLayers(source, dest, sourceindex, destindex);
                    break;
            }
        }

        public void MoveForward(LayerControl source)
        {
            //MoveLayers(source, LayerDirection.Forward);
            MoveLayersNextNew(source.Shape);
        }

        public void MoveBack(LayerControl source)
        {
            //MoveLayers(source, LayerDirection.Back);
            MoveLayersBackNew(source.Shape);
        }

        public void MoveLast(LayerControl source)
        {
            //MoveLayers(source, LayerDirection.Last);
            MoveLayersFirstNew(source.Shape);
        }

        public void MoveFirst(LayerControl source)
        {
            //MoveLayers(source, LayerDirection.First);
            MoveLayersLastNew(source.Shape);
        }

        public void MoveFirst()
        {
            //MoveFirst(shapeControl.Document.SelectedShape);
            MoveLayersLastNew(shapeControl.Document.SelectedShape);
        }

        public void MoveLast()
        {
            //MoveLast(shapeControl.Document.SelectedShape);
            MoveLayersFirstNew(shapeControl.Document.SelectedShape);
        }

        public void MoveFirst(ShapeBase shape)
        {
            LayerControl source = GetLayerControl(shape);

            MoveFirst(source);
        }

        public void MoveLast(ShapeBase shape)
        {
            LayerControl source = GetLayerControl(shape);
            MoveLast(source);
        }

        //设置图层为最底层
        public void MoveLayersFirstNew(ShapeBase shape)
        {
            Document shapes = this.shapeControl.Document;
            bool isBackGround = shapeControl.Document[0].IsBackground;
            ShapeBase destshape = null;

            if (isBackGround)
            {
                //如果仅一层或最下一层被设为背景层，只要退出就可。
                if (shape.ID == shapeControl.Document[0].ID) return;
                destshape = FindDestShape(shapes, 1, shape.IsDynamicLayer);
            }
            else
            {
                destshape = FindDestShape(shapes, 0, shape.IsDynamicLayer);
            }

            if (destshape.ID == shape.ID) return;

            LayerControl source = this.GetLayerControl(shape);
            LayerControl dest = this.GetLayerControl(destshape);
            //swap item
            Control container = dest.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int sourceIndex = container.Controls.GetChildIndex(source);
            int destIndex = container.Controls.GetChildIndex(dest);
            container.Controls.SetChildIndex(source, destIndex);

            //if (source.Shape.LayerType == LayerType.DynamicText ||
            //    source.Shape.LayerType == LayerType.DynamicVideo ||
            //    source.Shape.LayerType == LayerType.DynamicText)
            //{

            //}

            //swap shape
            if (source.Shape.LayerType == LayerType.Paint && dest.Shape.LayerType == LayerType.Paint)
            {
                //说明在Paint层上，且当前只有一个层，所以不做动作，返回
                return;
            }
            else if (source.Shape.LayerType == LayerType.Paint)
            {
                List<ShapeBase> tmpList = new List<ShapeBase>();
                if (isBackGround)
                {
                    tmpList.Insert(0, shapes[0]);
                    shapes.RemoveAt(0);
                }

                for (int i = shapes.Count - 1; i >= 0; i--)
                {
                    if (shapes[i] is ShapePaint)
                    {
                        ShapeBase s = shapes[i];
                        shapes.Remove(s);
                        if (isBackGround)
                            tmpList.Insert(1, s);
                        else
                            tmpList.Insert(0, s);
                    }
                }

                foreach (ShapeBase s in shapes)
                    tmpList.Add(s);

                shapes.Clear();

                for (int i = 0; i < tmpList.Count; i++)
                {
                    ShapeBase s = tmpList[i] as ShapeBase;
                    s.Index = i;
                    shapes.Add(s);
                }

                //foreach (ShapeBase s in tmpList)
                //    shapes.Add(s);
                //shapes.AddRange(tmpList);
            }
            else if (source.Shape.LayerType != LayerType.Paint)
            {
                shapes.Remove(shape);
                if (isBackGround)
                    shapes.Insert(1, shape);
                else
                    shapes.Insert(0, shape);
            }

            UndoService.AddLayerMoveAction(this, source, dest);
            shapeControl.Invalidate();
            container.Invalidate();
            
        }

        private ShapeBase FindDestShape(Document shapes, int startIndex, bool isDynamicLayer)
        {
            for (int i = startIndex; i < shapes.Count; i++)
            {
                if (shapes[i].IsDynamicLayer == isDynamicLayer)
                {
                    return shapes[i];
                }
            }
            return null;
        }

        //设置图层为最上层
        public void MoveLayersLastNew(ShapeBase shape)
        {
            Document shapes = this.shapeControl.Document;
            ShapeBase destshape = null;
            int pos = shapes.IndexOf(shape);
            if (shape.LayerType == LayerType.Paint)
                for (int i = shapes.Count - 1; i > pos; i--)
                {
                    if (shapes[i].LayerType != LayerType.Paint && !shapes[i].IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        break;
                    }
                }
            else if (shape.IsDynamicLayer)
                for (int i = shapes.Count - 1; i > pos; i--)
                {
                    if (shapes[i].IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        break;
                    }
                }
            else if (!shape.IsDynamicLayer)
                for (int i = shapes.Count - 1; i > pos; i--)
                {
                    if (!shapes[i].IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        break;
                    }
                }

            if (destshape == null || shape.ID == destshape.ID) return;

            LayerControl source = this.GetLayerControl(shape);
            LayerControl dest = this.GetLayerControl(destshape);
            if (source == null || dest == null) return;

            Control container = dest.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int sourceIndex = container.Controls.GetChildIndex(source);
            int destIndex = container.Controls.GetChildIndex(dest);
            container.Controls.SetChildIndex(source, destIndex);

            if (source.Shape.LayerType == LayerType.Paint)
            {
                List<ShapeBase> tmpList = new List<ShapeBase>();
                int index = 0;
                for (int i = 0; i < shapes.Count; i++)
                {
                    if (shapes[i] is ShapePaint)
                    {
                        ShapeBase s = shapes[i];
                        tmpList.Insert(tmpList.Count, s);
                    }
                    else
                    {
                        tmpList.Insert(index, shapes[i]);
                        index++;
                    }
                }
                shapes.Clear();

                for (int i = 0; i < tmpList.Count; i++)
                {
                    ShapeBase s = tmpList[i] as ShapeBase;
                    s.Index = i;
                    shapes.Add(s);
                }
            }
            else if (source.Shape.LayerType != LayerType.Paint)
            {
                shapes.Remove(shape);
                shapes.Insert(shapes.Count, shape);
            }

            UndoService.AddLayerMoveAction(this, source, dest);

            shapeControl.Invalidate();
            container.Invalidate();
        }

        //向下移动一层
        public void MoveLayersBackNew(ShapeBase shape)
        {
            if (shape.Type == ShapeType.ShapeDraw && (shape as ShapeDraw).Count > 0)
                shape = (shape as ShapeDraw).Childs[0];

            //find the targed shape
            Document shapes = this.shapeControl.Document;
            ShapeBase destshape = null;
            int sourceindex = shapes.IndexOf(shape);
            int destindex = -1;
            if (shape.LayerType == LayerType.Paint)
                for (int i = sourceindex - 1; i >= 0; i--)
                {
                    if (shapes[i].LayerType != LayerType.Paint && !shapes[i].IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        destindex = i;
                        break;
                    }
                }
            else
            {
                for (int i = sourceindex - 1; i >= 0; i--)
                {
                    if (shapes[i].IsDynamicLayer == shape.IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        destindex = i;
                        break;
                    }
                }
            }

            if (destshape == null
                || destindex < 0
                || (destindex == 0 && destshape.IsBackground)
                || destshape.ID == shape.ID) return;

            //swap item
            LayerControl source = this.GetLayerControl(shape);
            LayerControl dest = this.GetLayerControl(destshape);
            Control container = dest.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int sourceIndex = container.Controls.GetChildIndex(source);
            int destIndex = container.Controls.GetChildIndex(dest);
            container.Controls.SetChildIndex(source, destIndex);
            if (shape.Type == ShapeType.ShapeDraw) return;

            if (source.Shape.LayerType == LayerType.Paint)
            {
                List<ShapeBase> tmpList = new List<ShapeBase>();
                for (int i = 0; i <= destindex; i++)
                    tmpList.Add(shapes[i]);

                for (int i = destindex + 1; i < shapes.Count; i++)
                {
                    int di = tmpList.IndexOf(destshape);

                    if (shapes[i] is ShapePaint)
                        tmpList.Insert(di, shapes[i]);
                    else
                        tmpList.Add(shapes[i]);
                }
                shapes.Clear();
                for (int i = 0; i < tmpList.Count; i++)
                {
                    ShapeBase s = tmpList[i] as ShapeBase;
                    s.Index = i;
                    shapes.Add(s);
                }
            }
            else if (source.Shape.LayerType != LayerType.Paint && destshape.LayerType == LayerType.Paint)
            {
                for (int i = 0; i < shapes.Count; i++)
                {
                    if (shapes[i].LayerType == LayerType.Paint)
                    {
                        shapes.Remove(shape);
                        shapes.Insert(i, shape);
                        break;
                    }
                }
            }
            else
            {
                shapes.Remove(shape);
                shapes.Insert(destindex, shape);
            }
            UndoService.AddLayerMoveAction(this, source, dest);
            shapeControl.Invalidate();
            container.Invalidate();
        }

        //向上移动一层
        public void MoveLayersNextNew(ShapeBase shape)
        {
            if (shape.Type == ShapeType.ShapeDraw && (shape as ShapeDraw).Count > 0)
                shape = (shape as ShapeDraw).Childs[0];

            //find the targed shape
            Document shapes = this.shapeControl.Document;
            ShapeBase destshape = null;
            int sourceindex = shapes.IndexOf(shape);
            int destindex = -1;
            if (shape.LayerType == LayerType.Paint)
                for (int i = sourceindex; i < shapes.Count; i++)
                {
                    if (shapes[i].LayerType != LayerType.Paint && !shapes[i].IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        destindex = i;
                        break;
                    }
                }
            else
            {
                for (int i = sourceindex + 1; i < shapes.Count; i++)
                {
                    if (shapes[i].IsDynamicLayer == shape.IsDynamicLayer)
                    {
                        destshape = shapes[i];
                        destindex = i;
                        break;
                    }
                }
            }

            if (destshape == null || destshape.ID == shape.ID) return;

            //swap item
            LayerControl source = this.GetLayerControl(shape);
            LayerControl dest = this.GetLayerControl(destshape);
            Control container = dest.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int sourceIndex = container.Controls.GetChildIndex(source);
            int destIndex = container.Controls.GetChildIndex(dest);
            container.Controls.SetChildIndex(source, destIndex);
            if (shape.Type == ShapeType.ShapeDraw && (shape as ShapeDraw).Count <= 0) return;

            if (source.Shape.LayerType == LayerType.Paint)
            {
                List<ShapeBase> tmpList = new List<ShapeBase>();
                for (int i = 0, j = 0; i < shapes.Count; i++)
                {
                    if (shapes[i].LayerType == LayerType.Paint && i < destindex)
                    {
                        tmpList.Add(shapes[i]);
                    }
                    else if (i < destindex)
                    {
                        tmpList.Insert(j, shapes[i]);
                        j++;
                    }
                    else if (shapes[i].ID == destshape.ID && i == destindex)
                        tmpList.Insert(j, shapes[i]);
                    else
                    {
                        tmpList.Add(shapes[i]);
                    }
                }
                shapes.Clear();

                for (int i = 0; i < tmpList.Count; i++)
                {
                    ShapeBase s = tmpList[i] as ShapeBase;
                    s.Index = i;
                    shapes.Add(s);
                }
            }
            else if (source.Shape.LayerType != LayerType.Paint && destshape.LayerType == LayerType.Paint)
            {
                shapes.Remove(shape);
                int desti = shapes.FindLastIndex(delegate(ShapeBase s) { return s.LayerType == LayerType.Paint; });
                shapes.Insert(desti + 1, shape);
            }
            else
            {
                shapes.Remove(shape);
                shapes.Insert(destindex, shape);
            }
            UndoService.AddLayerMoveAction(this, source, dest);
            shapeControl.Invalidate();
            container.Invalidate();
        }

        public void SetBackground(bool IsSet)
        {
            UndoService.BeginTransaction("Set Background");
            ShapeBase shape = shapeControl.Document.SelectedShape;
            shape.IsBackground = IsSet;
            //if (IsSet)
            //    MoveLayersFirstNew(shape);
            shapeControl.Invalidate();
            ControlService.RefreshPropertyGrid(shape);
            UndoService.Commit();
        }

        private LayerControl GetLayerControl(LayerControl layerControl, LayerDirection direction)
        {
            if (layerControl == null)
                return null;

            Control container = layerControl.Shape.IsDynamicLayer ? _dynamicContainer : _staticContainer;
            int index = container.Controls.GetChildIndex(layerControl);
            int count = container.Controls.Count;

            if (count == 1)
                return null;

            int destIndex = -1;

            switch (direction)
            {
                case LayerDirection.First:
                    if (index != 0)
                        destIndex = 0;
                    break;
                case LayerDirection.Forward:
                    if (index > 0)
                        destIndex = index - 1;
                    break;
                case LayerDirection.Back:
                    if (index < count - 1)
                        destIndex = index + 1;
                    break;
                case LayerDirection.Last:
                    if (index != count - 1)
                    {
                        destIndex = count - 1;
                        LayerControl ctrl = container.Controls[destIndex] as LayerControl;
                        if (ctrl.Shape.IsBackground)
                            destIndex = count - 2;
                    }
                    break;
            }

            if (destIndex == -1)
                return null;

            return container.Controls[destIndex] as LayerControl;
        }

        

    }
}
