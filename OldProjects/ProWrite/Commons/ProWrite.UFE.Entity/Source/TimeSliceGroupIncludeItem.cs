using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// File items
    /// </summary>
    [Serializable]
    public class TimeSliceGroupIncludeItem
    {
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
        public TimeSliceGroupItemType Type;

        public TimeSliceGroupIncludeItem()
        {
            Id = Guid.NewGuid().ToString().Replace("-", "");
        }
    }
}
