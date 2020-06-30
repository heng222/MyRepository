/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：zhangheng
// 创建日期：2013-8-16 13:50:34 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Acl.Log;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// 日志配置信息
    /// </summary>
    public static class LogSettings
    {
        #region "Field"
        private static LogLevel _level = LogLevel.Information;
        private static ushort _expiredDays = 30;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 静态构造函数
        /// </summary>
        static LogSettings()
        {
            CommLogBasePath = string.Format(@"{0}CommLog\", AppDomain.CurrentDomain.BaseDirectory);
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// 获取/设置日志的保存级别
        /// </summary>
        static public LogLevel Level
        {
            get { return _level; }
            set { _level = value; }
        }

        /// <summary>
        /// 获取/设置日志的保存天数
        /// </summary>
        static public ushort ExpiredDays
        {
            get { return _expiredDays; }
            set { _expiredDays = value; }
        }

        /// <summary>
        /// 获取通讯日志的基础路径
        /// </summary>
        static public string CommLogBasePath { get; private set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
