/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：2013-8-16 15:11:00 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// 日志级别管理器
    /// </summary>
    public static class LogLevelManager
    {
        #region "Filed"
        private static readonly string[] _logLevelNames = { "调试", "提示", "警告", "错误", "致命" };
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取日志名称
        /// </summary>
        public static string[] LogLevelNames
        {
            get { return _logLevelNames; }
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
