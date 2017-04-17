//---------------------------------------------------------------------
//
// File: MainForm.cs
//
// Description:
// main form class
//
// Author: Kevin
//
// Modify history:
//      Kevin  2008-6-23 Resovle TLXPWDR-0073 problem and add comments
//      Louis 2008-6-24 Get images using resource key
//		Louis 2008-6-26 Add trayIcon to project
//      Jerry Xu 2008-12-25 Function:Initialize->Resolve modal dialog bug.
//      Jerry Xu 2009-3-20 Update method:RegisterMenuCommand()
//      Jerry Xu 2009-3-30 Update method:Initialize()
//      Jerry Xu 2009-3-31 Update method:AddSaveItem<TModel, TTabControl, TControlPanel, TCopyAction>(SaveAllDialog dialog, ModuleControl<TModel, TTabControl, TControlPanel, TCopyAction> module)
//      Jerry Xu 2009-4-2  Update method:private void AddSaveItem<TModel, TTabControl, TControlPanel, TCopyAction>(SaveAllDialog dialog, ModuleControl<TModel, TTabControl, TControlPanel, TCopyAction> module)
//      Jerry Xu 2009-4-16 Update method:Initialize()
//                         Update method:PageChangeSave(RibbonPageChangingEventArgs e)      
//      Jerry Xu 2009-5-7  Update method:WndProc(ref Message msg)    
//      Jerry Xu 2009-5-8  Update method:WndProc(ref Message msg) 
//      Jerry Xu 2009-5-12 Update method:WndProc(ref Message msg)
//      Jerry Xu 2009-6-19 Update method:WndProc(ref Message msg)
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DevExpress.Skins;
using DevExpress.XtraBars;
using DevExpress.XtraBars.Ribbon;
using DevExpress.XtraEditors.Repository;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.Resources;
using ProWrite.UI.Controls;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using ProWrite.UI.Controls.Playlist;
using ProWrite.UI.Controls.Settings;
using DevExpress.XtraEditors;
using DevExpress.Utils;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.UI.Controls.Modules;
using ProWrite.UI.Controls.CopyPaste;
using RepositoryItemFontEdit = ProWrite.UI.Controls.Editor.RepositoryItemFontEdit;
using System.Reflection;
using ProWrite.UI.Controls.Dashboard;
using System.Communication.Messaging;
using System.Communication;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using ProWrite.UFE;
using System.IO;
using DevExpress.UserSkins;
using DevExpress.LookAndFeel;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// main form class
    /// </summary>
    [MainForm]
    public partial class MainForm : RibbonForm, IMainForm
    {
        //dictionary of menu and command map 
        private Dictionary<MenuCommands, IBarItem> _menus;
        //dictionary of ribbonpage and module name 
        private Dictionary<string, RibbonPage> _pages;
        //module args
        private object[] _moduleArgs;
        private List<string> EmptyLibray = new List<string>();
        private Image _origDrawingImage = null;
        private UFERequestService _ufeReqService;
        //private EditorModuleNew editorModule;
        //private PlaylistModuleNew playlistModule;
        //private SchedulerModule schedulerModule;
        //private LiveModule liveModule;
        private MLPlaylistModule mlplaylistModule;
        private LineBarItem btnLineDash;
        private KeyBordHook keybordHook;
        public static bool IsCancelToNewSign = false;

        private NotifyIcon _trayIcon;
        private static readonly string mainWindowName = "Trans-Lux ProWrite";// + ProductInfo.Version;

        /// <summary>
        /// constructure function
        /// </summary>
        public MainForm()
        {
            //Register TabControl
            if (!DesignMode)
            {
                OfficeSkins.Register();
                const string skinName = "Office 2007 Silver";
                SkinManager.EnableFormSkins();
                LookAndFeelHelper.ForceDefaultLookAndFeelChanged();
                UserLookAndFeel.Default.SkinName = skinName;

                TopMost = true;
                Text = mainWindowName;
                ShowInTaskbar = true;

                Controls.Add(ModuleManager.Instance);

                this.InvokeMethod(() => InitializeComponent());
                //Initialize();

                _trayIcon = new NotifyIcon();
                _trayIcon.Icon = Resource.GetIcon(Resource.Icons.TrayIcon);
                _trayIcon.Text = ProductInfo.Name + " " + ProductInfo.Version;
                _trayIcon.Visible = true;
                _trayIcon.Click += delegate
                {
                    WindowState = FormWindowState.Maximized;
                    Visible = true;
                    Activate();
                };
            }
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            TopMost = false;
            RegistryKey registryKey;
            registryKey = Registry.CurrentUser.OpenSubKey("SOFTWARE\\ProWrite" /*+ ProductInfo.VersionCode.Replace(".","_")*/, true);
            var registerCode = registryKey.GetValue("StartTutorial", "").ToString().Trim();
            if (registerCode != null && registerCode == "1")
            {
                registryKey.SetValue("StartTutorial", "0");
                HelpManager.SetRibbonShowHelp(this, HelpNavigator.Topic, Resource.Helps.QuickStart);
            }

#if VERSION_2
            AuthenticateService auth = new ProWriteAuthenticateService();
            if (auth.IsShowLivePage())
                this.ribbonPageLive.Visible = true;
#endif
        }


        private void InitLineBarItem()
        {
            this.btnLineDash = new LineBarItem();
            this.btnLineDash.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLineDashCaption);
            this.btnLineDash.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLineDashdHint);
            this.btnLineDash.EditValue = System.Drawing.Drawing2D.DashStyle.Solid;
            this.btnLineDash.Name = "btnLineDash";

            this.ribbonControl1.Items.Add(btnLineDash);
            this.ribbonControl1.RepositoryItems.Add(btnLineDash.RepositoryItemImageComboBox);
            this.ribbonPageGroupEditorDrawing.ItemLinks.Add(this.btnLineDash);
        }


        /// <summary>
        /// System initialize
        /// </summary>
        public void Initialize()
        {
            FormHelper.ActiveForm = this;
            FutureContext.SynchronizationContext = SynchronizationContext.Current;
            FutureContext.SynchronizeObject = this;

            keybordHook = new KeyBordHook();
            keybordHook.OnKeyDownEvent += new KeyEventHandler(keybordHook_OnKeyDownEvent);

            _ufeReqService = new UFERequestService();
            _origDrawingImage = btnDrawing.Glyph;

            InitLineBarItem();

            btnTextFontName.Width = 100;
            barEditTextEffect.Width = 70;
            cmbSign.Width = 120;

            InitSkinStringList();
            try
            {
                InitTextEffect();

                InitTextLeadKern();
            }
            catch (Exception e)
            {
                DataGate.Log.Error(e.Message);
            }

            InitLineWidth();
            //Init ribbon bar items helppath
            InitItemsHelpPath();
            //System init
            btnSystemInit.ItemClick += delegate
                                        {
                                            if (MsgBox.Confirm("This will delete all settings and files in ProWrite and Libraries.Do you wish to continue?") == DialogResult.Yes)
                                            {
                                                DataGate.InitializeSystemData();

                                                MsgBox.Information("Delete success");
                                                Application.Restart();//.Exit();
                                            }
                                        };
            this.btnSystemDefault.ItemClick += btnSystemDefault_ItemClick;
            //this.btnUserManager.ItemClick += new ItemClickEventHandler(btnUserManager_ItemClick);
            //System exit
            btnExit.ItemClick += (s, e) => Close();
            btnHelp.ItemClick += (s, e) => HelpManager.SetRibbonShowHelp(this, HelpNavigator.Topic, Resource.Helps.QuickStart);
            btnFontColor.ColorChanged += (s, e) => OnPropertySet(s as IPropertySetBarItem);
            btnBackGroundColor.ColorChanged += (s, e) => OnPropertySet(s as IPropertySetBarItem);
            btnLinecolor.ColorChanged += (s, e) => OnPropertySet(s as IPropertySetBarItem);
            btnFill.ColorChanged += (s, e) => OnPropertySet(s as IPropertySetBarItem);
            btnLineDash.LineDashStyleChanged += (s, e) => OnPropertySet(s as IPropertySetBarItem);

            btnBold.DownChanged += (s, e) => OnFontStyleSet(s as IPropertySetBarItem);
            btnItalic.DownChanged += (s, e) => OnFontStyleSet(s as IPropertySetBarItem);

            btnTextFrameFixed.DownChanged += (s, e) =>
                                                 {
                                                     if (btnTextFontName.EditValue.ToString() == ControlService.ProWriteFontName)
                                                     {
                                                         int size = (int)btnTextFontSize.EditValue;
                                                         if (size == 5)
                                                         {
                                                             btnBold.Down = false;
                                                             btnBold.Enabled = false; //&& (!btnTextFrameFixed.Down);
                                                             btnItalic.Down = false;
                                                             btnItalic.Enabled = false; //&& (!btnTextFrameFixed.Down);
                                                         }
                                                         else if (size == 7)
                                                         {
                                                             //btnBold.Down = false;
                                                             btnBold.Enabled = true && (!btnTextFrameFixed.Down);
                                                             //btnItalic.Down = false;
                                                             btnItalic.Enabled = true && (!btnTextFrameFixed.Down);
                                                         }
                                                         else if (size == 12 || size == 16)
                                                         {
                                                             //btnBold.Down = true;
                                                             btnBold.Enabled = true && (!btnTextFrameFixed.Down);
                                                             btnItalic.Down = false;
                                                             btnItalic.Enabled = false; //&& (!btnTextFrameFixed.Down);
                                                         }
                                                     }
                                                     cmbTextFontSize.Enabled = !btnTextFrameFixed.Down;
                                                     btnTextFrameFixed.Glyph = btnTextFrameFixed.Down
                                                                 ? Resources.Resource.GetImage(Resources.Resource.Images.FrameFixedTrue16)
                                                                 : Resources.Resource.GetImage(Resources.Resource.Images.FrameFixed16);
                                                     OnTextFrameSet(s as IPropertySetBarItem, btnTextFrameFixed.Down);
                                                 };
            repositoryItemPopupContainerEdit3.QueryPopUp += (s, e) => popupContainerControl1.SelectedFont = btnTextFontName.EditValue as string;
            repositoryItemPopupContainerEdit3.QueryResultValue += (sender, e) =>
           {
               PopupContainerEdit item = sender as PopupContainerEdit;
               if (e.Value.ToString() != popupContainerControl1.SelectedFont)
               {
                   UndoService.BeginTransaction("change font");
                   e.Value = popupContainerControl1.SelectedFont;
                   btnTextFontName.EditValue = popupContainerControl1.SelectedFont;
                   btnTextFontSize.Enabled = false;
                   List<int> sizes = ControlService.GetFontSizes(popupContainerControl1.SelectedFont);
                   int oldfontSize = Convert.ToInt32(btnTextFontSize.EditValue);
                   int newfontSize = CommonHelper.FindMinWithDest(sizes, oldfontSize);
                   cmbTextFontSize.Items.Clear();
                   cmbTextFontSize.Items.AddRange(sizes);
                   btnTextFontSize.Enabled = true;
                   btnTextFontSize.EditValue = newfontSize;
                   btnTextFontSize.Enabled = !btnTextFrameFixed.Down;
                   LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextFont, PropertyName = btnTextFontName.TargetPropertyName, PropertyValue = popupContainerControl1.SelectedFont.ToString() });

                   UndoService.Commit();
               }
           };

            popupContainerControl1.FontSelectChanged += (s, e) =>
              {
                  if (String.IsNullOrEmpty(popupContainerControl1.SelectedFont)) return;

                  UndoService.BeginTransaction("change font");
                  //e.Value = popupContainerControl1.SelectedFont;
                  btnTextFontName.EditValue = popupContainerControl1.SelectedFont;
                  btnTextFontSize.Enabled = false;
                  List<int> sizes = ControlService.GetFontSizes(popupContainerControl1.SelectedFont);
                  int oldfontSize = Convert.ToInt32(btnTextFontSize.EditValue);
                  int newfontSize = CommonHelper.FindMinWithDest(sizes, oldfontSize);
                  cmbTextFontSize.Items.Clear();
                  cmbTextFontSize.Items.AddRange(sizes);
                  btnTextFontSize.Enabled = true;
                  btnTextFontSize.EditValue = newfontSize;
                  btnTextFontSize.Enabled = !btnTextFrameFixed.Down;

                  LocalMessageBus.Send(s, new PropertySetMessage { Command = MenuCommands.TextFont, PropertyName = btnTextFontName.TargetPropertyName, PropertyValue = popupContainerControl1.SelectedFont.ToString() });

                  UndoService.Commit();

              };

            btnTextFontName.EditValueChanged += (s, e) =>
                {
                    bool old = btnTextFontSize.Enabled;
                    btnTextFontSize.Enabled = false;
                    List<int> sizes = ControlService.GetFontSizes(btnTextFontName.EditValue.ToString());
                    cmbTextFontSize.Items.Clear();
                    cmbTextFontSize.Items.AddRange(sizes);
                    btnTextFontSize.Enabled = old;
                };

            btnAlignLeft.DownChanged += OnFontAlignSet;
            btnCenter.DownChanged += OnFontAlignSet;
            btnAlignRight.DownChanged += OnFontAlignSet;
            btnAlignLeft.DropDownEnabled = btnAlignRight.DropDownEnabled = btnCenter.DropDownEnabled = false;
            //selected page changing event on ribbon control
            ribbonControl1.SelectedPageChanged += (s, e) =>
                                                      {
                                                          ModuleControl mControl =
                                                              ModuleManager.CurrentModuleControl as ModuleControl;
                                                          if (mControl != null)
                                                          {
                                                              switch (mControl.ModuleName)
                                                              {
                                                                  case "Editor":
                                                                      this.btnNew.DropDownControl = this.newPopEditorMenu;
                                                                      break;
                                                                  case "Playlists":
                                                                      this.btnNew.DropDownControl = this.newPopPlaylistMenu;
                                                                      break;
                                                                  case "Scheduler":
                                                                      this.btnNew.DropDownControl = this.newPopSchedulerMenu;
                                                                      break;
                                                                  default:
                                                                      this.btnNew.DropDownControl = this.newPopDashboardMenu;
                                                                      break;
                                                              }
                                                          }
                                                      };

            ribbonControl1.SelectedPageChanging += delegate(object sender, RibbonPageChangingEventArgs e)
                                                    {
                                                        if (!SessionState.Instance.ContainsKey("SendToPlaylist")
                                                            && !SessionState.Instance.ContainsKey("SendToScheduler"))
                                                        {
                                                            if (!PageChangeSave(e))
                                                                return;
                                                        }

                                                        btnDelete.Enabled = false;
                                                        ModuleManager.LoadModule(e.Page.Name, _moduleArgs);

                                                        if (_moduleArgs != null)
                                                        {
                                                            Array.Clear(_moduleArgs, 0, _moduleArgs.Length);
                                                            _moduleArgs = null;
                                                        }

                                                        this.mnuView.ItemLinks.Clear();

                                                        ModuleControl moduleControl = ModuleManager.CurrentModuleControl as ModuleControl;
                                                        if (moduleControl != null
                                                            && moduleControl.DockMap != null
                                                            && moduleControl.DockMap.Count > 0)
                                                        {

                                                            foreach (Docks dock in moduleControl.DockMap.Keys)
                                                            {
                                                                BarStaticItem item = new BarStaticItem();
                                                                item.Caption = moduleControl.DockMap[dock];
                                                                item.Tag = dock;
                                                                item.ItemClick += (s, ea) => { moduleControl.ShowDockPanel((Docks)ea.Item.Tag); };
                                                                mnuView.ItemLinks.Add(item);
                                                            }

                                                            HelpManager.SetShowHelp(this, HelpNavigator.Topic, moduleControl.ModuleName);
                                                            //switch (moduleControl.ModuleName)
                                                            //{
                                                            //    case "Dashboard":
                                                            //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Dashboard);
                                                            //        break;
                                                            //    case "Editor":
                                                            //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Editor);
                                                            //        break;
                                                            //    case "Playlists":
                                                            //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Playlist);
                                                            //        break;
                                                            //    case "Scheduler":
                                                            //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Scheduler);
                                                            //        break;
                                                            //    default:
                                                            //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.QuickStart);
                                                            //        break;
                                                            //}
                                                            moduleControl.Focus();
                                                        }

                                                    };


            //respond menu event
            LocalMessageBus.Subject<MenuMessage>().Observers += (o, msg) => OmMenuMessage(msg);

            //respond menu command message
            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += (o, msg) => OnNewFilter(msg);
            LocalMessageBus.Subject<SelectedSignMessage>().Observers += new ObserverHandler<SelectedSignMessage>(MainForm_Observers);
            LocalMessageBus.Subject<IsSelectShapImage>().Observers += new ObserverHandler<IsSelectShapImage>(IsSelectShapImage);
            LocalMessageBus.Subject<SetPWLogo>().Observers += new ObserverHandler<SetPWLogo>(SetPWLogo);
            LocalMessageBus.Subject<SetBackGround>().Observers += new ObserverHandler<SetBackGround>(OnSetBackGround);
            LocalMessageBus.Subject<SetDefaultDrawingIcon>().Observers += new ObserverHandler<SetDefaultDrawingIcon>(MainForm_SetDefaultDrawIcon);
            //LocalMessageBus.Subject<ShapWidthHeightOutside>().Observers += new ObserverHandler<ShapWidthHeightOutside>(ShapOutside);

            //
            // register page
            //
            _pages = new Dictionary<string, RibbonPage>();
            RegisterPage(ModuleNames.Dashboard, ribbonPageDashBoard);
            RegisterPage(ModuleNames.Editor, ribbonPageEditor);
            RegisterPage(ModuleNames.Playlists, ribbonPagePlayLists);
            RegisterPage(ModuleNames.Scheduler, ribbonPageSchedule);
            //RegisterPage(ModuleNames.Manager, ribbonPageManager);
            RegisterPage(ModuleNames.Live, ribbonPageLive);
            //ribbonControl1.SelectedPage = _pages[ModuleNames.Scheduler];
            //ribbonControl1.SelectedPage = _pages[ModuleNames.Editor];
            //
            //Register Show module event
            //
            ModuleManager.ShowModule = OnShowModule;
            //
            //Register menu event 
            //
            RegisterMenuCommand();

            cmbSign.AutoHideEdit = false;
            cmbSign.Edit = ControlService.SignCombo;
            cmbSign.EditorShowMode = EditorShowMode.Default;
            ControlService.SignCombo.Editor = cmbSign;
            ControlService.SignImage.RefreshImage();
            ControlService.CurrentClip.RefreshClip();
            this.ribbonControl1.RepositoryItems.Add(cmbSign.Edit);


            cmbSession.AutoHideEdit = false;
            cmbSession.Edit = ControlService.SignCombo;
            cmbSession.EditorShowMode = EditorShowMode.Default;
            //ControlService.SignCombo.Editor = cmbSign;
            //ControlService.SignImage.RefreshImage();
            this.ribbonControl1.RepositoryItems.Add(cmbSession.Edit);

            ControlService.SignCombo.EditValueChanged += new EventHandler(OnSignSelectChanged);
            ControlService.FontCombo = cmbTextFontName;
            InitTextFont();
            if (ControlService.SignCombo.Current != null
                && ControlService.SignCombo.Current.DashboardType == DashboardType.Sign
                && !string.IsNullOrEmpty(ControlService.SignCombo.Current.Status))
                ResetPWLogo(ControlService.SignCombo.Current.Status);
            try
            {
                //string filePath = Config.GetAppSettingValueBytKey("ProFilePath");
                //if (string.IsNullOrEmpty(filePath))
                //    Config.AddOrUpdateAppSettings("ProFilePath", Constance.DataPath);
            }
            catch
            { }

            //
            //Register modules
            //
            //switch load modules at beginning by Louis
            //playlistModule = new PlaylistModuleNew();
            //editorModule = new EditorModuleNew();
            //schedulerModule = new SchedulerModule();

            //try
            //{
            //    ModuleManager.Register(new DashboardModule());
            //    ModuleManager.Register(editorModule);
            //    ModuleManager.Register(playlistModule);
            //    ModuleManager.Register(schedulerModule);

            //    ribbonControl1.SelectedPage = _pages[ModuleNames.Scheduler];
            //    ribbonControl1.SelectedPage = _pages[ModuleNames.Dashboard];
            //}
            //catch (Exception e)
            //{
            //    DataGate.Log.Error("Initia Error: " + e.Message);
            //}


            LocalMessageBus.Subject<EntityChangedMessage<MessageInfo>>().Observers += (s, e) => OnLibraryChanged(e.Action, e.Entities);
            LocalMessageBus.Subject<EntityChangedMessage<PlaylistInfo>>().Observers += (s, e) => OnLibraryChanged(e.Action, e.Entities);
            LocalMessageBus.Subject<EntityChangedMessage<SchedulerInfo>>().Observers += (s, e) => OnLibraryChanged(e.Action, e.Entities);
        }

        void IsSelectShapImage(object sender, IsSelectShapImage msg)
        {
            if (msg.BIsSelectShapImage)
            {
                btnEditPicture.Visibility = BarItemVisibility.Always;
                this.ribbonPageGroupEditorPicture.Visible = true;
            }
            else
            {
                btnEditPicture.Visibility = BarItemVisibility.Never;
                this.ribbonPageGroupEditorPicture.Visible = false;
            }
        }

        void SetPWLogo(object sender, SetPWLogo msg)
        {
            ResetPWLogo(msg.LogoColor);
        }

        /// <summary>
        /// Set PWLogo
        /// </summary>
        /// <param name="msg"></param>
        private void ResetPWLogo(string msg)
        {
            Bitmap bmp = (System.Drawing.Bitmap)Resource.GetImage(Resource.Images.PWLogoR);
            Icon icon = Resource.GetIcon(Resource.Icons.PW_LogoR16icon);
            if (msg.ToLower() == "yellow")
            {
                bmp = (System.Drawing.Bitmap)Resource.GetImage(Resource.Images.PWLogoY);
                icon = Resource.GetIcon(Resource.Icons.PW_LogoY16icon);
            }
            else if (msg.ToLower() == "green")
            {
                bmp = (System.Drawing.Bitmap)Resource.GetImage(Resource.Images.PWLogoG);
                icon = Resource.GetIcon(Resource.Icons.PW_LogoG16icon);
            }

            this.ribbonControl1.ApplicationIcon = bmp;

            _trayIcon.Icon = icon;
        }

        private bool PageChangeSave(RibbonPageChangingEventArgs e)
        {
            IsCancelToNewSign = false;

            ModuleControl mControl = ModuleManager.CurrentModuleControl as ModuleControl;
            if (mControl != null
                /*&& mControl.ModuleName != "Dashboard"*/)
            {
                SaveAllDialog dlg = new SaveAllDialog();
                //if (mControl.ModuleName == "Editor")
                //{
                //    AddSaveItem
                //        <MessageInfo, MessageTabControl, MessageControl,
                //            ShapeCopyAction>(dlg, editorModule);
                //}
                //if (mControl.ModuleName == "Playlists")
                //{
                //    AddSaveItem
                //        <PlaylistInfo, PlaylistTabControl, PlaylistControl,
                //            PlaylistCopyAction>(dlg, playlistModule);
                //}
                //if (mControl.ModuleName == "Scheduler")
                //{
                //    AddSaveItem
                //        <SchedulerInfo, ScheduleTabControl, ScheduleControl,
                //            SchedulerCopyAction>(dlg, schedulerModule);
                //}
                mControl.AddSaveItem(dlg, EmptyLibray);
                if (dlg.Count > 0)
                {
                    dlg.ShowModalDialog();
                    if (dlg.SaveResult == _Result.Cancel)
                    {
                        IsCancelToNewSign = true;
                        e.Cancel = true;
                        return false;
                    }
                    else if (dlg.SaveResult == _Result.No)
                    {
                        List<SaveItemInfo> items = dlg.Items;
                        foreach (SaveItemInfo item in items)
                        {
                            item.Controller.ClosePage(item.PageName);
                        }
                        if (EmptyLibray.Count > 0)
                        {
                            EmptyLibray.Clear();
                        }
                    }
                    else
                    {
                        List<SaveItemInfo> items = dlg.Items;
                        foreach (SaveItemInfo item in items)
                        {
                            switch (item.SaveResult)
                            {
                                case _Result.Save:
                                    item.Controller.Save(item.Tag);
                                    item.Controller.ClosePage(item.PageName);
                                    break;
                                case _Result.No:
                                    item.Controller.ClosePage(item.PageName);
                                    break;
                                case _Result.Cancel:
                                    e.Cancel = true;
                                    break;
                            }
                        }

                    }

                }
                if (EmptyLibray.Count > 0)
                {
                    foreach (string item in EmptyLibray)
                    {
                        MsgBox.Information(item + " is empty,was not saved");
                    }
                    EmptyLibray.Clear();
                }
            }
            return true;
        }

        protected override void WndProc(ref Message msg)
        {
            if (msg.Msg == API.WM_COPYDATA)
            {
                Type mytype = typeof(API.COPYDATASTRUCT);
                API.COPYDATASTRUCT mystr = (API.COPYDATASTRUCT)msg.GetLParam(mytype);
                if (!string.IsNullOrEmpty(mystr.lpData))
                {
                    //MessageBox.Show("1");
                    var argInfo = Shell.ArgInfo.Parse(mystr.lpData);
                    if (argInfo != null && !string.IsNullOrEmpty(argInfo.ModuleName))
                    {

                        SessionState.Instance["ImportOpen"] = true;
                        this.WindowState = FormWindowState.Maximized;

                        MemoryLibraryItem item = argInfo.Importer.OnImportOpen(mystr.lpData);
                        if (!string.IsNullOrEmpty(ModuleManager.CurrentModuleName) && ModuleManager.CurrentModuleName != argInfo.ModuleName)
                            ModuleManager.DisplayModule(argInfo.ModuleName, item);
                        else
                            ModuleManager.LoadModule(argInfo.ModuleName, new object[] { item });
                    }


                }

            }
            base.WndProc(ref msg);
        }

        public void DisplayItem(MemoryLibraryItem memory)
        {
            btnDelete.Enabled = false;
            //btnCopy.Enabled = false;
            //load module by module name
            string moduleName = ModuleNames.Editor;
            if (memory.Type == LibraryType.Message)
                moduleName = ModuleNames.Editor;
            if (memory.Type == LibraryType.Playlist)
                moduleName = ModuleNames.Playlists;

            //ModuleManager.DisplayModule(moduleName);
            ModuleManager.LoadModule(moduleName, new object[] { memory });
            _moduleArgs = new object[] { memory };

            if (_moduleArgs != null)
            {
                Array.Clear(_moduleArgs, 0, _moduleArgs.Length);
                _moduleArgs = null;
            }

            this.mnuView.ItemLinks.Clear();

            ModuleControl moduleControl = ModuleManager.CurrentModuleControl as ModuleControl;
            if (moduleControl != null
                && moduleControl.DockMap != null
                && moduleControl.DockMap.Count > 0)
            {

                foreach (Docks dock in moduleControl.DockMap.Keys)
                {
                    BarStaticItem item = new BarStaticItem();
                    item.Caption = moduleControl.DockMap[dock];
                    item.Tag = dock;
                    item.ItemClick += (s, ea) => { moduleControl.ShowDockPanel((Docks)ea.Item.Tag); };
                    mnuView.ItemLinks.Add(item);
                }

                //switch (moduleControl.ModuleName)
                //{
                //    case "Dashboard":
                //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Dashboard);
                //        break;
                //    case "Editor":
                //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Editor);
                //        break;
                //    case "Playlists":
                //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Playlist);
                //        break;
                //    case "Scheduler":
                //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.Scheduler);
                //        break;
                //    default:
                //        HelpManager.SetShowHelp(this, HelpNavigator.Topic, Resource.Helps.QuickStart);
                //        break;
                //}
                HelpManager.SetShowHelp(this, HelpNavigator.Topic, moduleControl.ModuleName);
                moduleControl.Focus();

                switch (memory.Type)
                {
                    case LibraryType.Message:
                        LocalMessageBus.Send(memory, new PWMessage<MenuCommands>(MenuCommands.OpenMessage));
                        break;
                    case LibraryType.Playlist:
                        LocalMessageBus.Send(memory, new PWMessage<MenuCommands>(MenuCommands.OpenPlaylist));
                        break;
                    case LibraryType.Schedule:
                        LocalMessageBus.Send(memory, new PWMessage<MenuCommands>(MenuCommands.OpenScheduler));
                        break;
                    default:
                        return;
                }
                ControlService.CancelPoistions();
                ControlService.LibraryTree.Controller.OnOpenLibraryItem(memory as LibraryItem);
                ControlService.RestorePoistions();
            }
        }

        private void OnLibraryChanged(EntityAction action, params MemoryLibraryItem[] items)
        {
            //TODO:Refresh Recent library menu item

        }

        private void InitItemsHelpPath()
        {
            this.btnNew.HelpPath = Resource.Helps.DashboardNew;
            this.btnDashBoardTools.HelpPath = Resource.Helps.DashboardSetup;
            this.cmbSign.HelpPath = Resource.Helps.CurrentSign;
            this.btnDisplay.HelpPath = Resource.Helps.DashboardDisplay;
            this.btnConnect.HelpPath = Resource.Helps.DashboardConnect;
            this.btnLiveView.HelpPath = Resource.Helps.DashboardLiveView;

            this.ribbonPageGroupDashBoardSystem.HelpPath = Resource.Helps.DashboardSign;
            //this.ribbonPageGroupManagerSystem.HelpPath = Resource.Helps.DashboardInit;
            this.ribbonPageGroup20.HelpPath = Resource.Helps.DashboardSystemDefault;

            ribbonPageGroupEditorSystem.HelpPath = Resource.Helps.EditorSign;
            ribbonPageGroup5.HelpPath = Resource.Helps.EditorFiles;
            ribbonPageGroup6.HelpPath = Resource.Helps.EditorContent;
            ribbonPageGroupEditorDrawing.HelpPath = Resource.Helps.EditorPaint;
            ribbonPageGroup1.HelpPath = Resource.Helps.EditorTextFont;
            ribbonPageGroup3.HelpPath = Resource.Helps.EditorWindows;

            ribbonPageGroupPlaylistSystem.HelpPath = Resource.Helps.PlaylistsSign;
            ribbonPageGroupPlaylistCopy.HelpPath = Resource.Helps.PlaylistsFiles;
            ribbonPageGroupPlaylistSend.HelpPath = Resource.Helps.PlaylistsContent;
            ribbonPageGroup4.HelpPath = Resource.Helps.PlaylistsProperties;

            ribbonPageGroupSchedulerSystem.HelpPath = Resource.Helps.SchedulerSign;
            ribbonPageGroupSchedulerCopy.HelpPath = Resource.Helps.SchedulerFiles;
            ribbonPageGroup7.HelpPath = Resource.Helps.SchedulerContent;
            ribbonPageGroup19.HelpPath = Resource.Helps.SchedulerProperties;

            ribbonPageDashBoard.HelpPath = Resource.Helps.Dashboard;
            ribbonPageEditor.HelpPath = Resource.Helps.Editor;
            ribbonPagePlayLists.HelpPath = Resource.Helps.Playlist;
            ribbonPageSchedule.HelpPath = Resource.Helps.Scheduler;
        }

        private void InitTextFont()
        {
            InitFontBySign();
        }

        void OnSetBackGround(object sender, SetBackGround msg)
        {
            msg.YesOrNo = true;
            if (MsgBox.Confirm("Background already exists. Would you like selected item to change to current background?", MessageBoxButtons.YesNo) == DialogResult.No)
                msg.YesOrNo = false;
        }

        private void InitFontName()
        {
            cmbTextFontName.Items.Clear();
            cmbTextFontName.Items.AddRange(ControlService.FontList);
            cmbTextFontName.SelectedValueChanged += delegate(object sender, EventArgs e)
            {
                ComboBoxEdit item = sender as ComboBoxEdit;
                if (item != null)
                {
                    PWFont font = item.EditValue as PWFont;
                    if (font != null)
                    {
                        cmbTextFontSize.Items.Clear();
                        cmbTextFontSize.Items.AddRange(font.Size);
                        //cmbTextFontSize.NullText = font.Size[0].ToString();
                    }
                    LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextFont, PropertyName = btnTextFontName.TargetPropertyName, PropertyValue = item.EditValue.ToString() });
                }
            };
        }

        private void InitBitMapFontName()
        {
            cmbTextFontName.Items.Clear();
            cmbTextFontName.Items.AddRange(ControlService.BitMapFontList);
            //cmbTextFontName.EditValueChanged += delegate(object sender, EventArgs e)
            cmbTextFontName.SelectedValueChanged += delegate(object sender, EventArgs e)
            {
                ComboBoxEdit item = sender as ComboBoxEdit;
                if (item != null)
                {
                    PWFont font = item.EditValue as PWFont;
                    if (font != null)
                    {
                        cmbTextFontSize.Items.Clear();
                        cmbTextFontSize.Items.AddRange(ControlService.GetFontSizes(font.Name));
                        cmbTextFontSize.NullText = font.Size[0].ToString();
                    }
                    LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextFont, PropertyName = btnTextFontName.TargetPropertyName, PropertyValue = item.EditValue.ToString() });
                }
            };
        }

        private void InitFontSize()
        {
            btnTextFontSize.EditValueChanged += (s, e) =>
            {
                BarEditItemEx item = s as BarEditItemEx;
                if (item != null && btnTextFontName.EditValue != null)
                {
                    bool isProwriteFont = btnTextFontName.EditValue.ToString() == ControlService.ProWriteFontName;

                    int value = (int)btnTextFontSize.EditValue;

                    if (isProwriteFont)
                    {
                        btnBold.Enabled = (!btnTextFrameFixed.Down) && ControlService.CanPWFontBold((int)btnTextFontSize.EditValue);
                        btnItalic.Enabled = (!btnTextFrameFixed.Down) && ControlService.CanPWFontItalic((int)btnTextFontSize.EditValue);
                    }
                    else
                    {
                        btnBold.Enabled = true;
                        btnItalic.Enabled = true;

                    }

                    LocalMessageBus.Send(item, new PropertySetMessage
                    {
                        Command = MenuCommands.TextFontSize,
                        PropertyName = btnTextFontSize.TargetPropertyName,
                        PropertyValue = value
                    });
                }
            };
        }

        void keybordHook_OnKeyDownEvent(object sender, KeyEventArgs e)
        {
            //if (sender is RibbonControl)
            {
                if (e.KeyCode == Keys.F1 && e.KeyValue == (int)Keys.F1)
                {
                    var p = ribbonControl1.PointToClient(Control.MousePosition);
                    HitTest(p);
                }
            }
        }

        private void HitTest(Point p)
        {
            var info = ribbonControl1.CalcHitInfo(p);
            if (info != null && !info.IsEmpty)
            {
                if (info.InItem)
                {
                    var linkItem = info.Item as BarItemLink;
                    if (linkItem == null)
                        return;

                    var item = linkItem.Item as IBarItem;
                    if (item != null && !string.IsNullOrEmpty(item.HelpPath))
                        ribbonControl1.SetRibbonShowHelp(HelpNavigator.Topic, item.HelpPath);
                }
                else if (info.InPageGroup)
                {
                    PageGroupEx pageGroup = info.PageGroup as PageGroupEx;

                    if (pageGroup != null && !string.IsNullOrEmpty(pageGroup.HelpPath))
                        ribbonControl1.SetRibbonShowHelp(HelpNavigator.Topic, pageGroup.HelpPath);
                }
                else if (info.InPage)
                {
                    RibbonPageEx page = info.Page as RibbonPageEx;
                    if (page != null && !string.IsNullOrEmpty(page.HelpPath))
                        ribbonControl1.SetRibbonShowHelp(HelpNavigator.Topic, page.HelpPath);
                }

            }
        }

        private void InitTextEffect()
        {
            repositoryItemTextEffectEdit.TextEffectChanged += (s, e) => //.TextEffectChanged 
                                                                  {
                                                                      TextEffectEdit item = s as TextEffectEdit;
                                                                      if (item != null)
                                                                      {
                                                                          LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextEffect, PropertyName = barEditTextEffect.TargetPropertyName, PropertyValue = item.EditValue });
                                                                      }
                                                                  };
        }

        private void InitLineWidth()
        {
            InnerLineWidthSpinEdit.EditValueChanged += (s, e) =>
            {
                SpinEdit item = s as SpinEdit;
                if (item != null)
                {
                    int value;
                    int.TryParse(item.EditValue.ToString(), out value);
                    LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.LineThickness, PropertyName = barLineWidth.TargetPropertyName, PropertyValue = value });
                }
            };

            btnLineDash.EditValueChanged += (s, e) => { OnPropertySet(s as IPropertySetBarItem); };
        }

        private void InitTextLeadKern()
        {
            repositoryItemKernEdit.EditValueChanged += (s, e) =>
            {
                SpinEdit item = s as SpinEdit;
                if (item != null)
                {
                    int value;
                    int.TryParse(item.EditValue.ToString(), out value);
                    LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextKern, PropertyName = btnTextKern.TargetPropertyName, PropertyValue = value });
                }
            };
            repositoryItemLeadEdit.EditValueChanged += (s, e) =>
            {
                SpinEdit item = s as SpinEdit;
                if (item != null)
                {
                    int value;
                    int.TryParse(item.EditValue.ToString(), out value);
                    LocalMessageBus.Send(item, new PropertySetMessage { Command = MenuCommands.TextLead, PropertyName = btnTextLead.TargetPropertyName, PropertyValue = value });
                }
            };
        }

        void MainForm_Observers(object sender, SelectedSignMessage msg)
        {
            if (sender != this && msg.CurrentSign != null)
            {
                //InitFontBySign();
                try
                {
                    if (msg.CurrentSign.Active)
                    {
                        ControlService.SignCombo.SelectedItem = msg.CurrentSign;

                    }
                    else
                    {
                        //ControlService.SignCombo.
                        cmbSign.EditValue = "";
                    }
                }
                catch
                {
                    //TODO: Write to logfile
                }
            }
        }

        void OnSignSelectChanged(object sender, EventArgs e)
        {
            DashboardItem item = (sender as LookUpEdit).EditValue as DashboardItem;
            if (item != null && item.DashboardType == DashboardType.Sign && item.Active)
            {
                //cmbSign.EditValue = (sender as LookUpEdit).EditValue;
                LocalMessageBus.Send(this, new SelectedSignMessage((sender as LookUpEdit).EditValue as SignInfo));
                SignInfo sign = item as SignInfo;
                //InitFontBySign();
                bool state = sign.Controller.Connection != null
                && sign.Controller.Connection.State == ConnectionState.Opened;
                bool online = sign.Controller.Connection.User.Status == ProWrite.UFE.UserStatus.Online;
                if (!state)
                {
                    this.btnConnect.Caption = "Connect";
                    this.btnConnect.Command = MenuCommands.Connect;
                    this.btnConnect.Enabled = sign.DashboardType == DashboardType.Sign;
                    this.btnUserManager.Enabled = false;
                }
                else
                {
                    if (online)
                    {
                        this.btnConnect.Caption = "DisConnect";
                        this.btnConnect.Command = MenuCommands.DisConnect;
                        this.btnConnect.Enabled = true;
                        this.btnUserManager.Enabled = true;
                    }
                    else
                    {
                        this.btnConnect.Caption = "Connect";
                        this.btnConnect.Command = MenuCommands.Connect;
                        this.btnConnect.Enabled = sign.DashboardType == DashboardType.Sign;
                        this.btnUserManager.Enabled = false;
                    }
                }
            }
            else if (item != null
                && item.DashboardType == DashboardType.DemoSign
                && item.Active)
            {
                //cmbSign.EditValue = (sender as LookUpEdit).EditValue;
                LocalMessageBus.Send(this, new SelectedSignMessage((sender as LookUpEdit).EditValue as SignInfo));
            }
            else
                cmbSign.EditValue = "";
        }

        private void InitFontBySign()
        {
            if (ControlService.SignCombo.Current != null && ControlService.SignCombo.Current.Template.Message.TextLayer.BitmapFontOnly)
                InitBitMapFontName();
            else
                InitFontName();
            InitFontSize();
        }

        void btnSystemDefault_ItemClick(object sender, ItemClickEventArgs e)
        {
            SettingDialog.Display(null, this);
        }

        private void OmMenuMessage(MenuMessage msg)
        {
            if (msg.Commands != null && msg.Commands.Length > 0)
            {
                bool isUndoRedo = false;
                foreach (MenuCommand item in msg.Commands)
                {
                    if (_menus != null && _menus.ContainsKey(item.Command))
                    {
                        IBarItem barItem = _menus[item.Command];
                        if (item.Command == MenuCommands.DisConnect)
                            btnConnect.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLogoffHint);
                        if (item.Command == MenuCommands.TextFontColor)
                            ribbonPageGroup1.Visible = item.Enabled.Value;
                        if (item.Command == MenuCommands.Connect)
                            btnConnect.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLoginHint);
                        if (item.Command == MenuCommands.BlankSign)
                        {
                            btnBlankSignSet.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Stop);
                            btnBlankSignSet.Caption = "Stop";
                        }
                        if (item.Command == MenuCommands.LiveImage
                            && item.Enabled.HasValue)
                            ControlService.CurrentClip.IsEnable = item.Enabled.Value;

                        if (item.Command == MenuCommands.UnBlankSign)
                        {
                            btnUnBlankSignSet.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.PlaySign);
                            btnUnBlankSignSet.Caption = "Play";
                        }
                        if (item.Enabled.HasValue
                            && item.Enabled.Value != barItem.Enabled)
                            barItem.Enabled = item.Enabled.Value;

                        if (item.Visibility.HasValue
                            && ((int)item.Visibility.Value) != ((int)barItem.Visibility))
                            barItem.Visibility = (BarItemVisibility)item.Visibility.Value;

                        if (!string.IsNullOrEmpty(item.Caption)
                            && item.Caption != barItem.Caption)
                            barItem.Caption = item.Caption;

                        if (barItem.Command != item.Command)
                            barItem.Command = item.Command;

                        if (!string.IsNullOrEmpty(item.PropertyName))
                            barItem.SetProperty(item.PropertyName, item.PropertyValue);

                        barItem.Command = item.Command;
                        if (item.Command == MenuCommands.Undo
                            || item.Command == MenuCommands.Redo)
                        {
                            isUndoRedo = true;
                        }
                    }

                }

                if (isUndoRedo)
                {
                    PopulateUndoRedoListMenu();
                }
            }
            btnConnect.Down = false;
            btnLiveView.Down = false;
            btnBlankSignSet.Down = false;
            btnUnBlankSignSet.Down = false;
        }

        [Conditional("DEBUG")]
        private void PopulateUndoRedoListMenu()
        {
            mnuUndoActionList.ItemLinks.Clear();
            mnuRedoActionList.ItemLinks.Clear();

            UndoManager undoMgr = UndoService.Current;
            if (undoMgr == null)
                return;

            if (undoMgr.UndoStackCount > 0)
            {
                IEnumerator<string> it = undoMgr.GetUndoEnumerator();
                while (it.MoveNext())
                {
                    BarStaticItem bar = new BarStaticItem();
                    bar.Caption = it.Current;
                    mnuUndoActionList.ItemLinks.Add(bar);
                }
            }

            if (undoMgr != null && undoMgr.RedoStackCount > 0)
            {
                IEnumerator<string> it = undoMgr.GetRedoEnumerator();
                while (it.MoveNext())
                {
                    BarStaticItem bar = new BarStaticItem();
                    bar.Caption = it.Current;
                    mnuRedoActionList.ItemLinks.Add(bar);
                }
            }
        }

        /// <summary>
        /// Register ribbon page
        /// </summary>
        /// <param name="moduleName">module name</param>
        /// <param name="page">page</param>
        private void RegisterPage(string moduleName, RibbonPage page)
        {
            page.Name = moduleName;
            _pages.Add(moduleName, page);
        }

        /// <summary>
        /// Show module event by module name
        /// </summary>
        /// <param name="moduleName"></param>
        /// <param name="args"></param>
        private void OnShowModule(string moduleName, params object[] args)
        {
            try
            {
                _moduleArgs = null;
                _moduleArgs = args;
                if (moduleName == ModuleNames.Live.ToString())
                    ribbonPageLive.Visible = true;
                ribbonControl1.SelectedPage = _pages[moduleName];
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(ex.Message, ex);
                MsgBox.Error(ex.Message);
            }
        }

        private void RegisterPropertySetCommand(IPropertySetBarItem item, MenuCommands command, string sourcePropertyName, string targetProperyName, bool enabled)
        {
            item.Command = command;
            item.Enabled = enabled;
            item.SourcePropertyName = sourcePropertyName;
            item.TargetPropertyName = targetProperyName;
            item.ItemClick += OnPropertySetItemClick;
            _menus.Add(command, item);

        }

        private void RegisterPropertySetCommandNoClickEvent(IPropertySetBarItem item, MenuCommands command, string sourcePropertyName, string targetProperyName, bool enabled)
        {
            RegisterPropertySetCommandNoClickEvent(item, command, sourcePropertyName, targetProperyName, enabled, null);
        }

        private void RegisterPropertySetCommandNoClickEvent(IPropertySetBarItem item, MenuCommands command, string sourcePropertyName, string targetProperyName, bool enabled, object tag)
        {
            item.Command = command;
            item.Enabled = enabled;
            item.SourcePropertyName = sourcePropertyName;
            item.TargetPropertyName = targetProperyName;
            item.Tag = tag;
            _menus.Add(command, item);
        }

        /// <summary>
        /// Register commond
        /// </summary>
        /// <param name="item">menu item</param>
        /// <param name="command">command</param>
        private void RegisterCommand(IBarItem item, MenuCommands command)
        {
            RegisterCommand(item, command, true);
        }

        private void RegisterCommand(IBarItem item, MenuCommands command, bool enabled)
        {
            item.Command = command;
            item.Tag = command;
            item.Enabled = enabled;
            item.Visibility = BarItemVisibility.Always;
            item.ItemClick += OnMenuItemClick;
            _menus.Add(command, item);
        }

        private void RegisterCommand(IBarItem item, MenuCommands command, bool enabled, BarItemVisibility visibility)
        {
            item.Command = command;
            item.Tag = command;
            item.Enabled = enabled;
            item.Visibility = visibility;
            item.ItemClick += OnMenuItemClick;
            _menus.Add(command, item);
        }

        /// <summary>
        /// Register menu and command map relation
        /// </summary>
        private void RegisterMenuCommand()
        {
            _menus = new Dictionary<MenuCommands, IBarItem>();

            RegisterCommand(btnCopy, MenuCommands.Copy, false);
            RegisterCommand(btnPaste, MenuCommands.Paste, false);
            RegisterCommand(btnUndo, MenuCommands.Undo, false);
            RegisterCommand(btnRedo, MenuCommands.Redo, false);
            RegisterCommand(btnDelete, MenuCommands.Delete, false);
            RegisterCommand(btnSave, MenuCommands.Save, false);
            RegisterCommand(btnSaveAs, MenuCommands.SaveAs, false);
            RegisterCommand(btnProperties, MenuCommands.Properties);
            RegisterCommand(btnNew, MenuCommands.New);
            //btnNew.HelpPath = Resource.Helps.DashboardModify;
            //HelpManager.Instance.RegisterHelp(ribbonControl1, HelpNavigator.Topic, Resource.GetHelpString(Resource.Helps.DashboardNew));
            RegisterCommand(btnOpen, MenuCommands.Open);
            RegisterCommand(btnOpenLibrary, MenuCommands.OpenLibrary);
            RegisterCommand(btnOpenFile, MenuCommands.OpenLibraryFile);
            RegisterCommand(btnNewLibrary, MenuCommands.NewLibraryGroup);
            RegisterCommand(btnNewTimeSliceGroup, MenuCommands.NewTimesliceGroup);

            RegisterCommand(btnDrawing, MenuCommands.Drawing, false);

            RegisterCommand(btnInsert, MenuCommands.Insert, false);
            RegisterCommand(btnInsertText, MenuCommands.Text, false);
            RegisterCommand(btnInsertImage, MenuCommands.Image, false);
            RegisterCommand(btnInsertVideo, MenuCommands.Video, false);
            RegisterCommand(btnInsertVariableText, MenuCommands.DynamicText, false);
            RegisterCommand(btnInsertTime, MenuCommands.Time, false);
            RegisterCommand(btnInsertTemperature, MenuCommands.Temperature, false);
            RegisterCommand(btnInsertVariableVideo, MenuCommands.DynamicVideo, false);
            RegisterCommand(btnInsertMessage, MenuCommands.InsertMessage, false, BarItemVisibility.Never);
            RegisterCommand(btnInsertTimeSliceGrp, MenuCommands.InsertTimeSlice, false, BarItemVisibility.Never);
            RegisterCommand(btnInsertPlayList, MenuCommands.InsertPlaylist, false, BarItemVisibility.Never);


            btnSendInEditor.Command = MenuCommands.SendToInEditor;
            btnSendInPlaylist.Command = MenuCommands.SendToInPlaylist;
            btnSendInScheduler.Command = MenuCommands.SendToInScheduler;
            RegisterCommand(btnSendLive, MenuCommands.SendToLiveStorage, false);
            RegisterCommand(btnSendSign, MenuCommands.SendToSign, false);
            RegisterCommand(btnSendPlaylist, MenuCommands.SendToPlaylist, false);
            RegisterCommand(btnSendSchedule, MenuCommands.SendToScheduler, false);
            RegisterCommand(btnSendMessagetoSign, MenuCommands.SendMessageOrPlaylistToSign, false);
            //_menus[MenuCommands.SendMessageOrPlaylistToSign] = btnSendPlayListtoSign;
            RegisterCommand(btnSendPlayListtoSign, MenuCommands.SendPlayListToSign, false);

            //
            //Dashboard
            //
            RegisterCommand(btnDashbaordNewSign, MenuCommands.NewSign);
            RegisterCommand(btnGoLive, MenuCommands.GoLive, false);

            RegisterCommand(btnDashboardNewSignGroup, MenuCommands.NewSignGroup);
            RegisterCommand(btnDashboardEdit, MenuCommands.DashboardEdit);

            //added by louis for full version
            RegisterCommand(btnConnect, MenuCommands.Connect, true);
            _menus[MenuCommands.DisConnect] = btnConnect;
            _menus[MenuCommands.CancelConnect] = btnConnect;

            RegisterCommand(btnUserManager, MenuCommands.UserManager, false);

            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardStatusReport);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardChangePWD);

            RegisterCommand(this.btnDimming, MenuCommands.Dimming, false);
            RegisterCommand(this.btnTempOffset, MenuCommands.TempOffset, false);
            RegisterCommand(this.btnReboot, MenuCommands.RebootCXC, false);
            RegisterCommand(this.btnTimeZone, MenuCommands.TimeZone, false);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardLogView);

            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardRebootCXC);
            RegisterCommand(this.btnSetTime, MenuCommands.ResetTime, false);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardFactoryReset);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardSkipMessage);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardClearQMessage);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardStopStartRender);

            //RegisterCommand(this.btnBlankSign, MenuCommands.BlankSign, false);
            //_menus[MenuCommands.UnBlankSign] = btnBlankSign;

            RegisterCommand(this.btnBlankSignSet, MenuCommands.BlankSign, false);
            //_menus[MenuCommands.UnBlankSign] = btnBlankSignSet;
            RegisterCommand(this.btnUnBlankSignSet, MenuCommands.UnBlankSign, false);

            //RegisterCommand(this.btnTestPattern, MenuCommands.TestPattern, false);
            RegisterCommand(this.btnLiveView, MenuCommands.LiveImage, false);
            //RegisterCommand(btnDashboardEdit, MenuCommands.DashboardUpdateLiveView);  

            //RegisterCommand(btnTestPatternExitTest, MenuCommands.TestPattern);
            RegisterCommand(btnTestPatternHRamp, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternVRamp, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternCross, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternDiagonal, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternVertical, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternColorBar, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternColorGrid, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColorRed, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColorGreen, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColorBlue, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColorWhite, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColorAmber, MenuCommands.TestPattern);
            //RegisterCommand(btnTestPatternSolidColor, MenuCommands.TestPattern);
            //
            //Editor
            //
            RegisterCommand(btnEditorNewMessage, MenuCommands.NewMessage);
            RegisterCommand(btnBatchLoad, MenuCommands.BatchLoad);

            RegisterCommand(btnRectangle, MenuCommands.Rectangle);
            RegisterCommand(btnArrowUp, MenuCommands.ArrowUp);
            RegisterCommand(btnArrowLeft, MenuCommands.ArrowLeft);
            RegisterCommand(btnArrowDown, MenuCommands.ArrowDown);
            RegisterCommand(btnArrowRight, MenuCommands.ArrowRight);
            RegisterCommand(btnEllipse, MenuCommands.Ellipse);
            RegisterCommand(btnPointer, MenuCommands.Pointer);
            RegisterCommand(btnLine, MenuCommands.Line, false);

            RegisterPropertySetCommandNoClickEvent(btnLinecolor, MenuCommands.LineColor, "SelectedColor", "BorderColor", false);
            RegisterPropertySetCommandNoClickEvent(barLineWidth, MenuCommands.LineThickness, "EditValue", "BorderWidth", false);
            RegisterPropertySetCommandNoClickEvent(btnFill, MenuCommands.ColorFill, "SelectedColor", "FillColor", false);
            RegisterPropertySetCommandNoClickEvent(btnLineDash, MenuCommands.LineDash, "LineDashStyle", "LineDashStyle", false);

            RegisterPropertySetCommandNoClickEvent(btnFontSizeFixed, MenuCommands.TextFontSizeFixed, null, "FontSizeFixed", false);
            RegisterPropertySetCommandNoClickEvent(btnTextFrameFixed, MenuCommands.TextFrameFixed, null, "FrameSizeFixed", false);


            RegisterPropertySetCommandNoClickEvent(btnTextFontName, MenuCommands.TextFont, null, "Font.Name", false);
            RegisterPropertySetCommandNoClickEvent(btnTextFontSize, MenuCommands.TextFontSize, null, "Font.Size", false);
            RegisterPropertySetCommandNoClickEvent(btnTextKern, MenuCommands.TextKern, "EditValue", "KernAmount", false);
            RegisterPropertySetCommandNoClickEvent(btnTextLead, MenuCommands.TextLead, "EditValue", "LeadAmount", false);
            RegisterPropertySetCommandNoClickEvent(btnBold, MenuCommands.TextBold, null, "Font.Style", false, FontStyle.Bold);
            RegisterPropertySetCommandNoClickEvent(btnItalic, MenuCommands.TextItalic, null, "Font.Style", false, FontStyle.Italic);
            RegisterPropertySetCommandNoClickEvent(btnAlignLeft, MenuCommands.TextAlignLeft, null, "TextAlignment", false, Align.LEFT);
            RegisterPropertySetCommandNoClickEvent(btnAlignRight, MenuCommands.TextAlignRight, null, "TextAlignment", false, Align.RIGHT);
            RegisterPropertySetCommandNoClickEvent(btnCenter, MenuCommands.TextAlignCenter, null, "TextAlignment", false, Align.CENTER);
            RegisterPropertySetCommandNoClickEvent(btnFontColor, MenuCommands.TextFontColor, "SelectedColor", "ForeColor", false);
            RegisterPropertySetCommandNoClickEvent(btnBackGroundColor, MenuCommands.TextBackgroundColor, "SelectedColor", "BackColor", false);
            RegisterPropertySetCommandNoClickEvent(barEditTextEffect, MenuCommands.TextEffect, null, "TextEffect", false);

            RegisterCommand(btnZoomIn, MenuCommands.ZoomIn);
            RegisterCommand(btnZoomOut, MenuCommands.ZoomOut);

            //PlayList
            //
            RegisterCommand(btnPlayListNew, MenuCommands.NewPlaylist);
            //
            //Scheduler
            //
            RegisterCommand(btnNewSchedule, MenuCommands.NewScheduler);

            //Live
            RegisterCommand(btnSessionSetup, MenuCommands.SessionSetup);
            RegisterCommand(btnSync, MenuCommands.Sync, false);
        }

        //private void AddSaveItem<TModel, TTabControl, TControlPanel, TCopyAction>(SaveAllDialog dialog, ModuleControl<TModel, TTabControl, TControlPanel, TCopyAction> module)
        //    where TModel : MemoryLibraryItem, new()
        //    where TTabControl : TabControlBase<TModel, TControlPanel, TCopyAction>, new()
        //    where TControlPanel : ControlPanel<TModel, TControlPanel>, new()
        //    where TCopyAction : CopyAction<TModel, TControlPanel>, new()
        //{
        //    if (module.TabControl.TabPages.Count > 0)
        //    {
        //        bool isEdit = false;
        //        bool isSaved = false;

        //        foreach (TabControlBase<TModel, TControlPanel, TCopyAction>.TabPage item in module.TabControl.TabPages)
        //        {
        //            item.Panel.LoadModelInfo();
        //            isSaved = CommonHelper.LibraryIsSaved(item.Panel.Model);
        //            if (item.Panel.ChangedService.HasChanged)
        //            {
        //            if (!isSaved)
        //            {
        //                EmptyLibray.Add(item.Panel.Model.Name);
        //            }
        //            //else
        //            //{
        //                isEdit = LibraryGroup.Current.GetByName(item.Panel.Model.Name, item.Panel.Model.Type) != null;
        //                dialog.AddItem(module.TabControl, item.Text, isEdit, item.Panel.Model);
        //            //}
        //            }
        //        }
        //    }

        //}

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            base.OnClosing(e);

            SaveAllDialog dlg = new SaveAllDialog();

            var modules = ModuleManager.Items;
            foreach (var module in modules)
                module.AddSaveItem(dlg, EmptyLibray);

            //AddSaveItem<MessageInfo, MessageTabControl, MessageControl, ShapeCopyAction>(dlg, editorModule);
            //AddSaveItem<PlaylistInfo, PlaylistTabControl, PlaylistControl, PlaylistCopyAction>(dlg, playlistModule);
            //AddSaveItem<SchedulerInfo, ScheduleTabControl, ScheduleControl, SchedulerCopyAction>(dlg, schedulerModule);
            if (dlg.Count <= 0)
            {
                foreach (SignInfo item in DashboardItem.AllSigns)
                {
                    item.IsBlankSign = true;
                }
                return;
            }

            dlg.ShowModalDialog();
            if (dlg.SaveResult == _Result.Save)
            {
                List<SaveItemInfo> items = dlg.Items;
                foreach (SaveItemInfo item in items)
                {
                    switch (item.SaveResult)
                    {
                        case _Result.Save:
                            item.Controller.Save(item.Tag);
                            item.Controller.ClosePage(item.Name);
                            break;
                        case _Result.No:
                            item.Controller.ClosePage(item.Name);
                            break;
                        case _Result.Cancel:
                            e.Cancel = true;
                            break;
                    }
                }
            }
            else if (dlg.SaveResult == _Result.Cancel)
            {
                e.Cancel = true;
            }
            foreach (SignInfo item in DataGate.GroupTree.Signs)
            {
                item.IsBlankSign = true;
            }
        }

        protected override void OnClosed(EventArgs e)
        {
            this.Hide();
            try
            {
                string autoDeleteDays = Config.GetAppSettingValueBytKey("AutoDeleteFileDays");// ConfigurationManager.AppSettings["AutoDeleteFileDays"];

                string autoBackupDays = Config.GetAppSettingValueBytKey("AutoBackupFileDays");
                if (!string.IsNullOrEmpty(autoBackupDays))
                {
                    int i_autoBackupDays = Convert.ToInt32(autoBackupDays);
                    string path = Config.GetAppSettingValueBytKey("BackupFilePath");

                    if (!System.IO.Directory.Exists(path))
                    {
                        string dateTime = DateTime.Now.ToString("yyyy-MM-dd_HH-mm-ss");
                        Config.CopyDir(Constance.LibraryDir, path + "\\" + dateTime + ".bk\\Library");
                        Config.CopyDir(Constance.SignImageDir, path + "\\" + dateTime + ".bk\\Image");

                        File.Copy(Constance.BinaryDataFile, path + "\\" + dateTime + ".bk\\data.binary", true);
                        Config.CopyDir(Constance.LayoutDir, path + "\\" + dateTime + ".bk\\Layout");
                        Config.CopyDir(Constance.DataPath + "\\log", path + "\\" + dateTime + ".bk\\log");
                        Config.CopyDir(Constance.DataPath + "\\imagetemp", path + "\\" + dateTime + ".bk\\imagetemp");
                    }
                    else
                    {
                        string[] fileList = System.IO.Directory.GetFileSystemEntries(path);
                        TimeSpan timespan;
                        bool bBackup = false;
                        if (fileList != null && fileList.Length > 0)
                        {
                            DateTime time = new DateTime();
                            for (int i = 0; i < fileList.Length; i++)
                            {
                                if (time == new DateTime())
                                    time = Directory.GetCreationTime(fileList[i]);
                                else
                                {
                                    timespan = time - Directory.GetCreationTime(fileList[i]);
                                    if (timespan.Days < 0)
                                        time = Directory.GetCreationTime(fileList[i]);
                                }
                            }
                            timespan = DateTime.Now - time.AddDays(i_autoBackupDays);
                            if (timespan.Days > 0)
                                bBackup = true;
                            if (bBackup)
                            {
                                try
                                {
                                    string dateTime = DateTime.Now.ToString("yyyy-MM-dd_HH-mm-ss");
                                    Config.CopyDir(Constance.LibraryDir, path + "\\" + dateTime + ".bk\\Library");
                                    Config.CopyDir(Constance.SignImageDir, path + "\\" + dateTime + ".bk\\Image");
                                    File.Copy(Constance.BinaryDataFile, path + "\\" + dateTime + ".bk\\data.binary", true);
                                    Config.CopyDir(Constance.LayoutDir, path + "\\" + dateTime + ".bk\\Layout");
                                    Config.CopyDir(Constance.DataPath + "\\log", path + "\\" + dateTime + ".bk\\log");
                                    Config.CopyDir(Constance.DataPath + "\\imagetemp", path + "\\" + dateTime + ".bk\\imagetemp");
                                }
                                catch { }
                            }
                        }
                    }

                }
                if (!string.IsNullOrEmpty(autoDeleteDays))
                {
                    int i_autoBackupDays = Convert.ToInt32(autoDeleteDays);
                    string path = Config.GetAppSettingValueBytKey("BackupFilePath");
                    string[] fileList = System.IO.Directory.GetFileSystemEntries(path);
                    TimeSpan timespan;
                    if (fileList != null && fileList.Length > 0)
                    {
                        for (int i = 0; i < fileList.Length; i++)
                        {
                            timespan = DateTime.Now - Directory.GetCreationTime(fileList[i]).AddDays(i_autoBackupDays);
                            if ((timespan.Days > 0 || timespan.Hours > 0 || timespan.Minutes > 0 || timespan.Seconds > 0)
                                && fileList[i].Contains(".bk"))
                            {
                                Config.DeleteFolder(fileList[i]);
                            }
                        }
                    }
                }
            }
            catch { }

            if (_trayIcon != null)
            {
                _trayIcon.Visible = false;
                _trayIcon.Dispose();
            }
            keybordHook.Dispose();
            base.OnClosed(e);
        }

        void btnAbout_ItemClick(object sender, ItemClickEventArgs e)
        {
            About form = new About();
            form.ShowModalDialog();
        }

        void btnEditPicture_ItemClick(object sender, ItemClickEventArgs e)
        {
            LocalMessageBus.Send(this, new EditImage(null));
        }

        void btnProfaneWord_ItemClick(object sender, ItemClickEventArgs e)
        {
            CustomDirtyWordsDictionary form = new CustomDirtyWordsDictionary();
            form.ShowModalDialog();
        }

        void btnTestCommand_ItemClick(object sender, ItemClickEventArgs e)
        {
            TestCommand test = new TestCommand();
            test.ShowModalDialog();
        }

        /// <summary>
        /// init skin string
        /// </summary>
        private void InitSkinStringList()
        {
            //skinsBli.ListItemClick += OnSkinClick;
            //foreach (SkinContainer cnt in SkinManager.Default.Skins)
            //{
            //    skinsBli.Strings.Add(cnt.SkinName);
            //}
        }

        /// <summary>
        /// Skin click event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnSkinClick(object sender, ListItemClickEventArgs e)
        {
            BarListItem barListItem = sender as BarListItem;
            if (barListItem != null)
            {
                string skinName = barListItem.Strings[barListItem.ItemIndex];
                DevExpress.LookAndFeel.UserLookAndFeel.Default.SkinName = skinName;
            }
        }

        /// <summary>
        /// menu message
        /// </summary>
        /// <param name="msg">message</param>
        private void OnNewFilter(PWMessage<MenuCommands> msg)
        {
            // current module name
            string currentModule = ModuleManager.CurrentModuleName;

            //
            if (string.IsNullOrEmpty(currentModule))
                return;

            bool currentSignExists = ControlService.SignCombo.Current != null;
            //Resovle TLXPWDR-0073 problem
            switch (msg.Content)
            {
                case MenuCommands.NewSign:
                case MenuCommands.NewSignGroup:
                    if (currentModule != ModuleNames.Dashboard)
                        ribbonControl1.SelectedPage = ribbonPageDashBoard;
                    break;
                case MenuCommands.NewMessage:
                case MenuCommands.OpenMessage:
                    if (currentModule != ModuleNames.Editor)
                        ribbonControl1.SelectedPage = ribbonPageEditor;
                    break;
                case MenuCommands.NewLibraryGroup:
                    if (currentModule != ModuleNames.Editor)
                        ribbonControl1.SelectedPage = ribbonPageEditor;
                    break;
                case MenuCommands.NewPlaylist:
                case MenuCommands.NewTimesliceGroup:
                case MenuCommands.OpenPlaylist:
                    if (currentModule != ModuleNames.Playlists)
                        ribbonControl1.SelectedPage = ribbonPagePlayLists;
                    break;
                case MenuCommands.NewScheduler:
                case MenuCommands.OpenScheduler:
                    if (currentModule != ModuleNames.Scheduler)
                        ribbonControl1.SelectedPage = ribbonPageSchedule;
                    break;

            }
        }

        private void OnFontStyleSet(IPropertySetBarItem item)
        {
            if (item != null && !string.IsNullOrEmpty(item.TargetPropertyName))
            {
                if (btnTextFontName.EditValue == null)
                    return;
                FontStyle value = FontStyle.Regular;
                if (btnTextFontName.EditValue.ToString() == ControlService.ProWriteFontName)
                {
                    if (btnBold.Down && item.Command == MenuCommands.TextBold)
                    {
                        value = value | FontStyle.Bold;
                        if (btnItalic.Down)
                        {
                            btnItalic.Down = false;
                            value = value & FontStyle.Italic;
                        }
                    }

                    if (btnItalic.Down && item.Command == MenuCommands.TextItalic)
                    {
                        value = value | FontStyle.Italic;
                        if (btnBold.Down)
                        {
                            btnBold.Down = false;
                            value = value & FontStyle.Bold;
                        }
                    }
                }
                else
                {
                    if (btnBold.Down)
                        value = value | FontStyle.Bold;
                    if (btnItalic.Down)
                        value = value | FontStyle.Italic;
                }
                LocalMessageBus.Send(item, new PropertySetMessage { Command = item.Command, PropertyName = item.TargetPropertyName, PropertyValue = value });
            }
        }

        private void OnTextFrameSet(IPropertySetBarItem item, bool textFrameFixed)
        {
            if (item != null && !string.IsNullOrEmpty(item.TargetPropertyName))
            {
                LocalMessageBus.Send(item, new PropertySetMessage { Command = item.Command, PropertyName = item.TargetPropertyName, PropertyValue = btnTextFrameFixed.Down });

            }
            LocalMessageBus.Send(null,
                                 new MenuMessage(new MenuCommand[] { new MenuCommand(MenuCommands.TextFontSize, !textFrameFixed) }));
        }

        private void OnFontAlignSet(object sender, ItemClickEventArgs e)
        {
            BarButtonItemEx item = sender as BarButtonItemEx;
            if (item != null
                && !string.IsNullOrEmpty(item.TargetPropertyName)
                && item.Tag != null)
            {
                Align value = (Align)item.Tag;
                LocalMessageBus.Send(item, new PropertySetMessage { Command = item.Command, PropertyName = item.TargetPropertyName, PropertyValue = value });
            }
        }

        private void OnPropertySet(IPropertySetBarItem item)
        {
            if (item != null
                && !string.IsNullOrEmpty(item.SourcePropertyName)
                && !string.IsNullOrEmpty(item.TargetPropertyName))
            {
                PropertyInfo p = item.GetType().GetProperty(item.SourcePropertyName);
                if (p != null && p.CanRead)
                {
                    try
                    {
                        LocalMessageBus.Send(item, new PropertySetMessage { Command = item.Command, PropertyName = item.TargetPropertyName, PropertyValue = p.GetValue(item, null) });
                    }
                    catch (Exception ex)
                    {
                        DataGate.Log.Error(ex.Message, ex);
                    }
                }
            }
        }

        private void OnPropertySetItemClick(object sender, ItemClickEventArgs e)
        {
            OnPropertySet(e.Item as IPropertySetBarItem);
        }
        /// <summary>
        /// menu item click event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnMenuItemClick(object sender, ItemClickEventArgs e)
        {
            IBarItem item = e.Item as IBarItem;

            if (item != null)
            {
                PopulateGlyphofDrawing(item);
                //send menu click message
                try
                {
                    LocalMessageBus.Send(e.Item, new PWMessage<MenuCommands>(item.Command));
                }
                catch (Exception ex)
                {
                    DataGate.Log.Error(ex.Message, ex);
                    MsgBox.Error(ex.Message);
                }
            }
        }

        //seting the icon of drawing button.
        private void PopulateGlyphofDrawing(IBarItem item)
        {
            switch (item.Command)
            {
                case MenuCommands.Rectangle:
                case MenuCommands.Ellipse:
                case MenuCommands.ArrowDown:
                case MenuCommands.ArrowLeft:
                case MenuCommands.ArrowRight:
                case MenuCommands.ArrowUp:
                    btnDrawing.Glyph = (item as BarButtonItemEx).Glyph;
                    break;
                default:
                    btnDrawing.Glyph = _origDrawingImage;
                    break;
            }
        }

        private void MainForm_SetDefaultDrawIcon(object sender, SetDefaultDrawingIcon icon)
        {
            btnDrawing.Glyph = _origDrawingImage;
        }
    }
}
