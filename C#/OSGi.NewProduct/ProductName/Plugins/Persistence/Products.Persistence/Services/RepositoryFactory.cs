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

using Products.Persistence.Services.Repositories;
using Products.Persistence.Specification;

namespace Products.Persistence.Services
{
    static class RepositoryFactory
    {
        public static IEnumerable<Repository> Create(IEnumerable<DataSource> dataSources, IRepositorySelect repositorySelection)
        {
            var repositories = new List<Repository>();

            dataSources.ForEach(p =>
            {
                var dbType = (DataBaseType)p.DbType;

                if (PersistenceConfig.IsRemoteDatabase(dbType))
                {
                    repositories.Add(new RepositoryRemote(p));
                }
                else if (dbType == DataBaseType.Sqlite)
                {
                    repositories.Add(new RepositorySqlite(p));
                }
                else if (dbType == DataBaseType.CSV)
                {
                    repositories.Add(new RepositoryCsvFile(p));
                }
                else if (dbType == DataBaseType.Memory)
                {
                    repositories.Add(new RepositoryMemory(p, repositorySelection));
                }
                else
                {
                    throw new Exception($"不支持的数据库类型 {dbType}。");
                }
            });

            return repositories;
        }
    }
}
