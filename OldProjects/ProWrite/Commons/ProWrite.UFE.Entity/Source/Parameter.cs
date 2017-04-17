using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Effect parameters
    /// </summary>
    [Serializable]
    public struct Parameter
    {
        [XmlAttribute]
        public string Name;
        [XmlAttribute]
        public string Value;
    }
}
