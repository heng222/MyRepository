/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        #region "���ݿ������ַ���"
        public const string DataSourceRemoteDbName = "RemoteDatabase";
        #endregion

        #region "ʵ�����"
        public static readonly ReadOnlyDictionary<TableKind, string> TableKinds = new ReadOnlyDictionary<TableKind, string>(
            new Dictionary<TableKind, string>() {
            { TableKind.StaticConfig, "StaticConfigEntityNames" },
            { TableKind.DynamicConfig, "DynamicConfigEntityNames" },
            { TableKind.Log, "LogTableEntityNames" },
        });
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
        public static ReadOnlyDictionary<Type, TableDescriptor> TableDescriptors { get; private set; }

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
            var cfgPath = string.Format(@"{0}\Config\Persistence.config", HelperTools.CurrentDllPath);
            Settings = SettingsManager.GetXmlSettings(cfgPath);

            InitializeDataSource();
        }
        #endregion

        #region "Private methods"


        private static void InitializeDataSource()
        {
            // ��������������
            CreateTableDescriptors();

            // ���� DataSources��
            _dataSources = PersistenceConfig.Settings.Get<List<DataSource>>("DataSources").ToDictionary(p => p.Name, q => q);
            _dataSources.Values.ForEach(p =>
            {
                p.Entities.Split(new char[] { ',', '��', ';', '��' }, StringSplitOptions.RemoveEmptyEntries).ForEach(q =>
                {
                    var entityType = ConvertToEntityType(q.Trim());

                    if (!TableDescriptors.ContainsKey(entityType)) throw new Exception(string.Format("û���ҵ� {0} �� TableDescriptor��", entityType.Name));
                    p.TableDescriptors[entityType] = TableDescriptors[entityType];
                });
            });
        }

        private static void CreateTableDescriptors()
        {
            var result = new Dictionary<Type, TableDescriptor>();

            // ��������������
            TableKinds.ForEach(p =>
            {
                var textName = Settings.Get<string>(p.Value);

                HelperTools.SplitTableNames(textName).ForEach(name =>
                {
                    var entityType = ConvertToEntityType(name);
                    var tableName = ConvertToTableName(entityType);

                    if (result.ContainsKey(entityType))
                        throw new ArgumentException(string.Format("{0} �ظ����á�", name));

                    result[entityType] = new TableDescriptor { EntityType = entityType, Name = tableName, TableKind = p.Key };
                });
            });

            TableDescriptors = new ReadOnlyDictionary<Type, TableDescriptor>(result);
        }

        private static void InitDbConfiguration(bool enableRemoteDb)
        {
            if (enableRemoteDb) RemoteConfiguration = GetOrCreateDbConfiguration(PersistenceConfig.DataSourceRemoteDbName, false);
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

        public static void Initialize(bool remoteDbEnabled)
        {
            InitDbConfiguration(remoteDbEnabled);
        }

        public static void Close()
        {
            DbConfiguration.Items.ToList().ForEach(p => p.Value.ClearPools());
        }

        public static DbConfiguration GetOrCreateDbConfiguration(string dbSourceName, bool validateSchema)
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

                // ��֤Schema
                if (validateSchema) cfg.ModelBuilder.ValidateSchema();
            }

            return cfg;
        }

        public static bool IsStaticConfigTable<T>()
        {
            return IsStaticConfigTable(typeof(T));
        }
        public static bool IsStaticConfigTable(Type entityType)
        {
            TableDescriptor value = null;
            if (TableDescriptors.TryGetValue(entityType, out value))
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

        public static bool IsRemoteDatabase(DataBaseType dbType)
        {
            return dbType == DataBaseType.Oracle || dbType == DataBaseType.MySql || dbType == DataBaseType.SqlServer;
        }

        /// <summary>
        /// ����ʵ�����ͣ���ȡ DataSource��
        /// </summary>
        public static DataSource GetDataSource(Type entityType)
        {
            return _dataSources.Values.Where(p => p.TableDescriptors.Values.Select(k => k.EntityType).Contains(entityType)).FirstOrDefault();
        }

        public static IEnumerable<DataSource> GetDataSources(DataBaseType dbType)
        {
            return _dataSources.Values.Where(p => (DataBaseType)p.DbType == dbType);
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
        public static Type GetEntityType(string entityName) {
            var desc = TableDescriptors.Values.Where(p => p.EntityType.Name == entityName).FirstOrDefault();
            return desc == null ? null : desc.EntityType;
        }
        /// <summary>
        /// ��ȡָ������ı���������
        /// </summary>
        public static IEnumerable<TableDescriptor> GetTableDescriptors(TableKind tableKind)
        {
            return TableDescriptors.Values.Where(p => p.TableKind == tableKind);
        }
        public static string GetTableName<T>()
        {
            return GetTableName(typeof(T));
        }
        public static string GetTableName(Type entityType)
        {
            TableDescriptor value;

            if (TableDescriptors.TryGetValue(entityType, out value)) return value.Name;

            return null;
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
        public static Dictionary<string, IEnumerable<Type>> GetDataSrcNameEntityMapping(DataBaseType dbType, TableKind tableKind)
        {
            // ��ȡָ������ı�����͡�
            var theTableTypes = TableDescriptors.Values.Where(p => p.TableKind == tableKind).Select(p => p.EntityType);

            // ��ȡָ�����������͵�ӳ�䡣
            var sqliteSrcNames = _dataSources.Values.Where(p => (DataBaseType)p.DbType == dbType).Select(p => p.Name);
            var theMapping = _dataSources.Where(p => sqliteSrcNames.Contains(p.Key)).ToDictionary(p => p.Key, q => q.Value.TableDescriptors.Select(k => k.Value.EntityType));

            // ���� DataSourceName �� Entity ��ӳ�䡣
            return theMapping.Where(p => p.Value.Intersect(theTableTypes).Any()).ToDictionary(p => p.Key, q => q.Value.Intersect(theTableTypes));
        }
        #endregion

    }
}
