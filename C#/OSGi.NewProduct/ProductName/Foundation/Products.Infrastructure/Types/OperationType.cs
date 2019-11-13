/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
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
    /// 操作类型
    /// </summary>
    public enum OperationType : byte
    {
        /// <summary>
        /// 无效操作。
        /// </summary>
        [MemberDes("无效操作")]
        None = 0,

        #region "操作分类1"
        /// <summary>
        /// X操作
        /// </summary>
        [MemberDes("X操作")]
        OperationX = 0x11,
        #endregion
    }
}
