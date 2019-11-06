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
    /// 系统节点类型定义
    /// </summary>
    public enum NodeType : ushort
    {
        /// <summary>
        /// 未知
        /// </summary>
        None = 0,

        /// <summary>
        /// 默认节点 。
        /// </summary>
        Default = Node1,

        #region "本系统节点"
        /// <summary>
        /// 节点类型1
        /// </summary>
        [MemberDes("节点类型1")]
        Node1 = 16,
        /// <summary>
        /// 节点类型2
        /// </summary>
        [MemberDes("节点类型2")]
        Node2 = 18,
        #endregion
    }

}
