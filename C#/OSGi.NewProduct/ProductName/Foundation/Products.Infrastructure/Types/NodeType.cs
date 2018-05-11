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
    public enum NodeType : byte
    {
        /// <summary>
        /// δ֪
        /// </summary>
        None = 0,

        #region "��ϵͳ�ڵ�"
        /// <summary>
        /// ���������
        /// </summary>
        [MemberDes("���������")]
        CenterServer = 0x01,
        /// <summary>
        /// ͨ�ŷ�����
        /// </summary>
        [MemberDes("ͨ�ŷ�����")]
        CommFEP = 0x02,
        /// <summary>
        /// ��վ������
        /// </summary>
        [MemberDes("��վ������")]
        BranchServer = 0x03,
        /// <summary>
        /// ���ݿ������
        /// </summary>
        [MemberDes("���ݿ������")]
        Database = 0x04,
        /// <summary>
        /// DAPר�ýӿڻ�
        /// </summary>
        [MemberDes("DAP�ӿڻ�")]
        DAPGateway = 0x07,
        /// <summary>
        /// ATPר�ýӿڻ�/ATP����
        /// </summary>
        [MemberDes("ATP����")]
        ATPGateWay = 0x08,
        /// <summary>
        /// ͨ�ýӿڻ�
        /// </summary>
        [MemberDes("ͨ�ýӿڻ�")]
        GeneralInterfaceMachine = 0x09,
        /// <summary>
        /// ����������
        /// </summary>
        [MemberDes("����������")]
        LargeScreenServer = 0x0A, // 10

        /// <summary>
        /// �Գ��߹���վ
        /// </summary>
        [MemberDes("�Գ��߹���վ")]
        CommissioningLineWorkstation = 0x0B, // 11

        /// <summary>
        /// ����Ա����վ
        /// </summary>
        [MemberDes("����Ա����վ")]
        DispatcherWorkStation = 0x20, // 32
        /// <summary>
        /// �������ι���վ
        /// </summary>
        [MemberDes("�������ι���վ")]
        DispatcherDirector = 0x22, // 34
        /// <summary>
        /// ά������վ
        /// </summary>
        [MemberDes("����ά������վ")]
        CenterMaintenanceWorkStation = 0x24, // 36
        /// <summary>
        /// ����ͼ��ʾ����վ
        /// </summary>
        [MemberDes("����ͼ��ʾ����վ")]
        ScheduleDisplayWorkStation = 0x26, // 38
        /// <summary>
        /// ����ͼ/ʱ�̱�༭����վ
        /// </summary>
        [MemberDes("����ͼ/ʱ�̱�༭����վ")]
        ScheduleEditWorkStation = 0x28, // 40
        /// <summary>
        /// ������ʾ����վ
        /// </summary>
        [MemberDes("������ʾ����վ")]
        LargeScreenWorkStation = 0x2A, // 42
        /// <summary>
        /// ��ѵ/��ʾ����վ
        /// </summary>
        [MemberDes("��ѵ/��ʾ����վ")]
        TrainningWorkstation = 0x2B, // 43

        /// <summary>
        /// ��վ��ʾ�ն�
        /// </summary>
        [MemberDes("��ʾ�ն�")]
        DisplayTerminal = 0x34, // 52
        /// <summary>
        /// DTI�ӿڻ�
        /// </summary>
        [MemberDes("��ʾ�ն˼�DTI�ӿڻ�")]
        DTIGateway = 0x35, // 53
        /// <summary>
        /// �ɰ๤��վ
        /// </summary>
        [MemberDes("�ɰ๤��վ")]
        ArrangementWorkStation = 0x36, // 54
        /// <summary>
        /// ����վ-�ֵؿ��ƹ���վ
        /// </summary>
        [MemberDes("����վ�ֵ�")]
        MainLocalWorkStation = 0x3A, // 58
        /// <summary>
        /// �Ǽ���վ-�ֵؿ��ƹ���վ
        /// </summary>
        [MemberDes("�Ǽ���վ�ֵ�")]
        SecondaryLocalWorkStation = 0x3B, // 59
        /// <summary>
        /// ��վά���ն�
        /// </summary>
        [MemberDes("��վά���ն�")]
        LocalMaintenanceTerminal = 0x3E, // 62 

        /// <summary>
        /// �ڲ��豸��������ֵ
        /// </summary>
        InternalMaxValue = 0x6F, // 111
        #endregion

        #region "CI��ϵͳ�ڵ�"
        /// <summary>
        /// ������
        /// </summary>
        [MemberDes("������λ��")]
        CiLowerMachine = 0x70, // 112
        /// <summary>
        /// ������λ��
        /// </summary>
        [MemberDes("������λ��")]
        CiUpperMachine = 0x72, // 114
        /// <summary>
        /// ����ά�޻�
        /// </summary>
        [MemberDes("����ά�޻�")]
        CiMaintenanceMachine = 0x74, // 116
        /// <summary>
        /// CI�豸��������ֵ
        /// </summary>
        CIMaxValue = 0x8F, // 143
        #endregion

        #region "ATP��ϵͳ�ڵ�"
        /// <summary>
        /// ATP���������
        /// </summary>
        [MemberDes("ATP���������")]
        ZC = 0x92, // 146
        /// <summary>
        /// ATP���ݿ�洢��Ԫ
        /// </summary>
        [MemberDes("ATP���ݿ�洢��Ԫ")]
        DSU = 0x94, // 148
        /// <summary>
        /// ����ATP������
        /// </summary>
        [MemberDes("����ATP������")]
        VOBC = 0x96, // 150
        /// <summary>
        /// ATP�豸��������ֵ
        /// </summary>
        ATPMaxValue = 0xAF, // 175
        #endregion

        #region "���ź�רҵ��ϵͳ"
        /// <summary>
        /// ʱ��
        /// </summary>
        [MemberDes("ʱ��")]
        Clock = 0xB0, // 176
        /// <summary>
        /// PIS
        /// </summary>
        [MemberDes("PIS")]
        PIS = 0xB2, // 178
        /// <summary>
        /// SCS
        /// </summary>
        [MemberDes("ISCS")]
        ISCS = 0xB4, // 180
        /// <summary>
        /// CSM
        /// </summary>
        [MemberDes("CSM")]
        CSM = 0xB5, // 181
        /// <summary>
        /// MSS
        /// </summary>
        [MemberDes("MSS")]
        MSS = 0xB6, // 182
        /// <summary>
        /// ����ͨ��
        /// </summary>
        [MemberDes("RAD")]
        RAD = 0xB8, // 184
        /// <summary>
        /// TCC
        /// </summary>
        [MemberDes("TCC")]
        TCC = 0xBA, // 186
        /// <summary>
        /// DTI
        /// </summary>
        [MemberDes("DTI")]
        DTI = 0xBB, // 187
        /// <summary>
        /// FAS
        /// </summary>
        [MemberDes("FAS")]
        FAS = 0xBC, // 188
        /// <summary>
        /// CCTV
        /// </summary>
        [MemberDes("CCTV")]
        CCTV = 0xBD, // 189
        /// <summary>
        /// PAS
        /// </summary>
        [MemberDes("PAS")]
        PAS = 0xBE, // 190
        /// <summary>
        /// DAP
        /// </summary>
        [MemberDes("DAP")]
        DAP = 0xBF, //191

        #endregion
    }

}
