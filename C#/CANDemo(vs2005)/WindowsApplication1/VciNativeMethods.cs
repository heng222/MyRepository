/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ACL
//
// 创 建 人：heng222_z
// 创建日期：2018/5/6 10:36:24 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ACL，保留所有权利。
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
    /// 广州致远CAN板块 - 接口库函数定义
    /// </summary>
    static class VciNativeMethods
    {
        public const string DllPath = "ControlCAN.dll";
        /// <summary>
        /// 函数返回成功。
        /// </summary>
        public static readonly int STATUS_OK = 1;

        /// <summary>
        /// 函数返回失败。
        /// </summary>
        public static readonly int STATUS_ERR = 0;  

        /// <summary>
        /// 此函数用以打开设备。注意一个设备只能打开一次。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。比如当只有一个PCIe-9221时，索引号为0，这时再插入一个PCIe-9221，那么后面插入的这个设备索引号就是1，以此类推。</param>
        /// <param name="Reserved">保留参数，通常为0。（特例：当设备为CANET-UDP时，此参数表示要打开的本地端口号，建议在5000到40000范围内取值。当设备为CANET-TCP时，此参数固定为0。）</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport(DllPath, EntryPoint = "VCI_OpenDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_OpenDevice(uint DeviceType, uint DeviceInd, uint Reserved); 
        /// <summary>
        /// 关闭设备。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_CloseDevice", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_CloseDevice(uint DeviceType, uint DeviceInd);        

        /// <summary>
        /// 以初始化指定的CAN通道。有多个CAN通道时，需要多次调用。
        /// 注意：当设备类型为PCI-5010-U、PCI-5020-U、USBCAN-E-U、USBCAN-2E-U时，必须在调用此函数之前调用VCI_SetReference对波特率进行设置。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="pInitConfig">初始化参数结构，为一个VCI_INIT_CONFIG结构体变量。
        /// （特例：当设备类型为PCI-5010-U、PCI-5020-U、USBCAN-E-U、USBCAN-2E-U时，对滤波和波特率的设置应该放到VCI_SetReference里设置，
        /// 这里pInitConfig中的成员只有Mode需要设置，其他的6个成员可以忽略，具体设置见VCI_SetReference说明；）。</param>
        /// <returns>为1表示操作成功，0表示操作失败。（特例：在CANET中无需调用，调用会返回1）</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_InitCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_InitCAN(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_INIT_CONFIG pInitConfig);

        /// <summary>
        /// 获取设备信息。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="pInfo">用来存储设备信息的VCI_BOARD_INFO结构指针。</param>
        /// <returns>为1表示操作成功，0表示操作失败。
        /// （特例：在CANET中无此函数，调用会返回0，并且错误码填充为ERR_CMDFAILED）</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadBoardInfo", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadBoardInfo(uint DeviceType, uint DeviceInd, ref VCI_BOARD_INFO pInfo);

        /// <summary>
        /// 获取CAN卡发生的最近一次错误信息。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。
        /// （特例：当调用VCI_OpenDevice，VCI_CloseDevice和VCI_ReadBoardInfo这些与特定的第几路CAN操作无关的操作函数失败后，
        /// 调用此函数来获取失败错误码的时候应该把CANIndex设为－1。）</param>
        /// <param name="pErrInfo">用来存储错误信息的VCI_ERR_INFO结构指针。
        /// pErrInfo->ErrCode可能为下列各个错误码的多种组合之一：(CANET相关错误代码，见2.3错误码定义)</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadErrInfo", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadErrInfo(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_ERR_INFO pErrInfo);

        /// <summary>
        /// 获取CAN状态
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="pCANStatus">用来存储CAN状态的VCI_CAN_STATUS结构体指针。</param>
        /// <returns>为1表示操作成功，0表示操作失败。（注：在CANET中无此函数，调用会返回0，获取错误码ERR_CMDFAILED）</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ReadCANStatus", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ReadCANStatus(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_STATUS pCANStatus);

        /// <summary>
        /// 获取设备的相应参数（主要是CANET的相关参数）。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="RefType">参数类型。</param>
        /// <param name="pData">用来存储参数有关数据缓冲区地址首指针。</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_GetReference", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_GetReference(uint DeviceType, uint DeviceInd, uint CANInd, uint RefType, ref object pData);
        /// <summary>
        /// 此函数用以设置CANET与PCI-5010-U/PCI-5020-U/USBCAN-E-U/ USBCAN-2E-U等设备的相应参数，主要处理不同设备的特定操作。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="RefType">参数类型。</param>
        /// <param name="pData">用来存储参数有关数据缓冲区地址首指针。</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_SetReference", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_SetReference(uint DeviceType, uint DeviceInd, uint CANInd, uint RefType, ref object pData);

        /// <summary>
        /// 获取指定CAN通道的接收缓冲区中，接收到但尚未被读取的帧数量。
        /// 主要用途是配合VCI_Receive使用，即缓冲区有数据，再接收。用户无需一直调用VCI_Receive，可以节约PC系统资源，提高程序效率。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <returns>返回尚未被读取的帧数。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_GetReceiveNum", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_GetReceiveNum(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// 清空指定CAN通道的缓冲区。
        /// 主要用于需要清除接收缓冲区数据的情况。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ClearBuffer", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ClearBuffer(uint DeviceType, uint DeviceInd, uint CANInd);

        
        /// <summary>
        /// 启动CAN卡的某一个CAN通道。有多个CAN通道时，需要多次调用。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <returns>为1表示操作成功，0表示操作失败。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_StartCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_StartCAN(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// 复位CAN。
        /// 主要与VCI_StartCAN配合使用，无需再初始化，即可恢复CAN卡的正常状态。比如当CAN卡进入总线关闭状态时，可以调用这个函数。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <returns>为1表示操作成功，0表示操作失败。（注：在CANET-TCP中将会断开网络，需要重新VCI_StartCAN才能使用）</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_ResetCAN", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_ResetCAN(uint DeviceType, uint DeviceInd, uint CANInd);

        /// <summary>
        /// 发送函数。
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="pSend">要发送的帧结构体VCI_CAN_OBJ数组的首指针。</param>
        /// <param name="Len">要发送的帧结构体数组的长度（发送的帧数量）。</param>
        /// <returns>返回实际发送成功的帧数。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_Transmit", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_Transmit(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_OBJ pSend, uint Len);

        /// <summary>
        /// 接收函数
        /// </summary>
        /// <param name="DeviceType">设备类型号。</param>
        /// <param name="DeviceInd">设备索引号。</param>
        /// <param name="CANInd">第几路CAN。即对应卡的CAN通道号，CAN0为0，CAN1为1，以此类推。</param>
        /// <param name="pReceive">用来接收的帧结构体VCI_CAN_OBJ数组的首指针。</param>
        /// <param name="Len">用来接收的帧结构体数组的长度（本次接收的最大帧数，实际返回值小于等于这个值）。</param>
        /// <param name="WaitTime">缓冲区无数据，函数阻塞等待时间，以毫秒为单位。若为-1则表示无超时，一直等待。</param>
        /// <returns>返回实际读取到的帧数。
        /// 如果返回值为0xFFFFFFFF，则表示读取数据失败，有错误发生，请调用VCI_ReadErrInfo函数来获取错误码。</returns>
        [DllImport("ControlCAN.dll", EntryPoint = "VCI_Receive", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern uint VCI_Receive(uint DeviceType, uint DeviceInd, uint CANInd, ref VCI_CAN_OBJ pReceive, uint Len, int WaitTime);  
    }
}
