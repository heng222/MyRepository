/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2013-7-23 15:14:23 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// （节点间）通信状态变化事件参数类
    /// </summary>
    public sealed class CommStateChangedEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个连接变化事件参数类
        /// </summary>
        /// <param name="commState">通信状态。</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localId">本地节点编号。</param>
        /// <param name="remoteType">远程节点类型。</param>
        /// <param name="remoteId">远程节点编号。</param>
        public CommStateChangedEventArgs(bool? commState,
            NodeType localType, uint localId,
            NodeType remoteType, uint remoteId)
        {
            this.CommState = commState;

            this.LocalNodeType = localType;
            this.LocalNodeCode = localId;
            this.RemoteNodeType = remoteType;
            this.RemoteNodeCode = remoteId;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取节点间的通信状态。
        /// <para>true表示通信正常，false表示通信异常，null表示未知。</para>
        /// </summary>
        public bool? CommState { get; set; }

        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public NodeType LocalNodeType { get; set; }
        /// <summary>
        /// 此事件对应的本地设备ID(此ID为设备在 本系统 中的编号，并非与接口通信时使用的编号)
        /// </summary>
        public UInt32 LocalNodeCode { get; set; }

        /// <summary>
        /// 此事件对应的对方设备类型
        /// </summary>
        public NodeType RemoteNodeType { get; set; }
        /// <summary>
        /// 此事件对应的对方设备ID(此ID为设备在 本系统 中的编号，并非与接口通信时使用的编号)
        /// </summary>
        public UInt32 RemoteNodeCode { get; set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
