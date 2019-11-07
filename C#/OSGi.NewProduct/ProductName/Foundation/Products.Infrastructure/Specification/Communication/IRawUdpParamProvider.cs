/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 一个接口，用于表示可以提供基于裸UDP通信参数。
    /// </summary>
    public interface IRawUdpParamProvider
    {
        /// <summary>
        /// 本地监听点。
        /// </summary>
        IPEndPoint LocalEndPoint { get; }

        /// <summary>
        /// Key = Remote ID
        /// </summary>
        Dictionary<uint, IPEndPoint> RemoteEndPoints { get; }

        /// <summary>
        /// 根据 IPEndPoint 获取 对应的远程节点编号。
        /// </summary>
        /// <param name="endPoint">IP终结点。</param>
        /// <returns>远程节点编号。</returns>
        uint GetRemoteCode(IPEndPoint endPoint);
    }
}
