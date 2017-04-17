using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Schedule Info
    /// </summary>
    [Serializable]
    [XmlRoot(Namespace = "http://xml.netbeans.org/schema/ProWriteSchedule", ElementName = "Schedule")]
    public class ScheduleType
    {
#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
        //public string Name;
#else
        public ContentIDType ContentID;
#endif
        public List<ScheduleItem> ScheduleItems;

        public ScheduleType()
        {
#if VERSION_1
            Id = Guid.NewGuid().ToString().Replace("-", "");
#else
            ContentID.CXCUniqueIdentifier = Guid.NewGuid().ToString().Replace("-", "");
#endif
        }

    }
}
