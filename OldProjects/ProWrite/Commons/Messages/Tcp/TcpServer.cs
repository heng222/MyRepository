using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Diagnostics;
using System.Communication;
using System.Communication.Service;
using System.Threading;

namespace System.Net.Tcp
{
    public partial class TcpServer<TConnection,TCoding, TPacket> : ServiceAdapter,IIOService
        where TConnection:TcpServerConnection<TCoding,TPacket>,new()
        where TCoding : ICoding<TPacket>, new()
        where TPacket : IPacket
    {
        private Socket _socket;
        private bool _stopped = true;
        private SocketAsyncEventArgs _asyncEvent = null;
        private Dispatcher _dispatcher;
        private System.Timers.Timer _timer;

        public IFrontController FrontController { get; set; }

        public class TcpServerConnectionEventArgs : EventArgs
        {
            public TConnection Connection { get; set; }
        }

        public event EventHandler<TcpServerConnectionEventArgs> Connected;

        public TcpServerParams Params { get; private set; }
        public TcpServerConnectionFactory<TConnection, TCoding,TPacket> ConnectionFactory { get; private set; } 

        public int CurrentConnectionCount { get; private set; }

        public TConnection[] CurrentConnections
        {
            get
            {
                lock (this)
                {
                    if (!_stopped)
                        return _dispatcher._conns.ToArray();
                    return null;
                }
            }
        }

        public bool IsFull { get; private set; }

        public void Init(IPEndPoint endPoint)
        {
            Init(new TcpServerConnectionFactory<TConnection, TCoding, TPacket>(), new TcpServerParams(endPoint));
        }

        public void Init(TcpServerParams serverParams)
        {
            Init(new TcpServerConnectionFactory<TConnection, TCoding, TPacket>(), serverParams);
        }

        public void Init(TcpServerConnectionFactory<TConnection, TCoding, TPacket> connFacotry, TcpServerParams serverParams)
        {
            Check.Require(connFacotry != null);
            Check.Require(serverParams != null);

            Params = serverParams;
            ConnectionFactory = connFacotry;

            _dispatcher = new Dispatcher(this, connFacotry);
        }

        protected override void DoStart()
        {
            if (_socket == null)
            {
                _socket = new Socket(
                    AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                _socket.NoDelay = true;
                _socket.Bind(Params.EndPoint);
                _socket.Listen(Params.ConnectionBacklog);

                _asyncEvent = new SocketAsyncEventArgs();
                _asyncEvent.Completed += SocketAccepted;

                Thread.CurrentThread.Name = "Tcp Server: " + Params.EndPoint.ToString();

                _timer = new System.Timers.Timer();
                _timer.Interval = Params.HeartInterval;
            }

            Run(_asyncEvent);
        }

        protected override void DoStop()
        {
            _timer.Stop();
        }

        public new IAsyncFuture Close()
        {
            Future.SimpleFuture closeFuture = new Future.SimpleFuture();
            Action closeCallback = base.Close;

            closeFuture.AsyncResult  = closeCallback.BeginInvoke(p=>
            {
                closeCallback.EndInvoke(closeFuture);
                closeFuture.Set();
            }, null);

            return closeFuture;
        }

        protected override  void DoClose()
        {
            _dispatcher.Dispose();
            if (_socket != null)
            {
                try
                {
                    _socket.Shutdown(SocketShutdown.Both);
                    _socket.Close();
                }
                catch (Exception ex)
                {
                    OnExceptionFired(ex);
                }
                _socket = null;
            }

            Connected = null;

            if (_asyncEvent != null)
                _asyncEvent.Dispose();
            _asyncEvent = null;
        }

        private void OnHeart(object state)
        {
            TConnection[] conns = null;
            lock (_dispatcher._conns)
            {
                if (_dispatcher._conns.Count == 0)
                {
                    DoStop();
                    return;
                }
                conns = _dispatcher._conns.ToArray();
            }

            foreach (var item in conns)
            {
                if (item.Socket != null &&  item.Socket.Connected)
                {
                    item.SendHeartPacket();
                }
                else
                {
                    item.Close();
                    if (_dispatcher._conns.Contains(item))
                        _dispatcher.OnConnectionDisconnected(item);
                }
            }
        }

        private void Run(object arg)
        {
            if (!IsFull)
            {
                SocketAsyncEventArgs e = arg as SocketAsyncEventArgs;
                e.AcceptSocket = null;
                _socket.InvokeAsyncMethod(_socket.AcceptAsync, SocketAccepted, e, OnExceptionFired, Close);
            }
        }

        private void Run(SocketAsyncEventArgs e)
        {
            if (!IsFull)
            {
                e.AcceptSocket = null;
                _socket.InvokeAsyncMethod(_socket.AcceptAsync, SocketAccepted, e, OnExceptionFired, Close);
            }
        }

        private void SocketAccepted(object sender, SocketAsyncEventArgs e)
        {
            if (e.SocketError == SocketError.OperationAborted)
                return;

            if (e.SocketError == SocketError.Success)
            {
                Socket socket = e.AcceptSocket;
                var conn = _dispatcher.Enqueue(socket);

                if (_dispatcher._conns.Count == 1)
                    _timer.Start();

                if (conn != null)
                {
                    OnSocketConnected(conn);
                }
            }

            Run(e);
        }

        protected virtual void OnSocketConnected(TConnection conn)
        {
            if (Connected != null)
                Connected(this, new TcpServerConnectionEventArgs() { Connection = conn });
        }
    }
}
