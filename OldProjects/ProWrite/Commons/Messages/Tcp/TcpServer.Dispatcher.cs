using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;
using System.Communication;

namespace System.Net.Tcp
{
    public partial class TcpServer<TConnection, TCoding, TPacket> 
    {
        private class Dispatcher : DisposableObject
        {
            private Stack<SocketAsyncEventArgs> _argsPool = null;
            private BufferManager _bufferManager = null;
            internal List<TConnection> _conns = null;
            internal Queue<Socket> _pendingQueue = null;
            private static readonly object innerLock = new object();
            private TcpServer<TConnection, TCoding, TPacket> _server;
            private ITcpServerConnectionFactory<TConnection, TCoding, TPacket> _connFactory;

            public Dispatcher(TcpServer<TConnection, TCoding, TPacket> server, ITcpServerConnectionFactory<TConnection, TCoding, TPacket> connFactory)
            {
                _server = server;
                _argsPool = new Stack<SocketAsyncEventArgs>(server.Params.MaxConnections);
                _bufferManager = new BufferManager(server.Params.MaxConnections, server.Params.BufferSize);
                _conns = new List<TConnection>(server.Params.MaxConnections);
                _pendingQueue = new Queue<Socket>(server.Params.MaxPendingConnections);
                _connFactory = connFactory;

                //Rev Async Event args
                for (int i = 0; i < server.Params.MaxConnections; i++)
                {
                    _argsPool.Push(new SocketAsyncEventArgs());
                }

                _server.CurrentConnectionCount = 0;
            }

            private void OnConnectionDisconnected(object sender, EventArgs ea)
            {

                TConnection conn = sender as TConnection;
                OnConnectionDisconnected(conn);
            }

            internal void OnConnectionDisconnected(TConnection conn)
            {
                lock (innerLock)
                {
                    if (_conns.Contains(conn))
                    {
                        _server.CurrentConnectionCount--;
                        _conns.Remove(conn);
                        _bufferManager.FreeBuffer(conn.ReceiveAsyncEvent);
                        _argsPool.Push(conn.ReceiveAsyncEvent);

                        if (!_server._stopped && _pendingQueue.Count > 0)
                        {
                            var socket = _pendingQueue.Dequeue();
                            if (socket != null)
                                StartConnection(socket);
                        }
                    }
                }
            }

            protected internal TConnection Enqueue(Socket socket)
            {
                lock (innerLock)
                {
                    if (_server.CurrentConnectionCount < _server.Params.MaxConnections)
                        return StartConnection(socket);
                    else
                    {
                        _server.IsFull = true;

                        if (_pendingQueue.Count < _server.Params.MaxPendingConnections)
                            _pendingQueue.Enqueue(socket);
                        return null;
                    }
                }
            }

            private TConnection StartConnection(Socket socket)
            {
                var revAsyncEvent = _argsPool.Pop();
                _bufferManager.SetBuffer(revAsyncEvent);

                var conn = new TConnection();
                conn.Params = _server.Params;
                conn.Init(socket, revAsyncEvent, new TCoding());
                conn.State = ConnectionState.Opened;
                conn.ConnectionClosed += OnConnectionDisconnected;

                conn.FrontController = _server.FrontController;
                _conns.Add(conn);

                _server.CurrentConnectionCount++;

                conn.Run();
                return conn;
            }

            protected override void Dispose(bool disposing)
            {
                if (_conns != null)
                {
                    foreach (var item in _conns)
                        item.Dispose();
                    _conns.Clear();
                    _conns = null;
                }

                if (_argsPool != null)
                {
                    foreach (var item in _argsPool)
                        item.Dispose();
                    _argsPool.Clear();
                    _argsPool = null;
                }

                if (_bufferManager != null)
                {
                    _bufferManager.Dispose();
                    _bufferManager = null;
                }

                base.Dispose(disposing);

            }
        }
    }
}
