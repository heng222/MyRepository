/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2014-6-23 14:27:02 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Products.Infrastructure.Events;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// 一个观察器接口，用于处理将要发送的协议帧。
    /// </summary>
    public interface IOutgoingFrameObserver<TProtocol>
        where TProtocol : ProtocolFrame
    {
        /// <summary>
        /// 处理将要发送的协议帧。
        /// </summary>
        /// <param name="e">OutgoingFrameArgs事件参数对象</param>
        void HandleFrame(FrameOutgoingEventArgs<TProtocol> e);
    }
}
