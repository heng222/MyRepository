/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�05/23/2013 13:03:15 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// ϵͳ�¼������塣
    /// </summary>
    public enum EventLevel : byte
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDes("��Ч")]
        None = 0,

        /// <summary>
        /// һ��
        /// </summary>
        [MemberDes("һ��")]
        First = 1,
  
        /// <summary>
        /// ����
        /// </summary>
        [MemberDes("����")]
        Second = 2,

        /// <summary>
        /// ����
        /// </summary>
        [MemberDes("����")]
        Third = 3,
    }
}
