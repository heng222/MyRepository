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
using System.Collections.Generic;

namespace Products
{
    /// <summary>
    /// IEnumerable ��չ��
    /// </summary>
    public static class IEnumerableExtension
    {
        /// <summary>
        /// IEnumerable.ForEach ��չ������
        /// </summary>
        public static void ForEach<T>(this IEnumerable<T> items, Action<T> action)
        {
            var it = items.GetEnumerator();
            while (it.MoveNext())
            {
                action(it.Current);
            }
        }

    }
}
