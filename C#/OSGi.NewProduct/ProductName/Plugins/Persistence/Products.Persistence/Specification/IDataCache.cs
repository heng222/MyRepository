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

namespace Products.Persistence.Specification
{
    /// <summary>
    /// 数据缓存接口。
    /// </summary>
    interface IDataCache
    {
        /// <summary>
        /// 获取实体对象。
        /// </summary>
        /// <param name="condition">指定的条件。</param>
        /// <param name="entityType">实体类型。</param>
        /// <returns></returns>
        object GetValue(Dictionary<string, object> condition, Type entityType);
    }
}
