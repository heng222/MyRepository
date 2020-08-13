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


using System.Net;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对N通信的UdpClient类。
    /// </summary>
    public abstract class One2NUdpClient : M2nUdpClient
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个 OneToNUdpClient 对象。
        /// </summary>
        protected One2NUdpClient()
        {
        }

        /// <summary>
        /// 构造一个OneToNUdpClient对象。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="localEndPoint">本地终结点。</param>
        protected One2NUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
        {
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取本地节点的编号。
        /// </summary>
        public virtual uint LocalCode { get; protected set; }

        #endregion

        #region "Abstract/Virtual methods"
        #endregion

        #region "Override methods"
        ///<inheritdoc/>
        protected override uint GetLocalCode(uint remoteCode, IPEndPoint remoteEndPoint)
        {
            return this.LocalCode;
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Protected methods"
        #endregion

        #region "Public methods"

        /// <summary>
        /// 一个模板方法，在派生类中重写时用于发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        /// <param name="remoteEndPoint">远程终结点。</param>
        public void Send(byte[] data, IPEndPoint remoteEndPoint)
        {
            base.Send(data, this.LocalCode, remoteEndPoint);
        }

        /// <summary>
        /// 将指定的数据发送到远程节点。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        public void Send(byte[] data, uint remoteCode)
        {
            var remoteEndPoints = this.GetRemoteEndPoints(remoteCode);

            remoteEndPoints.ForEach(p => this.Send(data, p));
        }
        #endregion

    }
}
