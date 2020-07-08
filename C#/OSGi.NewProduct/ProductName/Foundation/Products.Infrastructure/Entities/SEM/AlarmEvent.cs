using System;

using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 事件类型实体定义。
    /// </summary>
    [Table(Name = "AlarmEvents")]
    public class AlarmEvent : Entity
    {
        #region "DB字段"
        /// <summary>
        /// 名称。
        /// 例如：“信号不能开放”、“自动加载运行图失败”等。
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// 报警级别（A级/一级、B级/二级、C级/三级）
        /// </summary>
        [Column]
        public int LevelCode { get; set; }

        /// <summary>
        /// 报警种类（系统报警、设备报警、一般报警）
        /// </summary>
        [Column]
        public UInt32 CategoryCode { get; set; }

        /// <summary>
        /// 是否弹出确认对话框？
        /// </summary>
        [Column]
        public bool NeedPopupDialog { get; set; }

        /// <summary>
        /// 是否需要确认操作？
        /// </summary>
        [Column]
        public bool NeedConfirm { get; set; }

        /// <summary>
        /// 是否启用语音报警？
        /// </summary>
        [Column]
        public bool VoiceEnabled { get; set; }
        #endregion
    }
}
