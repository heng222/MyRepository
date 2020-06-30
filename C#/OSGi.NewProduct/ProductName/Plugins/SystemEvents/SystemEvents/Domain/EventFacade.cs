/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/5/25 9:57:36 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Acl;

using Products.Infrastructure.Specification;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// 子系统外观类。
    /// </summary>
    public class EventFacade : CompositeDisposable
    {
        #region "Field"
        private SystemEventManageImpl _sysEventMgr = new SystemEventManageImpl();
        private PersistenceProcessor _eventPeristence = new PersistenceProcessor();
        private NodeCommEventGenerator _commEventGenerator = new NodeCommEventGenerator();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public EventFacade()
        {
            this.AddDisposable(_eventPeristence);
            this.AddDisposable(_commEventGenerator);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取系统事件管理接口。
        /// </summary>
        public ISystemEventManage SEM { get { return _sysEventMgr; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// 打开
        /// </summary>
        public void Open()
        {
        }
        #endregion

    }
}
