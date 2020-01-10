/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2018-5-21 15:05:25 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 插件加载配置。
    /// </summary>
    [Acl.Data.Annotions.Table(Name = "system_PluginLoadingConfigs")]
    public class PluginLoadingConfig : Entity
    {
        #region DB字段
        /// <summary>
        /// 节点编号。
        /// </summary>
        public UInt32 NodeCode { get; set; }

        /// <summary>
        /// 节点类型。
        /// </summary>
        public NodeType NodeType { get; set; }

        /// <summary>
        /// 节点需要加载的插件类型。
        /// </summary>
        public string Plugins { get; set; }

        /// <summary>
        /// 节点需要显示的控件，以CVS格式表示的多个PresentationControlType。
        /// </summary>
        public string Controls { get; set; }

        /// <summary>
        /// 描述性信息。
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// NodeCode+NodeType+Plugins+Controls的MD5签名。
        /// </summary>
        public byte[] MessageDigest { get; set; }
        #endregion

        /// <summary>
        /// 是否包含指定的插件类型。
        /// </summary>
        /// <param name="type">指定的插件类型，可以使用位域表示多个插件类型。</param>
        /// <returns>true表示全部包含，false表示非全部包含。</returns>
        public bool Contains(PluginType type)
        {
            return this.GetPlugins().HasFlag(type);
        }

        /// <summary>
        /// 获取需要加载的插件。
        /// </summary>
        /// <returns></returns>
        public PluginType GetPlugins()
        {
            return (PluginType)UInt64.Parse(this.Plugins);
        }

        /// <summary>
        /// 设置需要显示的控件类型。
        /// </summary>
        /// <param name="controls">将要设置的值。</param>
        public void SetControlTypes(IEnumerable<PresentationControlType> controls)
        {
            if (controls == null || controls.Count() == 0)
            {
                this.Controls = string.Empty;
            }
            else
            {
                this.Controls = string.Join(",", controls.Select(p => ((int)p).ToString()));
            }
        }

        /// <summary>
        /// 获取需要显示的控件类型列表。
        /// </summary>
        /// <returns>节点需要加载的控件类型。</returns>
        public IEnumerable<PresentationControlType> GetControlTypes()
        {
            if (!string.IsNullOrWhiteSpace(this.Controls))
            {
                return this.Controls.Split(',').Select(p => (PresentationControlType)int.Parse(p));
            }
            else
            {
                return new List<PresentationControlType>();
            }
        }
    }
}