using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Remoting;
using System.Threading;
using System.Reflection;
using System.Net.Sockets;

namespace System.Communication.Messaging
{
    /// <summary>
    /// 消息总线Remoting客户端代理
    /// </summary>
    public class MessageRouterProxy
    {
        private static IMessageRouter MessageManager;
        private static Dictionary<Type, object> handlers = new Dictionary<Type, object>();
        private static readonly object InnerLocker = new object();

        public static bool IsNeedAsyncRegister = true;

        public static void Configure(string fileName, bool ensureSecurity)
        {
            RemotingConfiguration.Configure(fileName, false);
            MessageManager = new MessageRouter();
        }

        public static void Send(object sender, object msg)
        {
            ThreadPool.QueueUserWorkItem(new WaitCallback(DoSend), new SendWrapper(sender, msg));
        }

        private static SubjectProxy<TMessage> Subject<TMessage>(object sender)
        {
            SubjectProxy<TMessage> msgHandler = null;
            Type type = typeof(TMessage);

            if (!handlers.ContainsKey(type))
            {
                try
                {
                    msgHandler = new SubjectProxy<TMessage>(MessageManager.Subject<TMessage>(sender), IsNeedAsyncRegister);
                    lock (InnerLocker)
                        handlers[type] = msgHandler;
                }
                catch (SocketException ex)
                {
                    System.Diagnostics.Trace.WriteLine(ex.Message);
                }
            }
            else
            {
                msgHandler = handlers[type] as SubjectProxy<TMessage>;
            }

            return msgHandler;
        }

        public static void Register<TMessage>(object sender,ObserverHandler<TMessage> handler)
        {
            SubjectProxy<TMessage> msgHandler = Subject<TMessage>(sender);
            msgHandler.Observers += handler;
        }

        public static void UnRegister<TMessage>(object sender,ObserverHandler<TMessage> handler)
        {
            SubjectProxy<TMessage> msgHandler = Subject<TMessage>(sender);
            msgHandler.Observers -= handler;
        }

        public static void Register<TMessage>(ObserverHandler<TMessage> handler)
        {
            Register<TMessage>(null, handler);
        }

        public static void UnRegister<TMessage>(ObserverHandler<TMessage> handler)
        {
            UnRegister<TMessage>(null, handler);
        }
        

        private class SendWrapper
        {
            public readonly object Sender;
            public readonly object Message;

            public SendWrapper(object sender, object msg)
            {
                this.Sender = sender;
                this.Message = msg;
            }
        }

        private static void DoSend(object o)
        {
            SendWrapper wrapper = o as SendWrapper;
            if (wrapper != null)
            {
                try
                {
                    MessageManager.Send(wrapper.Sender, wrapper.Message);
                }
                catch(Exception ex)
                {
                    System.Diagnostics.Trace.WriteLine(ex.Message);
                }
            }
        }
    }
}
