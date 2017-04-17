using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace ProWrite.Entity.Dashboard
{
    /// <summary>
    /// Message info
    /// </summary>
    [Serializable]
    [XmlRoot(ElementName="Status")]
    public class StatusInfo : List<StatusInfo.Content>
    {
        [Serializable]
        public class Content
        {
             public string Item { get; set; }
            public string StatusValue { get; set; }
        }

    }
    
}
