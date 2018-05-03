using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using Acl.ServiceManagement;
using Platform.Presentation;
using Products.Infrastructure;
using Products.Presentation;
using Products.Resource;
using Products.Shell.MainView;
using Products.Shell.Properties;
using WeifenLuo.WinFormsUI.Docking;

namespace Products.Shell
{
    partial class FormDemo : FrmMain
    {
        private MockWorkspace _mockWorkspace;
        private List<Tuple<ProductPartAttribute, DockContentEx>> _dockContents = new List<Tuple<ProductPartAttribute, DockContentEx>>();
        
        private ToolStrip _menuStrip = null; // 菜单
        private ToolStripMenuItem _toolStripItemView = null;
        private ToolStripMenuItem _toolStripItemExit = null;

        private ToolStripStatusLabel _toolStripLanuchTime = null; // 状态栏
        private ToolStripStatusLabel _toolStripVersion = null;
        private ToolStripStatusLabel _toolStripProductName = null;
        //private ToolStripStatusLabel _labelDatabase = null;
        //private ToolStripStatusLabel _labelActiveStandby = null;

        private MenuCommandHandler _commandHandler = new MenuCommandHandler();

        private DeserializeDockContent m_deserializeDockContent;
        
        /// <summary>
        /// 构造函数。
        /// </summary>
        public FormDemo()
        {
            InitializeComponent();

            this._dockPanel.Dock = DockStyle.Fill;

            this.Icon = ProductResources.ApplicationIcon;

            Initialize();
            
            m_deserializeDockContent = new DeserializeDockContent(GetContentFromPersistString);
        }

        #region "protected methods"

        protected override void OnLoad(EventArgs e)
        {
            try
            {
                base.OnLoad(e);

                //InitNotifyIcon();

                this.SuspendLayout();

                RegisterPluginsMenu();

                CreateDockContents();

                CreateViewSubMenuItem();

                // 
                var configFile = GetDockConfigFileName();
                if (File.Exists(configFile))
                {
                    _dockPanel.LoadFromXml(configFile, m_deserializeDockContent);
                }
                else
                {
                    this.ShowDockContents();
                }

                this.ResumeLayout(false);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            try
            {
                SaveDockConfigToFile();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }

            base.OnFormClosing(e);
        }
        #endregion


        #region "private methods"

        private void Initialize()
        {
            // 
            InitWorkspace();

            // 初始化菜单项
            InitMainMenuItem();

            // 初始化状态栏
            InitStatusBar();

            // 添加日志窗体。
            MainWorkSpace.AddPart(new LogControl(), Resources.AppLog);
        }

        private void InitWorkspace()
        {
            _mockWorkspace = new MockWorkspace();
            Workbench.MainWorkspace = _mockWorkspace;
        }

        private void InitMainMenuItem()
        {
            _menuStrip = Workbench.GetToolStrip("Server.MenuStrip");
            if (_menuStrip != null)
            {
                this.Controls.Add(_menuStrip);
            }

            _toolStripItemView = Workbench.GetToolStripItem("mnuView") as ToolStripMenuItem;

            _toolStripItemExit = Workbench.GetToolStripItem("mnuExit") as ToolStripMenuItem;
            _toolStripItemExit.Image = Resources.Exit;
        }

        private void InitStatusBar()
        {
            var statusStrip = Workbench.GetToolStrip("Server.StatusStrip");
            if (statusStrip != null)
            {
                this.Controls.Add(statusStrip);
            }

            _toolStripLanuchTime = Workbench.GetToolStripItem("labelLanuchTime") as ToolStripStatusLabel;
            _toolStripVersion = Workbench.GetToolStripItem("labelVersion") as ToolStripStatusLabel;
            _toolStripProductName = Workbench.GetToolStripItem("labelProductName") as ToolStripStatusLabel;
            //_labelDatabase = Workbench.GetToolStripItem("labelDatabaseStatus") as ToolStripStatusLabel;
            //_labelActiveStandby = Workbench.GetToolStripItem("labelActiveStandbyStatus") as ToolStripStatusLabel;

            // 启动时间
            _toolStripLanuchTime.Text = String.Format("启动时间 {0} ", DateTime.Now);


#if DEBUG
            _toolStripVersion.ForeColor = Color.Blue;
            _toolStripVersion.Text = String.Format(" v{0} 调试版", ProductResources.ProductStringVersion);
#else
            // 程序版本号
            _toolStripVersion.Text = String.Format("版本 v{0} ", ProductResources.ProductStringVersion);
#endif

            _toolStripProductName.Text = String.Format(" {0} ", ProductResources.ProjectChsName);
        }

        private void RegisterPluginsMenu()
        {
            if (_menuStrip == null) return;

            // 获取所有ITopMenuProvider的实现者
            var topMenuProviders = ServiceManager.Current.GetAll<ITopMenuItemProvider>();

            // 添加到框架菜单中
            foreach (var provider in topMenuProviders)
            {
                var toolStripItems = provider.GetTopMenu().Reverse().ToList();

                foreach (var tsItem in toolStripItems)
                {
                    _menuStrip.Items.Insert(2, tsItem);
                }
            }
        }

        private void CreateDockContents()
        {
            foreach (var theControl in _mockWorkspace.MainControls)
            {
                var controlType = theControl.Item1.ControlType;

                DockContentEx newDockContent = null;

                if (controlType == PresentationControlType.ApplicationLog)
                {
                    newDockContent = new DockContentEx(theControl.Item2, theControl.Item1.Title, Resources.AppLog) 
                    { 
                        DefaultDockState = DockState.DockBottomAutoHide,
                    };
                }
                else
                {
                    newDockContent = new DockContentEx(theControl.Item2, theControl.Item1.Title)
                    { 
                        DefaultDockState = DockState.Document,
                    };
                }

                if (theControl.Item1.DefaultIcon != null)
                {
                    newDockContent.Icon = theControl.Item1.DefaultIcon;
                }
                newDockContent.CloseButtonVisible = true;
                newDockContent.PersistString = controlType.ToString();

                _dockContents.Add(new Tuple<ProductPartAttribute,DockContentEx>(theControl.Item1, newDockContent));
            }
        }

        private void CreateViewSubMenuItem()
        {
            foreach (var item in _dockContents)
            {
                var subMenuItem = new ToolStripMenuItem() { Text = item.Item1.Title, Tag = item.Item2 };
                subMenuItem.Click += OnViewSubMenuItemClick;
                _toolStripItemView.DropDownItems.Add(subMenuItem);

                if (item.Item1.DefaultIcon != null)
                {
                    subMenuItem.Image = item.Item1.DefaultIcon.ToBitmap();
                }
            }

            var menuResumeDefaultLayout = new ToolStripMenuItem() { Text = "恢复窗口默认布局(&R)" };
            menuResumeDefaultLayout.Click += OnMenuViewResumeDefaultLayout;
            _toolStripItemView.DropDownItems.AddRange(new ToolStripItem[] { new ToolStripSeparator(), menuResumeDefaultLayout });
        }

        private void ResumeDefaultLayout()
        {
            try
            {
                _dockPanel.SuspendLayout(true);

                this.CloseAllDockContents();
                this.CreateDockContents();

                this.UpdateDockContents();
            }
            finally
            {
                _dockPanel.ResumeLayout(true, true);
            }
        }
        private void CloseAllDockContents()
        {
            _dockContents.Select(p=>p.Item2).ToList().ForEach(p =>
            {
                p.DockPanel = null;
                p.RemoveATSPart();
                p.Close();
            });
        }
        private void UpdateDockContents()
        {
            DockContentEx firstContentToShow = null;

            foreach (var item in _dockContents)
            {
                if (firstContentToShow == null && item.Item2.DefaultDockState == DockState.Document)
                {
                    firstContentToShow = item.Item2;
                }

                item.Item2.Show(_dockPanel, item.Item2.DefaultDockState);
            }

            if (firstContentToShow != null)
            {
                firstContentToShow.Show();
            }
        }

        private void ShowDockContents()
        {
            _dockContents.Select(p=>p.Item2).ToList().ForEach(p =>
            {
                p.Show(_dockPanel, p.DefaultDockState);
            });

            _dockContents.Select(p => p.Item2).Where(p => p.DefaultDockState == DockState.Document).First().Show();
        }

        private string GetDockConfigFileName()
        {
            var fileName = string.Format("DockPanel.config");
            var pathFileName = Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), fileName);
            return pathFileName;
        }
        private void SaveDockConfigToFile()
        {
            var fileName = GetDockConfigFileName();
            _dockPanel.SaveAsXml(fileName);
        }
        private IDockContent GetContentFromPersistString(string persistString)
        {
            return _dockContents.Where(p => p.Item2.Text == persistString).Select(p=>p.Item2).FirstOrDefault();
        }
        #endregion
        
        #region "菜单事件"
        private void OnViewSubMenuItemClick(object sender, EventArgs e)
        {
            try
            {
                var menuItem = sender as ToolStripMenuItem;
                if (menuItem == null) return;

                var form = menuItem.Tag as DockContentEx;
                if (form != null)
                {
                    form.Show(_dockPanel);
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void OnMenuViewResumeDefaultLayout(object sender, EventArgs e)
        {
            try
            {
                ResumeDefaultLayout();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion

        #region "窗体事件"


        #endregion
    }
}
