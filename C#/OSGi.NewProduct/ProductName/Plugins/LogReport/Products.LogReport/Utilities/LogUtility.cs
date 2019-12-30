/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using Acl.Log;
using Products.Infrastructure.Log;

namespace Products.LogReport
{
    /// <summary>
    /// ��־ʵ�ù�����
    /// </summary>
    static class LogUtility
    {
        public static readonly ILog Log = LogManager.GetLogger(LoggerNames.LogReport);

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
