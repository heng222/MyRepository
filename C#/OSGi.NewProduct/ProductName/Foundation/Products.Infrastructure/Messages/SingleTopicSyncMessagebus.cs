/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 10:10:44 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;

using Acl.MessageBus;

namespace Products.Infrastructure.Messages
{
    /// <summary>
    /// ��һ����ġ�ͬ������Ϣ���ߡ���װ�ࡣ
    /// </summary>
    public class SingleTopicSyncMessagebus<TEventArgs> : IDisposable, ISingleTopicMessageBus<TEventArgs>
        where TEventArgs : EventArgs
    {
        #region "Field"

        private bool _disposed = false;

        private IMessageBus _messageBus;

        private List<IDisposable> _handlers = new List<IDisposable>();
        #endregion

        #region "Constructor"

        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="msgTopic">ָ������Ϣ���⡣��ָ������Ϣ����Ϊ��ʱ����ʹ��һ����������⡣</param>
        public SingleTopicSyncMessagebus(string msgTopic = null)
        {
            if (string.IsNullOrWhiteSpace(msgTopic))
            {
                this.Topic = string.Format("SingleTopic_{0}", Guid.NewGuid());
            }
            else
            {
                this.Topic = msgTopic;
            }

            _messageBus = LocalMessageBus.NewMessageBus();
        }

        /// <summary>
        /// �սắ����
        /// </summary>
        ~SingleTopicSyncMessagebus()
        {
            this.Dispose(false);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��Ϣ���߹��������⡣
        /// </summary>
        public string Topic { get; private set; }
        #endregion

        #region "Virtual methods"
        /// <summary>
        /// ������������ʹ�õ���Դ��
        /// </summary>
        /// <param name="disposing">�Ƿ��ͷ��й���Դ</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    _handlers.ForEach(p => p.Dispose());

                    _messageBus.Shutdown();
                }

                _disposed = true;
            }
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// ������Ϣ��
        /// </summary>
        public void Publish(TEventArgs args, object sender = null)
        {
            _messageBus.Publish(this.Topic, args, sender, false);
        }

        /// <summary>
        /// ������Ϣ��
        /// </summary>
        public IDisposable Subscribe(Action<object, TEventArgs> handler)
        {
            if (handler == null) throw new ArgumentNullException();

            var h = _messageBus.Subscribe<TEventArgs>(this.Topic, handler, SubscribeMode.Sync);
            _handlers.Add(h);

            return h;
        }

        /// <summary>
        /// �ر���Ϣ���ߣ��ͷ���Դ��
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion
    }
}
