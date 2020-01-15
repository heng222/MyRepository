/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using Acl;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services.Repository
{
    abstract class RepositoryImpl : CompositeDisposable, IRepository
    {
        #region "Field"
        #endregion

        #region "Constructor"
        protected RepositoryImpl()
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Abstract / Override methods"
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

        #region IRepository ��Ա

        abstract public uint NextSequence<T>() where T : Entity;

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
