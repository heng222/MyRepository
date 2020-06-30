/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;

using Acl.Log;

using Products.Infrastructure.Log;

namespace Products.UAC
{
    /// <summary>
    /// ��־ʵ�ù�����
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
