using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Presentation
{
    /// <summary>
    /// 配置页面名称定义
    /// </summary>
    public abstract class ConfigNodeNames
    {
        #region "环境配置"
        /// <summary>
        /// 环境
        /// </summary>
        public abstract class Environment
        {
            /// <summary>
            /// 常规
            /// </summary>
            public const string General = "环境/常规";
            /// <summary>
            /// 日志
            /// </summary>
            public const string Log = "环境/日志";
            /// <summary>
            /// 系统配置
            /// </summary>
            public const string SystemConfig = "环境/系统配置";
        }
        #endregion


        #region "插件管理"
        /// <summary>
        /// 插件管理
        /// </summary>
        public abstract class Plugins
        {
            /// <summary>
            /// Plugin1
            /// </summary>
            public abstract class Plugin1
            {
                /// <summary>
                /// General
                /// </summary>
                public const string General = "插件.Plugin1.常规";
            }
        }
        #endregion

    }
}
