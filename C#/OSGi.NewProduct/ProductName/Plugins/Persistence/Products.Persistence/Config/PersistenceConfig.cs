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
        #region "���ݿ������ַ���"
        public const string DataSourceRemoteDbName = "RemoteDatabase";
        #endregion

        #region "ʵ�����ͷ���"
        public const string StaticConfigEntities = "StaticConfigEntityNames";
        public const string DynamicConfigEntities = "DynamicConfigEntityNames";
        public const string LogEntities = "LogTableEntityNames";
        #endregion

        #region "Field"
        /// <summary>
        /// DataSource ���ϡ�
        /// </summary>
        private static List<DataSource> _dataSources;

        /// <summary>
        /// TextRepository ������ʵ�塣
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// DataSourceName �� Entity ��ӳ�䡣
        /// Key = Data source name.
        /// Value = DataSource������ʵ�塣
        /// </summary>
        private static Dictionary<string, List<Type>> _srcNameEntityMapping = new Dictionary<string, List<Type>>();

        /// <summary>
        /// ��ȡ������Entity type ��ʽ������"Products.Infrastructure.Entities.{0},Products.Infrastructure"
        /// </summary>
        private static readonly string EntityTypeFormat = HelperTools.BuildEntityFormat();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ��̬���캯����
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
        /// ��ȡPersistence Settings��
        /// </summary>
        public static ISettings Settings { get; private set; }

        /// <summary>
        /// ��ȡ Table ����������
        /// </summary>
        public static Dictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

        /// <summary>
        /// ��ȡԶ��DB���á�
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

                var tableNames = p.Entities.Split(new char[] { ',', '��', ';', '��' }, StringSplitOptions.RemoveEmptyEntries);
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
                    throw new ArgumentException(string.Format("{0} �ظ����á�", newValue.EntityType.Name));

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
            // ������̬���ñ����������
            var tablesNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, staticTables, TableType.StaticConfig);

            // ������̬���ñ����������
            tablesNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgTables, TableType.DynamicConfig);

            // ������־�����������
            tablesNames = Settings.Get<string>(PersistenceConfig.LogEntities);
            var logTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, logTables, TableType.Log);

            // ����Զ�����ݿ�����
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
                // ��ȡ exe.config �е������ַ�����
                var connectSettings = ConfigurationManager.ConnectionStrings.OfType<ConnectionStringSettings>()
                    .Where(p => p.Name == dbSourceName).FirstOrDefault();

                if (connectSettings != null)
                {
                    cfg = DbConfiguration.Configure(dbSourceName);
                }
                else
                {
                    var dataSrc = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").Where(p => p.Name == dbSourceName).FirstOrDefault();
                    if (dataSrc == null) throw new Exception(string.Format("û���ҵ� DataSource={0} ������ ��", dbSourceName));

                    var urlFixed = dataSrc.Url;
                    if (dataSrc.Driver.Contains("SQLite"))
                    {
                        urlFixed = HelperTools.FixSQLiteDbUrl(dataSrc.Url);
                    }
                    cfg = DbConfiguration.Configure(urlFixed, dataSrc.Driver, dbSourceName);
                }

                // ���ñ�����������
                cfg.SetMappingConversion(MappingConversion.Plural);

                // ���DB��ӳ�䡣
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

            if (type == null) throw new TypeLoadException(string.Format("���ܽ������������� {0}��", typeName));

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
        /// ָ���������Ƿ�洢���ı��ļ��У�
        /// </summary>
        public static bool IsTextData(Type entityType)
        {
            return _textRepositoryEntityMapping.Contains(entityType);
        }

        /// <summary>
        /// ��ȡָ�����ݿ����͵�DataSourceName�뾲̬���ӳ���ϵ��
        /// </summary>
        /// <returns>һ���ֵ����Key��ʾ��̬���Ӧ��DataSourceName��Value��ʾ��̬�����ͼ��ϡ�</returns>
        public static Dictionary<string, List<Type>> GetStaticTableTypes(DataBaseType dbType)
        {
            var result = new Dictionary<string, List<Type>>();

            // ��ȡ���о�̬����������
            var allStaticTables = TableDescriptors.Values.Where(p => p.TableType == TableType.StaticConfig);

            // ��ȡָ�����������͵�ӳ�䡣
            var sqliteDbSrc = _dataSources.Where(p => (DataBaseType)p.DbType == dbType).Select(p => p.Name);
            var theMapping = _srcNameEntityMapping.Where(p => sqliteDbSrc.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value);

            // ����DataSourceName�� Entity ��ӳ�䡣
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
        /// ��ȡSQLite���ݿ���ʵ���ӳ�䡣
        /// Key��Data Source Name��
        /// Value��SQLite���ݿ��а�����ʵ�����ͼ��ϡ�
        /// </summary>
        public static Dictionary<string, List<Type>> GetSqliteDataSourceEntityMapping()
        {
            var sqliteDbSrc = _dataSources.Where(p => (DataBaseType)p.DbType == DataBaseType.Sqlite).Select(p => p.Name);

            return _srcNameEntityMapping.Where(p => sqliteDbSrc.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value);
        }

        /// <summary>
        /// ��ȡ����Sqlite���ݿ��DataSourceName��
        /// </summary>
        public static List<string> GetSqliteDataSourceNames()
        {
            var sqliteSrcNameEntityMapping = GetSqliteDataSourceEntityMapping();

            return sqliteSrcNameEntityMapping.Keys.ToList();
        }

        /// <summary>
        /// ��ȡָ��ʵ���������ڵ�SQLite���ݿ�DataSourceName��
        /// </summary>
        public static string GetSqliteDataSourceName(Type entityType)
        {
            var sqliteSrcNameEntityMapping = GetSqliteDataSourceEntityMapping();

            return sqliteSrcNameEntityMapping.Where(p => p.Value.Contains(entityType)).FirstOrDefault().Key;
        }

        #endregion

    }
}
