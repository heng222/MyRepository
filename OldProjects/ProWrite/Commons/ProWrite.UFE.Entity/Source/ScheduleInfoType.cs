using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Schedule item parameter info(Appointmeng info)
    /// </summary>
    [Serializable]
    public struct ScheduleInfoType
    {
        public bool IsScheduled;

        public string StartTime;
        public string StartDay;

        public string StopTime;
        public string StopDay;

        public bool IsAllDayEvent;
        public bool IsExact;

        [NonSerialized]
        [XmlIgnore]
        public bool IsPlayMessageOnce;


        public ScheduleRecurrenceType Recurrence;

    }
}
