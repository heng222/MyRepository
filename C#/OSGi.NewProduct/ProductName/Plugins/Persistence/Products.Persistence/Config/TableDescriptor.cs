﻿/*----------------------------------------------------------------
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

namespace Products.Persistence
{
    /// <summary>
    /// 数据库表描述类
    /// </summary>
    class TableDescriptor
    {
        /// <summary>
        /// 表的名称，例如 “AlarmLogs”。
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 表的类型，例如 TableType.StaticConfig。
        /// </summary>
        public TableType Type { get; set; }

        /// <summary>
        /// 表关联的实体类类型，例如“Products.Entities.AlarmLog”。
        /// </summary>
        public Type EntityType { get; set; }
    }
}