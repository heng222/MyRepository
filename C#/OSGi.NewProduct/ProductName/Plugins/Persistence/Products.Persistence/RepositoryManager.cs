﻿/*----------------------------------------------------------------
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
using System.Configuration;
using System.Linq;
using System.Linq.Expressions;
using System.Windows.Forms;

using Acl.Data;
using Acl.Log;
using Acl.ServiceManagement;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Exceptions;
using Products.Infrastructure.Log;
using Products.Infrastructure.Specification;
using Products.Persistence.Services;
using Products.Persistence.Services.Repositories;

namespace Products.Persistence
{
    /// <summary>
    /// 持久化管理器。
    /// </summary>
    public class RepositoryManager : Acl.CompositeDisposable, IRepository
    {
        #region "Field"
        /// <summary>
        /// Key = DataSource Name。
        /// </summary>
        private Dictionary<string, Repository> _repositories = new Dictionary<string, Repository>();

        private StrategyRepositorySelection _repositorySelector = new StrategyRepositorySelection();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public RepositoryManager()
        {
        }
        #endregion

        #region "Properties"
        #endregion

        #region "public methods"

        /// <summary>
        /// 启动数据库配置管理器并根据配置文件中的设备ID初始化设备上下文。
        /// </summary>
        public void Open()
        {
            var enableRemoteDb = true;
            if (!string.IsNullOrWhiteSpace(ConfigurationManager.AppSettings["EnableRemoteDb"]))
            {
                enableRemoteDb = Convert.ToBoolean(ConfigurationManager.AppSettings["EnableRemoteDb"]);
            }

            this.Open(uint.MaxValue, enableRemoteDb);
        }

        /// <summary>
        /// 启动数据库配置管理器并根据指定的设备ID初始化设备上下文。
        /// </summary>
        /// <param name="deviceID">指定的本地设备编号。
        /// uint.MinValue表示不初始化节点上下文；uint.MaxValue表示根据配置文件中的ID初始化设备上下文。</param>
        /// <param name="enableRemoteDb">是否启用远程数据库？</param>
        public void Open(UInt32 deviceID, bool enableRemoteDb = true)
        {
            InitializeEnvironment(enableRemoteDb);

            // 
            LogUtility.Info("正在初始化数据仓储...");
            InitializeRepository(enableRemoteDb);

            // 
            LogUtility.Info("正在初始化实体导航属性...");
            this.InitializeEntityNavigationProperty();

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
            _repositories.Values.ForEach(p => p.Dispose());
            _repositories.Clear();

            // 
            DbConnectionMonitor.Current.Close();

            PersistenceConfig.Close();
        }
        #endregion

        #region "Private methods"
        private void InitializeEnvironment(bool enableRemoteDb)
        {
            // 数据库日志配置
            Database.UseLog(LoggerNames.Persistence);

            // 配置SQLite 底层的dll 对应的环境变量（主要是为了加载该底层的dll）
            Environment.SetEnvironmentVariable("PreLoadSQLite_BaseDirectory", HelperTools.CurrentDllPath);

            // 初始化配置。
            PersistenceConfig.Initialize(enableRemoteDb);
        }

        private void InitializeRepository(bool enableRemoteDb)
        {
            // 创建 Repository。
            this.CreateRepositories(enableRemoteDb);

            // 创建 RepsoitorySelection Strategy。
            _repositorySelector.SetRepositories(_repositories.Values);

            // 打开 Repository
            _repositories.Values.ForEach(p => p.Open());

            // 更新全局服务。
            ServiceManager.Current.RegisterInstance(this);
        }

        private void CreateRepositories(bool enableRemoteDb)
        {
            var dataSources = PersistenceConfig.GetDataSources();

            // 是否启用远程数据库？
            if (!enableRemoteDb)
            {
                dataSources = dataSources.Where(p => !PersistenceConfig.IsRemoteDatabase((DataBaseType)p.DbType));
            }

            // 内置 MemoryRepository。
            var memoryDataSource = new DataSource()
            {
                Name = DataBaseType.Memory.ToString(),
                DbType = (int)DataBaseType.Memory,
            };
            dataSources = dataSources.Union(new DataSource[] { memoryDataSource });

            // 创建 Repository。
            _repositories = RepositoryFactory.Create(dataSources, _repositorySelector).ToDictionary(p => p.DataSource.Name, q => q);
        }

        /// <summary>
        /// 初始化实体导航属性。
        /// </summary>
        private void InitializeEntityNavigationProperty()
        {

        }

        /// <summary>
        /// 根据配置文件中的设备ID初始化节点上下文。
        /// </summary>
        private void InitializeNodeContext(long nodeCode)
        {
            var deviceContext = new NodeContext();
            GlobalServices.NodeContext = deviceContext;

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
        }

        private uint SelectCustomNode()
        {
            uint customNode = 0;

            var dataSrc = BuildNodeSelectable();

            var mainForm = Application.OpenForms.OfType<Control>().FirstOrDefault();
            mainForm.Invoke(new Action(() =>
            {
                var form = new NodeSelectionForm(dataSrc);
                var rc = form.ShowDialog(mainForm);
                if (rc == DialogResult.OK)
                {
                    customNode = form.NodeCode;

                    this.SaveNodeCode2ConfigFile(customNode);
                }

                if (customNode == 0)
                {
                    throw new LanuchCanceledException("用户选择取消启动。");
                }
            }));

            return customNode;
        }

        /// <summary>
        /// 保存节点编号到配置文件中。
        /// </summary>
        private void SaveNodeCode2ConfigFile(uint nodeCode)
        {
            var key = "NodeCode";
            var config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);

            config.AppSettings.Settings.Remove(key);
            config.AppSettings.Settings.Add(key, nodeCode.ToString());
            config.Save(ConfigurationSaveMode.Modified);

            ConfigurationManager.RefreshSection("appSettings");
        }

        private Dictionary<uint, string> BuildNodeSelectable()
        {
            var theNodes = GlobalServices.Repository.Where<SystemNode>()
                .OrderBy(p => p.Code).ToList();

            return theNodes.ToDictionary(p => p.Code, q => string.Format("{0}_{1}",
                q.Code, q.Name));
        }

        /// <summary>
        /// 初始化日志页眉页脚。
        /// </summary>
        private void InitializeLogHeadersFooters()
        {
            if (GlobalServices.SysAttribute == null || GlobalServices.NodeContext == null) return;

            if (string.IsNullOrWhiteSpace(GlobalServices.NodeContext.Name)) return;

            LogManager.GetCurrentAppenders().Where(t => t.Option.Type == AppenderType.File).ForEach(p =>
            {
                p.Option.File.Header = $"--- 日志页眉：【{GlobalServices.SysAttribute.ProjectChsName}】-【{GlobalServices.NodeContext.Name}】 ---{Environment.NewLine}";
                p.Option.File.Header = $"--- 日志页脚：【{GlobalServices.SysAttribute.ProjectChsName}】-【{GlobalServices.NodeContext.Name}】 ---{Environment.NewLine}";
                //更新日志文件前缀。
                p.Option.File.Surfix = $"_{GlobalServices.NodeContext.Name}";

                p.ActiveOption();
            });
        }

        #endregion


        #region IRepository 成员
        /// <summary>
        /// 返回指定实体的下个序列值。
        /// </summary>
        public uint NextSequence<T>() where T : Entity
        {
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                return theRepository.NextSequence<T>();
            }
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public IList<T> Where<T>(Expression<Func<T, bool>> predicate = null) where T : Entity
        {
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                return theRepository.Where(predicate);
            }
        }

        /// <summary>
        /// 查询数据。
        /// </summary>
        public IList<T> Where<T>(string sql, object namedParameters = null)
        {
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                return theRepository.Where<T>(sql, namedParameters);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Insert<T>(params T[] entities) where T : Entity
        {
            // 如果是静态数据，则不允许此操作。
            var entityType = typeof(T);
            if (PersistenceConfig.IsStaticConfigTable(entityType))
            {
                throw new InvalidOperationException(string.Format($"{entityType.Name} 为静态配置数据，无法执行Insert操作。"));
            }

            // 
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.Insert(entities);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler) where T : Entity
        {
            // 如果是静态数据，则不允许此操作。
            var entityType = typeof(T);
            if (PersistenceConfig.IsStaticConfigTable(entityType))
            {
                throw new InvalidOperationException(string.Format($"{entityType.Name} 为静态配置数据，无法执行AsyncInsert操作。"));
            }

            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.AsyncInsert(entities, exceptionHandler);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Delete<T>(Expression<Func<T, bool>> predicate) where T : Entity
        {
            // 如果是静态数据，则不允许此操作。
            var entityType = typeof(T);
            if (PersistenceConfig.IsStaticConfigTable(entityType))
            {
                throw new InvalidOperationException(string.Format($"{entityType.Name} 为静态配置数据，无法执行Delete操作。"));
            }

            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.Delete(predicate);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Update<T>(object instance, Expression<Func<T, bool>> predicate) where T : Entity
        {
            // 如果是静态数据，则不允许此操作。
            var entityType = typeof(T);
            if (PersistenceConfig.IsStaticConfigTable(entityType))
            {
                throw new InvalidOperationException(string.Format($"{entityType.Name} 为静态配置数据，无法执行Update操作。"));
            }

            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.Update(instance, predicate);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Execute<T>(Action<IDbContext> handler) where T : Entity
        {
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.Execute<T>(handler);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void AsyncExecute<T>(Action<IDbContext> handler, Action<Exception> errorHandler) where T : Entity
        {
            var theRepository = _repositorySelector.SelectRepository(typeof(T));

            if (theRepository == null)
            {
                throw new InvalidOperationException();
            }
            else
            {
                theRepository.AsyncExecute<T>(handler, errorHandler);
            }
        }

        #endregion
    }
}
