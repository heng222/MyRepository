/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 15:46:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Drawing;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;
using Products.Plugin1.Properties;
using Products.Presentation;

namespace Products.Plugin1.Controls
{
    [ProductPart(ControlType = PresentationControlType.Plugin1Main)]
    partial class CtrlMain : UserControl
    {
        #region "Field"
        #endregion


        #region "Properties"
        public Icon Icon
        {
            get { return Resources.MyIcon1; }
        }
        #endregion

        #region "Constructor"
        public CtrlMain()
        {
            InitializeComponent();
        }
        #endregion
        
        #region "Private methods"
        #endregion
        
        #region "Public methods"
        #endregion

        #region "控件事件处理函数"

        private void btnGenerateSysEvent_Click(object sender, EventArgs e)
        {
            try
            {
                // 模拟产生一个系统日志；系统将显示此日志并进行持久化。
                var log = new SysEventLog(EventType.CommRecovery, EventLevel.Third, "节点 A 与节点 B 通信中断。");
                GlobalMessageBus.PublishNewSystemEventGenerated(new NewSystemEventArgs(log));

                // 模拟产生一个通信中断消息；系统将显示此消息并自动产生一个系统日志；然后持久化。
                var args = new CommStateChangedEventArgs(false, NodeType.Node1, 16, NodeType.Node2, 18);
                GlobalMessageBus.PublishCommStateChanged(args);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnGenerateOperationLog_Click(object sender, EventArgs e)
        {
            try
            {
                Task.Factory.StartNew(() =>
                {
                    var log = new OperationLog();
                    // 编号必须为零。
                    log.IsManual = true;
                    log.OperationDescription = "Operation X";
                    log.OperationType = OperationType.OperationX;
                    log.TargetDeviceCode = 18;
                    log.ResultDescription = "已发送";

                    // 发布消息。
                    var args = new OpeationLogCreateOrUpdateEventArgs(log);
                    GlobalMessageBus.PublishOperationLogChanged(args);

                    // 延时2秒，产生一个确认。
                    Thread.Sleep(2000);
                    log.ResultDescription = "已执行";
                    log.ResultTimestamp = log.Timestamp + TimeSpan.FromSeconds(10);
                    log.ResultType = OperationResult.Success;
                    GlobalMessageBus.PublishOperationLogChanged(args);
                });
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        #endregion

    }
}
