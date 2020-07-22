/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/


using System;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading.Tasks;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对N通信的UdpClient类。
    /// </summary>
    public abstract class OneToNUdpClient : CommEndPoint
    {
        #region "Field"
        private Task _receiveTask;
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
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        protected OneToNUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
            : base(localType, localCode)
        {
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"

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
        /// 在派生类中重写时，用于处理远程终结点。
        /// </summary>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected virtual void HandleRemoteEndPoint(IPEndPoint remoteEndPoint) { }

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

                if (_receiveTask != null)
                {
                    var tmpTask = _receiveTask;
                    _receiveTask = null;
                    tmpTask.Wait();
                }
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"
        private void OpenUdpClient()
        {
            try
            {
                this.LocalClient = new UdpClient();

                if (this.ReuseAddress)
                {
                    this.LocalClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
                }

                this.LocalClient.Client.Bind(this.LocalEndPoint);
                this.LocalEndPoint.Port = ((IPEndPoint)this.LocalClient.Client.LocalEndPoint).Port;

                // 【远程主机强迫关闭了一个现有的连接0x80004005】的解决方法。http://blog.csdn.net/u010851953/article/details/38258977
                uint IOC_IN = 0x80000000, IOC_VENDOR = 0x18000000;
                uint SIO_UDP_CONNRESET = IOC_IN | IOC_VENDOR | 12;
                this.LocalClient.Client.IOControl((int)SIO_UDP_CONNRESET, new byte[] { Convert.ToByte(false) }, null);

                // 开始异步接收。
                if (this.AllowReceive)
                {
                    _receiveTask = this.ReceiveAsync();
                }
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

        private async Task ReceiveAsync()
        {
            while (this.LocalClient != null)
            {
                try
                {
#pragma warning disable CA2007 // Consider calling ConfigureAwait on the awaited task
                    var recvResult = await this.LocalClient.ReceiveAsync();
#pragma warning restore CA2007 // Consider calling ConfigureAwait on the awaited task
                    var remoteEP = recvResult.RemoteEndPoint;
                    var remoteCode = this.GetRemoteCode(remoteEP);
                    var remoteType = this.GetRemoteType(remoteCode);

                    // 处理远程终结点。
                    this.HandleRemoteEndPoint(remoteEP);

                    // DataTransfer 消息通知。                
                    this.PublishDataTransferEvent(remoteType, remoteCode, true, recvResult.Buffer);

                    // CommLogCreated 消息通知。
                    this.PublishCommLogCreateEvent(remoteType, remoteCode, true, recvResult.Buffer);

                    // 数据是否有效？
                    if (!this.VerifyData(recvResult.Buffer, remoteEP)) continue;

                    // 在派生类中处理数据。
                    this.HandleDataReceived(recvResult.Buffer, remoteEP);

                    // 更新连接时间。
                    this.RefreshCommState(remoteCode);
                }
                catch (System.Exception ex)
                {
                    if (this.LocalClient != null) this.Log.Error(ex.Message);
                }
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

            this.OnOpen();

            this.SubscribeNetworkChangedEvent();
        }
        #endregion

    }
}
