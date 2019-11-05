/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-26 13:51:07 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using Acl.Log;
using Products.Infrastructure.Log;
using Products.Resource;

namespace Products.Domain.Utility
{
    /// <summary>
    /// ��־ʵ�ù�����
    /// </summary>
    static class LogUtility
    {
        private static readonly ILog _log = LogManager.GetLogger(LoggerNames.Platform);

        public static ILog Log { get { return _log; } }

        /// <summary>
        /// 
        /// </summary>
        public static void Debug(string info, Exception ex = null)
        {
            _log.Debug(info, ex);
        }

        /// <summary>
        /// 
        /// </summary>
        public static void DebugFormat(string info, params object[] args)
        {
            _log.DebugFormat(info, args);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="info"></param>
        /// <param name="ex"></param>
        public static void Info(string info, Exception ex = null)
        {
            _log.Info(info, ex);
        }

        /// <summary>
        /// 
        /// </summary>
        public static void InfoFormat(string info, params object[] args)
        {
            _log.InfoFormat(info, args);
        }

        /// <summary>
        /// 
        /// </summary>
        public static void WarningFormat(string info, params object[] args)
        {
            _log.WarnFormat(info, args);
        }
        /// <summary>
        /// 
        /// </summary>
        public static void Warning(string info, Exception ex = null)
        {
            _log.Warn(info, ex);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="info"></param>
        public static void Error(string info)
        {
            _log.Error(info);
        }

        public static void Error(string info, Exception ex)
        {
            _log.Error(info, ex);
        }
    }
}
