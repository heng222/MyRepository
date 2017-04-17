using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// TimeSliceGroup info
    /// </summary>
    [Serializable]
    [XmlRoot(Namespace = "http://xml.netbeans.org/schema/ProWriteTimeSliceGroup", ElementName = "TimeSliceGroup")]
    public class TimeSliceGroupType
    {
#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
        //public string Name;
#else
        public ContentIDType ContentID;
#endif

        [XmlArrayItem("Content")]
        public List<TimeSliceGroupIncludeItem> Contents;

        [XmlElement(IsNullable = false, ElementName = "DisplayTime")]
        public float Duration = 1;

        public bool IsRandom;

        public TimeSliceGroupType()
        {
#if VERSION_1
            Id = Guid.NewGuid().ToString().Replace("-", "");
#else
            ContentID.CXCUniqueIdentifier = Guid.NewGuid().ToString().Replace("-", "");
#endif
        }
    }
}
