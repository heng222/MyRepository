
using Acl.Utility;

namespace Products.Infrastructure
{
    /// <summary>
    /// 系统权限定义。
    /// 参见RBAC模式中的权限。
    /// </summary>
    public enum SystemPrivilege : byte
    {
        /// <summary>
        /// 无任何权限。
        /// </summary>
        [MemberDes("无任何权限")]
        None = byte.MinValue,
        /// <summary>
        /// 所有权限。
        /// </summary>
        [MemberDes("所有权限")]
        All = byte.MaxValue,

        // 注：region分类原则为RBAC中的What（权限针对的对象或资源）。

        #region "系统权限"

        /// <summary>
        /// 编辑系统参数。
        /// </summary>
        [MemberDes("编辑系统参数")]
        EditSysParam = 2,

        /// <summary>
        /// 显示程序运行日志。
        /// </summary>
        [MemberDes("显示程序运行日志")]
        ShowAppLog = 3,
        /// <summary>
        /// 显示时间控件。
        /// </summary>
        [MemberDes("显示时间控件")]
        ShowNixieTubeClock = 5,

        /// <summary>
        /// 显示扣车控件
        /// </summary>
        [MemberDes("显示扣车控件")]
        ShowSkipHold = 7,

        /// <summary>
        /// 显示内部通信状态。
        /// </summary>
        [MemberDes("显示内部通信状态")]
        ShowCommState = 9,

        /// <summary>
        /// 显示回放信息（站场回放、节点状态回放、操作记录回放）
        /// </summary>
        [MemberDes("显示回放")]
        ShowReplay = 11,

        /// <summary>
        /// 显示统计报表
        /// </summary>
        [MemberDes("显示统计报表")]
        ShowStatisticReport = 13,
        #endregion


        #region"站场的相关权限"
        /// <summary>
        /// 显示站场图。
        /// </summary>
        [MemberDes("显示站场图")]
        ShowStationView = 50,
        /// <summary>
        /// 显示功能按钮。
        /// </summary>
        [MemberDes("显示功能按钮")]
        ShowFunctionButton = 51,
        /// <summary>
        /// 显示表示灯。
        /// </summary>
        [MemberDes("显示表示灯")]
        ShowIndicationLamp = 52,
        /// <summary>
        /// 中心站场控制
        /// </summary>
        [MemberDes("中心站场控制")]
        CenterControl = 53,
        /// <summary>
        /// 车站站场控制
        /// </summary>
        [MemberDes("车站站场控制")]
        StationControl = 54,
        /// <summary>
        /// 功能按钮操作
        /// </summary>
        [MemberDes("功能按钮控制")]
        FunctionButtonControl = 55,
        ///// <summary>
        ///// 编辑开门策略。
        ///// </summary>
        //[MemberDes("开门策略控制")]
        //EditDoorOpeningStrategy = 56,
        /// <summary>
        /// 车组号管理
        /// </summary>
        [MemberDes("车组号管理")]
        EditTrainPhysicalNo = 57,
        /// <summary>
        /// 设计划车
        /// </summary>
        [MemberDes("设计划车")]
        SetPlanTrain = 58,
        /// <summary>
        /// 设目的地车
        /// </summary>
        [MemberDes("设目的地车")]
        SetDestTrain = 59,
        /// <summary>
        /// 设人工车
        /// </summary>
        [MemberDes("设人工车")]
        SetManualTrain = 60,
        /// <summary>
        /// 设特殊人工车
        /// </summary>
        [MemberDes("设特殊人工车")]
        SetSpecialManualTrain = 61,
        /// <summary>
        /// 关闭列车自动调整
        /// </summary>
        [MemberDes("关闭列车自动调整")]
        AdustmentBySchedule = 62,
        /// <summary>
        /// TSR操作。
        /// </summary>
        [MemberDes("TSR操作")]
        TsrOperation = 63,
        /// <summary>
        /// 计轴复位操作。
        /// </summary>
        [MemberDes("计轴复位操作")]
        AxleCounterReset = 64,
        /// <summary>
        /// 道岔强扳操作。
        /// </summary>
        [MemberDes("道岔强扳操作")]
        SwitchForcedPull = 65,

        #endregion


        #region "节点的相关权限"
        /// <summary>
        /// 编辑节点
        /// </summary>
        [MemberDes("编辑节点")]
        EditDeviceNode = 100,
        /// <summary>
        /// 显示全线节点状态
        /// </summary>
        [MemberDes("显示全线节点状态")]
        ShowGlobalNodeState = 101,
        /// <summary>
        /// 显示车站节点状态。
        /// </summary>
        [MemberDes("显示车站节点状态")]
        ShowStationNodeState = 102,
        /// <summary>
        /// 显示工具栏式节点状态。
        /// </summary>
        [MemberDes("显示工具栏式节点状态")]
        ShowToolbarNodeState = 103,
        #endregion


        #region "用户的相关权限"
        /// <summary>
        /// 查看用户信息。
        /// </summary>
        [MemberDes("查看用户信息")]
        ShowUserInfo = 110,
        /// <summary>
        /// 编辑用户
        /// </summary>
        [MemberDes("编辑用户")]
        EditUser = 111,
        #endregion


        #region "报警的相关权限"
        /// <summary>
        /// 显示报警信息。
        /// </summary>
        [MemberDes("显示报警信息")]
        ShowAlarm = 120,
        /// <summary>
        /// 编辑报警信息
        /// </summary>
        [MemberDes("编辑报警信息")]
        EditAlarm = 121,
        /// <summary>
        /// 表示用户可以进行报警确认操作。
        /// </summary>
        [MemberDes("报警确认")]
        ConfirmAlarm = 122,
        #endregion

    }
}
