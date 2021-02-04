using System;
using System.Collections.Generic;
using System.Linq;

using Products.Infrastructure;

namespace Products.UAC
{
    /// <summary>
    /// 用户信息。
    /// </summary>
    class UserInfo
    {
        #region "系统内置用户ID"
        /// <summary>
        /// 管理员ID。
        /// </summary>
        public const int AdministratorID = 1;
        /// <summary>
        /// Geust ID。
        /// </summary>
        public const int GuestID = 2;
        /// <summary>
        /// 无需登录节点（中央服务器、通信服务器、站机、各种接口机）的默认用户。
        /// </summary>
        public const int SystemID = 3;
        /// <summary>
        /// 自定义用户编号的起始值。
        /// </summary>
        public const int CustomUserIdMinValue = 100;
        #endregion

        #region "用户定义"
        /// <summary>
        /// Guest用户。
        /// </summary>
        public static readonly UserInfo Guest = new UserInfo()
        {
            Id = UserInfo.GuestID,
            Name = "Guest",
        };
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
        public List<SystemPrivilege> Privileges { get; set; } = new List<SystemPrivilege>();
        #endregion

        #region "Constructor"
        #endregion
    }
}
