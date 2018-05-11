/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：09/16/2011 07:36:38 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/
using System;
using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// 本系统中使用的插件类型。
    /// 使用8个字节位域的方式表示，一共可表示64种插件类型。
    /// </summary>
    [Flags]
    public enum PluginType : ulong
    {
        /// <summary>
        /// 无效
        /// </summary>
        [MemberDesAttribute("无")]
        None = 0,


        #region "第1、2字节（最低位字节），存放与业务无关的插件。"
        /// <summary>
        /// 内部通信插件
        /// </summary>
        [MemberDesAttribute("内部通信插件")]
        Communication = (1L << 0),
        /// <summary>
        /// 主备决策插件
        /// </summary>
        [MemberDesAttribute("主备决策插件")]
        HotStandby = (1L << 1),
        /// <summary>
        /// 时钟同步插件
        /// </summary>
        [MemberDesAttribute("时钟同步插件")]
        NTP = (1L << 2),

        // 3 ~ 7位预留。

        /// <summary>
        /// 报警插件
        /// </summary>
        [MemberDesAttribute("报警插件")]
        Alarm = (1L << 8),
        /// <summary>
        /// 用户管理插件
        /// </summary>
        [MemberDesAttribute("用户管理插件")]
        Usermanagement = (1L << 9),
        /// <summary>
        /// 节点管理插件
        /// </summary>
        [MemberDesAttribute("节点管理插件")]
        NDM = (1L << 10),

        // 11 ~ 15位预留。
        #endregion


        #region "第3、4字节，存放业务插件。"
        /// <summary>
        /// 站场设备管理插件
        /// </summary>
        [MemberDesAttribute("站场设备管理插件")]
        SDM = (1L << 16),
        /// <summary>
        /// 运行图插件
        /// </summary>
        [MemberDesAttribute("运行图插件")]
        Schedule = (1L << 17),
        /// <summary>
        /// 自动排路插件
        /// </summary>
        [MemberDesAttribute("自动排路插件")]
        ARS = (1L << 18),
        /// <summary>
        /// 列车监视与追踪插件
        /// </summary>
        [MemberDesAttribute("列车监视与追踪插件")]
        TMT = (1L << 19),
        /// <summary>
        /// 回放插件
        /// </summary>
        [MemberDesAttribute("回放插件")]
        Replay = (1L << 20),
        /// <summary>
        /// 车辆使用管理插件
        /// </summary>
        [MemberDesAttribute("车辆使用管理插件")]
        VUM = (1L << 21),
        /// <summary>
        /// 安全操作插件（TSR、计轴复位、强扳道岔等）。
        /// </summary>
        [MemberDesAttribute("安全操作插件")]
        SafetyOperation = (1L << 22),
        /// <summary>
        /// 日志/报表插件。
        /// </summary>
        [MemberDesAttribute("日志/报表插件")]
        StatisticReport = (1L << 23),
        ///// <summary>
        ///// 计轴复位插件。
        ///// </summary>
        //[MemberDesAttribute("计轴复位插件")]
        //AxleReset = (1L << 24),

        // 25 ~ 31位预留。
        #endregion



        #region "第5、6、7字节（存放系统接口管理插件）"
        /// <summary>
        /// CI接口管理插件。
        /// </summary>
        [MemberDesAttribute("CI接口管理插件")]
        CI = (1L << 32),
        /// <summary>
        /// ATP接口管理插件。
        /// </summary>
        [MemberDesAttribute("ATP接口管理插件")]
        ATP = (1L << 33),
        /// <summary>
        /// 时钟校时接口管理插件。
        /// </summary>
        [MemberDesAttribute("CLK接口管理插件")]
        CLK = (1L << 34),
        /// <summary>
        /// 旅客信息系统接口管理插件。
        /// </summary>
        [MemberDesAttribute("PIS接口管理插件")]
        PIS = (1L << 35),
        /// <summary>
        /// 综合监控系统接口管理插件。
        /// </summary>
        [MemberDesAttribute("ISCS接口管理插件")]
        ISCS = (1L << 36),
        /// <summary>
        /// 轨道交通指挥中心接口管理插件。
        /// </summary>
        [MemberDesAttribute("TCC接口管理插件")]
        TCC = (1L << 37),
        /// <summary>
        /// 火警系统接口管理插件。
        /// </summary>
        [MemberDesAttribute("FAS接口管理插件")]
        FAS = (1L << 38),
        /// <summary>
        /// 无线通信接口管理插件。
        /// </summary>
        [MemberDesAttribute("RAD接口管理插件")]
        RAD = (1L << 39),
        /// <summary>
        /// 微机监测接口管理插件。
        /// </summary>
        [MemberDesAttribute("CSM接口管理插件")]
        CSM = (1L << 40),
        /// <summary>
        /// 维护与支持系统接口管理插件。
        /// </summary>
        [MemberDes("MSS接口管理插件")]
        MSS = (1L << 41),
        /// <summary>
        /// 发车指示器接口管理插件。
        /// </summary>
        [MemberDes("DTI接口管理插件")]
        DTI = (1L << 42),
        /// <summary>
        /// CCTV接口管理插件。
        /// </summary>
        [MemberDes("CCTV接口管理插件。")]
        CCTV = (1L << 43),
        /// <summary>
        /// 公共广播接口管理插件。
        /// </summary>
        [MemberDes("PAS接口管理插件")]
        PAS = (1L << 44),
        /// <summary>
        /// 大屏接口管理插件。
        /// </summary>
        [MemberDes("OPS接口管理插件")]
        OPS = (1L << 45),
        /// <summary>
        /// DAP接口管理插件。
        /// </summary>
        [MemberDes("DAP接口管理插件")]
        DAP = (1L << 46),

        // 46 ~ 55，预留。
        #endregion


        #region "第8字节，预留。"
        // 56 ~ 63，预留。
        #endregion

    }
}
