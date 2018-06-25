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
    /// ATC�е���ϵͳ���͡�
    /// </summary>
    public enum AtcSubsystemType : byte
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDesAttribute("��Ч")]
        None = 0,

        /// <summary>
        /// ATS
        /// </summary>
        [MemberDesAttribute("ATS")]
        ATS = 0x03,

        /// <summary>
        /// ����ATP
        /// </summary>
        [MemberDesAttribute("����ATP")]
        VOBC = 0x14,

        /// <summary>
        /// ATO
        /// </summary>
        [MemberDesAttribute("ATO")]
        ATO = 0x08,

        /// <summary>
        /// ATP���������
        /// </summary>
        [MemberDesAttribute("ZC")]
        ZC = 0x1E,

        /// <summary>
        /// ���ݿ�洢��Ԫ
        /// </summary>
        [MemberDesAttribute("DSU")]
        DMS = 0x2B,

        /// <summary>
        /// ΢������
        /// </summary>
        [MemberDesAttribute("CI")]
        CI = 0x3C,
    };
}
