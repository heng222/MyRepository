using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Diagnostics;
using System.Net.Sockets;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Embedded or distributed message bus manager, it supplies asynchronous sending and receiving mechanism based on thread pool, and pluggable monitor
    /// </summary>
    [Serializable]
    public class MessageRouter : MarshalByRefObject, IMessageRouter,IDisposable
    {
        protected SynDictionary<Type, Subject> subjectList;
        private AsyncMessageMode asynMode = AsyncMessageMode.None;
        protected readonly object InnerLocker = new object();
        private HookManager HookManager; 
        private WaitCallback sendCallBack;
        private WaitCallback receieveCallBack;

        public MessageRouter()
        {
            subjectList = new SynDictionary<Type, Subject>();
            HookManager = new HookManager(); 
            sendCallBack = new WaitCallback(SendCallback);
            receieveCallBack = new WaitCallback(ReceiveCallback);
        }

        public MessageRouter(AsyncMessageMode asynMode):this()
        {
            this.asynMode = asynMode;
        }


        /// <summary>
        /// Get or set sending or receiving message mode
        /// </summary>
        public AsyncMessageMode AsyncMessageMode
        {
            get { return asynMode; }
            set { asynMode = value; }
        }

        /// <summary>
        /// Get the specified type's Subject
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public Subject this[Type type]
        {
            get
            {
                return subjectList[type];
            }
        }
        /// <summary>
        /// Get the amount of Subject
        /// </summary>
        public int Count
        {
            get { return subjectList.Count; }
        }

        /// <summary>
        /// Get the subject type collection
        /// </summary>
        public Type[] Types
        {
            get
            {
                Type[] types = new Type[subjectList.Keys.Count];
                subjectList.Keys.CopyTo(types, 0);
                return types;
            }
        }
        /// <summary>
        /// Whether or not to include specified type's subject
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public bool ContainSubject(Type type)
        {
            return subjectList.ContainsKey(type);
        }

        #region install or uninstall Hook
        /// <summary>
        /// Register Hook
        /// </summary>
        /// <param name="listner"></param>
        public void RegisterHook(params IHook[] hks)
        {
            HookManager.RegisterHook(hks);
        }

        public void UnRegisterHook(params IHook[] hks)
        {
            HookManager.UnRegisterHook(hks);
        }
        #endregion

        #region Get or set or remove Subject
        /// <summary>
        /// Get or set Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <returns></returns>
        public Subject<TMessage> Subject<TMessage>()
        {
            return Subject<TMessage>(null);
        }

        /// <summary>
        /// Get or set Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <returns></returns>
        public Subject<TMessage> Subject<TMessage>(object sender)
        {
            Subject<TMessage> msgHandler = null;
            if (!subjectList.ContainsKey(typeof(TMessage)))
            {
                msgHandler = new Subject<TMessage>(HookManager);
                subjectList.Add(typeof(TMessage), msgHandler);
            }
            else
            {
                msgHandler = subjectList[typeof(TMessage)] as Subject<TMessage>;
            }

            if (msgHandler != null)
                msgHandler.Subscriber = sender;

            return msgHandler;
        }
        /// <summary>
        /// Remove specified type's Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        public void Remove<TMessage>()
        {
            subjectList.Remove(typeof(TMessage));
        }
        /// <summary>
        /// Remove specified type's Subject
        /// </summary>
        /// <param name="type"></param>
        public void Remove(Type type)
        {
            subjectList.Remove(type);
        }
        #endregion

        #region Observer register or uninstall
        /// <summary>
        /// Register Subject,and register an Observer in the subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        public void Register<TMessage>(ObserverHandler<TMessage> handler)
        {
            Subject<TMessage> msgHandler = Subject<TMessage>(null);
            if (msgHandler != null)
                msgHandler.Observers += handler;
        }

        /// <summary>
        /// Register Subject,and register an Observer in the subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        public void Register<TMessage>(object sender,ObserverHandler<TMessage> handler)
        {
            Subject<TMessage> msgHandler = Subject<TMessage>(sender);
            if (msgHandler != null)
                msgHandler.Observers += handler;
        }


        /// <summary>
        /// Write off an Observer in Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        public void Unregister<TMessage>(ObserverHandler<TMessage> handler)
        {
            Subject<TMessage> msgHandler = Subject<TMessage>();
            if (msgHandler != null)
                msgHandler.Observers -= handler;
        }

        /// <summary>
        /// Write off an Observer in Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        public void Unregister<TMessage>(object sender,ObserverHandler<TMessage> handler)
        {
            Subject<TMessage> msgHandler = Subject<TMessage>(sender);
            if (msgHandler != null)
                msgHandler.Observers -= handler;
        }
        #endregion

        #region Message send
        /// <summary>
        /// Call the client Callback functin ditectely, often used in the message hook interception processing
        /// </summary>
        /// <param name="e"></param>
        public void SendMessage(MessagePacket e)
        {
            if (e == null || e.Handler == null)
                return;

            HookManager.OnMessageReceiving(e.Sender, e);

            if (e.Canceled) 
                return;

            if (AsyncMessageMode == AsyncMessageMode.Receive
                || AsyncMessageMode == AsyncMessageMode.Both)
            {
                ThreadPool.QueueUserWorkItem(receieveCallBack, e);
            }
            else
            {
                OnReceive(e);
            }
        }

        private void DoSend(MessagePacket mea)
        {
            MessagePacket e = null;
            Delegate[] invocationList = mea.Handler.GetInvocationList();
            
            foreach (Delegate del in invocationList)
            {
                e = new MessagePacket(mea.Sender, mea.Message, del);
                HookManager.OnMessageReceiving(e.Sender, e);
                if (e.Canceled)
                    return;
                OnReceive(e);
            }
        }

        private void ReceiveCallback(object o)
        {
            MessagePacket e = o as MessagePacket;
            if (e != null)
                OnReceive(e);
        }

        private static SocketException GetSocketException(Exception ex)
        {
            SocketException socketError = ex as SocketException;
            if (socketError != null) return socketError;

            if (ex.InnerException == null) return null;
            return GetSocketException(ex.InnerException);
        }

        private void OnReceive(MessagePacket e)
        {
            try
            {
                e.Handler.DynamicInvoke(e.Sender, e.Message);
            }
            catch (Exception ex)
            {
                e.Error = ex;
                SocketException socketError = GetSocketException(ex);

                if (socketError != null)
                {
                    Subject msgHandler = subjectList[e.Message.GetType()];
                    try
                    {
                        msgHandler.UnRegisterObserver(e.Handler);
                    }
                    catch (Exception innerEx)
                    {
                        e.Error = innerEx;
                    }
                }

                HookManager.OnMessageReceivedException(e.Sender, e);
            }
            finally
            {
                HookManager.OnMessageReceived(e.Sender, e);
                e = null;
            }
        }

        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">Message</param>
        public void Send(object sender, object msg)
        {
            if (msg == null)
                return;

            Type msgType = msg.GetType();
            Subject subject = subjectList[msgType];
            if (subject == null)
                return;

            Delegate handler = subject.Delegate;
            if (handler == null)
            {
                subjectList.Remove(msgType);
                return;
            }

            MessagePacket e = new MessagePacket(msg);
            HookManager.OnMessageSending(sender, e);

            if (e.Canceled)
            {
                HookManager.OnMessageSent(sender, e);
                return;
            }
            e.Sender = sender;
            e.Handler = handler;

            if (AsyncMessageMode == AsyncMessageMode.Send
                || AsyncMessageMode == AsyncMessageMode.Both)
                ThreadPool.QueueUserWorkItem(sendCallBack, e);
            else
                DoSend(e);

            HookManager.OnMessageSent(sender, e);
        }

        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">Message</param>
        /// <param name="isAsync">Whether or not to send asynchronously</param>
        public void Send(object sender, object msg,bool isAsync)
        {
            if (msg == null)
                return;

            Type msgType = msg.GetType();
            Delegate handler = subjectList[msgType].Delegate;
            if (handler == null)
            {
                subjectList.Remove(msgType);
                return;
            }

            MessagePacket e = new MessagePacket(msg);
            HookManager.OnMessageSending(sender, e);

            if (e.Canceled)
            {
                HookManager.OnMessageSent(sender, e);
                return;
            }
            e.Sender = sender;
            e.Handler = handler;

            if (isAsync && sendCallBack.Target != null)
                ThreadPool.QueueUserWorkItem(sendCallBack, e);
            else
                DoSend(e);

            HookManager.OnMessageSent(sender, e);
        }

        private void SendCallback(object o)
        {
            MessagePacket e = o as MessagePacket;
            if (e != null)
                DoSend(e);
        }
        #endregion

        public override object InitializeLifetimeService()
        {
            return null;
        }

        private bool disposed = false;

		~MessageRouter()
		{
			Dispose(false);
		}

        public void Dispose()
        {
            Dispose(true);
            subjectList.Clear();
            subjectList = null;
            HookManager.Dispose();
            HookManager = null;
            GC.SuppressFinalize(this);
        }
		protected bool IsDisposed
		{
			get
			{
				return disposed;
			}
		}

		protected virtual void Dispose(bool disposing)
		{
			disposed = true;
		}
    }

    [Serializable]
    public class MessageRouter<TMessage> : MessageRouter,IMessageRouter<TMessage>
    {
        public MessageRouter() { }
        public MessageRouter(AsyncMessageMode asyMode) : base(asyMode) { }

        public void Send(object sender, TMessage msg)
        {
            base.Send(sender, msg);
        }

        public void Send(object sender, TMessage msg, bool isAsync)
        {
            base.Send(sender, msg, isAsync);
        }
    }

    [Serializable]
    public class PriortyMessageRouter<TMessage> : MessageRouter<TMessage>,IPriortyMessageRouter<TMessage> where TMessage:IComparable<TMessage>
    {
        private MessageSchedule<TMessage> schedule;
    
        public PriortyMessageRouter() :this(new PriorityQueue<MessageInfo<TMessage>>()){ }
        public PriortyMessageRouter(AsyncMessageMode asyMode) : this(asyMode, new PriorityQueue<MessageInfo<TMessage>>()) { }
        public PriortyMessageRouter(AsyncMessageMode asyMode, PriorityQueue<MessageInfo<TMessage>> messageQueue)
            : base(asyMode)
        {
            Initialize(messageQueue);
        }

        public PriortyMessageRouter(IPriortyQueue<MessageInfo<TMessage>> messageQueue)
        {
            Initialize(messageQueue);
        }

        private void Initialize(IPriortyQueue<MessageInfo<TMessage>> messageQueue)
        {
            if (messageQueue != null)
            {
                schedule = new MessageSchedule<TMessage>(messageQueue,this);
            }
        }

        public virtual void Post(object sender, TMessage msg)
        {
            if (msg != null 
                && subjectList.ContainsKey(msg.GetType())
                && schedule != null)
            {
                schedule.Post(sender, msg);
            }
        }

        public int MillisecondsTimeout
        {
            get { return schedule.MillisecondsTimeout; }
            set { schedule.MillisecondsTimeout = value; }
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            schedule.Dispose();
        }
    }
}
