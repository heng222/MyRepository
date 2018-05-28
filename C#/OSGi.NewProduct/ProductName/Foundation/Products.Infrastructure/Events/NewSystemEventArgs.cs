/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 14:29:10 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 一个事件参数类，当新的系统事件产生时使用。
    /// </summary>
    public class NewSystemEventArgs : EventArgs
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="value">表示系统事件对象。</param>
        public NewSystemEventArgs(EventLog value)
        {
            this.Value = value;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取/设置系统事件对象。
        /// </summary>
        public EventLog Value { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
