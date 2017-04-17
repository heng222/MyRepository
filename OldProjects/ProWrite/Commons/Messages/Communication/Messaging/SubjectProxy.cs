using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Diagnostics;

namespace System.Communication.Messaging
{
    /// <summary>
    /// 消息事件处理器的客户端代理
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    [Serializable]
    public class SubjectProxy<TMessage> : MarshalByRefObject
    {
        private Subject<TMessage> Inner;
        private ObserverWrapper<TMessage> wraper;

        public readonly bool IsNeedAsyncRegister = true;

        private WeakReference<WaitCallback> registerRemoteMessageCallback;
        private WeakReference<WaitCallback> unRegisterRemoteMessageCallback;
        private WeakReference<ObserverHandler<TMessage>> localObserver;

        public SubjectProxy(Subject<TMessage> inner,bool isNeedAsyncRegister)
        {
            this.Inner = inner;
            wraper = new ObserverWrapper<TMessage>();
            localObserver = new WeakReference<ObserverHandler<TMessage>>(this.wraper.Register);
            this.IsNeedAsyncRegister = isNeedAsyncRegister;

            if (isNeedAsyncRegister)
            {
                registerRemoteMessageCallback = new WeakReference<WaitCallback>(this.RegisterRemoteMessage);
                unRegisterRemoteMessageCallback = new WeakReference<WaitCallback>(this.UnRegisterRemoteMessage);
            }

        }

        /// <summary>
        /// 注册或移除消息事件处理器的真实代理
        /// </summary>
        public event ObserverHandler<TMessage> Observers
        {
            add
            {
                if (IsNeedAsyncRegister)
                    ThreadPool.QueueUserWorkItem(this.registerRemoteMessageCallback);
                else
                    Inner.Observers += localObserver.Target;

                wraper.LocalHandler += value;
            }
            remove
            {
                if (IsNeedAsyncRegister)
                    ThreadPool.QueueUserWorkItem(this.unRegisterRemoteMessageCallback);
                else
                    Inner.Observers -= localObserver.Target;

                wraper.LocalHandler -= value;
            }
        }

        private void RegisterRemoteMessage(object o)
        {
            try
            {
                Inner.RegisterObserver(localObserver);
            }
            catch (SocketException ex)
            {
                Debug.WriteLine(ex);
            }
        }

        private void UnRegisterRemoteMessage(object o)
        {
            try
            {
                Inner.UnRegisterObserver(localObserver);
            }
            catch (SocketException ex)
            {
                Debug.WriteLine(ex);
            }
        }

        public override object InitializeLifetimeService()
        {

            return null;
        }
    }
}
