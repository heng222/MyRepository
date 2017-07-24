/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS-SIL2
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
        [MemberDes("平台")]
        public const string Platform = "平台";

        [MemberDes("Shell")]
        public const string Shell = "Shell";

        [MemberDes("Plugin1")]
        public const string Plugin1 = "Plugin1";
    }
}
