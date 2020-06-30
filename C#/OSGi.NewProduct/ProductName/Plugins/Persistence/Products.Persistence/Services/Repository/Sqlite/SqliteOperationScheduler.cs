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
using System.Threading.Tasks;

using Acl.Collections;
using Acl.Data;

namespace Products.Persistence.Services
{
    /// <summary>
    /// 本地Sqlite数据库操作调度器。
    /// </summary>
    class SqliteOperationScheduler : Acl.CompositeDisposable
    {
        #region struct ActionRequest
        struct ActionRequest
        {
            public Action Action;
            public TaskCompletionSource<object> Source;

            public ActionRequest(Action action)
            {
                Action = action;
                Source = new TaskCompletionSource<object>();
            }
        }
        #endregion

        #region "Field"
        private IDatabase _dbConnection;

        private object _dbOperationSyncLock = new object();

        private ThreadSafetyList<ActionRequest> _actionCache = new ThreadSafetyList<ActionRequest>();
        private int _actionMaxCount = 100;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public SqliteOperationScheduler(IDatabase db, int actionMaxCount = 100)
        {
            _dbConnection = db;
            _actionMaxCount = actionMaxCount;
        }
        #endregion

        #region "private methods"
        private bool NeedFlush()
        {
            return _actionMaxCount > 0 && _actionCache.Count >= _actionMaxCount;
        }
        #endregion

        #region "Protected methods"
        protected override void Dispose(bool disposing)
        {
            this.Flush();

            base.Dispose(disposing);
        }
        #endregion

        #region "public methods"
        public void Open()
        {
        }

        public void Close()
        {
            this.Dispose();
        }

        /// <summary>
        /// Flush 缓存操作
        /// </summary>
        public void Flush()
        {
            if (_actionCache.Count == 0) return;

            List<ActionRequest> tempList;
            lock (_actionCache.SyncRoot)
            {
                tempList = _actionCache.ToList();
                _actionCache.Clear();
            }

            lock (_dbOperationSyncLock)
            {
                _dbConnection.UsingTransaction(() =>
                {
                    foreach (var req in tempList)
                    {
                        try
                        {
                            req.Action();
                            req.Source.SetResult(null);
                        }
                        catch (Exception ex)
                        {
                            req.Source.SetException(ex);
                            LogUtility.Error(ex.Message, ex);
                        }
                    }

                    LogUtility.Debug(string.Format("Flush 操作个数 = {0}", tempList.Count));
                });
            }
        }

        /// <summary>
        /// 执行异步任务
        /// </summary>
        /// <param name="action"></param>
        public Task Async(Action action)
        {
            var req = new ActionRequest(action);
            _actionCache.Add(req);

            if (this.NeedFlush())
            {
                this.Flush();
            }

            return req.Source.Task;
        }

        /// <summary>
        /// 执行同步任务
        /// </summary>
        /// <param name="action"></param>
        public void Sync(Action action)
        {
            lock (_dbOperationSyncLock)
            {
                this.Flush();

                action();
            }
        }

        /// <summary>
        /// 执行同步任务
        /// </summary>
        public T Sync<T>(Func<T> func)
        {
            lock (_dbOperationSyncLock)
            {
                this.Flush();

                return func();
            }
        }
        #endregion
    }
}
