/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-8-16 15:11:00 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// ��־���������
    /// </summary>
    public static class LogLevelManager
    {
        #region "Filed"
        private static readonly string[] _logLevelNames = { "����", "��ʾ", "����", "����", "����" };
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��־����
        /// </summary>
        public static string[] LogLevelNames
        {
            get { return _logLevelNames; }
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
