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

namespace Products.Shell
{
    /// <summary>
    /// ��־ʵ�ù�����
    /// </summary>
    internal static class LogUtility
    {
        public static readonly ILog Log = LogManager.GetLogger(LoggerNames.Shell);


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
