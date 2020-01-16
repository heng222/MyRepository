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
        //private List<IoCollectionPoint> _ioCollectionPoints = new List<IoCollectionPoint>();

        /// <summary>
        /// Key = ʵ�����͡�
        /// </summary>
        private Dictionary<Type, IQueryable> _mapping = new Dictionary<Type, IQueryable>();

        /// <summary>
        /// KEY=ʵ�����ͣ�Value=�����ļ�·����
        /// </summary>
        private Dictionary<Type, string> _csvFiles;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="csvFiles">KEY=ʵ�����ͣ�Value=�����ļ�·����</param>
        public CsvFileRepository(IDictionary<Type, string> csvFiles)
        {
            _csvFiles = new Dictionary<Type, string>(csvFiles);
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"

        protected override void OnOpen()
        {
            this.ReadCsvFiles(_csvFiles);
        }
        #endregion

        #region "Private methods"

        private void ReadCsvFiles(IDictionary<Type, string> csvFiles)
        {
            //var csvSettings = new CsvSettings { Delimiter = "\t", HasHeader = true };

            csvFiles.ForEach(p =>
            {
                //_ioCollectionPoints = CsvFile.Query<IoCollectionPoint>(p.Value, null, csvSettings).ToList();
                //_mapping[p.Key] = _ioCollectionPoints.AsQueryable(); // TODO
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
