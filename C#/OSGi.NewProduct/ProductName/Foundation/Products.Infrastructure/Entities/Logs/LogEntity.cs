using System;

using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 日志实体基类定义。
    /// </summary>
    public abstract class LogEntity : Entity
    {
        /// <summary>
        /// 日志产生的时间。
        /// </summary>
        [Column]
        public DateTime Timestamp { get; set; } = DateTime.Now;
    }
}
