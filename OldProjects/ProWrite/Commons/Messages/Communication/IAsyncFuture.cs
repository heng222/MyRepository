using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Tcp;
using System.ComponentModel;

namespace System.Communication
{
    public interface IAsyncFuture: IAsyncResult
    {
        int Id { get; }
        IAsyncResult AsyncResult { get; set; }
        IAsyncFuture Parent { get; }

        Exception Exception { get; set;}
        bool IsSuccessed { get; }
        bool IsCancelled { get; }

        bool Wait();
        bool Wait(int millisecondsTimeout);

        void Cancel();
        void Cancel(CancelCallback cancelCallback, object arg);
        void Set();
        void Reset();

        void Close();
    }

    public interface IAsyncFuture<TValue> : IAsyncFuture
    {
        TValue Packet { get; }
    }

    public delegate void CancelCallback(object arg);

   

    public static class Future
    {
        public class Void
        {
            private Void() { }
            public static readonly Void Instance = new Void();
        }

        public class SimpleFuture : IAsyncFuture
        {
            public SimpleFuture()
            {
            }

            public int Id { get; protected internal set; }

            private IAsyncResult _ar;
            private IAsyncFuture _innerFuture;
            public IAsyncResult AsyncResult
            {
                get
                {
                    return _ar;
                }
                set
                {
                    if (value != _ar)
                    {
                        Check.Require(value != null, "value != null");
                        if (_ar != null && _ar.AsyncWaitHandle != null)
                        {
                            try
                            {
                                _ar.AsyncWaitHandle.Close();
                            }
                            catch(Exception ex)
                            {
                                Log.Error(ex.Message, ex);
                            }
                        }
                        _ar = value;

                        _innerFuture = _ar as IAsyncFuture;
                        if (_innerFuture != null)
                        {
                            SimpleFuture tmpFuture = _innerFuture as SimpleFuture;
                            if (tmpFuture != null)
                                tmpFuture.Parent = this;
                        }
                    }
                }
            }

            public IAsyncFuture Parent { get; protected set; }

            public virtual void Set()
            {
                if (Parent != null)
                {
                    Parent.Set();
                    return;
                }

                //if (IsCompleted)
                //    return;

                if (AsyncResult == null || AsyncResult.AsyncWaitHandle == null)
                {
                    IsCompleted = true;
                    return;
                }

                var mre = AsyncResult.AsyncWaitHandle as ManualResetEvent;
                if (mre != null)
                {
                    IsCompleted = true;
                    if (!IsCancelled)
                        OnCompleted();
                    else
                    {
                        if (cancelHandler.HasValue)
                            cancelHandler.Value.Invoke();
                    }

                    if (!mre.SafeWaitHandle.IsClosed)
                    {
                        mre.Set();
                    }
                }
            }

            public virtual void Reset()
            {
                if (AsyncResult == null || AsyncResult.AsyncWaitHandle == null)
                {
                    IsCompleted = false;
                    return;
                }

                var mre = AsyncResult.AsyncWaitHandle as ManualResetEvent;
                if (mre != null)
                {
                    IsCompleted = false;
                    mre.Reset();
                }
            }

            protected virtual void OnCompleted()
            {
            }

            private Exception exception;
            public  virtual Exception Exception
            {
                get
                {
                    if (exception == null)
                    {
                        if (_innerFuture != null)
                            return _innerFuture.Exception;
                    }
                    return exception;
                }
                set
                {
                    if (value != null)
                    {
                        exception = value;
                        Set();
                    }
                }
            }

            public virtual bool IsSuccessed { get { return Exception == null; }}

            public virtual bool Wait()
            {
                if (AsyncResult == null 
                    || AsyncResult.AsyncWaitHandle == null
                    || IsCancelled 
                    || IsCompleted)
                    return true;
                return AsyncResult.AsyncWaitHandle.WaitOne();
            }

            public virtual bool Wait(int millisecondsTimeout)
            {
                if (AsyncResult == null
                    || AsyncResult.AsyncWaitHandle == null
                    || IsCancelled
                    || IsCompleted)
                    return true;
                return AsyncResult.AsyncWaitHandle.WaitOne(millisecondsTimeout,false);
            }


            public virtual bool IsCompleted
            {
                get
                {
                    if (AsyncResult == null)
                        return true;
                    if (Exception != null)
                        return true;
                    return AsyncResult.IsCompleted;
                }
                protected set { ;}
            }

            public virtual bool IsCancelled { get; protected set; }

            protected Tuple? cancelHandler; 
            protected struct Tuple
            {
                public CancelCallback Handler;
                public object Arg;

                public void Invoke()
                {
                    if (Handler != null)
                        Handler.call(Arg);
                }
            }

            public virtual void Cancel()
            {
                Cancel(null, null);
            }

            public virtual void Cancel(CancelCallback callback, object arg)
            {
                this.cancelHandler = null;
                if (callback != null)
                    cancelHandler = new Tuple { Handler = callback, Arg = arg };

                IsCancelled = true;
                Set();
            }



            public void Close()
            {
                if (AsyncResult != null && AsyncResult.AsyncWaitHandle != null)
                {
                    try
                    {
                        AsyncResult.AsyncWaitHandle.Close();
                    }
                    catch(Exception ex)
                    {
                        Log.Error(ex.Message, ex);
                    }
                }
            }

            object IAsyncResult.AsyncState
            {
                get { return null; }
            }

            WaitHandle IAsyncResult.AsyncWaitHandle
            {
                get
                {
                    if (AsyncResult == null)
                        return null;
                    return AsyncResult.AsyncWaitHandle;
                }
            }

            bool IAsyncResult.CompletedSynchronously
            {
                get
                {
                    if (AsyncResult == null)
                        return true;
                    return AsyncResult.CompletedSynchronously;
                }
            }
        }

        public class AsyncFuture : SimpleFuture
        {
            public AsyncFuture()
            {
            }

            public AsyncFuture(IAsyncResult ar)
            {
                AsyncResult = ar;
            }

            public override bool Wait()
            {
                if (AsyncResult == null
                    || AsyncResult.AsyncWaitHandle == null
                    || IsCancelled
                    || IsCompleted)
                    return true;

                bool flag = AsyncResult.AsyncWaitHandle.WaitOne();
                if (flag && !IsCompleted)
                {
                    var mre = AsyncResult.AsyncWaitHandle as ManualResetEvent;
                    if (mre != null)
                    {
                        mre.Reset();
                        var rs = mre.WaitOne();
                        return rs;
                    }
                }
                return flag;
            }

            public override bool Wait(int millisecondsTimeout)
            {
                if (AsyncResult == null
                    || AsyncResult.AsyncWaitHandle == null
                    || IsCancelled
                    || IsCompleted)
                    return true;

                bool flag = AsyncResult.AsyncWaitHandle.WaitOne(millisecondsTimeout,false);
                if (flag && !IsCompleted)
                {
                    var mre = AsyncResult.AsyncWaitHandle as ManualResetEvent;
                    if (mre != null)
                    {
                        mre.Reset();
                        return mre.WaitOne();
                    }
                }
                return flag;
            }

            private bool isCompleted = false;
            public override bool IsCompleted
            {
                get
                {
                    if (Exception != null)
                        return true;
                    return isCompleted;
                }
                protected set
                {
                    if (isCompleted != value)
                    {
                        isCompleted = value;
                        //if (isCompleted)
                        //{
                        //    OnCompleted();
                        //}
                    }
                }
            }
        }

        public static void Invoke(System.Action action)
        {
            ThreadPool.QueueUserWorkItem(state =>
            {
                if (action != null)
                    action.call(null);
            }, null);
        }

        public static void Invoke<T>(Action<T> action, T arg)
        {
            ThreadPool.QueueUserWorkItem(state =>
            {
                if (action != null)
                    action.call(arg);
            }, null);
        }
        
    }

    public static class FutureContext
    {
        private static SynchronizationContext synchronizationContext;

        public static SynchronizationContext SynchronizationContext
        {
            get
            {
                if (synchronizationContext == null)
                    return SynchronizationContext.Current;
                return synchronizationContext;
            }
            set
            {
                synchronizationContext = value;
            }
        }

        public static ISynchronizeInvoke SynchronizeObject { get; set; }

        public static void call(this Delegate dlgt, params object[] args)
        {
            if (dlgt != null)
            {
                //必须通过异步接口调用的
                ISynchronizeInvoke hwnd = dlgt.Target as ISynchronizeInvoke;
                try
                {
                    if (hwnd != null)
                    {
                        if (hwnd.InvokeRequired)
                            hwnd.Invoke(dlgt, args);
                        else
                            dlgt.DynamicInvoke(args);
                    }
                    //if (hwnd != null && hwnd.InvokeRequired)
                    //{
                    //    hwnd.Invoke(dlgt, args);
                    //}
                    else
                    {
                        if (SynchronizeObject != null && SynchronizeObject.InvokeRequired)
                            SynchronizeObject.Invoke(dlgt, args);
                        else
                            dlgt.DynamicInvoke(args);//SynchronizationContext.Post(p => { dlgt.DynamicInvoke(args); }, null);
                    }
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message, ex);
                }
            }
        }

        public static void Post(Action action)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Post((p) => { action(); },null);
        }

        public static void Post<T>(Action<T> action, T arg)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Post((p) => action(arg),null);
        }

        public static void Post<TArg1, TArg2>(Action<TArg1, TArg2> action, TArg1 arg1, TArg2 arg2)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Post((p) => action(arg1, arg2),null);
        }

        public static void Send(Action action)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Send(p => { action(); }, null);
        }

        public static void Send<T>(Action<T> action, T arg)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Send((p) => action(arg),null);
        }

        public static void Send<TArg1, TArg2>( Action<TArg1, TArg2> action, TArg1 arg1, TArg2 arg2)
        {
            Check.Require(action, "action", Check.NotNull);
            SynchronizationContext.Send((p) => action(arg1, arg2),null);
        }

    }

    
}
