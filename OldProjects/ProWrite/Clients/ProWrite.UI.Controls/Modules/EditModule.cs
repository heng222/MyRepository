//---------------------------------------------------------------------
//
// File: EditorTab.cs
//
// Description:
// User Control of EditorTab 
//
// Author: Louis
//
// Modify History:
//      Kevin 2008-6-19 迁移
//      Kevin 2008-6-20 修正对效果数据的加载
//      Kevin 2008-6-30 Remove msgtab, tpMsg0,currentSign,indexID,
//          _messageTabCtrl,tpMessage fields in EditorTab, Remove CurrentSign property in EditorTab, Add class MessageTabPage in EditorTab
//      Kevin 2008-7-10 Remove field propertyGrid, remove OnPropertyGridEnabled,OnAssociateObjectToPropertyGrid,pgcLayer_CellValueChanged
//      Jerry Xu 2009-3-25 Update method:ModuleShown()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using System.Threading;
using System.Collections.Specialized;
using System.Drawing.Imaging;
using ProWrite.Core;
using ProWrite.Resources;
using DevExpress.XtraTab;
using DevExpress.Utils;
using DevExpress.XtraTab.ViewInfo;
using ProWrite.UI.Controls;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using ProWrite.UI.Controls.Library;
using ProWrite.UI.Controls.CopyPaste;
using CP = ProWrite.UI.Controls.CopyPaste.CopyAction;
using ProWrite.Entity.Shape;
using System.Reflection;
using DevExpress.XtraBars;

using ProWrite.UI.Controls.ShapeTools;
using ProWrite.UFE;

namespace ProWrite.UI.Controls.Modules
{
    /// <summary>
    /// Editor Module
    /// </summary>
    [PWModule(ModuleNames.Editor)]
    public partial class EditorModuleNew : ModuleControl<MessageInfo, MessageTabControl, MessageControl, ShapeCopyAction>
    //ControlBase
    {
        /// <summary>
        /// Constructure function
        /// </summary>
        public EditorModuleNew()
        {
            InitializeComponent();

            RegisterDockPanel(dockPanelToolBox, ControlService.ToolBox, Docks.ToolBox);
            RegisterDockPanel(dockPanelEffect, ControlService.EffectTree, Docks.Effects);
            RegisterDockPanel(dockPanelLibrary, ControlService.LibraryTree, Docks.Library);
            RegisterDockPanel(dockPanelProperty, ControlService.PropertyGrid, Docks.Properties);

            RegisterMenuAction();

            LocalMessageBus.Subject<PropertySetMessage>().Observers += (s, msg) =>
            {
                PropertySetMessage = msg;
                Update(msg.Command);
            };
        }

        private void RegisterMenuAction()
        {
            //Actions[MenuCommands.SendToSign] = SendToSign;
            Actions[MenuCommands.SendToPlaylist] = SendToPlaylist;
            Actions[MenuCommands.SendToScheduler] = SendToScheduler;
            Actions[MenuCommands.SendMessageOrPlaylistToSign] = SendMessageOrPlaylistToSign;
            Actions[MenuCommands.SendPlayListToSign] = SendMessageOrPlaylistToSign;
            Actions[MenuCommands.NewMessage] = New;
            Actions[MenuCommands.NewLibraryGroup] = delegate { ControlService.LibraryTree.AddLibraryGroup(); };
            Actions[MenuCommands.ZoomIn] = delegate
            {
                if (MessageControl.Current != null)
                    MessageControl.Current.ZoomIn();
            };
            Actions[MenuCommands.ZoomOut] = delegate
            {
                if (MessageControl.Current != null)
                    MessageControl.Current.ZoomOut();
            };

            Actions[MenuCommands.Pointer] = delegate { OnAddShape(ShapeToolType.ToolPointer); };
            Actions[MenuCommands.Line] = delegate { OnAddShape(ShapeToolType.ToolLine); };
            Actions[MenuCommands.Rectangle] = delegate { OnAddShape(ShapeToolType.ToolRectangle); };
            Actions[MenuCommands.Ellipse] = delegate { OnAddShape(ShapeToolType.ToolEllipse); };
            Actions[MenuCommands.ArrowUp] = delegate { OnAddShape(ShapeToolType.ToolUpArrow); };
            Actions[MenuCommands.ArrowDown] = delegate { OnAddShape(ShapeToolType.ToolDownArrow); };
            Actions[MenuCommands.ArrowLeft] = delegate { OnAddShape(ShapeToolType.ToolLeftArrow); };
            Actions[MenuCommands.ArrowRight] = delegate { OnAddShape(ShapeToolType.ToolRightArrow); };

            Actions[MenuCommands.Text] = delegate { OnAddShape(ShapeType.Text); };
            Actions[MenuCommands.Image] = delegate { OnAddShape(ShapeType.Image); };
            Actions[MenuCommands.Video] = delegate { OnAddShape(ShapeType.Video); };
            Actions[MenuCommands.DynamicText] = delegate { OnAddShape(ShapeType.DynamicText); };
            Actions[MenuCommands.DynamicVideo] = delegate { OnAddShape(ShapeType.DynamicVideo); };
            Actions[MenuCommands.Time] = delegate{OnAddShape(ShapeType.Time);};
            Actions[MenuCommands.Temperature] = delegate { OnAddShape(ShapeType.Temperature); };


            Actions[MenuCommands.TextAlignCenter] = SetShapeProperty;
            Actions[MenuCommands.TextAlignLeft] = SetShapeProperty;
            Actions[MenuCommands.TextAlignRight] = SetShapeProperty;
            Actions[MenuCommands.TextBackgroundColor] = SetShapeProperty;
            Actions[MenuCommands.TextBold] = SetShapeProperty;
            Actions[MenuCommands.TextEffect] = SetShapeProperty;
            Actions[MenuCommands.TextFont] = SetShapeProperty;
            Actions[MenuCommands.TextFontColor] = SetShapeProperty;
            //Actions[MenuCommands.TextFontSizeFixed] = SetShapeProperty;
            Actions[MenuCommands.TextFrameFixed] = SetShapeProperty;
            Actions[MenuCommands.TextItalic] = SetShapeProperty;
            Actions[MenuCommands.TextFontSize] = SetShapeProperty;
            Actions[MenuCommands.TextKern] = SetShapeProperty;
            Actions[MenuCommands.TextLead] = SetShapeProperty;
            Actions[MenuCommands.LineColor] = SetShapeProperty;
            Actions[MenuCommands.LineThickness] = SetShapeProperty;
            Actions[MenuCommands.ColorFill] = SetShapeProperty;
            Actions[MenuCommands.LineDash] = SetShapeProperty;

        }
        #region Methods

        #region Module Control
        /// <summary>
        /// get module name
        /// </summary>
        public override string ModuleName
        {
            get
            {
                return ModuleNames.Editor;
            }
        }

        protected override void ModuleShown()
        {
            base.ModuleShown();
            ControlService.LibraryTree.Controller.Type = LibraryGroup.EditorFilter;
            ItemVisibility visibility= ItemVisibility.Never;
            //ControlService.BarButton.Caption = "asdfadsf";
            bool insertEnabled = TabControl.Current != null;
            bool canCopy = insertEnabled && CopyAction.CanCopy;
            bool canPast = insertEnabled && CopyAction.CanPaste;
            if (insertEnabled)
                visibility = ItemVisibility.Always;
            bool sendToEnabled = HasInLibrary && ( TabControl.Current != null && !TabControl.Current.ChangedService.HasChanged) ;
            bool canOpen = CommonHelper.IsShowOpenDialog(LibraryType.Message);

            
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                , new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = insertEnabled, Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.InsertPlaylist, Enabled = insertEnabled, Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.InsertTimeSlice, Enabled = insertEnabled, Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.Text, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Image, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Video, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.DynamicText, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                //, new MenuCommand{Command= MenuCommands.DynamicVideo, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command = MenuCommands.Time, Enabled = insertEnabled,  Visibility = ItemVisibility.Always}
                , new MenuCommand{Command = MenuCommands.Temperature,Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Copy, Enabled = canCopy, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Paste, Enabled = canPast, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Enabled = sendToEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToSign, Enabled = TabControl.Current != null, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToPlaylist, Enabled = TabControl.Current != null, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToScheduler, Enabled = TabControl.Current != null, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendMessageOrPlaylistToSign, Enabled = TabControl.Current != null, Visibility = ItemVisibility.Always}
                 , new MenuCommand{Command= MenuCommands.SendPlayListToSign, Enabled = TabControl.Current != null, Visibility = ItemVisibility.Always}
                  ,new MenuCommand{Command= MenuCommands.Save, Enabled = TabControl.Current != null
                     &&TabControl.Current.Model != null
                     &&TabControl.Current.ChangedService.HasChanged, Visibility = ItemVisibility.Always}
                ,new MenuCommand{Command= MenuCommands.SaveAs, Enabled = TabControl.Current != null
                     &&TabControl.Current.Model != null
                     &&TabControl.Current.Model.Items.Length>0, Visibility = ItemVisibility.Always}
                }));
            

            //if (TabControl.Current == null || TabControl.Current.Model == null)
            //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewMessage));

        }

        protected override void ModuleClosed()
        {
            base.ModuleClosed();
            DataGate.Log.Debug("Editor Module LocalMessageBus.Send Start;");

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert,  Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.Text,  Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.Image,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.Video,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicText, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicVideo,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Time,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Temperature,Visibility = ItemVisibility.Never}

                , new MenuCommand{Command= MenuCommands.SendToLiveStorage,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToSign,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToPlaylist,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToScheduler,Visibility = ItemVisibility.Never}
                }));
            DataGate.Log.Debug("Editor Module LocalMessageBus.Send End;");
        }

        public override LibraryType ModelType
        {
            get
            {
                return LibraryType.Message;
            }
        }

        protected override void Delete()
        {
            if (MessageControl.Current != null
                &&MessageControl.Current.SelectedLayers.Count>0)
            {
                if (MessageControl.Current.SelectedLayers.Count == 1)
                {
                    string msg = MessageControl.Current.SelectedLayers[0].Shape.Type.ToString().ToLower();//.Replace("shape", "picture");
                    if (msg == ShapeType.ShapeDraw.ToString().ToLower())
                        msg = "shape";
                    if (MsgBox.Confirm("Are you sure you want to delete this " + msg +"?") != DialogResult.Yes)
                        return;
                }
                else
                {
                    if (MsgBox.Confirm("Are you sure you want to delete these " + MessageControl.Current.SelectedLayers.Count.ToString() + " items?") != DialogResult.Yes)
                        return;
                }
                MessageControl.Current.RemoveLayer();
            }
        }

        #endregion

        #region Menu event
       
        private void OnAddShape(ShapeToolType type)
        {
            MessageControl messageCtrl = MessageControl.Current;
            if (messageCtrl == null) return;
            Canvas canvas = messageCtrl.ShapeControl;
            canvas.ActiveTool = type;
        }

        private void OnAddShape(ShapeType type)
        {
            MessageControl messageCtrl = MessageControl.Current;
            if (messageCtrl == null) return;
            messageCtrl.AddLayer(type, ShapeAddMode.Menu);
        }

        private PropertySetMessage PropertySetMessage;

        private void SetShapeProperty()
        {
            MessageControl messageCtrl = MessageControl.Current;
            if (messageCtrl != null)
            {
                Document document = messageCtrl.ShapeControl.Document;
                PropertySetMessage msg = PropertySetMessage;

                switch (msg.Command)
                {
                    case MenuCommands.LineColor:
                        document.SetProperty("BorderColor", msg.PropertyValue);
                        break;
                    case MenuCommands.LineThickness:
                        document.SetProperty("BorderWidth", msg.PropertyValue);
                        break;
                    case MenuCommands.ColorFill:
                        document.SetProperty("FilledColor", msg.PropertyValue);
                        break;
                    case MenuCommands.LineDash:
                        document.SetProperty("LineDashStyle", msg.PropertyValue);
                        break;
                    default:
                        break;
                }

                ShapeBase[] shapes = document.SelectedShapes;

                foreach(ShapeBase shape in shapes) 
                {
                    if ((shape.Type == ShapeType.DynamicText || shape.Type == ShapeType.Temperature || shape.Type == ShapeType.Time) && msg.PropertyName == "TextAlignment")
                    {
                        shape.SetProperty("Align", msg.PropertyValue);
                    }
                    else
                    {
                        shape.SetProperty(msg.PropertyName, msg.PropertyValue);
                        if (msg.PropertyName == "Font.Style")
                        {
                            MessageControl.Current.ChangedService.MarkChanged();
                        }
                    }
                    messageCtrl.ShapeControl.Invalidate();
                }
            }
        }

        #endregion //End Menu events



        #endregion //End Methods

        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.Editor;
            }
        }

        protected override DevExpress.XtraBars.Docking.DockManager DockManager
        {
            get
            {
                return this.dockManager1;
            }
        }
    }
}