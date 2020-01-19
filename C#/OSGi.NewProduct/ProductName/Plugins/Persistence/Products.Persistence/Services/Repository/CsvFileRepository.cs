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
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Text;
using Acl.Data.Csv;
using Acl.Data.Mappings;
using Products.Domain.Preferences;
using Products.Infrastructure.Entities;
using Products.Persistence.Services.Repository;

namespace Products.Persistence.Implementation
{
    /// <summary>
    /// ����CSV�ļ������ݴ洢��
    /// </summary>
    class CsvFileRepository : RepositoryImpl
    {
        #region "Field"

        private static MethodInfo _asQueryableMethodInfo = typeof(Queryable).GetMethods().FirstOrDefault(p => p.Name == "AsQueryable" && p.IsGenericMethod);

        private static MethodInfo _csvQueryMethodInfo = typeof(CsvFile).GetMethod("Query", new Type[] { typeof(string), typeof(ColumnMappingBuilder), typeof(CsvSettings) });

        /// <summary>
        /// Key = ʵ�����͡�
        /// </summary>
        private Dictionary<Type, IQueryable> _mapping = new Dictionary<Type, IQueryable>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public CsvFileRepository()
        {
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"

        protected override void OnOpen()
        {
            var csvFiles = this.BuildCsvDbPath();
            this.ReadCsvFiles(csvFiles);
        }
        #endregion

        #region "Private methods"

        /// <summary>
        /// ����CSV����·����
        /// </summary>
        private Dictionary<Type, string> BuildCsvDbPath()
        {
            var csvFiles = new Dictionary<Type, string>();

            PersistenceConfig.GetDataSources(DataBaseType.CSV).ForEach(p =>
            {
                var paths = p.Url.Split(new string[] { ";", "��" }, StringSplitOptions.RemoveEmptyEntries).Where(q => !string.IsNullOrWhiteSpace(q));
                var count = p.TableDescriptors.Keys.Count;

                if (count != paths.Count())
                {
                    throw new Exception(string.Format("CSV��������ʵ���������ļ�������һ�¡�"));
                }

                for (int i = 0; i < count; i++)
                {
                    var type = p.TableDescriptors.Keys.ElementAt(i);
                    csvFiles[type] = string.Format(@"{0}\{1}", HelperTools.CurrentDllPath, paths.ElementAt(i).Trim());
                }
            });

            return csvFiles;
        }

        private void ReadCsvFiles(IDictionary<Type, string> csvFiles)
        {
            var csvSettings = new CsvSettings { HasHeader = true, IgoreWhiteSpace = true };

            csvFiles.ForEach(p =>
            {
                if (!File.Exists(p.Value)) throw new Exception(string.Format("û���ҵ��ļ� {0}��", p.Value));

                var list = _csvQueryMethodInfo.MakeGenericMethod(p.Key).Invoke(null, new object[] { p.Value, null, csvSettings });
                var queryable = (IQueryable)_asQueryableMethodInfo.MakeGenericMethod(p.Key).Invoke(null, new object[] { list });
                _mapping[p.Key] = queryable;
            });
        }
        #endregion

        #region "Public methods"

        public override uint NextSequence<T>()
        {
            throw new NotImplementedException();
        }

        public override IList<T> Where<T>(Expression<Func<T, bool>> predicate = null)
        {
            var typeT = typeof(T);
            IQueryable theValue = null;

            var flag = _mapping.TryGetValue(typeT, out theValue);
            if (!flag) return new List<T>();

            // 
            if (predicate == null)
            {
                return (theValue as IQueryable<T>).ToList();
            }
            else
            {
                return (theValue as IQueryable<T>).Where(predicate).ToList();
                //return theList.OfType<T>().AsQueryable<T>().Where(predicate).ToList();
            }
        }

        public override IList<T> Where<T>(string sql, object namedParameters = null)
        {
            throw new NotImplementedException();
        }

        public override void Insert<T>(params T[] entities)
        {
            throw new NotImplementedException();
        }

        public override void AsyncInsert<T>(T[] entities, Action<Exception> exceptionHandler = null)
        {
            throw new NotImplementedException();
        }

        public override void Update<T>(object instance, Expression<Func<T, bool>> predicate)
        {
            throw new NotImplementedException();
        }

        public override void Delete<T>(Expression<Func<T, bool>> predicate = null)
        {
            throw new NotImplementedException();
        }

        public override void Execute<T>(Action<Acl.Data.IDatabase> handler)
        {
            throw new NotImplementedException();
        }

        public override void AsyncExecute<T>(Action<Acl.Data.IDatabase> handler, Action<Exception> errorHandler)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
