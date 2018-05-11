/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：05/23/2013 13:03:15 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 系统节点类型定义
    /// </summary>
    public enum NodeType : byte
    {
        /// <summary>
        /// 未知
        /// </summary>
        None = 0,

        #region "本系统节点"
        /// <summary>
        /// 中央服务器
        /// </summary>
        [MemberDes("中央服务器")]
        CenterServer = 0x01,
        /// <summary>
        /// 通信服务器
        /// </summary>
        [MemberDes("通信服务器")]
        CommFEP = 0x02,
        /// <summary>
        /// 车站服务器
        /// </summary>
        [MemberDes("车站服务器")]
        BranchServer = 0x03,
        /// <summary>
        /// 数据库服务器
        /// </summary>
        [MemberDes("数据库服务器")]
        Database = 0x04,
        /// <summary>
        /// DAP专用接口机
        /// </summary>
        [MemberDes("DAP接口机")]
        DAPGateway = 0x07,
        /// <summary>
        /// ATP专用接口机/ATP网关
        /// </summary>
        [MemberDes("ATP网关")]
        ATPGateWay = 0x08,
        /// <summary>
        /// 通用接口机
        /// </summary>
        [MemberDes("通用接口机")]
        GeneralInterfaceMachine = 0x09,
        /// <summary>
        /// 大屏服务器
        /// </summary>
        [MemberDes("大屏服务器")]
        LargeScreenServer = 0x0A, // 10

        /// <summary>
        /// 试车线工作站
        /// </summary>
        [MemberDes("试车线工作站")]
        CommissioningLineWorkstation = 0x0B, // 11

        /// <summary>
        /// 调度员工作站
        /// </summary>
        [MemberDes("调度员工作站")]
        DispatcherWorkStation = 0x20, // 32
        /// <summary>
        /// 调度主任工作站
        /// </summary>
        [MemberDes("调度主任工作站")]
        DispatcherDirector = 0x22, // 34
        /// <summary>
        /// 维护工作站
        /// </summary>
        [MemberDes("中心维护工作站")]
        CenterMaintenanceWorkStation = 0x24, // 36
        /// <summary>
        /// 运行图显示工作站
        /// </summary>
        [MemberDes("运行图显示工作站")]
        ScheduleDisplayWorkStation = 0x26, // 38
        /// <summary>
        /// 运行图/时刻表编辑工作站
        /// </summary>
        [MemberDes("运行图/时刻表编辑工作站")]
        ScheduleEditWorkStation = 0x28, // 40
        /// <summary>
        /// 大屏显示工作站
        /// </summary>
        [MemberDes("大屏显示工作站")]
        LargeScreenWorkStation = 0x2A, // 42
        /// <summary>
        /// 培训/演示工作站
        /// </summary>
        [MemberDes("培训/演示工作站")]
        TrainningWorkstation = 0x2B, // 43

        /// <summary>
        /// 车站显示终端
        /// </summary>
        [MemberDes("显示终端")]
        DisplayTerminal = 0x34, // 52
        /// <summary>
        /// DTI接口机
        /// </summary>
        [MemberDes("显示终端及DTI接口机")]
        DTIGateway = 0x35, // 53
        /// <summary>
        /// 派班工作站
        /// </summary>
        [MemberDes("派班工作站")]
        ArrangementWorkStation = 0x36, // 54
        /// <summary>
        /// 集中站-现地控制工作站
        /// </summary>
        [MemberDes("集中站现地")]
        MainLocalWorkStation = 0x3A, // 58
        /// <summary>
        /// 非集中站-现地控制工作站
        /// </summary>
        [MemberDes("非集中站现地")]
        SecondaryLocalWorkStation = 0x3B, // 59
        /// <summary>
        /// 车站维护终端
        /// </summary>
        [MemberDes("车站维护终端")]
        LocalMaintenanceTerminal = 0x3E, // 62 

        /// <summary>
        /// 内部设备定义的最大值
        /// </summary>
        InternalMaxValue = 0x6F, // 111
        #endregion

        #region "CI子系统节点"
        /// <summary>
        /// 联锁机
        /// </summary>
        [MemberDes("联锁下位机")]
        CiLowerMachine = 0x70, // 112
        /// <summary>
        /// 联锁上位机
        /// </summary>
        [MemberDes("联锁上位机")]
        CiUpperMachine = 0x72, // 114
        /// <summary>
        /// 联锁维修机
        /// </summary>
        [MemberDes("联锁维修机")]
        CiMaintenanceMachine = 0x74, // 116
        /// <summary>
        /// CI设备定义的最大值
        /// </summary>
        CIMaxValue = 0x8F, // 143
        #endregion

        #region "ATP子系统节点"
        /// <summary>
        /// ATP区域控制器
        /// </summary>
        [MemberDes("ATP区域控制器")]
        ZC = 0x92, // 146
        /// <summary>
        /// ATP数据库存储单元
        /// </summary>
        [MemberDes("ATP数据库存储单元")]
        DSU = 0x94, // 148
        /// <summary>
        /// 车载ATP控制器
        /// </summary>
        [MemberDes("车载ATP控制器")]
        VOBC = 0x96, // 150
        /// <summary>
        /// ATP设备定义的最大值
        /// </summary>
        ATPMaxValue = 0xAF, // 175
        #endregion

        #region "非信号专业子系统"
        /// <summary>
        /// 时钟
        /// </summary>
        [MemberDes("时钟")]
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
        /// 无线通信
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
