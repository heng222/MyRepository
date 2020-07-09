/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        /// ʵ������ - ��������Դӳ���
        /// KEY= ʵ�����͡�
        /// </summary>
        private readonly Dictionary<Type, Repository> _mainRepositoryMapping = new Dictionary<Type, Repository>();

        /// <summary>
        /// ʵ������ - ��������Դӳ���
        /// KEY= ʵ�����͡�
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

                // ��ȡ����DataSource��
                var dataSrc = dataSrces.Where(p => p.TableDescriptors.Keys.Contains(entityType) && !p.IsBackup).First();

                // �������� Repository��
                _mainRepositoryMapping[entityType] = _repositories.Where(p => p.DataSource.Name == dataSrc.Name).First();

                // ���±���DataSource��
                if (!string.IsNullOrEmpty(dataSrc.BackupDataSourceName))
                {
                    _backupRepositoryMapping[entityType] = _repositories.Where(p => p.DataSource.Name == dataSrc.BackupDataSourceName).First(); 
                }
            });
        }

        #endregion

        #region "Public methods"
        /// <summary>
        /// ���ÿ��õĲִ���
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

            // �Ƿ������� MemoryRepository��
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                var isDynamicEntity = PersistenceConfig.IsDynamicConfigTable(entityType);

                // ���Ϊ����̬���ñ� || ��Ϊ��̬���ñ��Ҵ˱����ڵ�Զ�̿�û�����ӡ�
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
                // ���ÿ��Ƿ����ӣ�
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
