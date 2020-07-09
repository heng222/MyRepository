/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq.Expressions;

using Acl;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services.Repositories
{
    abstract class Repository : CompositeDisposable, IRepository
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="dataSource">����Դ��������</param>
        protected Repository(DataSource dataSource)
        {
            this.DataSource = dataSource;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��ǰ�ִ�����������Դ��������
        /// </summary>
        public DataSource DataSource { get; private set; }

        /// <summary>
        /// ��ȡһ��ֵ�����ڱ�ʾ��ǰ�ִ�������״̬��TODO��ʵ�ִ˹��ܡ�
        /// </summary>
        public bool Connected { get; private set; }
        #endregion

        #region "Abstract / Override methods"
        /// <summary>
        /// ������������дʱ�����ڴ򿪲ִ���
        /// </summary>
        protected abstract void OnOpen();

        #endregion

        #region "Virtual methods"
        #endregion

        #region "Override methods"
        /// <inheritdoc/>
        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);

            this.SetConnectionState(false);
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Protected methods"
        protected void SetConnectionState(bool connected)
        {
            // TODO������״̬�����仯��֪ͨ�¼���
            this.Connected = connected;
        }
        #endregion

        #region "Public methods"
        public void Open()
        {
            this.OnOpen();
        }
        #endregion

        #region IRepository ��Ա

        public abstract uint NextSequence<T>() where T : Entity;

        public abstract IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        public abstract IList<T> Where<T>(string sql, object namedParameters = null);

        public abstract void Insert<T>(params T[] entities) where T : Entity;

        public abstract void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null) where T : Entity;

        public abstract void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity;

        public abstract void Delete<T>(Expression<Func<T, bool>> predicate = null) where T : Entity;

        public abstract void Execute<T>(Action<Acl.Data.IDbContext> handler) where T : Entity;

        public abstract void AsyncExecute<T>(Action<Acl.Data.IDbContext> handler, Action<Exception> errorHandler) where T : Entity;

        #endregion
    }
}
