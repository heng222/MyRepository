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
using Acl.ComponentModel.Annotions;
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 用户实体定义
    /// </summary>
    [Table]
    public class User : Entity
    {
        /// <summary>
        /// 名称
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// 密码
        /// </summary>
        [Column]
        public byte[] Password { get; set; }

        /// <summary>
        /// 权限。
        /// </summary>
        [Column(Name = "Privileges")]
        private byte[] _privilegesInner;
        /// <summary>
        /// 获取用户权限。
        /// </summary>
        [Ignore]
        //[Column(Name = "Privileges", Storage = "_privilegesInner")]
        public SystemPrivilege[] Privileges
        {
            get { return _privilegesInner.Select(p => (SystemPrivilege)p).ToArray(); }
            set { _privilegesInner = value.Select(p => (byte)p).ToArray(); }
        }
    }
}
