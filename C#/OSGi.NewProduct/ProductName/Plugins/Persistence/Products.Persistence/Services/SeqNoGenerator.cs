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
using System.Linq;
using System.Text;
using Acl.Data;
using Products.Infrastructure.Entities;

namespace Products.Persistence.Services
{
    class SeqNoGenerator
    {
        #region class SequenceInfo
        class SequenceInfo
        {
            public string Name { get; private set; }
            public uint SeqNo { get; set; }

            public SequenceInfo(string name, uint initValue)
            {
                Name = name;
                SeqNo = initValue;
            }

            /// <summary>
            /// 获取下个序列值
            /// </summary>
            /// <returns></returns>
            public uint Next()
            {
                SeqNo++;

                if (SeqNo == 0) SeqNo++; // 编号从1开始。

                return SeqNo;
            }
        }
        #endregion

        #region "Field"
        private Dictionary<RuntimeTypeHandle, SequenceInfo> _seqInfo = new Dictionary<RuntimeTypeHandle, SequenceInfo>();
        private object _seqInfoLock = new object();
        #endregion
        
        /// <summary>
        /// 得到下个序列值
        /// </summary>
        public uint Next<T>(IDatabase connection) where T : Entity
        {
            bool isExist = false;
            SequenceInfo value;

            lock (_seqInfoLock)
            {
                isExist = _seqInfo.TryGetValue(typeof(T).TypeHandle, out value);

                if (!isExist)
                {
                    value = new SequenceInfo(typeof(T).Name, 0);
                    _seqInfo[typeof(T).TypeHandle] = value;
                }
            }

            if (!isExist) value.SeqNo = this.GetMaxCode<T>(connection);

            return value.Next();
        }

        private uint GetMaxCode<T>(IDatabase db) where T : Entity
        {
            var tableName = PersistenceConfig.ConvertToTableName<T>();

            var sql = string.Format(@"select Max(code) from {0}", db.Dialect.Quote(tableName));

            return db.ExecuteScalar<uint>(sql);
        }
    }
}
