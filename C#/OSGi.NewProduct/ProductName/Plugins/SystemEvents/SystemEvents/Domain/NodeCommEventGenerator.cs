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

using System.Linq;

using Acl;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.SystemEvents.Utilities;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// 节点间通信事件产生器。
    /// </summary>
    class NodeCommEventGenerator : CompositeDisposable
    {
        public NodeCommEventGenerator()
        {
            this.AddDisposable(GlobalMessageBus.SubscribeCommStateChanged(OnCommStateChanged));
        }

        #region "private methods"

        private void OnCommStateChanged(object sender, CommStateChangedEventArgs args)
        {
            try
            {
                var remoteNode = GlobalServices.Repository.Where<SystemNode>(p => p.Code == args.RemoteNodeCode).FirstOrDefault();

                //  产生事件。
                var eventLog = new SysEventLog();
                eventLog.TypeCode = args.CommState.GetValueOrDefault() ? EventType.CommRecovery : EventType.CommInterruption;
                eventLog.Level = GlobalServices.SEM.GetEventLevel(eventLog.TypeCode);

                var nodeName = remoteNode == null ? string.Format("{0}", args.RemoteNodeCode) : string.Format("{0}_{1}", args.RemoteNodeCode, remoteNode.Name);

                if (args.CommState.GetValueOrDefault())
                {
                    eventLog.Description = string.Format("本节点与远程节点（{0}）通信恢复。", nodeName);
                }
                else
                {
                    eventLog.Description = string.Format("本节点与远程节点（{0}）通信中断。", nodeName);
                }

                // 发布事件
                GlobalMessageBus.PublishNewSystemEventGenerated(new NewSystemEventArgs(eventLog));
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion
    }
}
