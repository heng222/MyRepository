/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-9-9 9:59:01 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
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
    /// ȫ����Ϣ����
    /// </summary>
    public static class GlobalMessageBuses
    {
        ///// <summary>
        ///// Ĭ����Ϣ���ߡ�
        ///// </summary>
        //private static IMessageBus DefaultMessageBus = LocalMessageBus.NewMessageBus();

        #region "���򼴽��ر���Ϣ"
        private static IMessageBus ApplicationExitingMessageBus = LocalMessageBus.NewMessageBus();
        private const string ApplicationExitingMessage = @"local://ApplicationExiting";
        /// <summary>
        /// ���ĳ��򼴽��ر��¼���
        /// </summary>
        public static IDisposable SubscribeApplicationExiting(Action<object, EventArgs> handler)
        {
            return ApplicationExitingMessageBus.Subscribe<EventArgs>(
                ApplicationExitingMessage, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// �������򼴽��ر��¼���
        /// </summary>
        public static IMessageResponse PublishApplicationExiting(EventArgs args, object sender = null)
        {
            return ApplicationExitingMessageBus.Publish(ApplicationExitingMessage, args, sender, false);
        }

        #endregion

        #region "ϵͳ�ڲ�Э��֡�����Ϣ"
        /// <summary>
        /// ϵͳЭ��֡��Ϣ���ߡ�
        /// </summary>
        private static IMessageBus InternalFrameMessagBus = LocalMessageBus.NewMessageBus();

        /// <summary>
        /// ���յ�ϵͳ�ڲ�Э��֡
        /// </summary>
        private const string InnerFrameIncoming = "local://Communication/InnerFrameIncoming";

        /// <summary>
        /// �����͵�ϵͳ�ڲ�Э��֡
        /// </summary>
        private const string InnerFrameOutgoing = "local://Communication/InnerFrameOutgoing";

        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡������Ϣ
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameIncoming(Action<object, IncomingFrameEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<IncomingFrameEventArgs<InternalFrame>>(
                InnerFrameIncoming,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡������Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameIncoming(IncomingFrameEventArgs<InternalFrame> frameIncoming, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameIncoming,
                frameIncoming, sender, false);
        }

        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameOutgoing(Action<object, OutgoingFrameEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<OutgoingFrameEventArgs<InternalFrame>>(
                InnerFrameOutgoing,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameOutgoing(OutgoingFrameEventArgs<InternalFrame> frameOutgoing, object sender = null)
        {
            var response = InternalFrameMessagBus.Publish(InnerFrameOutgoing,
                frameOutgoing, sender, false);

            return response;
        }

        #endregion

        #region "�ڵ����ӱ仯��Ϣ"
        /// <summary>
        /// �ڵ����ӱ仯��Ϣ���ߡ�
        /// </summary>
        private static IMessageBus NodeConnectionMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// �豸�����ӷ����仯
        /// </summary>
        private const string NodeConnectionChanged = "local://NDM/ConnectionChanged";
        /// <summary>
        /// ���Ľڵ����ӱ仯��Ϣ
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
        /// �����ڵ����ӱ仯��Ϣ
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
        
        #region "Ȩ�޹��������Ϣ"
        /// <summary>
        /// �û���Ҫ�л���Ϣ��
        /// </summary>
        private const string UserChangedMessageTopic = "local://AuthorityManagement/UserChanged";
        /// <summary>
        /// �û����л���Ϣ��
        /// </summary>
        private const string UserChangingMessageTopic = "local://AuthorityManagement/UserChanging";
        /// <summary>
        /// �û��Զ���¼ʧ����Ϣ��
        /// </summary>
        private const string UserAutoLogonFailedMessageTopic = "local://AuthorityManagement/AutoLogonFailed";
        /// <summary>
        /// Ȩ�޹��������Ϣ���ߡ�
        /// </summary>
        private static IMessageBus AuthorityManagementMessageBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// �����û���Ҫ�л��¼���
        /// </summary>
        public static IDisposable SubscribeUserChanging(Action<object, EventArgs> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<EventArgs>(UserChangingMessageTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// �����û���Ҫ�л��¼���
        /// </summary>
        public static IMessageResponse PublishUserChanging(EventArgs args, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserChangingMessageTopic, args, sender, false);
        }
        /// <summary>
        /// �����û��л��¼���
        /// </summary>
        public static IDisposable SubscribeUserChanged(Action<object, EventArgs> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<EventArgs>(UserChangedMessageTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// �����û��л��¼���
        /// </summary>
        public static IMessageResponse PublishUserChanged(EventArgs args, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserChangedMessageTopic, args, sender, false);
        }

        /// <summary>
        /// �û��Զ���¼ʧ����Ϣ��
        /// </summary>
        public static IMessageResponse PublishUserAutoLogonFailed(string errorMessage, object sender = null)
        {
            return AuthorityManagementMessageBus.Publish(UserAutoLogonFailedMessageTopic, errorMessage, sender, false);
        }

        /// <summary>
        /// �����û��Զ���¼ʧ����Ϣ��
        /// </summary>
        /// <param name="handler"></param>
        /// <returns></returns>
        public static IDisposable SubscribeUserAutoLogonFailed(Action<object, string> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<string>(UserAutoLogonFailedMessageTopic, handler, SubscribeMode.Async);
        }
        #endregion


        #region "ϵͳ�¼������Ϣ"
        /// <summary>
        /// ϵͳ�¼�������Ϣ��
        /// </summary>
        private const string SystemEventTopic = "local://SystemEventManagement/NewEvent";
        /// <summary>
        /// ���� �µ�ϵͳ�¼� ������Ϣ��
        /// </summary>
        public static IDisposable SubscribeNewSystemEventGenerated(Action<object, NewSystemEventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe<NewSystemEventArgs>(SystemEventTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ���� �µ�ϵͳ�¼� ������Ϣ��
        /// </summary>
        public static IMessageResponse PublishNewSystemEventGenerated(NewSystemEventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(SystemEventTopic, args, sender, false);
        }

        #endregion


        #region "ͨ����־Rollover��Ϣ"

        /// <summary>
        /// Rollover all communication log.
        /// </summary>
        private const string RolloverAllCommLog = @"Local://MenuMessageHandler/RolloverAllCommLog";
        /// <summary>
        /// ����ͨ����־Rollover�¼���
        /// </summary>
        public static IDisposable SubscribeCommLogRollover(Action<object, EventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe<EventArgs>(RolloverAllCommLog, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ͨ����־Rollover�¼���
        /// </summary>
        public static IMessageResponse PublishCommLogRollover(EventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(RolloverAllCommLog, args, sender, false);
        }
        #endregion
    }
}
