using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Message info
    /// </summary>
    [Serializable]
    [XmlRoot(Namespace = "http://xml.netbeans.org/schema/ProWriteFrameObject", ElementName = "FrameObject")]
    public class FrameObjectType
    {
#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;

        [XmlElement(IsNullable=false, ElementName="DisplayTime")]
        public float Length = 1;

        public EmphasisEffectType? EmphasisEffect;
        public string SignBackgroundColor;
        
#else
        public ContentIDType ContentID;
        public MasterLayerType MasterLayer;

       
#endif

        public FrameObjectType()
        {
#if VERSION_1
            Id = Guid.NewGuid().ToString().Replace("-", "");
#else
            ContentID.CXCUniqueIdentifier = Guid.NewGuid().ToString().Replace("-", "");
#endif

        }

        [XmlArrayItem("Content")]
        public List<FrameContentType> Contents;

    }
}
