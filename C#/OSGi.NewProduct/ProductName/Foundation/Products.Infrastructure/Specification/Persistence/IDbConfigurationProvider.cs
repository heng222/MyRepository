using Acl.Data.Configuration;

using Products.Infrastructure.Entities;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 一个接口，用于提供DbConfiguration。
    /// </summary>
    public interface IDbConfigurationProvider
    {
        /// <summary>
        /// 获取实体的 DbConfiguration。
        /// </summary>
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1004:GenericMethodsShouldProvideTypeParameter")]
        DbConfiguration GetConfig<T>() where T : Entity;
    }
}
