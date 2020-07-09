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

namespace Products.Persistence
{
    /// <summary>
    /// 日志实用工具类
    /// </summary>
    static class LogUtility
    {
        public static readonly ILog Log = LogManager.GetLogger(LoggerNames.Persistence);

        public static void Trace(string format, object[] args, LogLevel level, Exception ex)
        {
            string info = format;
            if (args != null && args.Length > 0)
                info = string.Format(format, args);

            switch (level)
            {
                case LogLevel.Debug:
                    Log.Debug(info, ex);
                    break;
                case LogLevel.Error:
                    Log.Error(info, ex);
                    break;
                case LogLevel.Fatal:
                    Log.Fatal(info, ex);
                    break;
                case LogLevel.Information:
                    Log.Info(info, ex);
                    break;
                case LogLevel.Warning:
                    Log.Warn(info, ex);
                    break;
            }
        }


        public static void Debug(string format, params object[] args)
        {
            Log.DebugFormat(format, args);
        }

        public static void Info(string format, params object[] args)
        {
            Log.InfoFormat(format, args);
        }

        public static void Warning(object info)
        {
            Log.Warn(info);
        }

        public static void Warning(object info, Exception ex)
        {
            Log.Warn(info, ex);
        }

        public static void Error(object info)
        {
            Log.Error(info);
        }

        public static void Error(object info, Exception ex)
        {
            Log.Error(info, ex);
        }
    }
}
