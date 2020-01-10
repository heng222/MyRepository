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
        private static Dictionary<string, DataSource> _dataSources = new Dictionary<string, DataSource>();

        /// <summary>
        /// TextRepository ������ʵ�塣
        /// </summary>
        private static readonly List<Type> _textRepositoryEntityMapping = new List<Type>() { typeof(IoDriverPoint), typeof(IoCollectionPoint) };

        /// <summary>
        /// ��ȡ������Entity type ��ʽ������"Products.Infrastructure.Entities.{0},Products.Infrastructure"
        /// </summary>
        private static readonly string EntityTypeFormat = HelperTools.BuildEntityFormat();
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡPersistence Settings��
        /// </summary>
        public static ISettings Settings { get; private set; }

        /// <summary>
        /// ��ȡ TableDescriptors��
        /// </summary>
        public static Dictionary<Type, TableDescriptor> TableDescriptors
        {
            get 
            {
                return _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).ToDictionary(p => p.EntityType, q => q); 
            } 
        }

        /// <summary>
        /// ��ȡԶ��DB���á�
        /// </summary>
        public static DbConfiguration RemoteConfiguration { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// ��̬���캯����
        /// </summary>
        static PersistenceConfig()
        {
            // Initialize Settings.
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Settings = SettingsManager.GetXmlSettings(cfgPath);

            InitializeDataSource();

            // ����Զ�����ݿ�����
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
                var entityNames = p.Value.Entities.Split(new char[] { ',', '��', ';', '��' }, StringSplitOptions.RemoveEmptyEntries);
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

            // ������̬���ñ����������
            var entityNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, staticCfgEntityNames, TableType.StaticConfig);

            // ������̬���ñ����������
            entityNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, dynamicCfgEntityNames, TableType.DynamicConfig);

            // ������־�����������
            entityNames = Settings.Get<string>(PersistenceConfig.LogEntities);
            var logEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(tableDescriptors, logEntityNames, TableType.Log);

            // ����DataSource������ TableDescriptors
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

            if (type == null) throw new TypeLoadException(string.Format("���ܽ������������� {0}��", typeName));

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
        /// ָ���������Ƿ�洢���ı��ļ��У�
        /// </summary>
        public static bool IsTextData(Type entityType)
        {
            return _textRepositoryEntityMapping.Contains(entityType);
        }

        /// <summary>
        /// ��ȡָ�����ݿ����͵�DataSourceName�뾲̬���ӳ���ϵ��
        /// </summary>
        /// <returns>һ���ֵ����Key��ʾ��̬���Ӧ��DataSourceName��Value��ʾ��̬ʵ�����ͼ��ϡ�</returns>
        public static Dictionary<string, List<Type>> GetStaticTableTypes(DataBaseType dbType)
        {
            var result = new Dictionary<string, List<Type>>();

            // ��ȡ���о�̬����������
            var staticTableDescriptors = _dataSources.Values.SelectMany(p => p.TableDescriptors.Values).Where(p=>p.TableType == TableType.StaticConfig);

            // ��ȡָ�����������͵�ӳ�䡣
            var sqliteSrcNames = _dataSources.Where(p => (DataBaseType)p.Value.DbType == dbType).Select(p => p.Value.Name);
            var theMapping = _dataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k=>k.Value.EntityType));

            // ���� DataSourceName �� Entity ��ӳ�䡣
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
        /// ��ȡSQLite���ݿ���ʵ���ӳ�䡣
        /// Key��Data Source Name��
        /// Value��SQLite���ݿ��а�����ʵ�����ͼ��ϡ�
        /// </summary>
        public static Dictionary<string, List<Type>> GetSqliteDataSourceEntityMapping()
        {
            return _dataSources.Values.Where(p => (DataBaseType)p.DbType == DataBaseType.Sqlite)
                .ToDictionary(p => p.Name, q => q.TableDescriptors.Values.Select(k => k.EntityType).ToList());
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

        /// <summary>
        /// ��ȡָ��ʵ���������ڵ����ݿ����͡�
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
