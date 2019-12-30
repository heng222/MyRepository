using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.LogReport.Data;

namespace Products.LogReport
{
    static class OperationRecordQueryable
    {
        public static IList<OperationRecordInfo> Query(DateTime beginTime, DateTime endTime, OperationType operationType, bool? isManual)
        {
            string sql = BuildSql(operationType, isManual);

            var logs = GlobalServices.Repository.Where<OperationLog>(sql, new { beginTime = beginTime, endTime = endTime });

            var items = (from t in logs
                         select new OperationRecordInfo
                         {
                             Timestamp = t.Timestamp,
                             IsManual = t.IsManual ? "手动执行" : "自动执行",
                             TargetDeviceCode = t.TargetDeviceCode.ToString(),
                             OperationDescription = t.OperationDescription,
                             OperationType = EnumUtility.GetDescription(t.OperationType),

                             ResultTime = t.ResultTimestamp,
                             ResultType = EnumUtility.GetDescription<OperationResult>(t.ResultType),
                             ResultDescription = t.ResultDescription,
                         }).ToArray();

            return items;
        }

        private static string BuildSql(OperationType operationType, bool? isManual)
        {
            var sql = new StringBuilder(@"select  t.* from OperationLogs t where t.[Timestamp] >=@beginTime and t.[Timestamp]<=@endTime");

            if (operationType != OperationType.None)
            {
                sql.AppendFormat(" and t.[OperationType]={0}", Convert.ToInt16(operationType));
            }

            if (isManual.HasValue)
            {
                sql.AppendFormat(" and t.[IsManual]={0}", isManual.Value ? 1 : 0);
            }

            sql.AppendFormat(" order by t.[Timestamp]");

            return sql.ToString();
        }

    }
}
