/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-9-9 9:59:01 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;

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
        private const string ApplicationExitingMessage = @"local://Product/ApplicationExiting";
        /// <summary>
        /// ���ĳ��򼴽��ر��¼���
        /// </summary>
        public static IDisposable SubscribeApplicationExiting(Action<object, ProcessExitingEventArgs> handler)
        {
            return ApplicationExitingMessageBus.Subscribe(ApplicationExitingMessage, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// �������򼴽��ر��¼���
        /// </summary>
        public static IMessageResponse PublishApplicationExiting(ProcessExitingEventArgs args, object sender = null)
        {
            return ApplicationExitingMessageBus.Publish(ApplicationExitingMessage, args, sender, false);
        }

        #endregion

        #region "����Դ״̬�仯��Ϣ"
        private const string DbSourceStateChangedTopic = @"local://Product/System/DbSourceStateChangedTopic";
        /// <summary>
        /// ��������Դ״̬�仯��Ϣ��
        /// </summary>
        public static IDisposable SubscribeDbSourceStateChanged(Action<object, DbSourceStateChangedEventArgs> handler)
        {
            return DefaultMessageBus.Subscribe(DbSourceStateChangedTopic, handler, SubscribeMode.Async);
        }
        /// <summary>
        /// ��������Դ״̬�仯��Ϣ��
        /// </summary>
        public static IMessageResponse PublishDbSourceStateChanged(DbSourceStateChangedEventArgs args, object sender = null)
        {
            return DefaultMessageBus.Publish(DbSourceStateChangedTopic, args, sender, true);
        }
        #endregion

        #region "�����շ���Ϣ"
        /// <summary>
        /// �����շ���Ϣ���ߡ�
        /// </summary>
        static IMessageBus DataIoMessagBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// ��Ϣ�����յ�����
        /// </summary>
        const string FrameIncoming = "local://Product/Communication/DataFrameIncoming";
        /// <summary>
        /// ��Ϣ����������
        /// </summary>
        const string FrameOutgoing = "local://Product/Communication/DataFrameOutgoing";

        /// <summary>
        /// �������ݽ�����Ϣ
        /// </summary>
        public static IDisposable SubscribeDataIncoming(Action<object, DataIncomingEventArgs> handler)
        {
            return DataIoMessagBus.Subscribe(FrameIncoming, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// �������ݽ�����Ϣ
        /// </summary>
        public static IMessageResponse PublishDataIncoming(DataIncomingEventArgs args, object sender = null)
        {
            return DataIoMessagBus.Publish(FrameIncoming, args, sender, false);
        }

        /// <summary>
        /// ����������ȥ��Ϣ
        /// </summary>
        public static IDisposable SubscribeDataOutgoing(Action<object, DataOutgoingEventArgs> handler)
        {
            return DataIoMessagBus.Subscribe(FrameOutgoing, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����������ȥ��Ϣ
        /// </summary>
        public static IMessageResponse PublishDataOutgoing(DataOutgoingEventArgs args, object sender = null)
        {
            return DataIoMessagBus.Publish(FrameOutgoing, args, sender, false);
        }

        #endregion

        #region "�ڲ�Э��֡�շ���Ϣ"
        /// <summary>
        /// ϵͳЭ��֡��Ϣ���ߡ�
        /// </summary>
        private static IMessageBus InternalFrameMessagBus = LocalMessageBus.NewMessageBus();

        /// <summary>
        /// ���յ�ϵͳ�ڲ�Э��֡
        /// </summary>
        private const string InnerFrameIncoming = "local://Product/Communication/InnerFrameIncoming";

        /// <summary>
        /// �����͵�ϵͳ�ڲ�Э��֡
        /// </summary>
        private const string InnerFrameOutgoing = "local://Product/Communication/InnerFrameOutgoing";

        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡������Ϣ
        /// </summary>
        public static IDisposable SubscribeInternalFrameIncoming(Action<object, FrameIncomingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe(InnerFrameIncoming, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡������Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameIncoming(FrameIncomingEventArgs<InternalFrame> frameIncoming, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameIncoming, frameIncoming, sender, false);
        }

        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        public static IDisposable SubscribeInternalFrameOutgoing(Action<object, FrameOutgoingEventArgs<InternalFrame>> handler)
        {
            return InternalFrameMessagBus.Subscribe(InnerFrameOutgoing, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ϵͳ�ڲ�Э��֡��ȥ��Ϣ
        /// </summary>
        public static IMessageResponse PublishInternalFrameOutgoing(FrameOutgoingEventArgs<InternalFrame> frameOutgoing, object sender = null)
        {
            return InternalFrameMessagBus.Publish(InnerFrameOutgoing, frameOutgoing, sender, false);
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
        private const string NodeConnectionChanged = "local://Product/NDM/ConnectionChanged";
        /// <summary>
        /// ����ͨ��״̬�仯��Ϣ
        /// </summary>
        public static IDisposable SubscribeCommStateChanged(Action<object, CommStateChangedEventArgs> handler)
        {
            return CommStateChangedMessagBus.Subscribe(
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
        private const string UserChangedMessageTopic = "local://Product/AuthorityManagement/UserChanged";
        /// <summary>
        /// �û����л���Ϣ��
        /// </summary>
        private const string UserChangingMessageTopic = "local://Product/AuthorityManagement/UserChanging";
        /// <summary>
        /// �û��Զ���¼ʧ����Ϣ��
        /// </summary>
        private const string UserAutoLogonFailedMessageTopic = "local://Product/AuthorityManagement/AutoLogonFailed";
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
        public static IDisposable SubscribeUserAutoLogonFailed(Action<object, string> handler)
        {
            return AuthorityManagementMessageBus.Subscribe<string>(UserAutoLogonFailedMessageTopic, handler, SubscribeMode.Async);
        }
        #endregion

        #region "ϵͳ�¼������Ϣ"
        private static IMessageBus SystemEventMessageBus = LocalMessageBus.NewMessageBus();
        /// <summary>
        /// ϵͳ�¼������������Ϣ��
        /// </summary>
        private const string SystemEventTopic = "local://Product/SystemEventManagement/NewEvent";
        /// <summary>
        /// ���� ϵͳ�¼���������� ��Ϣ��
        /// </summary>
        public static IDisposable SubscribeNewSystemEventGenerated(Action<object, NewSystemEventArgs> handler)
        {
            return SystemEventMessageBus.Subscribe(SystemEventTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ���� ϵͳ�¼���������� ��Ϣ��
        /// </summary>
        public static IMessageResponse PublishNewSystemEventGenerated(NewSystemEventArgs args, object sender = null)
        {
            return SystemEventMessageBus.Publish(SystemEventTopic, args, sender, false);
        }
        #endregion

        #region "������¼�����Ϣ"
        /// <summary>
        /// ������¼�����������Ϣ��
        /// </summary>
        private const string OperationRecordTopic = "local://Product/OperationRecords/NewLog";
        /// <summary>
        /// ���� ������¼��������� ��Ϣ��
        /// </summary>
        public static IDisposable SubscribeOperationLogChanged(Action<object, OpeationLogCreateOrUpdateEventArgs> handler)
        {
            return SystemEventMessageBus.Subscribe(OperationRecordTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ���� ������¼��������� ��Ϣ��
        /// </summary>
        public static IMessageResponse PublishOperationLogChanged(OpeationLogCreateOrUpdateEventArgs args, object sender = null)
        {
            return SystemEventMessageBus.Publish(OperationRecordTopic, args, sender, false);
        }
        #endregion


        #region "ͨ����־�����Ϣ"
        /// <summary>
        /// Rollover all communication log.
        /// </summary>
        private const string RolloverAllCommLog = @"Local://Product/RolloverAllCommLog";
        /// <summary>
        /// ����ͨ����־Rollover�¼���
        /// </summary>
        public static IDisposable SubscribeCommLogRollover(Action<object, EventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe(RolloverAllCommLog, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ͨ����־Rollover�¼���
        /// </summary>
        public static IMessageResponse PublishCommLogRollover(EventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(RolloverAllCommLog, args, sender, false);
        }

        /// <summary>
        /// һ����Ϣ���⣬���ڱ�ʾ�����µ�ͨ������־��
        /// </summary>
        private const String CommLogCreatedTopic = @"Local://Product/NewCommLogCreated";
        /// <summary>
        /// ����ͨ������־�����¼���
        /// </summary>
        public static IDisposable SubscribeCommLogCreated(Action<object, CommLogCreatedEventArgs> handler)
        {
            return LocalMessageBus.Current.Subscribe(CommLogCreatedTopic, handler, SubscribeMode.Sync);
        }
        /// <summary>
        /// ����ͨ������־�����¼���
        /// </summary>
        public static IMessageResponse PublishCommLogCreated(CommLogCreatedEventArgs args, object sender = null)
        {
            return LocalMessageBus.Current.Publish(CommLogCreatedTopic, args, sender, false);
        }

        #endregion
    }
}
