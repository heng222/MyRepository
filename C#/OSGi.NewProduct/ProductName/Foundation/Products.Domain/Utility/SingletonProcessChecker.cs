/*----------------------------------------------------------------
// 公司名称：请输入公司名称
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

using System.Threading;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 单进程实例检查器
    /// </summary>
    public class SingletonProcessChecker : Acl.CompositeDisposable
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
            this.AddDisposable(_mutex);

            IsPassed = createdNew;
        }
    }
}
