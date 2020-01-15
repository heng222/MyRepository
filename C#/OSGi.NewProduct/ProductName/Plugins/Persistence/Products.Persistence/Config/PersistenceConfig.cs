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
using System.Linq;
using System.Reflection;
using Acl.Configuration;
using Acl.Data;
using Acl.Data.Configuration;
using Acl.Data.Mapping;
using Acl.Reflection;

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
        public static Dictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

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
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Settings = SettingsManager.GetXmlSettings(cfgPath);
            
            InitializeDataSource();

            // 创建远程数据库配置
            RemoteConfiguration = GetOrCreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName);

            DbConnectionMonitor.Current.SubscribeConnectionStateChanged(OnDbConnectionChanged);
        }
        #endregion

        #region "Private methods"

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

        private static void InitializeDataSource()
        {
            CreateTableDescriptors();

            // 
            _dataSources = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToDictionary(p => p.Name, q => q);
            _dataSources.ForEach(p =>
            {
                var entityNames = p.Value.Entities.Split(new char[] { ',', '，', ';', '；' }, StringSplitOptions.RemoveEmptyEntries);
                entityNames.ForEach(q =>
                {
                    var entityType = ConvertToEntityType(q.Trim());

                    if (!TableDescriptors.ContainsKey(entityType)) throw new Exception(string.Format("没有找到 {0} 的 TableDescriptor。", entityType.Name));
                    p.Value.TableDescriptors[entityType] = TableDescriptors[entityType];
                });
            });
        }

        private static void CreateTableDescriptors()
        {
            TableDescriptors = new Dictionary<Type, TableDescriptor>();

            // 创建静态配置表的描述符。
            var entityNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(TableDescriptors, staticCfgEntityNames, TableKind.StaticConfig);

            // 创建动态配置表的描述符。
            entityNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgEntityNames, TableKind.DynamicConfig);

            // 创建日志表的描述符。
            entityNames = Settings.Get<string>(PersistenceConfig.LogEntities);
            var logEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(TableDescriptors, logEntityNames, TableKind.Log);
        }

        private static void CreateTableDescriptor(Dictionary<Type, TableDescriptor> descriptors, IEnumerable<string> entityNames, TableKind tableType)
        {
            foreach (var entityName in entityNames)
            {
                var entityType = ConvertToEntityType(entityName);
                var tableName = ConvertToTableName(entityType);

                var newValue = new TableDescriptor { EntityType = entityType, Name = tableName, TableKind = tableType };

                if (descriptors.ContainsKey(newValue.EntityType))
                    throw new ArgumentException(string.Format("{0} 重复配置。", newValue.EntityType.Name));

                descriptors[newValue.EntityType] = newValue;
            }
        }

        private static Type ConvertToEntityType(string entityName)
        {
            var typeName = string.Format(EntityTypeFormat, entityName);
            var type = System.Type.GetType(typeName);

            if (type == null) throw new TypeLoadException(string.Format("不能解析的类型名称 {0}。", typeName));

            return type;
        }

        private static string ConvertToTableName(Type entityType)
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

        public static bool IsStaticConfigTable<T>()
        {
            TableDescriptor value = null;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.TableKind == TableKind.StaticConfig;
            }
            else
            {
                return false;
            }
        }
        public static bool IsDynamicConfigTable<T>()
        {
            TableDescriptor value = null;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.TableKind == TableKind.DynamicConfig;
            }
            else
            {
                return false;
            }
        }
        public static bool IsNormalLogTable<T>()
        {
            TableDescriptor value = null;
            if (TableDescriptors.TryGetValue(typeof(T), out value))
            {
                return value.TableKind == TableKind.Log;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// 获取指定实体所在的数据库类型。
        /// </summary>
        public static DataBaseType GetDatabaseType(Type entityType)
        {
            var theDataSource = GetDataSource(entityType);

            return theDataSource != null ? (DataBaseType)theDataSource.DbType : DataBaseType.None;
        }

        /// <summary>
        /// 根据实体类型，获取 DataSource。
        /// </summary>
        public static DataSource GetDataSource(Type entityType)
        {
            return _dataSources.Values.Where(p => p.TableDescriptors.Values.Select(k => k.EntityType).Contains(entityType)).FirstOrDefault();
        }
        
        /// <summary>
        /// 根据实体类型与数据库类型获取DataSourceName。
        /// </summary>
        public static string GetDataSourceName(Type entityType, DataBaseType dbType)
        {
            var sqliteSrcNameEntityMapping = GetDataSrcNameEntityMapping(dbType);

            return sqliteSrcNameEntityMapping.Where(p => p.Value.Contains(entityType)).FirstOrDefault().Key;
        }
        /// <summary>
        /// 根据数据库类型，获取DataSourceName。
        /// </summary>
        public static IEnumerable<string> GetDataSourceNames(DataBaseType dbType)
        {
            var sqliteSrcNameEntityMapping = GetDataSrcNameEntityMapping(dbType);

            return sqliteSrcNameEntityMapping.Keys.ToList();
        }

        public static TableDescriptor GetTableDescriptor<T>()
        {
            return GetTableDescriptor(typeof(T));
        }
        public static TableDescriptor GetTableDescriptor(Type entityType)
        {
            return GetTableDescriptor(entityType.Name);
        }
        public static TableDescriptor GetTableDescriptor(string entityName)
        {
            return TableDescriptors.Values.Where(p => p.EntityType.Name == entityName).FirstOrDefault();
        }
        /// <summary>
        /// 获取指定种类的表描述符。
        /// </summary>
        public static IEnumerable<TableDescriptor> GetTableDescriptors(TableKind tableKind)
        {
            return TableDescriptors.Values.Where(p => p.TableKind == tableKind);
        }

        /// <summary>
        /// 获取数据库与实体的映射。
        /// Key：Data Source Name。
        /// Value：数据库中包含的实体类型集合。
        /// </summary>
        public static Dictionary<string, List<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType)
        {
            return _dataSources.Values.Where(p => (DataBaseType)p.DbType == dbType)
                .ToDictionary(p => p.Name, q => q.TableDescriptors.Values.Select(k => k.EntityType).ToList());
        }

        /// <summary>
        /// 根据数据库类型与表的种类获取DataSourceName与实体类型的映射关系。
        /// </summary>
        /// <returns>一个字典对象，Key表示DataSourceName，Value表示实体类型集合。</returns>
        public static Dictionary<string, List<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType, TableKind tableKind)
        {
            var result = new Dictionary<string, List<Type>>();

            // 获取指定种类的表的描述符。
            var staticTableDescriptors = TableDescriptors.Values.Where(p => p.TableKind == tableKind);

            // 获取指定数据类类型的映射。
            var sqliteSrcNames = _dataSources.Where(p => (DataBaseType)p.Value.DbType == dbType).Select(p => p.Value.Name);
            var theMapping = _dataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k => k.Value.EntityType));

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
        #endregion

    }
}
