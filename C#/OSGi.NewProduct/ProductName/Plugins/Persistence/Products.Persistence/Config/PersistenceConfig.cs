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
using System.Data;
using System.IO;
using System.Linq;
using System.Reflection;
using Acl.Configuration;
using Acl.Data;
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
        private static Dictionary<string, DataSource> _dataSources = new Dictionary<string, DataSource>();

        /// <summary>
        /// TextRepository 包含的实体。
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// 获取或设置Entity type 格式，例如"Products.Infrastructure.Entities.{0},Products.Infrastructure"
        /// </summary>
        private static readonly string EntityTypeFormat = HelperTools.BuildEntityFormat();
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取Persistence Settings。
        /// </summary>
        public static ISettings Settings { get; private set; }

        /// <summary>
        /// 获取 TableDescriptors。
        /// </summary>
        public static Dictionary<Type, TableDescriptor> TableDescriptors
        {
            get 
            {
                return _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).ToDictionary(p => p.EntityType, q => q); 
            } 
        }

        /// <summary>
        /// 获取远程DB配置。
        /// </summary>
        public static DbConfiguration RemoteConfiguration { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// 静态构造函数。
        /// </summary>
        static PersistenceConfig()
        {
            // Initialize Settings.
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Settings = SettingsManager.GetXmlSettings(cfgPath);

            InitializeDataSource();

            // 创建远程数据库配置
            //RemoteConfiguration = GetOrCreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName);

            DbConnectionMonitor.Current.SubscribeConnectionStateChanged(OnDbConnectionChanged);
        }
        #endregion

        #region "Private methods"

        private static void InitializeDataSource()
        {
            _dataSources = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToDictionary(p => p.Name, q => q);
            _dataSources.ForEach(p =>
            {
                var entityNames = p.Value.Entities.Split(new char[] { ',', '，', ';', '；' }, StringSplitOptions.RemoveEmptyEntries);
                entityNames.ForEach(q =>
                {
                    var entityType = ConvertToEntityType(q.Trim());
                    p.Value.TableDescriptors[entityType] = null;
                });
            });

            UpdateTableDescriptors();
        }

        private static void UpdateTableDescriptors()
        {
            var tableDescriptors = new Dictionary<Type, TableDescriptor>();

            // 创建静态配置表的描述符。
            var entityNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, staticCfgEntityNames, TableType.StaticConfig);

            // 创建动态配置表的描述符。
            entityNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, dynamicCfgEntityNames, TableType.DynamicConfig);

            // 创建日志表的描述符。
            entityNames = Settings.Get<string>(PersistenceConfig.LogEntities);
            var logEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, logEntityNames, TableType.Log);

            // 更新DataSource关联的 TableDescriptors
            tableDescriptors.ForEach(p =>
            {
                var theDataSource = _dataSources.Where(q => q.Value.TableDescriptors.ContainsKey(p.Key)).Select(q => q.Value).FirstOrDefault();

                if (theDataSource != null)
                {
                    theDataSource.TableDescriptors[p.Key] = p.Value;
                }
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
                if (_dataSources.ContainsKey(dbSourceName))
                {
                    _dataSources[dbSourceName].TableDescriptors.ForEach(p => cfg.ModelBuilder.AddClass(p.Value.EntityType));
                }
            }

            return cfg;
        }

        private static void OnDbConnectionChanged(ConnectionState connectionState)
        {
            try
            {
                if (connectionState == ConnectionState.Open)
                {
                    RemoteConfiguration.ModelBuilder.ValidateSchema();
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        public static bool IsStaticConfigTable<T>()
        {
            var value = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p => p.EntityType == typeof(T)).FirstOrDefault();

            if (value != null)
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
            var value = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p => p.EntityType == typeof(T)).FirstOrDefault();

            if (value != null)
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
            var value = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p => p.EntityType == typeof(T)).FirstOrDefault();

            if (value != null)
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
            var value = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p => p.EntityType == entityType).FirstOrDefault();

            if (value != null)
            {
                return value.Name;
            }
            else
            {
                return null;
            }
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
        /// <returns>一个字典对象，Key表示静态表对应的DataSourceName，Value表示静态实体类型集合。</returns>
        public static Dictionary<string, List<Type>> GetStaticTableTypes(DataBaseType dbType)
        {
            var result = new Dictionary<string, List<Type>>();

            // 获取所有静态表描述符。
            var staticTableDescriptors = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p=>p.TableType == TableType.StaticConfig);

            // 获取指定数据类类型的映射。
            var sqliteSrcNames = _dataSources.Where(p => (DataBaseType)p.Value.DbType == dbType).Select(p => p.Value.Name);
            var theMapping = _dataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k=>k.Value.EntityType));

            // 构建 DataSourceName 与 Entity 的映射。
            foreach (var item in theMapping)
            {
                var value = item.Value.Intersect(staticTableDescriptors.Select(p => p.EntityType)).ToList();
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
            return _dataSources.Values.Where(p => (DataBaseType)p.DbType == DataBaseType.Sqlite)
                .ToDictionary(p => p.Name, q => q.TableDescriptors.Values.Select(k => k.EntityType).ToList());
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

        /// <summary>
        /// 获取指定实体类型所在的数据库类型。
        /// </summary>
        public static DataBaseType GetDatabaseType(Type entityType)
        {
            var theValue = _dataSources.Values.Where(p => p.TableDescriptors.Values.Select(k => k.EntityType).Contains(entityType)).FirstOrDefault();

            if (theValue != null)
            {
                return (DataBaseType)theValue.DbType;
            }
            else
            {
                return DataBaseType.None;
            }
        }
        #endregion

    }
}
