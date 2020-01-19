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
using Acl.Data.Annotions;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 系统节点实体定义。
    /// </summary>
    [Acl.Data.Annotions.Table(Name = "ndm_SystemNodes")]
    public class SystemNode : Entity
    {
        #region "DB 字段"
        /// <summary>
        /// 名称。
        /// </summary>
        [Column]
        public string Name { get; set; }
        /// <summary>
        /// 类型。
        /// </summary>
        [Column]
        public NodeType Type { get; set; }

        /// <summary>
        /// 描述信息。
        /// </summary>
        [Column]
        public string Description { get; set; }

        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        /// <summary>
        /// 获取此实例的易读性信息。
        /// </summary>
        /// <returns>一个易读性信息。</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(64);

            sb.AppendFormat("编号={0}，名称={1}，类型= {2}, 描述 = {3}", this.Code, this.Name, this.Type, this.Description);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
