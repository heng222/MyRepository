/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�02/18/2013 08:41:53 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using Acl.Log;
using Products.Infrastructure.Log;

namespace Products.Plugin1.Utilities
{
    /// <summary>
    /// ��־ʵ�ù�����
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
