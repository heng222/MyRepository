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

namespace Products.Persistence
{
    /// <summary>
    /// DataSource
    /// </summary>
    public class DataSource
    {
        /// <summary>
        /// Name
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Driver
        /// </summary>
        public string Driver { get; set; }

        /// <summary>
        /// DatabaseType.
        /// </summary>
        public int DbType { get; set; }

        /// <summary>
        /// Url。
        /// </summary>
        public string Url { get; set; }

        /// <summary>
        /// 获取备用 DataSourceName。
        /// </summary>
        public string BackupDataSourceName { get; set; }

        /// <summary>
        /// DataSource 包含的实体。逗号分隔。
        /// </summary>
        public string Entities { get; set; }

        /// <summary>
        /// DataSource 包含的 TableDescriptors。
        /// </summary>
        [System.Xml.Serialization.XmlIgnore]
        internal Dictionary<Type, TableDescriptor> TableDescriptors { get; set; }

        /// <summary>
        /// 构造函数。
        /// </summary>
        public DataSource()
        {
            this.TableDescriptors = new Dictionary<Type, TableDescriptor>();
        }
    }
}
