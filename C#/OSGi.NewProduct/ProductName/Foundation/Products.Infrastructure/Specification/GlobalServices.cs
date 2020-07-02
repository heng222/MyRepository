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
        public static ISystemProperty SysAttribute
        {
            get { return ServiceManager.Current.Get<ISystemProperty>(); }
        }

        /// <summary>
        /// 获取/设置DBConfig提供器接口。
        /// </summary>
        public static IDbConfigurationProvider DbConfigProvider
        {
            get { return ServiceManager.Current.Get<IDbConfigurationProvider>(); }
        }

        /// <summary>
        /// 获取 IRepository 接口。
        /// </summary>
        public static IRepository Repository
        {
            get { return ServiceManager.Current.Get<IRepository>(); }
        }

        /// <summary>
        /// 获取/设置节点上下文接口。
        /// </summary>
        public static INodeContext NodeContext { get; set; }

        /// <summary>
        /// 获取 UAC 接口。
        /// </summary>
        public static IUserAccessControl UAC
        {
            get { return ServiceManager.Current.Get<IUserAccessControl>(); }
        }

        /// <summary>
        /// 获取 系统事件管理 接口
        /// </summary>
        public static ISystemEventManage SEM
        {
            get { return ServiceManager.Current.Get<ISystemEventManage>(); }
        }
    }
}
