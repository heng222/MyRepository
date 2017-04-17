using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Schedule Recurrence info (in Appointment)
    /// </summary>
    [Serializable]
    public struct ScheduleRecurrenceType
    {
        [XmlElement("NoEndDate", Type = typeof(bool))]
        [XmlElement("EndByDate", Type = typeof(string))]
        [XmlElement("EndAfterByOccurence", Type = typeof(int))]
        public object Range;

        [XmlIgnore]
        public bool NoEndDateRange
        {
            set { Range = value; }
        }

        [XmlIgnore]
        public string EndByDateRange
        {
            set { Range = value; }
        }

        [XmlIgnore]
        public int EndAfterByOccurenceRange
        {
            set { Range = value; }
        }

        [XmlElement("Daily", Type = typeof(int))]
        [XmlElement("Weekly", Type = typeof(WeeklyRecurrence))]
        public object Pattern;

        [XmlIgnore]
        public int DailyPattern
        {
            set { Pattern = value; }
        }

        [XmlIgnore]
        public WeeklyRecurrence WeeklyPattern
        {
            set { Pattern = value; }
        }

    }
}
