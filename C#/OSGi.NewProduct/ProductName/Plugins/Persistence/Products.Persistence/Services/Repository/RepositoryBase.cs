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
using System.Linq.Expressions;
using System.Text;

using Acl;
using Acl.Data;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services.Repository
{
    abstract class RepositoryBase : CompositeDisposable, IRepository
    {
        #region "Field"
        private TableSeqNoManager _sequenceGenerator = new TableSeqNoManager();
        #endregion

        #region "Constructor"
        protected RepositoryBase()
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Abstract / Override methods"
        protected abstract void OnOpen();

        protected virtual IDatabase GetDatabase<TEntity>() where TEntity : Entity
        {
            return null;
        }
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

        public virtual UInt32 NextSequence<T>() where T : Entity
        {
            var connection = this.GetDatabase<T>();

            return (connection != null) ? _sequenceGenerator.Next<T>(connection) : 0;
        }

        abstract public IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        abstract public IList<T> Where<T>(string sql, object namedParameters = null);

        abstract public void Insert<T>(params T[] entities) where T : Entity;

        abstract public void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null) where T : Entity;

        abstract public void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity;

        abstract public void Delete<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        abstract public void Execute<T>(Action<Acl.Data.IDatabase> handler) where T : Entity;

        abstract public void AsyncExecute<T>(Action<Acl.Data.IDatabase> handler, Action<Exception> errorHandler) where T : Entity;

        #endregion
    }
}
