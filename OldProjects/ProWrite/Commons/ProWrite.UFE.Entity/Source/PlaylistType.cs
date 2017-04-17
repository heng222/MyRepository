using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Playlist info
    /// </summary>
    [Serializable]
    [XmlRoot(Namespace = "http://xml.netbeans.org/schema/ProWritePlaylist", ElementName = "Playlist")]
    public class PlaylistType
    {

       
#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;
#else
        public ContentIDType ContentID;

#endif


        [XmlElement(IsNullable = false, ElementName = "DisplayTime")]
        public int Duration = 1;

        [XmlArrayItem("Content")]
        public List<PlaylistIncludeItem> Contents;

        
        public PlaylistType()
        {
#if VERSION_1
            Id = Guid.NewGuid().ToString().Replace("-", "");
#else
            ContentID.CXCUniqueIdentifier = Guid.NewGuid().ToString().Replace("-", "");
#endif
        }

    }
}
