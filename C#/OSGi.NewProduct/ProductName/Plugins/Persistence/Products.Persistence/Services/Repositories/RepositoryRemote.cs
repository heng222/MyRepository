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

using Acl.Data;
using Acl.Data.Configuration;
using Acl.Data.Event;
using Acl.Threading.ActiveObject;

namespace Products.Persistence.Services.Repositories
{
    class RepositoryRemote : Repository
    {
        #region "Field"
        private DbConnectionMonitor _connectionMonitor;
        private ActiveObjectImpl _scheduler;
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

            // 
            _scheduler = new ActiveObjectImpl(string.Format($"Զ��DB-{this.DataSource.Name} Scheudler�߳�"));
            this.AddDisposable(_scheduler);
            _scheduler.Start();

            // ����һ��ConnectionMonitor���򿪡�
            this.OpenDbConnectionMonitor();
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

        public override uint NextSequence<T>()
        {
            if (_seqNoManager.Contains(typeof(T)))
            {
                return _seqNoManager.Next<T>();
            }
            else
            {
                this.CheckDb();

                using (var db = this.DbConfig.Open())
                {
                    return _seqNoManager.Next<T>(db);
                }
            }
        }

        public override IList<T> Where<T>(Expression<Func<T, bool>> predicate = null)
        {
            this.CheckDb();

            using (var db = this.DbConfig.Open())
            {
                return db.Query(predicate);
            }
        }

        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            this.CheckDb();

            using (var db = this.DbConfig.Open())
            {
                return db.Query<T>(sql, namedParameters);
            }
        }

        public override void Insert<T>(params T[] entities)
        {
            this.CheckDb();

            using (var db = this.DbConfig.Open())
            {
                db.Insert(entities);
            }
        }

        public override void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null)
        {
            this.CheckDb();

            _scheduler.AddAsyncTask(() =>
            {
                try
                {
                    Insert(entities);
                }
                catch (Exception ex)
                {
                    if (exceptionHandler == null)
                    {
                        var errMsg = string.Format("�첽��������{0}ʧ�ܣ�{1}��", typeof(T).Name, ex);
                        LogUtility.Error(errMsg);
                    }
                    else
                    {
                        try
                        {
                            exceptionHandler(ex);
                        }
                        catch
                        {
                        }
                    }
                }
            });
        }

        public override void Update<T>(object instance, Expression<Func<T, bool>> predicate)
        {
            this.CheckDb();

            using (var db = this.DbConfig.Open())
            {
                db.Update<T>(instance, predicate);
            }
        }

        public override void Delete<T>(Expression<Func<T, bool>> predicate = null)
        {
            this.CheckDb();

            using (var db = this.DbConfig.Open())
            {
                db.Delete<T>(predicate);
            }
        }

        public override void Execute<T>(Action<IDbContext> handler)
        {
            this.CheckDb();

            using (var db = DbConfig.CreateDbContext())
            {
                handler(db);
            }
        }

        public override void AsyncExecute<T>(Action<IDbContext> handler, Action<Exception> errorHandler)
        {
            this.CheckDb();

            void action()
            {
                try
                {
                    using (var db = DbConfig.CreateDbContext()) handler(db);
                }
                catch (Exception ex)
                {
                    if (errorHandler != null)
                    {
                        try
                        {
                            errorHandler(ex);
                        }
                        catch { }
                    }
                    else
                    {
                        LogUtility.Error(string.Format("Զ��DBִ��AsyncExcuteʧ�ܣ�{0}��", ex));
                    }
                }
            }

            _scheduler.AddAsyncTask(action);
        }
        #endregion

        #region "Private methods"
        /// <summary>
        /// ������ݿ��Ƿ���á�
        /// </summary>
        private void CheckDb()
        {
            if (!this.Connected) 
                throw new InvalidOperationException(string.Format("Զ�����ݿ�{0}û�����ӡ�", this.DataSource.Name));
        }

        /// <summary>
        /// ��Զ��DB���Ӽ�������
        /// </summary>
        private void OpenDbConnectionMonitor()
        {
            LogUtility.Info($"�������ӵ�Զ�����ݿ� {this.DataSource.Name} ...");

            _connectionMonitor = new DbConnectionMonitor(this.DbConfig, 3000);
            _connectionMonitor.DbConnectionChanged += this.OnDbConnectionChanged;

            if (_connectionMonitor.TestConnection())
            {
                LogUtility.Info($"�����ݿ� {this.DataSource.Name} �ɹ�...");
            }
            else
            {
                LogUtility.Warning($"�����ݿ� {this.DataSource.Name} ʧ��...");
            }

            // �����Ӽ�����
            _connectionMonitor.Open();
        }

        private void OnDbConnectionChanged(object sender, DbConnectionChangedEventArgs e)
        {
            try
            {
                this.SetConnectionState(e.Connected);
            }
            catch (System.Exception /*ex*/)
            {                
            }
        }
        #endregion

        #region "Public methods"
        #endregion
    }
}
