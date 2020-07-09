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
using Products.Persistence.Services.Repository;

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
        private List<RepositoryBase> _repositories = new List<RepositoryBase>();
        #endregion

        #region "Constructor"
        public StrategyRepositorySelection()
        {
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// ���ÿ��õĲִ���
        /// </summary>
        public void SetRepositories(IEnumerable<RepositoryBase> repositories)
        {
            _repositories.AddRange(repositories);
        }

        /// <inheritdoc/>
        public IRepository SelectRepository<T>(bool memRepositoryEnabled = true)
        {
            return this.SelectRepository(typeof(T), memRepositoryEnabled);
        }

        /// <inheritdoc/>
        public IRepository SelectRepository(Type entityType, bool memRepositoryEnabled = true)
        {
            // TODO: ���ʵ���������ڵ����ݿ�AΪ����״̬���򷵻�A�����򷵻�A�ı��ÿ⡣��main DB, backup DB��

            // �������� MemoryRepository�� �� ����̬���ñ�����ʹ���ڴ����ݿ⡣
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                if (isStaticEntity)
                {
                    return _repositories.Where(p => p.DataSource.DbType == (int)DataBaseType.Memory).FirstOrDefault();
                }

                // TODO�����Ϊ��̬���ñ��Ҵ˱����ڵ�Զ�̿�û�����ӣ���ʹ���ڴ����ݿ⡣
            }

            // ��ȡָ��ʵ�����Ͷ�Ӧ�����ݿ����͡�
            var theDataSrc = PersistenceConfig.GetDataSource(entityType);

            // 
            return _repositories.Where(p => p.DataSource.Name == theDataSrc.Name).FirstOrDefault();
        }
        #endregion

    }
}
