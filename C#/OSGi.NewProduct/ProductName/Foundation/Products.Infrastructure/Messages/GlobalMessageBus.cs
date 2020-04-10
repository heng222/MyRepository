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
    public static class GlobalMessageBus
    {
        /// <summary>
        /// 默认消息总线。
        /// </summary>
        private static IMessageBus DefaultMessageBus = LocalMessageBus.NewMessageBus();

        #region "程序即将关闭消息"
        private static IMessageBus ApplicationExitingMessageBus = LocalMessageBus.NewMessageBus();
        private const string ApplicationExitingMessage = @"local://Product/ApplicationExiting";
        /// <summary>
        /// 订阅程序即将关闭事件。
        /// </summary>
        public static IDisposable SubscribeApplicationExiting(Action<object, ProcessExitingEventArgs> handler)
        {
            return ApplicationExitingMessageBus.Subscribe<ProcessExitingEventArgs>(
                ApplicationExitingMessage, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// 发布程序即将关闭事件。
        /// </summary>
        public static IMessageResponse PublishApplicationExiting(ProcessExitingEventArgs args, object sender = null)
        {
            return ApplicationExitingMessageBus.Publish(ApplicationExitingMessage, args, sender, false);
        }

        #endregion
        
        #region "数据收发消息"
        /// <summary>
        /// 数据收发消息总线。
        /// </summary>
        static IMessageBus DataIoMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// 消息：接收到数据
        /// </summary>
        const string FrameIncoming = "local://Product/Communication/DataFrameIncoming";
        /// <summary>
        /// 消息：发送数据
        /// </summary>
        const string FrameOutgoing = "local://Product/Communication/DataFrameOutgoing";

        /// <summary>
        /// 订阅数据进入消息
        /// </summary>
        public static IDisposable SubscribeDataIncoming(Action<object, DataIncomingEventArgs> handler)
        {
            return DataIoMessagBus.Subscribe<DataIncomingEventArgs>(FrameIncoming, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布数据进入消息
        /// </summary>
        public static IMessageResponse PublishDataIncoming(DataIncomingEventArgs args, object sender = null)
        {
            return DataIoMessagBus.Publish(FrameIncoming, args, sender, false);
        }

        /// <summary>
        /// 订阅数据离去消息
        /// </summary>
        public static IDisposable SubscribeDataOutgoing(Action<object, DataOutgoingEventArgs> handler)
        {
            return DataIoMessagBus.Subscribe<DataOutgoingEventArgs>(FrameOutgoing,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布数据离去消息
        /// </summary>
        public static IMessageResponse PublishDataOutgoing(DataOutgoingEventArgs args, object sender = null)
        {
            return DataIoMessagBus.Publish(FrameOutgoing, args, sender, false);
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
        private const string InnerFrameIncoming = "local://Product/Communication/InnerFrameIncoming";

        /// <summary>
        /// 待发送的系统内部协议帧
        /// </summary>
        private const string InnerFrameOutgoing = "local://Product/Communication/InnerFrameOutgoing";

        /// <summary>
        /// 订阅系统内部协议帧进入消息
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameIncoming(Action<object, FrameIncomingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<FrameIncomingEventArgs<InternalFrame>>(
                InnerFrameIncoming,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布系统内部协议帧进入消息
        /// </summary>
        public static IMessageResponse PublishInternalFrameIncoming(FrameIncomingEventArgs<InternalFrame> frameIncoming, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameIncoming,
                frameIncoming, sender, false);
        }

        /// <summary>
        /// 订阅系统内部协议帧离去消息
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameOutgoing(Action<object, FrameOutgoingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<FrameOutgoingEventArgs<InternalFrame>>(
                InnerFrameOutgoing,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布系统内部协议帧离去消息
        /// </summary>
        public static IMessageResponse PublishInternalFrameOutgoing(FrameOutgoingEventArgs<InternalFrame> frameOutgoing, object sender = null)
        {
            var response = InternalFrameMessagBus.Publish(InnerFrameOutgoing,
                frameOutgoing, sender, false);

            return response;
        }

        #endregion

        #region "通信状态变化消息"
        /// <summary>
        /// 通信状态变化消息总线。
        /// </summary>
        private static IMessageBus CommStateChangedMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// 设备间连接发生变化
        /// </summary>
        private const string NodeConnectionChanged = "local://Product/NDM/ConnectionChanged";
        /// <summary>
        /// 订阅通信状态变化消息
        /// </summary>
        public static IDisposable SubscribeCommStateChanged(Action<object, CommStateChangedEventArgs> handler)
        {
            return CommStateChangedMessagBus.Subscribe<CommStateChangedEventArgs>(
                NodeConnectionChanged,
               handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布通信状态变化消息
        /// </summary>
        public static IMessageResponse PublishCommStateChanged(CommStateChangedEventArgs args, object sender = null)
        {
            return CommStateChangedMessagBus.Publish(NodeConnectionChanged,
                args, sender, false);
        }
        #endregion
        
        #region "权限管理相关消息"
        /// <summary>
        /// 用户将要切换消息。
        /// </summary>
        private const string UserChangedMessageTopic = "local://Product/AuthorityManagement/UserChanged";
        /// <summary>
        /// 用户已切换消息。
        /// </summary>
        private const string UserChangingMessageTopic = "local://Product/AuthorityManagement/UserChanging";
        /// <summary>
        /// 用户自动登录失败消息。
        /// </summary>
        private const string UserAutoLogonFailedMessageTopic = "local://Product/AuthorityManagement/AutoLogonFailed";
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
        /// 系统事件产生或更新消息。
        /// </summary>
        private const string SystemEventTopic = "local://Product/SystemEventManagement/NewEvent";
        /// <summary>
        /// 订阅 系统事件产生或更新 消息。
        /// </summary>
        public static IDisposable SubscribeNewSystemEventGenerated(Action<object, NewSystemEventArgs> handler)
        {
            return DefaultMessageBus.Subscribe<NewSystemEventArgs>(SystemEventTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布 系统事件产生或更新 消息。
        /// </summary>
        public static IMessageResponse PublishNewSystemEventGenerated(NewSystemEventArgs args, object sender = null)
        {
            return DefaultMessageBus.Publish(SystemEventTopic, args, sender, false);
        }
        #endregion

        #region "操作记录相关消息"
        /// <summary>
        /// 操作记录产生或更新消息。
        /// </summary>
        private const string OperationRecordTopic = "local://Product/OperationRecords/NewLog";
        /// <summary>
        /// 订阅 操作记录产生或更新 消息。
        /// </summary>
        public static IDisposable SubscribeOperationLogChanged(Action<object, OpeationLogCreateOrUpdateEventArgs> handler)
        {
            return DefaultMessageBus.Subscribe<OpeationLogCreateOrUpdateEventArgs>(OperationRecordTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布 操作记录产生或更新 消息。
        /// </summary>
        public static IMessageResponse PublishOperationLogChanged(OpeationLogCreateOrUpdateEventArgs args, object sender = null)
        {
            return DefaultMessageBus.Publish(OperationRecordTopic, args, sender, false);
        }
        #endregion


        #region "通信日志Rollover消息"
        /// <summary>
        /// Rollover all communication log.
        /// </summary>
        private const string RolloverAllCommLog = @"Local://Product/RolloverAllCommLog";
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

        /// <summary>
        /// 一个消息主题，用于表示产生新的通信流日志。
        /// </summary>
        private const String CommLogCreatedTopic = @"Local://Product/NewCommLogCreated";
        /// <summary>
        /// 订阅通信流日志产生事件。
        /// </summary>
        public static IDisposable SubscribeCommLogCreated(Action<object, CommLogCreatedEventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe<CommLogCreatedEventArgs>(CommLogCreatedTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// 发布通信流日志产生事件。
        /// </summary>
        public static IMessageResponse PublishCommLogCreated(CommLogCreatedEventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(CommLogCreatedTopic, args, sender, false);
        }

        #endregion
    }
}
