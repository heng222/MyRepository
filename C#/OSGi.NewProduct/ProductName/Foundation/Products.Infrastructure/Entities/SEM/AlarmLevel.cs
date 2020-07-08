using System;

using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 报警级别实体定义。
    /// </summary>
    [Table(Name = "AlarmLevels")]
    public class AlarmLevel : Entity
    {
        #region "DB字段"
        /// <summary>
        /// 名称
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// 颜色
        /// </summary>
        [Column]
        public Int32 Color { get; set; }
        #endregion
    }
}
