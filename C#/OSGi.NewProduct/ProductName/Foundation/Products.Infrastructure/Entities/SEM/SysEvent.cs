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
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 系统事件实体定义。
    /// </summary>
    public class SysEvent : Entity
    {
        /// <summary>
        /// 编号。
        /// </summary>
        public EventType Code { get; set; }

        /// <summary>
        /// 事件名称
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 事件级别（一级、二级或三级)
        /// </summary>
        public EventLevel LevelCode { get; set; }

        /// <summary>
        /// 是否需要确认？
        /// </summary>
        public bool ConfirmEnabled { get; set; }

        /// <summary>
        /// 是否弹出确认对话框？
        /// </summary>
        public bool ConfirmDialogEnabled { get; set; }
    }
}
