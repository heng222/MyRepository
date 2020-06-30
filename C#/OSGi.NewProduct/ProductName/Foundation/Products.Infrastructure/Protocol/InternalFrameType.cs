using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure.Protocol
{
    /// <summary>
    /// �ڲ�Э��֡������
    /// </summary>
    public enum InternalFrameType : byte
    {
        /// <summary>
        /// ��Ч
        /// </summary>
        [MemberDes("��Ч")]
        None = 0,

        /// <summary>
        /// RPC��Ϣ֡
        /// </summary>
        [MemberDes("RPC��Ϣ֡")]
        Rpc = 0x03, // 3

        /// <summary>
        /// ϵͳ����ͬ��֡��
        /// </summary>
        [MemberDes("ϵͳ����ͬ��֡")]
        SystemConfigSync = 0x0A, // 10
        /// <summary>
        /// �û���֤��Ϣ֡
        /// </summary>
        [MemberDes("�û���֤��Ϣ֡")]
        UserAuthentication = 0x10, // 16
        /// <summary>
        /// �ڵ�״̬֡
        /// </summary>
        [MemberDes("�ڵ�״̬֡")]
        NodeState = 0x1A, // 26
        /// <summary>
        /// ������Ϣ֡
        /// </summary>
        [MemberDes("������Ϣ֡")]
        TrainPositionReport = 0x28, // 40
        /// <summary>
        /// �г���Ϣ֡
        /// </summary>
        [MemberDes("�г���Ϣ֡")]
        TrainInfo = 0x51, // 81
        /// <summary>
        /// ����������״̬֡
        /// </summary>
        [MemberDes("����������״̬֡")]
        MBWorkingState = 0x6A, // 106
        /// <summary>
        /// ����״̬֡
        /// </summary>
        [MemberDes("����״̬֡")]
        NetWorkState = 0x75, // 117
        /// <summary>
        /// �ն˷����ƻ���Ϣ֡
        /// </summary>
        [MemberDes("�ն˷����ƻ���Ϣ֡")]
        TerminalPlan = 0x7C, // 124
        /// <summary>
        /// �ɰ�ƻ���Ϣ֡
        /// </summary>
        [MemberDes("�ɰ�ƻ���Ϣ֡")]
        DispatchPlan = 0x83, // 131
        /// <summary>
        /// ����֡
        /// </summary>
        [MemberDes("����֡")]
        Alarm = 0x8E, // 142
        /// <summary>
        /// ��������֡
        /// </summary>
        [MemberDes("��������֡")]
        ControlCommand = 0xA5, // 165
        /// <summary>
        /// ���������Ӧ֡
        /// </summary>
        [MemberDes("���������Ӧ֡")]
        CtrlCmdResponse = 0xAF, // 175
        /// <summary>
        /// վ����Ϣ֡
        /// </summary>
        [MemberDes("վ����Ϣ֡")]
        StationState = 0xBB, // 187
        /// <summary>
        /// ����ͼ����֡
        /// </summary>
        [MemberDes("����ͼ����֡")]
        TimeTableAdjust = 0xC3, // 195
        /// <summary>
        /// ��վ����Ȩ
        /// </summary>
        [MemberDes("��վ����Ȩ")]
        StationControl = 0xD3, // 211
        /// <summary>
        /// �Զ���·��ͻ֡
        /// </summary>
        [MemberDes("�Զ���·��ͻ֡")]
        RouteCollision = 0xD6, // 214
    }
}
