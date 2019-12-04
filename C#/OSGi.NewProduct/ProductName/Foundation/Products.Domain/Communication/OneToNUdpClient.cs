/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ACL
//
// 创 建 人：heng2
// 创建日期：2019/11/26 16:37:03 
// 邮    箱：heng2@163.com
//
// Copyright (C) 2019 ACL，保留所有权利。
//
//----------------------------------------------------------------*/


using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Timers;
using Acl.Core;
using Acl.Log;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对N通信的UdpClient类。
    /// </summary>
    public abstract class OneToNUdpClient : Acl.CompositeDisposable
    {
        #region "Field"

        private DataValidityChecker<uint> _commStateChecker = null;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个 OneToNUdpClient 对象。
        /// </summary>
        protected OneToNUdpClient()
        {

        }

        /// <summary>
        /// 构造一个OneToNUdpClient对象。
        /// </summary>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        protected OneToNUdpClient(uint localCode, IPEndPoint localEndPoint)
        {
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取日志接口。
        /// </summary>
        protected abstract ILog Log { get; }

        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public abstract NodeType LocalType { get; }
        /// <summary>
        /// 获取本地节点的编号。
        /// </summary>
        public uint LocalCode { get; protected set; }
        /// <summary>
        /// 获取本地通信终结点。
        /// </summary>
        public IPEndPoint LocalEndPoint { get; protected set; }

        /// <summary>
        /// 获取 UdpClient 对象。
        /// </summary>
        protected UdpClient LocalClient { get; private set; }

        /// <summary>
        /// 是否允许将套接字绑定到已在使用中的地址？
        /// </summary>
        protected abstract bool ReuseAddress { get; }

        /// <summary>
        /// 获取远程数据的有效期N（秒），当N秒没有收到远程数据时，通知连接中断。
        /// 小于等于0时表示不检查。
        /// </summary>
        protected virtual int RemoteDataExpiredTime { get { return -1; } }

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
        /// 在派生类中重写时，用于获取远程节点的编号。
        /// </summary>
        /// <param name="remoteEndPoint">远程节点使用的IP终结点。</param>
        /// <returns>远程节点的编号。</returns>
        protected abstract uint GetRemoteCode(IPEndPoint remoteEndPoint);
        /// <summary>
        /// 在派生类中重写时，用于获取远程节点的类型。
        /// </summary>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <returns>远程节点的编号。</returns>
        protected abstract NodeType GetRemoteType(uint remoteCode);

        /// <summary>
        /// 在派生类中重写时，用于验证数据是否有效。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        /// <returns>true表示数据是有效的，false 表示数据是无效的。</returns>
        protected virtual bool VerifyData(byte[] data, IPEndPoint remoteEndPoint) { return true; }

        /// <summary>
        /// 在派生类中重写时，用于处理收到的数据。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected abstract void HandleDataReceived(byte[] data, IPEndPoint remoteEndPoint);
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
                this.CloseUdpClient();
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"
        private void OpenUdpClient()
        {
            try
            {
                LocalClient = new UdpClient();

                if (this.ReuseAddress)
                {
                    LocalClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
                }

                LocalClient.Client.Bind(this.LocalEndPoint);
                this.LocalEndPoint.Port = ((IPEndPoint)this.LocalClient.Client.LocalEndPoint).Port;

                // 【远程主机强迫关闭了一个现有的连接0x80004005】的解决方法。http://blog.csdn.net/u010851953/article/details/38258977
                uint IOC_IN = 0x80000000, IOC_VENDOR = 0x18000000;
                uint SIO_UDP_CONNRESET = IOC_IN | IOC_VENDOR | 12;
                LocalClient.Client.IOControl((int)SIO_UDP_CONNRESET, new byte[] { Convert.ToByte(false) }, null);

                // 开始异步接收。
                LocalClient.BeginReceive(ReceiveDataAsync, null);
            }
            catch (System.Exception ex)
            {
                CloseUdpClient();
                this.Log.Error(string.Format("打开UdpClient（{0}）错误，{1}", this.LocalEndPoint, ex.Message));
            }
        }

        private void CloseUdpClient()
        {
            var client = LocalClient;

            if (LocalClient != null)
            {
                LocalClient = null;

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
            try
            {
                if (this.LocalType != NodeType.None && this.GetRemoteType(e.Data) != NodeType.None)
                {
                    var remoteType = this.GetRemoteType(e.Data);

                    var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, this.LocalCode, remoteType, e.Data);

                    GlobalMessageBus.PublishCommStateChanged(args);

                    if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private void BeginReceive()
        {
            try
            {
                if (LocalClient != null)
                {
                    LocalClient.BeginReceive(ReceiveDataAsync, null);
                }
            }
            catch (System.Exception ex)
            {
                this.Log.Error(string.Format("IPEndPoint = {0}。\r\n {1}", LocalClient, ex));
            }
        }

        private void ReceiveDataAsync(IAsyncResult ar)
        {
            try
            {
                if (this.LocalClient == null) return;

                // End Receive.
                IPEndPoint remoteEP = null;
                var data = LocalClient.EndReceive(ar, ref remoteEP);

                // 验证数据是否有效。
                if (!this.VerifyData(data, remoteEP)) return;

                // 获取远程编号。
                var remoteCode = this.GetRemoteCode(remoteEP);

                // 更新连接时间。
                if (_commStateChecker != null)
                {
                    _commStateChecker.Refresh(remoteCode);
                }

                // 在派生类中处理数据。
                this.HandleDataReceived(data, remoteEP);
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex.Message);
            }
            finally
            {
                this.BeginReceive();
            }
        }
        
        private void CheckUdpClient(NetworkAvailabilityEventArgs args)
        {
            try
            {
                if (this.LocalClient == null)
                {
                    this.OpenUdpClient();
                }
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex.ToString());
            }
        }

        private void SubscribeNetworkChangedEvent()
        {
            NetworkChange.NetworkAvailabilityChanged += (sender, args) => CheckUdpClient(args);
            NetworkChange.NetworkAddressChanged += (sender, args) => CheckUdpClient(null);
        }
        #endregion

        #region "Protected methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// 打开。
        /// </summary>
        public void Open()
        {
            this.OpenUdpClient();

            this.StartCommStateChecker();

            this.OnOpen();

            this.SubscribeNetworkChangedEvent();
        }
        #endregion

    }
}
