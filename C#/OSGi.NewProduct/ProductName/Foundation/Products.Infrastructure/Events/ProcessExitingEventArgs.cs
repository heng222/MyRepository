/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ACL
//
// 创 建 人：heng222_z
// 创建日期：2018/10/17 13:49:00 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ACL，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 一个事件参数类，当进程将要退出时使用。
    /// </summary>
    public class ProcessExitingEventArgs : EventArgs
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造一个进程正常退出时使用的对象。
        /// </summary>
        public ProcessExitingEventArgs()
        {
            this.IsNormal = true;
            this.InnerException = null;
        }

        /// <summary>
        /// 构造一个进程非正常退出时使用的对象。
        /// </summary>
        /// <param name="ex">非正常退出时的异常消息。</param>
        public ProcessExitingEventArgs(Exception ex)
        {
            this.IsNormal = false;
            this.InnerException = ex;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 是否是正常结束。
        /// </summary>
        public bool IsNormal { get; private set; }

        /// <summary>
        /// 内部异常
        /// </summary>
        public Exception InnerException { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
