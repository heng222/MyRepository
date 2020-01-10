/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Products.Persistence
{
    /// <summary>
    /// 数据库类型定义。
    /// </summary>
    public enum DataBaseType
    {
        /// <summary>
        /// 未知类型
        /// </summary>
        None = 0,

        /// <summary>
        /// Oracle
        /// </summary>
        Oracle = 1,
        /// <summary>
        /// SqlServer
        /// </summary>
        SqlServer = 2,
        /// <summary>
        /// MySql
        /// </summary>
        MySql = 4,
        
        /// <summary>
        /// 
        /// </summary>
        Sqlite = 20,
        /// <summary>
        /// 
        /// </summary>
        Access = 22,

        /// <summary>
        /// 
        /// </summary>
        Excel = 30,
        /// <summary>
        /// 
        /// </summary>
        Text = 32,
    }
}
