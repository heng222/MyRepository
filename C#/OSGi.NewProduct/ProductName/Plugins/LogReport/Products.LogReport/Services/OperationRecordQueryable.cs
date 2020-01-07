using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Data.Configuration;
using Acl.Utility;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.LogReport.Data;

namespace Products.LogReport
{
    static class OperationRecordQueryable
    {
        //public static List<OperationRecordInfo> Query(DateTime beginTime, DateTime endTime, OperationType operationType, bool? isManual)
        //{
        //    var sql = BuildSql(operationType, isManual);

        //    var logs = GlobalServices.Repository.Where<OperationLog>(sql, new { beginTime = beginTime, endTime = endTime });

        //    var items = (from t in logs
        //                 select new OperationRecordInfo
        //                 {
        //                     Timestamp = t.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff"),
        //                     IsManual = t.IsManual ? "手动执行" : "自动执行",
        //                     TargetDeviceCode = t.TargetDeviceCode.ToString(),
        //                     OperationDescription = t.OperationDescription,
        //                     OperationType = EnumUtility.GetDescription(t.OperationType),

        //                     ResultTime = t.ResultTimestamp,
        //                     ResultType = EnumUtility.GetDescription<OperationResult>(t.ResultType),
        //                     ResultDescription = t.ResultDescription,
        //                 }).ToList();

        //    return items;
        //}

        //private static string BuildSql(OperationType operationType, bool? isManual)
        //{
        //    var sql = new StringBuilder(@"select  t.* from OperationLogs t where t.Timestamp >=@beginTime and t.Timestamp<=@endTime");

        //    if (operationType != OperationType.None)
        //    {
        //        sql.AppendFormat(" and t.OperationType={0}", Convert.ToInt16(operationType));
        //    }

        //    if (isManual.HasValue)
        //    {
        //        sql.AppendFormat(" and t.IsManual={0}", isManual.Value ? 1 : 0);
        //    }

        //    sql.AppendFormat(" order by t.Timestamp");

        //    return sql.ToString();
        //}

        public static List<OperationRecordInfo> Query(DateTime beginTime, DateTime endTime, OperationType operationType, bool? isManual)
        {
            var cfg = DbConfiguration.Configure("SqliteDb.OperationLogs");

            using (var dbContext = cfg.CreateDbContext())
            {
                IQueryable<OperationLog> repository = dbContext.Set<OperationLog>()
                    .Where(p => p.Timestamp >= beginTime && p.Timestamp <= endTime);

                if (operationType != OperationType.None)
                {
                    repository = repository.Where(p => p.OperationType == operationType);
                }

                if (isManual.HasValue)
                {
                    repository = repository.Where(p => p.IsManual == isManual.Value);
                }

                var items = repository.OrderBy(p => p.Timestamp).Select(p => new OperationRecordInfo
                          {
                              Timestamp = p.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff"),
                              IsManual = p.IsManual ? "手动执行" : "自动执行",
                              TargetDeviceCode = p.TargetDeviceCode.ToString(),
                              OperationDescription = p.OperationDescription,
                              OperationType = EnumUtility.GetDescription(p.OperationType),

                              ResultTime = p.ResultTimestamp,
                              ResultType = EnumUtility.GetDescription<OperationResult>(p.ResultType),
                              ResultDescription = p.ResultDescription,
                          });

                return items.ToList();
            }
        }
    }
}
