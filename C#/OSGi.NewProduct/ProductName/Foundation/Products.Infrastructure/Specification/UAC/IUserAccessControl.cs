﻿namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 用户访问控制接口
    /// </summary>
    public interface IUserAccessControl
    {
        /// <summary>
        /// 获取当前用户编号。
        /// </summary>
        uint CurrentUserCode { get; }

        /// <summary>
        /// 获取当前用户名称。
        /// </summary>
        string CurrentUserName { get; }

        /// <summary>
        /// 判断当前用户是否包含指定的权限。
        /// </summary>
        /// <param name="privilege">指定的权限。</param>
        /// <returns>true 表示拥有指定的权限，false 表示没有指定的权限。</returns>
        bool Contains(SystemPrivilege privilege);
    }
}
