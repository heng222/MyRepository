//---------------------------------------------------------------------
//
// File: TcpConnection.cs
//
// Description:
// Tcp Connection class
//
// Author: Kevin
// 
// Modify History:
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.IO;
using System.ComponentModel;
using System.Threading;
using ProWrite.Core;
using System.Security.Authentication;
using System.Diagnostics;
using Org.Mentalis.Network.ProxySocket;
using System.Net.Tcp;
using Tamir.SharpSsh;
using ProWrite.UFE.Entity;
using System.Threading.Tasks;
using log4net;
using System.Communication;

namespace ProWrite.UFE
{
    public class TcpUFEConnection : System.Net.Tcp.TcpProxyConnection<EncryptionCoding, UFEPacket>, IUFEConnection
    {
        public TcpUFEConnection()
        {
            State = System.Communication.ConnectionState.Closed;
            User = new User();
            FtpUser = new User();
            ServerLibraries = new List<ServerLibraryItem>();
            Users = new List<User>();
        }

        public User User { get; set; }
        public User FtpUser { get; set; }
        public bool CanLock { get; set; }
        public bool Locked { get; set; }
        public ISignInfo Sign { get; set; }

        public List<ServerLibraryItem> ServerLibraries { get; set; }
        public List<User> Users { get; set; }

        public ConnectionMode Mode { get { return ConnectionMode.Tcp; } }


        private SFtpManager ftpMgr;
        public IFtpManager FtpManager 
        { 
            get {
                if (ftpMgr == null && Params.EndPoint != null)
                    ftpMgr= new SFtpManager(Params.EndPoint.Address.ToString(), FtpUser.Account, FtpUser.NoSecurityPWD);
                else if (ftpMgr.IsNewAddress(Params.EndPoint.Address.ToString(), FtpUser.Account, FtpUser.NoSecurityPWD))
                    ftpMgr = new SFtpManager(Params.EndPoint.Address.ToString(), FtpUser.Account, FtpUser.NoSecurityPWD);
                return ftpMgr;
            }

        }
        //private Task openFtpTask;

        #region Open
        private class OpenAsyncFuture : System.Communication.AsyncFuture<UFEPacket>
        {
            private TcpUFEConnection conn;
            public OpenAsyncFuture(Action<IAsyncContext<UFEPacket>> completedCallback, TcpUFEConnection conn)
            {
                CompletedHandler = completedCallback;
                this.conn = conn;
            }

            public void OnCompleted(UFEPacket resp)
            {
                Packet = resp;
                if (resp.HasError)
                    base.Exception = new NetException(resp.ActionError.Message,Exception);

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
                if (conn.Socket.Connected)
                    conn.Close();
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
                    try
                    {
                        mre.Set();
                    }
                    catch
                    { }
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

        OpenAsyncFuture openAsyncFuture;
        public override System.Communication.IAsyncFuture Open()
        {
            return OpenAsync(null);
        }

        protected override IAsyncFuture CreateOpenFuture()
        {
            openAsyncFuture = new OpenAsyncFuture(completedCallback,this);
            return openAsyncFuture;
        }

        Action<IAsyncContext<UFEPacket>> completedCallback;
        public IAsyncFuture OpenAsync(Action<IAsyncContext<UFEPacket>> completedCallback)
        {
            this.completedCallback = completedCallback;
            return base.Open();;
        }

        #endregion

        protected override void OnConnectionOpened()
        {
            base.OnConnectionOpened();
            State = ConnectionState.Opening;
        }

        protected override void OnReceived(UFEPacket resp)
        {
            if (resp == null)
                return;

            if (resp.Command == Commands.GetSignInfo)
            {
                RaiseReceived(resp);
                openAsyncFuture.OnCompleted(resp);
                return;
            }

            if (resp.Command == Commands.Disconnect)
            {
                resp.ActionError = new ActionError { Message = "Client too many, the server refuse." };
                base.OnReceived(resp);
                openAsyncFuture.OnCompleted(resp);
                return;
            }

            //base.OnReceived(resp);
            if (resp.Command == Commands.PlayCompleted)
            {
                if (resp.Content != null)
                {
                    try
                    {
                        string messageId = resp.Content.GetProperty<string>("UpcomingMessageUUID");

                        string messageInfo = resp.Content.GetProperty<string>("UpcomingMessageName");
                        string scheduleInfo = resp.Content.GetProperty<string>(" CurrentScheduleName");
                        string plsylistInfo = resp.Content.GetProperty<string>("UpcomingPlaylistName");
                        string endTime = resp.Content.GetProperty<string>(" FinishedTime");
                        MessageBus.Send(this, new PlayComplete(messageId,messageInfo,scheduleInfo,plsylistInfo,endTime));
                    }
                    catch { }
                }
                

            }
            if (resp.Command == Commands.Login)
            
            {
                if (resp.HasError)
                {
                    State = ConnectionState.Closed;
                    base.OnReceived(resp);
                    Close();
                    return;
                }
                else 
                {
                    State = ConnectionState.Opened;
                    //if (resp.Role == Role.FileTransfer || resp.Role >= Role.All)
                    //{
                    //    Exception error = null;
                    //    var openFtpTask = Task.Create(p =>
                    //    {
                    //        string ftpHost = Params.EndPoint.Address.ToString();
                    //        ftpMgr = new SFtpManager(ftpHost, FtpUser.Account, FtpUser.NoSecurityPWD);
                    //        Log.Info("Begin Open Ftp Server......");
                    //        try
                    //        {
                    //            ftpMgr.OpenTask = Task.Current;
                    //            //SFtpManager.Current = ftpMgr;

                    //            ftpMgr.Open();
                    //            ftpMgr.IsConnected = true;
                    //            Log.Info("End Open Ftp Server.");
                    //        }
                    //        catch (Exception ex)
                    //        {
                    //            error = ex;
                    //            if (ftpMgr != null)
                    //                ftpMgr.IsConnected = false;
                    //            Log.Error("Connect SFtp failed!", ex);
                    //        }

                    //    });
                    //}
                }
            }
            base.OnReceived(resp);
        }

       
        protected override void OnReceivedHeartPacket(byte[] packet)
        {
            base.OnReceivedHeartPacket(packet);
            //Log.Info(packet.GetStringUTF8());
        }


        protected override void OnConnectionClosed()
        {
            if(User!=null)
                User.Status = UserStatus.Offline;
            if(Users!=null && Users.Count>0)
                Users.Clear();
            if(ServerLibraries!=null && ServerLibraries.Count>0)
                ServerLibraries.Clear();

            CanLock = false;

            if (ftpMgr != null && ftpMgr.Connected)
            {
                try
                {
                    ftpMgr.Close();
                }
                catch(Exception e)
                {
                    Log.Error("ftpMgr close exception:" + e.Message);
                }
                ftpMgr = null;
            }

            if (openAsyncFuture != null)
                openAsyncFuture.Close();
            openAsyncFuture = null;

            base.OnConnectionClosed();
        }
    }
}
