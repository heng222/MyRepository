/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2020/1/20 13:50:46 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2020 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

using Acl.Data;
using Acl.Data.Configuration;

namespace Products.Persistence.Services.Repository
{
    class RepositoryRemote : RepositoryBase
    {
        #region "Field"
        private TableSeqNoManager _seqNoManager = new TableSeqNoManager();
        #endregion

        #region "Constructor"
        public RepositoryRemote(DataSource dataSrc)
            : base(dataSrc)
        {
        }
        #endregion

        #region "Properties"

        protected DbConfiguration DbConfig { get; private set; }
        #endregion

        #region "Override methods"

        protected override void OnOpen()
        {
            this.DbConfig = PersistenceConfig.GetOrCreateDbConfiguration(this.DataSource.Name, false);
        }

        protected override void Dispose(bool disposing)
        {
            if (this.DbConfig != null)
            {
                this.DbConfig.Close();
                this.DbConfig = null;
            }

            base.Dispose(disposing);
        }

        public override IList<T> Where<T>(Expression<Func<T, bool>> predicate = null)
        {
            using (var db = this.DbConfig.Open())
            {
                return db.Query(predicate);
            }
        }

        public override uint NextSequence<T>()
        {
            if (_seqNoManager.Contains(typeof(T)))
            {
                return _seqNoManager.Next<T>();
            }
            else
            {
                using (var db = this.DbConfig.Open())
                {
                    return _seqNoManager.Next<T>(db);
                }
            }
        }

        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            throw new NotImplementedException();
        }

        public override void Insert<T>(params T[] entities)
        {
            throw new NotImplementedException();
        }

        public override void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null)
        {
            throw new NotImplementedException();
        }

        public override void Update<T>(object instance, Expression<Func<T, bool>> predicate)
        {
            throw new NotImplementedException();
        }

        public override void Delete<T>(Expression<Func<T, bool>> predicate = null)
        {
            throw new NotImplementedException();
        }

        public override void Execute<T>(Action<Acl.Data.IDatabase> handler)
        {
            throw new NotImplementedException();
        }

        public override void AsyncExecute<T>(Action<Acl.Data.IDatabase> handler, Action<Exception> errorHandler)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion
    }
}
