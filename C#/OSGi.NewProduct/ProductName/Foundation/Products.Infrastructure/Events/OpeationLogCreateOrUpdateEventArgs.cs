/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2014-9-9 9:59:01 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 一个事件参数类，当操作记录产生或更新时使用。
    /// </summary>
    public class OpeationLogCreateOrUpdateEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="value">表示一个操作记录对象。</param>
        public OpeationLogCreateOrUpdateEventArgs(OperationLog value)
        {
            this.Value = value;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取/设置操作记录对象。
        /// </summary>
        public OperationLog Value { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
