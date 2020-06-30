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

using Acl.Data;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services
{
    abstract class RepositoryDecorator : Acl.CompositeDisposable, IRepository
    {
        protected RepositoryDecorator(IRepository repository)
        {
            this.Repository = repository;
        }

        protected IRepository Repository { get; private set; }

        #region IRepository 成员

        public uint NextSequence<T>() where T : Entity
        {
            return this.Repository.NextSequence<T>();
        }

        public virtual IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity
        {
            return this.Repository.Where<T>(predicate);
        }

        public IList<T> Where<T>(string sql, object namedParameters = null)
        {
            return this.Repository.Where<T>(sql, namedParameters);
        }

        public virtual void Insert<T>(params T[] entities) where T : Entity
        {
            this.Repository.Insert<T>(entities);
        }

        public virtual void Delete<T>(Expression<Func<T, bool>> condition = null) where T : Entity
        {
            this.Repository.Delete<T>(condition);
        }

        public virtual void Update<T>(object instance, Expression<Func<T, bool>> condition) where T : Entity
        {
            this.Repository.Update<T>(instance, condition);
        }

        public virtual void Execute<T>(Action<IDatabase> handler) where T : Entity
        {
            this.Repository.Execute<T>(handler);
        }

        public virtual void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler) where T : Entity
        {
            this.Repository.AsyncExecute<T>(handler, errorHandler);
        }

        public virtual void AsyncInsert<T>(T[] data, Action<Exception> exceptionHandler) where T : Entity
        {
            this.Repository.AsyncInsert<T>(data, exceptionHandler);
        }
        #endregion
    }
}
