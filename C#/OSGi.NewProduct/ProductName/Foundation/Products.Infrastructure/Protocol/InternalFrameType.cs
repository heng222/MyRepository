using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure.Protocol
{
    /// <summary>
    /// 内部协议帧主类型
    /// </summary>
    public enum InternalFrameType : byte
    {
        /// <summary>
        /// 无效
        /// </summary>
        [MemberDes("无效")]
        None = 0,

        /// <summary>
        /// RPC信息帧
        /// </summary>
        [MemberDes("RPC信息帧")]
        Rpc = 0x03, // 3

        /// <summary>
        /// 系统配置同步帧。
        /// </summary>
        [MemberDes("系统配置同步帧")]
        SystemConfigSync = 0x0A, // 10
        /// <summary>
        /// 用户验证信息帧
        /// </summary>
        [MemberDes("用户验证信息帧")]
        UserAuthentication = 0x10, // 16
        /// <summary>
        /// 节点状态帧
        /// </summary>
        [MemberDes("节点状态帧")]
        NodeState = 0x1A, // 26
        /// <summary>
        /// 报点信息帧
        /// </summary>
        [MemberDes("报点信息帧")]
        TrainPositionReport = 0x28, // 40
        /// <summary>
        /// 列车信息帧
        /// </summary>
        [MemberDes("列车信息帧")]
        TrainInfo = 0x51, // 81
        /// <summary>
        /// 主备机工作状态帧
        /// </summary>
        [MemberDes("主备机工作状态帧")]
        MBWorkingState = 0x6A, // 106
        /// <summary>
        /// 网络状态帧
        /// </summary>
        [MemberDes("网络状态帧")]
        NetWorkState = 0x75, // 117
        /// <summary>
        /// 终端发车计划信息帧
        /// </summary>
        [MemberDes("终端发车计划信息帧")]
        TerminalPlan = 0x7C, // 124
        /// <summary>
        /// 派班计划信息帧
        /// </summary>
        [MemberDes("派班计划信息帧")]
        DispatchPlan = 0x83, // 131
        /// <summary>
        /// 报警帧
        /// </summary>
        [MemberDes("报警帧")]
        Alarm = 0x8E, // 142
        /// <summary>
        /// 控制命令帧
        /// </summary>
        [MemberDes("控制命令帧")]
        ControlCommand = 0xA5, // 165
        /// <summary>
        /// 控制命令回应帧
        /// </summary>
        [MemberDes("控制命令回应帧")]
        CtrlCmdResponse = 0xAF, // 175
        /// <summary>
        /// 站场信息帧
        /// </summary>
        [MemberDes("站场信息帧")]
        StationState = 0xBB, // 187
        /// <summary>
        /// 运行图调整帧
        /// </summary>
        [MemberDes("运行图调整帧")]
        TimeTableAdjust = 0xC3, // 195
        /// <summary>
        /// 车站控制权
        /// </summary>
        [MemberDes("车站控制权")]
        StationControl = 0xD3, // 211
        /// <summary>
        /// 自动排路冲突帧
        /// </summary>
        [MemberDes("自动排路冲突帧")]
        RouteCollision = 0xD6, // 214
    }
}
