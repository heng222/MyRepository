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
    /// ϵͳ�¼����Ͷ���
    /// </summary>
    public enum EventType : int
    {
        #region "ͨ������"
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDes("��Ч")]
        None = 0,
        /// <summary>
        /// �ڵ��ͨ�Ž���
        /// </summary>
        [MemberDesAttribute("ͨ�Żָ�")]
        CommRecovery = 21,
        /// <summary>
        /// �ڵ��ͨ�ŶϿ�
        /// </summary>
        [MemberDesAttribute("ͨ���ж�")]
        CommInterruption = 22,
        #endregion


        #region "yyyy"

        #endregion
        
    }
}
