using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// File items
    /// </summary>
    [Serializable]
    public class ScheduleIncludeItem
    {
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
        public ScheduleItemType Type;

        public ScheduleIncludeItem()
        {
            Id = Guid.NewGuid().ToString().Replace("-", "");
        }
    }
}
