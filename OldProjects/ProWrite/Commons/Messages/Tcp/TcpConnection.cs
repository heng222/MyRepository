using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Diagnostics;
using Org.Mentalis.Network.ProxySocket;
using System.Threading;
using System.Communication;

namespace System.Net.Tcp
{
    
    public abstract class TcpConnection<TSocket, TConnectionParams, TCoding, TPacket> : TcpConnectionBase<TSocket, TConnectionParams, TCoding, TPacket>,IConnectionBase<TPacket> 
        where TSocket :Socket
        where TConnectionParams :ConnectionParams
        where TCoding : ICoding<TPacket> ,new()
        where TPacket : IPacket
    {
        private System.Timers.Timer timer;

        private DateTime prev = DateTime.Now;
        private DateTime current = DateTime.Now;
        private int interval = 1000;

        private uint heartCount = 0;
        private bool IsHeart = false;
        private volatile object trackLocker = new object();

        public TcpConnection()
        {
        }

        protected abstract  TSocket CreateSocket();

        

        private EventHandler _connectionOpened;
        public event EventHandler ConnectionOpened
        {
            add { _connectionOpened += value; }
            remove { _connectionOpened -= value; }
        }

        

        protected virtual void Init()
        {
            Check.Require(State != ConnectionState.Opened);
            Check.Require(Params != null);

            TSocket socket = CreateSocket();
            Check.Require(socket != null);
            Init(socket, new SocketAsyncEventArgs(), new TCoding());
            ReceiveAsyncEvent.SetBuffer(new byte[Params.BufferSize], 0, Params.BufferSize);

            timer = new System.Timers.Timer();
            timer.Elapsed += new System.Timers.ElapsedEventHandler(timer_Elapsed);
            timer.Interval = interval;
        }

        void timer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            lock (trackLocker)
            {
                if (!IsHeart || heartCount < 2)
                {
                    if (!NetHelper.InternetConnectedState)
                        Close();
                    else
                        current = DateTime.Now;
                }
                else
                {
                    var timespan = DateTime.Now - current;
                    var tick = timespan.TotalMilliseconds;
                    if (tick > interval * 10)
                        Close();
                }
            }
        }

        protected virtual IAsyncFuture CreateOpenFuture()
        {
            return new Future.SimpleFuture();
        }

        public virtual IAsyncFuture Open()
        {
            var openFuture = CreateOpenFuture();

            try
            {
                Log.InfoFormat("Begin Open.");
                Init();

                State = ConnectionState.Opening;
                openFuture.AsyncResult = Socket.BeginConnect(Params.EndPoint, ar =>
                {
                    try
                    {
                        Socket.EndConnect(openFuture.AsyncResult);
                        openFuture.Set();
                        if (openFuture.IsSuccessed)
                            OnConnectionOpened();
                    }
                    catch (SocketException ex)
                    {
                        openFuture.Exception = new NetException(ex.SocketErrorCode);
                        OnConnectionException(openFuture.Exception);
                    }
                    catch (Exception ex)
                    {
                        openFuture.Exception = new NetException(ex.Message, ex);
                        OnConnectionException(openFuture.Exception);
                    }



                }, null);
            }
            catch (SocketException ex)
            {
                openFuture.Exception = new NetException(ex.SocketErrorCode);
                OnConnectionException(openFuture.Exception);
            }
            catch (Exception ex)
            {
                openFuture.Exception = new NetException(ex.Message, ex);
                OnConnectionException(openFuture.Exception);
            }

            //const int connectionTimeout = 5 * 1000;
            //openFuture.Wait(connectionTimeout);
            return openFuture;
        }

        protected internal virtual void OnConnectionOpened()
        {
            try
            {
                Log.InfoFormat("End Open.");
                State = ConnectionState.Opened;
                if (_connectionOpened != null)
                    _connectionOpened.call(this, EventArgs.Empty);

                current = DateTime.Now;
                timer.Start();
                Run();
            }
            catch (Exception ex)
            {
                OnExceptionFired(ex);
            }
        }

        protected virtual void OnConnectionException(Exception ex)
        {
            State = ConnectionState.Closed;
        }


        protected override void OnReceived(TPacket resp)
        {
            var task = AsyncFuture<TPacket>.Get(resp.Id);
            if (task != null && !task.IsCancelled) 
                base.OnReceived(resp);
            AsyncFuture<TPacket>.OnCompleted(resp);
        }

        protected void AsyncFutureCompleted(TPacket resp)
        {
            AsyncFuture<TPacket>.OnCompleted(resp);
        }

        protected override void OnReceivedHeartPacket(byte[] packet)
        {
            lock (trackLocker)
            {
                prev = current;
                current = DateTime.Now;

                if (heartCount == uint.MaxValue)
                    heartCount = 3;

                heartCount++;

                if (heartCount ==1)
                {
                    IsHeart = true;
                    interval = Params.HeartInterval;
                    timer.Interval = interval; 
                }
            }

            base.OnReceivedHeartPacket(packet);
        }

        protected override void OnConnectionClosed()
        {
            if (timer != null)
            {
                timer.Close();
                if (timer != null)
                {
                    timer.Dispose();
                    timer = null;
                }
            }
            AsyncFuture<TPacket>.CancelAll();

            base.OnConnectionClosed();
        }

    }

    public class TcpConnection<TCoding,TPacket> : TcpConnection<Socket,ConnectionParams, TCoding,TPacket>
        where TCoding : ICoding<TPacket>, new()
        where TPacket : IPacket
    {
        public TcpConnection()
        {
        }

        protected override Socket CreateSocket()
        {
            return new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }
    }

    public class TcpProxyConnection<TCoding,TPacket> : TcpConnection<ProxySocket, TcpConnectionParams, TCoding,TPacket>
        where TCoding : ICoding<TPacket>, new()
        where TPacket : IPacket
    {
        public TcpProxyConnection()
        {
        }

        protected override ProxySocket CreateSocket()
        {
            return new ProxySocket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }


        protected override void Init()
        {
            base.Init();

            if (Params.ProxyEndPoint != null
                   && Params.ProxyType != ProxyTypes.None)
            {
                Socket.ProxyEndPoint = Params.ProxyEndPoint;
                Socket.ProxyType = Params.ProxyType;
                Socket.ProxyUser = Params.ProxyUser;
                Socket.ProxyPass = Params.ProxyPassword;
            }
        }
    }
}
