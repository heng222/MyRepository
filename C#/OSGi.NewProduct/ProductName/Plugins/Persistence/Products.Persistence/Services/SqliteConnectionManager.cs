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
        /// Key = Data Source Name。
        /// </summary>
        private Dictionary<string, IDatabase> _dbConnections = new Dictionary<string, IDatabase>();

        /// <summary>
        /// DataSourceName与Entity映射。
        /// Key = Data source name.
        /// Value = DataSource包含的表。
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
        /// 获取默认的DataBase接口。
        /// </summary>
        public IDatabase DataBase { get { return _dbConnections.First().Value; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private IDatabase OpenDatabase(string dbSourceName)
        {
            Acl.Data.Configuration.DbConfiguration cfg;

            if (!Acl.Data.Configuration.DbConfiguration.Items.TryGetValue(dbSourceName, out cfg))
            {
                var dataSrc = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").Where(p => p.Name == dbSourceName).FirstOrDefault();
                if (dataSrc == null) throw new Exception(string.Format("没有找到 DataSource={0} 的配置 。", dbSourceName));

                // 
                var urlFixed = HelperTools.FixSQLiteDbUrl(dataSrc.Url);
                cfg = Acl.Data.Configuration.DbConfiguration.Configure(urlFixed, dataSrc.Driver, dbSourceName);

                // 设置表名复数策略
                cfg.SetMappingConversion(MappingConversion.Plural);
            }

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
            if (_dbConnections.Count == 1)
            {
                return this.DataBase;
            }
            else
            {
                var theItem = _entityMapping.Where(p => p.Value.Contains(typeof(TEntity)));
                var connectionString = theItem.Count() > 0 ? theItem.First().Key : string.Empty;
                return string.IsNullOrEmpty(connectionString) ? null : _dbConnections[connectionString];
            }
        }
        #endregion

    }
}
