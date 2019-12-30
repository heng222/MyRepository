using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Utility;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;
using Products.LogReport.Data;

namespace Products.LogReport
{
    static class SysEventLogInfoQueryable
    {
        public static IList<SysEventLogInfo> Query(DateTime beginTime, DateTime endTime,string eventLevel,string eventType)
        {
            string sql = BuildSql(eventLevel, eventType);

            var events = GlobalServices.Repository.Where<SysEvent>();
            var getEventTypeName = new Func<EventType, string>(t =>
            {
                var e = events.FirstOrDefault(s => s.Code == (uint)t);
                return e != null ? e.Name : "";
            });

            return GlobalServices.Repository.Where<SysEventLog>(sql, new { beginTime = beginTime, endTime = endTime })
                .Select(log => new SysEventLogInfo
                {
                    ConfirmTime = log.ConfirmTime,
                    Description = log.Description,
                    EventTypeCode = EnumUtility.GetDescription<EventType>(log.TypeCode),
                    Level = (int)log.Level,
                    Timestamp = log.Timestamp,
                    EventTypeName = getEventTypeName(log.TypeCode),
                }).ToList();
        }

        private static string BuildSql(string eventLevel, string eventType)
        {
            var sql = new StringBuilder(@"select * from SysEventLogs t where t.[Timestamp] >=@beginTime and t.[Timestamp]<=@endTime");

            // 增加时间级别的查询条件
            if (!string.IsNullOrEmpty(eventLevel))
            {
                var evLevel = EnumUtility.GetValue<EventLevel>(eventLevel);

                int type = -1;
                type = Convert.ToInt16(evLevel);

                if (type != -1)
                    sql.AppendFormat(" and t.[Level]={0}", type);
            }

            // 增加事件类型的查询条件
            if (!string.IsNullOrEmpty(eventType))
            {
                var evType = EnumUtility.GetValue<EventType>(eventType);

                int type = -1;
                type = Convert.ToInt16(evType);

                if (type != -1)
                    sql.AppendFormat(" and t.[TypeCode]={0}", type);
            }

            sql.AppendFormat(" order by t.[Timestamp]");

            return sql.ToString();
        }

    }
}
