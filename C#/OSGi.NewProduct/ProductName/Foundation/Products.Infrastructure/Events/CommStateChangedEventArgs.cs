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
using System.Collections.Generic;
using System.Text;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// （节点间）通信状态变化事件参数类
    /// </summary>
    public sealed class CommStateChangedEventArgs : EventArgs
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个连接变化事件参数类
        /// </summary>
        /// <param name="connected"></param>
        /// <param name="localId"></param>
        /// <param name="remoteId"></param>
        /// <param name="remoteType"></param>
        public CommStateChangedEventArgs(bool connected, uint localId, 
            uint remoteId, NodeType remoteType)
        {
            this.Connected = connected;
            this.LocalDeviceID = localId;
            this.RemoteDeviceID = remoteId;
            this.RemoteDeviceType = remoteType;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 返回一个值，用于表示是否为设备间连接事件。
        /// </summary>
        public bool Connected { get; set; }

        /// <summary>
        /// 此事件对应的本地设备ID(此ID为设备在 本系统 中的编号，并非与接口通信时使用的编号)
        /// </summary>
        public UInt32 LocalDeviceID { get; set; }

        /// <summary>
        /// 此事件对应的对方设备类型
        /// </summary>
        public NodeType RemoteDeviceType { get; set; }

        /// <summary>
        /// 此事件对应的对方设备ID(此ID为设备在 本系统 中的编号，并非与接口通信时使用的编号)
        /// </summary>
        public UInt32 RemoteDeviceID { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
