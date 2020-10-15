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

using Acl.Data;

using Products.Infrastructure.Entities;
using Products.Persistence.Services.Repositories;

namespace Products.Persistence.Services
{
    /// <summary>
    /// Sqlite 数据库。
    /// </summary>
    class RepositorySqlite : Repository
    {
        #region "Field"
        private IDbContext _dbContext;

        private SqliteOperationScheduler _scheduler;

        private readonly TableSeqNoManager _seqNoManager = new TableSeqNoManager();

        private System.Timers.Timer _timerFlush;

        private uint _latestClearTickcount = 0;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public RepositorySqlite(DataSource dataSrc)
            : base(dataSrc)
        {
        }
        #endregion

        #region "override methods"
        /// <summary>
        /// 释放资源。
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            CloseTimer();

            CloseScheduler();

            base.Dispose(disposing);
        }

        /// <inheritdoc/>
        protected override void OnOpen()
        {
            OpenDatabase();

            OpenScheduler(_dbContext);

            RemoveExpiredLogs();

            StartTimer(30000);
        }
        #endregion

        #region "private methods"

        private void OpenDatabase()
        {
            var cfg = PersistenceConfig.GetOrCreateDbConfiguration(this.DataSource.Name, false);
            _dbContext = cfg.CreateDbContext();
            this.AddDisposable(_dbContext);

            // 
            base.SetConnectionState(true);
        }

        private void StartTimer(int flushCacheInterval)
        {
            if (_timerFlush == null)
            {
                _timerFlush = new System.Timers.Timer();
                _timerFlush.Interval = flushCacheInterval;
                _timerFlush.Elapsed += OnTimer_Elapsed;
            }

            _timerFlush.Start();
        }

        private void CloseTimer()
        {
            if (_timerFlush != null)
            {
                var tmp = _timerFlush;
                _timerFlush = null;
                tmp.Close();
            }
        }

        private void OnTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                // Pause timer.
                if (_timerFlush != null) _timerFlush.Stop();

                // Flush
                _scheduler.Flush();

                // 每月1日凌晨两点执行清理任务。
                var span = TimeSpan.FromSeconds((uint)(Environment.TickCount / 1000) - _latestClearTickcount);

                if (DateTime.Now.Day == 1 && DateTime.Now.Hour == 2 && span.Hours > 2)
                {
                    _latestClearTickcount = (uint)(Environment.TickCount / 1000);

                    RemoveExpiredLogs();
                }
            }
            catch (Exception ex)
            {
                LogUtility.Error(ex);
            }
            finally
            {
                if (_timerFlush != null) _timerFlush.Start();
            }
        }

        private void RemoveExpiredLogs()
        {
            try
            {
                var expiredDate = DateTime.Now.AddYears(-1);

                var logTableDescriptors = this.DataSource.TableDescriptors.Values.Where(p => p.TableKind == TableKind.Log);
                logTableDescriptors.ForEach(p =>
                {
                    try
                    {
                        var sqlText = string.Format(@"delete from {0} where {1} < @{2}",
                            _dbContext.Dialect.Quote(p.Name),
                            _dbContext.Dialect.Quote(nameof(LogEntity.Timestamp)),
                            nameof(expiredDate));

                        _dbContext.ExecuteNonQuery(sqlText, new { expiredDate });
                    }
                    catch (Exception ex)
                    {
                        LogUtility.Error(string.Format("删除表 {0} 的过期日志时发生异常。\r\n{1}", p.Name, ex));
                    }
                });
            }
            catch (Exception ex)
            {
                LogUtility.Error(ex);
            }
        }


        private void OpenScheduler(IDatabase db)
        {
            _scheduler = new SqliteOperationScheduler(db);
            _scheduler.Open();
        }

        private void CloseScheduler()
        {
            if (_scheduler != null)
            {
                _scheduler.Close();
                _scheduler = null;
            }
        }

        #endregion

        #region "public methods"

        public override uint NextSequence<T>()
        {
            return _seqNoManager.Next<T>(_dbContext);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(Expression<Func<T, bool>> condition = null)
        {
            IList<T> action() => _dbContext != null ? _dbContext.Query(condition) : new List<T>();

            return _scheduler.Sync(action);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            IList<T> action() => _dbContext.Query<T>(sql, namedParameters);

            return _scheduler.Sync(action);
        }


        public override void Insert<T>(params T[] entities)
        {
            _scheduler.Async(() => _dbContext.Insert(entities));
        }


        public override void AsyncInsert<T>(T[] entity, Action<Exception> exceptionHandler)
        {
            _scheduler.Async(() => _dbContext.Insert(entity));
        }

        /// <summary>
        /// 更新数据。
        /// </summary>
        public override void Update<T>(object instance, Expression<Func<T, bool>> condition)
        {
            void action() => _dbContext.Update(instance, condition);

            _scheduler.Async(action);
        }

        /// <summary>
        /// 删除数据。
        /// </summary>
        public override void Delete<T>(Expression<Func<T, bool>> condition = null)
        {
            void action() => _dbContext.Delete(condition);

            _scheduler.Async(action);
        }

        public override void Execute<T>(Action<IDbContext> handler)
        {
            this.Execute(handler);
        }

        public void Execute(Action<IDbContext> handler)
        {
            _scheduler.Sync(() => handler(_dbContext));
        }

        public override void AsyncExecute<T>(Action<IDbContext> handler, Action<Exception> errorHandler)
        {
            void action()
            {
                try
                {
                    handler(_dbContext);
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
            }

            _scheduler.Async(action);
        }
        #endregion
    }
}
