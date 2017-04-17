using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// File items
    /// </summary>
    [Serializable]
    public class PlaylistIncludeItem
    {
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
        public PlaylistItemType Type;

        public PlaylistIncludeItem()
        {
            Id = Guid.NewGuid().ToString().Replace("-", "");
        }
    }
}
