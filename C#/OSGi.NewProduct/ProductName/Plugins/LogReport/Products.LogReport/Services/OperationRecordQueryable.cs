using System;
using System.Collections.Generic;
using System.Linq;

using Acl.Utility;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.LogReport.Data;

namespace Products.LogReport
{
    static class OperationRecordQueryable
    {
        public static List<OperationRecordInfo> Query(DateTime beginTime, DateTime endTime, OperationType operationType, bool? isManual)
        {
            List<OperationRecordInfo> values = null;

            GlobalServices.Repository.Execute<OperationLog>(db =>
            {
                using (var dbContext = db.Cfg.CreateDbContext())
                {
                    var querable = dbContext.Set<OperationLog>()
                        .Where(p => p.Timestamp >= beginTime && p.Timestamp <= endTime);

                    if (operationType != OperationType.None)
                    {
                        querable = querable.Where(p => p.OperationType == operationType);
                    }

                    if (isManual.HasValue)
                    {
                        querable = querable.Where(p => p.IsManual == isManual.Value);
                    }

                    var items = querable.OrderBy(p => p.Timestamp).Select(p => new OperationRecordInfo
                    {
                        Timestamp = p.Timestamp.ToString("yyyy-MM-dd HH:mm:ss.fff"),
                        UserName = p.UserName,
                        IsManual = p.IsManual ? "手动执行" : "自动执行",
                        TargetDeviceCode = p.TargetDeviceCode.ToString(),
                        OperationDescription = p.OperationDescription,
                        OperationType = EnumUtility.GetDescription(p.OperationType),

                        ResultTime = p.ResultTimestamp,
                        ResultType = EnumUtility.GetDescription(p.ResultType),
                        ResultDescription = p.ResultDescription,
                    });

                    // 
                    values = items.ToList();
                }
            });

            return values;
        }
    }
}
