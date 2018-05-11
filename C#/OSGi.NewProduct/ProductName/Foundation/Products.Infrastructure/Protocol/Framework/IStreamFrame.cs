using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{

    /// <summary>
    /// 一个接口，用于表示可流化的消息。
    /// </summary>
    public interface IStreamFrame
    {
        /// <summary>
        /// 获取消息对应的数据流。
        /// </summary>
        /// <returns>协议对应的数据流</returns>
        Array GetStream();

        /// <summary>
        /// 解析指定的数据流。
        /// </summary>
        /// <param name="stream">数据流</param>
        /// <param name="startIndex">协议数据在数据流中的起始地址</param>
        void ParseStream(Array stream, int startIndex);
    }

    /// <summary>
    /// 一个接口，用于表示可流化的消息。
    /// </summary>
    public interface IStreamFrame<T> : IStreamFrame
    {
        /// <summary>
        /// 获取消息对应的数据流。
        /// </summary>
        /// <returns>协议对应的数据流</returns>
        new T[] GetStream();

        /// <summary>
        /// 解析指定的数据流。
        /// </summary>
        /// <param name="stream">数据流</param>
        /// <param name="startIndex">协议数据在数据流中的起始地址</param>
        void ParseStream(T[] stream, int startIndex);
    }
}
