using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE.Entity;
using System.Communication;
using System.IO.Ports;
using System.Threading;
using System.Net.Tcp;
using ProWrite.Core;

namespace ProWrite.UFE
{

    public class RS232Params
    {
        public string PortName { get; set; }
        public int BaudRate { get; set; }
        public int DataBits { get; set; }
        public StopBits StopBits { get; set; }
        public Parity Parity { get; set; }
        public Handshake Handshake { get; set; }
        public int ReadTimeout { get; set; }
        public int WriteTimeout { get; set; }
        public byte[] PacketSeparateFlag { get; set; }

        public RS232Params()
        {
            ReadTimeout = WriteTimeout = -1;
        }
    }
    /*
    public class RS232Connection : IUFEConnection
    {

        private SerialPort SerialPort { get; set; }
        private UFEPacketCoding Coding { get; set; }
        private PacketParser parser;
        private RS232Params _connParams;
        private const string EOFString = "#EOF#";
        private static readonly byte[] EOF = EOFString.GetBytesUTF8();

        private IFtpManager ftpManager;
        private class SPFtpManager : IFtpManager
        {
            private RS232Connection conn;
            public SPFtpManager(RS232Connection conn)
            {
                this.conn = conn;
            }

            #region IFtpManager Members

            public void Open()
            {
            }

            public bool? IsConnected
            {
                get { return true; }
                set { ;}
            }

            public void Put(string fromFilePath, string toFilePath)
            {
            }

            public void Cancel()
            {
            }

            public void Close()
            {
            }

            #endregion
        }

        public RS232Connection()
        {
            SerialPort = new SerialPort();
            Coding = new UFEPacketCoding();
            State = System.Communication.ConnectionState.Closed;
            User = new User();
            FtpUser = new User();
            ServerLibraries = new List<ServerLibraryItem>();
            Users = new List<User>();
        }

        public IFtpManager FtpManager { get { return ftpManager; } }

        public RS232Params Params
        {
            get
            {
                return _connParams;
            }
            set
            {
                Check.Require(State == ConnectionState.Closed, "State == ConnectionState.Close");
                Check.Require(value != null);
                _connParams = value;
                parser = new PacketParser(EOF, OnReceived);
            }
        }


        public ConnectionMode Mode
        {
            get { return ConnectionMode.RS232; }
        }

        public ISignInfo Sign { get; set; }
        public User User { get; set; }
        public User FtpUser { get; set; }
        public bool CanLock { get; set; }
        public bool Locked { get; set; }

        public List<ServerLibraryItem> ServerLibraries { get; set; }
        public List<User> Users { get; set; }

        public ConnectionState State { get; protected internal set; }

        public event EventHandler ConnectionClosed;
        public event EventHandler<EventArgs<Exception>> ExceptionFired;



        #region IConnection<UFEPacket> Members


        private class OpenAsyncFuture : System.Communication.AsyncFuture<UFEPacket>
        {
            private RS232Connection conn;
            public OpenAsyncFuture(Action<IAsyncContext<UFEPacket>> completedCallback, RS232Connection conn)
            {
                CompletedHandler = completedCallback;
                this.conn = conn;
            }

            public void OnCompleted(UFEPacket resp)
            {
                Packet = resp;
                if (resp.HasError)
                    base.Exception = new Exception(resp.ActionError.Message, Exception);

                IsCompleted = true;

                if (!IsCancelled)
                    OnCompleted();
                else
                {
                    if (cancelHandler.HasValue)
                        cancelHandler.Value.Handler.call(new object[] { cancelHandler.Value.Arg });
                }

                CompletedHandler = null;
            }

            public override bool IsSuccessed
            {
                get
                {
                    return Exception == null;
                }
            }

            public override void Cancel(CancelCallback callback, object arg)
            {
                base.Cancel(callback, arg);
                conn.State = ConnectionState.Closed;
            }

            public override bool IsCompleted { get; protected set; }

            public override void Set()
            {
                if (AsyncResult == null
                    || AsyncResult.AsyncWaitHandle == null)
                    return;
                var mre = AsyncResult.AsyncWaitHandle as ManualResetEvent;
                if (mre != null)
                {
                    mre.Set();
                }
            }

            public override Exception Exception
            {
                get
                {
                    return base.Exception;
                }
                set
                {
                    base.Exception = value;
                    if (value != null)
                    {
                        OnCompleted();
                    }
                }
            }
        }

        public System.Communication.IAsyncFuture Open()
        {
            return OpenAsync(null);
        }

        private void Init()
        {
            Check.Require(State != ConnectionState.Opened);
            Check.Require(Params != null);

            SerialPort.PortName = Params.PortName;
            SerialPort.BaudRate = Params.BaudRate;
            SerialPort.Handshake = Params.Handshake;
            SerialPort.Parity = Params.Parity;
            SerialPort.ReadTimeout = Params.ReadTimeout;
            SerialPort.StopBits = Params.StopBits;
            SerialPort.WriteTimeout = Params.WriteTimeout;
            SerialPort.DataBits = Params.DataBits;
        }

        private OpenAsyncFuture openAsyncFuture;
        public IAsyncFuture OpenAsync(Action<IAsyncContext<UFEPacket>> completedCallback)
        {
            OpenAsyncFuture future = new OpenAsyncFuture(completedCallback, this);
            openAsyncFuture = future;

            Log.InfoFormat("Begin Open.");
            Init();

            State = ConnectionState.Opening;

            Action openCallback = SerialPort.Open;
            try
            {

                future.AsyncResult = openCallback.BeginInvoke(ar =>
                {
                    try
                    {
                        openCallback.EndInvoke(ar);
                        future.Set();
                        if (future.IsSuccessed)
                            OnConnectionOpened();
                    }
                    catch (Exception ex)
                    {
                        future.Exception = new Exception(ex.Message, ex);
                        OnConnectionException(future.Exception);
                    }
                }, null);

            }
            catch (Exception ex)
            {
                future.Exception = new Exception(ex.Message, ex);
                OnConnectionException(future.Exception);
            }
            return future;
        }

        private void OnConnectionException(Exception exception)
        {
            State = ConnectionState.Closed;
        }

        private void OnConnectionOpened()
        {
            try
            {
                Log.InfoFormat("End Open.");
                State = ConnectionState.Opened;
                if (ConnectionOpened != null)
                    ConnectionOpened.call(this, EventArgs.Empty);

                SerialPort.DataReceived += new SerialDataReceivedEventHandler(SerialPort_DataReceived);
            }
            catch (Exception ex)
            {
                OnExceptionFired(ex);
            }
        }

        void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (e.EventType == SerialData.Chars)
            {
                int length = SerialPort.BytesToRead;
                byte[] bytes = new byte[length];
                SerialPort.Read(bytes, 0, length);
                parser.Parse(bytes);
            }
        }

        private void OnReceived(byte[] data)
        {
            var packet = Coding.DecodePacket(data);
            if (packet != null)
            {
                if (packet.HasError)
                    Log.Error("Receive packet:" + packet.ToString());
                else
                    Log.Info("Receive packet:" + packet.ToString());


                if (packet.Command == Commands.GetSignInfo)
                {
                    OnReceived(packet);
                    openAsyncFuture.OnCompleted(packet);
                    return;
                }

                if (packet.Command == Commands.Disconnect)
                {
                    packet.ActionError = new ActionError { Message = "Client too many, the server refuse." };
                    OnReceived(packet);
                    openAsyncFuture.OnCompleted(packet);
                    return;
                }

                if (packet.Command == Commands.Login)
                {
                    if (packet.HasError)
                    {
                        Close();
                        State = ConnectionState.Closed;
                    }
                    else
                    {
                        State = ConnectionState.Opened;
                        if (packet.Role == Role.FileTransfer || packet.Role >= Role.All)
                            ftpManager = new SPFtpManager(this);
                    }
                }

                var task = AsyncFuture<UFEPacket>.Get(packet.Id);
                if (task != null && !task.IsCancelled)
                    OnReceived(packet);
                AsyncFuture<UFEPacket>.OnCompleted(packet);
            }
        }

        private void OnReceived(UFEPacket packet)
        {
            Action<UFEPacket> handler = Received;
            if (handler != null)
            {
                if (packet != null)
                {
                    handler.call(packet);
                }
            }
        }

        private void OnExceptionFired(Exception ex)
        {
            Log.Error(ex.Message, ex);
            if (ExceptionFired != null)
                ExceptionFired.call(this, new EventArgs<Exception>(ex));
        }

        public event EventHandler ConnectionOpened;

        public AsyncFuture<UFEPacket> SendAsync(UFEPacket packt)
        {
            return SendAsync(packt, null);
        }

        public AsyncFuture<UFEPacket> SendAsync(UFEPacket req, Action<IAsyncContext<UFEPacket>> callback)
        {
            Check.Require(req != null);
            Check.Require(Coding != null);

            var future = AsyncFuture<UFEPacket>.Get(callback);
            req.Id = future.Id;
            future.SetProperty("Packet", req);

            if (State != ConnectionState.Opened)
            {
                future.Exception = new Exception("No open serial port");
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
                Action<byte[], int, int> sendHandler = SerialPort.Write;
                future.AsyncResult = sendHandler.BeginInvoke(bytes, 0, length, ar =>
                {
                    try
                    {
                        sendHandler.EndInvoke(ar);
                        //wait response packet
                        future.Reset();
                        future.Wait();
                    }
                    catch (Exception ex)
                    {
                        future.Exception = ex;
                        Close();
                    }
                }, null);
            }
            catch (Exception ex)
            {
                future.Exception = ex;
                Close();
            }
            return future;
        }

        #endregion

        #region IConnectionBase<UFEPacket> Members

        public event Action<UFEPacket> Received;

        public void Send(UFEPacket packt)
        {
            SendAsync(packt, null);
        }

        #endregion

        public IAsyncFuture Close()
        {
            var future = new Future.SimpleFuture();

            if (SerialPort == null || !SerialPort.IsOpen)
            {
                Log.Warn("SerialPort == null || !SerialPort.IsOpen");
                return future;
            }


            try
            {
                Action closeCallback = SerialPort.Close;

                future.AsyncResult = closeCallback.BeginInvoke(p =>
                {
                    try
                    {
                        closeCallback.EndInvoke(future.AsyncResult);
                        Log.Info("Socket close.");
                        future.Set();
                    }
                    catch (Exception ex)
                    {
                        future.Exception = ex;
                        InternalOnConnectionClosed();
                    }

                    OnConnectionClosed();

                }, null);
            }
            catch (Exception ex)
            {
                future.Exception = ex;
                InternalOnConnectionClosed();
            }


            return future;
        }

        private void InternalOnConnectionClosed()
        {
            try
            {
                AsyncFuture<UFEPacket>.CancelAll();

                OnConnectionClosed();
                Log.Info("Connection closed.");
            }
            catch (Exception ex)
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

    }*/
}
