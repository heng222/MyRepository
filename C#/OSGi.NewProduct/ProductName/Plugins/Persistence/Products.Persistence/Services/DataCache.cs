/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
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
    /// ���ݻ���ӿڡ�
    /// </summary>
    interface IDataCache
    {
        /// <summary>
        /// ��ȡʵ�����
        /// </summary>
        /// <param name="condition">ָ����������</param>
        /// <param name="entityType">ʵ�����͡�</param>
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
                    var msg = string.Format("��ȡ�� {0} ��������{1}��", entityType.Name, ex.Message);
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
                throw new Exception(string.Format("�����ݻ�����û���ҵ�ʵ������ {0}��", entityType.Name));
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
