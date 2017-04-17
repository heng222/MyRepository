//---------------------------------------------------------------------
//
// File: SchedulerTab.cs
//
// Description:
// User Control of SchedulerTab 
//
// Author: Louis
//Modify History:
//      Jerry Xu 2009-3-25 Update method:ChangeState()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraScheduler;
using DevExpress.XtraScheduler.Localization;
using DevExpress.XtraScheduler.Services;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraTreeList;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.UI.Controls.Library;
using DevExpress.XtraTab;
using DevExpress.Utils;
using ProWrite.UI.Controls.Editor;

using ProWrite.Core;
using ProWrite.Resources;
using DevExpress.XtraTab.ViewInfo;
using ProWrite.UI.Controls.CopyPaste;
using DevExpress.XtraBars;
using ProWrite.UFE;
using System.Communication.Messaging;

namespace ProWrite.UI.Controls.Modules
{
    [PWModule(ModuleNames.Scheduler)]
    public partial class SchedulerModule : ModuleControl<SchedulerInfo, ScheduleTabControl, ScheduleControl, SchedulerCopyAction>
    {
        public SchedulerModule()
        {
            InitializeComponent();
            RegisterDockPanel(dockPanelNailImage, ControlService.NailImageBox, Docks.NailImage);
            RegisterDockPanel(dockPanelProperty, ControlService.PropertyGrid, Docks.Properties);
            RegisterDockPanel(dockPanLibrary, ControlService.LibraryTree, Docks.Library);

            Actions[MenuCommands.SendToSign] = SendToSign;
            Actions[MenuCommands.NewScheduler] = New;
        }

        protected override void InitModule()
        {
            base.InitModule();
            LocalMessageBus.Subject<SelectedSignMessage>().Observers += new ObserverHandler<SelectedSignMessage>(SchedulerModule_Observers);
        }

        void SchedulerModule_Observers(object sender, SelectedSignMessage msg)
        {
            if (IsActive)
                ChangeState();
        }

        void ChangeState()
        {
            bool insertEnabled = TabControl.Current != null;
            bool canCopy = insertEnabled && CopyAction.CanCopy;
            bool canPast = insertEnabled && CopyAction.CanPaste;
            bool canOpen = CommonHelper.IsShowOpenDialog(LibraryType.Schedule);
            bool isSaved = TabControl.Current != null
                && TabControl.Current.Model != null
                && ControlService.LibraryTree.Controller.GetNode(TabControl.Current.Model) != null;
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                                , new MenuCommand{ Command= MenuCommands.Text,  Visibility = ItemVisibility.Never}
                                , new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                , new MenuCommand{Command= MenuCommands.Image,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.Video,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicText, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicVideo,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Time,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Temperature,Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = insertEnabled && LibraryGroup.Current.Messages.Count>0, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.InsertTimeSlice, Enabled = insertEnabled && LibraryGroup.Current.TimeSliceGroups.Count>0, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.InsertPlaylist, Enabled = insertEnabled && LibraryGroup.Current.Playlists.Count>0, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToSign, Enabled =  TabControl.Current != null, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Copy, Enabled = canCopy, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Paste, Enabled = canPast, Visibility = ItemVisibility.Always}
                //, new MenuCommand{Command= MenuCommands.SendToSign, Enabled = insertEnabled
                //    && TabControl.Current.Sign.Controller.Connection.User.Status == UserStatus.Online
                //    &&!ScheduleControl.Current.ChangedService.HasChanged
                //    &&ControlService.SignCombo.Current==TabControl.Current.Sign
                //    &&ControlService.SignCombo.Current.Controller.Connection.User.IsFtpRole
                //    &&isSaved, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Enabled = false, Visibility = ItemVisibility.Always}
                ,new MenuCommand{Command= MenuCommands.Save, Enabled = TabControl.Current != null
                    &&TabControl.Current.Model != null
                    &&TabControl.Current.ChangedService.HasChanged, Visibility = ItemVisibility.Always}
                ,new MenuCommand{Command= MenuCommands.SaveAs, Enabled = TabControl.Current != null
                    &&TabControl.Current.Model != null
                    &&TabControl.Current.Model.Items.Length>0, Visibility = ItemVisibility.Always}
                }));

            //if (TabControl.Current == null || TabControl.Current.Model == null)
            //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewScheduler));
        }
        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.Schedule;
            }
        }

        protected override DevExpress.XtraBars.Docking.DockManager DockManager
        {
            get
            {
                return this.dockManager1;
            }
        }

        public override string ModuleName
        {
            get { return ModuleNames.Scheduler; }
        }

        protected override void ModuleShown()
        {
            base.ModuleShown();
            ControlService.LibraryTree.Controller.Type = LibraryGroup.SchedulerFilter;
            ChangeState();
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Open, (LibraryGroup.Current.Messages.Count > 0 && ModelType == LibraryType.Message) || (LibraryGroup.Current.Playlists.Count > 0 && ModelType == LibraryType.Playlist) || (LibraryGroup.Current.Schedulers.Count > 0 && ModelType == LibraryType.Schedule)));
            bool insertEnabled = TabControl.Current != null;
            //bool isSaved = TabControl.Current != null
            //    && TabControl.Current.Model != null
            //    && ControlService.LibraryTree.Controller.GetNode(TabControl.Current.Model) != null;
            //LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
            //    new MenuCommand{ Command= MenuCommands.Insert, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
            //    , new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
            //    , new MenuCommand{Command= MenuCommands.InsertTimeSlice, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
            //    , new MenuCommand{Command= MenuCommands.InsertPlaylist, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
            //    , new MenuCommand{Command= MenuCommands.SendToSign, Enabled = insertEnabled
            //        && ControlService.SignCombo.Current.Controller.Connection.User.Status == UserStatus.Online
            //        &&!ScheduleControl.Current.ChangedService.HasChanged
            //        &&isSaved, Visibility = ItemVisibility.Always}
            //    , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Enabled = false, Visibility = ItemVisibility.Always}
            //    }));
        }


        protected override void ModuleClosed()
        {
            base.ModuleClosed();
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert, Visibility = ItemVisibility.Never}    
                , new MenuCommand{ Command= MenuCommands.InsertMessage, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.InsertTimeSlice,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.InsertPlaylist,Visibility = ItemVisibility.Never}

                , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Visibility = ItemVisibility.Never}
                }));
        }

        protected override void Delete()
        {
            ScheduleControl.Current.DeleteAppointment();
        }
        public override LibraryType ModelType
        {
            get
            {
                return LibraryType.Schedule;
            }
        }


        //private void NewScheduler()
        //{
        //    TabControl.AddPage(null);
        //}
    }
}