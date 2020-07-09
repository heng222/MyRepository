/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
using Products.Persistence.Specification;
using Products.Persistence.Services.Repositories;

namespace Products.Persistence.Services
{
    /// <summary>
    /// ���ڻ������ñ���̬���ñ� + ��̬���ñ���
    /// </summary>
    class RepositoryMemory : Repository, IDataCache
    {
        #region "Field"
        private MethodInfo _asQueryableMethodInfo = typeof(Queryable).GetMethods().FirstOrDefault(p => p.Name == "AsQueryable" && p.IsGenericMethod);

        private MethodInfo _whereMethodOfRepository = (from m in typeof(IRepository).GetMethods().Where(p => p.Name == "Where")
                                                       let ps = m.GetParameters()
                                                       where ps.Length == 1
                                                       where typeof(LambdaExpression).IsAssignableFrom(ps[0].ParameterType)
                                                       select m).FirstOrDefault();

        private static DataSource _dataSrc = new DataSource() { DbType = (int)DataBaseType.Memory };

        private Dictionary<string, IEnumerable> _cache = new Dictionary<string, IEnumerable>();

        #endregion

        #region "Constructor"
        public RepositoryMemory(IRepositorySelect reposSelector)
            : base(_dataSrc)
        {
            this.RepositorySelector = reposSelector;
        }
        #endregion

        #region "Properties"
        public IRepositorySelect RepositorySelector { get; private set; }
        #endregion

        #region "Override methods"
        protected override void OnOpen()
        {
            var staticEntityTypes = PersistenceConfig.TableDescriptors.Values
                .Where(p => p.TableKind == TableKind.StaticConfig || p.TableKind == TableKind.DynamicConfig)
                .Select(p => p.EntityType);

            foreach (var entityType in staticEntityTypes)
            {
                try
                {
                    if (_cache.ContainsKey(entityType.Name)) continue;

                    var whereMethod = _whereMethodOfRepository.MakeGenericMethod(entityType);

                    var theRepository = this.RepositorySelector.SelectRepository(entityType, false);
                    if (theRepository == null)
                    {
                        throw new Exception(string.Format($"�޷��ҵ�ʵ��{entityType.Name}���������ݿ�ӿڡ�"));
                    }

                    var enumerable = whereMethod.Invoke(theRepository, new object[] { null });

                    var queryable = _asQueryableMethodInfo.MakeGenericMethod(entityType).Invoke(null, new object[] { enumerable }) as IQueryable;

                    _cache[entityType.Name] = queryable;
                }
                catch (System.Exception ex)
                {
                    var msg = string.Format("����� {0} ʱ��������", entityType.Name);
                    throw new Exception(msg, ex);
                }
            }

            // 
            base.SetConnectionState(true);
        }

        public override uint NextSequence<T>()
        {
            throw new NotImplementedException();
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
            throw new InvalidOperationException("Memory repository ��֧��SQL�ű���ѯ");
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

        public override void Execute<T>(Action<IDbContext> handler)
        {
            throw new NotImplementedException();
        }

        public override void AsyncExecute<T>(Action<IDbContext> handler, Action<Exception> errorHandler)
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

        #endregion

        #region "IDataCache ����"

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
