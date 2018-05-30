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

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 协议帧输出事件参数类。
    /// 用于发件人期望送件人将协议帧发送到目的地。
    /// </summary>
    public class FrameOutgoingEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Filed"
        /// <summary>
        /// 如果指定了目的地，则不再根据路由规则进行转发。
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="frame">协议帧对象的引用，不能为空</param>
        public FrameOutgoingEventArgs(TProtocol frame)
        {
            if (frame == null) throw new ArgumentNullException();

            this.Frame = frame;

            this.BytesStream = new byte[0];
            this.ExtraDelay = 0;
            this.ForcedSend = false;
        }
        /// <summary>
        /// 构造一个协议帧接收消息的事件参数类
        /// </summary>
        /// <param name="bytesStream">协议帧对应的字节流</param>
        public FrameOutgoingEventArgs(byte[] bytesStream)
        {
            if (bytesStream == null) throw new ArgumentNullException();

            this.BytesStream = bytesStream;

            this.Frame = null;
            this.ExtraDelay = 0;
            this.ForcedSend = false;
        }
        #endregion

        #region "Properties"
                
        /// <summary>
        /// 获取目的设备ID列表
        /// </summary>
        public uint[] DestDeviceIDs
        {
            get { return _destDevices.ToArray(); }
        }

        /// <summary>
        /// 获取一个值，用于表示目的地是否为空。
        /// 如果指定了目的地，则不再根据路由规则进行转发。
        /// </summary>
        public bool IsDestEmpty
        {
            get { return _destDevices.Count == 0; }
        }
        
        /// <summary>
        /// 表示将要发送的协议帧，可以为空。
        /// </summary>
        public TProtocol Frame { get; set; }

        /// <summary>
        /// 设置/获取协议帧关联的字节流。为空引用时表示不对外公开协议帧内容。
        /// </summary>
        public byte[] BytesStream { get; set; }

        /// <summary>
        /// 获取/设置一个值，用于表示协议帧的附加时延。
        /// 一般用于协议帧转发时。
        /// </summary>
        public uint ExtraDelay { get; set; }

        /// <summary>
        /// 是否强制发送。
        /// 默认值为false，表示仅当本节点为主机时才发送协议帧。为true时，表示忽略主备状态，强制发送。
        /// </summary>
        public bool ForcedSend { get; set; }
        #endregion

        #region "Override methods"
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
}
