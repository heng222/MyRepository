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
using System.Data;
using System.Drawing;
using System.Windows.Forms;

using Acl;
using Acl.ServiceManagement;

using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;

namespace Products.Shell.Presentation.MainForm
{
    partial class FrmMainStatusBarPresenter : CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// 用于显示当前时间。
        /// </summary>
        private Timer _currentTimer;

        /// <summary>
        /// 状态栏
        /// </summary>
        private StatusStrip _statusStrip = new StatusStrip();
        private ToolStripStatusLabel _statusLabelUserCode = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelUserName = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelUserRole = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelVersion = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelLanuchTime = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelCurrentTime = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelDbText = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelDbState = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelHotstandbyText = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelHotstandbyState = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelNodeName = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelLocation = new ToolStripStatusLabel();
        private ToolStripStatusLabel _statusLabelProjectName = new ToolStripStatusLabel();
        #endregion

        #region "Constructor"
        public FrmMainStatusBarPresenter(FrmMain view)
        {
            this.View = view;
            this.View.Load += OnOwnerViewLoad;

            //// 订阅数据库事件
            //DbConnectionMonitor.Current.SubscribeConnectionStateChanged(OnDbConnectionChanged);
            //this.OnDbConnectionChanged(DbConnectionMonitor.Current.State ?? ConnectionState.Closed);

            // 订阅主备状态变化事件
            //AtsMessageBus.SubscribeHotStandbyStateChanged(OnHotstandbyStateChanged);

            this.CreateStatusBar();

            // 
            this.AddDisposable(_statusStrip);
            this.AddDisposable(_currentTimer);
        }
        #endregion

        #region "Properties"
        public FrmMain View { get; private set; }

        public StatusStrip StatusBar { get { return _statusStrip; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Mobility", "CA1601:DoNotUseTimersThatPreventPowerStateChanges")]
        private void CreateStatusBar()
        {
            // stslbUserID
            _statusLabelUserCode.Visible = false;
            _statusLabelUserCode.AutoSize = false;
            _statusLabelUserCode.Width = 120;
            _statusLabelUserCode.Text = "用户ID：";
            _statusLabelUserCode.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelUserCode.Click += OnUserCodeOrNameLableClick;

            // stslbUserName
            _statusLabelUserName.AutoSize = false;
            _statusLabelUserName.Width = 120;
            _statusLabelUserName.Text = "用户名：";
            _statusLabelUserName.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelUserName.Click += OnUserCodeOrNameLableClick;

            //// stslbUserRole
            //_statusLabelUserRole.Visible = NodeContextManager.Current.ControlTypes.Contains(PresentationControlType.Logon);
            //_statusLabelUserRole.AutoSize = false;
            //_statusLabelUserRole.Width = 130;
            //_statusLabelUserRole.Text = "角色：";
            //_statusLabelUserRole.TextAlign = ContentAlignment.MiddleCenter;

            //// stslMachineName
            //_statusLabelNodeName.AutoSize = false;
            //_statusLabelNodeName.Width = 180;
            //_statusLabelNodeName.Text = "设备名称：";
            //_statusLabelNodeName.TextAlign = ContentAlignment.MiddleCenter;

            //// stslbUserStation
            //_statusLabelLocation.Visible = NodeContextManager.Current.ControlTypes.Contains(PresentationControlType.Logon);
            //_statusLabelLocation.AutoSize = false;
            //_statusLabelLocation.Width = 150;
            //_statusLabelLocation.Text = "登录位置";
            //_statusLabelLocation.TextAlign = ContentAlignment.MiddleCenter;

            //// 数据库状态。
            //_statusLabelDbText.Text = "数据库状态";
            //_statusLabelDbText.TextAlign = ContentAlignment.MiddleCenter;
            //_statusLabelDbState.Text = "     ";
            //_statusLabelDbState.AutoToolTip = false;
            //_statusLabelDbState.BackColor = Color.Black;

            //// 主备状态
            //_statusLabelHotstandbyText.Visible = NodeContextManager.HasSibling();
            //_statusLabelHotstandbyText.Text = "      主备状态";
            //_statusLabelHotstandbyText.TextAlign = ContentAlignment.MiddleCenter;
            //_statusLabelHotstandbyState.Visible = NodeContextManager.HasSibling();
            //_statusLabelHotstandbyState.Text = "       ";
            //_statusLabelHotstandbyState.AutoToolTip = true;
            //_statusLabelHotstandbyState.BackColor = Color.Black;

            // 登录时间
            _statusLabelLanuchTime.AutoSize = false;
            _statusLabelLanuchTime.Visible = false;
            _statusLabelLanuchTime.Width = 200;
            _statusLabelLanuchTime.Text = "登录时间";
            _statusLabelLanuchTime.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelLanuchTime.Click += OnTimeLabelClick;

            // 当前时间
            _statusLabelCurrentTime.AutoSize = false;
            _statusLabelCurrentTime.Width = 200;
            _statusLabelCurrentTime.Text = "当前时间";
            _statusLabelCurrentTime.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelCurrentTime.Click += OnTimeLabelClick;

            _currentTimer = new Timer() { Interval = 500, Enabled = true };
            _currentTimer.Tick += OnCurrentTimerTick;

            // stslbVersion
            _statusLabelVersion.Text = "版本号：";

            // stslbProjectName
            _statusLabelProjectName.AutoSize = false;
            _statusLabelProjectName.Text = "项目中文名称";
            _statusLabelProjectName.Spring = true;
            _statusLabelProjectName.TextAlign = ContentAlignment.MiddleRight;

            //
            _statusStrip.SizingGrip = this.View.InitalTitleVisible;
            _statusStrip.Items.AddRange(new ToolStripItem[] {_statusLabelUserCode, _statusLabelUserName,
                                        _statusLabelUserRole,
                                        _statusLabelLocation, _statusLabelNodeName,
                                        _statusLabelDbText, _statusLabelDbState,
                                        _statusLabelHotstandbyText, _statusLabelHotstandbyState,
                                        _statusLabelLanuchTime, _statusLabelCurrentTime,
                                        _statusLabelVersion, _statusLabelProjectName});
            this.View.Controls.Add(_statusStrip);
        }

        private void UpdateStatusBar()
        {
            try
            {
                if (GlobalServices.UAC != null)
                {
                    _statusLabelUserCode.Text = string.Format("用户编号：{0}", GlobalServices.UAC.CurrentUserCode);
                    _statusLabelUserName.Text = string.Format("用户名称：{0}", GlobalServices.UAC.CurrentUserName);
                }
                else
                {
                    _statusLabelUserCode.Text = string.Empty;
                    _statusLabelUserName.Text = string.Empty;
                }
                //_statusLabelUserRole.Text = string.Format("角色：{0}", CurrentUserDetail.Instance.RoleName);
                ////_statusLabelDepart.Text = string.Format("部门：{0}", CurrentUserDetail.Instance.DepartName);
                //_statusLabelNodeName.Text = string.Format("节点名称：{0}", NodeContextManager.Current.Name);

                //if (CurrentUserDetail.Instance.OwnerStationID == Department.Center)
                //{
                //    _statusLabelLocation.Text = string.Format("位置：控制中心");
                //}
                //else
                //{
                //    _statusLabelLocation.Text = string.Format("位置：{0}", CurrentUserDetail.Instance.OwnerStationName);
                //}

                _statusLabelLanuchTime.Text = string.Format("登录时间：{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));


                var sysAttri = ServiceManager.Current.Get<ISystemProperty>();
                _statusLabelVersion.Text = string.Format(" 版本号：v{0}", sysAttri.ProductStringVersion);
                _statusLabelProjectName.Text = string.Format("{0}  ", sysAttri.ProjectChsName);

                this.UpdateDbStateLabel();
                this.UpdateHotstandyStateLabel();
            }
            catch (Exception ex)
            {
                LogUtility.Error(ex.ToString());
            }
        }

        private void UpdateDbStateLabel()
        {
            //_statusLabelDbState.BackColor = DbConnectionMonitor.Current.Connected ? Color.DarkGreen : Color.Red;
            //_statusLabelDbState.ToolTipText = DbConnectionMonitor.Current.Connected ? "连接" : "断开";
        }

        private void UpdateHotstandyStateLabel()
        {
            //var state = HotStandbyManager.CurrentState;

            //if (state == NodeHotStandbyState.Main)
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.DarkGreen;
            //    _statusLabelHotstandbyState.ToolTipText = "主机";
            //}
            //else if (state == NodeHotStandbyState.Back)
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.Yellow;
            //    _statusLabelHotstandbyState.ToolTipText = "备机";
            //}
            //else
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.Black;
            //    _statusLabelHotstandbyState.ToolTipText = "未知";
            //}
        }

        private void OnUserChanged(object sender, EventArgs e)
        {
            try
            {
                // 更新状态栏
                this.View.Invoke(new Action(() =>
                {
                    this.UpdateStatusBar();
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
            _statusStrip.Visible = true; // 状态栏可见。
            _statusStrip.SizingGrip = this.View.InitalTitleVisible;
        }
        #endregion

        #region "窗体事件"

        private void OnOwnerViewLoad(object sender, EventArgs e)
        {
            try
            {
                // 订阅用户切换事件。
                GlobalMessageBus.SubscribeUserChanged(OnUserChanged);

                // 更新状态栏。
                this.UpdateStatusBar();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "控件事件"
        private void OnUserCodeOrNameLableClick(object sender, EventArgs e)
        {
            _statusLabelUserCode.Visible = !_statusLabelUserCode.Visible;
            _statusLabelUserName.Visible = !_statusLabelUserName.Visible;
        }

        private void OnCurrentTimerTick(object sender, EventArgs e)
        {
            try
            {
                if (this.View.IsHandleCreated && _statusLabelCurrentTime.Visible)
                {
                    _statusLabelCurrentTime.Text = string.Format("当前时间：{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private void OnTimeLabelClick(object sender, EventArgs e)
        {
            _statusLabelCurrentTime.Visible = !_statusLabelCurrentTime.Visible;
            _statusLabelLanuchTime.Visible = !_statusLabelLanuchTime.Visible;

            if (_statusLabelCurrentTime.Visible)
            {
                _statusLabelCurrentTime.Text = string.Format("当前时间：{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
            }
        }
        #endregion

        #region "数据库连接变化事件"
        private void OnDbConnectionChanged(ConnectionState connectionState)
        {
            try
            {
                if (this.View.IsHandleCreated)
                {
                    this.View.BeginInvoke(new Action(() =>
                    {
                        try
                        {
                            //UpdateDbStateLabel();
                        }
                        catch (Exception ex)
                        {
                            LogUtility.Error(ex);
                        }
                    }));
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "双机热备事件"
        ///// <summary>
        ///// 当收到主备同步模块的主备切换事件
        ///// </summary>
        //private void OnHotstandbyStateChanged(object sender, HotstandbyStateChangedEventArgs args)
        //{
        //    try
        //    {                
        //        this.View.BeginInvoke(new Action(() =>
        //        {
        //            UpdateHotstandyStateLabel();
        //        }));
        //    }
        //    catch (System.Exception /*ex*/)
        //    {
        //    }
        //}
        #endregion
    }
}
