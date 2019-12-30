using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.LogReport.Data
{
    /// <summary>
    /// 事件记录数据
    /// </summary>
    class SysEventLogInfo
    {
        /// <summary>
        /// 应答器编号
        /// </summary>
        public int EventCode { get; set; }

        /// <summary>
        /// 事件类型名称。
        /// </summary>
        public string EventTypeName { get; set; }

        /// <summary>
        /// 事件类型编号
        /// </summary>
        public string EventTypeCode { get; set; }

        /// <summary>
        /// 事件发生时间
        /// </summary>
        public DateTime Timestamp { get; set; }

        /// <summary>
        /// 报文产生时间
        /// </summary>
        public DateTime ConfirmTime { get; set; }

        /// <summary>
        /// 级别
        /// </summary>
        public int Level { get; set; }

        /// <summary>
        /// 时间描述信息
        /// </summary>
        public string Description { get; set; }

    }
}
