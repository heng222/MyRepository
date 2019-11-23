/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：有轨电车仿真
//
// 创 建 人：heng222_z
// 创建日期：2019/11/14 10:50:55 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2019 泰可斯，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Acl.Log;
using Products.Domain.Utility;
using Products.Infrastructure.Events;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 一对多UdpClient包装器。
    /// </summary>
    public abstract class One2MultiplyUdpClient : Acl.CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// 最后一次检查IP地址是否可用的时间。
        /// </summary>
        private DateTime _lastIpCheckTime = DateTime.MinValue;

        /// <summary>
        /// Key = Remote Node Code.
        /// Value = 最后一次收到的数据的时间。
        /// </summary>
        private ConcurrentDictionary<uint, DateTime> _dataTimestamp = new ConcurrentDictionary<uint, DateTime>();

        /// <summary>
        /// 1、检查指定的IPEndPoint是否可用。
        /// 2、检查本节点与对方节点的连接状态。
        /// </summary>
        private System.Timers.Timer _checkTimer;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个One2MultiplyUdpClient对象。
        /// </summary>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        protected One2MultiplyUdpClient(uint localCode, IPEndPoint localEndPoint)
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
        public uint LocalCode { get; private set; }
        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public abstract NodeType RemoteType { get; }

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

        #region "Abstract methods"
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
        /// 在派生类中重写时，用于获取远程节点的IP终结点。
        /// </summary>
        /// <param name="remtoeCode">远程节点编号。</param>
        /// <returns>远程节点的IP终结点。</returns>
        protected abstract List<IPEndPoint> GetRemoteEndPoints(uint remtoeCode);

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
                this.CloseTimer();
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

        private int GetTimerInterval()
        {
            var timeSpan = TimeSpan.FromSeconds(this.RemoteDataExpiredTime);
            if (timeSpan.TotalMinutes > 1)
            {
                return 60000; // 60 秒
            }
            else if(timeSpan.TotalSeconds >= 30)
            {
                return 5000; // 5秒
            }
            else
            {
                return 1000; // 1 秒
            }
        }

        private void StartCheckTimer()
        {
            if (this.RemoteDataExpiredTime > 0)
            {
                var interval = GetTimerInterval();
                _checkTimer = new System.Timers.Timer(interval);
                _checkTimer.AutoReset = false;
                _checkTimer.Elapsed += OnCheckTimerElapsed;
                _checkTimer.Start();
            }
        }

        private void OnCheckTimerElapsed(object sender, ElapsedEventArgs e)
        {
            try
            {
                // 尝试打开UdpClient
                if (this.LocalClient == null
                    && (DateTime.Now - _lastIpCheckTime).Minutes > 1)
                {
                    _lastIpCheckTime = DateTime.Now;
                    this.OpenUdpClient();
                }

                // 检查连接状态。
                this.UpdateConnectionState();
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex);
            }
            finally
            {
                if (_checkTimer != null) _checkTimer.Start();
            }
        }

        private void UpdateConnectionState()
        {
            if (this.RemoteDataExpiredTime <= 0) return;

            _dataTimestamp.ToList().ForEach(p =>
            {
                if ((DateTime.Now - p.Value).TotalSeconds >= this.RemoteDataExpiredTime)
                {
                    DateTime value;
                    _dataTimestamp.TryRemove(p.Key, out value);

                    // 通知连接中断。
                    var args = new CommStateChangedEventArgs(false, this.LocalType, this.LocalCode, this.RemoteType, p.Key);
                    this.NotifyCommStateChanged(args);
                }
            });
        }

        private void CloseTimer()
        {
            var tmpTimer = _checkTimer;
            _checkTimer = null;

            if (tmpTimer != null)
            {
                tmpTimer.Close();
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
                if (LocalClient != null)
                {
                    IPEndPoint remoteEP = null;
                    var stream = LocalClient.EndReceive(ar, ref remoteEP);

                    // 获取远程编号。
                    var remoteCode = this.GetRemoteCode(remoteEP);
                    
                    // 更新连接时间。
                    var existed = _dataTimestamp.ContainsKey(remoteCode);
                    _dataTimestamp.AddOrUpdate(remoteCode, DateTime.Now, (key, oldValue) => DateTime.Now);

                    // 通知连接状态
                    if (!existed)
                    {
                        var args = new CommStateChangedEventArgs(true, this.LocalType, this.LocalCode, this.RemoteType, remoteCode);
                        this.NotifyCommStateChanged(args);
                    }

                    // 在派生类中处理数据。
                    this.HandleDataReceived(stream, remoteEP);
                }
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

        private void NotifyCommStateChanged(CommStateChangedEventArgs args)
        {
            try
            {
                if (this.CommStateChanged != null) this.CommStateChanged(this, args);
            }
            catch (System.Exception /*ex*/)
            {
            }
        }
        #endregion

        #region "Public methods"      
        /// <summary>
        /// 打开。
        /// </summary>
        public void Open()
        {
            this.OpenUdpClient();

            this.StartCheckTimer();

            this.OnOpen();
        }

        /// <summary>
        /// 发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        public void Send(byte[] data, IPEndPoint remoteEndPoint)
        {
            if (this.LocalClient == null) return;

            this.LocalClient.Send(data, data.Length, remoteEndPoint);
        }

        /// <summary>
        /// 将指定的数据发送到远程节点。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        public void Send(byte[] data, uint remoteCode)
        {
            if (this.LocalClient == null) return;

            var remoteEndPoints = this.GetRemoteEndPoints(remoteCode);

            remoteEndPoints.ForEach(p => this.Send(data, p));
        }
        #endregion
    }
}
