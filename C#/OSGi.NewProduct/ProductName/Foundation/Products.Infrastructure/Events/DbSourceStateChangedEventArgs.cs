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

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 数据源状态改变事件参数类。
    /// </summary>
    public class DbSourceStateChangedEventArgs : EventArgs
    {
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="dataSrcName">数据源名称。</param>
        /// <param name="connected">是否连接？</param>
        public DbSourceStateChangedEventArgs(string dataSrcName, bool connected)
        {
            this.Connected = connected;
            this.DataSourceName = dataSrcName;
        }

        /// <summary>
        /// 数据源是否连接？
        /// </summary>
        public bool Connected { get; private set; }

        /// <summary>
        /// 获取数据源名称。
        /// </summary>
        public string DataSourceName { get; private set; }
    }
}
