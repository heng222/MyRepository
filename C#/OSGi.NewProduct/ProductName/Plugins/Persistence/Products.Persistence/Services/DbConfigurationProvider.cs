/*----------------------------------------------------------------
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
using Acl.Data.Configuration;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services
{
    class DbConfigurationProvider : IDbConfigurationProvider
    {
        #region IDbConfigurationProvider 成员

        public DbConfiguration GetConfig<T>() where T : Entity
        {
            var dataSource = PersistenceConfig.GetDataSource(typeof(T));

            return PersistenceConfig.GetOrCreateDbConfiguration(dataSource.Name, false);
        }

        #endregion
    }
}
