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
        /// 设置可用的仓储。
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
            // TODO: 如果实体类型所在的数据库A为连接状态，则返回A；否则返回A的备用库。（main DB, backup DB）

            // “启用了 MemoryRepository” 且 “静态配置表”，则使用内存数据库。
            if (memRepositoryEnabled)
            {
                var isStaticEntity = PersistenceConfig.IsStaticConfigTable(entityType);
                if (isStaticEntity)
                {
                    return _repositories.Where(p => p.DataSource.DbType == (int)DataBaseType.Memory).FirstOrDefault();
                }

                // TODO：如果为动态配置表且此表所在的远程库没有连接，则使用内存数据库。
            }

            // 获取指定实体类型对应的数据库类型。
            var theDataSrc = PersistenceConfig.GetDataSource(entityType);

            // 
            return _repositories.Where(p => p.DataSource.Name == theDataSrc.Name).FirstOrDefault();
        }
        #endregion

    }
}
