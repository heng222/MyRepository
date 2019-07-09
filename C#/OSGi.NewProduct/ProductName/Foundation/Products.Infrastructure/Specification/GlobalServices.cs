/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/22 14:49:57 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.ServiceManagement;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 全局服务。
    /// </summary>
    public static class GlobalServices
    {
        /// <summary>
        /// 获取系统属性接口。
        /// </summary>
        public static ISystemAttribute SysAttribute
        {
            get { return ServiceManager.Current.GetAll<ISystemAttribute>().FirstOrDefault(); }
        }

        /// <summary>
        /// 获取 UAC 接口。
        /// </summary>
        public static IUserAccessControl UAC 
        {
            get { return ServiceManager.Current.GetAll<IUserAccessControl>().FirstOrDefault(); }
        }

        /// <summary>
        /// 获取 IRepository 接口。
        /// </summary>
        public static IRepository Repository
        {
            get { return ServiceManager.Current.GetAll<IRepository>().FirstOrDefault(); }
        }
    }
}
