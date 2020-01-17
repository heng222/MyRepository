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
using Products.Persistence.Services.Repository;

namespace Products.Persistence.Services
{
    /// <summary>
    /// 本地Sqlite数据库仓储。
    /// </summary>
    class SqliteRepository : RepositoryImpl
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
            var dataSrcNames = PersistenceConfig.GetDataSourceNames(DataBaseType.Sqlite);

            var sqliteDbSrcEntityMapping = PersistenceConfig.GetDataSrcNameEntityMapping(DataBaseType.Sqlite);
            _dbConnectionManager = new SqliteConnectionManager(dataSrcNames, sqliteDbSrcEntityMapping);

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

        /// <summary>
        /// 打开数据仓储
        /// </summary>
        protected override void OnOpen()
        {
            _dbConnectionManager.Open();

            CreateAndOpenPersistenceScheduler();

            // 初始化数据缓存。
            var staticTables = PersistenceConfig.GetDataSrcNameEntityMapping(DataBaseType.Sqlite, TableKind.StaticConfig);
            staticTables.ForEach(p =>
            {
                var db = _dbConnectionManager.GetConnection(p.Key);
                _dataCache.Cache(db, p.Value);
            });

            RemoveExpiredLogs();

            CreateTimer(30000);
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

                PersistenceConfig.GetTableDescriptors(TableKind.Log).ForEach(p =>
                {
                    try
                    {
                        this.Execute(p.EntityType, db =>
                        {
                            var descriptor = PersistenceConfig.GetTableDescriptor(p.EntityType);

                            var sqlText = string.Format(@"delete from {0} where {1} < @expiredDate",
                                db.Dialect.Quote(descriptor.Name), db.Dialect.Quote("TimeStamp"));

                            db.ExecuteNonQuery(sqlText, new { expiredDate = expiredDate });
                        });
                    }
                    catch (System.Exception ex)
                    {
                        LogUtility.Error(string.Format("删除表 {0} 过期日志时发生异常。\r\n{1}", p.Name, ex));
                    }
                });
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex.ToString());
            }
        }


        private void CreateAndOpenPersistenceScheduler()
        {
            var dataSrcNames = PersistenceConfig.GetDataSourceNames(DataBaseType.Sqlite);

            dataSrcNames.ForEach(p =>
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

        private SqliteOperationScheduler GetOperationScheduler<TEntity>()
        {
            return this.GetOperationScheduler(typeof(TEntity));
        }

        private SqliteOperationScheduler GetOperationScheduler(Type type)
        {
            var dataSrcName = PersistenceConfig.GetDataSourceName(type, DataBaseType.Sqlite);

            if (string.IsNullOrWhiteSpace(dataSrcName))
            {
                throw new Exception(string.Format("没有找到类型 {0} 对应的 ConnectionString.", type));
            }

            return _dbSchedulers[dataSrcName];
        }

        #endregion

        #region "public methods"

        /// <summary>
        /// Flush 缓存操作
        /// </summary>
        public void Flush()
        {
            _timerFlush.Stop();

            _dbSchedulers.Values.ToList().ForEach(p => p.Flush());

            if (_timerFlush != null) _timerFlush.Start();
        }

        /// <summary>
        /// 查询指定实体的下个序列值。
        /// </summary>
        public override uint NextSequence<T>() 
        {
            var connection = _dbConnectionManager.GetConnection<T>();
            return _sequenceGenerator.Next<T>(connection);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(Expression<Func<T, bool>> condition = null)
        {
            var scheduler = this.GetOperationScheduler<T>();

            if (_dataCache.Contains<T>())
            {
                return _dataCache.Query(condition);
            }
            else
            {
                Func<IList<T>> action = () =>
                {
                    var db = _dbConnectionManager.GetConnection<T>();
                    return db != null ? db.Query<T>(condition) : new List<T>();
                };

                return scheduler.Sync<IList<T>>(action);
            }
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            if (_dataCache.Contains<T>()) throw new InvalidOperationException("静态数据不支持SQL脚本查询");

            var scheduler = this.GetOperationScheduler<T>();

            Func<IList<T>> action = () =>
            {
                var db = _dbConnectionManager.GetConnection<T>();
                return db.Query<T>(sql, namedParameters);
            };

            return scheduler.Sync<IList<T>>(action);
        }


        public override void Insert<T>(params T[] entities) 
        {
            var db = _dbConnectionManager.GetConnection<T>();

            GetOperationScheduler<T>().Async(() => db.Insert(entities));
        }


        public override void AsyncInsert<T>(T[] entity, Action<Exception> exceptionHandler) 
        {
            var db = _dbConnectionManager.GetConnection<T>();

            GetOperationScheduler<T>().Async(() => db.Insert(entity));
        }

        /// <summary>
        /// 更新数据。
        /// </summary>
        public override void Update<T>(object instance, Expression<Func<T, bool>> condition) 
        {
            Action action = () =>
            {
                _dbConnectionManager.GetConnection<T>().Update<T>(instance, condition);
            };

            GetOperationScheduler<T>().Async(action);
        }

        /// <summary>
        /// 删除数据。
        /// </summary>
        public override void Delete<T>(Expression<Func<T, bool>> condition = null) 
        {
            Action action = () =>
            {
                var db = _dbConnectionManager.GetConnection<T>();
                db.Delete<T>(condition);
            };

            GetOperationScheduler<T>().Async(action);
        }

        public override void Execute<T>(Action<IDatabase> handler) 
        {
            this.Execute(typeof(T), handler);
        }

        public void Execute(Type entityType, Action<IDatabase> handler)
        {
            var scheduler = this.GetOperationScheduler(entityType);
            var db = _dbConnectionManager.GetConnection(entityType);
            scheduler.Sync(() => handler(db));
        }

        public override void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler) 
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

            var scheduler = this.GetOperationScheduler<T>();
            scheduler.Async(action);
        }
        #endregion
    }
}
