/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/6/11 15:16:54 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 泰可斯科技，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 系统事件管理接口。
    /// </summary>
    public interface ISystemEventManage
    {
        #region "系统事件"
        /// <summary>
        /// 获取指定类型的事件级别。
        /// </summary>
        /// <param name="eventType">事件类型</param>
        /// <returns>事件级别</returns>
        EventLevel GetEventLevel(EventType eventType);
        /// <summary>
        /// 获取一个值，用于指示指定类型的事件是否需要确认。
        /// </summary>
        /// <param name="eventType">事件类型。</param>
        /// <returns>true 表示需要确认，false表示不需要确认。</returns>
        bool GetConfirmEnabled(EventType eventType);
        /// <summary>
        /// 新增系统事件
        /// </summary>
        void AddSysEventLog(SysEventLog log);
        /// <summary>
        /// 更新系统事件
        /// </summary>
        void UpdateSysEventLog(SysEventLog log);
        #endregion

        #region "操作记录"
        /// <summary>
        /// 获取指定编号的操作记录
        /// </summary>
        OperationLog GetOperationLog(uint code);
        /// <summary>
        /// 新增操作记录
        /// </summary>
        void AddOperationLog(OperationLog log);
        /// <summary>
        /// 更新操作记录
        /// </summary>
        void UpdateOperationLog(OperationLog log);
        #endregion
    }
}
