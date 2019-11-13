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
using System.Configuration;
using System.IO;
using System.Linq;
using System.Reflection;
using Acl.Configuration;
using Acl.Data.Configuration;
using Acl.Data.Mapping;
using Products.Infrastructure.Entities;

namespace Products.Persistence
{
    static class PersistenceConfig
    {
        #region "Data source names"
        public const string DataSourceRemoteDbName = "RemoteDatabase";
        public const string DataSourceSqliteDb4StaticConfig = "SqliteDb4StaticConfigTables";
        #endregion

        #region "Table type names"
        public const string StaticConfigTables = "StaticConfigTableNames";
        public const string DynamicConfigTables = "DynamicConfigTableNames";
        public const string LogTables = "LogTableNames";
        #endregion

        #region "Field"
        /// <summary>
        /// TextRepository 包含的表。
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// SQLite数据库 DataSourceName 与 Entity 映射。
        /// Key = Data source name.
        /// Value = DataSource包含的表。
        /// </summary>
        private static Dictionary<string, List<Type>> _sqliteDbEntityMapping = new Dictionary<string, List<Type>>();

        /// <summary>
        /// 获取或设置Entity type 格式，例如"Products.Infrastructure.Entities.{0},Products.Infrastructure"
        /// </summary>
        private static readonly string EntityTypeFormat = HelperTools.BuildEntityFormat();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 静态构造函数。
        /// </summary>
        static PersistenceConfig()
        {
            TableDescriptors = new Dictionary<Type, TableDescriptor>();

            // Initialize Settings.
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Settings = SettingsManager.GetXmlSettings(cfgPath);
            
            InitializeDbEntityMapping();
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取Persistence Settings。
        /// </summary>
        public static ISettings Settings { get; private set; }

        /// <summary>
        /// 获取SQLite数据库与实体的映射。
        /// Key：Data Source Name。
        /// Value：type of Entity.
        /// </summary>
        public static Dictionary<string, List<Type>> SqliteDbEntityMapping { get { return _sqliteDbEntityMapping; } }

        /// <summary>
        /// 获取 Table 的描述符。
        /// </summary>
        public static Dictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

        /// <summary>
        /// 获取远程DB配置。
        /// </summary>
        public static DbConfiguration RemoteConfiguration { get; private set; }
        #endregion

        #region "Private methods"

        private static void InitializeDbEntityMapping()
        {
            var dataSrcList = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToList();
            dataSrcList.ForEach(p =>
            {
                if (p.Driver.IndexOf("SQLite", StringComparison.OrdinalIgnoreCase) != -1)
                {
                    var tableTypes = new List<Type>();

                    var tableNames = p.Tables.Split(new char[] { ',', '，', ';', '；' }, StringSplitOptions.RemoveEmptyEntries);
                    tableNames.ToList().ForEach(q => tableTypes.Add(ConvertToEntityType(q.Trim())));

                    _sqliteDbEntityMapping[p.Name] = tableTypes;
                }
            });
        }

        private static DbConfiguration CreateDbConfiguration(string dbName)
        {
            // 获取 exe.config 中的连接字符串。
            var connectSettings = ConfigurationManager.ConnectionStrings.OfType<ConnectionStringSettings>()
                .Where(p => p.Name == dbName).FirstOrDefault();

            DbConfiguration cfg = null;

            if (connectSettings != null)
            {
                cfg = DbConfiguration.Configure(dbName);
            }
            else
            {
                var dataSrc = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").Where(p => p.Name == dbName).FirstOrDefault();
                if (dataSrc == null) throw new Exception(string.Format("没有找到 DataSource={0} 的配置 。", dbName));

                var urlFixed = dataSrc.Url;
                if (dataSrc.Driver.Contains("SQLite"))
                {
                    urlFixed = HelperTools.FixSQLiteDbUrl(dataSrc.Url);
                }
                cfg = DbConfiguration.Configure(urlFixed, dataSrc.Driver, dbName);
            }

            // 设置表名复数策略
            cfg.SetMappingConversion(MappingConversion.Plural);

            return cfg;
        }

        private static void CreateTableDescriptor(Dictionary<Type, TableDescriptor> descriptors, IEnumerable<string> tableNames, TableType type)
        {            
            foreach (var name in tableNames)
            {
                var entityType = ConvertToEntityType(name);
                var newValue = new TableDescriptor { EntityType = entityType, Name = name, Type = type };

                if (descriptors.ContainsKey(newValue.EntityType))
                    throw new ArgumentException(string.Format("{0} 重复配置。", newValue.EntityType.Name));

                descriptors[newValue.EntityType] = newValue;
            }
        }

        #endregion

        #region "Public methods"

        public static void Initialize()
        {
            // 创建远程数据库配置
            RemoteConfiguration = CreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName);

            // 创建静态配置表的描述符。
            var tablesNames = Settings.Get<string>(PersistenceConfig.StaticConfigTables);
            var staticTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, staticTables, TableType.StaticConfig);

            // 创建动态配置表的描述符。
            tablesNames = Settings.Get<string>(PersistenceConfig.DynamicConfigTables);
            var dynamicCfgTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgTables, TableType.DynamicConfig);

            // 创建日志表的描述符。
            tablesNames = Settings.Get<string>(PersistenceConfig.LogTables);
            var logTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, logTables, TableType.Log);
        }

        public static void Close()
        {
            DbConfiguration.Items.ToList().ForEach(p => p.Value.ClearPools());
        }

        public static bool IsStaticConfigTable<T>()
        {
            TableDescriptor value;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.Type == TableType.StaticConfig;
            }
            else
            {
                return false;
            }
        }
        public static bool IsDynamicConfigTable<T>()
        {
            TableDescriptor value;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.Type == TableType.DynamicConfig;
            }
            else
            {
                return false;
            }
        }
        public static bool IsNormalLogTable<T>()
        {
            TableDescriptor value;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.Type == TableType.Log;
            }
            else
            {
                return false;
            }
        }
        
        public static Type ConvertToEntityType(string tableName)
        {
            var typeShortName = Acl.Inflector.Singular(tableName);
            var typeName = string.Format(EntityTypeFormat, typeShortName);

            var type = System.Type.GetType(typeName);

            if (type == null) throw new TypeLoadException(string.Format("不能解析的类型名称 {0}。", typeName));

            return type;
        }
        public static string ConvertToTableName<T>()
        {
            TableDescriptor value;

            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.Name;
            }

            return null;
        }

        /// <summary>
        /// 指定的类型是否存储在文本文件中？
        /// </summary>
        public static bool IsTextData(Type entityType)
        {
            return _textRepositoryEntityMapping.Contains(entityType);
        }
        
        /// <summary>
        /// 获取所有静态表信息。
        /// </summary>
        /// <returns>一个字典对象，Key表示静态表对应的DataSource，Value表示静态表集合。</returns>
        public static Dictionary<string, List<Type>> GetStaticTableTypes()
        {
            var result = new Dictionary<string, List<Type>>();

            var allStaticTables = TableDescriptors.Values.Where(p => p.Type == TableType.StaticConfig);

            foreach (var item in _sqliteDbEntityMapping)
            {
                var value = item.Value.Intersect(allStaticTables.Select(p => p.EntityType)).ToList();
                if (value.Count > 0)
                {
                    result[item.Key] = value;
                }
            }

            return result;
        }

        /// <summary>
        /// 获取所有Sqlite数据库的DataSourceName。
        /// </summary>
        public static List<string> GetSqliteDataSourceNames()
        {
            return _sqliteDbEntityMapping.Keys.ToList();
        }

        /// <summary>
        /// 获取指定实体类型所在的SQLite数据库DataSourceName。
        /// </summary>
        public static string GetSqliteDataSourceName(Type entityType)
        {
            var theItem = _sqliteDbEntityMapping.Where(p => p.Value.Contains(entityType));

            return theItem.Count() > 0 ? theItem.First().Key : PersistenceConfig.DataSourceSqliteDb4StaticConfig;            
        }

        #endregion

    }
}
