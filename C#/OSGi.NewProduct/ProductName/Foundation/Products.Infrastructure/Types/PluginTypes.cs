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
        [MemberDes("��")]
        None = 0,
        /// <summary>
        /// ���в��
        /// </summary>
        [MemberDes("���в��")]
        All = UInt64.MaxValue,


        #region "��1��2�ֽڣ����λ�ֽڣ��������ҵ���޹صĲ����"
        /// <summary>
        /// �ڲ�ͨ�Ų��
        /// </summary>
        [MemberDes("�ڲ�ͨ��")]
        Communication = (1L << 0),
        /// <summary>
        /// �������߲��
        /// </summary>
        [MemberDes("��������")]
        HotStandby = (1L << 1),
        /// <summary>
        /// ʱ��ͬ�����
        /// </summary>
        [MemberDes("ʱ��ͬ��")]
        NTP = (1L << 2),
        /// <summary>
        /// �־û����
        /// </summary>
        [MemberDes("�־û�")]
        Persistence = (1L << 3),
        /// <summary>
        /// ����������
        /// </summary>
        [MemberDes("��־����")]
        LogReport = (1L << 4),

        // 

        /// <summary>
        /// ϵͳ�¼�����
        /// </summary>
        [MemberDes("ϵͳ�¼�����")]
        SEM = (1L << 8),
        /// <summary>
        /// �û�������
        /// </summary>
        [MemberDes("�û�����")]
        UAC = (1L << 9),
        /// <summary>
        /// �ڵ������
        /// </summary>
        [MemberDes("�ڵ����")]
        NDM = (1L << 10),

        // 11 ~ 15λԤ����
        #endregion


        #region "��3��4�ֽڣ����ҵ������"
        /// <summary>
        /// Plugin1
        /// </summary>
        [MemberDes("Plugin1")]
        Plugin1 = (1L << 16), // 65536
        /// <summary>
        /// Plugin2
        /// </summary>
        [MemberDes("Plugin2")]
        Plugin2 = (1L << 17), // 131072
        /// <summary>
        /// Plugin3
        /// </summary>
        [MemberDes("Plugin3")]
        Plugin3 = (1L << 18), // 262144
        /// <summary>
        /// Plugin4
        /// </summary>
        [MemberDes("Plugin4")]
        Plugin4 = (1L << 19), // 524288
        /// <summary>
        /// Plugin5
        /// </summary>
        [MemberDes("Plugin5")]
        Plugin5 = (1L << 20), // 1048576

        // 25 ~ 31λԤ����
        #endregion



        #region "��5��6��7�ֽڣ����ϵͳ�ӿڹ�������"
        /// <summary>
        /// �ӿڹ�����1��
        /// </summary>
        [MemberDes("�ӿڹ�����1")]
        Interface1 = (1L << 32),

        // 46 ~ 55��Ԥ����
        #endregion


        #region "��8�ֽڣ�Ԥ����"
        // 56 ~ 63��Ԥ����
        #endregion

    }
}
