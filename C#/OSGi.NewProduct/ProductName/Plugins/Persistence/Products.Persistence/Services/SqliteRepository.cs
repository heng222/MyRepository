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
using System.Linq.Expressions;
using Acl.Data;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services
{
    /// <summary>
    /// 本地Sqlite数据库仓储。
    /// </summary>
    class SqliteRepository : Acl.CompositeDisposable, IRepository
    {
        #region "Field"
        private SqliteConnectionManager _dbConnectionManager;

        private Dictionary<string, SqliteOperationScheduler> _dbSchedulers = new Dictionary<string, SqliteOperationScheduler>();

        private SeqNoGenerator _sequenceGenerator = new SeqNoGenerator();
        private System.Timers.Timer _timerFlush;

        private uint _latestClearTickcount = 0;

        private DataCache _dataCache = new DataCache();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public SqliteRepository()
        {
            var dataSrcNames = PersistenceConfig.GetSqliteDataSourceNames();

            _dbConnectionManager = new SqliteConnectionManager(dataSrcNames, PersistenceConfig.SqliteDbEntityMapping);

            this.AddDisposable(_dbConnectionManager);
        }
        #endregion

        #region "override methods"
        /// <summary>
        /// 释放资源。
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            CloseTimer();

            ClosePersistenceScheduler();

            _sequenceGenerator = null;

            base.Dispose(disposing);
        }
        #endregion

        #region "private methods"

        private void CreateTimer(int flushCacheInterval)
        {
            _timerFlush = new System.Timers.Timer();
            _timerFlush.Interval = flushCacheInterval;
            _timerFlush.Elapsed += OnTimer_Elapsed;
            _timerFlush.Start();
        }

        private void CloseTimer()
        {
            var tmp = _timerFlush;
            _timerFlush = null;
            tmp.Stop();
            tmp.Dispose();
        }

        private void OnTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                Flush();

                // 每月1日凌晨两点执行清理任务。
                var span = TimeSpan.FromSeconds((uint)(Environment.TickCount / 1000) - _latestClearTickcount);

                if (DateTime.Now.Day == 1 && DateTime.Now.Hour == 2 && span.Hours > 2)
                {
                    _latestClearTickcount = (uint)(Environment.TickCount / 1000);

                    RemoveExpiredLogs();
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex.ToString());
            }
        }

        private void RemoveExpiredLogs()
        {
            try
            {
                var expiredDate = DateTime.Now.AddYears(-1);

                // TODO：删除过期的日志。
                this.Delete<SysEventLog>(p => p.Timestamp < expiredDate);
                this.Delete<OperationLog>(p => p.Timestamp < expiredDate);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex.ToString());
            }
        }


        private void CreateAndOpenPersistenceScheduler()
        {
            var connectionStrings = PersistenceConfig.GetSqliteDataSourceNames();

            connectionStrings.ForEach(p =>
            {
                var db = _dbConnectionManager.GetConnection(p);
                _dbSchedulers[p] = new SqliteOperationScheduler(db);
                _dbSchedulers[p].Open();
            });
        }

        private void ClosePersistenceScheduler()
        {
            _dbSchedulers.Values.ToList().ForEach(p => p.Close());
            _dbSchedulers.Clear();
        }

        private SqliteOperationScheduler GetAsyncPersistenceScheduler<TEntity>()
        {
            var connectionString = PersistenceConfig.GetSqliteDataSourceName(typeof(TEntity));

            return _dbSchedulers[connectionString];
        }
        #endregion

        #region "public methods"
        /// <summary>
        /// 打开数据仓储
        /// </summary>
        /// <param name="flushInterval">flush缓存间隔</param>
        public void Open(int flushInterval = 30000)
        {
            _dbConnectionManager.Open();

            CreateAndOpenPersistenceScheduler();

            // 初始化数据缓存。
            var staticTables = PersistenceConfig.GetStaticTableTypes();
            foreach (var item in staticTables)
            {
                var db = _dbConnectionManager.GetConnection(item.Key);
                _dataCache.Cache(db, item.Value);
            }

            RemoveExpiredLogs();

            CreateTimer(flushInterval);
        }

        /// <summary>
        /// Flush 缓存操作
        /// </summary>
        public void Flush()
        {
            _timerFlush.Stop();

            _dbSchedulers.Values.ToList().ForEach(p => p.Flush());

            if (_timerFlush != null) _timerFlush.Start();
        }
        #endregion

        #region IRepository 成员

        /// <summary>
        /// 返回指定实体的下个序列值
        /// </summary>
        public uint NextSequence<T>() where T : Entity
        {
            var connection = _dbConnectionManager.GetConnection<T>();
            return _sequenceGenerator.Next<T>(connection);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public IList<T> Where<T>(Expression<Func<T, bool>> condition = null) where T : Entity
        {
            var scheduler = this.GetAsyncPersistenceScheduler<T>();

            if (_dataCache.Contains<T>())
            {
                return _dataCache.Query(condition);
            }
            else
            {
                Func<IList<T>> action = () =>
                {
                    var db = _dbConnectionManager.GetConnection<T>();
                    return db.Query<T>(condition);
                };

                return scheduler.Sync<IList<T>>(action);
            }
        }
                

        public void Insert<T>(params T[] entities) where T : Entity
        {
            var db = _dbConnectionManager.GetConnection<T>();

            GetAsyncPersistenceScheduler<T>().Async(() => db.Insert(entities));
        }


        public void AsyncInsert<T>(T[] entity, Action<Exception> exceptionHandler) where T : Entity
        {
            var db = _dbConnectionManager.GetConnection<T>();

            GetAsyncPersistenceScheduler<T>().Async(() => db.Insert(entity));
        }

        /// <summary>
        /// 更新数据。
        /// </summary>
        public void Update<T>(object instance, Expression<Func<T, bool>> condition) where T : Entity
        {
            Action action = () => 
            { 
                _dbConnectionManager.GetConnection<T>().Update<T>(instance, condition); 
            };

            GetAsyncPersistenceScheduler<T>().Async(action);
        }

        /// <summary>
        /// 删除数据。
        /// </summary>
        public void Delete<T>(Expression<Func<T, bool>> condition = null) where T : Entity
        {
            Action action = () =>
            {
                var db = _dbConnectionManager.GetConnection<T>();
                db.Delete<T>(condition);
            };

            GetAsyncPersistenceScheduler<T>().Async(action);
        }
        
        public void Execute<T>(Action<IDatabase> handler) where T : Entity
        {
            var scheduler = this.GetAsyncPersistenceScheduler<T>();
            var db = _dbConnectionManager.GetConnection<T>();
            scheduler.Sync(() => handler(db));
        }

        public void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler) where T : Entity
        {
            Action action = () =>
            {
                try
                {
                    var db = _dbConnectionManager.GetConnection<T>();
                    handler(db);                    
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
                        LogUtility.Info(ex.Message, ex);
                    }
                }
            };

            var scheduler = this.GetAsyncPersistenceScheduler<T>();
            scheduler.Async(action);            
        }
        #endregion
    }
}
