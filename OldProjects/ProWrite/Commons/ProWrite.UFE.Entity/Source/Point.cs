using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Point
    /// </summary>
    [Serializable]
    public struct Point
    {
        [XmlElement("XCoordinate")]
        public int X;
        [XmlElement("YCoordinate")]
        public int Y;
    }
}
