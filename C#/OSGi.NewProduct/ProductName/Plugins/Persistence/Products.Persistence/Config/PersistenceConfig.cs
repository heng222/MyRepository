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
        /// TextRepository �����ı�
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// SQLite���ݿ� DataSourceName �� Entity ӳ�䡣
        /// Key = Data source name.
        /// Value = DataSource�����ı�
        /// </summary>
        private static Dictionary<string, List<Type>> _sqliteDbEntityMapping = new Dictionary<string, List<Type>>();

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
            
            InitializeDbEntityMapping();
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡPersistence Settings��
        /// </summary>
        public static ISettings Settings { get; private set; }

        /// <summary>
        /// ��ȡSQLite���ݿ���ʵ���ӳ�䡣
        /// Key��Data Source Name��
        /// Value��type of Entity.
        /// </summary>
        public static Dictionary<string, List<Type>> SqliteDbEntityMapping { get { return _sqliteDbEntityMapping; } }

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

        private static void InitializeDbEntityMapping()
        {
            var dataSrcList = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToList();
            dataSrcList.ForEach(p =>
            {
                if (p.Driver.IndexOf("SQLite", StringComparison.OrdinalIgnoreCase) != -1)
                {
                    var tableTypes = new List<Type>();

                    var tableNames = p.Tables.Split(new char[] { ',', '��', ';', '��' }, StringSplitOptions.RemoveEmptyEntries);
                    tableNames.ToList().ForEach(q => tableTypes.Add(ConvertToEntityType(q.Trim())));

                    _sqliteDbEntityMapping[p.Name] = tableTypes;
                }
            });
        }

        private static DbConfiguration CreateDbConfiguration(string dbName)
        {
            // ��ȡ exe.config �е������ַ�����
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
                if (dataSrc == null) throw new Exception(string.Format("û���ҵ� DataSource={0} ������ ��", dbName));

                var urlFixed = dataSrc.Url;
                if (dataSrc.Driver.Contains("SQLite"))
                {
                    urlFixed = HelperTools.FixSQLiteDbUrl(dataSrc.Url);
                }
                cfg = DbConfiguration.Configure(urlFixed, dataSrc.Driver, dbName);
            }

            // ���ñ�����������
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
                    throw new ArgumentException(string.Format("{0} �ظ����á�", newValue.EntityType.Name));

                descriptors[newValue.EntityType] = newValue;
            }
        }

        #endregion

        #region "Public methods"

        public static void Initialize()
        {
            // ����Զ�����ݿ�����
            RemoteConfiguration = CreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName);

            // ������̬���ñ����������
            var tablesNames = Settings.Get<string>(PersistenceConfig.StaticConfigTables);
            var staticTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, staticTables, TableType.StaticConfig);

            // ������̬���ñ����������
            tablesNames = Settings.Get<string>(PersistenceConfig.DynamicConfigTables);
            var dynamicCfgTables = HelperTools.SplitTableNames(tablesNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgTables, TableType.DynamicConfig);

            // ������־�����������
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

            if (type == null) throw new TypeLoadException(string.Format("���ܽ������������� {0}��", typeName));

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
        /// ָ���������Ƿ�洢���ı��ļ��У�
        /// </summary>
        public static bool IsTextData(Type entityType)
        {
            return _textRepositoryEntityMapping.Contains(entityType);
        }
        
        /// <summary>
        /// ��ȡ���о�̬����Ϣ��
        /// </summary>
        /// <returns>һ���ֵ����Key��ʾ��̬���Ӧ��DataSource��Value��ʾ��̬���ϡ�</returns>
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
        /// ��ȡ����Sqlite���ݿ��DataSourceName��
        /// </summary>
        public static List<string> GetSqliteDataSourceNames()
        {
            return _sqliteDbEntityMapping.Keys.ToList();
        }

        /// <summary>
        /// ��ȡָ��ʵ���������ڵ�SQLite���ݿ�DataSourceName��
        /// </summary>
        public static string GetSqliteDataSourceName(Type entityType)
        {
            var theItem = _sqliteDbEntityMapping.Where(p => p.Value.Contains(entityType));

            return theItem.Count() > 0 ? theItem.First().Key : PersistenceConfig.DataSourceSqliteDb4StaticConfig;            
        }

        #endregion

    }
}
