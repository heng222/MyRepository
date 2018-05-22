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
    public enum SystemPrivilege : int
    {
        /// <summary>
        /// ���κ�Ȩ��
        /// </summary>
        [MemberDes("���κ�Ȩ��")]
        None = 0,

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


        #region "�г������Ȩ��"
        /// <summary>
        /// ��ʾ�г��б���ͼ��
        /// </summary>
        [MemberDes("��ʾ�г��б���ͼ")]
        ShowOnlineTrainListView = 201,
        /// <summary>
        /// ��ʾ����ʹ�ù���
        /// </summary>
        [MemberDes("��ʾ����ʹ�ù���")]
        ShowVUM = 203,
        /// <summary>
        /// �༭����ʹ�ù���
        /// </summary>
        [MemberDes("�༭����ʹ�ù���")]
        EditVUM = 205,
        #endregion


        #region "����ͼ�����Ȩ��"
        /// <summary>
        /// ��ʾ����ͼ��
        /// </summary>
        [MemberDes("��ʾ����ͼ")]
        ShowSchedule = 255,
        /// <summary>
        /// �༭����ͼ
        /// </summary>
        [MemberDes("�༭����ͼ")]
        EditBasicTimetable = 257,
        /// <summary>
        /// �༭�ƻ�ͼ
        /// </summary>
        [MemberDes("�༭�ƻ�ͼ")]
        EditOnlineTimetable = 259,
        /// <summary>
        /// �༭��Ӫ�ƻ�
        /// </summary>
        [MemberDes("�༭��Ӫ�ƻ�")]
        EditOperationPlan = 261,
        /// <summary>
        /// �༭�ɰ�ƻ�
        /// </summary>
        [MemberDes("�༭�ɰ�ƻ�")]
        EditDispatchPlan = 263,
        /// <summary>
        /// �༭����ƻ�
        /// </summary>
        [MemberDes("�༭����ƻ�")]
        EditTrainConsist = 265,
        /// <summary>
        /// �����ն˷����ƻ�
        /// </summary>
        [MemberDes("�ն˷����ƻ�����")]
        EditTerminalDeparturePlan = 267,
        #endregion


        #region "�ڵ�����Ȩ��"
        /// <summary>
        /// �༭�ڵ�����ͼ
        /// </summary>
        [MemberDes("�༭�ڵ�����ͼ")]
        EditNodeTopologyModel = 305,
        /// <summary>
        /// ��ʾȫ�߽ڵ�״̬
        /// </summary>
        [MemberDes("��ʾȫ�߽ڵ�״̬")]
        ShowGlobalNodeState = 307,
        /// <summary>
        /// ��ʾ��վ�ڵ�״̬��
        /// </summary>
        [MemberDes("��ʾ��վ�ڵ�״̬")]
        ShowStationNodeState = 309,
        /// <summary>
        /// ��ʾ������ʽ�ڵ�״̬��
        /// </summary>
        [MemberDes("��ʾ������ʽ�ڵ�״̬")]
        ShowToolbarNodeState = 311,
        #endregion


        #region "�û������Ȩ��"
        /// <summary>
        /// �鿴�û���Ϣ��
        /// </summary>
        [MemberDes("�鿴�û���Ϣ")]
        ShowUserInfo = 335,
        /// <summary>
        /// �༭�û�
        /// </summary>
        [MemberDes("�༭�û�")]
        EditUser = 336,
        #endregion


        #region "���������Ȩ��"
        /// <summary>
        /// ��ʾ������Ϣ��
        /// </summary>
        [MemberDes("��ʾ������Ϣ")]
        ShowAlarm = 441,
        /// <summary>
        /// �༭������Ϣ
        /// </summary>
        [MemberDes("�༭������Ϣ")]
        EditAlarm = 443,
        /// <summary>
        /// ��ʾ�û����Խ��б���ȷ�ϲ�����
        /// </summary>
        [MemberDes("����ȷ��")]
        ConfirmAlarm = 445,
        #endregion
        
    }
}
