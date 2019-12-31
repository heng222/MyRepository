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
    static class SysEventLogInfoQueryable
    {
        public static List<SysEventLogInfo> Query(DateTime beginTime, DateTime endTime, EventLevel eventLevel, EventType eventType)
        {
            var sql = BuildSql(eventLevel, eventType);
            
            return GlobalServices.Repository.Where<SysEventLog>(sql, new { beginTime = beginTime, endTime = endTime })
                .Select(log => new SysEventLogInfo
                {
                    Timestamp = log.Timestamp,
                    Description = log.Description,
                    EventTypeName = EnumUtility.GetDescription(log.TypeCode),
                    Level = EnumUtility.GetDescription(log.Level),
                    ConfirmTime = log.ConfirmTime == DateTime.MinValue ? string.Empty : log.ConfirmTime.ToString(),
                }).ToList();
        }

        private static string BuildSql(EventLevel eventLevel, EventType eventType)
        {
            var sql = new StringBuilder(@"select * from SysEventLogs t where t.Timestamp >=@beginTime and t.Timestamp<=@endTime");

            // 事件级别
            if (eventLevel != EventLevel.None)
            {
                sql.AppendFormat(" and t.Level={0}", (int)eventLevel);
            }

            // 事件类型
            if (eventType != EventType.None)
            {
                sql.AppendFormat(" and t.TypeCode={0}", (int)eventType);
            }

            sql.AppendFormat(" order by t.Timestamp");

            return sql.ToString();
        }

    }
}
