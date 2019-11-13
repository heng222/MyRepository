/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
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
    /// 操作记录实体定义。
    /// </summary>
    public class OperationLog : LogEntity
    {
        /// <summary>
        /// 操作类型
        /// </summary>
        public OperationType OperationType { get; set; }

        /// <summary>
        /// 是否为人工操作？
        /// true表示人工（手动）操作，false表示系统（自动）操作。
        /// </summary>
        public bool IsManual { get; set; }

        /// <summary>
        /// 目标设备编号
        /// </summary>
        public uint TargetDeviceCode { get; set; }

        /// <summary>
        /// 操作描述
        /// </summary>
        public string OperationDescription { get; set; }

        /// <summary>
        /// 操作结果
        /// </summary>
        public OperationResult ResultType { get; set; }

        /// <summary>
        /// 结果响应时间
        /// </summary>
        public DateTime ResultTimestamp { get; set; }

        /// <summary>
        /// 结果描述
        /// </summary>
        public string ResultDescription { get; set; }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public OperationLog()
        {
            this.Timestamp = DateTime.Now;
        }
    }
}
