
using System;

using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 表示层控件类型定义
    /// </summary>
    [Obsolete]
    public enum PresentationControlType : uint
    {
        /// <summary>
        /// 无类型或类型无效
        /// </summary>
        None = 0,

        #region  "Shell"
        /// <summary>
        /// 程序运行日志
        /// </summary>
        [MemberDes("程序运行日志")]
        ApplicationLog = 1,
        /// <summary>
        /// 数码管时钟控件
        /// </summary>
        [MemberDes("数码管时钟控件")]
        NixieTubeClock = 2,
        #endregion

        /// <summary>
        /// 日志报告
        /// </summary>
        [MemberDes("日志报告")]
        LogReport = 5,

        #region "SEM / 系统事件管理"
        /// <summary>
        /// 系统事件
        /// </summary>
        [MemberDes("系统事件")]
        SystemEvent = 11,
        /// <summary>
        /// 操作记录
        /// </summary>
        [MemberDes("操作记录")]
        OperationLog = 12,
        #endregion

        #region  "Plugin1"
        /// <summary>
        /// 插件1主控件
        /// </summary>
        [MemberDes("插件1主控件")]
        Plugin1Main = 27,
        #endregion
    }
}
