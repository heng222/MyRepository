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
    public static class GlobalMessageBus
    {
        /// <summary>
        /// Ĭ����Ϣ���ߡ�
        /// </summary>
        private static IMessageBus DefaultMessageBus = LocalMessageBus.NewMessageBus();

        #region "���򼴽��ر���Ϣ"
        private static IMessageBus ApplicationExitingMessageBus = LocalMessageBus.NewMessageBus();
        private const string ApplicationExitingMessage = @"local://ApplicationExiting";
        /// <summary>
        /// ���ĳ��򼴽��ر��¼���
        /// </summary>
        public static IDisposable SubscribeApplicationExiting(Action<object, ProcessExitingEventArgs> handler)
        {
            return ApplicationExitingMessageBus.Subscribe<ProcessExitingEventArgs>(
                ApplicationExitingMessage, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// �������򼴽��ر��¼���
        /// </summary>
        public static IMessageResponse PublishApplicationExiting(ProcessExitingEventArgs args, object sender = null)
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
        public static IDisposable SubscribeInternalFrameIncoming(Action<object, FrameIncomingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<FrameIncomingEventArgs<InternalFrame>>(
                InnerFrameIncoming,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡������Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameIncoming(FrameIncomingEventArgs<InternalFrame> frameIncoming, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameIncoming,
                frameIncoming, sender, false);
        }

        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        [SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures")]
        public static IDisposable SubscribeInternalFrameOutgoing(Action<object, FrameOutgoingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe<FrameOutgoingEventArgs<InternalFrame>>(
                InnerFrameOutgoing,
                handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameOutgoing(FrameOutgoingEventArgs<InternalFrame> frameOutgoing, object sender = null)
        {
            var response = InternalFrameMessagBus.Publish(InnerFrameOutgoing,
                frameOutgoing, sender, false);

            return response;
        }

        #endregion

        #region "ͨ��״̬�仯��Ϣ"
        /// <summary>
        /// ͨ��״̬�仯��Ϣ���ߡ�
        /// </summary>
        private static IMessageBus CommStateChangedMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// �豸�����ӷ����仯
        /// </summary>
        private const string NodeConnectionChanged = "local://NDM/ConnectionChanged";
        /// <summary>
        /// ����ͨ��״̬�仯��Ϣ
        /// </summary>
        public static IDisposable SubscribeCommStateChanged(Action<object, CommStateChangedEventArgs> handler)
        {
            return CommStateChangedMessagBus.Subscribe<CommStateChangedEventArgs>(
                NodeConnectionChanged,
               handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ͨ��״̬�仯��Ϣ
        /// </summary>
        public static IMessageResponse PublishCommStateChanged(CommStateChangedEventArgs args, object sender = null)
        {
            return CommStateChangedMessagBus.Publish(NodeConnectionChanged,
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
        /// ϵͳ�¼������������Ϣ��
        /// </summary>
        private const string SystemEventTopic = "local://SystemEventManagement/NewEvent";
        /// <summary>
        /// ���� ϵͳ�¼���������� ��Ϣ��
        /// </summary>
        public static IDisposable SubscribeNewSystemEventGenerated(Action<object, NewSystemEventArgs> handler)
        {
            return DefaultMessageBus.Subscribe<NewSystemEventArgs>(SystemEventTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ���� ϵͳ�¼���������� ��Ϣ��
        /// </summary>
        public static IMessageResponse PublishNewSystemEventGenerated(NewSystemEventArgs args, object sender = null)
        {
            return DefaultMessageBus.Publish(SystemEventTopic, args, sender, false);
        }
        #endregion

        #region "������¼�����Ϣ"
        /// <summary>
        /// ������¼�����������Ϣ��
        /// </summary>
        private const string OperationRecordTopic = "local://OperationRecords/NewLog";
        /// <summary>
        /// ���� ������¼��������� ��Ϣ��
        /// </summary>
        public static IDisposable SubscribeOperationLogChanged(Action<object, OpeationLogCreateOrUpdateEventArgs> handler)
        {
            return DefaultMessageBus.Subscribe<OpeationLogCreateOrUpdateEventArgs>(OperationRecordTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ���� ������¼��������� ��Ϣ��
        /// </summary>
        public static IMessageResponse PublishOperationLogChanged(OpeationLogCreateOrUpdateEventArgs args, object sender = null)
        {
            return DefaultMessageBus.Publish(OperationRecordTopic, args, sender, false);
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
