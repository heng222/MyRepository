﻿
using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using Acl.Data;
using Products.Infrastructure.Entities;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 数据仓储接口。
    /// </summary>
    public interface IRepository
    {
        #region "Query"
        /// <summary>
        /// 查询数据。
        /// </summary>
        /// <param name="predicate"></param>
        /// <returns></returns>
        IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        #endregion


        #region "Insert"
        /// <summary>
        /// 插入数据。
        /// </summary>
        /// <param name="entities"></param>
        void Insert<T>(params T[] entities) where T : Entity;

        /// <summary>
        /// 异步插入数据
        /// </summary>
        /// <param name="entities"></param>
        /// <param name="exceptionHandler">异常处理函数。</param>
        void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null) where T : Entity;
        #endregion


        #region "Update"
        /// <summary>
        /// 更新，如果远程数据库断开连接，则禁止执行更新操作
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="instance"></param>
        /// <param name="predicate"></param>
        void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity;
        #endregion


        #region "Delete"
        /// <summary>
        /// 删除数据。
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="predicate">为null时表示删除表中的所有数据。</param>
        void Delete<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;
        #endregion


        #region "Custom operations"
        /// <summary>
        /// 执行一个方法。
        /// </summary>
        /// <param name="handler"></param>
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1004:GenericMethodsShouldProvideTypeParameter")]
        void Execute<T>(Action<IDatabase> handler) where T : Entity;

        /// <summary>
        /// 异步执行一个方法。
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="errorHandler"></param>
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1004:GenericMethodsShouldProvideTypeParameter")]
        void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler) where T : Entity;
        #endregion
    }
}
