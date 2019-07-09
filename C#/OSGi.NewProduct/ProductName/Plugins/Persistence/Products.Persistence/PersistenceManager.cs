﻿/*----------------------------------------------------------------
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
using System.Configuration;
using System.Linq.Expressions;
using System.Reflection;
using System.Windows.Forms;
using Acl.Data;
using Acl.Log;
using Acl.ServiceManagement;
using Products.Domain;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Exceptions;
using Products.Infrastructure.Specification;
using Products.Persistence.Implementation;
using Products.Persistence.Services;

namespace Products.Persistence
{
    /// <summary>
    /// 持久化管理器。
    /// </summary>
    public class PersistenceManager : Acl.CompositeDisposable, IRepository
    {
        #region "Field"
        private SqliteRepository _localSqliteRepository;

        private TextFileDataStorage _txtFileDataStorage = new TextFileDataStorage();
        #endregion

        #region "Properties"
        #endregion

        #region "public methods"

        /// <summary>
        /// 启动数据库配置管理器并根据配置文件中的设备ID初始化设备上下文。
        /// </summary>
        public void Open()
        {
            this.Open(uint.MaxValue);
        }

        /// <summary>
        /// 启动数据库配置管理器并根据指定的设备ID初始化设备上下文。
        /// </summary>
        /// <param name="deviceID">指定的本地设备编号。
        /// uint.MinValue表示不初始化节点上下文；uint.MaxValue表示根据配置文件中的ID初始化设备上下文。</param>
        public void Open(UInt32 deviceID)
        {
            InitializeEnvironment();

            // 
            LogUtility.Info("正在初始化数据仓储...");
            InitializeRepository();

            // 
            LogUtility.Info("正在初始化节点上下文...");
            if (deviceID == uint.MaxValue)
            {
                InitializeNodeContext(-1);
            }
            else if (deviceID != uint.MinValue)
            {
                InitializeNodeContext(deviceID);
            }

            // 
            InitializeLogHeadersFooters();
        }

        /// <summary>
        /// Close manager.
        /// </summary>
        public void Close()
        {
            // 
            if (_localSqliteRepository != null)
            {
                _localSqliteRepository.Dispose();
            }

            // 
            DbConnectionMonitor.Current.Close();

            PersistenceConfig.Close();
        }
        #endregion

        #region "Private methods"
        private void InitializeEnvironment()
        {
            // 数据库日志配置
            Database.Logger = (fmt, args, level, ex) => LogUtility.Trace(fmt, args, (LogLevel)level, ex);

            // 配置SQLite 底层的dll 对应的环境变量（主要是为了加载该底层的dll）
            string configurationFieldirectory = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            Environment.SetEnvironmentVariable("PreLoadSQLite_BaseDirectory", configurationFieldirectory);

            // 初始化配置。
            PersistenceConfig.Initialize();
        }

        private void InitializeRepository()
        {
            // 创建Remote DB连接监视器
            CreateRemoteDbConnectionMonitor();

            // 创建本地 Sqlite 仓储。
            _localSqliteRepository = new SqliteRepository();
            _localSqliteRepository.Open();
            
            // 更新全局服务。
            ServiceManager.Current.RegisterInstance(this);
        }

        /// <summary>
        /// 初始化远程DB连接监视器。
        /// </summary>
        private void CreateRemoteDbConnectionMonitor()
        {
            LogUtility.Info("创建远程数据库连接监视器...");
            DbConnectionMonitor.MarkDbConnectionMonitor(PersistenceConfig.DataSourceRemoteDbName);

            if (DbConnectionMonitor.Current.TestConnection())
            {
                LogUtility.Log.LogLevel = LogLevel.Information;
                LogUtility.Info("打开数据库连接成功...");
            }
            else
            {
                LogUtility.Info("打开数据库连接失败...");
                DbConnectionMonitor.EnabledLog = false;
                LogUtility.Log.LogLevel = LogLevel.Warning;
            }

            // 打开连接监视器
            DbConnectionMonitor.Current.Open();
        }

        /// <summary>
        /// 根据配置文件中的设备ID初始化节点上下文。
        /// </summary>
        private void InitializeNodeContext(long nodeCode)
        {
            var deviceContext = new NodeContextImpl();

            var idInAppConfig = nodeCode;

            // 如果指定的ID小于等于零，则从配置文件中读取ID。
            if (idInAppConfig < 0)
            {
                var dictLocalSettings = ConfigurationManager.AppSettings;

                if (!string.IsNullOrWhiteSpace(dictLocalSettings["NodeCode"]))
                {
                    idInAppConfig = Convert.ToInt32(dictLocalSettings["NodeCode"]);
                }
                else
                {
                    throw new InvalidOperationException("在配置文件中没有找到NodeCode。");
                }
            }

            if (idInAppConfig < 0)
            {
                // 如果ID值无效，则根据IP初始化。
                deviceContext.Initialize();
            }
            else if (idInAppConfig > 0)
            {
                // 如果ID值有效，则使用指定的ID值初始化。
                deviceContext.Initialize((UInt32)idInAppConfig);
            }
            else
            {
                var customNode = SelectCustomNode();
                deviceContext.Initialize(customNode);
            }

            GlobalServices.NodeContext = deviceContext;
        }

        private uint SelectCustomNode()
        {
            uint customNode = 0;

            var dataSrc = BuildNodeSelectable();

            var form = new NodeSelectionForm(dataSrc);
            var rc = form.ShowDialog(null);
            if (rc == DialogResult.OK)
            {
                customNode = form.NodeCode;
            }

            if (customNode == 0)
            {
                throw new LanuchCanceledException("用户选择取消启动。");
            }

            return customNode;
        }

        private Dictionary<uint, string> BuildNodeSelectable()
        {
            return new Dictionary<uint, string>();
            //// 初始化节点列表。
            //var atsNodes = GlobalServices.Repository.Where<Machine>().Where(p => NodeContextManager.Contains(p.TypeCode))
            //    .OrderBy(p => p.Code).ToList();

            //return atsNodes.ToDictionary(p => p.Code, q => string.Format("{0}_{1}（{2}_{3}）",
            //    q.Code, q.Name, q.StationCode, q.Station == null ? "中心" : q.Station.Name));
        }
        

        /// <summary>
        /// 初始化日志页眉页脚。
        /// </summary>
        private void InitializeLogHeadersFooters()
        {
            if (GlobalServices.SysAttribute == null || GlobalServices.NodeContext == null) return;

            Acl.Log.LogManager.FileHeader = string.Format("--- 日志页眉：【{0}】-【{1}】 ---{2}",
                GlobalServices.SysAttribute.ProjectChsName,
                GlobalServices.NodeContext.Name,
                Environment.NewLine);

            Acl.Log.LogManager.FileFooter = string.Format("--- 日志页脚：【{0}】-【{1}】 ---{2}",
                GlobalServices.SysAttribute.ProjectChsName,
                GlobalServices.NodeContext.Name,
                Environment.NewLine);

            // 更新日志文件前缀。
            LogManager.FileNameSurfix = string.Format("_{0}", GlobalServices.NodeContext.Name);
            LogManager.ActivateOptions();
        }

        #endregion


        #region IRepository 成员
        /// <summary>
        /// 
        /// </summary>
        public IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity
        {
            if (PersistenceConfig.IsTextData(typeof(T)))
            {
                return _txtFileDataStorage.Where(predicate);
            }
            else
            {
                return _localSqliteRepository.Where(predicate);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Insert<T>(params T[] entities) where T : Entity
        {
            if (PersistenceConfig.IsTextData(typeof(T))) throw new InvalidOperationException();

            _localSqliteRepository.Insert(entities);
        }

        /// <summary>
        /// 
        /// </summary>
        public void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler) where T : Entity
        {
            if (PersistenceConfig.IsTextData(typeof(T))) throw new InvalidOperationException();

            _localSqliteRepository.AsyncInsert(entities, exceptionHandler);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Delete<T>(Expression<Func<T, bool>> predicate) where T : Entity
        {
            if (PersistenceConfig.IsTextData(typeof(T))) throw new InvalidOperationException();

            _localSqliteRepository.Delete(predicate);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity
        {
            if (PersistenceConfig.IsTextData(typeof(T))) throw new InvalidOperationException();

            _localSqliteRepository.Update(instance, predicate);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Execute<T>(Action<IDatabase> handler) where T : Entity
        {
            _localSqliteRepository.Execute<T>(handler);
        }

        /// <summary>
        /// 
        /// </summary>
        public void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler) where T : Entity
        {
            _localSqliteRepository.AsyncExecute<T>(handler, errorHandler);
        }

        #endregion
    }
}