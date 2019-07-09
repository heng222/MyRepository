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
    /// 表类型
    /// </summary>
    enum TableType
    {
        /// <summary>
        /// 静态配置表。
        /// </summary>
        StaticConfig,

        /// <summary>
        /// 动态配置表。
        /// </summary>
        DynamicConfig,

        /// <summary>
        /// 日志表。
        /// </summary>
        NormalLog,
    }
}
