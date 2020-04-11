using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using Platform.Presentation;
using Products.Infrastructure;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.Resource;
using Products.Shell.Presentation.MainForm;
using Products.Shell.Properties;
using WeifenLuo.WinFormsUI.Docking;

namespace Products.Shell
{
    partial class FrmMain : Form, IControlOptimizer
    {
        /// <summary>
        /// UI布局配置文件的后缀名。
        /// </summary>
        public const string UiLayoutSuffix = "Layout";

        #region "Field"
        protected List<IControlOptimizer> _controlOptimizers = new List<IControlOptimizer>();

        private Dictionary<ProductPartAttribute, DockContentEx> _dockContents = new Dictionary<ProductPartAttribute, DockContentEx>();

        /// <summary>
        /// DockPanel
        /// </summary>
        private DockPanel _dockPanel = null;

        private FrmMainMenuPresenter _menuPresenter;
        private FrmMainStatusBarPresenter _statusBarPresenter;

        #endregion


        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="initalTitlebarVisible">标题栏初始可见性。</param>
        public FrmMain(bool initalTitlebarVisible)
        {
            this.InitalTitleVisible = initalTitlebarVisible;
            this.CurrentTitleVisible = initalTitlebarVisible;

            InitializeComponent();
            
            CreateDockPanel();

            Initialize();
        }

        #endregion

        #region "Properties"

        /// <summary>
        /// 获取DockPanel。
        /// </summary>
        public DockPanel DockPanel { get { return _dockPanel; } }

        /// <summary>
        /// 获取DockContents。
        /// </summary>
        public List<KeyValuePair<ProductPartAttribute, DockContentEx>> DockContents { get { return _dockContents.ToList(); } }

        /// <summary>
        /// 标题栏的初始可见性。
        /// </summary>
        public bool InitalTitleVisible { get; private set; }
        /// <summary>
        /// 标题栏的当前可见性。
        /// </summary>
        public bool CurrentTitleVisible { get; set; }

        /// <summary>
        /// 获取主菜单。
        /// </summary>
        public MenuStrip MainMenu { get { return _menuPresenter.MenuBar; } }

        /// <summary>
        /// 获取状态栏。
        /// </summary>
        public StatusStrip StatusBar { get { return _statusBarPresenter.StatusBar; } }
        
        #endregion

        #region "override methods"

        #endregion


        #region "Private methods"

        private void CreateDockPanel()
        {
            if (this._dockPanel != null)
            {
                this.Controls.Remove(_dockPanel);
            }

            _dockPanel = new DockPanel() { Dock = DockStyle.Fill };
            _dockPanel.ShowDocumentIcon = true;
            _dockPanel.DockTopPortion = 100D;
            this.Controls.Add(_dockPanel);
        }

        private void Initialize()
        {
            _menuPresenter = new FrmMainMenuPresenter(this);
            _statusBarPresenter = new FrmMainStatusBarPresenter(this);

            this.Icon = ProductResources.ApplicationIcon;

            this.ResetFormBorderStyle();
        }

        /// <summary>
        /// 复位窗体边框风格。
        /// </summary>
        private void ResetFormBorderStyle()
        {
            if (InitalTitleVisible)
            {
                this.FormBorderStyle = FormBorderStyle.Sizable;
                this.WindowState = FormWindowState.Maximized;
            }
            else
            {
                this.FormBorderStyle = FormBorderStyle.None;
                this.WindowState = FormWindowState.Normal;
                this.DesktopBounds = new Rectangle(0, 0, Screen.AllScreens.Sum(p => p.Bounds.Width), Screen.AllScreens.Min(p => p.Bounds.Height));
            }
        }

        private void PerformLoad()
        {
            //this.DesktopBounds = new Rectangle(0, 0, Screen.AllScreens.Sum(p => p.Bounds.Width),
            //    Screen.AllScreens.Min(p => p.Bounds.Height));

            // 设置主窗口标题
            if (string.IsNullOrWhiteSpace(GlobalServices.NodeContext.Name))
            {
                this.Text = ProductResources.ProjectChsName;
            }
            else
            {
                this.Text = string.Format("{0} - {1}", GlobalServices.NodeContext.Name, ProductResources.ProjectChsName);
            }

            // 构建需要优化的控件集
            _controlOptimizers = Workbench.MainWorkspace.SmartParts.OfType<IControlOptimizer>().ToList();

            // 构造DockContents
            this.CreateDockContents();

            // 订阅用户切换事件。
            GlobalMessageBus.SubscribeUserChanging(OnUserChanging);
            GlobalMessageBus.SubscribeUserChanged(OnUserChanged);

            // 显示DockContents。
            var configFile = BuildDockConfigFileName();
            if (File.Exists(configFile))
            {
                try
                {
                    _dockPanel.LoadFromXml(configFile, DeserializeDockContentCallback);
                }
                catch (System.Exception /*ex*/)
                {
                    File.Delete(configFile);
                    this.ResetWindowsLayout();
                }

                this.HideNonPermissionContents();
            }
            else
            {
                // 更新DockContent
                this.UpdateDockContents();
            }
        }

        private IDockContent DeserializeDockContentCallback(string persistString)
        {
            var theContent = _dockContents.Where(p => p.Key.ControlType.ToString() == persistString).FirstOrDefault().Value;
            return theContent;
        }
        
        private void CreateDockContents()
        {
            var theWorkspace = Workbench.MainWorkspace as MockWorkspace;
            foreach (var theControl in theWorkspace.MainControls)
            {
                var controlType = theControl.Key.ControlType;

                DockContentEx newDockContent = null;

                if (controlType == PresentationControlType.ApplicationLog)
                {
                    newDockContent = new DockContentEx(theControl.Value, theControl.Key.Title, Resources.AppLog)
                    {
                        DefaultDockState = DockState.DockBottom,
                    };
                }
                else
                {
                    newDockContent = new DockContentEx(theControl.Value, theControl.Key.Title)
                    {
                        DefaultDockState = DockState.Document,
                    };
                }

                if (theControl.Key.DefaultIcon != null)
                {
                    newDockContent.Icon = theControl.Key.DefaultIcon;
                }
                newDockContent.CloseButtonVisible = true;
                newDockContent.PersistString = controlType.ToString();

                _dockContents[theControl.Key] = newDockContent;
            }
        }
        public void UpdateDockContents()
        {
            DockContentEx firstContentToShow = null;

            foreach (var item in _dockContents)
            {
                if (firstContentToShow == null && item.Value.DefaultDockState == DockState.Document)
                {
                    firstContentToShow = item.Value;
                }

                item.Value.Show(_dockPanel, item.Value.DefaultDockState);
            }

            if (firstContentToShow != null)
            {
                firstContentToShow.Show();
            }
        }
        private void ShowAllDockContents()
        {
            _dockContents.Select(p => p.Value).ToList().ForEach(p =>
            {
                p.Show(_dockPanel, p.DefaultDockState);
            });

            _dockContents.Select(p => p.Value).Where(p => p.DefaultDockState == DockState.Document).First().Show();
        }
        public void ShowSpecifiedDockContent(PresentationControlType controlType)
        {
            var theContent = _dockContents.Where(p => p.Key.ControlType == controlType).First().Value;

            if (theContent != null)
            {
                theContent.Show(_dockPanel);
            }
        }
        private void HideNonPermissionContents()
        {
            foreach (var item in _dockContents)
            {
                if (!this.CanShow(item.Key.ControlType) && item.Value.Visible)
                {
                    item.Value.Hide();
                }
            }
        }
        private void CloseAllDockContents()
        {
            _dockContents.Values.ToList().ForEach(p =>
            {
                p.DockPanel = null;
                p.RemoveChildPart();
                p.Close();
            });
        }


        public bool CanShow(PresentationControlType controlType)
        {
            //var authorities = CurrentUserDetail.Instance.OperationAuthorities;

            //var privilege = ShellHelper.GetControlPrivilege(controlType);

            //if (privilege != SystemPrivilege.None)
            //{
            //    return authorities.Contains(privilege);
            //}
            //else
            //{
            //    return true;
            //}
            return true;
        }

        /// <summary>
        /// 根据当前用户构建Dock配置文件。
        /// </summary>
        public string BuildDockConfigFileName()
        {
            var fileName = string.Empty;

            if (GlobalServices.UAC != null)
            {
                fileName = string.Format("{0}{1}_{2}{3}.{4}",GlobalServices.NodeContext.Code, GlobalServices.NodeContext.Name,
                     GlobalServices.UAC.CurrentUserCode, GlobalServices.UAC.CurrentUserName, FrmMain.UiLayoutSuffix);
            }
            else
            {
                fileName = string.Format("{0}{1}.{2}",GlobalServices.NodeContext.Code, GlobalServices.NodeContext.Name,
                    FrmMain.UiLayoutSuffix);
            }

            return Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location), fileName);
        }
        public void SaveDockConfigToFile()
        {
            var fileName = BuildDockConfigFileName();
            _dockPanel.SaveAsXml(fileName);
        }
        public void LoadLayoutFromFile(string fileName)
        {
            try
            {
                // suspend layout
                _dockPanel.SuspendLayout(true);

                // 关闭所有DockContents。
                this.CloseAllDockContents();

                // 创建新的DockContents。
                this.CreateDockContents();

                // 加载配置文件
                _dockPanel.LoadFromXml(fileName, DeserializeDockContentCallback);

                // 隐藏无权限的视图。
                this.HideNonPermissionContents();
            }
            catch (System.Exception /*ex*/)
            {
                throw;
            }
            finally
            {
                _dockPanel.ResumeLayout(true, true);
            }
        }

        /// <summary>
        /// 重置窗口布局。
        /// </summary>
        public void ResetWindowsLayout()
        {
            try
            {
                _dockPanel.SuspendLayout(true);
          
                _menuPresenter.Reset();
                _statusBarPresenter.Reset();
  
                this.ResetFormBorderStyle();

                this.CloseAllDockContents();
                this.CreateDockContents();
                //this.ShowAllDockContents();
                this.UpdateDockContents();
            }
            catch (Exception ex)
            {
                LogUtility.Warning(ex);
            }
            finally
            {
                _dockPanel.ResumeLayout(true, true);
            }
        }

        private void OnUserChanging(object sender, EventArgs e)
        {
            try
            {
                // 保存当前用户的布局信息。
                this.SaveDockConfigToFile();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        private void OnUserChanged(object sender, EventArgs e)
        {
            // 如果当前用户的布局配置文件存在，则加载。否则按默认方式布局。

            var configFile = this.BuildDockConfigFileName();

            if (File.Exists(configFile))
            {
                this.Invoke(new Action(() => 
                {
                    try
                    {
                        this.LoadLayoutFromFile(configFile); 
                    }
                    catch (System.Exception /*ex*/)
                    {
                        this.ResetWindowsLayout();
                    }
                }));
            }
            else
            {
                this.Invoke(new Action(() => 
                {
                    this.ResetWindowsLayout(); 
                }));
            }
        }

        #endregion

        #region "IControlOptimizer 方法"
        public void OptimizeIdle()
        {
            try
            {
                foreach (var item in _controlOptimizers)
                {
                    item.OptimizeIdle();
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "控件事件响应函数"
        private void OnFormLoad(object sender, EventArgs e)
        {
            this.PerformLoad();
        }

        private void OnFormClosing(object sender, FormClosingEventArgs e)
        {
            // 保存布局。
            this.SaveDockConfigToFile();
        }

        #endregion
    }
}
