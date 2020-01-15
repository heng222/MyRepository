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
        public static Dictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

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
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location));
            Settings = SettingsManager.GetXmlSettings(cfgPath);
            
            InitializeDataSource();

            // ����Զ�����ݿ�����
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
                var entityNames = p.Value.Entities.Split(new char[] { ',', '��', ';', '��' }, StringSplitOptions.RemoveEmptyEntries);
                entityNames.ForEach(q =>
                {
                    var entityType = ConvertToEntityType(q.Trim());

                    if (!TableDescriptors.ContainsKey(entityType)) throw new Exception(string.Format("û���ҵ� {0} �� TableDescriptor��", entityType.Name));
                    p.Value.TableDescriptors[entityType] = TableDescriptors[entityType];
                });
            });
        }

        private static void CreateTableDescriptors()
        {
            TableDescriptors = new Dictionary<Type, TableDescriptor>();

            // ������̬���ñ����������
            var entityNames = Settings.Get<string>(PersistenceConfig.StaticConfigEntities);
            var staticCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(TableDescriptors, staticCfgEntityNames, TableKind.StaticConfig);

            // ������̬���ñ����������
            entityNames = Settings.Get<string>(PersistenceConfig.DynamicConfigEntities);
            var dynamicCfgEntityNames = HelperTools.SplitTableNames(entityNames);
            CreateTableDescriptor(TableDescriptors, dynamicCfgEntityNames, TableKind.DynamicConfig);

            // ������־�����������
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
                    throw new ArgumentException(string.Format("{0} �ظ����á�", newValue.EntityType.Name));

                descriptors[newValue.EntityType] = newValue;
            }
        }

        private static Type ConvertToEntityType(string entityName)
        {
            var typeName = string.Format(EntityTypeFormat, entityName);
            var type = System.Type.GetType(typeName);

            if (type == null) throw new TypeLoadException(string.Format("���ܽ������������� {0}��", typeName));

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
        /// ��ȡָ��ʵ�����ڵ����ݿ����͡�
        /// </summary>
        public static DataBaseType GetDatabaseType(Type entityType)
        {
            var theDataSource = GetDataSource(entityType);

            return theDataSource != null ? (DataBaseType)theDataSource.DbType : DataBaseType.None;
        }

        /// <summary>
        /// ����ʵ�����ͣ���ȡ DataSource��
        /// </summary>
        public static DataSource GetDataSource(Type entityType)
        {
            return _dataSources.Values.Where(p => p.TableDescriptors.Values.Select(k => k.EntityType).Contains(entityType)).FirstOrDefault();
        }
        
        /// <summary>
        /// ����ʵ�����������ݿ����ͻ�ȡDataSourceName��
        /// </summary>
        public static string GetDataSourceName(Type entityType, DataBaseType dbType)
        {
            var sqliteSrcNameEntityMapping = GetDataSrcNameEntityMapping(dbType);

            return sqliteSrcNameEntityMapping.Where(p => p.Value.Contains(entityType)).FirstOrDefault().Key;
        }
        /// <summary>
        /// �������ݿ����ͣ���ȡDataSourceName��
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
        /// ��ȡָ������ı���������
        /// </summary>
        public static IEnumerable<TableDescriptor> GetTableDescriptors(TableKind tableKind)
        {
            return TableDescriptors.Values.Where(p => p.TableKind == tableKind);
        }

        /// <summary>
        /// ��ȡ���ݿ���ʵ���ӳ�䡣
        /// Key��Data Source Name��
        /// Value�����ݿ��а�����ʵ�����ͼ��ϡ�
        /// </summary>
        public static Dictionary<string, List<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType)
        {
            return _dataSources.Values.Where(p => (DataBaseType)p.DbType == dbType)
                .ToDictionary(p => p.Name, q => q.TableDescriptors.Values.Select(k => k.EntityType).ToList());
        }

        /// <summary>
        /// �������ݿ��������������ȡDataSourceName��ʵ�����͵�ӳ���ϵ��
        /// </summary>
        /// <returns>һ���ֵ����Key��ʾDataSourceName��Value��ʾʵ�����ͼ��ϡ�</returns>
        public static Dictionary<string, List<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType, TableKind tableKind)
        {
            var result = new Dictionary<string, List<Type>>();

            // ��ȡָ������ı����������
            var staticTableDescriptors = TableDescriptors.Values.Where(p => p.TableKind == tableKind);

            // ��ȡָ�����������͵�ӳ�䡣
            var sqliteSrcNames = _dataSources.Where(p => (DataBaseType)p.Value.DbType == dbType).Select(p => p.Value.Name);
            var theMapping = _dataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k => k.Value.EntityType));

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
        #endregion

    }
}
