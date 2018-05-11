/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;

namespace Products.Infrastructure.Messages
{
    /// <summary>
    /// 表示单个消息主题的总线接口。
    /// </summary>
    /// <typeparam name="TEventArgs"></typeparam>
    public interface ISingleTopicMessageBus<TEventArgs> where TEventArgs : EventArgs
    {
        /// <summary>
        /// 获取消息总线关联的主题。
        /// </summary>
        string Topic { get; }

        /// <summary>
        /// 发布消息。
        /// </summary>
        void Publish(TEventArgs args, object sender = null);

        /// <summary>
        /// 订阅消息。
        /// </summary>
        /// <returns>一个可取消订阅的接口。</returns>
        IDisposable Subscribe(Action<object, TEventArgs> handler);
    }
}
