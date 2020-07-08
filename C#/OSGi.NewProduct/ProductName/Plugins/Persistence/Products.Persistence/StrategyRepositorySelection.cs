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
        private ReadOnlyDictionary<DataBaseType, IRepository> _repositories;
        #endregion

        #region "Constructor"
        public StrategyRepositorySelection(IDictionary<DataBaseType, IRepository> repositories)
        {
            _repositories = new ReadOnlyDictionary<DataBaseType, IRepository>(repositories);
        }
        #endregion

        #region "Properties"
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

            // �������� MemoryRepository�� �� ����̬���ñ�����ʹ���ڴ����ݿ⡣
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                if (isStaticEntity)
                {
                    return _repositories[DataBaseType.Memory];
                }

                // TODO�����Ϊ��̬���ñ��Ҵ˱����ڵ�Զ�̿�û�����ӣ���ʹ���ڴ����ݿ⡣
            }

            // ��ȡָ��ʵ�����Ͷ�Ӧ�����ݿ����͡�
            var localDataSrc = PersistenceConfig.GetDataSource(entityType);
            var localDbType = (DataBaseType)localDataSrc.DbType;

            // 
            return _repositories[localDbType];
        }
        #endregion

    }
}
