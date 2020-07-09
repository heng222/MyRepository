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

using Products.Persistence.Services.Repository;

namespace Products.Persistence.Services
{
    /// <summary>
    /// Sqlite 数据库。
    /// </summary>
    class RepositorySqlite : RepositoryBase
    {
        #region "Field"
        private IDatabase _dataBase;

        private SqliteOperationScheduler _scheduler;

        private TableSeqNoManager _seqNoManager = new TableSeqNoManager();

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

            OpenScheduler(_dataBase);

            RemoveExpiredLogs();

            StartTimer(30000);
        }
        #endregion

        #region "private methods"

        private void OpenDatabase()
        {
            var cfg = PersistenceConfig.GetOrCreateDbConfiguration(this.DataSource.Name, false);
            _dataBase = cfg.Open();
            this.AddDisposable(_dataBase);
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
            catch (System.Exception ex)
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
                        var sqlText = string.Format(@"delete from {0} where {1} < @expiredDate",
                            _dataBase.Dialect.Quote(p.Name), _dataBase.Dialect.Quote("TimeStamp"));

                        _dataBase.ExecuteNonQuery(sqlText, new { expiredDate = expiredDate });
                    }
                    catch (System.Exception ex)
                    {
                        LogUtility.Error(string.Format("删除表 {0} 的过期日志时发生异常。\r\n{1}", p.Name, ex));
                    }
                });
            }
            catch (System.Exception ex)
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
            return _seqNoManager.Next<T>(_dataBase);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(Expression<Func<T, bool>> condition = null)
        {
            IList<T> action() => _dataBase != null ? _dataBase.Query(condition) : new List<T>();

            return _scheduler.Sync(action);
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            IList<T> action() => _dataBase.Query<T>(sql, namedParameters);

            return _scheduler.Sync(action);
        }


        public override void Insert<T>(params T[] entities)
        {
            _scheduler.Async(() => _dataBase.Insert(entities));
        }


        public override void AsyncInsert<T>(T[] entity, Action<Exception> exceptionHandler)
        {
            _scheduler.Async(() => _dataBase.Insert(entity));
        }

        /// <summary>
        /// 更新数据。
        /// </summary>
        public override void Update<T>(object instance, Expression<Func<T, bool>> condition)
        {
            void action() => _dataBase.Update<T>(instance, condition);

            _scheduler.Async(action);
        }

        /// <summary>
        /// 删除数据。
        /// </summary>
        public override void Delete<T>(Expression<Func<T, bool>> condition = null)
        {
            void action() => _dataBase.Delete(condition);

            _scheduler.Async(action);
        }

        public override void Execute<T>(Action<IDatabase> handler)
        {
            this.Execute(handler);
        }

        public void Execute(Action<IDatabase> handler)
        {
            _scheduler.Sync(() => handler(_dataBase));
        }

        public override void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler)
        {
            void action()
            {
                try
                {
                    handler(_dataBase);
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
