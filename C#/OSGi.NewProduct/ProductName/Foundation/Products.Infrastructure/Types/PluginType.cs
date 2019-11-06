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
        /// <summary>
        /// 所有插件
        /// </summary>
        [MemberDesAttribute("所有插件")]
        All = UInt64.MaxValue,


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
        /// <summary>
        /// 持久化插件
        /// </summary>
        [MemberDesAttribute("持久化插件")]
        Persistence = (1L << 3),

        // 3 ~ 7位预留。

        /// <summary>
        /// 系统事件管理
        /// </summary>
        [MemberDesAttribute("系统事件管理")]
        SEM = (1L << 8),
        /// <summary>
        /// 用户管理插件
        /// </summary>
        [MemberDesAttribute("用户管理插件")]
        UAC = (1L << 9),
        /// <summary>
        /// 节点管理插件
        /// </summary>
        [MemberDesAttribute("节点管理插件")]
        NDM = (1L << 10),

        // 11 ~ 15位预留。
        #endregion


        #region "第3、4字节，存放业务插件。"
        /// <summary>
        /// Plugin1
        /// </summary>
        [MemberDesAttribute("Plugin1")]
        Plugin1 = (1L << 16), // 65536
        /// <summary>
        /// Plugin2
        /// </summary>
        [MemberDesAttribute("Plugin2")]
        Plugin2 = (1L << 17), // 131072
        /// <summary>
        /// Plugin3
        /// </summary>
        [MemberDesAttribute("Plugin3")]
        Plugin3 = (1L << 18), // 262144
        /// <summary>
        /// Plugin4
        /// </summary>
        [MemberDesAttribute("Plugin4")]
        Plugin4 = (1L << 19), // 524288
        /// <summary>
        /// Plugin5
        /// </summary>
        [MemberDesAttribute("Plugin5")]
        Plugin5 = (1L << 20), // 1048576

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
        // 46 ~ 55，预留。
        #endregion


        #region "第8字节，预留。"
        // 56 ~ 63，预留。
        #endregion

    }
}
