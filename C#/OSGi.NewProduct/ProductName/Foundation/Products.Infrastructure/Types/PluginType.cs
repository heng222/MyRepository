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
    public enum PluginType : ulong
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDesAttribute("��")]
        None = 0,


        #region "��1��2�ֽڣ����λ�ֽڣ��������ҵ���޹صĲ����"
        /// <summary>
        /// �ڲ�ͨ�Ų��
        /// </summary>
        [MemberDesAttribute("�ڲ�ͨ�Ų��")]
        Communication = (1L << 0),
        /// <summary>
        /// �������߲��
        /// </summary>
        [MemberDesAttribute("�������߲��")]
        HotStandby = (1L << 1),
        /// <summary>
        /// ʱ��ͬ�����
        /// </summary>
        [MemberDesAttribute("ʱ��ͬ�����")]
        NTP = (1L << 2),

        // 3 ~ 7λԤ����

        /// <summary>
        /// �������
        /// </summary>
        [MemberDesAttribute("�������")]
        Alarm = (1L << 8),
        /// <summary>
        /// �û�������
        /// </summary>
        [MemberDesAttribute("�û�������")]
        Usermanagement = (1L << 9),
        /// <summary>
        /// �ڵ������
        /// </summary>
        [MemberDesAttribute("�ڵ������")]
        NDM = (1L << 10),

        // 11 ~ 15λԤ����
        #endregion


        #region "��3��4�ֽڣ����ҵ������"
        /// <summary>
        /// վ���豸������
        /// </summary>
        [MemberDesAttribute("վ���豸������")]
        SDM = (1L << 16),
        /// <summary>
        /// ����ͼ���
        /// </summary>
        [MemberDesAttribute("����ͼ���")]
        Schedule = (1L << 17),
        /// <summary>
        /// �Զ���·���
        /// </summary>
        [MemberDesAttribute("�Զ���·���")]
        ARS = (1L << 18),
        /// <summary>
        /// �г�������׷�ٲ��
        /// </summary>
        [MemberDesAttribute("�г�������׷�ٲ��")]
        TMT = (1L << 19),
        /// <summary>
        /// �طŲ��
        /// </summary>
        [MemberDesAttribute("�طŲ��")]
        Replay = (1L << 20),
        /// <summary>
        /// ����ʹ�ù�����
        /// </summary>
        [MemberDesAttribute("����ʹ�ù�����")]
        VUM = (1L << 21),
        /// <summary>
        /// ��ȫ���������TSR�����Ḵλ��ǿ�����ȣ���
        /// </summary>
        [MemberDesAttribute("��ȫ�������")]
        SafetyOperation = (1L << 22),
        /// <summary>
        /// ��־/��������
        /// </summary>
        [MemberDesAttribute("��־/������")]
        StatisticReport = (1L << 23),
        ///// <summary>
        ///// ���Ḵλ�����
        ///// </summary>
        //[MemberDesAttribute("���Ḵλ���")]
        //AxleReset = (1L << 24),

        // 25 ~ 31λԤ����
        #endregion



        #region "��5��6��7�ֽڣ����ϵͳ�ӿڹ�������"
        /// <summary>
        /// CI�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("CI�ӿڹ�����")]
        CI = (1L << 32),
        /// <summary>
        /// ATP�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("ATP�ӿڹ�����")]
        ATP = (1L << 33),
        /// <summary>
        /// ʱ��Уʱ�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("CLK�ӿڹ�����")]
        CLK = (1L << 34),
        /// <summary>
        /// �ÿ���Ϣϵͳ�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("PIS�ӿڹ�����")]
        PIS = (1L << 35),
        /// <summary>
        /// �ۺϼ��ϵͳ�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("ISCS�ӿڹ�����")]
        ISCS = (1L << 36),
        /// <summary>
        /// �����ָͨ�����Ľӿڹ�������
        /// </summary>
        [MemberDesAttribute("TCC�ӿڹ�����")]
        TCC = (1L << 37),
        /// <summary>
        /// ��ϵͳ�ӿڹ�������
        /// </summary>
        [MemberDesAttribute("FAS�ӿڹ�����")]
        FAS = (1L << 38),
        /// <summary>
        /// ����ͨ�Žӿڹ�������
        /// </summary>
        [MemberDesAttribute("RAD�ӿڹ�����")]
        RAD = (1L << 39),
        /// <summary>
        /// ΢�����ӿڹ�������
        /// </summary>
        [MemberDesAttribute("CSM�ӿڹ�����")]
        CSM = (1L << 40),
        /// <summary>
        /// ά����֧��ϵͳ�ӿڹ�������
        /// </summary>
        [MemberDes("MSS�ӿڹ�����")]
        MSS = (1L << 41),
        /// <summary>
        /// ����ָʾ���ӿڹ�������
        /// </summary>
        [MemberDes("DTI�ӿڹ�����")]
        DTI = (1L << 42),
        /// <summary>
        /// CCTV�ӿڹ�������
        /// </summary>
        [MemberDes("CCTV�ӿڹ�������")]
        CCTV = (1L << 43),
        /// <summary>
        /// �����㲥�ӿڹ�������
        /// </summary>
        [MemberDes("PAS�ӿڹ�����")]
        PAS = (1L << 44),
        /// <summary>
        /// �����ӿڹ�������
        /// </summary>
        [MemberDes("OPS�ӿڹ�����")]
        OPS = (1L << 45),
        /// <summary>
        /// DAP�ӿڹ�������
        /// </summary>
        [MemberDes("DAP�ӿڹ�����")]
        DAP = (1L << 46),

        // 46 ~ 55��Ԥ����
        #endregion


        #region "��8�ֽڣ�Ԥ����"
        // 56 ~ 63��Ԥ����
        #endregion

    }
}
