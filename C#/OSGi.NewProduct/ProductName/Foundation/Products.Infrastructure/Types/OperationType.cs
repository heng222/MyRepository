/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
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
    /// ��������
    /// </summary>
    public enum OperationType : byte
    {
        /// <summary>
        /// ��Ч������
        /// </summary>
        [MemberDes("��Ч����")]
        None = 0,

        #region "��������1"
        /// <summary>
        /// X����
        /// </summary>
        [MemberDes("X����")]
        OperationX = 0x11,
        #endregion
    }
}
