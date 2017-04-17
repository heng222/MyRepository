using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct ScrollContentType
    {
        [XmlElement("Temp", typeof(VariableTempType))]
        [XmlElement("Text", typeof(TextType))]
        [XmlElement("Time", typeof(VariableTimeType))]
        public object Item;

        [XmlIgnore]
        public VariableTempType? Temp
        {
            set { Item = value; }
        }

        [XmlIgnore]
        public TextType? Text
        {
            set { Item = value; }
        }

        [XmlIgnore]
        public VariableTimeType? Time
        {
            set { Item = value; }
        }
    }
}
