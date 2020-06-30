/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-8-16 13:50:34 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Acl.Log;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// ��־������Ϣ
    /// </summary>
    public static class LogSettings
    {
        #region "Field"
        private static LogLevel _level = LogLevel.Information;
        private static ushort _expiredDays = 30;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ��̬���캯��
        /// </summary>
        static LogSettings()
        {
            CommLogBasePath = string.Format(@"{0}CommLog\", AppDomain.CurrentDomain.BaseDirectory);
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// ��ȡ/������־�ı��漶��
        /// </summary>
        static public LogLevel Level
        {
            get { return _level; }
            set { _level = value; }
        }

        /// <summary>
        /// ��ȡ/������־�ı�������
        /// </summary>
        static public ushort ExpiredDays
        {
            get { return _expiredDays; }
            set { _expiredDays = value; }
        }

        /// <summary>
        /// ��ȡͨѶ��־�Ļ���·��
        /// </summary>
        static public string CommLogBasePath { get; private set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
