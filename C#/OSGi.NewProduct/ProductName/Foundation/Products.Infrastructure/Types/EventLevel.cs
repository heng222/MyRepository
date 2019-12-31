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
    /// 系统事件级别定义。
    /// </summary>
    public enum EventLevel : byte
    {
        /// <summary>
        /// 无效
        /// </summary>
        [MemberDes("无效")]
        None = 0,

        /// <summary>
        /// 一级
        /// </summary>
        [MemberDes("一级")]
        First = 1,
  
        /// <summary>
        /// 二级
        /// </summary>
        [MemberDes("二级")]
        Second = 2,

        /// <summary>
        /// 三级
        /// </summary>
        [MemberDes("三级")]
        Third = 3,
    }
}
