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

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 一个接口，用于描述节点上下文信息。
    /// </summary>
    public interface INodeContext
    {
        #region "Properties"

        /// <summary>
        /// 获取当前节点编号
        /// </summary>
        UInt32 Code { get; }
        /// <summary>
        /// 获取当前节点名称
        /// </summary>
        string Name { get; }
        /// <summary>
        /// 获取当前节点类型
        /// </summary>
        NodeType Type { get; }

        /// <summary>
        /// 获取当前节点需要加载的插件编号。
        /// </summary>
        IEnumerable<string> Plugins { get; }

        /// <summary>
        /// 获取当前节点需要加载的控件编号。
        /// </summary>
        IEnumerable<string> Controls { get; }

        #endregion


        #region "Operations"
        /// <summary>
        /// 当前节点是否加载指定的插件。
        /// </summary>
        /// <param name="pluginID">指定的插件编号。</param>
        /// <returns>true表示需要加载指定的插件，false表示不需要加载。</returns>
        bool ContainsPlugin(string pluginID);
        #endregion

    }
}
