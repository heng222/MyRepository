/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2017/7/13 11:47:58 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2017 ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// ��ȫͨ��Э�鶨�塣
    /// </summary>
    public enum SafetyCommProtocol : byte
    {
        /// <summary>
        /// ��
        /// </summary>
        None = 0,

        /// <summary>
        /// RSSP-I
        /// </summary>
        RsspI = 1,

        /// <summary>
        /// RSSP-II
        /// </summary>
        RsspII = 2
    }
}
