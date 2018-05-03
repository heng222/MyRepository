/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：wqs_486
// 创建日期：2013-7-3 16:51:49 
// 邮    箱：wqs_486@163.com
//
// Copyright (C) 2013 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Collections.Specialized;
using System.Reflection;
using System.Threading;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 单进程实例检查器
    /// </summary>
    public class SingletonProcessChecker : IDisposable
    {
        /// <summary>
        /// 互斥体
        /// </summary>
        private Mutex _mutex;
        /// <summary>
        /// 得到一个值用来指示是否通过检查
        /// </summary>
        public bool IsPassed { get; private set; }

        /// <summary>
        /// 构造单进程实例检查器
        /// </summary>
        /// <param name="symbolicName"></param>
        public SingletonProcessChecker(string symbolicName)
        {
            bool createdNew;
            _mutex = new Mutex(true, symbolicName, out createdNew);

            IsPassed = createdNew;
        }

        /// <summary>
        /// 释放资源
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (_mutex != null)
            {
                _mutex.Close();
                _mutex = null;
            }
        }
    }
}
