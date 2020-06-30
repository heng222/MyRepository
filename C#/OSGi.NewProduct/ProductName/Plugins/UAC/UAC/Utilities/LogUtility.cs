/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;

using Acl.Log;

using Products.Infrastructure.Log;

namespace Products.UAC
{
    /// <summary>
    /// 日志实用工具类
    /// </summary>
    static class LogUtility
    {
        private static readonly ILog _log = LogManager.GetLogger(LoggerNames.UAC);

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
