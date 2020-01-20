/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
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
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="value">表示系统事件对象。</param>
        public NewSystemEventArgs(SysEventLog value)
        {
            this.Value = value;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取/设置系统事件对象。
        /// </summary>
        public SysEventLog Value { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
