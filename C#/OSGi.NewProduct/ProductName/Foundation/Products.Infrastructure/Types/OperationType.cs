/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
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

        #region "��λ����ز���"
        /// <summary>
        /// ��Ӧ�������ġ�
        /// </summary>
        [MemberDes("��Ӧ��������")]
        ReadBalisePackage = 0x02,
        /// <summary>
        /// �޸���λ����ַ��
        /// </summary>
        [MemberDes("�޸���λ����ַ")]
        ModifyHypMacAddr = 0x04,
        /// <summary>
        /// ��ѯ��λ��״̬��
        /// </summary>
        [MemberDes("��ѯ��λ��״̬")]
        QueryHypogyMacState = 0x06,
        #endregion

        #region "�ڵ������ز���"
        /// <summary>
        /// �����ڵ�
        /// </summary>
        [MemberDes("�����ڵ�")]
        AddNewNode = 0x11,
        /// <summary>
        /// �Ƴ��ڵ�
        /// </summary>
        [MemberDes("�Ƴ��ڵ�")]
        RemoveNode = 0x12,
        #endregion
    }
}
