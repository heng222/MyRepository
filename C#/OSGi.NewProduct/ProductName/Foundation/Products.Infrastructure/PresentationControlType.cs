using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure
{
    /// <summary>
    /// 表示层控件类型定义
    /// </summary>
    public enum PresentationControlType
    {
        /// <summary>
        /// 无类型或类型无效
        /// </summary>
        None = 0,

        #region  "Shell"
        /// <summary>
        /// 程序运行日志
        /// </summary>
        [MemberDesAttribute("程序运行日志")]
        ApplicationLog = 1,
        /// <summary>
        /// 数码管时钟控件
        /// </summary>
        [MemberDesAttribute("数码管时钟控件")]
        NixieTubeClock = 2,
        #endregion

        #region "SEM"
        /// <summary>
        /// 系统事件
        /// </summary>
        [MemberDesAttribute("系统事件")]
        SystemEvent = 11,
        #endregion

        #region  "Plugin1"
        /// <summary>
        /// Plugin1Control1
        /// </summary>
        [MemberDesAttribute("Plugin1Control1")]
        Plugin1Control1 = 27,
        /// <summary>
        /// Plugin1Control2
        /// </summary>
        [MemberDesAttribute("Plugin1Control2")]
        Plugin1Control2 = 28,
        #endregion
    }
}
