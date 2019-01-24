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
using System.Net;
using Acl.Log;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Log;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// 节点上下文管理器。
    /// 此静态工具类包括本地节点的属性，同级节点的属性以及所有父级及子级的属性。
    /// 并且提供一些常用的静态方法。
    /// </summary>
    public static class NodeContextManager
    {
        #region "Filed"

        #endregion

        #region "Construct"
        /// <summary>
        /// 构造函数。
        /// </summary>
        static NodeContextManager()
        {
            Current = new DefaultNodeContextImpl();
        }
        #endregion

        #region "Property"
        /// <summary>
        /// 获取当前节点上下文信息
        /// </summary>
        public static INodeContext Current { get; set; }

        /// <summary>
        /// 获取本地节点ID
        /// </summary>
        public static uint LocalNodeCode { get { return Current.Code; } }

        /// <summary>
        /// 获取本地节点名称
        /// </summary>
        public static string LocalNodeName { get { return Current.Name; } }

        /// <summary>
        /// 获取本地节点类型
        /// </summary>
        public static NodeType LocalNodeType { get { return Current.Type; } }

        #endregion

        #region "Public methods"
        /// <summary>
        /// 初始化
        /// </summary>
        public static void Initialize()
        {

        }
        #endregion
    }
}
