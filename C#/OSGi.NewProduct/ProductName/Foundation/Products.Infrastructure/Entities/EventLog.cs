/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/28 13:57:44 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// ϵͳ�¼�
    /// </summary>
    public class EventLog
    {
        /// <summary>
        /// �¼�������ʱ��
        /// </summary>
        public DateTime Timestamp { get; set; }

        /// <summary>
        /// �¼�����
        /// </summary>
        public EventType TypeCode { get; set; }

        /// <summary>
        /// �¼�����
        /// </summary>
        public EventLevel Level { get; set; }

        /// <summary>
        /// ����
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// ���캯����
        /// </summary>
        public EventLog()
        {
            this.Timestamp = DateTime.Now;
            this.Description = string.Empty;
        }

        /// <summary>
        /// ���캯����
        /// </summary>
        public EventLog(EventType type, EventLevel level, string description)
        {
            this.Timestamp = DateTime.Now;
            this.TypeCode = type;
            this.Level = level;
            this.Description = description;
        }
    }
}
