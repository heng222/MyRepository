using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace System.Communication
{
    public abstract class FrontControllerBase<TConnection, TFilterProcessor, TFilter, TActionProcessor, TAction, TPacket> : DisposableObject
           , IFrontController<TConnection, TFilterProcessor,TFilter, TActionProcessor, TAction, TPacket>
        where TConnection : IConnection<TPacket>, new()
        where TFilterProcessor : IFilterProcessor<TFilter, TPacket>, new()
        where TFilter : IFilter<TPacket>
        where TActionProcessor : IActionProcessor<TAction, TPacket>, new()
        where TAction : IAction<TPacket>
        where TPacket : IPacket
    {

        private TConnection conn;
        private TFilterProcessor filterProcessor;
        private TActionProcessor actionProcessor;

        private Dictionary<string, object> _cookie; 

        public FrontControllerBase()
        {
            _cookie = new Dictionary<string, object>();
            conn = new TConnection();
            filterProcessor = new TFilterProcessor();
            actionProcessor = new TActionProcessor();
            conn.ConnectionOpened += OnConnectionOpened;
        }

        public object this[string name]
        {
            get
            {
                if (_cookie.ContainsKey(name))
                    return _cookie[name];
                return null;
            }
            set
            {
                _cookie[name] = value;
            }
        }

        public TConnection Connection
        {
            get { return conn; }
        }

        public TActionProcessor ActionProcessor
        {
            get { return actionProcessor; }
        }

        public TFilterProcessor FilterProcessor
        {
            get { return filterProcessor; }
        }

        public virtual void Init()
        {
            actionProcessor.Init();
        }

        public virtual void Process(TPacket packet)
        {
            Check.Require(packet != null);
            if (FilterProcessor != null)
                FilterProcessor.Process(packet);

            if (packet.HasError)
                return;

            if (ActionProcessor != null)
                ActionProcessor.Process(packet);
        }

        public virtual AsyncFuture<TPacket> SendAsync(TPacket req)
        {
            Check.Require(conn.State == ConnectionState.Opened || conn.State == ConnectionState.Opening);
            return conn.SendAsync(req);
        }

        public virtual AsyncFuture<TPacket> SendAsync(TPacket req, Action<IAsyncContext<TPacket>> completedCallback)
        {
            Check.Require(conn.State == ConnectionState.Opened || conn.State == ConnectionState.Opening);
            return conn.SendAsync(req,completedCallback);
        }

       

        public virtual void Send(TPacket packet)
        {
            Check.Require(conn.State == ConnectionState.Opened || conn.State == ConnectionState.Opening);
            conn.Send(packet);
        }

        private void SubscribeConnectionEvent()
        {
            Connection.Received += Process;
            Connection.ConnectionClosed += OnConnectionClosed;
            Connection.ExceptionFired += new EventHandler<EventArgs<Exception>>(OnConnectionException);
        }

        protected virtual void OnConnectionOpened(object sender, EventArgs e)
        {
            SubscribeConnectionEvent();
        }

        protected virtual void OnConnectionClosed(object sender, EventArgs e)
        {
            UnSubscribeConnectionEvent();
        }

        private void UnSubscribeConnectionEvent()
        {
            Connection.Received -= Process;
            Connection.ConnectionClosed -= OnConnectionClosed;
            Connection.ExceptionFired -= OnConnectionException;
        }

        protected virtual void OnConnectionException(object sender, EventArgs<Exception> e)
        {

        }

        public virtual void Destroy()
        {
            if (conn != null)
                conn.Close();
            if (actionProcessor != null)
                actionProcessor.Destroy();
        }

        protected override void Dispose(bool disposing)
        {
            Destroy();
            base.Dispose(disposing);
        }

        #region IFrontController<TConnection,TFilterProcessor,TFilter,TActionProcessor,TAction,TPacket> Members


       

        #endregion
    }
}
