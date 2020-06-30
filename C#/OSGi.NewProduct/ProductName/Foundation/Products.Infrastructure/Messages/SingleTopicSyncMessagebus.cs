/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 10:10:44 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;

using Acl.MessageBus;

namespace Products.Infrastructure.Messages
{
    /// <summary>
    /// 单一主题的“同步性消息总线”封装类。
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
        /// 构造函数。
        /// </summary>
        /// <param name="msgTopic">指定的消息主题。当指定的消息主题为空时，将使用一个随机的主题。</param>
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
        /// 终结函数。
        /// </summary>
        ~SingleTopicSyncMessagebus()
        {
            this.Dispose(false);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取消息总线关联的主题。
        /// </summary>
        public string Topic { get; private set; }
        #endregion

        #region "Virtual methods"
        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">是否释放托管资源</param>
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
        /// 发布消息。
        /// </summary>
        public void Publish(TEventArgs args, object sender = null)
        {
            _messageBus.Publish(this.Topic, args, sender, false);
        }

        /// <summary>
        /// 订阅消息。
        /// </summary>
        public IDisposable Subscribe(Action<object, TEventArgs> handler)
        {
            if (handler == null) throw new ArgumentNullException();

            var h = _messageBus.Subscribe<TEventArgs>(this.Topic, handler, SubscribeMode.Sync);
            _handlers.Add(h);

            return h;
        }

        /// <summary>
        /// 关闭消息总线，释放资源。
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion
    }
}
