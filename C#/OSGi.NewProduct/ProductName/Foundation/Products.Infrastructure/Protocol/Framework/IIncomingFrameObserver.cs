/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：01/15/2013 15:02:55 
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
    /// 一个观察器接口，用于处理接收到的协议帧。
    /// </summary>
    public interface IIncomingFrameObserver<TProtocol>
        where TProtocol : ProtocolFrame
    {
        /// <summary>
        /// 协议帧处理入口函数
        /// </summary>
        /// <param name="e">事件参数对象</param>
        void HandleFrame(FrameIncomingEventArgs<TProtocol> e);
    }
}
