﻿/*----------------------------------------------------------------
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

namespace Products.Persistence
{
    /// <summary>
    /// 表的种类。
    /// </summary>
    enum TableKind
    {
        /// <summary>
        /// 未知
        /// </summary>
        None = 0,

        /// <summary>
        /// 静态配置表。
        /// </summary>
        StaticConfig = 1,

        /// <summary>
        /// 动态配置表。
        /// </summary>
        DynamicConfig = 2,

        /// <summary>
        /// 日志表。
        /// </summary>
        Log = 3,
    }
}
