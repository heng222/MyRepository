/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2018-8-1 13:33:34 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Management;
using System.Net;
using System.Security.Cryptography;
using System.Text;
using Acl.Log;
using Acl.Utility;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// 节点上下文信息
    /// </summary>
    class DefaultNodeContextImpl : INodeContext
    {
        #region "Filed"
        private List<PresentationControlType> _controlTypes = new List<PresentationControlType>();
        #endregion

        #region "Property"
        /// <summary>
        /// 获取本地节点ID。
        /// </summary>
        public uint Code { get; private set; }
        /// <summary>
        /// 获取本地节点名称。
        /// </summary>
        public string Name { get; private set; }
        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public NodeType Type { get; private set; }

        
        /// <summary>
        /// 获取当前节点需要加载的插件。
        /// </summary>
        public PluginType Plugins { get; private set; }

        /// <summary>
        /// 获取当前节点需要加载的控件类型。
        /// </summary>
        public IEnumerable<PresentationControlType> ControlTypes { get { return _controlTypes; } }
        #endregion

        #region "Public methods"

        /// <summary>
        /// 初始化本地节点相关信息。
        /// 默认方式下将根据本地IP从数据库中查找对应的节点信息。
        /// </summary>
        public void Initialize()
        {
            this.Name = string.Empty;
            this.Type = NodeType.Default;
            this.Plugins = PluginType.All;
        }

        #endregion


        #region "INodeContext 成员"
        /// <summary>
        /// 当前节点是否加载指定的插件。
        /// </summary>
        /// <param name="pluginType">指定的插件类型。</param>
        /// <returns>true表示需要加载指定的插件，false表示不需要加载。</returns>
        public bool ContainsPlugin(PluginType pluginType)
        {
            return (pluginType & this.Plugins) == pluginType;
        }

        #endregion
    }
}
