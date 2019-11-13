/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/6/11 15:20:19 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 泰可斯科技，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure;
using Products.Infrastructure.Specification;
using Products.Domain;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// 系统事件管理实现类。
    /// </summary>
    class SystemEventManageImpl : ISystemEventManage
    {
        #region "Field"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"

        public EventLevel GetEventLevel(EventType eventType)
        {
            var theReord = GlobalServices.Repository.Where<SysEvent>(p => (EventType)p.Code == eventType).FirstOrDefault();
            return theReord != null ? theReord.LevelCode : EventLevel.None;
        }

        public bool GetConfirmEnabled(EventType eventType)
        {
            var theReord = GlobalServices.Repository.Where<SysEvent>(p => (EventType)p.Code == eventType).FirstOrDefault();
            return theReord != null ? theReord.ConfirmEnabled : false;
        }

        public OperationLog GetOperationLog(uint code)
        {
            return GlobalServices.Repository.Where<OperationLog>(p=>p.Code == code).FirstOrDefault();
        }

        public void AddOperationLog(OperationLog log)
        {
            if (log.Code == Entity.InvalidCode)
            {
                log.Code = GlobalServices.Repository.NextSequence<OperationLog>();
            }

            GlobalServices.Repository.Insert(log);
        }
        public void UpdateOperationLog(OperationLog log)
        {
            GlobalServices.Repository.Update<OperationLog>(log, p => p.Code == log.Code);
        }

        public void AddSysEventLog(SysEventLog log)
        {
            if (log.Code == Entity.InvalidCode)
            {
                log.Code = GlobalServices.Repository.NextSequence<SysEventLog>();
            }

            GlobalServices.Repository.Insert(log);
        }
        public void UpdateSysEventLog(SysEventLog log)
        {
            GlobalServices.Repository.Update<SysEventLog>(log, p => p.Code == log.Code);
        }
        #endregion
    }
}
