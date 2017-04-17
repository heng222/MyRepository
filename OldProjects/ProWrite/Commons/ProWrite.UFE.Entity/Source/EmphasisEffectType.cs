using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Emphasis  Effect info
    /// </summary>
    [Serializable]
    public struct EmphasisEffectType
    {
        //#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "EmphasisEffect")]
        public EmphasisType Name;
        //#endif

        [XmlElement(IsNullable = false, ElementName = "Duration")]
        public float Length;

        //#if VERSION_1
        public int EffectSpeed;
        public Parameter[] Params;
        //#else
        //        [XmlElement("Bijou", typeof(Bijou))]
        //        [XmlElement("Flash", typeof(Flash))]
        //        [XmlElement("Snow", typeof(Snow))]
        //        [XmlElement("Sparkle", typeof(Sparkle))]
        //        [XmlElement("Travel", typeof(Travel))]
        //        [XmlElement("Wraparound", typeof(Wraparound))]
        //        public object Effect;
        //#endif


    }
}
