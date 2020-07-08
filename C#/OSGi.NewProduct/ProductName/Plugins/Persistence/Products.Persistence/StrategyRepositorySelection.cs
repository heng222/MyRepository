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

            // “启用了 MemoryRepository” 且 “静态配置表”，则使用内存数据库。
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                if (isStaticEntity)
                {
                    return _repositories[DataBaseType.Memory];
                }

                // TODO：如果为动态配置表且此表所在的远程库没有连接，则使用内存数据库。
            }

            // 获取指定实体类型对应的数据库类型。
            var localDataSrc = PersistenceConfig.GetDataSource(entityType);
            var localDbType = (DataBaseType)localDataSrc.DbType;

            // 
            return _repositories[localDbType];
        }
        #endregion

    }
}
