using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct TextType
    {
        [XmlElement(ElementName = "TextString")]
        public string DisplayText;
        [XmlElement(ElementName = "Font")]
        public FontInfoType FontInfo;
    }
}
