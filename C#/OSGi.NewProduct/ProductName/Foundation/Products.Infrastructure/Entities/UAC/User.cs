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

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 用户实体定义
    /// </summary>
    public class User : Entity
    {
        /// <summary>
        /// 名称
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 密码
        /// </summary>
        public byte[] Password { get; set; }

        /// <summary>
        /// 权限。
        /// </summary>
        public byte[] Privileges { get; set; }
    }
}
