/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2018-5-21 15:05:25 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;

using Acl.Data.Annotions;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 插件加载配置。
    /// </summary>
    [Table(Name = "system_PluginLoadingConfigs")]
    public class PluginLoadingConfig : Entity
    {
        #region "Field"
        private IEnumerable<string> _pluginsID;
        private IEnumerable<string> _controlsID;
        #endregion

        #region DB字段
        /// <summary>
        /// 节点编号。
        /// </summary>
        [Column]
        public UInt32 NodeCode { get; set; }

        /// <summary>
        /// 节点类型。
        /// </summary>
        [Column]
        public NodeType NodeType { get; set; }

        /// <summary>
        /// 节点需要加载的插件。
        /// <para>CSV格式的插件ID集合。</para>
        /// </summary>
        [Column]
        public string Plugins { get; set; }

        /// <summary>
        /// 节点需要显示的控件，以CVS格式表示的多个PresentationControlType。
        /// </summary>
        [Column]
        public string Controls { get; set; }

        /// <summary>
        /// 描述性信息。
        /// </summary>
        [Column(Length = 100)]
        public string Description { get; set; }

        /// <summary>
        /// NodeCode+NodeType+Plugins+Controls的MD5签名。
        /// </summary>
        [Column(Length = 16)]
        public byte[] MessageDigest { get; set; }
        #endregion

        /// <summary>
        /// 是否包含指定的插件。
        /// </summary>
        /// <param name="pluginID">插件编号。</param>
        /// <returns>true表示全部包含，false表示非全部包含。</returns>
        public bool Contains(string pluginID)
        {
            return this.GetPlugins().Contains(pluginID);
        }

        /// <summary>
        /// 获取需要加载的插件ID集合。
        /// </summary>
        /// <returns>CSV格式的插件ID集合。</returns>
        public IEnumerable<string> GetPlugins()
        {
            if (_pluginsID == null)
            {
                _pluginsID = string.IsNullOrWhiteSpace(this.Plugins) ? Enumerable.Empty<string>() : this.Plugins.Split(new char[] { ',', '，' }).ToList();
            }

            return _pluginsID;
        }

        /// <summary>
        /// 获取需要显示的控件。
        /// </summary>
        /// <returns>节点需要加载的控件。</returns>
        public IEnumerable<string> GetControls()
        {
            if (_controlsID == null)
            {
                _controlsID = string.IsNullOrWhiteSpace(this.Controls) ? Enumerable.Empty<string>() : this.Controls.Split(new char[] { ',', '，' }).ToList();
            }

            return _controlsID;
        }
    }
}