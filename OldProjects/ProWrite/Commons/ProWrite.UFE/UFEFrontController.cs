using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.Threading;
using System.Windows.Forms;
using System.ComponentModel;
using ProWrite.UFE.Responses;
using System.Diagnostics;
using System.Text.RegularExpressions;
using log4net;
using System.Communication;
using ProWrite.UFE.Entity;
using System.Net.Tcp;

namespace ProWrite.UFE
{
    public partial class UFEFrontController<TConnection> : FrontControllerBase<TConnection, UFEFilterProcessor, UFEFilter, UFEActionProcessor, IUFEAction, UFEPacket>
        , IUFEFrontController <TConnection>
        , ILogManager
        , IMAManager
        where TConnection :IUFEConnection,new() 
    {
        public ISignInfo Sign { get; private set; }

        private IFileManager fileMgr;
        private IUserManager userMgr;
        public UFEFrontController(ISignInfo name)
        {
            Sign = name;
            ActionProcessor.FrontController = this;

            Init();
        }

        public override void Init()
        {
            base.Init();
            fileMgr = new FileManagerImp(this);
            userMgr = new UserManagerImp(this);
            Connection.Sign = Sign;
        }

        IUFEConnection IUFEFrontController.Connection
        {
            get { return base.Connection; }
        }


        #region ISignController 
        
        public IUserManager UserManager
        {
            get { return userMgr; }
        }


        public IFileManager FileManager
        {
            get { return fileMgr; }
        }

        public ILogManager LogManager
        {
            get { return this; }
        }

        public IMAManager MAManager
        {
            get { return this; }
        }
        #endregion

        
        private bool IsConnected
        {
            get
            {
                return Connection.State == ConnectionState.Opened;
            }
        }

        public AsyncFuture<UFEPacket> SendAsync(Commands cmd)
        {
            return SendAsync(cmd, null,null);
        }

        public AsyncFuture<UFEPacket> SendAsync(Commands cmd, Action<IAsyncContext<UFEPacket>> callback)
        {
            const uint defaultRetryCount = 1;
            return SendAsync(cmd, callback, null, defaultRetryCount);
        }

        public AsyncFuture<UFEPacket> SendAsync(Commands cmd, object body)
        {
            const uint defaultRetryCount = 1;
            return SendAsync(cmd, null, body, defaultRetryCount);
        }

        public AsyncFuture<UFEPacket> SendAsync(Commands cmd, Action<IAsyncContext<UFEPacket>> callback, object body)
        {
            const uint defaultRetryCount = 1;
            return SendAsync(cmd, callback, body, defaultRetryCount);
        }

        private User User
        {
            get { return Connection.User; }
        }

        internal AsyncFuture<UFEPacket> SendAsync(Commands cmd, Action<IAsyncContext<UFEPacket>> callback, object body, uint retryCount)
        {
            var req = new UFEPacket();
            req.UserId = User.Id;
            req.Role = User.Role;
            req.Command = cmd;
            req.Content = body;

            Log.Info("Send [" + cmd.ToString() + "] packet");
            return base.SendAsync(req,callback);
        }

        protected override void OnConnectionException(object sender, EventArgs<Exception> e)
        {
            base.OnConnectionException(sender, e);
            Log.Error(e.First.Message, e.First);
        }

        protected override void OnConnectionClosed(object sender, EventArgs e)
        {
            base.OnConnectionClosed(sender, e);
            Connection.User.Status = UserStatus.Offline;
            if(Connection.Users!=null && Connection.Users.Count>0)
                Connection.Users.Clear();
            if(Connection.ServerLibraries!=null && Connection.ServerLibraries.Count>0)
                Connection.ServerLibraries.Clear();
        }

    }
}
