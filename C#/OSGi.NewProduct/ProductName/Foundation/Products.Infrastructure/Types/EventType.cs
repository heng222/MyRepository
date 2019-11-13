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
    /// 系统事件类型定义
    /// </summary>
    public enum EventType : int
    {
        #region "通用类型"
        /// <summary>
        /// 无效
        /// </summary>
        [MemberDes("无效")]
        None = 0,
        /// <summary>
        /// 节点间通信建立
        /// </summary>
        [MemberDesAttribute("通信恢复")]
        CommRecovery = 21,
        /// <summary>
        /// 节点间通信断开
        /// </summary>
        [MemberDesAttribute("通信中断")]
        CommInterruption = 22,
        #endregion


        #region "yyyy"

        #endregion
        
    }
}
