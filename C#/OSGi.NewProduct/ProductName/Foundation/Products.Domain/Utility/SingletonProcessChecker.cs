/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�wqs_486
// �������ڣ�2013-7-3 16:51:49 
// ��    �䣺wqs_486@163.com
//
// Copyright (C) 2013 ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Collections.Specialized;
using System.Reflection;
using System.Threading;

namespace Products.Domain.Utility
{
    /// <summary>
    /// ������ʵ�������
    /// </summary>
    public class SingletonProcessChecker : IDisposable
    {
        /// <summary>
        /// ������
        /// </summary>
        private Mutex _mutex;
        /// <summary>
        /// �õ�һ��ֵ����ָʾ�Ƿ�ͨ�����
        /// </summary>
        public bool IsPassed { get; private set; }

        /// <summary>
        /// ���쵥����ʵ�������
        /// </summary>
        /// <param name="symbolicName"></param>
        public SingletonProcessChecker(string symbolicName)
        {
            bool createdNew;
            _mutex = new Mutex(true, symbolicName, out createdNew);

            IsPassed = createdNew;
        }

        /// <summary>
        /// �ͷ���Դ
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (_mutex != null)
            {
                _mutex.Close();
                _mutex = null;
            }
        }
    }
}
