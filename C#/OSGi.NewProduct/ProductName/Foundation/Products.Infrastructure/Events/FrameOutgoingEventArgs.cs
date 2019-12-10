/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2014-6-23 14:24:19 
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
    /// 数据输出事件参数类。
    /// </summary>
    public class DataOutgoingEventArgs : EventArgs
    {
        #region "Field"
        /// <summary>
        /// 目的地。
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        public DataOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType)
        {
            if (data == null) throw new ArgumentNullException();

            this.ExtraDelay = 0;

            this.Data = data;
            this.LocalType = localType;
            this.LocalCode = localID;
            this.RemoteType = remoteType;
        }

        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        public DataOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : this(data, localType, localID, remoteType)
        {
            _destDevices.Add(remoteCode);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public NodeType LocalType { get; set; }
        /// <summary>
        /// 本地设备ID。
        /// </summary>
        public uint LocalCode { get; set; }

        /// <summary>
        /// 获取/设置目标设备类型。
        /// </summary>
        public NodeType RemoteType { get; set; }
        /// <summary>
        /// 获取目的设备ID列表
        /// </summary>
        public IEnumerable<uint> RemoteCodes { get { return _destDevices; } }

        /// <summary>
        /// 获取一个值，用于表示目的地是否为空。
        /// 如果指定了目的地，则不再根据路由规则进行转发。
        /// </summary>
        public bool IsDestEmpty { get { return _destDevices.Count == 0; } }

        /// <summary>
        /// 设置/获取协议帧关联的字节流。
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// 获取/设置一个值，用于表示协议帧的附加时延（单位：毫秒）。
        /// </summary>
        public uint ExtraDelay { get; set; }

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// 添加一个目的地
        /// </summary>
        /// <param name="destId"></param>
        public void AddDest(uint destId)
        {
            if (!_destDevices.Contains(destId))
            {
                _destDevices.Add(destId);
            }
        }

        /// <summary>
        /// 设置目的地址
        /// </summary>
        /// <param name="destID"></param>
        public void SetDest(uint destID)
        {
            this.ClearDest();
            _destDevices.Add(destID);
        }

        /// <summary>
        /// 清空目的地
        /// </summary>
        public void ClearDest()
        {
            _destDevices.Clear();
        }
        #endregion

    }

    /// <summary>
    /// 协议帧输出事件参数类。
    /// </summary>
    public class FrameOutgoingEventArgs : DataOutgoingEventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public FrameOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {

        }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public FrameOutgoingEventArgs(ProtocolFrame frame, byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取将要发送的协议帧，可以为空。
        /// </summary>
        public ProtocolFrame Frame { get; set; }
        #endregion
    }

    /// <summary>
    /// 协议帧输出事件参数类。
    /// </summary>
    public class FrameOutgoingEventArgs<TProtocol> : FrameOutgoingEventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public FrameOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {

        }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public FrameOutgoingEventArgs(TProtocol frame, byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取将要发送的协议帧，可以为空。
        /// </summary>
        public new TProtocol Frame { get; set; }
        #endregion
    }
}
