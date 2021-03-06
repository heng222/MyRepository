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
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Data;
using System.Linq;

using Acl.Configuration;
using Acl.Data;
using Acl.Data.Configuration;
using Acl.Data.Mapping;
using Acl.Reflection;

namespace Products.Persistence
{
    static class PersistenceConfig
    {
        #region "实体分组"
        public static readonly ReadOnlyDictionary<TableKind, string> TableKinds = new ReadOnlyDictionary<TableKind, string>(
            new Dictionary<TableKind, string>() {
            { TableKind.StaticConfig, "StaticConfigEntityNames" },
            { TableKind.DynamicConfig, "DynamicConfigEntityNames" },
            { TableKind.Log, "LogTableEntityNames" },
        });
        #endregion

        #region "Field"

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
        /// 获取所有 TableDescriptors。
        /// <para>KEY= 实体类型。</para>
        /// </summary>
        public static ReadOnlyDictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

        /// <summary>
        /// 获取所有 DataSource。
        /// <para>Key = DataSource.Name.</para>
        /// </summary>
        public static Dictionary<string, DataSource> DataSources { get; private set; } = new Dictionary<string, DataSource>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 静态构造函数。
        /// </summary>
        static PersistenceConfig()
        {
            // Initialize Settings.
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", HelperTools.CurrentDllPath);
            Settings = SettingsManager.GetXmlSettings(cfgPath);

            // 创建表描述符。
            CreateTableDescriptor();

            // 构建 DataSources。
            CreateDataSource();
        }
        #endregion

        #region "Private methods"

        private static void CreateTableDescriptor()
        {
            var result = new Dictionary<Type, TableDescriptor>();

            // 构建表描述符。
            TableKinds.ForEach(p =>
            {
                var textName = Settings.Get<string>(p.Value);

                HelperTools.SplitTableNames(textName).ForEach(name =>
                {
                    var entityType = ConvertToEntityType(name);
                    var tableName = ConvertToTableName(entityType);

                    if (result.ContainsKey(entityType))
                        throw new ArgumentException(string.Format("{0} 重复配置。", name));

                    result[entityType] = new TableDescriptor { EntityType = entityType, Name = tableName, TableKind = p.Key };
                });
            });

            TableDescriptors = new ReadOnlyDictionary<Type, TableDescriptor>(result);
        }

        private static void CreateDataSource()
        {
            DataSources = Settings.Get<List<DataSource>>("DataSources").ToDictionary(p => p.Name, q => q);
            DataSources.Values.ForEach(p =>
            {
                p.Entities.Split(new char[] { ',', '，', ';', '；' }, StringSplitOptions.RemoveEmptyEntries).ForEach(q =>
                {
                    var entityType = ConvertToEntityType(q.Trim());

                    if (!TableDescriptors.ContainsKey(entityType)) throw new Exception(string.Format("没有找到 {0} 的 TableDescriptor。", entityType.Name));
                    p.TableDescriptors[entityType] = TableDescriptors[entityType];
                });
            });
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

        public static void Initialize(bool remoteDbEnabled)
        {
        }

        public static void Close()
        {
            DbConfiguration.Shutdown();
        }

        public static DbConfiguration GetOrCreateDbConfiguration(string dbSourceName, bool validateSchema)
        {
            if (!Acl.Data.Configuration.DbConfiguration.Items.TryGetValue(dbSourceName, out DbConfiguration cfg))
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
                    var dataSrc = DataSources.Values.Where(p => p.Name == dbSourceName).FirstOrDefault();
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
                if (DataSources.ContainsKey(dbSourceName))
                {
                    DataSources[dbSourceName].TableDescriptors.ForEach(p => cfg.ModelBuilder.AddClass(p.Value.EntityType));
                }

                // 验证Schema
                if (validateSchema) cfg.ModelBuilder.ValidateSchema();
            }

            return cfg;
        }

        public static bool IsStaticConfigTable(Type entityType)
        {
            TableDescriptors.TryGetValue(entityType, out TableDescriptor value);

            return value != null && value.TableKind == TableKind.StaticConfig;
        }

        public static bool IsDynamicConfigTable(Type entityType)
        {
            TableDescriptors.TryGetValue(entityType, out TableDescriptor value);

            return value != null && value.TableKind == TableKind.DynamicConfig;
        }

        public static bool IsNormalLogTable(Type entityType)
        {
            TableDescriptors.TryGetValue(entityType, out TableDescriptor value);

            return value != null && value.TableKind == TableKind.Log;
        }

        public static bool IsRemoteDatabase(DataBaseType dbType)
        {
            return dbType == DataBaseType.Oracle || dbType == DataBaseType.MySql || dbType == DataBaseType.SqlServer;
        }

        /// <summary>
        /// 根据实体类型，获取 DataSource。
        /// </summary>
        public static DataSource GetDataSource(Type entityType)
        {
            return DataSources.Values.Where(p => p.TableDescriptors.Keys.Contains(entityType)).FirstOrDefault();
        }

        public static IEnumerable<DataSource> GetDataSources(DataBaseType dbType)
        {
            return DataSources.Values.Where(p => (DataBaseType)p.DbType == dbType);
        }

        public static IEnumerable<DataSource> GetDataSources()
        {
            return DataSources.Values;
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

        public static TableDescriptor GetTableDescriptor(Type entityType)
        {
            return GetTableDescriptor(entityType.Name);
        }
        public static TableDescriptor GetTableDescriptor(string entityName)
        {
            return TableDescriptors.Values.Where(p => p.EntityType.Name == entityName).FirstOrDefault();
        }
        public static Type GetEntityType(string entityName)
        {
            var desc = TableDescriptors.Values.Where(p => p.EntityType.Name == entityName).FirstOrDefault();
            return desc == null ? null : desc.EntityType;
        }
        /// <summary>
        /// 获取指定种类的表描述符。
        /// </summary>
        public static IEnumerable<TableDescriptor> GetTableDescriptors(TableKind tableKind)
        {
            return TableDescriptors.Values.Where(p => p.TableKind == tableKind);
        }
        public static string GetTableName(Type entityType)
        {

            if (TableDescriptors.TryGetValue(entityType, out TableDescriptor value)) return value.Name;

            return null;
        }

        /// <summary>
        /// 获取数据库与实体的映射。
        /// Key：Data Source Name。
        /// Value：数据库中包含的实体类型集合。
        /// </summary>
        public static Dictionary<string, List<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType)
        {
            return DataSources.Values.Where(p => (DataBaseType)p.DbType == dbType)
                .ToDictionary(p => p.Name, q => q.TableDescriptors.Values.Select(k => k.EntityType).ToList());
        }

        /// <summary>
        /// 根据数据库类型与表的种类获取DataSourceName与实体类型的映射关系。
        /// </summary>
        /// <returns>一个字典对象，Key表示DataSourceName，Value表示实体类型集合。</returns>
        public static Dictionary<string, IEnumerable<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType, TableKind tableKind)
        {
            // 获取指定种类的表的类型。
            var theTableTypes = TableDescriptors.Values.Where(p => p.TableKind == tableKind).Select(p => p.EntityType);

            // 获取指定数据类类型的映射。
            var sqliteSrcNames = DataSources.Values.Where(p => (DataBaseType)p.DbType == dbType).Select(p => p.Name);
            var theMapping = DataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k => k.Value.EntityType));

            // 构建 DataSourceName 与 Entity 的映射。
            return theMapping.Where(p => p.Value.Intersect(theTableTypes).Any()).ToDictionary(p => p.Key, q => q.Value.Intersect(theTableTypes));
        }
        #endregion

    }
}
