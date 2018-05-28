/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2014-9-9 9:59:01 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Diagnostics.CodeAnalysis;
using Acl.MessageBus;
using Products.Infrastructure.Events;
using Products.Infrastructure.Protocol;

namespace Products.Infrastructure.Messages
{
    /// <summary>
    /// 全局消息总线
    /// </summary>
    public static class GlobalMessageBuses
    {
        ///// <summary>
        ///// 默认消息总线。
        ///// </summary>
        //private static IMessageBus DefaultMessageBus = LocalMessageBus.NewMessageBus();

        #region "程序即将关闭消息"
        private static IMessageBus ApplicationExitingMessageBus = LocalMessageBus.NewMessageBus();
        private const string ApplicationExitingMessage = @"local://ApplicationExiting";
        /// <summary>
        /// 订阅程序即将关闭事件。
        /// </summary>
        public static IDisposable SubscribeApplicationExiting(Action<object, EventArgs> handler)
        {
            return ApplicationExitingMessageBus.Subscribe<EventArgs>(
                ApplicationExitingMessage, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// 发布程序即将关闭事件。
        /// </summary>
        public static IMessageResponse PublishApplicationExiting(EventArgs args, object sender = null)
        {
            return ApplicationExitingMessageBus.Publish(ApplicationExitingMessage, args, sender, false);
        }

        #endregion

        #region "系统内部协议帧相关消息"
        /// <summary>
        /// 系统协议帧消息总线。
        /// </summary>
        private static IMessageBus InternalFrameMessagBus = LocalMessageBus.NewMessageBus();

        /// <summary>
        /// 接收到系统内部协议帧
        /// </summary>
        private const string InnerFrameIncoming = "local://Communication/InnerFrameIncoming";

        /// <summary>
        /// 待发送的系统内部协议帧
        /// </summary>
        private const string InnerFrameOutgoing = "local://Communication/InnerFrameOutgoing";

        /// <summary>
        /// 订阅系统内部协议帧进入消息
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameIncoming(Action<object, IncomingFrameEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<IncomingFrameEventArgs<InternalFrame>>(
                InnerFrameIncoming,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布系统内部协议帧进入消息
        /// </summary>
        public static IMessageResponse PublishInternalFrameIncoming(IncomingFrameEventArgs<InternalFrame> frameIncoming, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameIncoming,
                frameIncoming, sender, false);
        }

        /// <summary>
        /// 订阅系统内部协议帧离去消息
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameOutgoing(Action<object, OutgoingFrameEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<OutgoingFrameEventArgs<InternalFrame>>(
                InnerFrameOutgoing,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布系统内部协议帧离去消息
        /// </summary>
        public static IMessageResponse PublishInternalFrameOutgoing(OutgoingFrameEventArgs<InternalFrame> frameOutgoing, object sender = null)
        {
            var response = InternalFrameMessagBus.Publish(InnerFrameOutgoing,
                frameOutgoing, sender, false);

            return response;
        }

        #endregion

        #region "节点连接变化消息"
        /// <summary>
        /// 节点连接变化消息总线。
        /// </summary>
        private static IMessageBus NodeConnectionMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// 设备间连接发生变化
        /// </summary>
        private const string NodeConnectionChanged = "local://NDM/ConnectionChanged";
        /// <summary>
        /// 订阅节点连接变化消息
        /// </summary>
        /// <param name="handler"></param>
        /// <returns></returns>
        public static IDisposable SubscribeNodeConnectionChanged(Action<object, NodeConnectionChangedEventArgs> handler)
        {
            return NodeConnectionMessagBus.Subscribe<NodeConnectionChangedEventArgs>(
                NodeConnectionChanged,
               handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布节点连接变化消息
        /// </summary>
        /// <param name="args"></param>
        /// <param name="sender"></param>
        /// <returns></returns>
        public static IMessageResponse PublishNodeConnectionChanged(NodeConnectionChangedEventArgs args, object sender = null)
        {
            return NodeConnectionMessagBus.Publish(NodeConnectionChanged,
                args, sender, false);
        }
        #endregion
        
        #region "权限管理相关消息"
        /// <summary>
        /// 用户将要切换消息。
        /// </summary>
        private const string UserChangedMessageTopic = "local://AuthorityManagement/UserChanged";
        /// <summary>
        /// 用户已切换消息。
        /// </summary>
        private const string UserChangingMessageTopic = "local://AuthorityManagement/UserChanging";
        /// <summary>
        /// 用户自动登录失败消息。
        /// </summary>
        private const string UserAutoLogonFailedMessageTopic = "local://AuthorityManagement/AutoLogonFailed";
        /// <summary>
        /// 权限管理相关消息总线。
        /// </summary>
        private static IMessageBus AuthorityManagementMessageBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// 订阅用户将要切换事件。
        /// </summary>
        public static IDisposable SubscribeUserChanging(Action<object, EventArgs> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<EventArgs>(UserChangingMessageTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布用户将要切换事件。
        /// </summary>
        public static IMessageResponse PublishUserChanging(EventArgs args, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserChangingMessageTopic, args, sender, false);
        }
        /// <summary>
        /// 订阅用户切换事件。
        /// </summary>
        public static IDisposable SubscribeUserChanged(Action<object, EventArgs> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<EventArgs>(UserChangedMessageTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布用户切换事件。
        /// </summary>
        public static IMessageResponse PublishUserChanged(EventArgs args, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserChangedMessageTopic, args, sender, false);
        }

        /// <summary>
        /// 用户自动登录失败消息。
        /// </summary>
        public static IMessageResponse PublishUserAutoLogonFailed(string errorMessage, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserAutoLogonFailedMessageTopic, errorMessage, sender, false);
        }

        /// <summary>
        /// 订阅用户自动登录失败消息。
        /// </summary>
        /// <param name="handler"></param>
        /// <returns></returns>
        public static IDisposable SubscribeUserAutoLogonFailed(Action<object, string> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<string>(UserAutoLogonFailedMessageTopic, handler, SubscribeMode.Async);
        }
        #endregion


        #region "系统事件相关消息"
        /// <summary>
        /// 系统事件产生消息。
        /// </summary>
        private const string SystemEventTopic = "local://SystemEventManagement/NewEvent";
        /// <summary>
        /// 订阅 新的系统事件 产生消息。
        /// </summary>
        public static IDisposable SubscribeNewSystemEventGenerated(Action<object, NewSystemEventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe<NewSystemEventArgs>(SystemEventTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布 新的系统事件 产生消息。
        /// </summary>
        public static IMessageResponse PublishNewSystemEventGenerated(NewSystemEventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(SystemEventTopic, args, sender, false);
        }

        #endregion


        #region "通信日志Rollover消息"

        /// <summary>
        /// Rollover all communication log.
        /// </summary>
        private const string RolloverAllCommLog = @"Local://MenuMessageHandler/RolloverAllCommLog";
        /// <summary>
        /// 订阅通信日志Rollover事件。
        /// </summary>
        public static IDisposable SubscribeCommLogRollover(Action<object, EventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe<EventArgs>(RolloverAllCommLog, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布通信日志Rollover事件。
        /// </summary>
        public static IMessageResponse PublishCommLogRollover(EventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(RolloverAllCommLog, args, sender, false);
        }
        #endregion
    }
}
