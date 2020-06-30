/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Net;

using Acl.RsspI4net.Config;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 一个接口，用于表示可以提供基于UDP的RSSP-1通信参数。
    /// </summary>
    public interface IRssp1ParamProvider
    {
        /// <summary>
        /// 是否A机？
        /// </summary>
        bool IsMachineA { get; }

        /// <summary>
        /// 本节点的工作周期。
        /// </summary>
        int WorkPeriod { get; }

        /// <summary>
        /// 本地工作参数。
        /// </summary>
        WorkParameters LocalWorkParameter { get; }

        /// <summary>
        /// 本地安全参数。
        /// </summary>
        SafetyParameters LocalSafetyParam { get; }

        /// <summary>
        /// 会话参数。
        /// </summary>
        IEnumerable<Tuple<IEnumerable<UdpParameters>, SessionConfig>> SessionParam { get; }

        /// <summary>
        /// 根据 指定的地址 查找 对应的ID。
        /// </summary>
        /// <param name="address">例如：0x1E01</param>
        /// <returns>例如：0x9201, 0x9202</returns>
        List<uint> FindRemoteCode(ushort address);

        /// <summary>
        /// 根据节点的自定义编号查找对应的RSSP-I地址。
        /// </summary>
        /// <param name="customCode">自定义编号，例如：0x9201, 0x9202。</param>
        /// <returns>自定义编号对应的地址。例如：0x1E01。</returns>
        ushort FindAddress(uint customCode);
    }
}
