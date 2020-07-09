/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
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

using System.Threading;

namespace Products.Domain.Utility
{
    /// <summary>
    /// ������ʵ�������
    /// </summary>
    public class SingletonProcessChecker : Acl.CompositeDisposable
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
            this.AddDisposable(_mutex);

            IsPassed = createdNew;
        }
    }
}
