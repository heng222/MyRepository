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
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
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
    /// 一对多UdpClient包装器。
    /// </summary>
    public abstract class One2MultipleUdpClient : OneToNUdpClient
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个One2MultiplyUdpClient对象。
        /// </summary>
        protected One2MultipleUdpClient()
        {
        }

        /// <summary>
        /// 构造一个One2MultiplyUdpClient对象。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        protected One2MultipleUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
            : base(localType, localCode, localEndPoint)
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Abstract methods"
        /// <summary>
        /// 在派生类中重写时，用于获取远程节点的IP终结点。
        /// </summary>
        /// <param name="remtoeCode">远程节点编号。</param>
        /// <returns>远程节点的IP终结点。</returns>
        protected abstract IEnumerable<IPEndPoint> GetRemoteEndPoints(uint remtoeCode);

        /// <summary>
        /// 一个模板方法，用于发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        public virtual void Send(byte[] data, IPEndPoint remoteEndPoint)
        {
            if (this.LocalClient == null) return;

            // 消息通知。
            if (this.PublishDataOutgoing)
            {
                var remoteID = this.GetRemoteCode(remoteEndPoint);
                var remoteType = this.GetRemoteType(remoteID);
                var args = new DataOutgoingEventArgs(data, this.LocalType, this.LocalCode, remoteType, remoteID);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // 发送
            this.LocalClient.Send(data, data.Length, remoteEndPoint);
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"

        #endregion

        #region "Public methods"

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
