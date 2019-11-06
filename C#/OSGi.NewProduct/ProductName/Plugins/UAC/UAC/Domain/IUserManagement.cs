/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// 用户管理接口。
    /// </summary>
    interface IUserManagement
    {
        /// <summary>
        /// 根据用户名查询用户记录。
        /// </summary>
        User GetUser(string name);

        /// <summary>
        /// 修改密码。
        /// </summary>
        void ModifyPassword(string userName, string oldPassword, string newPassword);
    }
}
