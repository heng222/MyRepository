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

using System.Collections.Generic;
using System.Net;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 一对一UdpClient包装器。
    /// </summary>
    public abstract class One2OneUdpClient : One2NUdpClient
    {
        #region "Field"
        private IEnumerable<IPEndPoint> _remoteEndPoints;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        protected One2OneUdpClient()
        {
            this.RemoteType = NodeType.None;
        }

        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="remoteType">远程节点类型。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        protected One2OneUdpClient(NodeType localType, uint localCode,
            NodeType remoteType, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
            : base(localType, localCode, localEndPoint)
        {
            this.RemoteType = remoteType;
            this.RemoteCode = remoteCode;
            this.RemoteEndPoint = remoteEndPoint;

            _remoteEndPoints = new IPEndPoint[] { this.RemoteEndPoint };
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public NodeType RemoteType { get; }

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
        /// 一个模板方法，在派生类中重写时用于发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        public virtual void Send(byte[] data)
        {
            if (this.RemoteEndPoint == null) return;

            base.Send(data, this.RemoteEndPoint);
        }
        #endregion

        #region "Override methods"
        ///<inheritdoc/>
        protected sealed override uint GetRemoteCode(IPEndPoint remoteEndPoint)
        {
            return this.RemoteCode;
        }

        ///<inheritdoc/>
        protected sealed override NodeType GetRemoteType(uint remoteCode)
        {
            return this.RemoteType;
        }

        ///<inheritdoc/>
        protected sealed override IEnumerable<IPEndPoint> GetRemoteEndPoints(uint remoteCode)
        {
            return _remoteEndPoints;
        }

        ///<inheritdoc/>
        protected sealed override void HandleRemoteEndPoint(IPEndPoint remoteEndPoint)
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
