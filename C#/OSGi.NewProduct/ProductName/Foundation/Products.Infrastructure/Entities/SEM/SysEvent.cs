/*----------------------------------------------------------------
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
using System.Text;
using Acl.Data.Annotions;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 系统事件实体定义。
    /// </summary>
    [Acl.Data.Annotions.Table(Name = "system_Events")]
    public class SysEvent : Entity
    {
        /// <summary>
        /// 事件类型。
        /// </summary>
        [Acl.ComponentModel.Annotions.Ignore]
        public EventType Type 
        {
            get { return (EventType)base.Code; }

            set { base.Code = Convert.ToUInt32(value); }
        }

        /// <summary>
        /// 事件名称
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// 事件级别（一级、二级或三级)
        /// </summary>
        [Column]
        public EventLevel LevelCode { get; set; }

        /// <summary>
        /// 是否需要确认？
        /// </summary>
        [Column]
        public bool ConfirmEnabled { get; set; }

        /// <summary>
        /// 是否弹出确认对话框？
        /// </summary>
        [Column]
        public bool ConfirmDialogEnabled { get; set; }

        /// <summary>
        /// 是否启用语音报警？
        /// </summary>
        [Column]
        public bool VoiceEnabled { get; set; }
    }
}
