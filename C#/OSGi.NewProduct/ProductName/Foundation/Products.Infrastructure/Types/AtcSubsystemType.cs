/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：05/23/2013 13:03:15 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// ATC中的子系统类型。
    /// </summary>
    public enum AtcSubsystemType : byte
    {
        /// <summary>
        /// 无效
        /// </summary>
        [MemberDesAttribute("无效")]
        None = 0,

        /// <summary>
        /// ATS
        /// </summary>
        [MemberDesAttribute("ATS")]
        ATS = 0x03,

        /// <summary>
        /// 车载ATP
        /// </summary>
        [MemberDesAttribute("车载ATP")]
        VOBC = 0x14,

        /// <summary>
        /// ATO
        /// </summary>
        [MemberDesAttribute("ATO")]
        ATO = 0x08,

        /// <summary>
        /// ATP区域控制器
        /// </summary>
        [MemberDesAttribute("ZC")]
        ZC = 0x1E,

        /// <summary>
        /// 数据库存储单元
        /// </summary>
        [MemberDesAttribute("DSU")]
        DMS = 0x2B,

        /// <summary>
        /// 微机联锁
        /// </summary>
        [MemberDesAttribute("CI")]
        CI = 0x3C,
    };
}
