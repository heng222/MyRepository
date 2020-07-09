/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Threading.Tasks;

using Acl.Log;

namespace Products
{
    /// <summary>
    /// TaskFactory ��չ��
    /// </summary>
    public static class TaskFactoryExtension
    {
        /// <summary>
        /// StartNewWithCatch ��չ������
        /// </summary>
        public static void StartNewWithCatch(this TaskFactory factory, Action action, ILog log)
        {
            factory.StartNew(() =>
            {
                try
                {
                    action();
                }
                catch (System.Exception ex)
                {
                    log.Error(ex);
                }
            });
        }

    }
}
