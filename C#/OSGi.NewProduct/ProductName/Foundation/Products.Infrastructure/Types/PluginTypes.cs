/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�09/16/2011 07:36:38 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/
using System;

using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// ��ϵͳ��ʹ�õĲ�����͡�
    /// ʹ��8���ֽ�λ��ķ�ʽ��ʾ��һ���ɱ�ʾ64�ֲ�����͡�
    /// </summary>
    [Flags]
    public enum PluginTypes : ulong
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDesAttribute("��")]
        None = 0,
        /// <summary>
        /// ���в��
        /// </summary>
        [MemberDesAttribute("���в��")]
        All = UInt64.MaxValue,


        #region "��1��2�ֽڣ����λ�ֽڣ��������ҵ���޹صĲ����"
        /// <summary>
        /// �ڲ�ͨ�Ų��
        /// </summary>
        [MemberDesAttribute("�ڲ�ͨ��")]
        Communication = (1L << 0),
        /// <summary>
        /// �������߲��
        /// </summary>
        [MemberDesAttribute("��������")]
        HotStandby = (1L << 1),
        /// <summary>
        /// ʱ��ͬ�����
        /// </summary>
        [MemberDesAttribute("ʱ��ͬ��")]
        NTP = (1L << 2),
        /// <summary>
        /// �־û����
        /// </summary>
        [MemberDesAttribute("�־û�")]
        Persistence = (1L << 3),
        /// <summary>
        /// ����������
        /// </summary>
        [MemberDesAttribute("��־����")]
        LogReport = (1L << 4),

        // 

        /// <summary>
        /// ϵͳ�¼�����
        /// </summary>
        [MemberDesAttribute("ϵͳ�¼�����")]
        SEM = (1L << 8),
        /// <summary>
        /// �û��������
        /// </summary>
        [MemberDesAttribute("�û�����")]
        UAC = (1L << 9),
        /// <summary>
        /// �ڵ�������
        /// </summary>
        [MemberDesAttribute("�ڵ����")]
        NDM = (1L << 10),

        // 11 ~ 15λԤ����
        #endregion


        #region "��3��4�ֽڣ����ҵ������"
        /// <summary>
        /// Plugin1
        /// </summary>
        [MemberDesAttribute("Plugin1")]
        Plugin1 = (1L << 16), // 65536
        /// <summary>
        /// Plugin2
        /// </summary>
        [MemberDesAttribute("Plugin2")]
        Plugin2 = (1L << 17), // 131072
        /// <summary>
        /// Plugin3
        /// </summary>
        [MemberDesAttribute("Plugin3")]
        Plugin3 = (1L << 18), // 262144
        /// <summary>
        /// Plugin4
        /// </summary>
        [MemberDesAttribute("Plugin4")]
        Plugin4 = (1L << 19), // 524288
        /// <summary>
        /// Plugin5
        /// </summary>
        [MemberDesAttribute("Plugin5")]
        Plugin5 = (1L << 20), // 1048576

        // 25 ~ 31λԤ����
        #endregion



        #region "��5��6��7�ֽڣ����ϵͳ�ӿڹ��������"
        /// <summary>
        /// �ӿڹ������1��
        /// </summary>
        [MemberDesAttribute("�ӿڹ������1")]
        Interface1 = (1L << 32),

        // 46 ~ 55��Ԥ����
        #endregion


        #region "��8�ֽڣ�Ԥ����"
        // 56 ~ 63��Ԥ����
        #endregion

    }
}