/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：02/18/2013 08:41:53 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using Acl.Log;
using Products.Infrastructure.Log;

namespace Products.Plugin1.Utilities
{
    /// <summary>
    /// 日志实用工具类
    /// </summary>
    internal static class LogUtility
    {
        private static readonly ILog _log = LogManager.GetLogger(LoggerNames.Plugin1);


        public static void Debug(string format, params object[] args)
        {
            _log.DebugFormat(format, args);
        }

        public static void Info(string format, params object[] args)
        {
            _log.InfoFormat(format, args);
        }

        public static void Warning(object info)
        {
            _log.Warn(info);
        }

        public static void Warning(object info, Exception ex)
        {
            _log.Warn(info, ex);
        }

        public static void Error(object info)
        {
            _log.Error(info);
        }

        public static void Error(object info, Exception ex)
        {
            _log.Error(info, ex);
        }
    }
}
