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
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Persistence.Specification
{
    /// <summary>
    /// ���ݻ���ӿڡ�
    /// </summary>
    interface IDataCache
    {
        /// <summary>
        /// ��ȡʵ�����
        /// </summary>
        /// <param name="condition">ָ����������</param>
        /// <param name="entityType">ʵ�����͡�</param>
        /// <returns></returns>
        object GetValue(Dictionary<string, object> condition, Type entityType);
    }
}
