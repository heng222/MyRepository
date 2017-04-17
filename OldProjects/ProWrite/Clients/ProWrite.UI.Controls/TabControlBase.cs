//---------------------------------------------------------------------
//
// File: TabControlBase.cs
//
// Description:
//      TabControl class
//
// Author: Kevin
//
//Modify History:
//      Jerry Xu 2009-1-4 Update methods:Save(TControlPanel controlPanel, bool isSaveAs),UpdateModel(TControlPanel controlPanel)
//      Jerry Xu 2009-1-9 Update method:Save(TControlPanel controlPanel, bool isSaveAs)
//      Jerry Xu 2009-1-9 Update method:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-1-14 Update method:AddEntity(TModel item),OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-1-14 Update method:UpdateAndLockModel(TControlPanel controlPanel, TModel model, string modelName)
//      Jerry Xu 2009-1-15 Update method:UpdateModel(TControlPanel controlPanel),UpdateAndLockModel(TControlPanel controlPanel, TModel model, string modelName)
//      Jerry Xu 2009-2-12 Update method:AddEntity(TModel item)
//      Jerry Xu 2009-3-18 Update method Save(TControlPanel controlPanel, bool isSaveAs, bool isShowSuccessMSG)
//      Jerry Xu 2009-3-25 Update method:Save(TControlPanel controlPanel, bool isSaveAs, bool isShowSuccessMSG)
//      Jerry Xu 2009-3-25 Update method:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-4-2  Update method:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-4-8  Update method:PlaylistTabControl : TabControlBase<PlaylistInfo, PlaylistControl, PlaylistCopyAction> PrepareMenuCommands()
//      Jerry Xu 2009-5-7  Update event:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-5-8  Update event:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-5-22 Update event:OnCloseButtonClick(object sender, EventArgs e)
//      Jerry Xu 2009-6-26 Update method:Save(TControlPanel controlPanel, bool isSaveAs, bool isShowSuccessMSG)
//      Jerry Xu 2009-6-30 Update method:Save(TControlPanel controlPanel, bool isSaveAs, bool isShowSuccessMSG)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraTab;
using ProWrite.Entity.Library;
using DevExpress.Utils;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.Dashboard;
using System.Drawing;
using DevExpress.XtraTab.ViewInfo;
using CP = ProWrite.UI.Controls.CopyPaste.CopyAction;
using ProWrite.UI.Controls.CopyPaste;
using ProWrite.UI.Controls.Playlist;
using System.Windows.Forms;
using ProWrite.UI.Controls.Scheduler;
using System.Threading;
using DevExpress.XtraEditors.Controls;
using ProWrite.Core;
using System.Communication.Messaging;
using ProWrite.UI.Controls.Library;
using ProWrite.UI.Controls.MLPlaylist;
using ProWrite.UFE;

using ProWrite.Entity.Shape;
using DevExpress.XtraBars;

using ProWrite.UI.Controls.Modules;
using DevExpress.XtraScheduler.UI;
using DevExpress.XtraScheduler;

namespace ProWrite.UI.Controls
{
    
    public abstract class TabControlBase : XtraTabControl, IPageController
    {
        public abstract void AddPage(MemoryLibraryItem model);
        public abstract void Save(MemoryLibraryItem model);
        public abstract void ClosePage(string pageName);
        public abstract List<MemoryLibraryItem> OpenedModels { get; }
    }

    public abstract class TabControlBase<TModel, TControlPanel, TCopyAction> : TabControlBase
        where TModel : MemoryLibraryItem, new()
        where TControlPanel : ControlPanel<TModel, TControlPanel>, new()
        where TCopyAction : CopyAction<TModel, TControlPanel>, new()
    {
        public const int MaxPageCount = 5;

        private TCopyAction _copyAction;
        public TabControlBase()
        {
            BorderStyle = BorderStyles.NoBorder;
            BorderStylePage = BorderStyles.NoBorder;
            ClosePageButtonShowMode = ClosePageButtonShowMode.InActiveTabPageHeader;
            Dock = DockStyle.Fill;
            _copyAction = new TCopyAction();
        }

        public override List<MemoryLibraryItem> OpenedModels
        {
            get
            {
                List<MemoryLibraryItem> openedlist = new List<MemoryLibraryItem>();
                if (TabPages.Count > 0)
                    foreach (TabPage page in TabPages)
                    {
                        openedlist.Add(page.ControlPanel.Model);
                    }

                return openedlist;
            }
        }

        public virtual void OnBeforeSave(TControlPanel controlPanel, bool isSaveAs)
        {
        }

        public virtual void Save(TControlPanel controlPanel, bool isSaveAs, bool isShowSuccessMSG)
        {
            if (controlPanel == null || controlPanel.Model == null)
                return;
            if (!controlPanel.ChangedService.HasChanged && !isSaveAs)
                return;
            //if (controlPanel.Model.Type == LibraryType.Schedule)
            //{
            //    bool b = false;
            //    for (int i = 0; i < (controlPanel.Model as SchedulerInfo).Items.Length; i++)
            //    {
            //        if ((controlPanel.Model as SchedulerInfo).Items[1].HasExceptions)
            //            b = true;
            //    }
            //    if (b)
            //    {
            //        if (MsgBox.Confirm("Any exceptions associated with this recurring appointment will be lost. Proceed?") == DialogResult.No)
            //            return;
            //    }
            //    //ScheduleControl scheControl= controlPanel as ScheduleControl;
            //    //Appointment apt=AppointmentConverter.Convert((controlPanel.Model as SchedulerInfo).Items[0]);
            //    //MyAppointmentFormController controler = new MyAppointmentFormController(scheControl.Scheduler, apt);
            //}
            MemoryLibraryItem item;
            TModel model = default(TModel);

            if (!isSaveAs)
            {
                //update
                //if (LibraryGroup.Current.Contains(controlPanel.Model))
                //{
                if (controlPanel.IsNew)
                {
                    //MsgBox.Information(ProWrite.Resources.Resource.GetFormatString(ProWrite.Resources.Resource.Strings.LibraryImportNameExistInfo, controlPanel.Model.Type.ToString(), controlPanel.Model.Name));
                    controlPanel.IsNew = false;
                    isSaveAs = true;
                }
                else
                {
                    OnBeforeSave(controlPanel, isSaveAs);
                    UpdateModel(controlPanel);

                    if (controlPanel.Model.Type == LibraryType.Message)
                        LocalMessageBus.Send(this, new LibraryLenghtChangedMessage(controlPanel.Model.Name, controlPanel.Model.Length, controlPanel.Model.Type));


                    item = LibraryGroup.Current.GetByName(controlPanel.Model.Name, controlPanel.Model.Type) as MemoryLibraryItem;
                    if (item != null)
                    {
                        item.Image = null;
                    }
                    bool isEnabled = ControlService.SignCombo.Current.Controller.Connection.User.Status == UserStatus.Online
                        && ControlService.SignCombo.Current == Current.Sign;
                    LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                        new MenuCommand(MenuCommands.Save,false)
                        //, new MenuCommand(MenuCommands.SaveAs,false)
                        , new MenuCommand{ Command =  MenuCommands.SendToSign,Enabled =true, Visibility=ItemVisibility.Always}
                        , new MenuCommand{ Command =  MenuCommands.SendToLiveStorage,Enabled = false}
                        , new MenuCommand{ Command =  MenuCommands.SendToPlaylist,Enabled = true}
                        , new MenuCommand{ Command =  MenuCommands.SendMessageOrPlaylistToSign,Enabled = true}
                         , new MenuCommand{ Command =  MenuCommands.SendPlayListToSign,Enabled = true}
                        , new MenuCommand{ Command =  MenuCommands.SendToScheduler,Enabled = true}
                        }));
                    UndoManager.Current.Clear();

                    //UpdatePlaylistLevel((controlPanel.Model as MemoryLibraryItem).Copy());
                    return;
                    //    }
                    //}
                    //isSaveAs = true;
                }
            }

            string modelName = string.Empty;
            string oldName = string.Empty;

            //Show the saved form
            MessageSaveForm frmSave = new MessageSaveForm(controlPanel.Model.Type);
            frmSave.ShowModalDialog();

            if (string.IsNullOrEmpty(frmSave.ModelName))
            {
                controlPanel.IsNew = true;
                //isSaveAs = true;
                return;
            }

            OnBeforeSave(controlPanel, isSaveAs);
            model = controlPanel.Model.Copy() as TModel;

            controlPanel.ChangedService.SuspendChanged();
            oldName = model.Name;
            model.Name = modelName = frmSave.ModelName;
            if (LibraryGroup.Current.GetByName(frmSave.ModelName, model.Type) == null)
                model.Id = Guid.NewGuid().ToString();
            if (string.IsNullOrEmpty(modelName))
                return;

            //update
            if (frmSave.IsUpdate)
            {
                //close existed
                foreach (TabPage p in TabPages)
                    if (p.Panel.Model.Name == modelName)
                    {
                        ClosePage(p.Text);
                        break;
                    }

                UpdateAndLockModel(controlPanel, model, modelName);

                if (LibraryGroup.Current.GetByName(oldName, model.Type) != null)
                {
                    MemoryLibraryItem item1 = LibraryGroup.Current.GetByName(oldName, model.Type) as MemoryLibraryItem;
                    if (item1 != null)
                    {
                        item1.IsOpen = false;
                        ILockLibraryItem locker1 = item1 as ILockLibraryItem;
                        if (locker1 != null)
                            LibraryGroup.Current.LockLibrary(locker1, false);
                    }
                }

                bool canOpen = CommonHelper.IsShowOpenDialog(model.Type);
                //UpdatePlaylistLevel((model as MemoryLibraryItem).Copy());
                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                            ,new MenuCommand { Command = MenuCommands.InsertMessage,  Enabled = LibraryGroup.Current.Messages.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertTimeSlice,  Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertPlaylist,  Enabled = LibraryGroup.Current.Playlists.Count > 0}
                            }));
                return;
            }

            //save as
            TModel modelItem = model.Copy() as TModel;
            modelItem.Name = controlPanel.Model.Name = modelName;
            controlPanel.LibraryName = modelName;
            modelItem.CreateTime = DateTime.Now;
            controlPanel.IsNew = false;
            modelItem.SetCounterZero();
            if (ControlService.LibraryTree.Add(modelItem))
            {



                //new name
                item = LibraryGroup.Current.GetByName(modelItem.Name, modelItem.Type) as MemoryLibraryItem;
                bool isopen = false;
                if (item != null)
                {
                    isopen = item.IsOpen;
                    item.IsOpen = true;
                    LibraryGroup.Current.LockLibrary(item, true);
                }
                if (isopen)
                {
                    //old name
                    item = LibraryGroup.Current.GetByName(oldName, modelItem.Type) as MemoryLibraryItem;
                    if (item != null)
                    {
                        item.IsOpen = false;
                        LibraryGroup.Current.LockLibrary(item, false);
                    }
                }
                string text = SelectedTabPage.Text;
                string replaceText = text.Replace(oldName, modelItem.Name);
                SelectedTabPage.Text = replaceText;
                controlPanel.ChangedService.AcceptChanged();
                controlPanel.ChangedService.ResumeChanged();
                //controlPanel.IsNew = false;
                if (isShowSuccessMSG)
                    MsgBox.Information(ProWrite.Resources.Resource.GetFormatString(ProWrite.Resources.Resource.Strings.InfoSaveMessage, modelItem.Type.ToString()));
                UndoManager.Current.Clear();

                bool isEnabled = ControlService.SignCombo.Current.Controller.Connection.User.Status == UserStatus.Online
                     && ControlService.SignCombo.Current == Current.Sign;

                bool canOpen = CommonHelper.IsShowOpenDialog(modelItem.Type);


                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                            new MenuCommand(MenuCommands.Save,false)
                            //, new MenuCommand(MenuCommands.SaveAs,false)
                            , new MenuCommand{ Command =  MenuCommands.SendToSign,Enabled =true, Visibility=ItemVisibility.Always}
                            , new MenuCommand{ Command =  MenuCommands.SendToLiveStorage,Enabled = false}
                            , new MenuCommand{ Command =  MenuCommands.SendToPlaylist,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendToScheduler,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendMessageOrPlaylistToSign,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendPlayListToSign,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                            ,new MenuCommand { Command = MenuCommands.InsertMessage,  Enabled = LibraryGroup.Current.Messages.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertTimeSlice,  Enabled = LibraryGroup.Current.TimeSliceGroups.Count > 0}
                            ,new MenuCommand { Command = MenuCommands.InsertPlaylist,  Enabled = LibraryGroup.Current.Playlists.Count > 0}
                            }));


                //UpdatePlaylistLevel((modelItem as MemoryLibraryItem).Copy());
            }
        }

        private static void UpdatePlaylistLevel(MemoryLibraryItem memory)
        {
            if (memory.Type == LibraryType.Playlist)
            {
                PlaylistInfo playlist = memory as PlaylistInfo;
                if (playlist != null && playlist.Items != null && playlist.Items.Length > 0)
                {
                    foreach (LibraryAdapter adapter in playlist.Items)
                    {
                        if (adapter.Target != null && adapter.Target.Type == LibraryType.Playlist)
                        {
                            ControlService.LibraryTree.Update(adapter.Target);
                        }
                    }
                }
            }
        }

        private void UpdateAndLockModel(TControlPanel controlPanel, TModel model, string modelName)
        {
            model.IsOpen = true;

            if (ControlService.LibraryTree.Update(model))
            {
                controlPanel.IsNew = false;

                LibraryGroup.Current.LockLibrary(model, true);

                //controlPanel.Model.Name = modelName;                

                string text = SelectedTabPage.Text;
                string replaceText = text.Replace(controlPanel.Model.Name, modelName);
                SelectedTabPage.Text = replaceText;
                controlPanel.Model.Name = modelName;

                controlPanel.HasSaved = true;
                controlPanel.ChangedService.AcceptChanged();
            }
            controlPanel.ChangedService.ResumeChanged();
        }

        public void UpdateModel(TControlPanel controlPanel)
        {
            TModel model = controlPanel.Model.Copy() as TModel;
            model.ModifyTime = DateTime.Now;
            controlPanel.ChangedService.SuspendChanged();

            model.IsOpen = true;
            if (ControlService.LibraryTree.Update(model))
            {
                controlPanel.HasSaved = true;

                controlPanel.ChangedService.AcceptChanged();
            }

            controlPanel.ChangedService.ResumeChanged();
        }

        public override void Save(MemoryLibraryItem model)
        {
            if (TabPages.Count <= 0)
                return;
            foreach (TabPage item in TabPages)
            {
                if (item.ControlPanel.Model.Name == model.Name
                    &&CommonHelper.LibraryIsSaved(model))
                    item.Save(model);
            }
        }

        public override void AddPage(MemoryLibraryItem model)
        {
            this.AddPage(model as TModel);
        }

        public override void ClosePage(string pageName)
        {
            ProWrite.UI.Controls.TabControlBase<TModel, TControlPanel, TCopyAction>.TabPage page = null;
            foreach (TabPage item in TabPages)
            {
                if (item.Text == pageName.Replace("* ",""))
                {
                    page = item;
                    break;
                }
            }

            if (page != null)
            {
                SelectedTabPage = page;
            }

            UndoService.RemoveService();
            CP.Current = null;

            TabPage tabPage = SelectedTabPage as TabPage;

            if (tabPage != null && tabPage.Panel != null)
            {
                //DialogResult result = DialogResult.Cancel;
                //if (tabPage.Panel.ChangedService.HasChanged)
                //{
                //    tabPage.Panel.ChangedService.SuspendChanged();
                //    tabPage.Panel.LoadModelInfo();
                //    result = MsgBox.Confirm(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.DialogConfirmInfo), MessageBoxButtons.YesNoCancel);
                //    switch (result)
                //    {
                //        case DialogResult.Yes:
                //            if (!tabPage.Panel.Model.IsEmpty)
                //                Save(tabPage.Panel, string.IsNullOrEmpty(tabPage.Panel.Model.Name), true);
                //            else
                //            {
                //                MsgBox.Information(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.DialogSaveEmptyInfo));
                //            }
                //            break;
                //        case DialogResult.No:
                //            break;
                //        case DialogResult.Cancel:
                //            return;
                //    }
                //}

                //tabPage.Panel.OnClosing();

                MemoryLibraryItem item = LibraryGroup.Current.GetByName(tabPage.Panel.Model.Name, tabPage.Panel.Model.Type) as MemoryLibraryItem;
                if (item != null)
                {
                    item.IsOpen = false;
                }
                //if (result == DialogResult.Yes)
                //{
                //    LibraryGroup.Current.LockLibrary(item, false);
                //}
                //else
                //{
                    if (tabPage.Panel.Model.Type == LibraryType.Playlist)
                    {
                        foreach (LibraryAdapter temp in (tabPage.Panel.Model as PlaylistInfo).Items)
                        {
                            LibraryGroup.Current.LockLibrary(temp.Target, false);
                        }
                    }
                    else if (tabPage.Panel.Model.Type == LibraryType.Schedule)
                    {
                        SchedulerInfo info = tabPage.Panel.Model as SchedulerInfo;
                        foreach (MemoryLibraryItem temp in info.Playlists)
                        {
                            LibraryGroup.Current.LockLibrary(temp, false);
                        }
                        foreach (MemoryLibraryItem temp in info.Messages)
                        {
                            LibraryGroup.Current.LockLibrary(temp, false);
                        }
                        foreach (MemoryLibraryItem temp in info.TimeSliceGroups)
                        {
                            LibraryGroup.Current.LockLibrary(temp, false);
                        }
                    }
                    else if (tabPage.Panel.Model.Type == LibraryType.Message)
                    {
                        LibraryGroup.Current.LockLibrary(tabPage.Panel.Model, false);
                    }
                //}
                LibraryGroup.Current.IsLock = false;
                LocalMessageBus.Send(this, new LibraryGroupActionStateMessage(!LibraryGroup.Current.IsLock));

                bool canOpen = CommonHelper.IsShowOpenDialog(tabPage.Panel.Model.Type);


                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                            }));

                TabPages.Remove(tabPage);
                tabPage.Panel.Sign.RefernceCount--;
                //ControlService.SignCombo.Current.RefernceCount--;
                tabPage.Dispose();
                GC.Collect();
                GC.WaitForPendingFinalizers();
                //return;
                //page.Panel.Model.IsOpen = false;
                //page.Panel.Model.IsLock = false;
                //LibraryGroup.Current.IsLock = false;
                    
                //TabPages.Remove(page);

                //ControlService.SignCombo.Current.RefernceCount--;
                //page.Dispose();
                //GC.Collect();
                //GC.WaitForPendingFinalizers();
                //page.Dispose();
                //page = null;
            }
        }

        public class TabPage : XtraTabPage
        {
            private static int _autoId = 0;
            private TControlPanel innerCtrl;
            private LibraryType _libraryType;
            private string _signText = null;
            private bool hasDirty;

            internal TabControlBase<TModel, TControlPanel, TCopyAction> TabControl;

            public TControlPanel ControlPanel { get { return innerCtrl; } }
            public void Populate(TModel item)
            {
                _autoId++;
                ShowCloseButton = DefaultBoolean.True;
                //
                AddEntity(item);
            }

            public void Save(MemoryLibraryItem _model)
            {

                TControlPanel controlPanel = innerCtrl;// TabControl.Current;
                //foreach (TabPage page in TabControl.TabPages)
                //{
                //    if (page.Name.Replace("*", "") == _model.Name)
                //        controlPanel = page as ControlPanel();
                //}
                bool isSaveAs = !LibraryGroup.Current.Contains(_model);
                try
                {
                    TabControl.OnBeforeSave(innerCtrl, isSaveAs);
                }
                catch { }

                innerCtrl.LoadModelInfo();

                var entity = innerCtrl.Model.Copy();
                entity.Name = _model.Name;

               

                //TabControl.Save(innerCtrl, isSaveAs, false);
                if (CommonHelper.LibraryIsSaved(_model))
                {
                    if (LibraryGroup.Current.Contains(entity))
                    {
                        ControlService.LibraryTree.Update(entity);
                        if (controlPanel.Model.Type == LibraryType.Message)
                            LocalMessageBus.Send(this, new LibraryLenghtChangedMessage(_model.Name, _model.Length, _model.Type));
                    }
                    else
                        ControlService.LibraryTree.Add(entity);
                    string oldName = Text.Substring(0, Text.IndexOf("(") - 1).Replace("* ", "");
                    string text = Text;
                    string replaceText = text.Replace(oldName, _model.Name);
                    Text = replaceText;
                    innerCtrl.HasSaved = true;
                    innerCtrl.IsNew = false;
                    innerCtrl.ChangedService.AcceptChanged();
                    //UpdateModel(innerCtrl);
                    UndoManager.Current.Clear();
                }
                

                //innerCtrl.ChangedService.ResumeChanged();
            }
            private void AddEntity(TModel item)
            {

                innerCtrl = new TControlPanel();
                ControlPanel<TModel, TControlPanel>.Current = innerCtrl;
                innerCtrl.Dock = System.Windows.Forms.DockStyle.Fill;
                //innerCtrl.Location = new System.Drawing.Point(0, 0);
                //innerCtrl.Size = new System.Drawing.Size(719, 477);
                innerCtrl.ChangedService.ModelChanged += new EventHandler(OnModelChanged);
                innerCtrl.ChangedService.AcceptedChanged += new EventHandler(OnModelAcceptedChanged);
                SignInfo sign = ControlService.SignCombo.Current;
                string signstring = " (" + sign.Name + " " + sign.Height.ToString() + " x " + sign.Width.ToString() + " " + sign.Type.ToString() + ")";
                _signText = signstring;
                bool isNull = item == null;
                hasDirty = isNull;
                innerCtrl.IsNew = isNull;
                if (isNull)
                {
                    item = new TModel();
                    //add by michael
                    string newName = "New " + item.Type.ToString() + _autoId.ToString();
                    while (ControlService.LibraryTree.Controller.FindNodeByFieldValue("Name", newName) != null)
                    {
                        _autoId++;
                        newName = "New " + item.Type.ToString() + _autoId.ToString();
                    }
                    item.Name = newName;
                }
                else
                    UndoService.Suspend();

                innerCtrl.LibraryName = item.Name;
                _libraryType = item.Type;
                this.Tooltip = signstring;
                Text = !isNull ? (item.Name + signstring) : ("New " + item.Type.ToString() + _autoId.ToString() + signstring);
                innerCtrl.ChangedService.SuspendChanged();

                TModel model;
                if (isNull)
                    model = item;
                else
                    model = item.Copy() as TModel;
                innerCtrl.Populate(
                    sign
                    , model);

                LocalMessageBus.Subject<LibraryRenameMessage>().Observers += new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
                LibraryGroup.Current.IsLock = true;

                LocalMessageBus.Send(this, new LibraryGroupActionStateMessage(!LibraryGroup.Current.IsLock));
                //LocalMessageBus.Subject<LibraryGroupActionStateMessage>().Observers += new ObserverHandler<LibraryGroupActionStateMessage>(TabPage_Observers);
                Controls.Add(innerCtrl);
                innerCtrl.ChangedService.ResumeChanged();
                //ControlService.RefreshPropertyGrid(model);

                if (!isNull)
                    UndoService.Resume();
            }

            //void TabPage_Observers(object sender, LibraryGroupActionStateMessage msg)
            //{
            //    //msg.CanEdit = LibraryGroup.Current.IsLock;
            //}

            void OnLibraryRename(object sender, LibraryRenameMessage msg)
            {
                if (msg.Type == _libraryType && msg.OldName == innerCtrl.LibraryName)
                {
                    innerCtrl.LibraryName = msg.NewName;
                    innerCtrl.Model.Name = msg.NewName;

                    Text = msg.NewName + _signText;
                    //Text = Text.Replace(msg.OldName, msg.NewName);
                }
                //Controls[0].Refresh();

            }

            public bool HasDirty
            {
                get { return hasDirty; }
            }

            private bool HasInLibrary
            {
                get
                {
                    return ControlService.LibraryTree.Controller.GetNode(innerCtrl.Model) != null;
                }
            }

            private bool EnabledSendTo
            {
                get
                {
                    return HasInLibrary && !innerCtrl.ChangedService.HasChanged;
                }
            }


            private void ChangeSendToItemState()
            {
                var enabledSendTo = EnabledSendTo;

                var enableSendToLiveStorage = enabledSendTo;
                var enableSendToScheduler = enabledSendTo;
                var enableSendToSign = enabledSendTo;
                var enableSendToPlaylist = enabledSendTo;

                MemoryLibraryItem modelItem = innerCtrl.Model;
                if (enabledSendTo)
                {
                    enableSendToPlaylist = modelItem.Type != LibraryType.Playlist
                            && modelItem.Type != LibraryType.Schedule;
                    enableSendToScheduler = modelItem.Type != LibraryType.Schedule;

                    var currentUser = ControlService.SignCombo.Current.Controller.Connection.User;
                    var enableFtp = currentUser.Status == UserStatus.Online && currentUser.IsFtpRole;

                    enableSendToLiveStorage = enableFtp;
                    enableSendToSign = enableFtp;
                }

                var commands = new List<MenuCommand>(new MenuCommand[]{
                           new MenuCommand{Command = MenuCommands.SendToLiveStorage,Enabled = enableSendToLiveStorage}
                           , new MenuCommand { Command = MenuCommands.SendToScheduler, Enabled = true }
                           , new MenuCommand { Command = MenuCommands.SendToSign, Enabled = true }
                            , new MenuCommand { Command = MenuCommands.SendMessageOrPlaylistToSign, Enabled = true }
                             , new MenuCommand { Command = MenuCommands.SendPlayListToSign, Enabled = true }
                           , new MenuCommand { Command = MenuCommands.SendToPlaylist, Enabled = true }});

                if (modelItem == null)
                    commands.Add(new MenuCommand { Command = MenuCommands.Delete, Enabled = false });

                LocalMessageBus.Send(null, new MenuMessage(commands.ToArray()));
            }

            void OnModelAcceptedChanged(object sender, EventArgs e)
            {
                if (Text.StartsWith("* "))
                {
                    hasDirty = false;
                    Text = Text.Remove(0, 2);
                    ChangeSendToItemState();
                }
            }

            void OnModelChanged(object sender, EventArgs e)
            {
                if (!Text.StartsWith("* "))
                {
                    Text = "* " + Text;
                    if (!hasDirty)
                    {
                        hasDirty = true;

                        LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.SendToSign,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendToLiveStorage,Enabled = false}
                            , new MenuCommand{ Command =  MenuCommands.SendToPlaylist,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendMessageOrPlaylistToSign,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendPlayListToSign,Enabled = true}
                            , new MenuCommand{ Command =  MenuCommands.SendToScheduler,Enabled = true}
                            }));
                    }
                }
                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                            new MenuCommand(MenuCommands.Save,true)
                            , new MenuCommand(MenuCommands.SaveAs,true)
                            }));
            }

            public TControlPanel Panel
            {
                get { return innerCtrl; }
            }

            protected override void Dispose(bool disposing)
            {
                if (innerCtrl.ChangedService != null)
                {
                    innerCtrl.ChangedService.ModelChanged -= OnModelChanged;
                    innerCtrl.ChangedService.AcceptedChanged -= OnModelAcceptedChanged;
                }
                LocalMessageBus.Subject<LibraryRenameMessage>().Observers -= new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
                base.Dispose(disposing);

                if (innerCtrl != null)
                {
                    innerCtrl.Dispose();
                }
            }
        }

        public virtual void AddPage(TModel model)
        {
            if (TabPages.Count == MaxPageCount)
            {
                if (model != null)
                    model.IsOpen = false;
                MsgBox.Warning("Open page too many.");
                return;
            }

            if (ControlService.SignCombo.Current == null)
            {
                //bug:pw928当没有Sign激活的时候编辑一个message，这个message关闭后就不能再被打开
                if (model != null)
                    model.IsOpen = false;

                MsgBox.Warning(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.AddNewSignFirst));
                return;
            }
            LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Delete, false));
            TabPage newPage = new TabPage();
            //Add TabPage
            if (newPage != null)
            {
                newPage.TabControl = this;
                //
                newPage.Populate(model);
                TabPages.Add(newPage);
                SelectedTabPageIndex = TabPages.Count - 1;
                bool canCopy = CopyAction.CanCopy;
                bool canPast = CopyAction.CanPaste;
                ControlService.SignCombo.Current.RefernceCount++;

                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand{Command= MenuCommands.Copy, Enabled = canCopy, Visibility = ItemVisibility.Always}
                , new MenuCommand{Command= MenuCommands.Paste, Enabled = canPast, Visibility = ItemVisibility.Always}
                }));
            }
        }

        public void ActivePageByModel(MemoryLibraryItem model)
        {
            if (TabPages.Count < 1 || model == null)
                return;

            foreach (TabPage item in TabPages)
            {
                if (item.ControlPanel.Model.Name == model.Name)
                {
                    SelectedTabPage = item;
                    return;
                }
            }
        }

        protected override void OnCloseButtonClick(object sender, EventArgs e)
        {
            base.OnCloseButtonClick(sender, e);

            ClosePageButtonEventArgs ce = e as ClosePageButtonEventArgs;
            if (ce != null)
            {
                SelectedTabPage = ce.Page as XtraTabPage;
            }

            UndoService.RemoveService();
            CP.Current = null;

            TabPage tabPage = SelectedTabPage as TabPage;

            if (tabPage != null && tabPage.Panel != null)
            {
                DialogResult result = DialogResult.Cancel;
                if (tabPage.Panel.ChangedService.HasChanged)
                {
                    tabPage.Panel.ChangedService.SuspendChanged();
                    tabPage.Panel.LoadModelInfo();
                    result = MsgBox.Confirm(ProWrite.Resources.Resource.GetString(ProWrite.Resources.Resource.Strings.DialogConfirmInfo), MessageBoxButtons.YesNoCancel);
                    switch (result)
                    {
                        case DialogResult.Yes:
                            if (!tabPage.Panel.Model.IsEmpty)
                                Save(tabPage.Panel, string.IsNullOrEmpty(tabPage.Panel.Model.Name), true);
                            else
                            {
                                MsgBox.Information(ProWrite.Resources.Resource.GetFormatString(ProWrite.Resources.Resource.Strings.DialogSaveEmptyInfo,tabPage.Panel.Model.Type.ToString(),tabPage.Panel.Model.Name));
                            }
                            break;
                        case DialogResult.No:
                            break;
                        case DialogResult.Cancel:
                            return;
                    }

                    MemoryLibraryItem item = LibraryGroup.Current.GetByName(tabPage.Panel.Model.Name, tabPage.Panel.Model.Type) as MemoryLibraryItem;
                    if (item != null)
                    {
                        item.IsOpen = false;
                        LibraryGroup.Current.LockLibrary(item, false);
                    }
                    else
                    {
                        LibraryGroup.Current.SetLock(tabPage.Panel.Model, false);
                    }
                }
                else
                {
                    MemoryLibraryItem item = LibraryGroup.Current.GetByName(tabPage.Panel.Model.Name, tabPage.Panel.Model.Type) as MemoryLibraryItem;
                    if (item != null)
                    {
                        item.IsOpen = false;
                        LibraryGroup.Current.LockLibrary(item, false);
                    }
                    
                }

                //tabPage.Panel.OnClosing();

                
                LibraryGroup.Current.IsLock = false;
                LocalMessageBus.Send(this, new LibraryGroupActionStateMessage(!LibraryGroup.Current.IsLock));

                bool canOpen = CommonHelper.IsShowOpenDialog(tabPage.Panel.Model.Type);


                LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                            }));

                TabPages.Remove(tabPage);
                tabPage.Panel.Sign.RefernceCount--;
                //ControlService.SignCombo.Current.RefernceCount--;
                tabPage.Dispose();
                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
        }

        

        public abstract TControlPanel Current { get; set; }

        public TCopyAction CopyAction { get { return _copyAction; } }

        public bool HasInLibrary
        {
            get
            {
                return Current != null
                    && ControlService.LibraryTree.Controller.GetNode(Current.Model) != null;
            }
        }

        public bool EnabledSendTo
        {
            get
            {
                return HasInLibrary && !Current.ChangedService.HasChanged;
            }
        }

        public TabPage ActivePage
        {
            get { return this.SelectedTabPage as TabPage; }
        }

        protected virtual void PrepareMenuCommands()
        {
            bool isNullPage = Current == null;
            _menuCommands.Add(new MenuCommand { Command = MenuCommands.Save, Enabled = Current != null && Current.ChangedService.HasChanged });
            bool isHaveItem = false;
            if (Current != null && Current.Model != null)
            {
                if (Current.Model.Type == LibraryType.Playlist)
                    isHaveItem = (Current.Model as PlaylistInfo).Items.Length > 0;
                else if (Current.Model.Type == LibraryType.Message)
                    isHaveItem = (Current.Model as MessageInfo).Items.Length > 0;
                else if (Current.Model.Type == LibraryType.Schedule)
                    isHaveItem = (Current.Model as SchedulerInfo).Items.Length > 0;
            }
            _menuCommands.Add(new MenuCommand { Command = MenuCommands.SaveAs, Enabled = Current != null && isHaveItem });

            if (isNullPage)
            {
                _menuCommands.Add(new MenuCommand { Command = MenuCommands.Delete, Enabled = false });
            }

            var enableUndo = !isNullPage && Current.UndoManager.CanUndo;
            var enableRedo = !isNullPage && Current.UndoManager.CanRedo;

            var enabledSendTo = EnabledSendTo;

            var enableSendToLiveStorage = enabledSendTo;
            var enableSendToScheduler = enabledSendTo;
            var enableSendToSign = enabledSendTo;
            var enableSendToPlaylist = enabledSendTo;
            var visibleSendToSign = ItemVisibility.Never;

            if (enabledSendTo)
            {
                MemoryLibraryItem modelItem = Current.Model;
                enableSendToPlaylist = modelItem.Type != LibraryType.Playlist
                        && modelItem.Type != LibraryType.Schedule;
                enableSendToScheduler = modelItem.Type != LibraryType.Schedule;
                var enableFtp = false;
                if (ControlService.SignCombo.Current != null)
                {
                    var currentUser = ControlService.SignCombo.Current.Controller.Connection.User;
                    enableFtp = currentUser.Status == UserStatus.Online && currentUser.IsFtpRole;
                }
                enableSendToLiveStorage = enableFtp;
                enableSendToSign = enableFtp;

                if (enableSendToSign)
                    visibleSendToSign = ItemVisibility.Always;
            }

            _menuCommands.AddRange(new MenuCommand[]{
                           new MenuCommand { Command = MenuCommands.Undo, Enabled = enableUndo}
                           ,new MenuCommand { Command = MenuCommands.Redo, Enabled = enableRedo}
                           , new MenuCommand{Command = MenuCommands.SendToLiveStorage,Enabled = enableSendToLiveStorage}
                           , new MenuCommand { Command = MenuCommands.SendToScheduler, Enabled = Current!=null }
                           , new MenuCommand { Command = MenuCommands.SendMessageOrPlaylistToSign, Enabled = Current!=null }
                           , new MenuCommand { Command = MenuCommands.SendPlayListToSign, Enabled = Current!=null }
                           , new MenuCommand { Command = MenuCommands.SendToSign, Enabled = Current!=null,Visibility = ItemVisibility.Always }
                           , new MenuCommand { Command = MenuCommands.SendToPlaylist, Enabled = Current!=null }});

        }

        private List<MenuCommand> _menuCommands = new List<MenuCommand>();
        protected virtual List<MenuCommand> MenuItemCommands
        {
            get { return _menuCommands; }
        }

        protected override void OnSelectedPageChanged(object sender, ViewInfoTabPageChangedEventArgs e)
        {
            base.OnSelectedPageChanged(sender, e);


            if (e.Page == null)
            {
                Current = null;
                CP.Current = null;

                ControlService.PropertyGrid.SelectedObject = null;
                UndoService.Current = null;
            }
            else
            {
                Current = (e.Page as TabPage).Panel;
                _copyAction.ControlPanel = Current;
                CP.Current = _copyAction;
                ControlService.PropertyGrid.SelectedObject = Current.Model;
                UndoService.Current = Current.UndoManager;

                //DataGate.Project.RootGroup.Signs.GroupTree.Signs
                bool isHave = false;
                foreach (SignInfo sign in DashboardItem.ActiveSigns)
                {
                    if (sign.Name == Current.Sign.Name)
                        isHave = true;
                }
                if (isHave)
                    LocalMessageBus.Send(this, new SelectedSignMessage(Current.Sign));
                else
                    LocalMessageBus.Send(this, new SelectedSignMessage(null));

            }

            _menuCommands.Clear();
            PrepareMenuCommands();
            ControlService.EnableCopyMenu(false);
            if (_menuCommands.Count > 0)
                LocalMessageBus.Send(this, new MenuMessage(_menuCommands.ToArray()));
        }
    }


    public class MessageTabControl : TabControlBase<MessageInfo, MessageControl, ShapeCopyAction>
    {

        public MessageTabControl()
        {
        }

        public override void OnBeforeSave(MessageControl item, bool isSaveAs)
        {
            if (!isSaveAs)
            {
                IOHelper.RemoveNailImage(item.Model.ImagePath);
            }
            item.GenerateNailImageNoWaitCursor();
            //item.Model.Image = IOHelper.GetImageFromFile(item.Model.ImagePath);
        }

        protected override void PrepareMenuCommands()
        {
            base.PrepareMenuCommands();

            bool enabledDrawing = Current != null;
            bool enabledZoomIn = true;
            bool enabledZoomOut = true;
            if (enabledDrawing)
            {
                enabledZoomIn = Current.ZoomInEnable;
                enabledZoomOut = Current.ZoomOutEnable;
            }

            LocalMessageBus.Send(this, new IsSelectShapImage(false));

            MenuItemCommands.AddRange(new MenuCommand[]{
                new MenuCommand(MenuCommands.Drawing,enabledDrawing),
                new MenuCommand(MenuCommands.Line,enabledDrawing),
                
                new MenuCommand(MenuCommands.LineColor,false),
                new MenuCommand(MenuCommands.LineThickness,false),
                new MenuCommand(MenuCommands.LineDash,false),
                new MenuCommand(MenuCommands.ColorFill,false),

                new MenuCommand(MenuCommands.TextAlignCenter, false),
                new MenuCommand(MenuCommands.TextAlignLeft, false),
                new MenuCommand(MenuCommands.TextAlignRight, false),
                new MenuCommand(MenuCommands.TextBackgroundColor, false),
                new MenuCommand(MenuCommands.TextFontColor, false),
                new MenuCommand(MenuCommands.TextBold, false),
                new MenuCommand(MenuCommands.TextItalic, false),
                new MenuCommand(MenuCommands.TextLead, false),
                new MenuCommand(MenuCommands.TextKern, false),
                new MenuCommand(MenuCommands.TextFontSize, false),
                new MenuCommand(MenuCommands.TextFont, false),
                new MenuCommand(MenuCommands.TextEffect, false),
                new MenuCommand(MenuCommands.TextFrameFixed, false),
                new MenuCommand(MenuCommands.TextFontSizeFixed, false),
                new MenuCommand(MenuCommands.ZoomIn,enabledZoomIn),
                new MenuCommand(MenuCommands.ZoomOut,enabledZoomOut),

                new MenuCommand{Command= MenuCommands.InsertMessage,Visibility = ItemVisibility.Never,Enabled=LibraryGroup.Current.Messages.Count>0},
                new MenuCommand{Command= MenuCommands.InsertPlaylist,Visibility = ItemVisibility.Never,Enabled=LibraryGroup.Current.Playlists.Count>0},
                new MenuCommand{Command= MenuCommands.InsertTimeSlice, Visibility = ItemVisibility.Never,Enabled=LibraryGroup.Current.TimeSliceGroups.Count>0},
                new MenuCommand{Command = MenuCommands.Insert, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.Text, Enabled = enabledDrawing, Visibility = ItemVisibility.Always },
                new MenuCommand{Command = MenuCommands.Image, Enabled = enabledDrawing, Visibility = ItemVisibility.Always },
                new MenuCommand{Command = MenuCommands.Video, Enabled = enabledDrawing, Visibility = ItemVisibility.Always },
                new MenuCommand{Command = MenuCommands.DynamicText, Enabled = enabledDrawing, Visibility = ItemVisibility.Always },
                new MenuCommand{Command = MenuCommands.DynamicVideo, Enabled = enabledDrawing , Visibility= ItemVisibility.Never},
                new MenuCommand{Command = MenuCommands.Time, Enabled = enabledDrawing , Visibility = ItemVisibility.Always },
                new MenuCommand{Command = MenuCommands.Temperature, Enabled = enabledDrawing , Visibility = ItemVisibility.Always },
                });

            if (enabledDrawing)
            {
                SignInfo sign = Current.Sign;
                ControlService.UpdateFontCombo(sign);
                //切换时Message，取消所有shape的选择
                ShapeDraw s = Current.ShapeControl.Document.ShapeDraw;
                //s.BeginEdit();
                s.IsSelected = false;
                //s.EndEdit();
                foreach (ShapeBase shape in Current.ShapeControl.Document.SelectedShapes)
                {
                    //shape.BeginEdit();
                    shape.IsSelected = false;
                    //shape.EndEdit();
                }
            }
        }

        public override MessageControl Current
        {
            get
            {
                //if (MessageControl.Current == null)
                //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewMessage));
                return MessageControl.Current;
            }
            set
            {
                MessageControl.Current = value;
            }
        }
    }

    public class PlaylistTabControl : TabControlBase<PlaylistInfo, PlaylistControl, PlaylistCopyAction>
    {
        public override PlaylistControl Current
        {
            get
            {
                //if (PlaylistControl.Current == null)
                //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewPlaylist));
                return PlaylistControl.Current;
            }
            set
            {
                PlaylistControl.Current = value;
            }
        }

        protected override void PrepareMenuCommands()
        {
            base.PrepareMenuCommands();

            bool enabledDrawing = Current != null;
            MenuItemCommands.AddRange(new MenuCommand[]{
                new MenuCommand{Command = MenuCommands.Insert, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.InsertMessage, Enabled = enabledDrawing && LibraryGroup.Current.Messages.Count > 0},
                new MenuCommand{Command = MenuCommands.InsertTimeSlice, Enabled = enabledDrawing && LibraryGroup.Current.TimeSliceGroups.Count > 0 },
                new MenuCommand{Command = MenuCommands.InsertPlaylist, Enabled = LibraryGroup.Current.Playlists.Count > 0 },
                });
        }
    }

    public class ScheduleTabControl : TabControlBase<SchedulerInfo, ScheduleControl, SchedulerCopyAction>
    {
        public override ScheduleControl Current
        {
            get
            {
                //if (ScheduleControl.Current == null)
                //    LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.NewScheduler));
                return ScheduleControl.Current;
            }
            set
            {
                ScheduleControl.Current = value;
            }
        }

        protected override void PrepareMenuCommands()
        {
            base.PrepareMenuCommands();
            bool enabledDrawing = Current != null;
            MenuItemCommands.AddRange(new MenuCommand[]{
                new MenuCommand{Command = MenuCommands.Insert, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.InsertMessage, Enabled = enabledDrawing  && LibraryGroup.Current.Messages.Count > 0},
                new MenuCommand{Command = MenuCommands.InsertTimeSlice, Enabled = enabledDrawing  && LibraryGroup.Current.TimeSliceGroups.Count > 0 },
                new MenuCommand{Command = MenuCommands.InsertPlaylist, Enabled = enabledDrawing && LibraryGroup.Current.Playlists.Count > 0},
                });
        }
    }

    public class MLPlaylistTabControl : TabControlBase<MLPlaylistInfo, MLPlaylistControl, MLPlaylistCopyAction>
    {
        public override MLPlaylistControl Current
        {
            get
            {
                return MLPlaylistControl.Current;
            }
            set
            {
                MLPlaylistControl.Current = value;
            }
        }

        protected override void PrepareMenuCommands()
        {
            base.PrepareMenuCommands();
            bool enabledDrawing = Current != null;
            MenuItemCommands.AddRange(new MenuCommand[]{
                new MenuCommand{Command = MenuCommands.Insert, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.InsertMessage, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.InsertTimeSlice, Enabled = enabledDrawing },
                new MenuCommand{Command = MenuCommands.InsertPlaylist, Enabled = enabledDrawing },
                });
        }
    }
}
