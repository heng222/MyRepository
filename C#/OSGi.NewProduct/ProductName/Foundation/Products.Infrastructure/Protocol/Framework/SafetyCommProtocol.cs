/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2017/7/13 11:47:58 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2017 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// 安全通信协议定义。
    /// </summary>
    public enum SafetyCommProtocol : byte
    {
        /// <summary>
        /// 无
        /// </summary>
        None = 0,

        /// <summary>
        /// RSSP-I
        /// </summary>
        RsspI = 1,

        /// <summary>
        /// RSSP-II
        /// </summary>
        RsspII = 2
    }
}
