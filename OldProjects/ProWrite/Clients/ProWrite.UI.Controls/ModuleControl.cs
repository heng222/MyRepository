//---------------------------------------------------------------------
//
// File: ModuleControl.cs
//
// Description:
//Module base Type
//
// Author: Kevin
// Modify histroy:
//      Jerry Xu 2008-9-8  Add method:IsExist
//      Jerry Xu 2009-2-13 Update method:ModuleShown(params object[] args)
//      Jerry Xu 2009-3-20 Update method:SendToPlaylist(),SendToScheduler()
//      Jerry Xu 2009-3-23 Update method:SendToPlaylist(),SendToScheduler()
//      Jerry Xu 2009-3-30 Update method:ModuleShown(params object[] args),DoModuleShown(object[] args),ModuleShown()
//      Jerry Xu 2009-4-1  Update method:SendToScheduler()
//      Jerry Xu 2009-4-2  Update method:OpenLibrary(LibraryItem item)
//                         Add method:ChangeLockOpenState(LibraryItem item)
//      Jerry Xu 2009-4-10 Update method:DoModuleShown(object[] args)
//      Jerry Xu 2009-4-15 Update method:DoModuleShown(object[] args)
//      Jerry Xu 2009-4-22 Update method:OpenLibrary(LibraryItem item)
//      Jerry Xu 2009-5-7  Update method:DoModuleShown(object[] args)
//      Jerry Xu 2009-5-8  Update method:Save(bool isSaveAs, bool isShowSuccessMSG)
//      Jerry Xu 2009-5-12 Update method:DoModuleShown(object[] args)
//      Jerry Xu 2009-6-25 Update method:AddSaveItem(ISaveAllController ctx, List<string> emptyLibrary)
//      Jerry Xu 2009-6-29 Update method:OpenLibrary(LibraryItem item)
//      Jerry Xu 2009-6-30 Update method:AddSaveItem(ISaveAllController ctx, List<string> emptyLibrary)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Linq;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.CopyPaste;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Library;
using DevExpress.XtraBars.Docking;
using DevExpress.XtraTab;
using CP = ProWrite.UI.Controls.CopyPaste.CopyAction;
using System.Collections;
using System.IO;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;
//using ProWrite.UI.Controls.UFE.Live1;
using ProWrite.UI.Controls.Modules;
using ProWrite.UI.Controls.Dashboard;
using ProWrite.UI.Controls.Actions.UFE;
using ProWrite.UI.Controls.Editor;
using ProWrite.Resources;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using DevExpress.XtraScheduler;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.UI.Controls.Playlist;
using DevExpress.LookAndFeel;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Module control base type
    /// </summary>
    public partial class ModuleControl : ControlBase, IPWModule
    {
        private Dictionary<DockPanel, Control> _containers;
        private Dictionary<MenuCommands, Action> _actions;

        public ModuleControl()
        {
            const string skinName = "Office 2007 Silver";
            UserLookAndFeel.Default.SkinName = skinName;

            InitializeComponent();
            _containers = new Dictionary<DockPanel, Control>();
            _actions = new Dictionary<MenuCommands, Action>();

            _actions[MenuCommands.New] = New;
            _actions[MenuCommands.Save] = delegate { Save(false, true); };
            _actions[MenuCommands.SaveAs] = delegate { Save(true, true); };
            _actions[MenuCommands.Delete] = Delete;
            _actions[MenuCommands.Properties] = ShowProperty;
            _actions[MenuCommands.Copy] = Copy;
            _actions[MenuCommands.Paste] = Paste;

            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += SubscribeMenuEvent;
        }

        protected Dictionary<MenuCommands, Action> Actions
        {
            get { return _actions; }
        }

        /// <summary>
        /// get copy uploadAction
        /// </summary>
        [Browsable(false)]
        public virtual ICopyAction CopyAction { get { return null; } }

        protected void RegisterDockPanel(DockPanel dockPanel, Control ctrl, Docks dock)
        {
            if (dockPanel == null || ctrl == null)
                return;

            if (!_containers.ContainsKey(dockPanel))
            {
                dockPanel.Tag = dock;
                if (DockMap != null && DockMap.ContainsKey(dock))
                    dockPanel.Text = DockMap[dock];
                ctrl.Dock = DockStyle.Fill;
                _containers[dockPanel] = ctrl;
            }
        }

        protected virtual DockManager DockManager { get { return null; } }

        public virtual Dictionary<Docks, string> DockMap { get { return null; } }

        public void ShowDockPanel(Docks dock)
        {
            DockManager dockMgr = DockManager;
            if (dockMgr == null || dockMgr.Panels.Count == 0)
                return;

            List<DockPanel> panels = new List<DockPanel>(dockMgr.Panels.Count);
            foreach (DockPanel panel in dockMgr.Panels)
                panels.Add(panel);

            foreach (var panel in panels)
            {
                if (panel.Tag != null
                    && panel.Tag is Docks
                    && ((Docks)panel.Tag) == dock)
                {
                    switch (panel.Visibility)
                    {
                        case DockVisibility.Visible:
                            if (panel.ParentPanel != null && panel.ParentPanel.ActiveChild != panel)
                                panel.ParentPanel.ActiveChild = panel;
                            else
                                panel.Visibility = DockVisibility.AutoHide;
                            break;
                        case DockVisibility.Hidden:
                        case DockVisibility.AutoHide:
                            panel.Visibility = DockVisibility.Visible;
                            if (panel.ParentPanel != null)
                                panel.ParentPanel.ActiveChild = panel;
                            break;

                    }
                    break;
                }
            }
        }

        #region IPWModule Members
        /// <summary>
        /// Initialize module information
        /// </summary>
        public virtual void InitModule(params object[] args)
        {
            InitModule();
        }

        protected virtual void InitModule()
        {
            if (DockManager != null)
                DockManager.DockingOptions.ShowCloseButton = false;

            LoadLayout();
        }


        private bool _isInitialized;
        public bool IsInitialized
        {
            get { return _isInitialized; }
            set { _isInitialized = value; }
        }


        public virtual void SaveLayout()
        {
            var layoutFile = Constance.LayoutDir + ModuleName + ".xml";
            if (DockManager != null)
                DockManager.SaveLayoutToXml(layoutFile);
        }

        public virtual void LoadLayout()
        {
            var layoutFile = Constance.LayoutDir + ModuleName + ".xml";
            dockLayout = IOHelper.ReadAllBytes(layoutFile);
        }

        public virtual void ModuleShowing(params object[] args)
        {
            ModuleShowing();
        }

        /// <summary>
        /// Show Module
        /// </summary>
        public virtual void ModuleShown(params object[] args)
        {
            ModuleShown();
        }

        private byte[] dockLayout;
        [Browsable(false)]
        public byte[] LayoutData { get { return dockLayout; } set { dockLayout = value; } }

        protected virtual void ModuleShowing()
        {
            foreach (var dockPanel in _containers.Keys)
            {
                dockPanel.ControlContainer.Controls.Add(_containers[dockPanel]);
            }

            DockManager dockMgr = DockManager;
            if (dockMgr == null
                || dockMgr.Panels.Count == 0
                || dockLayout == null)
                return;

            using (var stream = new MemoryStream(dockLayout))
            {
                dockMgr.RestoreLayoutFromStream(stream);
            }
        }

        protected virtual void ModuleShown()
        {

        }


        /// <summary>
        /// Hide Module
        /// </summary>
        public virtual void ModuleClosed(params object[] args)
        {
            ModuleClosed();
        }

        protected virtual void ModuleClosed()
        {
            DataGate.Log.Debug(this.GetType().Name + "Closed Start;");
            ControlService.PropertyGrid.SelectedObject = null;
            ControlService.NailImageBox.Image = null;
            //foreach (DockPanel dockPanel in _containers.Keys)
            //{
            //    dockPanel.ControlContainer.Controls.Clear();
            //}
            DataGate.Log.Debug("PropertyGrid select null;");

            DockManager dockMgr = DockManager;
            if (dockMgr == null || dockMgr.Panels.Count == 0)
                return;
            DataGate.Log.Debug("DockMgr save layout start;");
            using (MemoryStream stream = new MemoryStream())
            {
                dockMgr.SaveLayoutToStream(stream);
                dockLayout = stream.ToArray();
            }
            DataGate.Log.Debug("DockMgr save layout end;");

            List<DockPanel> panels = new List<DockPanel>(dockMgr.Panels.Count);
            foreach (DockPanel panel in dockMgr.Panels)
                panels.Add(panel);

            DataGate.Log.Debug("panel add end;");


            //foreach (DockPanel panel in panels)
            //{
            //    panel.Visibility = DockVisibility.Hidden;
            //}
            DataGate.Log.Debug(this.GetType().Name + "Closed End;");
        }

        public virtual void AddSaveItem(ISaveAllController ctx, List<string> emptyLibrary)
        {
        }
        /// <summary>
        /// Mudule Name
        /// </summary>
        public virtual string ModuleName
        {
            get { return null; }
        }

        private bool _isOnScreen;
        /// <summary>
        /// Show or not
        /// </summary>
        public bool IsOnScreen
        {
            get
            {
                return _isOnScreen;
            }
            set
            {
                _isOnScreen = value;
            }
        }

        /// <summary>
        /// Whether to run edgeless module in background
        /// </summary>
        public bool IsBackgroud
        {
            get
            {
                return false;
            }
        }

        /// <summary>
        /// Return the corresponding control of the module
        /// </summary>
        /// <returns></returns>
        public Control GetControl()
        {
            return this;
        }

        #endregion

        protected MenuCommands CurrentActionId { get; set; }

        private void SubscribeMenuEvent(object sender, PWMessage<MenuCommands> msg)
        {
            if (!IsActive)
                return;
            Update(msg.Content);
        }

        protected void Update(MenuCommands cmd)
        {
            CurrentActionId = cmd;

            Action action = null;
            _actions.TryGetValue(cmd, out action);
            if (action != null)
                action.Invoke();
        }

        protected virtual void New()
        {
        }

        protected virtual void Save(bool isSaveAs, bool isShowSuccessMSG)
        {
        }

        protected virtual void Delete()
        {
        }

        private void Copy()
        {
            var copyAction = CopyAction;
            if (copyAction != null)
                copyAction.Copy();
        }

        private void Paste()
        {
            var copyAction = CopyAction;
            if (copyAction != null)
                copyAction.Paste();
        }

        private void ShowProperty()
        {
            //WindowManager.Instance.ShowPanel(Docks.Properties);
            ShowDockPanel(Docks.Properties);
        }
        /// <summary>
        /// is active
        /// </summary>
        public bool IsActive
        {
            get { return ModuleManager.CurrentModuleName == ModuleName; }
        }
    }

    public interface ITabModuleControl : IPWModule
    {
        TabControlBase TabControl { get; }
    }

    public abstract partial class ModuleControl<TModel, TTabControl, TControlPanel, TCopyAction> : ModuleControl, ITabModuleControl
        where TModel : MemoryLibraryItem, new()
        where TTabControl : TabControlBase<TModel, TControlPanel, TCopyAction>, new()
        where TControlPanel : ControlPanel<TModel, TControlPanel>, new()
        where TCopyAction : CopyAction<TModel, TControlPanel>, new()
    {

        private TTabControl _tabControl;

        public ModuleControl()
        {

            _tabControl = new TTabControl();
            Controls.Add(_tabControl);

            Actions[MenuCommands.Open] = Open;
            Actions[MenuCommands.OpenLibrary] = Open;
            Actions[MenuCommands.OpenLibraryFile] = OpenLibraryFile;

            Actions[MenuCommands.Insert] = Insert;
            Actions[MenuCommands.InsertMessage] = InsertMessage;
            Actions[MenuCommands.InsertTimeSlice] = InsertTimeSliceGroup;
            Actions[MenuCommands.InsertPlaylist] = InsertPlaylist;

            //Actions[MenuCommands.SendToSign] = SendToSign;
            //Actions[MenuCommands.SendToPlaylist] = SendToPlaylist;
            //Actions[MenuCommands.SendToScheduler] = SendToScheduler;
            //Actions[MenuCommands.SendMessageToSign] = SendMessageToSign;
        }


        public override void AddSaveItem(ISaveAllController ctx, List<string> emptyLibrary)
        {
            if (TabControl.TabPages.Count > 0)
            {
                bool isEdit = false;
                bool isSaved = false;

                foreach (TabControlBase<TModel, TControlPanel, TCopyAction>.TabPage item in TabControl.TabPages)
                {
                    item.Panel.LoadModelInfo();
                    isSaved = CommonHelper.LibraryIsSaved(item.Panel.Model);
                    if (item.Panel.ChangedService.HasChanged)
                    {
                        if (!isSaved)
                        {
                            emptyLibrary.Add(item.Panel.Model.Name);
                        }
                        //else
                        //{
                        //isEdit = LibraryGroup.Current.GetByName(item.Panel.Model.Name, item.Panel.Model.Type) != null;

                        isEdit = !item.Panel.IsNew;
                        ctx.AddItem(TabControl, item.Text, isEdit, item.Panel.Model);
                        //}
                    }
                }
            }

        }


        private void Insert()
        {
            if (ModelType != LibraryType.Message)
                InsertLibrary(CurrentActionId, this.ModelType);
        }

        private void InsertMessage()
        {
            InsertLibrary(CurrentActionId, LibraryType.Message);
        }

        private void InsertPlaylist()
        {
            InsertLibrary(CurrentActionId, LibraryType.Playlist);
        }

        private void InsertTimeSliceGroup()
        {
            InsertLibrary(CurrentActionId, LibraryType.TimeSliceGroup);
        }

        protected void SendToSign()
        {
            if (TabControl.Current != null
                    && (TabControl.Current.Model as SchedulerInfo).Items.Length <= 0)
            {
                MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageIsEmpty, TabControl.Current.Model.Name));
                return;
            }
            if (ControlService.SignCombo.Current != TabControl.Current.Sign)
            {
                //MsgBox.Warning("Open schedule conflict with current sign!");
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignSignConflict));
                return;
            }
            if (TabControl.Current.Sign.Controller.Connection.State != System.Communication.ConnectionState.Opened
                || TabControl.Current.Sign.Controller.Connection.User.Status != UserStatus.Online)
            {
                //MsgBox.Warning("Please login first!");
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignLoginFirst));
                return;
            }
            if (TabControl.Current.Sign.Controller.Connection.User.Role == Role.Commands)
            {
                //MsgBox.Warning("You don't have upload permissions.");
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignNoPermission));
                return;
            }
            if (!EnabledSendTo)
            {
                DialogResult result = MsgBox.WarningConfirm(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageChanged, TabControl.Current.Model.Name), MessageBoxButtons.YesNo);
                if (result == DialogResult.No)
                {
                    return;
                }
                else if (result == DialogResult.Yes)
                {
                    Save(false, false);
                    if (EnabledSendTo)
                        TabControl.Current.SendToSign();
                    return;
                }

                //MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSaveFirst));
                //return;
            }
            TabControl.Current.SendToSign();

        }

        protected void SendMessageOrPlaylistToSign()
        {

            var currentModel = TabControl.Current.Model;
            var libraryItem = LibraryGroup.Current.GetByName(currentModel.Name, currentModel.Type);

            if (ControlService.SignCombo.Current.DashboardType != DashboardType.Sign)
            {
                MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.UpLoadMessageNotLiveSign,currentModel.Type.ToString().ToLower()));
                return;
            }
            if (ControlService.SignCombo.Current != TabControl.Current.Sign)
            {
                //MsgBox.Warning("Open schedule conflict with current sign!");
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignSignConflict));
                return;
            }

            if (TabControl.Current.Sign.Controller.Connection.State != System.Communication.ConnectionState.Opened
                || TabControl.Current.Sign.Controller.Connection.User.Status != UserStatus.Online)
            {
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignLoginFirst));
                return;
            }
            if (TabControl.Current.Sign.Controller.Connection.User.Role == Role.Commands)
            {
                //MsgBox.Warning("You don't have upload permissions.");
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSendToSignNoPermission));
                return;
            }

            DialogResult result = MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.UpLoadMessageConfirm), MessageBoxButtons.OKCancel);
            if (result == DialogResult.Cancel)
                return;
            if (EnabledSendTo)
            {
                //ModuleManager.DisplayModule(ModuleNames.Editor, libraryItem);
                SchedulerInfo schedulerInfo = new SchedulerInfo();
                schedulerInfo.Add(GetAppointmentByMessage(currentModel as MemoryLibraryItem));
                schedulerInfo.Name = currentModel.Name;
                Save(schedulerInfo as MemoryLibraryItem);
                UploadAction uplopdAction = new UploadAction(ControlService.SignCombo.Current, schedulerInfo);
                uplopdAction.IsSendMessageToSign = true;
                uplopdAction.ModelType = currentModel.Type.ToString().ToLower();
                uplopdAction.Perform();
                return;
            }
            else
            {
                int length = 0;
                if (currentModel.Type == LibraryType.Message)
                    length = (TabControl.Current as MessageControl).Layers.Length;
                else
                    length = (TabControl.Current as PlaylistControl).Model.Length;
                if (TabControl.Current != null
                    && length <= 0)
                {
                    //Message is no valid
                    //if (currentModel.Type == LibraryType.Message)
                        MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageIsEmpty, currentModel.Name));
                    //else
                    //    MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.playlist, currentModel.Name));
                    return;
                }
                DialogResult resultDialog = MsgBox.WarningConfirm(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageChanged, currentModel.Name), MessageBoxButtons.YesNoCancel);

                if (resultDialog == DialogResult.Cancel)
                {
                    return;
                }
                else if (resultDialog == DialogResult.No)
                {
                    return;
                }
                else if (resultDialog == DialogResult.Yes)
                {
                    Save(false, false);
                    SchedulerInfo schedulerInfo = new SchedulerInfo();
                    schedulerInfo.Add(GetAppointmentByMessage(currentModel as MemoryLibraryItem));

                    schedulerInfo.Name = currentModel.Name;
                    Save(schedulerInfo as MemoryLibraryItem);
                    UploadAction uplopdAction = new UploadAction(ControlService.SignCombo.Current, schedulerInfo);
                    uplopdAction.IsSendMessageToSign = true;
                    uplopdAction.ModelType = currentModel.Type.ToString().ToLower();
                    uplopdAction.Perform();
                    
                    return;
                }

                //MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSaveFirst));

            }
        }

        private void Save(MemoryLibraryItem item)
        {
            //if (TabPages.Count <= 0)
            //    return;
            //TControlPanel controlPanel = TabControl.Current;

            //bool isSaveAs = !LibraryGroup.Current.Contains(item);
            //try
            //{
            //    TabControl.OnBeforeSave(controlPanel, isSaveAs);
            //}
            //catch { }

            //controlPanel.LoadModelInfo();

            var entity = item.Copy();// innerCtrl.Model.Copy();
            entity.Name = item.Name;



            //TabControl.Save(innerCtrl, isSaveAs, false);
            if (CommonHelper.LibraryIsSaved(item))
            {
                if (LibraryGroup.Current.Contains(entity))
                {
                    ControlService.LibraryTree.Update(entity);
                }
                else
                    ControlService.LibraryTree.Add(entity);
                //controlPanel.HasSaved = true;
                //controlPanel.IsNew = false;
                //controlPanel.ChangedService.AcceptChanged();
                //UndoManager.Current.Clear();
            }
        }

        protected void SendToPlaylist()
        {
            if (TabControl.Current != null
                    && TabControl.Current as PlaylistControl != null)
                return;

            Session["SendToPlaylist"] = true;

            var currentModel = TabControl.Current.Model;
            var libraryItem = LibraryGroup.Current.GetByName(currentModel.Name, currentModel.Type);

            if (EnabledSendTo)
            {
                ModuleManager.DisplayModule(ModuleNames.Playlists, libraryItem);
                Session.Remove("SendToPlaylist");
            }
            else
            {
                if (TabControl.Current != null
                    && TabControl.Current as MessageControl != null && (TabControl.Current as MessageControl).Layers.Length <= 0)
                {
                    //Message is no valid
                    MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageIsEmpty, currentModel.Name));
                    Session.Remove("SendToPlaylist");
                    return;
                }
                DialogResult result = MsgBox.WarningConfirm(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageChanged, currentModel.Name), MessageBoxButtons.YesNoCancel);

                if (result == DialogResult.Cancel)
                {
                    Session.Remove("SendToPlaylist");
                    return;
                }
                else if (result == DialogResult.No)
                {
                    if (libraryItem == null)
                    {
                        //MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageIsEmpty, currentModel.Name));
                        Session.Remove("SendToPlaylist");
                        return;
                    }

                    ModuleManager.DisplayModule(ModuleNames.Playlists, libraryItem);
                    Session.Remove("SendToPlaylist");
                    return;
                }
                else if (result == DialogResult.Yes)
                {
                    Save(false, false);
                    var libraryItem1 = LibraryGroup.Current.GetByName(currentModel.Name, currentModel.Type);
                    if (EnabledSendTo && libraryItem1 != null)
                        ModuleManager.DisplayModule(ModuleNames.Playlists, libraryItem1);
                    Session.Remove("SendToPlaylist");
                    return;
                }

                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSaveFirst));
                Session.Remove("SendToPlaylist");
            }
        }

        private AppointmentInfo GetAppointmentByMessage(MemoryLibraryItem item)
        {
            //AppointmentInfo appInfo = new AppointmentInfo();

            if (item == null)
                return null;
            ILockLibraryItem locker = item as ILockLibraryItem;
            if (locker != null)
                locker.IsLock = true;

            //AppointmentBaseCollection appointments = new AppointmentBaseCollection();
            Appointment apt = new Appointment(AppointmentType.Pattern); // = schedulerStorage1.CreateAppointment(AppointmentType.Normal);
            apt.Subject = item.Name;
            //apt.Location = item.Name + item.Type.ToString();
            apt.LabelId = DataGate.FindColorIndex(item.Color);
            apt.StatusId = 0;
            apt.Description = item.Type.ToString();
            double length = Convert.ToDouble(item.Length) / 3600;

            //if (item.Type == LibraryType.Message)
            //{
            //    apt.Duration = TimeSpan.FromHours(length);
            //    apt.End = apt.Start.AddSeconds(item.Length);
            //}
            apt.Start = DateTime.Now;
            apt.End = DateTime.Now;//.ToShortDateString();
            apt.AllDay = true;


            apt.RecurrenceInfo.AllDay = true;// item.RecurrenceInfo.AllDay;
            apt.RecurrenceInfo.DayNumber = 1;
            apt.RecurrenceInfo.Start = apt.Start;
            //apt.RecurrenceInfo.Duration = apt.Duration;
            apt.RecurrenceInfo.End = apt.End;
            apt.RecurrenceInfo.Month = 1;
            apt.RecurrenceInfo.OccurrenceCount = 10;// item.RecurrenceInfo.OccurrenceCount;
            apt.RecurrenceInfo.Periodicity = 1;
            apt.RecurrenceInfo.Range = RecurrenceRange.NoEndDate;

            apt.RecurrenceInfo.Type = RecurrenceType.Daily;
            apt.RecurrenceInfo.WeekDays = WeekDays.EveryDay;
            apt.RecurrenceInfo.WeekOfMonth = WeekOfMonth.First;

            AppointmentConverter appConverter = new AppointmentConverter();
            return appConverter.Convert(apt);
        }

        protected void SendToScheduler()
        {
            if (TabControl.Current != null
                    && TabControl.Current as ScheduleControl != null)
                return;
            Session["SendToScheduler"] = true;
            var currentModel = TabControl.Current.Model;
            var libraryItem = LibraryGroup.Current.GetByName(currentModel.Name, currentModel.Type);
            if (EnabledSendTo)
                ModuleManager.DisplayModule(ModuleNames.Scheduler, libraryItem);
            else
            {
                if (currentModel.Type == LibraryType.Schedule)
                    return;
                if (TabControl.Current != null)
                {
                    int length = 0;
                    if (currentModel.Type == LibraryType.Message)
                    {
                        length = (TabControl.Current as MessageControl).Layers.Length;
                    }
                    else
                        length = (currentModel as PlaylistInfo).Items.Length;
                    if (length <= 0)
                    {
                        MsgBox.Error(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageIsEmpty, currentModel.Name));
                        return;
                    }
                }

                DialogResult result = MsgBox.WarningConfirm(Resources.Resource.GetFormatString(Resources.Resource.Strings.MessageChanged, currentModel.Name), MessageBoxButtons.YesNoCancel);

                if (result == DialogResult.Cancel)
                    return;
                else if (result == DialogResult.No)
                {

                    //ModuleManager.DisplayModule(ModuleNames.Scheduler);
                    if (libraryItem == null)
                    {
                        Session.Remove("SendToScheduler");
                        return;
                    }
                    ModuleManager.DisplayModule(ModuleNames.Scheduler, libraryItem);
                    Session.Remove("SendToScheduler");
                    return;

                }
                else if (result == DialogResult.Yes)
                {
                    Save(false, false);
                    if (EnabledSendTo)
                    {
                        libraryItem = LibraryGroup.Current.GetByName(currentModel.Name, currentModel.Type);
                        ModuleManager.DisplayModule(ModuleNames.Scheduler, libraryItem);
                    }
                    return;
                }
                MsgBox.Error(Resources.Resource.GetString(Resources.Resource.Strings.SendSaveFirst));
            }
        }

        public TTabControl TabControl { get { return _tabControl; } }

        TabControlBase ITabModuleControl.TabControl { get { return _tabControl; } }

        public override ICopyAction CopyAction
        {
            get
            {
                return TabControl.CopyAction;
            }
        }

        public abstract LibraryType ModelType { get; }

        public bool HasInLibrary
        {
            get
            {
                return TabControl.Current != null
                    && ControlService.LibraryTree.Controller.GetNode(TabControl.Current.Model) != null;
            }
        }

        public bool EnabledSendTo
        {
            get
            {
                return HasInLibrary && !TabControl.Current.ChangedService.HasChanged;
            }
        }
        /// <summary>
        /// init module
        /// </summary>
        protected override void InitModule()
        {
            base.InitModule();
            ControlService.LibraryTree.Controller.OpenLibraryItem += new EventHandler<OpenLibraryEventArgs>(OnOpenLibrayItem);
        }

        public override void ModuleShown(params object[] args)
        {
            if (args != null
                && args.Length > 0
                && args[0] != null)
            {
                DoModuleShown(args);
            }
            base.ModuleShown(args);

            if ((TabControl.Current == null || TabControl.Current.Model == null) && args == null)
            {
                if ((ModuleManager.CurrentModuleName == ModuleNames.Editor || ModuleManager.CurrentModuleName == ModuleNames.Scheduler
                    || ModuleManager.CurrentModuleName == ModuleNames.Playlists) && TabControl.TabPages.Count == 0)
                    New();
            }
        }

        private void DoModuleShown(object[] args)
        {
            MemoryLibraryItem item = args[0] as MemoryLibraryItem;
            if (item == null)
                return;

            if (TabControl.Current != null)
            {
                //if (TabControl.Current.Model.Type == LibraryType.Schedule
                //    && item.Type == LibraryType.Message)
                //{
                if (args.Length == 1&&TabControl.Current.Model.Type != LibraryType.Message)
                {
                    if (!SessionState.Instance.ContainsKey("ImportOpen"))
                    {
                        SendToConfirm result = new SendToConfirm(item.Type, ModelType);
                        result.ShowModalDialog();
                        if (result.DialogResult == 0)
                        {
                            TabControl.AddPage(item);
                            TabControl.Current.InsertLibrary(item);
                        }
                        else if (result.DialogResult == 1)
                        {
                            UndoService.Current = TabControl.Current.UndoManager;

                            TabControl.Current.InsertLibrary(item);
                        }
                        else
                        {
                            //ModuleManager.DisplayModule(LibraryType.Message.ToString());
                            Array.Clear(args, 0, args.Length);
                            args = null;
                            return;
                        }
                    }
                    else
                    {
                        Session["Import"] = true;
                        SessionState.Instance.Remove("ImportOpen");
                        OpenLibrary(item);
                    }
                }
                else
                {
                    //Import
                    Session["Import"] = true;
                    OpenLibrary(item);
                    //TabControl.AddPage(item);
                    //TabControl.Current.InsertLibrary(item);
                }
                //}
                //else
                //{
                //    UndoService.Current = TabControl.Current.UndoManager;
                //    //Send to exist
                //    TabControl.Current.InsertLibrary(item);
                //}
            }
            else
            {
                if (args.Length == 1)
                {
                    //if (ModelType == LibraryType.Schedule
                    //    &&item.Type == LibraryType.Message)
                    //{
                    if (!SessionState.Instance.ContainsKey("ImportOpen"))
                    {
                        SendToConfirm result = new SendToConfirm(item.Type, ModelType);
                        result.ShowModalDialog();
                        if (result.DialogResult == 0)
                        {
                            TabControl.AddPage(item);
                            TabControl.Current.InsertLibrary(item);
                        }
                        else if (result.DialogResult == 1)
                        {
                            Open();
                            TabControl.Current.InsertLibrary(item);
                        }
                        else
                        {
                            //ModuleManager.DisplayModule(LibraryType.Message.ToString());
                            SessionState.Instance.Remove("ImportOpen");
                            return;
                        }
                        //}
                        //else
                        //{
                        //    DialogResult result1 = MsgBox.Confirm("Whether you need to create a new " + ModelType.ToString() + "?", MessageBoxButtons.YesNo);
                        //    if (result1 == DialogResult.Yes)
                        //    {
                        //        //Send to new
                        //        TabControl.AddPage(item);
                        //        TabControl.Current.InsertLibrary(item);
                        //    }
                        //    else
                        //    {
                        //        Open();
                        //        TabControl.Current.InsertLibrary(item);
                        //    }
                        //}
                    }
                    else
                    {
                        //Import
                        Session["Import"] = true;
                        SessionState.Instance.Remove("ImportOpen");
                        OpenLibrary(item);
                        //TabControl.AddPage(item);
                        //TabControl.Current.InsertLibrary(item);
                    }
                }
                else
                {
                    //Import
                    Session["Import"] = true;
                    OpenLibrary(item);
                    //TabControl.AddPage(item);
                    //TabControl.Current.InsertLibrary(item);
                }
            }
            args = null;
        }

        protected override void ModuleShown()
        {
            base.ModuleShown();
            //WindowManager.Instance.ShowPanels(ModuleName);

            if (TabControl.Current != null)
            {
                ControlService.PropertyGrid.SelectedObject = TabControl.Current.Model;
                UndoService.Current = TabControl.Current.UndoManager;
                TabControl.CopyAction.ControlPanel = TabControl.Current;
                CP.Current = TabControl.CopyAction;
            }
            else
            {
                ControlService.PropertyGrid.SelectedObject
                    = UndoService.Current = null;
                CP.Current = null;
            }
        }

        private void Open()
        {
            using (LibraryDialog dlg = new LibraryDialog(ModelType))
            {
                DialogResult result = dlg.ShowModalDialog();
                if (result == DialogResult.OK)
                {
                    ControlService.CancelPoistions();
                    OpenLibrary(dlg.SelectedItems[0]);
                    ControlService.RestorePoistions();
                }
            }
        }

        private void OpenLibraryFile()
        {
            //LibraryType type = ModelType;
        }

        void OnOpenLibrayItem(object sender, OpenLibraryEventArgs e)
        {
            OpenLibrary(e.Item);
        }

        private void ChangeLockOpenState(LibraryItem item)
        {
            if (item == null)
                return;
            ILockLibraryItem locker = item as ILockLibraryItem;
            MemoryLibraryItem memory = item as MemoryLibraryItem;
            if (memory != null)
            {
                if (memory.IsOpen)
                {
                    ModuleControl mc = ModuleManager.CurrentModuleControl as ModuleControl;
                    if (mc != null)
                    {
                        var editor = mc as ProWrite.UI.Controls.Modules.EditorModuleNew;
                        if (editor != null)
                        {
                            editor.TabControl.ActivePageByModel(memory as MessageInfo);
                        }

                        var plsylist = mc as ProWrite.UI.Controls.Modules.PlaylistModuleNew;
                        if (plsylist != null)
                        {
                            plsylist.TabControl.ActivePageByModel(memory as PlaylistInfo);
                        }

                        var scheduler = mc as ProWrite.UI.Controls.Modules.SchedulerModule;
                        if (scheduler != null)
                        {
                            scheduler.TabControl.ActivePageByModel(memory as SchedulerInfo);
                        }
                    }
                    return;
                }
                else
                    memory.IsOpen = true;
                bool canOpen = CommonHelper.IsShowOpenDialog(memory.Type);
                LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                             new MenuCommand{ Command =  MenuCommands.Open,Enabled = canOpen}
                        }));
            }
            if (locker != null)
                locker.IsLock = true;
        }

        protected virtual void OpenLibrary(LibraryItem item)
        {
            if (item.Type == ModelType)
            {
                // && IsActive)
                //if(item.Type == LibraryType.Message)
                //    ModuleManager.DisplayModule(ModuleNames.Editor, item);
                //if(item.Type == LibraryType.Playlist)
                //    ModuleManager.DisplayModule(ModuleNames.Playlists, item);
                //if (item.Type == LibraryType.Schedule)
                //    ModuleManager.DisplayModule(ModuleNames.Scheduler, item);
                ChangeLockOpenState(item);
                TabControl.AddPage(item as TModel);
                if (!IsActive || TabControl.Current == null)
                    ModuleManager.DisplayModule(ModuleName);

            }
            else
            {
                if (item.Type == LibraryType.TimeSliceGroup)
                {
                    TabControl.AddPage(null);
                    if (!IsActive)
                        ModuleManager.DisplayModule(ModuleName);
                }
            }
        }

        private void InsertLibrary(MenuCommands cmd, LibraryType type)
        {
            if (TabControl != null && TabControl.Current != null)
            {
                using (LibraryDialog dlg = new LibraryDialog(cmd, type))
                {
                    DialogResult result = dlg.ShowModalDialog();
                    if (result == DialogResult.OK)
                    {
                        TabControl.Current.InsertLibrary(dlg.SelectedItems);
                    }
                }
            }
        }

        protected override void Save(bool isSaveAs, bool isShowSuccessMSG)
        {
            using (new WaitCursor())
            {
                TControlPanel ctrlPanel = TabControl.Current;
                if (ctrlPanel == null)
                    return;

                ctrlPanel.LoadModelInfo();
                if (ctrlPanel.Model.IsEmpty)
                {
                    MsgBox.Error(ProWrite.Resources.Resource.GetFormatString(ProWrite.Resources.Resource.Strings.SaveEmptyInfo, ctrlPanel.Model.Type.ToString(), ctrlPanel.Model.Name));
                    return;
                }

                TabControl.Save(ctrlPanel, isSaveAs, isShowSuccessMSG);
            }
        }

        protected override void New()
        {
            //ControlService.LibraryTree.
            TabControl.AddPage(null);
        }
    }
}
