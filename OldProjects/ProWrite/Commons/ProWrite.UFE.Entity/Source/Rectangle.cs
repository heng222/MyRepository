using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Rectangle
    /// </summary>
    [Serializable]
    public struct Rectangle
    {
        [XmlElement("TLCorner")]
        public Point TopLeft;

        [XmlElement("BRCorner")]
        public Point BottomRight;

    }
}
