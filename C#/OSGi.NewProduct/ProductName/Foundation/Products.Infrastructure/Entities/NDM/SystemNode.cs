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
    /// 系统节点实体定义。
    /// </summary>
    public class SystemNode : Entity
    {
        #region "DB 字段"
        /// <summary>
        /// 编号。
        /// </summary>
        public ushort Code { get; set; }
        /// <summary>
        /// 名称。
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// 类型。
        /// </summary>
        public NodeType Type { get; set; }


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

            sb.AppendFormat("编号={0}，名称={1}，", this.Code, this.Name);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
