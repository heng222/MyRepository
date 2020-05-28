/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2020/5/26 19:35:28 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2020 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using Acl.Core;
using Acl.Log;

using Products.Infrastructure;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对1通信的TCP客户端通信类。
    /// <para>注：1个TCP客户端只能与1个TCP服务器通信。</para>
    /// </summary>
    public abstract class One2OneTcpClient : Acl.CompositeDisposable
    {
        #region "Filed"
        private DataValidityChecker<uint> _commStateChecker = null;

        /// <summary>
        /// 接收缓存。
        /// </summary>
        private byte[] _receiveBuffer = new byte[128];


        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="remoteType">远程节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected One2OneTcpClient(NodeType localType, NodeType remoteType,
            uint localCode, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
        {
            this.LocalType = localType;
            this.RemoteType = remoteType;

            this.LocalCode = localCode;
            this.RemoteCode = remoteCode;

            this.LocalEndPoint = localEndPoint;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取日志接口。
        /// </summary>
        protected abstract ILog Log { get; }

        /// <summary>
        /// 获取 UdpClient 对象。
        /// </summary>
        protected TcpClient TcpClient { get; private set; }

        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public NodeType LocalType { get; private set; }
        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public NodeType RemoteType { get; private set; }
        /// <summary>
        /// 获取本地节点的编号。
        /// </summary>
        public uint LocalCode { get; protected set; }
        /// <summary>
        /// 获取远程节点的编号。
        /// </summary>
        public uint RemoteCode { get; protected set; }

        /// <summary>
        /// 获取本地通信终结点。
        /// </summary>
        public IPEndPoint LocalEndPoint { get; protected set; }
        /// <summary>
        /// 获取远程通信终结点。
        /// </summary>
        public IPEndPoint RemoteEndPoint { get; protected set; }

        /// <summary>
        /// 获取远程数据的有效期N（秒），当N秒没有收到远程数据时，通信中断。
        /// 小于等于0时表示不检查。
        /// </summary>
        protected virtual int RemoteDataExpiredTime { get { return Timeout.Infinite; } }

        /// <summary>
        /// 是否在全局总线上发布CommStateChanged消息？
        /// </summary>
        protected virtual bool PublishCommStateChanged { get { return true; } }
        /// <summary>
        /// 是否在全局总线上发布DataIncoming消息？
        /// </summary>
        protected virtual bool PublishDataIncoming { get { return true; } }
        /// <summary>
        /// 是否在全局总线上发布DataOutgoing消息？
        /// </summary>
        protected virtual bool PublishDataOutgoing { get { return true; } }

        /// <summary>
        /// 一个事件，当与远程节点通信状态改变时引发。
        /// </summary>
        public event EventHandler<CommStateChangedEventArgs> CommStateChanged;
        #endregion

        #region "Abstract/Virtual methods"
        /// <summary>
        /// 在派生类中重写时，用于处理初始化事件。
        /// </summary>
        protected virtual void OnOpen() { }

        /// <summary>
        /// 在派生类中重写时，用于验证数据是否有效。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <param name="len">数据的有效长度。</param>
        /// <returns>true表示数据是有效的，false 表示数据是无效的。</returns>
        protected virtual bool VerifyData(byte[] data, int len) { return true; }

        /// <summary>
        /// 在派生类中重写时，用于处理收到的数据。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <param name="len">数据的有效长度。</param>
        protected abstract void HandleDataReceived(byte[] data, int len);
        #endregion

        #region "Override methods"
        /// <summary>
        /// 释放资源。
        /// </summary>
        /// <param name="disposing">是否释放托管资源？</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                this.CloseTcpClient();
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"

        private void CreateTcpClient()
        {
            if (TcpClient == null)
            {
                TcpClient = new TcpClient(this.LocalEndPoint);
            }
        }

        private void CloseTcpClient()
        {
            var client = TcpClient;

            if (TcpClient != null)
            {
                TcpClient = null;

                client.Close();
            }
        }

        private void StartCommStateChecker()
        {
            if (this.RemoteDataExpiredTime > 0 && _commStateChecker == null)
            {
                _commStateChecker = new DataValidityChecker<uint>(this.RemoteDataExpiredTime);
                this.AddDisposable(_commStateChecker);
                _commStateChecker.DataValidityChanged += CommStateChecker_DataValidityChanged;

                _commStateChecker.Open();
            }
        }

        private void CommStateChecker_DataValidityChanged(object sender, DataValidityChangedEventArgs<uint> e)
        {
            if (this.PublishCommStateChanged)
            {
                try
                {
                    Task.Factory.StartNew(() =>
                    {
                        var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, this.LocalCode, this.RemoteType, e.Data);
                        GlobalMessageBus.PublishCommStateChanged(args);

                        if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                    });
                }
                catch (System.Exception /*ex*/)
                {
                }
            }
        }

        private void BeginConnectAsyn(int delay)
        {
            Task.Factory.StartNew(() =>
            {
                Thread.Sleep(delay);
                this.BeginConnect();
            });
        }

        private void BeginConnect()
        {
            try
            {
                if (this.IsDisposed) return;

                this.CloseTcpClient();

                this.CreateTcpClient();

                TcpClient.BeginConnect(this.RemoteEndPoint.Address, this.RemoteEndPoint.Port, ConnectCallBack, null);
            }
            catch (Exception ex)
            {
                this.Log.Error(string.Format("{0}，{1}", this.LocalEndPoint, ex.Message));

                this.BeginConnectAsyn(30000);
            }
        }

        private void ConnectCallBack(IAsyncResult rc)
        {
            try
            {
                if (TcpClient != null) TcpClient.EndConnect(rc);

                // 更新连接时间。
                if (_commStateChecker != null) _commStateChecker.Refresh(this.RemoteCode);

                // 连接成功后，开始接收数据。
                this.BeginReceive();
            }
            catch (Exception ex)
            {
                this.Log.Error(ex);
                this.BeginConnectAsyn(30000);
            }
        }

        private void BeginReceive()
        {
            try
            {
                if (this.IsDisposed) return;

                TcpClient.Client.BeginReceive(_receiveBuffer, 0, _receiveBuffer.Length, SocketFlags.None, ReceiveCallBack, TcpClient);
            }
            catch (Exception ex)
            {
                Task.Factory.StartNew(() =>
                {
                    Thread.Sleep(3000);
                    this.BeginReceive();
                });
            }
        }

        private void ReceiveCallBack(IAsyncResult rc)
        {
            int count = 0;

            try
            {
                if (this.TcpClient != null) count = TcpClient.Client.EndReceive(rc);

                if (count > 0)
                {
                    // 消息通知。
                    if (this.PublishDataIncoming)
                    {
                        var args = new DataIncomingEventArgs(_receiveBuffer.Take(count).ToArray(),
                            this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                        GlobalMessageBus.PublishDataIncoming(args, this);
                    }

                    // 验证数据是否有效。
                    if (!this.VerifyData(_receiveBuffer, count)) return;

                    // 在派生类中处理数据。
                    this.HandleDataReceived(_receiveBuffer, count);

                    // 更新连接时间。
                    if (_commStateChecker != null) _commStateChecker.Refresh(this.RemoteCode);
                }
                // 字节数为0表示服务器主动关闭连接。
                else
                {
                    this.BeginConnectAsyn(30000);
                }
            }
            catch (SocketException ex)
            {
                count = 0;
                this.Log.Error(string.Format($"{ex.Message} SocketErrorCode = {ex.SocketErrorCode}"));
                this.BeginConnectAsyn(30000);
            }
            catch (Exception ex)
            {
                this.Log.Error(ex);
            }
            finally
            {
                if (count > 0) this.BeginReceive();
            }
        }

        #endregion

        #region "Public methods"

        /// <summary>
        /// 打开。
        /// </summary>
        public void Open()
        {
            this.BeginConnect();

            this.StartCommStateChecker();

            this.OnOpen();
        }

        /// <summary>
        /// 发送数据。
        /// </summary>
        public void Send(byte[] buffer)
        {
            // 消息通知。 
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(buffer, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // 如果已经连接，则发送数据。
            if (this.TcpClient != null && this.TcpClient.Connected)
            {
                var stream = this.TcpClient.GetStream();
                stream.Write(buffer, 0, buffer.Length);
            }
        }

        #endregion
    }
}
