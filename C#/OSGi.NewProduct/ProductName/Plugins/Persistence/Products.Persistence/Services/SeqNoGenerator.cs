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
using System.Text;
using Acl.Data;
using Products.Domain.Utility;
using Products.Infrastructure.Entities;

namespace Products.Persistence.Services
{
    class SeqNoGenerator
    {
        #region "Field"
        private Dictionary<RuntimeTypeHandle, SeqNoManager> _seqInfo = new Dictionary<RuntimeTypeHandle, SeqNoManager>();
        private object _seqInfoLock = new object();
        #endregion
        
        /// <summary>
        /// 得到下个序列值
        /// </summary>
        public uint Next<T>(IDatabase connection) where T : Entity
        {
            bool isExist = false;
            SeqNoManager value;

            lock (_seqInfoLock)
            {
                isExist = _seqInfo.TryGetValue(typeof(T).TypeHandle, out value);

                if (!isExist)
                {
                    value = new SeqNoManager(1, UInt32.MaxValue, 1);
                    _seqInfo[typeof(T).TypeHandle] = value;
                }
            }

            if (!isExist)
            {
                value.SendSeqNo = this.GetMaxCode<T>(connection);
                value.GetAndUpdateSendSeq();
            }

            return value.GetAndUpdateSendSeq();
        }

        private uint GetMaxCode<T>(IDatabase db) where T : Entity
        {
            return (db as IDbContext).Set<T>().Max(p => p.Code);
        }
    }
}
