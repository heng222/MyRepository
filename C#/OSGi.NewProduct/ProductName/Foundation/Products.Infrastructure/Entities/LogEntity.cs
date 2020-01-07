using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 日志实体基类定义。
    /// </summary>
    public abstract class LogEntity : Entity
    {
        /// <summary>
        /// 
        /// </summary>
        private string _timestampInner;

        /// <summary>
        /// 日志产生的时间。
        /// </summary>
        [Acl.Data.Annotions.Column(Name = "TimestampString", Storage = "_timestampInner")]
        public DateTime Timestamp
        {
            get { return DateTime.ParseExact(_timestampInner.Substring(4, 23), "yyyy-MM-dd HH:mm:ss.fff", CultureInfo.CurrentCulture); }

            set { _timestampInner = value.ToString("CDT_yyyy-MM-dd HH:mm:ss.fff"); }
        }
    }
}
