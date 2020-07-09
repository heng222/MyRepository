using System;

namespace Products.LogReport.Data
{
    /// <summary>
    /// 事件记录数据
    /// </summary>
    class SysEventLogInfo
    {
        /// <summary>
        /// 事件发生时间
        /// </summary>
        public DateTime Timestamp { get; set; }

        /// <summary>
        /// 事件类型名称。
        /// </summary>
        public string EventTypeName { get; set; }

        /// <summary>
        /// 级别
        /// </summary>
        public string Level { get; set; }

        /// <summary>
        /// 描述信息
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// 报文产生时间
        /// </summary>
        public string ConfirmTime { get; set; }

    }
}
