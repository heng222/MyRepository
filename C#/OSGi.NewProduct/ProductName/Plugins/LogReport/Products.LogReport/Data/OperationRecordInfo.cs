using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.LogReport.Data
{
    /// <summary>
    /// 操作日志数据
    /// </summary>
    class OperationRecordInfo
    {
        /// <summary>
        /// 操作时间
        /// </summary>
        public string Timestamp { get; set; }
        /// <summary>
        /// 操作类型
        /// </summary>
        public string OperationType { get; set; }
        /// <summary>
        /// 是否人工操作？
        /// </summary>
        public string IsManual { get; set; }
        /// <summary>
        /// 目标设备编号
        /// </summary>
        public string TargetDeviceCode { get; set; }
        /// <summary>
        /// 操作描述
        /// </summary>
        public string OperationDescription { get; set; }

        /// <summary>
        /// 回应时间
        /// </summary>
        public DateTime ResultTime { get; set; }
        /// <summary>
        /// 执行结果
        /// </summary>
        public string ResultType { get; set; }
        /// <summary>
        /// 回应描述
        /// </summary>
        public string ResultDescription { get; set; }
    }
}
