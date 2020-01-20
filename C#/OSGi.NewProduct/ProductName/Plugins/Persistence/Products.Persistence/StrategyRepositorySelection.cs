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

            // “启用了 MemoryRepository” 且 “静态配置表”
            if (memRepositoryEnabled && isStaticEntity)
            {
                return _localRepositories[DataBaseType.Memory];
            }

            // 如果 RemoteRepository 连接正常
            if (DbConnectionMonitor.Current.Connected)
            {
                return this.RemoteRepository;
            }

            // 获取指定实体类型对应的本地数据库类型。
            var localDataSrc = PersistenceConfig.GetDataSource(entityType);
            var localDbType = (DataBaseType)localDataSrc.DbType;

            // 
            return _localRepositories[localDbType];
        }
        #endregion

    }
}
