using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    public struct ScrollEffectType
    {
        public bool? IsScrolling;
        [XmlElement(ElementName = "ScrollDirection")]
        public ScrollDirectionType? Direction;
        public float? Speed;
        //[XmlIgnore]
        //public ScrollContentType Content;
    }
}
