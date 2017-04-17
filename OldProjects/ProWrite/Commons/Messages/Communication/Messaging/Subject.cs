using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Message event processor
    /// </summary>
    public abstract class Subject : MarshalByRefObject
    {
        public abstract Type Type
        {
            get;
        }

        private object subscriber;
        public object Subscriber
        {
            get { return subscriber; }
            set { subscriber = value; }
        }

        public abstract Delegate Delegate { get;}
        public abstract void UnRegisterObserver(Delegate observer);
        public abstract void UnRegisterObserver(object sender, Delegate observer);
        public abstract void RegisterObserver(Delegate observer);
        public abstract void RegisterObserver(object sender, Delegate observer);

        public override object InitializeLifetimeService()
        {
            return null;
        }
    }

    /// <summary>
    /// Generic message event processor
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    [Serializable]
    public class Subject<TMessage> : Subject,IDisposable
    {
        private HookManager HookManager;
        internal Subject(HookManager hookManager/*, WeakDelegateManager weakManager*/)
        {
            HookManager = hookManager;
            //_handler = new WeakReference<ObserverHandler<TMessage>>();
        }
        private ObserverHandler<TMessage> _handler;
        //private WeakReference<ObserverHandler<TMessage>> _handler;
        public override Delegate Delegate
        {
            get
            {
                return _handler/*.Target*/;
            }
        }

        public override Type Type
        {
            get { return typeof(TMessage); }
        }
        
        public event ObserverHandler<TMessage> Observers
        {
            add
            {
                RegisterObserver(Subscriber, value);
            }
            remove
            {
                UnRegisterObserver(Subscriber, value);
            }
        }

        public void UnRegisterObserver(object sender, ObserverHandler<TMessage> value)
        {
            if (value == null) return;
            HookManager.OnObserverRemoving(Subscriber, value, Type);
            //_handler/*.Target*/ -= _handler/*.Target*/ - value;
            _handler -= value;
            HookManager.OnObserverRemoved(Subscriber, value, Type);
        }

        public override void UnRegisterObserver(Delegate handler)
        {
            UnRegisterObserver(Subscriber, handler as ObserverHandler<TMessage>);
        }

        public override void UnRegisterObserver(object sender, Delegate handler)
        {
            UnRegisterObserver(sender, handler as ObserverHandler<TMessage>);
        }

        public override void RegisterObserver(Delegate handler)
        {
            RegisterObserver(Subscriber, handler);
        }

        public void RegisterObserver(object sender, ObserverHandler<TMessage> value)
        {
            if (value == null) return;
            HookManager.OnObserverAdding(Subscriber, value, Type);
            _handler/*.Target*/ = _handler/*.Target*/ + value;
            HookManager.OnObserverAdded(Subscriber, value, Type);
        }

        public override void RegisterObserver(object sender, Delegate handler)
        {
            RegisterObserver(sender, handler as ObserverHandler<TMessage>);
        }

        public void Dispose()
        {
            //_handler.Target = null;
            _handler = null;
        }
    }
}
