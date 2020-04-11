/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.ComponentModel.Annotions;
using Acl.Data.Annotions;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 系统事件日志实体定义。
    /// </summary>
    [Table(Name = "SysEventLogs")]
    public class SysEventLog : LogEntity
    {
        /// <summary>
        /// 事件类型
        /// </summary>
        [Column]
        public EventType TypeCode { get; set; }

        /// <summary>
        /// 事件级别
        /// </summary>
        [Column]
        public EventLevel Level { get; set; }

        /// <summary>
        /// 事件描述
        /// </summary>
        [Column]
        public string Description { get; set; }

        /// <summary>
        /// 确认时间
        /// </summary>
        [Column]
        public DateTime ConfirmTime { get; set; }

        /// <summary>
        /// 获取一个值，用于表示本事件是否已经确认？
        /// </summary>
        [Ignore]
        public bool IsConfirmed { get { return this.ConfirmTime != DateTime.MinValue; } }
        
        /// <summary>
        /// 构造函数。
        /// </summary>
        public SysEventLog()
        {
            this.Timestamp = DateTime.Now;
            this.Description = string.Empty;
        }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public SysEventLog(EventType type, EventLevel level, string description)
        {
            this.Timestamp = DateTime.Now;
            this.TypeCode = type;
            this.Level = level;
            this.Description = description;
        }
    }
}
