/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 13:13:43 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System.Linq;

using Acl.ComponentModel.Annotions;
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 用户实体定义
    /// </summary>
    [Table(Name = "Users")]
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
        //[Column(Name = "Privileges", Storage = "_privilegesInner")]
        [Ignore]
        public SystemPrivilege[] Privileges
        {
            get
            {
                if (_privileges == null) _privileges = _privilegesInner.Select(p => (SystemPrivilege)p).ToArray();
                return _privileges;
            }

            set
            {
                _privileges = value;
                _privilegesInner = value.Select(p => (byte)p).ToArray();
            }
        }
        private SystemPrivilege[] _privileges;
    }
}
