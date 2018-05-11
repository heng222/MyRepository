/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：03/02/2012 15:13:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009-2015 保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// 表示通讯协议的种类
    /// </summary>
    [Flags]
    public enum ProtocolKind : ulong
    {
        /// <summary>
        /// 系统内部通讯协议
        /// </summary>
        Internal = 0x00000001,

        /// <summary>
        /// 本系统 与 外部系统1 的通讯协议
        /// </summary>
        CI = 0x00000002,
        /// <summary>
        /// 本系统 与 外部系统2 的通讯协议
        /// </summary>
        ATP = 0x00000004,
        /// <summary>
        /// 本系统 与 外部系统3 的通讯协议
        /// </summary>
        CLK = 0x00000008,
        /// <summary>
        /// 本系统 与 外部系统4 的通讯协议
        /// </summary>
        FAS = 0x00000010,
        /// <summary>
        /// 本系统 与 外部系统5 的通讯协议
        /// </summary>
        ISCS = 0x00000020,
    }
}
