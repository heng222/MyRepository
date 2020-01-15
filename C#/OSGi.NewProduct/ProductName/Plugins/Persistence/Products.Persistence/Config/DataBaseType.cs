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
    enum DataBaseType
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
        SqlServer = 4,
        /// <summary>
        /// MySql
        /// </summary>
        MySql = 6,
        
        /// <summary>
        /// Sqlite
        /// </summary>
        Sqlite = 20,
        /// <summary>
        /// Access
        /// </summary>
        Access = 24,

        /// <summary>
        /// Excel
        /// </summary>
        Excel = 30,

        /// <summary>
        /// CSV
        /// </summary>
        CSV = 32,
    }
}
