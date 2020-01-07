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
    static class SysEventLogInfoQueryable
    {
        public static List<SysEventLogInfo> Query(DateTime beginTime, DateTime endTime, EventLevel eventLevel, EventType eventType)
        {
            var cfg = DbConfiguration.Configure("SqliteDb.EventLogs");

            using (var dbContext = cfg.CreateDbContext())
            {
                IQueryable<SysEventLog> repository = dbContext.Set<SysEventLog>()
                    .Where(p => p.Timestamp >= beginTime && p.Timestamp <= endTime);
                
                // 事件级别
                if (eventLevel != EventLevel.None)
                {
                    repository = repository.Where(p => p.Level == eventLevel);
                }

                // 事件类型
                if (eventType != EventType.None)
                {
                    repository = repository.Where(p => p.TypeCode == eventType);
                }

                var items = repository.OrderBy(p => p.Timestamp).Select(log => new SysEventLogInfo
                {
                    Timestamp = log.Timestamp,
                    Description = log.Description,
                    EventTypeName = EnumUtility.GetDescription(log.TypeCode),
                    Level = EnumUtility.GetDescription(log.Level),
                    ConfirmTime = log.ConfirmTime == DateTime.MinValue ? string.Empty : log.ConfirmTime.ToString(),
                }).ToList();

                return items.ToList();
            }
        }        
    }
}
