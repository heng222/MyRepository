/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ACL
//
// 创 建 人：heng222_z
// 创建日期：2018/5/6 9:44:27 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ACL，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZlgCanDemo
{
    /// <summary>
    /// 广州致远接口卡设备类型定义
    /// </summary>
    enum ZhiyuanDeviceType : uint
    {
        VCI_None = 0,

        VCI_PCI5121 = 1,

        /// <summary>
        /// PCI-9810I
        /// </summary>
        VCI_PCI9810 = 2,

        /// <summary>
        /// USBCAN-I/I+
        /// </summary>
        VCI_USBCAN1 = 3,

        /// <summary>
        /// USBCAN-II/II+
        /// </summary>
        VCI_USBCAN2 = 4,
        VCI_USBCAN2A = 4,

        /// <summary>
        /// PCI-9820
        /// </summary>
        VCI_PCI9820 = 5,

        VCI_CAN232 = 6,
        VCI_PCI5110 = 7,
        VCI_CANLITE = 8,
        VCI_ISA9620 = 9,
        VCI_ISA5420 = 10,
        VCI_PC104CAN = 11,

        /// <summary>
        /// CANET-100T/200T、CANET-E/2E+的UDP工作方式
        /// </summary>
        VCI_CANETUDP = 12,
        VCI_CANETE = 12,

        VCI_DNP9810 = 13,

        /// <summary>
        /// PCI-9840I
        /// </summary>
        VCI_PCI9840 = 14,

        /// <summary>
        /// PC104-CAN2I
        /// </summary>
        VCI_PC104CAN2 = 15,

        /// <summary>
        /// PCI-9820I
        /// </summary>
        VCI_PCI9820I = 16,

        /// <summary>
        /// CANET-100T/200T的TCP工作方式
        /// </summary>
        VCI_CANETTCP = 17,

        VCI_PEC9920 = 18,

        /// <summary>
        /// PCI-5010-U
        /// </summary>
        VCI_PCI5010U = 19,

        /// <summary>
        /// USBCAN-E-U
        /// </summary>
        VCI_USBCAN_E_U = 20,

        /// <summary>
        /// USBCAN-2E-U
        /// </summary>
        VCI_USBCAN_2E_U = 21,

        /// <summary>
        /// PCI-5020-U
        /// </summary>
        VCI_PCI5020U = 22,
        VCI_EG20T_CAN = 23,

        /// <summary>
        /// PCIe-9221
        /// </summary>
        VCI_PCIE9221 = 24,
    }

}
