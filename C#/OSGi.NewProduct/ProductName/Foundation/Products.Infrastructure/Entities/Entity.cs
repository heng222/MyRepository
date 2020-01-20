/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
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
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 实体基类
    /// </summary>
    [Serializable]
    public abstract class Entity
    {
        /// <summary>
        /// 无效编号。
        /// </summary>
        public const uint InvalidCode = uint.MinValue;

        /// <summary>
        /// 编号，从1开始，0表示无效编号。
        /// </summary>
        [Column]
        public uint Code { get; set; }

        /// <summary>
        /// 默认构造函数。
        /// </summary>
        protected Entity()
        {
        }
    }
}
