using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Diagnostics;
using System.Threading;

namespace System.Communication
{
    public enum ConnectionState
    {
        Closed,
        Opening,
        Opened,
    }

    public interface IConnectionBase
    {
        IAsyncFuture Close();
        ConnectionState State { get; }
        event EventHandler ConnectionClosed;
        event EventHandler<EventArgs<Exception>> ExceptionFired;
    }

    public interface IConnectionBase<TPacket> : IConnectionBase
        where TPacket : IPacket
    {
        event Action<TPacket> Received;


        void Send(TPacket packt);
    }

    public interface IAsyncContext<TPacket>
    {
        Exception Exception { get;}
        bool IsSuccessed { get; }
        TPacket Packet { get; }
    }

    public class AsyncFuture<TPacket> : Future.AsyncFuture, IAsyncFuture<TPacket>, IAsyncContext<TPacket> where TPacket : IPacket
    {
        private static Dictionary<int, AsyncFuture<TPacket>> _pendings = new Dictionary<int, AsyncFuture<TPacket>>();
        private static Queue<AsyncFuture<TPacket>> _queues = new Queue<AsyncFuture<TPacket>>();
        private static int _seed = 0;
        private static readonly object _innerLock = new object();

        protected AsyncFuture()
        {
        }

        public static AsyncFuture<TPacket> Current
        {
            get;
            protected internal set;
        }

        public virtual TPacket Packet { get; internal protected set; }

        public override bool IsSuccessed
        {
            get
            {
                if (Packet == null)
                    return base.IsSuccessed;
                return base.IsSuccessed && !Packet.HasError; 
            }
        }

        public Action<IAsyncContext<TPacket>> CompletedHandler { get; protected set; }

        public static AsyncFuture<TPacket> Get(Action<IAsyncContext<TPacket>> completedCallback)
        {
            AsyncFuture<TPacket> future = null;
            lock (_innerLock)
            {
                if (_queues.Count > 0)
                {
                    future = _queues.Dequeue();
                }
                else
                {
                    future = new AsyncFuture<TPacket>();
                    _seed++;
                    future.Id = _seed;
                }
                _pendings[future.Id] = future;
            }

            if (future.CompletedHandler != null)
                future.CompletedHandler = null;
            future.CompletedHandler = completedCallback;

            Current = future;
            return future;
        }

        protected override void OnCompleted()
        {
            base.OnCompleted();
            if (CompletedHandler != null)
            {
                CompletedHandler.call(this);
                CompletedHandler = null;
            }
        }

        public static AsyncFuture<TPacket> Get(int futureId)
        {
            lock (_innerLock)
            {
                if (_pendings.ContainsKey(futureId))
                {
                    return _pendings[futureId];
                }
            }

            return null;
        }

        public static void OnCompleted(TPacket resp)
        {
            AsyncFuture<TPacket> future = null;
            lock (_innerLock)
            {
                if (_pendings.ContainsKey(resp.Id))
                {
                    future = _pendings[resp.Id];
                    _pendings.Remove(resp.Id);
                }
            }

            Current = future;
            if (future != null)
            {
                future.Packet = resp;
                future.Set();
            }
        }

        public static void Clear()
        {
            lock (_innerLock)
            {
                if (_pendings.Count > 0)
                {
                    foreach (var item in _pendings)
                    {
                        Current = item.Value;
                        item.Value.Set();
                    }

                    _pendings.Clear();
                }
            }
        }

        public static void CancelAll()
        {
            lock (_innerLock)
            {
                if (_pendings.Count > 0)
                {
                    foreach (var item in _pendings)
                    {
                        Current = item.Value;
                        item.Value.Cancel();
                    }
                    _pendings.Clear();
                }
            }
        }

    }

    public class AsyncFuture
    {
        
    }
   
}
