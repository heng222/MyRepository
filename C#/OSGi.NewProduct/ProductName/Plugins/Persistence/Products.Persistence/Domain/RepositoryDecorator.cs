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
using System.Linq.Expressions;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Domain
{
    abstract class RepositoryDecorator : Acl.CompositeDisposable, IRepository
    {
        protected RepositoryDecorator(IRepository repository)
        {
            this.Repository = repository;
        }

        protected IRepository Repository { get; private set; }

        #region IRepository 成员

        public virtual IList<T> Where<T>(System.Linq.Expressions.Expression<Func<T, bool>> predicate = null) where T : Infrastructure.Entities.Entity
        {
            return this.Repository.Where<T>(predicate);
        }

        public virtual void Insert<T>(params T[] entities) where T : Infrastructure.Entities.Entity
        {
            this.Repository.Insert<T>(entities);
        }

        public virtual void Delete<T>(Expression<Func<T, bool>> condition = null) where T : Infrastructure.Entities.Entity
        {
            this.Repository.Delete<T>(condition);
        }

        public virtual void Update<T>(object instance, System.Linq.Expressions.Expression<Func<T, bool>> condition) where T : Infrastructure.Entities.Entity
        {
            this.Repository.Update<T>(instance, condition);
        }
        
        public virtual void Execute<T>(Action<Acl.Data.IDatabase> handler) where T : Entity
        {
            this.Repository.Execute<T>(handler);
        }

        public virtual void AsyncExecute<T>(Action<Acl.Data.IDatabase> handler, Action<Exception> errorHandler)  where T : Entity
        {
            this.Repository.AsyncExecute<T>(handler, errorHandler);
        }

        public virtual void AsyncInsert<T>(T[] data, Action<Exception> exceptionHandler) where T : Infrastructure.Entities.Entity
        {
            this.Repository.AsyncInsert<T>(data, exceptionHandler);
        }
        #endregion
    }
}
