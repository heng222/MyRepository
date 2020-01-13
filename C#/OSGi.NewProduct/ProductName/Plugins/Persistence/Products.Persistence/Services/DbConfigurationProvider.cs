using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Acl.Data.Configuration;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;

namespace Products.Persistence.Services
{
    class DbConfigurationProvider : IDbConfigurationProvider
    {
        #region "Field"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

        #region IDbConfigurationProvider 成员

        public DbConfiguration GetConfig<T>() where T : Entity
        {
            var dbSrcName = PersistenceConfig.GetDataSourceName(typeof(T));

            return PersistenceConfig.GetOrCreateDbConfiguration(dbSrcName);
        }

        #endregion
    }
}
