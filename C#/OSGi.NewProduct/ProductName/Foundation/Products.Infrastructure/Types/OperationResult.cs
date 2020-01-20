/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 操作结果
    /// </summary>
    public enum OperationResult : byte
    {
        /// <summary>
        /// 未知
        /// </summary>
        [MemberDes("未知")]
        Unknown = 0,

        /// <summary>
        /// 成功
        /// </summary>
        [MemberDes("成功")]
        Success = 1,

        /// <summary>
        /// 失败
        /// </summary>
        [MemberDes("失败")]
        Failure = 2,

        /// <summary>
        /// 回应超时
        /// </summary>
        [MemberDes("超时")]
        Timeout = 3,
    }
}
