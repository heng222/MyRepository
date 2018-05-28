/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 13:57:44 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 系统事件
    /// </summary>
    public class EventLog
    {
        /// <summary>
        /// 事件发生的时间
        /// </summary>
        public DateTime Timestamp { get; set; }

        /// <summary>
        /// 事件类型
        /// </summary>
        public EventType TypeCode { get; set; }

        /// <summary>
        /// 事件级别
        /// </summary>
        public EventLevel Level { get; set; }

        /// <summary>
        /// 描述
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public EventLog()
        {
            this.Timestamp = DateTime.Now;
            this.Description = string.Empty;
        }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public EventLog(EventType type, EventLevel level, string description)
        {
            this.Timestamp = DateTime.Now;
            this.TypeCode = type;
            this.Level = level;
            this.Description = description;
        }
    }
}
