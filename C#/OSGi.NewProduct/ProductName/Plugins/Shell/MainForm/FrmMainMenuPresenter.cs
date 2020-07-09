/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

using Acl.ServiceManagement;

using Platform.Presentation;
using Platform.Presentation.CommonControl;

using Products.Domain.Utility;
using Products.Infrastructure.Messages;
using Products.Presentation;
using Products.Resource;
using Products.Shell.Properties;

namespace Products.Shell.Presentation.MainForm
{
    partial class FrmMainMenuPresenter : Acl.CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// 顶级菜单（从左到右依次排列）。
        /// </summary>
        private MenuStrip _mainMenuStrip = new MenuStrip() { Dock = DockStyle.Top };
        private ToolStripMenuItem _menuView = new ToolStripMenuItem() { Text = "视图(&V)" }; // “视图”菜单
        private ToolStripMenuItem _menuTool = new ToolStripMenuItem() { Text = "工具(&T)" }; // “工具”菜单
        private ToolStripMenuItem _menuDebug = new ToolStripMenuItem() { Text = "调试(&D)" }; // “调试”菜单
        private ToolStripMenuItem _menuHelp = new ToolStripMenuItem() { Text = "帮助(&H)" }; // “帮助”菜单
        private ToolStripMenuItem _menuExitLeft = new ToolStripMenuItem() { Text = "退出(&X)" }; // 左“退出”菜单
        private ToolStripMenuItem _menuCompanyLogo = new ToolStripMenuItem() { Text = "CompanyLogo" }; // 右边“公司LOGO”菜单
        private ToolStripMenuItem _menuExitRight = new ToolStripMenuItem() { Text = "退出(&X)" }; // 右“退出”菜单

        /// <summary>
        /// 视图：显示标题栏
        /// </summary>
        private ToolStripMenuItem _menuShowTitleBar;
        #endregion


        #region "Constructor"
        public FrmMainMenuPresenter(FrmMain view)
        {
            this.View = view;

            this.View.Load += OnOwnerViewLoad;

            this.CreateMainMenu();
        }
        #endregion

        #region "Properties"
        public FrmMain View { get; private set; }

        public MenuStrip MenuBar { get { return _mainMenuStrip; } }
        #endregion

        #region "Private methods"

        private void CreateMainMenu()
        {
            #region "一级菜单：视图"
            _menuShowTitleBar = new ToolStripMenuItem() { Text = "显示标题栏", ShortcutKeys = Keys.Shift | Keys.Alt | Keys.F5 };
            _menuShowTitleBar.Click += OnMenuViewShowTitleBar;

            var menuShowMenuStrip = new ToolStripMenuItem() { Text = "显示/隐藏菜单栏", ShortcutKeys = Keys.Shift | Keys.Alt | Keys.F6 };
            _menuShowTitleBar.Text = this.View.InitalTitleVisible ? "隐藏标题栏" : "显示标题栏";
            menuShowMenuStrip.Click += OnMenuViewShowMenuStrip;

            var menuShowStatusbar = new ToolStripMenuItem() { Text = "隐藏状态栏", ShortcutKeys = Keys.Shift | Keys.Alt | Keys.F7 };
            menuShowStatusbar.Click += OnMenuViewShowStatusbar;

            var menuShowDocumentIcon = new ToolStripMenuItem() { Text = this.View.DockPanel.ShowDocumentIcon ? "隐藏标签图标" : "显示标签图标" };
            menuShowDocumentIcon.Click += OnMenuViewShowDocumentIcon;
#if !DEBUG
            _menuShowTitleBar.Visible = false;
            menuShowMenuStrip.Visible = false;
            menuShowStatusbar.Visible = false;
#endif

            var menuShowAllWindows = new ToolStripMenuItem() { Text = "显示所有窗口(&A)", Image = Resources.SwitchScreen.ToBitmap() };
            menuShowAllWindows.Click += OnMenuViewShowAllWindows;
            var menuLayout = new ToolStripMenuItem() { Text = "窗口布局" };
            var menuResetWindowsLayout = new ToolStripMenuItem() { Text = "重置窗口布局(&R)" };
            menuResetWindowsLayout.Click += OnMenuViewResetWindowsLayout;
            var menuLockLayout = new ToolStripMenuItem() { Text = "锁定窗口布局(&L)", Image = Resources.LockLayout };
            menuLockLayout.Click += OnMenuViewLockUnlockLayout;
            var menuImportLayout = new ToolStripMenuItem() { Text = "导入布局(&I)...", Image = Resources.Import };
            menuImportLayout.Click += OnMenuViewImportLayout;
            var menuExportLayout = new ToolStripMenuItem() { Text = "导出布局(&E)...", Image = Resources.Export };
            menuExportLayout.Click += OnMenuViewExportLayout;
            menuLayout.DropDownItems.AddRange(new ToolStripItem[] { menuResetWindowsLayout, menuLockLayout, new ToolStripSeparator(), menuImportLayout, menuExportLayout });

            var swithToScreenMenu = new ToolStripMenuItem() { Text = "切换窗口到(&S)" };
            var swithToAllScreen = new ToolStripMenuItem() { Text = "全屏显示", Image = Resources.FullScreen.ToBitmap() };
            swithToAllScreen.Click += OnMenuViewSwithcToAllScreen;
            swithToScreenMenu.DropDownItems.Add(swithToAllScreen);

            int num = 1;
            Screen.AllScreens.OrderBy(p => p.Bounds.Left).ToList().ForEach(p =>
            {
                var switchSubMenu = new ToolStripMenuItem() { Tag = p };
#if DEBUG
                switchSubMenu.Text = string.Format("屏幕{0}({1})", num++, p);
#else
                switchSubMenu.Text = string.Format("屏幕{0}({1})", num++, p.DeviceName);
#endif
                switchSubMenu.Click += OnMenuViewSwithToScreenX;
                swithToScreenMenu.DropDownItems.Add(switchSubMenu);
            });

            _menuView.DropDownItems.AddRange(new ToolStripItem[]
            {
                menuShowAllWindows,
                new ToolStripSeparator(), _menuShowTitleBar, menuShowMenuStrip, menuShowStatusbar, menuShowDocumentIcon,
                new ToolStripSeparator(), swithToScreenMenu,  menuLayout
            });
            #endregion

            #region "一级菜单：工具"
            var mnuToolOption = new ToolStripMenuItem() { Text = "选项(&O)...", Image = Resources.Options };
            mnuToolOption.Click += OnMenuToolOption;
            var mnuOpenExeFolder = new ToolStripMenuItem() { Text = "打开程序所在目录..." };
            mnuOpenExeFolder.Click += OnMenuToolOpenExeFolder;
            var mnuRolloverAllCommLog = new ToolStripMenuItem() { Text = "滚动所有日志文件..." };
            mnuRolloverAllCommLog.Click += OnMenuToolRolloverLog;
            var mnuScreenshot = new ToolStripMenuItem() { Text = "截屏...", ShortcutKeys = Keys.Alt | Keys.S };
            mnuScreenshot.Click += OnMenuToolScreenshot;
            var mnuRunCommand = new ToolStripMenuItem() { Text = "运行(&R)..." };
            mnuRunCommand.Click += OnMenuToolRunCommand;

            _menuTool.DropDownItems.AddRange(new ToolStripItem[] { mnuToolOption,
                new ToolStripSeparator(), mnuOpenExeFolder, mnuRolloverAllCommLog, mnuScreenshot, mnuRunCommand});
            #endregion

            //#region "一级菜单：调试"
            //var mnuOpenNDMDebugForm = new ToolStripMenuItem() { Text = "打开NDM调试窗口..." };
            //mnuOpenNDMDebugForm.Click += OnMenuDebugOpenNDMDebugForm;
            //var mnuOpenTMTDebugForm = new ToolStripMenuItem() { Text = "打开TMT调试窗口..." };
            //mnuOpenTMTDebugForm.Click += OnMenuDebugOpenTMTDebugForm;
            //var mnuOpenSDMDebugForm = new ToolStripMenuItem() { Text = "打开SDM调试窗口..." };
            //mnuOpenSDMDebugForm.Click += OnMenuDebugOpenSDMDebugForm;
            //var mnuOpenCommDebugForm = new ToolStripMenuItem() { Text = "打开内部通信调试窗口..." };
            //mnuOpenCommDebugForm.Click += OnMenuDebugOpenCommDebugForm;
            //var mnuSaveStationRangeTable = new ToolStripMenuItem() { Text = "打开车站范围管理窗口..." };
            //mnuSaveStationRangeTable.Click += OnMenuDebugSaveStationRangeTable;

            //_menuDebug.DropDownItems.AddRange(new ToolStripItem[] { mnuOpenNDMDebugForm, 
            //    mnuOpenTMTDebugForm, mnuOpenSDMDebugForm, mnuOpenCommDebugForm, mnuSaveStationRangeTable});
            _menuDebug.Visible = false;
            //#endregion

            #region "一级菜单：帮助"
            var menustripAbout = new ToolStripMenuItem() { Text = "关于本产品" };
            menustripAbout.Click += new EventHandler(OnMenuHelpAbout);
            var toolStripManual = new ToolStripMenuItem() { Text = "操作手册", ShortcutKeys = Keys.F1, Image = Resources.Help };
            toolStripManual.Click += new EventHandler(OnMenuHelpManual);
            _menuHelp.DropDownItems.AddRange(new ToolStripItem[] { menustripAbout, toolStripManual });
            #endregion

            #region "一级菜单：公司LOGO"
            _menuCompanyLogo.Alignment = ToolStripItemAlignment.Right;
            _menuCompanyLogo.DisplayStyle = ToolStripItemDisplayStyle.Image;
            _menuCompanyLogo.TextImageRelation = TextImageRelation.ImageBeforeText;
            _menuCompanyLogo.ImageScaling = ToolStripItemImageScaling.None;
            _menuCompanyLogo.Text = ProductResources.CompanyChsAbbrName;
            _menuCompanyLogo.Image = Resources.CompanyLogo;
            _menuCompanyLogo.Click += OnMenuCompanyLogoClick;
            #endregion

            #region "一级菜单：退出"
            _menuExitLeft.ShortcutKeys = Keys.Alt | Keys.F4;
            _menuExitLeft.Image = Resources.Exit;
            _menuExitLeft.Click += OnMenuExit;

            _menuExitRight.ShortcutKeys = Keys.Alt | Keys.F4;
            _menuExitRight.ToolTipText = string.Format("退出程序");
            _menuExitRight.Image = Resources.CloseForm;
            _menuExitRight.Click += OnMenuExit;
            _menuExitRight.DisplayStyle = ToolStripItemDisplayStyle.Image;
            _menuExitRight.Alignment = ToolStripItemAlignment.Right;
            _menuExitRight.Visible = !this.View.InitalTitleVisible;
            #endregion

            // 主菜单
            _mainMenuStrip.Items.AddRange(new ToolStripItem[] { _menuView, _menuTool, _menuDebug, _menuHelp, _menuExitRight, _menuCompanyLogo });
            this.View.Controls.Add(_mainMenuStrip);
            //_mainMenuStrip.BackColor = Color.DarkGray;
        }

        private void LoadPluginsMenu()
        {
            try
            {
                var topMenuProviders = ServiceManager.Current.GetAll<ITopMenuItemProvider>();

                // 获取相关的菜单项。
                var menusBeforeView = new List<ToolStripItem>();
                var menusBeforeOption = new List<ToolStripItem>();

                foreach (var provider in topMenuProviders)
                {
                    if (provider.Position == -1)
                    {
                        menusBeforeOption.AddRange(provider.GetTopMenu());
                    }
                    else
                    {
                        menusBeforeView.AddRange(provider.GetTopMenu());
                    }
                }

                // “视图”菜单之前的菜单。
                foreach (var item in menusBeforeView)
                {
                    var viewMenuPosition = _mainMenuStrip.Items.IndexOf(_menuView);
                    _mainMenuStrip.Items.Insert(viewMenuPosition, item);
                }

                // “选项”菜单之前的菜单。
                foreach (var item in menusBeforeOption)
                {
                    var optionMenuPosition = _mainMenuStrip.Items.IndexOf(_menuTool);
                    _mainMenuStrip.Items.Insert(optionMenuPosition, item);
                }

                // 将退出菜单添加第一个菜单的子项中。
                var firstMenuItem = (_mainMenuStrip.Items[0] as ToolStripMenuItem);
                firstMenuItem.DropDownItems.AddRange(new ToolStripItem[] { new ToolStripSeparator(), _menuExitLeft });
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex.ToString());
            }
        }

        private void CreateViewSubmenu()
        {
            var dockContents = this.View.DockContents;

            foreach (var item in dockContents)
            {
                // 创建菜单。
                var subMenuItem = new ToolStripMenuItem()
                {
                    Text = string.Format("显示{0}", item.Key.Title),
                    Tag = item.Key
                };

                if (item.Key.DefaultIcon != null)
                {
                    subMenuItem.Image = item.Key.DefaultIcon.ToBitmap();
                }

                subMenuItem.Click += OnMenuViewShowDockContentX;

                _menuView.DropDownItems.Insert(0, subMenuItem);
            }
        }

        private void UpdateViewSubMenu()
        {
            var dockContentMenuItems = _menuView.DropDownItems.OfType<ToolStripMenuItem>();
            var dockContents = this.View.DockContents;

            foreach (var item in dockContentMenuItems)
            {
                var partAttri = item.Tag as ProductPartAttribute;
                if (partAttri == null) continue;

                var controlType = dockContents.Where(p => p.Key.ControlType == partAttri.ControlType).
                    First().Key.ControlType;

#if DEBUG
                item.Enabled = this.View.CanShow(controlType);
#else
                item.Visible = this.View.CanShow(controlType);
#endif
            }
        }

        /// <summary>
        /// 切换标题栏的可见性。
        /// </summary>
        private void SwitchTitleBarVisible(bool exceptedVisible)
        {
            // 设置状态栏的SizingGrip。
            this.View.StatusBar.SizingGrip = exceptedVisible;

            // 设置右侧退出菜单的可见性。
            _menuExitRight.Visible = !exceptedVisible;

            if (exceptedVisible)
            {
                this.View.FormBorderStyle = FormBorderStyle.Sizable;
                //this.WindowState = FormWindowState.Maximized;
                _menuShowTitleBar.Text = "隐藏标题栏";

                this.View.Height = Screen.PrimaryScreen.WorkingArea.Height;
            }
            else
            {
                this.View.FormBorderStyle = FormBorderStyle.None;
                this.View.WindowState = FormWindowState.Normal;
                this.View.DesktopBounds = new Rectangle(0, 0, Screen.AllScreens.Sum(p => p.Bounds.Width), Screen.AllScreens.Min(p => p.Bounds.Height));
                _menuShowTitleBar.Text = "显示标题栏";
            }
        }

        private void OnUserChanged(object sender, EventArgs e)
        {
            try
            {
                // 更新视图菜单
                this.View.Invoke(new Action(() =>
                {
                    this.UpdateViewSubMenu();
                }));
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "public methods"
        public void Reset()
        {
            _menuExitRight.Visible = !this.View.InitalTitleVisible;  // 右侧退出菜单可见性。
            _mainMenuStrip.Visible = true; // 菜单栏可见。
        }
        #endregion

        #region "窗体事件"

        private void OnOwnerViewLoad(object sender, EventArgs e)
        {
            try
            {
                // 订阅用户切换事件。
                GlobalMessageBus.SubscribeUserChanged(OnUserChanged);

                // 加载插件菜单。
                LoadPluginsMenu();

                // 创建View子菜单。
                this.CreateViewSubmenu();

                // 更新View子菜单。
                this.UpdateViewSubMenu();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion


        #region "View菜单事件响应函数"
        private void OnMenuViewShowDockContentX(object sender, EventArgs e)
        {
            try
            {
                var menuItem = sender as ToolStripMenuItem;
                var partAttri = menuItem.Tag as ProductPartAttribute;

                this.View.ShowSpecifiedDockContent(partAttri.ControlType);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnMenuViewSwithToScreenX(object sender, EventArgs e)
        {
            try
            {
                var menuItem = sender as ToolStripMenuItem;
                var theScreen = menuItem.Tag as Screen;
                if (theScreen != null)
                {
                    this.View.DesktopBounds = theScreen.Bounds;
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnMenuViewSwithcToAllScreen(object sender, EventArgs e)
        {
            try
            {
                this.View.DesktopBounds = new Rectangle(0, 0,
                    Screen.AllScreens.Sum(p => p.Bounds.Width),
                    Screen.PrimaryScreen.Bounds.Height);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnMenuViewShowTitleBar(object sender, EventArgs e)
        {
            try
            {
                var exceptedVisible = !this.View.CurrentTitleVisible;

                SwitchTitleBarVisible(exceptedVisible);

                this.View.CurrentTitleVisible = exceptedVisible;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnMenuViewShowMenuStrip(object sender, EventArgs e)
        {
            try
            {
                if (_mainMenuStrip.Visible)
                {
                    (sender as ToolStripMenuItem).Text = "显示菜单栏";
                }
                else
                {
                    (sender as ToolStripMenuItem).Text = "隐藏菜单栏";
                }

                _mainMenuStrip.Visible = !_mainMenuStrip.Visible;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnMenuViewShowStatusbar(object sender, EventArgs e)
        {
            try
            {
                if (this.View.StatusBar.Visible)
                {
                    (sender as ToolStripMenuItem).Text = "显示状态栏";
                }
                else
                {
                    (sender as ToolStripMenuItem).Text = "隐藏状态栏";
                }

                this.View.StatusBar.Visible = !this.View.StatusBar.Visible;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnMenuViewShowDocumentIcon(object sender, EventArgs e)
        {
            if (this.View.DockPanel.ShowDocumentIcon)
            {
                (sender as ToolStripMenuItem).Text = "显示标签图标";
            }
            else
            {
                (sender as ToolStripMenuItem).Text = "隐藏标签图标";
            }

            this.View.DockPanel.ShowDocumentIcon = !this.View.DockPanel.ShowDocumentIcon;
        }
        private void OnMenuViewShowAllWindows(object sender, EventArgs e)
        {
            try
            {
                this.View.DockPanel.SuspendLayout(true);

                var preDocument = this.View.DockPanel.ActiveDocument;

                this.View.UpdateDockContents();

                if (preDocument != null)
                {
                    preDocument.DockHandler.Show();
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                this.View.DockPanel.ResumeLayout(true, true);
            }
        }
        private void OnMenuViewResetWindowsLayout(object sender, EventArgs e)
        {
            try
            {
                var dialogRc = MessageBox.Show("确认恢复窗口默认布局？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (dialogRc != DialogResult.Yes) return;

                this.View.ResetWindowsLayout();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnMenuViewLockUnlockLayout(object sender, EventArgs e)
        {
            try
            {
                var theMenuItem = sender as ToolStripMenuItem;

                if (this.View.DockPanel.AllowEndUserDocking)
                {
                    theMenuItem.Text = "解锁窗口布局(&L)";
                    theMenuItem.Image = Resources.UnlockLayout;
                }
                else
                {
                    theMenuItem.Text = "锁定窗口布局(&L)";
                    theMenuItem.Image = Resources.LockLayout;
                }

                this.View.DockPanel.AllowEndUserDocking = !this.View.DockPanel.AllowEndUserDocking;

                // 更新所有DockContent的CloseButton状态。
                this.View.DockContents.ForEach(p =>
                {
                    p.Value.CloseButtonVisible = this.View.DockPanel.AllowEndUserDocking;
                });
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnMenuViewImportLayout(object sender, EventArgs e)
        {
            bool success = false;

            try
            {
                var dlg = new OpenFileDialog()
                {
                    Filter = string.Format("界面布局文件(*.{0})|*.{0}", FrmMain.UiLayoutSuffix),
                    RestoreDirectory = true,
                    Title = "指定想要导入的界面布局文件"
                };
                var dlgResult = dlg.ShowDialog();
                if (dlgResult != DialogResult.OK) return;

                // 保存当前布局。
                this.View.SaveDockConfigToFile();

                // 加载指定的文件
                this.View.LoadLayoutFromFile(dlg.FileName);

                success = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(string.Format("加载指定的文件时发生错误，{0}", ex.Message), "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            // 导入失败，则恢复上次布局。
            if (!success)
            {
                try
                {
                    var configFile = this.View.BuildDockConfigFileName();
                    this.View.LoadLayoutFromFile(configFile);
                }
                catch (System.Exception /*ex*/)
                {
                    // 恢复上次布局失败，则使用默认布局。
                    this.View.ResetWindowsLayout();
                }
            }
        }

        private void OnMenuViewExportLayout(object sender, EventArgs e)
        {
            try
            {
                var fileName = DateTime.Now.ToString("yyyy_MM_dd HH.mm.ss");

                var dlg = new SaveFileDialog()
                {
                    FileName = string.Format("{0}.atsLayout", fileName),
                    RestoreDirectory = true,
                    Filter = string.Format("界面布局文件(*.{0})|*.{0}", FrmMain.UiLayoutSuffix),
                    Title = "指定将要导出的界面布局文件"
                };
                var dlgResult = dlg.ShowDialog();
                if (dlgResult != DialogResult.OK) return;

                // 
                this.View.DockPanel.SaveAsXml(dlg.FileName);

                // 创建对应的图像名称。
                var imageFileName = Path.ChangeExtension(dlg.FileName, "png");

                // 保存当前屏幕截图
                //using (var bmp = new Bitmap(this.Size.Width, this.Size.Height))
                //{
                //    this.DrawToBitmap(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height));
                //    bmp.Save(imageFileName, System.Drawing.Imaging.ImageFormat.Png);
                //}
                GdiNativeMethods.PrintScreenToFile(this.View, imageFileName);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion


        #region "Tool菜单事件响应函数"
        /// <summary>
        /// 工具 - 选项
        /// </summary>
        private void OnMenuToolOption(object sender, EventArgs e)
        {
            try
            {
                Workbench.OptionManager.Title = "选项";
                Workbench.OptionManager.Show(this.View);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 工具 - 打开程序目录
        /// </summary>
        private void OnMenuToolOpenExeFolder(object sender, EventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start("explorer.exe", AppDomain.CurrentDomain.BaseDirectory);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 工具 - 滚动日志
        /// </summary>
        private void OnMenuToolRolloverLog(object sender, EventArgs e)
        {
            try
            {
                GlobalMessageBus.PublishCommLogRollover(e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 工具 - 截屏
        /// </summary>
        private void OnMenuToolScreenshot(object sender, EventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start("SnagIt.exe");
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 工具 - 运行
        /// </summary>
        private void OnMenuToolRunCommand(object sender, EventArgs e)
        {
            try
            {
                var cmdForm = new CmdInputForm();
                var rc = cmdForm.ShowDialog();

                if (rc == DialogResult.OK)
                {
                    string cmd = cmdForm.Command;
                    if (cmd.Equals("debug -s", StringComparison.OrdinalIgnoreCase))
                    {
                        _menuDebug.Visible = true;
                    }
                    else if (cmd.Equals("debug -h", StringComparison.OrdinalIgnoreCase))
                    {
                        _menuDebug.Visible = false;
                    }
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion


        #region "Debug菜单事件响应函数"
        /// <summary>
        /// 调试 - 打开NDM调试窗口
        /// </summary>
        private void OnMenuDebugOpenNDMDebugForm(object sender, EventArgs e)
        {
            try
            {
                //LocalMessageBus.Current.Publish(AtsMessageTopics.AppDianostic.OpenNDMDebugForm, e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 调试 - 打开TMT调试窗口
        /// </summary>
        private void OnMenuDebugOpenTMTDebugForm(object sender, EventArgs e)
        {
            try
            {
                //LocalMessageBus.Current.Publish(AtsMessageTopics.AppDianostic.OpenTMTDebugForm, e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 调试 - 打开SDM调试窗口
        /// </summary>
        private void OnMenuDebugOpenSDMDebugForm(object sender, EventArgs e)
        {
            try
            {
                //LocalMessageBus.Current.Publish(AtsMessageTopics.AppDianostic.OpenSDMDebugForm, e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 调试 - 打开内部通信调试窗口
        /// </summary>
        private void OnMenuDebugOpenCommDebugForm(object sender, EventArgs e)
        {
            try
            {
                //LocalMessageBus.Current.Publish(AtsMessageTopics.AppDianostic.OpenCommDebugForm, e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 调试 - 打开保存车站范围管理表调试窗口
        /// </summary>
        private void OnMenuDebugSaveStationRangeTable(object sender, EventArgs e)
        {
            try
            {
                //LocalMessageBus.Current.Publish(AtsMessageTopics.AppDianostic.SaveStationRangeTable, e, sender);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion


        #region "About菜单事件响应函数"
        /// <summary>
        /// 关于
        /// </summary>
        private void OnMenuHelpAbout(object sender, EventArgs e)
        {
            try
            {
                Workbench.AboutBox.TopMost = true;
                Workbench.AboutBox.StartPosition = FormStartPosition.CenterScreen;
                Workbench.AboutBox.ShowDialog(Workbench.MainForm);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        /// <summary>
        /// 操作手册
        /// </summary>
        private void OnMenuHelpManual(object sender, EventArgs e)
        {
            try
            {
                string strManualName = "产品使用手册.chm";
                string strDirExe = Directory.GetCurrentDirectory();
                string strDirManual = strDirExe + "\\" + strManualName;
                if (File.Exists(strDirManual))
                {
                    Help.ShowHelp(this.View, strDirManual);
                }
                else
                {
                    MessageBox.Show("产品使用手册未找到。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void OnMenuCompanyLogoClick(object sender, EventArgs e)
        {
            try
            {
                var form = new CompanyContactsForm();
                form.ShowDialog();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 退出
        /// </summary>
        private void OnMenuExit(object sender, EventArgs e)
        {
            this.View.Close();
        }

        #endregion
    }
}
