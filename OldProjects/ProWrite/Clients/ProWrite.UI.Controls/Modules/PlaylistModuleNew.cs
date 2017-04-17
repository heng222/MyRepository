//---------------------------------------------------------------------
//
// File: PlaylistModuleNew.cs
//
// Description:
// PlaylistModuleNew Control 
//
// Author: 
//
// Date: 
//
//Modify History:
//      Jerry Xu 2009-3-20 Add the method:NewTimesliceGroup()
//      Jerry Xu 2009-3-20 Update method:PlaylistModuleNew()
//      Jerry Xu 2009-3-25 Update method:ModuleShown()
//      Jerry Xu 2009-4-8  Update method:ModuleShown()
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
using ProWrite.UI.Controls;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Playlist;
using ProWrite.UI.Controls.Library;
using ProWrite.Entity.Library;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.UI.Controls.CopyPaste;
using DevExpress.XtraBars;
using ProWrite.UFE;

namespace ProWrite.UI.Controls.Modules
{
    [PWModule(ModuleNames.Playlists)]
    public partial class PlaylistModuleNew : ModuleControl<PlaylistInfo, PlaylistTabControl, PlaylistControl, PlaylistCopyAction>
    //ControlBase
    {
		public PlaylistModuleNew()
		{
			InitializeComponent();

			RegisterDockPanel(dockPanelNailImage, ControlService.NailImageBox, Docks.NailImage);
			RegisterDockPanel(dockPanelLibrary, ControlService.LibraryTree, Docks.Library);
			RegisterDockPanel(dockPanelProperty, ControlService.PropertyGrid, Docks.Properties);
			RegisterDockPanel(dockPanelTimeSliceGrp, ControlService.TimeSliceControl, Docks.TimeSliceGroup);

            Actions[MenuCommands.SendToScheduler] = SendToScheduler;
            Actions[MenuCommands.SendMessageOrPlaylistToSign] = SendMessageOrPlaylistToSign;
            Actions[MenuCommands.SendPlayListToSign] = SendMessageOrPlaylistToSign;
            Actions[MenuCommands.NewPlaylist] = New;
            Actions[MenuCommands.NewTimesliceGroup] = NewTimesliceGroup;
		}

        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.Playlist;
            }
        }

        private void NewTimesliceGroup()
        {
            ControlService.TimeSliceControl.EditGroup("");
            ControlService.TimeSliceControl.EnableEditButtonState();
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
			get { return ModuleNames.Playlists; }
		}

        protected override void Delete()
        {
            if (PlaylistControl.Current != null)
            {
                if (MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) != DialogResult.Yes)
                    return;
                PlaylistControl.Current.Delete();
            }
                
        }

		protected override void ModuleShown()
		{
			base.ModuleShown();
			ControlService.SetPlaylistLibraryTree();

            bool insertEnabled = TabControl.Current != null;
            bool insertMessage = insertEnabled && LibraryGroup.Current.Messages.Count > 0;
            bool insertTimeSliceGroup = insertEnabled && LibraryGroup.Current.TimeSliceGroups.Count > 0;
            bool insertPlaylist = insertEnabled && LibraryGroup.Current.Playlists.Count > 0;
            bool sendToEnabled = HasInLibrary && !TabControl.Current.ChangedService.HasChanged;
            bool canCopy = insertEnabled && CopyAction.CanCopy;
            bool canPast = insertEnabled && CopyAction.CanPaste;
            bool canOpen = CommonHelper.IsShowOpenDialog(LibraryType.Playlist);
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert, Enabled = insertEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{ Command= MenuCommands.InsertMessage, Enabled = insertMessage, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.InsertTimeSlice, Enabled = insertTimeSliceGroup, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.InsertPlaylist, Enabled = insertPlaylist, Visibility = ItemVisibility.Always}
                                                , new MenuCommand{ Command= MenuCommands.Text,  Visibility = ItemVisibility.Never}
                                                , new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}

                , new MenuCommand{Command= MenuCommands.Image,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.Video,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicText, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.DynamicVideo,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Time,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command = MenuCommands.Temperature,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.Copy, Enabled = canCopy, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Paste, Enabled = canPast, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Enabled = sendToEnabled, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendToSign, Enabled = TabControl.Current!=null, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToScheduler, Enabled = TabControl.Current!=null, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.SendMessageOrPlaylistToSign, Enabled = TabControl.Current!=null, Visibility = ItemVisibility.Always}
                 , new MenuCommand{Command= MenuCommands.SendPlayListToSign, Enabled = TabControl.Current!=null, Visibility = ItemVisibility.Always}
                 ,new MenuCommand{Command= MenuCommands.Save, Enabled = TabControl.Current != null
                    &&TabControl.Current.Model != null
                    &&TabControl.Current.ChangedService.HasChanged, Visibility = ItemVisibility.Always}
                ,new MenuCommand{Command= MenuCommands.SaveAs, Enabled = TabControl.Current != null
                    &&TabControl.Current.Model != null
                    &&TabControl.Current.Model.Items.Length>0, Visibility = ItemVisibility.Always}
                }));

            //if ((TabControl.Current == null || TabControl.Current.Model == null) && TabControl.TabPages.Count == 0)
            //    New();
            //if (TabControl.Current == null || TabControl.Current.Model == null)
            //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewPlaylist));
		}

        protected override void ModuleClosed()
        {
            base.ModuleClosed();
            DataGate.Log.Debug("Playlist Module LocalMessageBus.Send Start;");

            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{ Command= MenuCommands.Insert, Visibility = ItemVisibility.Never}
                , new MenuCommand{ Command= MenuCommands.InsertMessage, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.InsertTimeSlice,Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.InsertPlaylist,Visibility = ItemVisibility.Never}

                , new MenuCommand{Command= MenuCommands.SendToLiveStorage, Enabled = false, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToSign, Enabled = false, Visibility = ItemVisibility.Never}
                , new MenuCommand{Command= MenuCommands.SendToScheduler, Enabled = false, Visibility = ItemVisibility.Never}
                }));
            DataGate.Log.Debug("Playlist Module LocalMessageBus.Send End;");

        }

		public override LibraryType ModelType
		{
			get
			{
				return LibraryType.Playlist;
			}
		}
	}
}