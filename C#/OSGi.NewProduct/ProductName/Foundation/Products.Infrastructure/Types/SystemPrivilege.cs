using System;
using System.Collections.Generic;
using System.Text;
using Acl.Utility;

namespace Products.Infrastructure
{
    /// <summary>
    /// ϵͳȨ�޶��塣
    /// �μ�RBACģʽ�е�Ȩ�ޡ�
    /// </summary>
    public enum SystemPrivilege : byte
    {
        /// <summary>
        /// ���κ�Ȩ�ޡ�
        /// </summary>
        [MemberDes("���κ�Ȩ��")]
        None = byte.MinValue,
        /// <summary>
        /// ����Ȩ�ޡ�
        /// </summary>
        [MemberDes("����Ȩ��")]
        All = byte.MaxValue,

        // ע��region����ԭ��ΪRBAC�е�What��Ȩ����ԵĶ������Դ����

        #region "ϵͳȨ��"
        /// <summary>
        /// �༭ϵͳ������
        /// </summary>
        [MemberDes("�༭ϵͳ����")]
        EditSysParam = 2,

        /// <summary>
        /// ��ʾ����������־��
        /// </summary>
        [MemberDes("��ʾ����������־")]
        ShowAppLog = 3,
        /// <summary>
        /// ��ʾʱ��ؼ���
        /// </summary>
        [MemberDes("��ʾʱ��ؼ�")]
        ShowNixieTubeClock = 5, 

        /// <summary>
        /// ��ʾ�۳��ؼ�
        /// </summary>
        [MemberDes("��ʾ�۳��ؼ�")]
        ShowSkipHold = 7,

        /// <summary>
        /// ��ʾ�ڲ�ͨ��״̬��
        /// </summary>
        [MemberDes("��ʾ�ڲ�ͨ��״̬")]
        ShowCommState = 9,

        /// <summary>
        /// ��ʾ�ط���Ϣ��վ���طš��ڵ�״̬�طš�������¼�طţ�
        /// </summary>
        [MemberDes("��ʾ�ط�")]
        ShowReplay = 11,

        /// <summary>
        /// ��ʾͳ�Ʊ���
        /// </summary>
        [MemberDes("��ʾͳ�Ʊ���")]
        ShowStatisticReport = 13,
        #endregion


        #region"վ�������Ȩ��"
        /// <summary>
        /// ��ʾվ��ͼ��
        /// </summary>
        [MemberDes("��ʾվ��ͼ")]
        ShowStationView = 50,
        /// <summary>
        /// ��ʾ���ܰ�ť��
        /// </summary>
        [MemberDes("��ʾ���ܰ�ť")]
        ShowFunctionButton = 51,
        /// <summary>
        /// ��ʾ��ʾ�ơ�
        /// </summary>
        [MemberDes("��ʾ��ʾ��")]
        ShowIndicationLamp = 52,        
        /// <summary>
        /// ����վ������
        /// </summary>
        [MemberDes("����վ������")]
        CenterControl = 53,
        /// <summary>
        /// ��վվ������
        /// </summary>
        [MemberDes("��վվ������")]
        StationControl = 54,
        /// <summary>
        /// ���ܰ�ť����
        /// </summary>
        [MemberDes("���ܰ�ť����")]
        FunctionButtonControl = 55,
        ///// <summary>
        ///// �༭���Ų��ԡ�
        ///// </summary>
        //[MemberDes("���Ų��Կ���")]
        //EditDoorOpeningStrategy = 56,
        /// <summary>
        /// ����Ź���
        /// </summary>
        [MemberDes("����Ź���")]
        EditTrainPhysicalNo = 57,
        /// <summary>
        /// ��ƻ���
        /// </summary>
        [MemberDes("��ƻ���")]
        SetPlanTrain = 58,
        /// <summary>
        /// ��Ŀ�ĵس�
        /// </summary>
        [MemberDes("��Ŀ�ĵس�")]
        SetDestTrain = 59,
        /// <summary>
        /// ���˹���
        /// </summary>
        [MemberDes("���˹���")]
        SetManualTrain = 60,
        /// <summary>
        /// �������˹���
        /// </summary>
        [MemberDes("�������˹���")]
        SetSpecialManualTrain = 61,
        /// <summary>
        /// �ر��г��Զ�����
        /// </summary>
        [MemberDes("�ر��г��Զ�����")]
        AdustmentBySchedule = 62,
        /// <summary>
        /// TSR������
        /// </summary>
        [MemberDes("TSR����")]
        TsrOperation = 63,
        /// <summary>
        /// ���Ḵλ������
        /// </summary>
        [MemberDes("���Ḵλ����")]
        AxleCounterReset = 64,
        /// <summary>
        /// ����ǿ�������
        /// </summary>
        [MemberDes("����ǿ�����")]
        SwitchForcedPull = 65,
        
        #endregion


        #region "�ڵ�����Ȩ��"
        /// <summary>
        /// �༭�ڵ�
        /// </summary>
        [MemberDes("�༭�ڵ�")]
        EditDeviceNode = 100,
        /// <summary>
        /// ��ʾȫ�߽ڵ�״̬
        /// </summary>
        [MemberDes("��ʾȫ�߽ڵ�״̬")]
        ShowGlobalNodeState = 101,
        /// <summary>
        /// ��ʾ��վ�ڵ�״̬��
        /// </summary>
        [MemberDes("��ʾ��վ�ڵ�״̬")]
        ShowStationNodeState = 102,
        /// <summary>
        /// ��ʾ������ʽ�ڵ�״̬��
        /// </summary>
        [MemberDes("��ʾ������ʽ�ڵ�״̬")]
        ShowToolbarNodeState = 103,
        #endregion


        #region "�û������Ȩ��"
        /// <summary>
        /// �鿴�û���Ϣ��
        /// </summary>
        [MemberDes("�鿴�û���Ϣ")]
        ShowUserInfo = 110,
        /// <summary>
        /// �༭�û�
        /// </summary>
        [MemberDes("�༭�û�")]
        EditUser = 111,
        #endregion


        #region "���������Ȩ��"
        /// <summary>
        /// ��ʾ������Ϣ��
        /// </summary>
        [MemberDes("��ʾ������Ϣ")]
        ShowAlarm = 120,
        /// <summary>
        /// �༭������Ϣ
        /// </summary>
        [MemberDes("�༭������Ϣ")]
        EditAlarm = 121,
        /// <summary>
        /// ��ʾ�û����Խ��б���ȷ�ϲ�����
        /// </summary>
        [MemberDes("����ȷ��")]
        ConfirmAlarm = 122,
        #endregion
        
    }
}
