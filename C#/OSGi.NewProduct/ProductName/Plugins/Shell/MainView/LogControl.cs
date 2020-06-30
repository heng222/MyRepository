using System;
using System.Collections.Generic;
using System.Windows.Forms;

using Acl.Log;
using Acl.Log.Presentation;

using Platform.Presentation;

using Products.Infrastructure.Types;
using Products.Presentation;

namespace Products.Shell.MainView
{
    /// <summary>
    /// ������ͨ��־��ͼ
    /// </summary>
    [ProductPart(ControlType = PresentationControlType.ApplicationLog, ActivateTab = true)]
    public partial class LogControl : UserControl, IControlOptimizer
    {
        private LogControlMultiPages _logMonitor = new LogControlMultiPages();

        /// <summary>
        /// ���캯��
        /// </summary>
        public LogControl()
        {
            InitializeComponent();

            this.CreateHandle();

            _logMonitor.LogPath = string.Format(@"{0}Log\All\", AppDomain.CurrentDomain.BaseDirectory);
            this.Controls.Add(_logMonitor);
            _logMonitor.Dock = DockStyle.Fill;
        }

        #region "�˵��¼�"

        #endregion
        /// <summary>
        /// �ڿؼ�����ʾ��־ʵ����Ϣ
        /// </summary>
        public void ShowLog(IEnumerable<LogEntity> logs)
        {
            try
            {
                _logMonitor.ShowLog(logs);
            }
            catch (System.Exception /*ex*/)
            {
            }
        }
        /// <summary>
        /// 
        /// </summary>
        public void OptimizeIdle()
        {
            try
            {
                _logMonitor.DebugLogAlive = false;
            }
            catch (System.Exception /*ex*/)
            {

            }
        }
    }
}
