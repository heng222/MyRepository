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
using System.Collections.Generic;
using System.Text;
using Products.Infrastructure.Protocol.Framework;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 协议帧输入事件参数类。
    /// 表示收件人收到协议帧。
    /// </summary>
    public class FrameIncomingEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="frame">协议帧对象的引用，不能为空</param>
        /// <param name="bytesStream">协议帧对应的字节流</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(TProtocol frame,
            byte[] bytesStream,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
        {
            this.Frame = frame;
            this.BytesStream = bytesStream;
            this.RemoteDeviceType = remoteType;
            this.RemoteDeviceID = remoteDeviceId;
            this.TimeDelay = timeDelay;
        }
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="bytesStream">协议帧对应的字节流</param>
        /// <param name="remoteType">远程设备类型。</param>
        /// <param name="remoteDeviceId">协议帧发送方的设备ID</param>
        /// <param name="timeDelay">发送时延</param>
        public FrameIncomingEventArgs(byte[] bytesStream,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
        {
            this.BytesStream = bytesStream;
            this.RemoteDeviceType = remoteType;
            this.RemoteDeviceID = remoteDeviceId;
            this.TimeDelay = timeDelay;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取远程设备类型。
        /// </summary>
        public NodeType RemoteDeviceType { get; set; }        
        /// <summary>
        /// 获取远程设备ID，即协议帧发送方的ID。
        /// </summary>
        public UInt32 RemoteDeviceID { get; set; }

        /// <summary>
        /// 表示协议帧的时延，单位：10毫秒。
        /// </summary>
        public UInt32 TimeDelay { get; set; }

        /// <summary>
        /// 表示接收到的协议帧，可以为空，
        /// </summary>
        public TProtocol Frame { get; set; }

        /// <summary>
        /// 设置/获取协议帧关联的字节流，可以为null。
        /// </summary>
        public byte[] BytesStream { get; set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion


    }
}
