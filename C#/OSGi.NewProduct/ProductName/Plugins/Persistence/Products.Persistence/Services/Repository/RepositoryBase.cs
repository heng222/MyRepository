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
using System.Linq.Expressions;

using Acl;
using Acl.Data;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services.Repository
{
    abstract class RepositoryBase : CompositeDisposable, IRepository
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="dataSource">数据源描述符。</param>
        protected RepositoryBase(DataSource dataSource)
        {
            this.DataSource = dataSource;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取当前仓储关联的数据源描述符。
        /// </summary>
        public DataSource DataSource { get; private set; }

        /// <summary>
        /// 获取一个值，用于表示当前仓储的连接状态。
        /// </summary>
        public bool Connected { get; private set; }
        #endregion

        #region "Abstract / Override methods"
        /// <summary>
        /// 在派生类中重写时，用于打开仓储。
        /// </summary>
        protected abstract void OnOpen();

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        public void Open()
        {
            this.OnOpen();
        }
        #endregion

        #region IRepository 成员

        public abstract uint NextSequence<T>() where T : Entity;

        public abstract IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        public abstract IList<T> Where<T>(string sql, object namedParameters = null);

        public abstract void Insert<T>(params T[] entities) where T : Entity;

        public abstract void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null) where T : Entity;

        public abstract void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity;

        public abstract void Delete<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        public abstract void Execute<T>(Action<Acl.Data.IDatabase> handler) where T : Entity;

        public abstract void AsyncExecute<T>(Action<Acl.Data.IDatabase> handler, Action<Exception> errorHandler) where T : Entity;

        #endregion
    }
}
