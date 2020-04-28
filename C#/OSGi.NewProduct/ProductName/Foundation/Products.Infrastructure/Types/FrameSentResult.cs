/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2018-5-15 10:50:33 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 协议帧发送结果定义
    /// </summary>
    public enum FrameSentResult : byte
    {
        /// <summary>
        /// 未知。
        /// </summary>
        Unknown,
        /// <summary>
        /// 发送成功。
        /// </summary>
        Successful,
        /// <summary>
        /// 发送失败。
        /// </summary>
        Failed,
    }
}
