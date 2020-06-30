/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Domain;
using Products.Infrastructure;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.UAC.Utilities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// 用户管理接口实现。
    /// </summary>
    class UserManagementImpl : IUserManagement
    {
        #region "Field"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

        #region "IUserManagement 接口"
        public User GetUser(string name)
        {
            return GlobalServices.Repository.Where<User>()
                .Where(p => string.Equals(p.Name, name, StringComparison.OrdinalIgnoreCase))
                .FirstOrDefault();
        }

        public void ModifyPassword(string userName, string oldPassword, string newPassword)
        {
            if (string.IsNullOrWhiteSpace(userName)) throw new Exception("用户名非法。");

            // 新密码是否合法？

            // 旧密码是否正确？
            var theUser = this.GetUser(userName);
            if (theUser == null) throw new Exception("用户不存在。");

            var oldPwdMd5 = HelperTool.BuildMd5(oldPassword);
            if (!HelperTool.BytesEquals(oldPwdMd5, theUser.Password))
            {
                throw new Exception("旧密码不正确。");
            }

            // 更新密码。
            var newPwdMd5 = HelperTool.BuildMd5(newPassword);
            GlobalServices.Repository.Update<User>(new { Password = newPwdMd5 }, p => p.Code == theUser.Code);
        }
        #endregion
    }
}
