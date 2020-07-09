/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2013-7-25 14:33:39 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;

using Products.Infrastructure.Protocol.Framework;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 数据到达事件参数类。
    /// </summary>
    public class DataIncomingEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个数据到达消息的事件参数类
        /// </summary>
        /// <param name="data">到达的数据。</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localID">本地节点编号。</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteCode">远程设备编号。</param>
        /// <param name="timeDelay">时延（单位：毫秒）。</param>
        public DataIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode,
            UInt32 timeDelay = 0)
        {
            this.Data = data;
            this.LocalType = localType;
            this.LocalCode = localID;
            this.RemoteType = remoteType;
            this.RemoteCode = remoteCode;
            this.TimeDelay = timeDelay;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取/设置本地节点类型。
        /// </summary>
        public NodeType LocalType { get; set; }
        /// <summary>
        /// 获取/设置本地设备ID。
        /// </summary>
        public UInt32 LocalCode { get; set; }

        /// <summary>
        /// 获取/设置远程设备类型。
        /// </summary>
        public NodeType RemoteType { get; set; }
        /// <summary>
        /// 获取/设置对方设备ID。
        /// </summary>
        public UInt32 RemoteCode { get; set; }

        /// <summary>
        /// 获取/设置协议帧的时延，单位：毫秒。
        /// </summary>
        public UInt32 TimeDelay { get; set; }

        /// <summary>
        /// 设置/获取协议帧关联的数据。
        /// </summary>
        public byte[] Data { get; set; }

        #endregion
    }

    /// <summary>
    /// 协议帧输入事件参数类。
    /// </summary>
    public class FrameIncomingEventArgs : DataIncomingEventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="data">接收的数据字节流。</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localID">本地节点编号。</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : base(data, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
        }

        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="frame">协议帧对象</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localID">本地节点编号。</param>
        /// <param name="bytesStream">协议帧对应的字节流</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(ProtocolFrame frame, byte[] bytesStream,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : this(bytesStream, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// 获取/设置接收到的协议帧。
        /// </summary>
        public ProtocolFrame Frame { get; set; }

        #endregion
    }

    /// <summary>
    /// 协议帧输入事件参数类。
    /// </summary>
    public class FrameIncomingEventArgs<TProtocol> : FrameIncomingEventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="data">接收的数据字节流。</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localID">本地节点编号。</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : base(data, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
        }

        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="frame">协议帧对象</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localID">本地节点编号。</param>
        /// <param name="bytesStream">协议帧对应的字节流</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(TProtocol frame, byte[] bytesStream,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : this(bytesStream, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// 获取/设置接收到的协议帧。
        /// </summary>
        public new TProtocol Frame { get; set; }

        #endregion
    }
}
