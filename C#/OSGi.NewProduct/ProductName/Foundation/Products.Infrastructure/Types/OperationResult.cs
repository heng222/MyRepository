/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// �������
    /// </summary>
    public enum OperationResult : byte
    {
        /// <summary>
        /// δ֪
        /// </summary>
        [MemberDes("δ֪")]
        Unknown = 0,

        /// <summary>
        /// �ɹ�
        /// </summary>
        [MemberDes("�ɹ�")]
        Success = 1,

        /// <summary>
        /// ʧ��
        /// </summary>
        [MemberDes("ʧ��")]
        Failure = 2,

        /// <summary>
        /// ��Ӧ��ʱ
        /// </summary>
        [MemberDes("��ʱ")]
        Timeout = 3,
    }
}
