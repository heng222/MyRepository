/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        /// ������ʾ��ǰʱ�䡣
        /// </summary>
        private Timer _currentTimer;

        /// <summary>
        /// ״̬��
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

            //// �������ݿ��¼�
            //DbConnectionMonitor.Current.SubscribeConnectionStateChanged(OnDbConnectionChanged);
            //this.OnDbConnectionChanged(DbConnectionMonitor.Current.State ?? ConnectionState.Closed);

            // ��������״̬�仯�¼�
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
            _statusLabelUserCode.Text = "�û�ID��";
            _statusLabelUserCode.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelUserCode.Click += OnUserCodeOrNameLableClick;

            // stslbUserName
            _statusLabelUserName.AutoSize = false;
            _statusLabelUserName.Width = 120;
            _statusLabelUserName.Text = "�û�����";
            _statusLabelUserName.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelUserName.Click += OnUserCodeOrNameLableClick;

            //// stslbUserRole
            //_statusLabelUserRole.Visible = NodeContextManager.Current.ControlTypes.Contains(PresentationControlType.Logon);
            //_statusLabelUserRole.AutoSize = false;
            //_statusLabelUserRole.Width = 130;
            //_statusLabelUserRole.Text = "��ɫ��";
            //_statusLabelUserRole.TextAlign = ContentAlignment.MiddleCenter;

            //// stslMachineName
            //_statusLabelNodeName.AutoSize = false;
            //_statusLabelNodeName.Width = 180;
            //_statusLabelNodeName.Text = "�豸���ƣ�";
            //_statusLabelNodeName.TextAlign = ContentAlignment.MiddleCenter;

            //// stslbUserStation
            //_statusLabelLocation.Visible = NodeContextManager.Current.ControlTypes.Contains(PresentationControlType.Logon);
            //_statusLabelLocation.AutoSize = false;
            //_statusLabelLocation.Width = 150;
            //_statusLabelLocation.Text = "��¼λ��";
            //_statusLabelLocation.TextAlign = ContentAlignment.MiddleCenter;

            //// ���ݿ�״̬��
            //_statusLabelDbText.Text = "���ݿ�״̬";
            //_statusLabelDbText.TextAlign = ContentAlignment.MiddleCenter;
            //_statusLabelDbState.Text = "     ";
            //_statusLabelDbState.AutoToolTip = false;
            //_statusLabelDbState.BackColor = Color.Black;

            //// ����״̬
            //_statusLabelHotstandbyText.Visible = NodeContextManager.HasSibling();
            //_statusLabelHotstandbyText.Text = "      ����״̬";
            //_statusLabelHotstandbyText.TextAlign = ContentAlignment.MiddleCenter;
            //_statusLabelHotstandbyState.Visible = NodeContextManager.HasSibling();
            //_statusLabelHotstandbyState.Text = "       ";
            //_statusLabelHotstandbyState.AutoToolTip = true;
            //_statusLabelHotstandbyState.BackColor = Color.Black;

            // ��¼ʱ��
            _statusLabelLanuchTime.AutoSize = false;
            _statusLabelLanuchTime.Visible = false;
            _statusLabelLanuchTime.Width = 200;
            _statusLabelLanuchTime.Text = "��¼ʱ��";
            _statusLabelLanuchTime.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelLanuchTime.Click += OnTimeLabelClick;

            // ��ǰʱ��
            _statusLabelCurrentTime.AutoSize = false;
            _statusLabelCurrentTime.Width = 200;
            _statusLabelCurrentTime.Text = "��ǰʱ��";
            _statusLabelCurrentTime.TextAlign = ContentAlignment.MiddleCenter;
            _statusLabelCurrentTime.Click += OnTimeLabelClick;

            _currentTimer = new Timer() { Interval = 500, Enabled = true };
            _currentTimer.Tick += OnCurrentTimerTick;

            // stslbVersion
            _statusLabelVersion.Text = "�汾�ţ�";

            // stslbProjectName
            _statusLabelProjectName.AutoSize = false;
            _statusLabelProjectName.Text = "��Ŀ��������";
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
                    _statusLabelUserCode.Text = string.Format("�û���ţ�{0}", GlobalServices.UAC.CurrentUserCode);
                    _statusLabelUserName.Text = string.Format("�û����ƣ�{0}", GlobalServices.UAC.CurrentUserName);
                }
                else
                {
                    _statusLabelUserCode.Text = string.Empty;
                    _statusLabelUserName.Text = string.Empty;
                }
                //_statusLabelUserRole.Text = string.Format("��ɫ��{0}", CurrentUserDetail.Instance.RoleName);
                ////_statusLabelDepart.Text = string.Format("���ţ�{0}", CurrentUserDetail.Instance.DepartName);
                //_statusLabelNodeName.Text = string.Format("�ڵ����ƣ�{0}", NodeContextManager.Current.Name);

                //if (CurrentUserDetail.Instance.OwnerStationID == Department.Center)
                //{
                //    _statusLabelLocation.Text = string.Format("λ�ã���������");
                //}
                //else
                //{
                //    _statusLabelLocation.Text = string.Format("λ�ã�{0}", CurrentUserDetail.Instance.OwnerStationName);
                //}

                _statusLabelLanuchTime.Text = string.Format("��¼ʱ�䣺{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));


                var sysAttri = ServiceManager.Current.Get<ISystemProperty>();
                _statusLabelVersion.Text = string.Format(" �汾�ţ�v{0}", sysAttri.ProductStringVersion);
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
            //_statusLabelDbState.ToolTipText = DbConnectionMonitor.Current.Connected ? "����" : "�Ͽ�";
        }

        private void UpdateHotstandyStateLabel()
        {
            //var state = HotStandbyManager.CurrentState;

            //if (state == NodeHotStandbyState.Main)
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.DarkGreen;
            //    _statusLabelHotstandbyState.ToolTipText = "����";
            //}
            //else if (state == NodeHotStandbyState.Back)
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.Yellow;
            //    _statusLabelHotstandbyState.ToolTipText = "����";
            //}
            //else
            //{
            //    _statusLabelHotstandbyState.BackColor = Color.Black;
            //    _statusLabelHotstandbyState.ToolTipText = "δ֪";
            //}
        }

        private void OnUserChanged(object sender, EventArgs e)
        {
            try
            {
                // ����״̬��
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
            _statusStrip.Visible = true; // ״̬���ɼ���
            _statusStrip.SizingGrip = this.View.InitalTitleVisible;
        }
        #endregion

        #region "�����¼�"

        private void OnOwnerViewLoad(object sender, EventArgs e)
        {
            try
            {
                // �����û��л��¼���
                GlobalMessageBus.SubscribeUserChanged(OnUserChanged);

                // ����״̬����
                this.UpdateStatusBar();
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "�ؼ��¼�"
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
                    _statusLabelCurrentTime.Text = string.Format("��ǰʱ�䣺{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
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
                _statusLabelCurrentTime.Text = string.Format("��ǰʱ�䣺{0}", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
            }
        }
        #endregion

        #region "���ݿ����ӱ仯�¼�"
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

        #region "˫���ȱ��¼�"
        ///// <summary>
        ///// ���յ�����ͬ��ģ��������л��¼�
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
