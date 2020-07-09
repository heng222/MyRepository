/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Threading.Tasks;

using Acl.Log;

namespace Products
{
    /// <summary>
    /// TaskFactory 扩展。
    /// </summary>
    public static class TaskFactoryExtension
    {
        /// <summary>
        /// StartNewWithCatch 扩展方法。
        /// </summary>
        public static void StartNewWithCatch(this TaskFactory factory, Action action, ILog log)
        {
            factory.StartNew(() =>
            {
                try
                {
                    action();
                }
                catch (System.Exception ex)
                {
                    log.Error(ex);
                }
            });
        }

    }
}
