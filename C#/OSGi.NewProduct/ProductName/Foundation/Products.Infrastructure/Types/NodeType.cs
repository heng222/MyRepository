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
    /// ϵͳ�ڵ����Ͷ���
    /// </summary>
    public enum NodeType : ushort
    {
        /// <summary>
        /// δ֪
        /// </summary>
        None = 0,

        /// <summary>
        /// Ĭ�Ͻڵ� ��
        /// </summary>
        Default = Node1,

        #region "��ϵͳ�ڵ�"
        /// <summary>
        /// �ڵ�����1
        /// </summary>
        [MemberDes("�ڵ�����1")]
        Node1 = 16,
        /// <summary>
        /// �ڵ�����2
        /// </summary>
        [MemberDes("�ڵ�����2")]
        Node2 = 18,
        #endregion
    }

}
