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
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using Acl.Data;
using Products.Infrastructure.Specification;

namespace Products.Persistence
{
    interface IRepositorySelect
    {
        IRepository SelectRepository<T>(bool memRepositoryEnabled = true);

        IRepository SelectRepository(Type entityType, bool memRepositoryEnabled = true);
    }

    class StrategyRepositorySelection : IRepositorySelect
    {
        #region "Field"
        private ReadOnlyDictionary<DataBaseType, IRepository> _localRepositories;
        #endregion

        #region "Constructor"
        public StrategyRepositorySelection(IRepository remoteRepsoitory, IDictionary<DataBaseType, IRepository> localReposities)
        {
            this.RemoteRepository = remoteRepsoitory;
            _localRepositories = new ReadOnlyDictionary<DataBaseType, IRepository>(localReposities);
        }
        #endregion

        #region "Properties"
        public IRepository RemoteRepository { get; private set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        public IRepository SelectRepository<T>(bool memRepositoryEnabled = true)
        {
            return this.SelectRepository(typeof(T), memRepositoryEnabled);
        }

        public IRepository SelectRepository(Type entityType, bool memRepositoryEnabled = true)
        {
            var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);

            // �������� MemoryRepository�� �� ����̬���ñ�
            if (memRepositoryEnabled && isStaticEntity)
            {
                return _localRepositories[DataBaseType.Memory];
            }

            // ��� RemoteRepository ��������
            if (DbConnectionMonitor.Current.Connected)
            {
                return this.RemoteRepository;
            }

            // ��ȡָ��ʵ�����Ͷ�Ӧ�ı������ݿ����͡�
            var localDataSrc = PersistenceConfig.GetDataSource(entityType);
            var localDbType = (DataBaseType)localDataSrc.DbType;

            // 
            return _localRepositories[localDbType];
        }
        #endregion

    }
}
