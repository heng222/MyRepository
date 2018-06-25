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
    /// 程序普通日志视图
    /// </summary>
    [ProductPart(ControlType = PresentationControlType.ApplicationLog, ActivateTab= true)]
    public partial class LogControl : UserControl, IControlOptimizer
    {
        private LogControlMultiPages _logMonitor = new LogControlMultiPages();

        /// <summary>
        /// 构造函数
        /// </summary>
        public LogControl()
        {
            InitializeComponent();

            this.CreateHandle();
            this.Controls.Add(_logMonitor);
            _logMonitor.Dock = DockStyle.Fill;
        }
        
        #region "菜单事件"
        
        #endregion
        /// <summary>
        /// 在控件上显示日志实体信息
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
                _logMonitor.DebugLogAlived = false;
            }
            catch (System.Exception /*ex*/)
            {
            	
            }
        }
    }
}
