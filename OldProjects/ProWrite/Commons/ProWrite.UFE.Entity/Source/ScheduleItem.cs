using System;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Schedule item(Appointment)
    /// </summary>
    [Serializable]
    public class ScheduleItem
    {
        public ScheduleInfoType Timing { get; set; }
        public ScheduleIncludeItem DisplayContent;
    }
}
