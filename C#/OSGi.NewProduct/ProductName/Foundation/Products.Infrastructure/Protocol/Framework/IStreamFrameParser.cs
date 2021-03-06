/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2014-6-10 14:57:11 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// 一个接口，用于描述流解析器。
    /// </summary>
    public interface IStreamFrameParser
    {
        /// <summary>
        /// 将指定的流解析为协议帧对象
        /// </summary>
        /// <param name="stream">将要被解析的流</param>
        /// <param name="startIndex">解析时起始地址</param>
        /// <returns>一个<seealso cref="ProtocolFrame"/>对象</returns>
        ProtocolFrame Parse(Array stream, int startIndex);
    }

    /// <summary>
    /// 一个接口，用于描述流解析器。
    /// </summary>
    public interface IStreamFrameParser<T> : IStreamFrameParser
    {
        /// <summary>
        /// 将指定的流解析为协议帧对象
        /// </summary>
        /// <param name="stream">将要被解析的流</param>
        /// <param name="startIndex">解析时起始地址</param>
        /// <returns>一个<seealso cref="ProtocolFrame"/>对象</returns>
        ProtocolFrame Parse(T[] stream, int startIndex);
    }
}
