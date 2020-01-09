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
using Acl.Reflection;
using Products.Infrastructure.Entities;

namespace Products.Persistence
{
    static class PersistenceConfig
    {
        #region "数据库连接字符串"
        public const string DataSourceRemoteDbName = "RemoteDatabase";
        #endregion

        #region "实体类型分组"
        public const string StaticConfigEntities = "StaticConfigEntityNames";
        public const string DynamicConfigEntities = "DynamicConfigEntityNames";
        public const string LogEntities = "LogTableEntityNames";
        #endregion

        #region "Field"
        /// <summary>
        /// DataSource 集合。
        /// </summary>
        private static List<DataSource> _dataSources;

        /// <summary>
        /// TextRepository 包含的实体。
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// DataSourceName 与 Entity 的映射。
        /// Key = Data source name.
        /// Value = DataSource包含的实体。
        /// </summary>
        private static Dictionary<string, List<Type>> _srcNameEntityMapping = new Dictionary<string, List<Type>>();

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

            InitializeSrcNameEntityMapping();
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取Persistence Settings。
        /// </summary>
        public static ISettings Settings { get; private set; }

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

        private static void InitializeSrcNameEntityMapping()
        {
            _dataSources = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToList();
            _dataSources.ForEach(p =>
            {
                var tableTypes = new List<Type>();

                var tableNames = p.Entities.Split(new char[] { ',', '，', ';', '；' }, StringSplitOptions.RemoveEmptyEntries);
                tableNames.ToList().ForEach(q => tableTypes.Add(ConvertToEntityType(q.Trim())));

                _srcNameEntityMapping[p.Name] = tableTypes;
            });
        }

        private static void CreateTableDescriptor(Dictionary<Type, TableDescriptor> descriptors, IEnumerable<string> entityNames, TableType tableType)
        {
            foreach (var entityName in entityNames)
            {
                var entityType = ConvertToEntityType(entityName);
                var tableName = GetEntityTableName(entityType);

                var newValue = new TableDescriptor { EntityType = entityType, Name = tableName, TableType = tableType };

                if (descriptors.ContainsKey(newValue.EntityType))
                    throw new ArgumentException(string.Format("{0} 重复配置。", newValue.EntityType.Name));

                descriptors[newValue.EntityType] = newValue;
            }
        }

        private static string GetEntityTableName(Type entityType)
        {
            var att = entityType.GetAttribute<Acl.Data.Annotions.TableAttribute>(false);

            if (att != null && !string.IsNullOrWhiteSpace(att.Name))
            {
                return att.Name;
            }
            else
            {
                return Acl.Inflector.Plural(entityType.Name);
            }
        }
        #endregion

        #region "Public methods"

        public static void Initialize()
        {
            // 创建静态配置表的描述符。
            var tablesNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, staticTables, TableType.StaticConfig);

            // 创建动态配置表的描述符。
            tablesNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgTables, TableType.DynamicConfig);

            // 创建日志表的描述符。
            tablesNames = Settings.Get<string>(PersistenceConfig.LogEntities);
            var logTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, logTables, TableType.Log);

            // 创建远程数据库配置
            RemoteConfiguration = GetOrCreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName);
        }

        public static void Close()
        {
            DbConfiguration.Items.ToList().ForEach(p => p.Value.ClearPools());
        }

        public static DbConfiguration GetOrCreateDbConfiguration(string dbSourceName)
        {
            DbConfiguration cfg = null;

            if (!Acl.Data.Configuration.DbConfiguration.Items.TryGetValue(dbSourceName, out cfg))
            {
                // 获取 exe.config 中的连接字符串。
                var connectSettings = ConfigurationManager.ConnectionStrings.OfType<ConnectionStringSettings>()
                    .Where(p => p.Name == dbSourceName).FirstOrDefault();

                if (connectSettings != null)
                {
                    cfg = DbConfiguration.Configure(dbSourceName);
                }
                else
                {
                    var dataSrc = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").Where(p => p.Name == dbSourceName).FirstOrDefault();
                    if (dataSrc == null) throw new Exception(string.Format("没有找到 DataSource={0} 的配置 。", dbSourceName));

                    var urlFixed = dataSrc.Url;
                    if (dataSrc.Driver.Contains("SQLite"))
                    {
                        urlFixed = HelperTools.FixSQLiteDbUrl(dataSrc.Url);
                    }
                    cfg = DbConfiguration.Configure(urlFixed, dataSrc.Driver, dbSourceName);
                }

                // 设置表名复数策略
                cfg.SetMappingConversion(MappingConversion.Plural);

                // 添加DB表映射。
                if (_srcNameEntityMapping.ContainsKey(dbSourceName))
                {
                    _srcNameEntityMapping[dbSourceName].ForEach(p => cfg.ModelBuilder.AddClass(p));
                }

                cfg.ModelBuilder.ValidateSchema();
            }

            return cfg;
        }

        public static bool IsStaticConfigTable<T>()
        {
            TableDescriptor value;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.TableType == TableType.StaticConfig;
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
                return value.TableType == TableType.DynamicConfig;
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
                return value.TableType == TableType.Log;
            }
            else
            {
                return false;
            }
        }

        public static Type ConvertToEntityType(string entityName)
        {
            var typeName = string.Format(EntityTypeFormat, entityName);

            var type = System.Type.GetType(typeName);

            if (type == null) throw new TypeLoadException(string.Format("不能解析的类型名称 {0}。", typeName));

            return type;
        }
        public static string ConvertToTableName<T>()
        {
            return ConvertToTableName(typeof(T));
        }
        public static string ConvertToTableName(Type entityType)
        {
            TableDescriptor value;

            if (TableDescriptors.TryGetValue(entityType, out value))
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
        /// 获取指定数据库类型的DataSourceName与静态表的映射关系。
        /// </summary>
        /// <returns>一个字典对象，Key表示静态表对应的DataSourceName，Value表示静态表类型集合。</returns>
        public static Dictionary<string, List<Type>> GetStaticTableTypes(DataBaseType dbType)
        {
            var result = new Dictionary<string, List<Type>>();

            // 获取所有静态表描述符。
            var allStaticTables = TableDescriptors.Values.Where(p => p.TableType == TableType.StaticConfig);

            // 获取指定数据类类型的映射。
            var sqliteDbSrc = _dataSources.Where(p => (DataBaseType)p.DbType == dbType).Select(p => p.Name);
            var theMapping = _srcNameEntityMapping.Where(p => sqliteDbSrc.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value);

            // 构建DataSourceName与 Entity 的映射。
            foreach (var item in theMapping)
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
        /// 获取SQLite数据库与实体的映射。
        /// Key：Data Source Name。
        /// Value：SQLite数据库中包含的实体类型集合。
        /// </summary>
        public static Dictionary<string, List<Type>> GetSqliteDataSourceEntityMapping()
        {
            var sqliteDbSrc = _dataSources.Where(p => (DataBaseType)p.DbType == DataBaseType.Sqlite).Select(p => p.Name);

            return _srcNameEntityMapping.Where(p => sqliteDbSrc.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value);
        }

        /// <summary>
        /// 获取所有Sqlite数据库的DataSourceName。
        /// </summary>
        public static List<string> GetSqliteDataSourceNames()
        {
            var sqliteSrcNameEntityMapping = GetSqliteDataSourceEntityMapping();

            return sqliteSrcNameEntityMapping.Keys.ToList();
        }

        /// <summary>
        /// 获取指定实体类型所在的SQLite数据库DataSourceName。
        /// </summary>
        public static string GetSqliteDataSourceName(Type entityType)
        {
            var sqliteSrcNameEntityMapping = GetSqliteDataSourceEntityMapping();

            return sqliteSrcNameEntityMapping.Where(p => p.Value.Contains(entityType)).FirstOrDefault().Key;
        }

        #endregion

    }
}
