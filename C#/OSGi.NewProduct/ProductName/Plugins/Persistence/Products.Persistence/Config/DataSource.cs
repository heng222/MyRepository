/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
        /// Url��
        /// </summary>
        public string Url { get; set; }

        /// <summary>
        /// ��ȡ���� DataSourceName��
        /// </summary>
        public string BackupDataSourceName { get; set; }

        /// <summary>
        /// DataSource ������ʵ�塣���ŷָ���
        /// </summary>
        public string Entities { get; set; }

        /// <summary>
        /// DataSource ������ TableDescriptors��
        /// </summary>
        [System.Xml.Serialization.XmlIgnore]
        internal Dictionary<Type, TableDescriptor> TableDescriptors { get; set; }

        /// <summary>
        /// ���캯����
        /// </summary>
        public DataSource()
        {
            this.TableDescriptors = new Dictionary<Type, TableDescriptor>();
        }
    }
}
