/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Acl;
using Acl.Data;

namespace Products.Persistence.Services
{
    /// <summary>
    /// 数据缓存接口。
    /// </summary>
    interface IDataCache
    {
        /// <summary>
        /// 获取实体对象。
        /// </summary>
        /// <param name="condition">指定的条件。</param>
        /// <param name="entityType">实体类型。</param>
        /// <returns></returns>
        object GetValue(Dictionary<string, object> condition, Type entityType);
    }

    class DataCache : IDataCache
    {
        #region "Field"
        private MethodInfo _asQueryableMethodInfo = typeof(Queryable).GetMethods().FirstOrDefault(p => p.Name == "AsQueryable" && p.IsGenericMethod);

        private Dictionary<string, IEnumerable> _cache = new Dictionary<string, IEnumerable>();
        #endregion

        #region "Constructor"
        public DataCache()
        {

        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
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
        public void Initialize(IDatabase db, IEnumerable<Type> entityTypes)
        {
            foreach (var entityType in entityTypes)
            {
                try
                {
                    if (_cache.ContainsKey(entityType.Name)) continue;

                    using (var reader = db.ExecuteReader("select * from " + Acl.Inflector.Plural(entityType.Name)))
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
        
        public bool Contains<TEntity>()
        {
            var entityName = typeof(TEntity).Name;

            return _cache.Keys.Contains(entityName);
        }

        public IList<T> Query<T>(Expression<Func<T, bool>> predicate)
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
