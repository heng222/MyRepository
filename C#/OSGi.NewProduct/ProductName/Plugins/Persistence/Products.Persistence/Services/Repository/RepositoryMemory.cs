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

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;

using Acl;
using Acl.Data;

using Products.Infrastructure.Specification;
using Products.Persistence.Services.Repository;
using Products.Persistence.Specification;

namespace Products.Persistence.Services
{
    class RepositoryMemory : RepositoryBase, IDataCache
    {
        #region "Field"
        private MethodInfo _asQueryableMethodInfo = typeof(Queryable).GetMethods().FirstOrDefault(p => p.Name == "AsQueryable" && p.IsGenericMethod);

        private MethodInfo _whereMethodOfRepository = (from m in typeof(IRepository).GetMethods().Where(p => p.Name == "Where")
                                                       let ps = m.GetParameters()
                                                       where ps.Length == 1
                                                       where typeof(LambdaExpression).IsAssignableFrom(ps[0].ParameterType)
                                                       select m).FirstOrDefault();

        private Dictionary<string, IEnumerable> _cache = new Dictionary<string, IEnumerable>();

        #endregion

        #region "Constructor"
        public RepositoryMemory()
        {
        }
        #endregion

        #region "Properties"
        public IRepositorySelect RepositorySelector { get; set; }
        #endregion

        #region "Override methods"
        protected override void OnOpen()
        {
            var staticEntityTypes = PersistenceConfig.TableDescriptors.Where(p => p.Value.TableKind == TableKind.StaticConfig).Select(p => p.Value.EntityType);

            foreach (var entityType in staticEntityTypes)
            {
                try
                {
                    if (_cache.ContainsKey(entityType.Name)) continue;

                    var whereMethod = _whereMethodOfRepository.MakeGenericMethod(entityType);

                    var srcRepository = this.RepositorySelector.SelectRepository(entityType, false);

                    var enumerable = whereMethod.Invoke(srcRepository, new object[] { null });

                    var queryable = _asQueryableMethodInfo.MakeGenericMethod(entityType).Invoke(null, new object[] { enumerable }) as IQueryable;

                    _cache[entityType.Name] = queryable;
                }
                catch (System.Exception ex)
                {
                    var msg = string.Format("缓存数据时，读取表 {0} 发生错误，{1}。", entityType.Name, ex.Message);
                    throw new Exception(msg, ex);
                }
            }
        }

        public override IList<T> Where<T>(Expression<Func<T, bool>> predicate = null)
        {
            var entityName = typeof(T).Name;

            IEnumerable data;

            if (_cache.TryGetValue(entityName, out data))
            {
                var rep = data as IQueryable<T>;

                return predicate == null ? rep.ToList() : rep.Where(predicate).ToList();
            }
            else
            {
                return new List<T>();
            }
        }

        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            throw new InvalidOperationException("Memory repository 不支持SQL脚本查询");
        }

        public override void Insert<T>(params T[] entities)
        {
            throw new NotImplementedException();
        }

        public override void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null)
        {
            throw new NotImplementedException();
        }

        public override void Update<T>(object instance, Expression<Func<T, bool>> predicate)
        {
            throw new NotImplementedException();
        }

        public override void Delete<T>(Expression<Func<T, bool>> predicate = null)
        {
            throw new NotImplementedException();
        }

        public override void Execute<T>(Action<IDatabase> handler)
        {
            throw new NotImplementedException();
        }

        public override void AsyncExecute<T>(Action<IDatabase> handler, Action<Exception> errorHandler)
        {
            throw new NotImplementedException();
        }
        #endregion

        #region "Private methods"

        private bool TryGetValue(Dictionary<string, object> condition, Type type, object instance)
        {
            var found = false;

            foreach (var item in condition)
            {
                var property = type.GetProperty(item.Key);

                if (property == null)
                {
                    return false;
                }

                try
                {
                    var value = property.PropertyType == item.Value.GetType()
                        ? item.Value
                        : Converter.Convert(item.Value, property.PropertyType);

                    if (Equals(property.GetValue(instance, null), value))
                    {
                        found = true;
                    }
                    else
                    {
                        return false;
                    }
                }
                catch (Exception /*ex*/)
                {
                    return false;
                }
            }

            return found;
        }

        #endregion

        #region "Public methods"
        [Obsolete]
        public void Cache(IDatabase db, IEnumerable<Type> entityTypes)
        {
            foreach (var entityType in entityTypes)
            {
                try
                {
                    if (_cache.ContainsKey(entityType.Name)) continue;

                    var descriptor = PersistenceConfig.GetTableDescriptor(entityType);

                    using (var reader = db.ExecuteReader("select * from " + db.Dialect.Quote(descriptor.Name)))
                    {
                        var enumerable = Acl.Mapper.Map(reader, typeof(IList<>).MakeGenericType(entityType));

                        var queryable = _asQueryableMethodInfo.MakeGenericMethod(entityType).Invoke(null, new object[] { enumerable }) as IQueryable;

                        _cache[entityType.Name] = queryable;
                    }
                }
                catch (System.Exception ex)
                {
                    var msg = string.Format("读取表 {0} 发生错误，{1}。", entityType.Name, ex.Message);
                    throw new Exception(msg, ex);
                }
            }
        }

        #endregion

        #region "IDataCache 方法"

        public object GetValue(Dictionary<string, object> condition, Type entityType)
        {
            if (!_cache.ContainsKey(entityType.Name))
            {
                throw new Exception(string.Format("在数据缓存中没有找到实体类型 {0}。", entityType.Name));
            }

            var entityList = _cache[entityType.Name];

            foreach (var instance in entityList)
            {
                if (this.TryGetValue(condition, entityType, instance))
                {
                    return instance;
                }
            }

            return null;
        }
        #endregion
    }
}
