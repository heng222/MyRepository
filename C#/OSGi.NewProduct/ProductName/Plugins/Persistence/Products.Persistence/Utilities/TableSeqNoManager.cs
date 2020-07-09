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
using System.Linq;

using Acl.Data;

using Products.Infrastructure.Entities;

namespace Products.Persistence.Services
{
    abstract class SeqNoGenerator
    {
        public uint SeqNo { get; set; }

        abstract public uint Next();
    }

    class SeqNoGenerator<TEntity> : SeqNoGenerator where TEntity : Entity
    {
        public SeqNoGenerator(IDatabase db)
        {
            this.SeqNo = this.GetMaxCode(db);
        }

        private uint GetMaxCode(IDatabase db)
        {
            var tableName = PersistenceConfig.GetTableName<TEntity>();

            var sql = string.Format(@"select Max(code) from {0}", db.Dialect.Quote(tableName));

            return db.ExecuteScalar<uint>(sql);
        }

        /// <summary>
        /// 获取下个序列值
        /// </summary>
        /// <returns></returns>
        public override uint Next()
        {
            SeqNo++;

            if (SeqNo == 0) SeqNo++; // 编号从1开始。

            return SeqNo;
        }
    }

    /// <summary>
    /// 一个序列号管理器，用于管理数据库表自然主键。
    /// </summary>
    class TableSeqNoManager
    {
        #region "Field"
        private Dictionary<RuntimeTypeHandle, SeqNoGenerator> _seqInfo = new Dictionary<RuntimeTypeHandle, SeqNoGenerator>();
        private object _seqInfoLock = new object();
        #endregion


        #region "Public methods"

        public bool Contains(Type entityType)
        {
            return _seqInfo.Keys.Contains(entityType.TypeHandle);
        }

        public uint Next<T>() where T : Entity
        {
            if (!this.Contains(typeof(T)))
            {
                throw new InvalidOperationException();
            }

            _seqInfo.TryGetValue(typeof(T).TypeHandle, out SeqNoGenerator value);
            return value.Next();
        }

        public uint Next<T>(IDatabase db) where T : Entity
        {
            var isExist = _seqInfo.TryGetValue(typeof(T).TypeHandle, out SeqNoGenerator value); ;

            if (!isExist)
            {
                value = new SeqNoGenerator<T>(db);
                lock (_seqInfoLock)
                {
                    _seqInfo[typeof(T).TypeHandle] = value;
                }
            }

            return value.Next();
        }
        #endregion
    }
}
