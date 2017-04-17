using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Net.Tcp;
using System.IO;
using System.Threading;
using System.Communication;

namespace System.Net.Tcp
{
    public class TcpConnectionBase<TSocket,TConnectionParams,TCoding, TPacket> 
        : DisposableObject
        , IConnectionBase<TPacket>
        where TSocket : Socket
        where TConnectionParams :ConnectionParams
        where TCoding : ICoding<TPacket>
        where TPacket :IPacket
    {
        private PacketParser parser = null;

        public TcpConnectionBase()
        {
        }

        protected internal TSocket Socket { get; private set; }

        private TConnectionParams _connParams;
        public TConnectionParams Params
        {
            get
            {
                return _connParams;
            }
            set
            {
                Check.Require(State == ConnectionState.Closed,"State == ConnectionState.Close" );
                Check.Require(value != null);
                _connParams = value;
                parser = new PacketParser(SR.EOF, ParsePacket);
            }
        }

        private TCoding _coding;
        public TCoding Coding
        {
            get { return _coding; }
            protected internal set
            {
                Check.Require(State == ConnectionState.Closed, "State == ConnectionState.Close");
                Check.Require(value != null);
                _coding = value;
            }
        }

        public ConnectionState State { get; protected internal set; }

        internal SocketAsyncEventArgs ReceiveAsyncEvent { get; private set; }

        public event Action<TPacket> Received;
        public event EventHandler ConnectionClosed;
        private EventHandler<EventArgs<Exception>> _exceptionFired;
        public event EventHandler<EventArgs<Exception>> ExceptionFired
        {
            add { _exceptionFired += value; }
            remove { _exceptionFired -= value; }
        }

        protected internal virtual void OnExceptionFired(Exception ex)
        {
            Log.Error(ex.Message, ex);
            if (_exceptionFired != null)
                _exceptionFired.call(this, new EventArgs<Exception>(ex));
        }


        public virtual void Init(TSocket socket
            , SocketAsyncEventArgs receiveAsyncEvent
            , TCoding coding)
        {
            Check.Require(socket != null);
            Check.Require(receiveAsyncEvent != null);

            Coding = coding;

            socket.NoDelay = true;
            LingerOption lingerOption = new LingerOption(true, 2);
            socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, lingerOption);
            //socket.SendBufferSize = 1024 * 5;
            //socket.ReceiveBufferSize = 1024 * 5;
            socket.SendTimeout = Params.SendTimeout;
            socket.ReceiveTimeout = Params.ReceiveTimeout;

            Socket = socket;

            ReceiveAsyncEvent = receiveAsyncEvent;
            ReceiveAsyncEvent.Completed += OnReceivedCompleted;
        }

        

        protected virtual internal void Send(byte[] data)
        {
            if (!Socket.Connected)
            {
                OnExceptionFired(new NetException(SocketError.NotConnected));
            }
    
            if (data != null && data.Length > 0)
            {
                int length = data.Length + Params.PacketSeparateFlag.Length;
                var bytes = new byte[length];

                data.CopyTo(bytes, 0);
                Params.PacketSeparateFlag.CopyTo(bytes, data.Length);

                try
                {
                    Socket.BeginSend(bytes, 0, length, SocketFlags.None, ar =>
                        {
                            try
                            {
                                Socket.EndSend(ar);
                            }
                            catch (SocketException ex)
                            {
                                OnExceptionFired(ex);
                                Close();
                            }
                            catch (Exception ex)
                            {
                                OnExceptionFired(ex);
                                Close();
                            }
                        }, null);
                }
                catch (IOException ex)
                {
                    OnExceptionFired(ex);
                    Close();
                }
                catch (SocketException ex)
                {
                    OnExceptionFired(ex);
                    Close();
                }
                catch (Exception ex)
                {
                    OnExceptionFired(ex);
                }
            }
        }

        internal protected virtual void SendHeartPacket()
        {
            Send(Params.HeartPacket);
        }

        public virtual void Send(TPacket req)
        {
            Check.Require(req != null);
            Check.Require(Coding != null);

            var data = Coding.EncodePacket(req);
            Send(data);
        }

        public virtual AsyncFuture<TPacket> SendAsync(TPacket req,Action<IAsyncContext<TPacket>> callback )
        {
            Check.Require(req != null);
            Check.Require(Coding != null);

            var future = AsyncFuture<TPacket>.Get(callback);
            req.Id = future.Id;
            future.Packet = req;

            if (Socket == null || !Socket.Connected)
            {
                future.Exception = new NetException(SocketError.NotConnected);
                return future;
            }

            if (!NetHelper.InternetConnectedState)
            {
                future.Exception = new NetException(SocketError.NotConnected);
                //OnExceptionFired(future.Exception);
                return future;
            }

            var data = Coding.EncodePacket(req);

            int length = data.Length + Params.PacketSeparateFlag.Length;
            var bytes = new byte[length];

            data.CopyTo(bytes, 0);
            Params.PacketSeparateFlag.CopyTo(bytes, data.Length);

            try
            {
                Log.Info("Send packet:" + req.ToString());
                future.AsyncResult = Socket.BeginSend(bytes, 0, length, SocketFlags.None, ar =>
                {
                    try
                    {
                        Socket.EndSend(ar);
                        //wait response packet
                        future.Reset();
                        future.Wait();
                    }
                    catch (SocketException ex)
                    {
                        future.Exception = new NetException(ex.SocketErrorCode);
                        //OnExceptionFired(future.Exception);
                        Close();
                    }
                    catch (Exception ex)
                    {
                        future.Exception = new NetException(ex.Message, ex);
                        //OnExceptionFired(future.Exception);
                        Close();
                    }
                }, null);
            }
            catch (IOException ex)
            {
                future.Exception = new NetException(ex.Message, ex);
                //OnExceptionFired(future.Exception);
                Close();
            }
            catch (SocketException ex)
            {
                future.Exception = new NetException(ex.SocketErrorCode);
                //OnExceptionFired(future.Exception);
                Close();
            }
            catch (Exception ex)
            {
                future.Exception = new NetException(ex.Message, ex) ;
                //OnExceptionFired(future.Exception);
            }

            return future;
        }
        public virtual AsyncFuture<TPacket> SendAsync(TPacket packet)
        {
            return SendAsync(packet, null);
        }

        protected virtual void OnReceived(byte[] data)
        {
            var packet = Coding.DecodePacket(data);
            if (packet != null)
            {
                if (packet.HasError)
                    Log.Error("Receive packet:" + packet.ToString());
                else
                    Log.Info("Receive packet:" + packet.ToString());
                OnReceived(packet);
            }
        }


        protected virtual void OnReceived(TPacket packet)
        {
            RaiseReceived(packet);
        }

        protected virtual void RaiseReceived(TPacket packet)
        {
            Action<TPacket> handler = Received;
            if (handler != null)
            {
                if (packet != null)
                {
                    handler.call(packet);
                }
            }
        }

        internal void Run()
        {

            if (Socket.Connected)
            {
                Socket.InvokeAsyncMethod(Socket.ReceiveAsync, OnReceivedCompleted, ReceiveAsyncEvent, OnExceptionFired, Close);
            }
        }

        private void OnReceivedCompleted(object sender, SocketAsyncEventArgs args)
        {
            try
            {
                if (args.BytesTransferred == 0)
                {
                    //OnExceptionFired(new NetException(args.SocketError));
                    Close();
                    return;
                }
                if (args.SocketError != SocketError.Success)
                {
                    //OnExceptionFired(new NetException(args.SocketError));
                    Log.Error(args.SocketError.ToString());
                    Close();
                    return;
                }

                Byte[] data = new Byte[args.BytesTransferred];
                Array.Copy(args.Buffer, args.Offset, data, 0, data.Length);

                parser.Parse(data);

                Run();
            }
            catch (Exception ex)
            {
                OnExceptionFired(ex);
            }
        }


        public virtual IAsyncFuture Close()
        {
            var future = new Future.SimpleFuture();

            if (Socket == null || !Socket.Connected)
            {
                Log.Warn("Socket == null || !Socket.Connected.");
                InternalCloseSocket();
                InternalOnConnectionClosed();
                return future;
            }
            
            try
            {
                Log.Info("Socket shutdown");
                Socket.Shutdown(SocketShutdown.Both);
            }
            catch (SocketException ex)
            {
                future.Exception = new NetException(ex.SocketErrorCode);
                InternalCloseSocket();
                InternalOnConnectionClosed();

            }
            catch (Exception ex)
            {
                future.Exception = new NetException(ex.Message, ex);
                InternalCloseSocket();
                InternalOnConnectionClosed();
            }

            try
            {
                Action closeCallback = Socket.Close;

                future.AsyncResult = closeCallback.BeginInvoke(p =>
                {
                    try
                    {
                        closeCallback.EndInvoke(future.AsyncResult);
                        Log.Info("Socket close.");
                        future.Set();
                    }
                    catch (SocketException ex)
                    {
                        future.Exception = new NetException(ex.SocketErrorCode) ;
                        InternalOnConnectionClosed();
                    }
                    catch (Exception ex)
                    {
                        future.Exception = new NetException(ex.Message, ex);
                        InternalOnConnectionClosed();
                    }

                    OnConnectionClosed();
                    
                }, null);
            }
            catch (SocketException ex)
            {
                future.Exception = new NetException(ex.SocketErrorCode);
                InternalOnConnectionClosed();
            }
            catch (Exception ex)
            {
                future.Exception = new NetException(ex.Message, ex);
                InternalOnConnectionClosed();
            }
            
            
            return future;
        }

        private void ParsePacket(byte[] packet)
        {
            if (IsHeartPacket(packet))
            {
                Send(packet);
                OnReceivedHeartPacket(packet);
                Log.Info("Receive heart packet.");
            }
            else
                OnReceived(packet);
        }

        protected virtual void OnReceivedHeartPacket(byte[] packet)
        {

        }

        protected bool IsHeartPacket(byte[] packet)
        {
            int length = Params.HeartPacket.Length;
            if (packet == null || packet.Length != length)
                return false;

            for (int i = 0; i < length; i++)
                if (packet[i] != Params.HeartPacket[i])
                    return false;
            return true;
        }

        private void InternalOnConnectionClosed()
        {
            try
            {
                OnConnectionClosed();
                Log.Info("Connection closed.");
            }
            catch(Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
        }
        protected virtual void OnConnectionClosed()
        {
            State = ConnectionState.Closed;

            if (ConnectionClosed != null)
                ConnectionClosed.call(this, EventArgs.Empty);

            
        }

        protected override void Dispose(bool disposing)
        {
            Close();

            ConnectionClosed = null;
            _exceptionFired = null;
            ReceiveAsyncEvent = null;

            
            base.Dispose(disposing);
        }

        private void InternalCloseSocket()
        {
            try
            {
                if (Socket != null && Socket.Connected)
                    Socket.Close();
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
        }
    }

    public class PacketParser
    {
        const int defaultBufferSize = 1024 * 100;
        private List<byte> buffer = new List<byte>(defaultBufferSize);
        private readonly byte[] EOF = null;
        private List<byte> packet = new List<byte>(defaultBufferSize);
        private Action<byte[]> onReadyPacket;
        private bool IsFullPacketFlag = true;
        private volatile object innerLock = new object();

        public PacketParser(byte[] packetSeparateFlag, Action<byte[]> callback)
        {
            EOF = packetSeparateFlag;
            onReadyPacket = callback;
        }

        public void Parse(byte[] bytes)
        {
            //lock (innerLock)
            {
                buffer.AddRange(bytes);
                if (buffer.Count < EOF.Length)
                    return;

                int length = buffer.Count;
                int seperateLength = EOF.Length;

                int m = length - seperateLength;
                for (int n = 0; n < seperateLength; n++, m++)
                {
                    if (buffer[m] != EOF[n])
                    {
                        IsFullPacketFlag = false;
                        break;
                    }
                }

                int i = 0;
                for (; i < length; i++)
                {
                    if (packet.Count > 0 
                        && buffer[i] == EOF[0]
                        && (i+seperateLength -1) < length)
                    {
                        bool hasPass = true;
                        for (int j = 1; j < seperateLength; j++)
                        {
                            if (buffer[i + j] != EOF[j])
                            {
                                hasPass = false;
                                break;
                            }
                        }
                        if (!hasPass)
                        {
                            packet.Add(buffer[i]);
                        }
                        else
                        {
                            i += seperateLength - 1;
                            if (onReadyPacket != null)
                                onReadyPacket(packet.ToArray());
                            packet.Clear();
                        }
                    }
                    else
                    {
                        packet.Add(buffer[i]);
                    }

                }

                if (IsFullPacketFlag)
                {
                    buffer.Clear();
                    packet.Clear();
                }
                else
                {
                    buffer.RemoveRange(0, i);
                }
            }
        }
    }
}
