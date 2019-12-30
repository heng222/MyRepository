/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：2013-7-17 14:34:15 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2013 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/


using Acl.Utility;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// 日志分类名称定义
    /// </summary>
    public static class LoggerNames
    {
        /// <summary>
        /// 平台
        /// </summary>
        [MemberDes("平台")]
        public const string Platform = "平台";
        /// <summary>
        /// 持久化模块
        /// </summary>
        [MemberDes("持久化")]
        public const string Persistence = "持久化";
        /// <summary>
        /// Shell
        /// </summary>
        [MemberDes("日志报告")]
        public const string LogReport = "LogReport";

        /// <summary>
        /// Shell
        /// </summary>
        [MemberDes("Shell")]
        public const string Shell = "Shell";

        /// <summary>
        /// 用户访问控制
        /// </summary>
        [MemberDes("UAC")]
        public const string UAC = "UAC";
        /// <summary>
        /// 系统事件管理
        /// </summary>
        [MemberDes("SEM")]
        public const string SEM = "SEM";
        /// <summary>
        /// Plugin1
        /// </summary>
        [MemberDes("Plugin1")]
        public const string Plugin1 = "Plugin1";
    }
}
