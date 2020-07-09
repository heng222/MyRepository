
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
