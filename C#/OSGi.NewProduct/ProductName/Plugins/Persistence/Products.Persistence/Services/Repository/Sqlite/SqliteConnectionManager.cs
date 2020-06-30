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
using System.Collections.Generic;
using System.Linq;

using Acl.Data;
using Acl.Data.Mapping;

namespace Products.Persistence.Services
{
    class SqliteConnectionManager : Acl.CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// Data source names.
        /// </summary>
        private List<string> _dataSrcNames = new List<string>();

        /// <summary>
        /// Key = Data Source Name��
        /// </summary>
        private Dictionary<string, IDatabase> _dbConnections = new Dictionary<string, IDatabase>();

        /// <summary>
        /// DataSourceName��Entityӳ�䡣
        /// Key = Data source name.
        /// Value = DataSource�����ı�
        /// </summary>
        private Dictionary<string, List<Type>> _entityMapping = null;

        #endregion

        #region "Constructor"
        public SqliteConnectionManager(string dataSrcName)
        {
            _dataSrcNames.Add(dataSrcName);
        }

        public SqliteConnectionManager(IEnumerable<string> dataSrcNames, IDictionary<string, List<Type>> dataSrc2EntityMapping)
        {
            _dataSrcNames.AddRange(dataSrcNames);
            _entityMapping = new Dictionary<string, List<Type>>(dataSrc2EntityMapping);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡĬ�ϵ�DataBase�ӿڡ�
        /// </summary>
        public IDatabase DataBase { get { return _dbConnections.First().Value; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private IDatabase OpenDatabase(string dbSourceName)
        {
            var cfg = PersistenceConfig.GetOrCreateDbConfiguration(dbSourceName, true);
            return cfg.Open();
        }

        #endregion

        #region "Public methods"

        public void Open()
        {
            _dataSrcNames.ForEach(p =>
            {
                var db = this.OpenDatabase(p);
                this.AddDisposable(db);

                _dbConnections.Add(p, db);
            });
        }

        public IDatabase GetConnection(string dataSourceName)
        {
            IDatabase result = null;
            _dbConnections.TryGetValue(dataSourceName, out result);
            return result;
        }

        public IDatabase GetConnection<TEntity>()
        {
            return this.GetConnection(typeof(TEntity));
        }

        public IDatabase GetConnection(Type entityType)
        {
            if (_dbConnections.Count == 1)
            {
                return this.DataBase;
            }
            else
            {
                var theItem = _entityMapping.Where(p => p.Value.Contains(entityType));
                var connectionString = theItem.Count() > 0 ? theItem.First().Key : string.Empty;
                return string.IsNullOrEmpty(connectionString) ? null : _dbConnections[connectionString];
            }
        }
        #endregion

    }
}
