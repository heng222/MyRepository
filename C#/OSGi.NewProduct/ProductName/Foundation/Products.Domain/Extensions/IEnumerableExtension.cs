/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products
{
    /// <summary>
    /// IEnumerable 扩展。
    /// </summary>
    public static class IEnumerableExtension
    {
        /// <summary>
        /// IEnumerable.ForEach 扩展方法。
        /// </summary>
        public static void ForEach<T>(this IEnumerable<T> items, Action<T> action)
        {
            var it = items.GetEnumerator();
            while (it.MoveNext())
            {
                action(it.Current);
            }
        }

    }
}
