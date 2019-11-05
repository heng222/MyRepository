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
using System.Text;
using Acl.Utility;
using Products.Domain.Utility;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// 节点上下文信息。
    /// </summary>
    public class NodeContextImpl : INodeContext
    {
        #region "Filed"
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
        public IEnumerable<PresentationControlType> ControlTypes { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public NodeContextImpl()
        {
            //this.Name = "节点名称";
            this.Name = string.Empty;
            this.Type = NodeType.Default;
            this.Plugins = PluginType.All;
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// 初始化本地节点相关信息。
        /// 默认方式下将根据本地IP从数据库中查找对应的节点信息。
        /// </summary>
        public void Initialize()
        {

        }

        /// <summary>
        /// 初始化节点上下文。
        /// </summary>
        /// <param name="nodeCode"></param>
        public void Initialize(uint nodeCode)
        {
            BuildPluginsConfig();
            LogLocalDeviceInfo();
        }

        private void BuildPluginsConfig()
        {
            this.Plugins = PluginType.None;

            // 
            var allRecords = GlobalServices.Repository.Where<PluginLoadingConfig>().ToList();
            var localPluginCfg = allRecords.Where(p => p.NodeCode == this.Code).FirstOrDefault();

            if (localPluginCfg == null)
            {
                localPluginCfg = allRecords.Where(p => p.NodeType == this.Type).
                    FirstOrDefault();
            }

            if (localPluginCfg == null)
            {
                throw new Exception("没有找到合适的插件配置数据。");
            }

            if (localPluginCfg.MessageDigest == null)
            {
                throw new Exception("插件配置数据错误，签名为空。");
            }

            // 检查数字签名。
            //using (var md5 = MD5.Create())
            //{
            //    var expectedMd5 = AuthenticationHelper.CalculatePluginConfigMD5(localPluginCfg);

            //    var isEqual = expectedMd5.SequenceEqual(localPluginCfg.MessageDigest);
            //    if (!isEqual)
            //    {
            //        throw new Exception("插件配置数据错误，签名不匹配。");
            //    }
            //}

            // 
            this.Plugins = localPluginCfg.GetPlugins();
            this.ControlTypes = localPluginCfg.GetControlTypes();
        }

        /// <summary>
        /// 记录相关日志。
        /// </summary>
        private void LogLocalDeviceInfo()
        {
            try
            {
                // 记录本节点的信息
                var strBuilder = new StringBuilder(128);
                strBuilder.AppendFormat("\r\n本节点信息：ID= {0}, Name= {1}",
                    this.Code, this.Name);

                // 本节点需要加载的插件。
                strBuilder.AppendFormat("\r\n本节点需要加载的插件= {0}。",
                    EnumUtility.GetDescription<PluginType>(this.Plugins));

                // 本节点需要显示的控件。
                strBuilder.AppendFormat("\r\n本节点需要显示的控件= {0}。",
                    string.Join(",", this.ControlTypes.Select(p => string.Format("{0}", p))));
                
                LogUtility.Info(strBuilder.ToString());
            }
            catch (System.Exception /*ex*/)
            {
            }
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
            return this.Plugins.HasFlag(pluginType);
        }

        #endregion
    }
}
