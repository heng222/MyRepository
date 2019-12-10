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
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Acl.Log;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 一对一UdpClient包装器。
    /// </summary>
    public abstract class One2OneUdpClient : OneToNUdpClient
    {
        #region "Field"

        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        protected One2OneUdpClient()
        {
        }

        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected One2OneUdpClient(uint localCode, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
            : base(localCode, localEndPoint)
        {
            this.RemoteCode = remoteCode;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// 获取远程节点的编号。
        /// </summary>
        public uint RemoteCode { get; protected set; }
        /// <summary>
        /// 获取远程通信终结点。
        /// </summary>
        public IPEndPoint RemoteEndPoint { get; protected set; }

        #endregion

        #region "Abstract/Virtual methods"

        /// <summary>
        /// 一个模板方法，用于发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        public virtual void Send(byte[] data)
        {
            if (this.LocalClient == null || this.RemoteEndPoint == null) return;

            // 消息通知。
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // 发送
            this.LocalClient.Send(data, data.Length, this.RemoteEndPoint);
        }
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
            }

            base.Dispose(disposing);
        }

        /// <summary>
        /// 在派生类中重写时，用于获取远程节点的编号。
        /// </summary>
        /// <param name="remoteEndPoint">远程节点使用的IP终结点。</param>
        /// <returns>远程节点的编号。</returns>
        protected override uint GetRemoteCode(IPEndPoint remoteEndPoint)
        {
            return this.RemoteCode;
        }

        /// <summary>
        /// 在派生类中重写时，用于获取远程节点的类型。
        /// </summary>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <returns>远程节点的编号。</returns>
        protected override NodeType GetRemoteType(uint remoteCode)
        {
            return this.RemoteType;
        }

        /// <summary>
        /// 在派生类中重写时，用于处理收到的数据。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected override void HandleDataReceived(byte[] data, IPEndPoint remoteEndPoint)
        {
            if (this.RemoteEndPoint == null)
            {
                this.RemoteEndPoint = remoteEndPoint;
            }
        }
        #endregion

        #region "Private methods"

        #endregion

        #region "Public methods"
        #endregion
    }
}
