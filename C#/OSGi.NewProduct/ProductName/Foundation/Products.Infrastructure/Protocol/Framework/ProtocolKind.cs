/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�03/02/2012 15:13:41 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009-2015 ��������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// ��ʾͨѶЭ�������
    /// </summary>
    [Flags]
    public enum ProtocolKind : ulong
    {
        /// <summary>
        /// ϵͳ�ڲ�ͨѶЭ��
        /// </summary>
        Internal = 0x00000001,

        /// <summary>
        /// ��ϵͳ �� �ⲿϵͳ1 ��ͨѶЭ��
        /// </summary>
        CI = 0x00000002,
        /// <summary>
        /// ��ϵͳ �� �ⲿϵͳ2 ��ͨѶЭ��
        /// </summary>
        ATP = 0x00000004,
        /// <summary>
        /// ��ϵͳ �� �ⲿϵͳ3 ��ͨѶЭ��
        /// </summary>
        CLK = 0x00000008,
        /// <summary>
        /// ��ϵͳ �� �ⲿϵͳ4 ��ͨѶЭ��
        /// </summary>
        FAS = 0x00000010,
        /// <summary>
        /// ��ϵͳ �� �ⲿϵͳ5 ��ͨѶЭ��
        /// </summary>
        ISCS = 0x00000020,
    }
}
