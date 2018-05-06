/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ACL
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/6 10:36:24 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ACL����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ZlgCanDemo
{
    /// <summary>
    /// ������ԶCAN��� - �ӿڿ⺯������
    /// </summary>
    static class VciNativeMethods
    {
        public const string DllPath = "ControlCAN.dll";
        /// <summary>
        /// �������سɹ���
        /// </summary>
        public static readonly int STATUS_OK = 1;

        /// <summary>
        /// ��������ʧ�ܡ�
        /// </summary>
        public static readonly int STATUS_ERR = 0;  

        /// <summary>
        /// �˺������Դ��豸��ע��һ���豸ֻ�ܴ�һ�Ρ�
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š����統ֻ��һ��PCIe-9221ʱ��������Ϊ0����ʱ�ٲ���һ��PCIe-9221����ô������������豸�����ž���1���Դ����ơ�</param>
        /// <param name="Reserved">����������ͨ��Ϊ0�������������豸ΪCANET-UDPʱ���˲�����ʾҪ�򿪵ı��ض˿ںţ�������5000��40000��Χ��ȡֵ�����豸ΪCANET-TCPʱ���˲����̶�Ϊ0����</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport(DllPath, EntryPoint = "VCI_OpenDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_OpenDevice(uint DeviceType, uint DeviceInd, uint Reserved); 
        /// <summary>
        /// �ر��豸��
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_CloseDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_CloseDevice(uint DeviceType, uint DeviceInd);        

        /// <summary>
        /// �Գ�ʼ��ָ����CANͨ�����ж��CANͨ��ʱ����Ҫ��ε��á�
        /// ע�⣺���豸����ΪPCI-5010-U��PCI-5020-U��USBCAN-E-U��USBCAN-2E-Uʱ�������ڵ��ô˺���֮ǰ����VCI_SetReference�Բ����ʽ������á�
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="pInitConfig">��ʼ�������ṹ��Ϊһ��VCI_INIT_CONFIG�ṹ�������
        /// �����������豸����ΪPCI-5010-U��PCI-5020-U��USBCAN-E-U��USBCAN-2E-Uʱ�����˲��Ͳ����ʵ�����Ӧ�÷ŵ�VCI_SetReference�����ã�
        /// ����pInitConfig�еĳ�Աֻ��Mode��Ҫ���ã�������6����Ա���Ժ��ԣ��������ü�VCI_SetReference˵��������</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�����������CANET��������ã����û᷵��1��</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_InitCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_InitCAN(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_INIT_CONFIG pInitConfig);

        /// <summary>
        /// ��ȡ�豸��Ϣ��
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="pInfo">�����洢�豸��Ϣ��VCI_BOARD_INFO�ṹָ�롣</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�
        /// ����������CANET���޴˺��������û᷵��0�����Ҵ��������ΪERR_CMDFAILED��</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadBoardInfo", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadBoardInfo(uint DeviceType, uint DeviceInd, ref VCI_BOARD_INFO pInfo);

        /// <summary>
        /// ��ȡCAN�����������һ�δ�����Ϣ��
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�
        /// ��������������VCI_OpenDevice��VCI_CloseDevice��VCI_ReadBoardInfo��Щ���ض��ĵڼ�·CAN�����޹صĲ�������ʧ�ܺ�
        /// ���ô˺�������ȡʧ�ܴ������ʱ��Ӧ�ð�CANIndex��Ϊ��1����</param>
        /// <param name="pErrInfo">�����洢������Ϣ��VCI_ERR_INFO�ṹָ�롣
        /// pErrInfo->ErrCode����Ϊ���и���������Ķ������֮һ��(CANET��ش�����룬��2.3�����붨��)</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadErrInfo", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadErrInfo(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_ERR_INFO pErrInfo);

        /// <summary>
        /// ��ȡCAN״̬
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="pCANStatus">�����洢CAN״̬��VCI_CAN_STATUS�ṹ��ָ�롣</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ���ע����CANET���޴˺��������û᷵��0����ȡ������ERR_CMDFAILED��</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadCANStatus", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadCANStatus(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_STATUS pCANStatus);

        /// <summary>
        /// ��ȡ�豸����Ӧ��������Ҫ��CANET����ز�������
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="RefType">�������͡�</param>
        /// <param name="pData">�����洢�����й����ݻ�������ַ��ָ�롣</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_GetReference", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_GetReference(uint DeviceType, uint DeviceInd, uint CANInd, uint RefType, ref object pData);
        /// <summary>
        /// �˺�����������CANET��PCI-5010-U/PCI-5020-U/USBCAN-E-U/ USBCAN-2E-U���豸����Ӧ��������Ҫ����ͬ�豸���ض�������
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="RefType">�������͡�</param>
        /// <param name="pData">�����洢�����й����ݻ�������ַ��ָ�롣</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_SetReference", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_SetReference(uint DeviceType, uint DeviceInd, uint CANInd, uint RefType, ref object pData);

        /// <summary>
        /// ��ȡָ��CANͨ���Ľ��ջ������У����յ�����δ����ȡ��֡������
        /// ��Ҫ��;�����VCI_Receiveʹ�ã��������������ݣ��ٽ��ա��û�����һֱ����VCI_Receive�����Խ�ԼPCϵͳ��Դ����߳���Ч�ʡ�
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <returns>������δ����ȡ��֡����</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_GetReceiveNum", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_GetReceiveNum(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// ���ָ��CANͨ���Ļ�������
        /// ��Ҫ������Ҫ������ջ��������ݵ������
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ClearBuffer", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ClearBuffer(uint DeviceType, uint DeviceInd, uint CANInd);

        
        /// <summary>
        /// ����CAN����ĳһ��CANͨ�����ж��CANͨ��ʱ����Ҫ��ε��á�
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_StartCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_StartCAN(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// ��λCAN��
        /// ��Ҫ��VCI_StartCAN���ʹ�ã������ٳ�ʼ�������ɻָ�CAN��������״̬�����統CAN���������߹ر�״̬ʱ�����Ե������������
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <returns>Ϊ1��ʾ�����ɹ���0��ʾ����ʧ�ܡ���ע����CANET-TCP�н���Ͽ����磬��Ҫ����VCI_StartCAN����ʹ�ã�</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ResetCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ResetCAN(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// ���ͺ�����
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="pSend">Ҫ���͵�֡�ṹ��VCI_CAN_OBJ�������ָ�롣</param>
        /// <param name="Len">Ҫ���͵�֡�ṹ������ĳ��ȣ����͵�֡��������</param>
        /// <returns>����ʵ�ʷ��ͳɹ���֡����</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_Transmit", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_Transmit(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_OBJ pSend, uint Len);

        /// <summary>
        /// ���պ���
        /// </summary>
        /// <param name="DeviceType">�豸���ͺš�</param>
        /// <param name="DeviceInd">�豸�����š�</param>
        /// <param name="CANInd">�ڼ�·CAN������Ӧ����CANͨ���ţ�CAN0Ϊ0��CAN1Ϊ1���Դ����ơ�</param>
        /// <param name="pReceive">�������յ�֡�ṹ��VCI_CAN_OBJ�������ָ�롣</param>
        /// <param name="Len">�������յ�֡�ṹ������ĳ��ȣ����ν��յ����֡����ʵ�ʷ���ֵС�ڵ������ֵ����</param>
        /// <param name="WaitTime">�����������ݣ����������ȴ�ʱ�䣬�Ժ���Ϊ��λ����Ϊ-1���ʾ�޳�ʱ��һֱ�ȴ���</param>
        /// <returns>����ʵ�ʶ�ȡ����֡����
        /// �������ֵΪ0xFFFFFFFF�����ʾ��ȡ����ʧ�ܣ��д������������VCI_ReadErrInfo��������ȡ�����롣</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_Receive", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_Receive(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_OBJ pReceive, uint Len, int WaitTime);  
    }
}
