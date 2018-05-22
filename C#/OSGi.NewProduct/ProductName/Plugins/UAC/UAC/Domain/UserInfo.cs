using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure;

namespace Products.UAC
{
    /// <summary>
    /// 用户信息。
    /// </summary>
    class UserInfo
    {
        #region "系统内置用户"
        /// <summary>
        /// 管理员。
        /// </summary>
        public const int Administrator = 1;
        /// <summary>
        /// 表示Geust用户。
        /// </summary>
        public const int Guest = 2;
        /// <summary>
        /// 无需登录节点（中央服务器、通信服务器、站机、各种接口机）的默认用户。
        /// </summary>
        public const int System = 3;
        /// <summary>
        /// 自定义用户编号的起始值。
        /// </summary>
        public const int CustomUserCodeMinValue = 100;
        #endregion
        
        #region "Properties"
        /// <summary>
        /// 用户编号。
        /// </summary>
        public UInt32 Id { get; set; }
        /// <summary>
        /// 用户姓名。
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 用户拥有的权限。
        /// </summary>
        public List<SystemPrivilege> Privileges { get; set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public UserInfo()
        {
            this.Id = UserInfo.Guest;
            this.Name = "Guest";
            this.Privileges = new List<SystemPrivilege>() { SystemPrivilege.None };
        }
        #endregion
    }
}
