/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2018-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;

using Products.Infrastructure.Specification;
using Products.Persistence.Services.Repositories;
using Products.Persistence.Specification;

namespace Products.Persistence
{
    class StrategyRepositorySelection : IRepositorySelect
    {
        #region "Field"
        private readonly List<Repository> _repositories = new List<Repository>();

        /// <summary>
        /// 实体类型 - 主用数据源映射表。
        /// KEY= 实体类型。
        /// </summary>
        private readonly Dictionary<Type, Repository> _mainRepositoryMapping = new Dictionary<Type, Repository>();

        /// <summary>
        /// 实体类型 - 备用数据源映射表。
        /// KEY= 实体类型。
        /// </summary>
        private readonly Dictionary<Type, Repository> _backupRepositoryMapping = new Dictionary<Type, Repository>();
        #endregion

        #region "Constructor"
        public StrategyRepositorySelection()
        {
        }
        #endregion

        #region "Properties"
        public Repository MemoryRepository { get; private set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void UpdateDataSourceMappings()
        {
            var dataSrces = _repositories.Select(p => p.DataSource);

            PersistenceConfig.TableDescriptors.ForEach(q =>
            {
                var entityType = q.Value.EntityType;

                // 获取主用DataSource。
                var dataSrc = dataSrces.Where(p => p.TableDescriptors.Keys.Contains(entityType) && !p.IsBackup).First();

                // 更新主用 Repository。
                _mainRepositoryMapping[entityType] = _repositories.Where(p => p.DataSource.Name == dataSrc.Name).First();

                // 更新备用DataSource。
                if (!string.IsNullOrEmpty(dataSrc.BackupDataSourceName))
                {
                    _backupRepositoryMapping[entityType] = _repositories.Where(p => p.DataSource.Name == dataSrc.BackupDataSourceName).First(); 
                }
            });
        }

        #endregion

        #region "Public methods"
        /// <summary>
        /// 设置可用的仓储。
        /// </summary>
        public void SetRepositories(IEnumerable<Repository> repositories)
        {
            _repositories.AddRange(repositories);

            this.MemoryRepository = _repositories.Where(p => p.DataSource.DbType == (int)DataBaseType.Memory).First();

            this.UpdateDataSourceMappings();
        }

        /// <inheritdoc/>
        public IRepository SelectRepository<T>(bool memRepositoryEnabled = true)
        {
            return this.SelectRepository(typeof(T), memRepositoryEnabled);
        }

        /// <inheritdoc/>
        public IRepository SelectRepository(Type entityType, bool memRepositoryEnabled = true)
        {
            var mainRepository = _mainRepositoryMapping[entityType];

            // 是否启用了 MemoryRepository？
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                var isDynamicEntity = PersistenceConfig.IsDynamicConfigTable(entityType);

                // 如果为“静态配置表” || “为动态配置表且此表所在的远程库没有连接”
                if (isStaticEntity || (isDynamicEntity && !mainRepository.Connected))
                {
                    return this.MemoryRepository;
                }
                else
                {
                    return _mainRepositoryMapping[entityType];
                }        
            }
            else
            {
                // 主用库是否连接？
                if (mainRepository.Connected)
                {
                    return mainRepository;
                }
                else
                {
                    _backupRepositoryMapping.TryGetValue(entityType, out Repository backupRepository);
                    return backupRepository;
                }
            }

        }
        #endregion

    }
}
