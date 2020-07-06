/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2020/4/9 16:54:57 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2020 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 一个事件参数类，在产生新的通信日志事件中使用。
    /// </summary>
    public class CommLogCreatedEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"

        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="remoteType">对方节点类型。</param>
        /// <param name="remoteCode">对方节点编号。</param>
        /// <param name="isIncoming">是否为输入流。</param>
        /// <param name="data">数据流。</param>
        public CommLogCreatedEventArgs(NodeType localType, uint localCode,
            NodeType remoteType, uint remoteCode, bool isIncoming, byte[] data)
        {
            this.Timestamp = DateTime.Now;
            this.LocalNodeType = localType;
            this.LocalNodeCode = localCode;
            this.RemoteNodeType = remoteType;
            this.RemoteNodeCode = remoteCode;
            this.IsIncomingData = isIncoming;
            this.Data = data;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 本地节点类型。
        /// </summary>
        public NodeType LocalNodeType { get; private set; }
        /// <summary>
        /// 本地节点编号。
        /// </summary>
        public uint LocalNodeCode { get; private set; }

        /// <summary>
        /// 对方节点类型。
        /// </summary>
        public NodeType RemoteNodeType { get; private set; }
        /// <summary>
        /// 对方节点编号。
        /// </summary>
        public uint RemoteNodeCode { get; private set; }

        /// <summary>
        /// 是否为输入数据流？
        /// true表示输入数据流，fasle表示输出数据流。
        /// </summary>
        public bool IsIncomingData { get; private set; }

        /// <summary>
        /// 新产生的数据流。
        /// </summary>
        public byte[] Data { get; private set; }

        /// <summary>
        /// 获取日志的产生时间。
        /// </summary>
        public DateTime Timestamp { get; private set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
