using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Transition Effect info
    /// </summary>
    [Serializable]
    public struct TransitionEffectType
    {
        //#if VERSION_1
        [XmlElement(IsNullable = false, ElementName = "TransitionEffect")]
        public TransitionType Name;

        static string FirstUpper(string src)
        {
            return src[0].ToString().ToUpper() + src.Remove(0, 1);
        }


        [XmlIgnore]
        public string EffectName
        {
            get { return FirstUpper(Name.ToString().ToLower()); }
        }
        //#endif

        [XmlElement(IsNullable = false, ElementName = "Duration")]
        public float Length;

//#if VERSION_1
        public int EffectSpeed;
//#endif

        //#if VERSION_1
        public Parameter[] Params;
        //#else
        //        [XmlElement("None", typeof(None))]
        //        [XmlElement("Automatic", typeof(Automatic))]
        //        [XmlElement("Blank", typeof(Blank))]
        //        [XmlElement("Bounce", typeof(Bounce))]
        //        [XmlElement("BlackHole", typeof(BlackHole))]
        //        [XmlElement("Coalesce", typeof(Coalesce))]
        //        [XmlElement("Copy", typeof(Copy))]
        //        [XmlElement("Fade", typeof(Fade))]
        //        [XmlElement("Filter", typeof(Filter))]
        //        [XmlElement("Interleave", typeof(Interleave))]
        //        [XmlElement("Line", typeof(Line))]
        //        [XmlElement("MultiWipe", typeof(MultiWipe))]
        //        [XmlElement("Radar", typeof(Radar))]
        //        [XmlElement("Rain", typeof(Rain))]
        //        [XmlElement("Slide", typeof(Slide))]
        //        [XmlElement("Slot", typeof(Slot))]
        //        [XmlElement("Venetian", typeof(Venetian))]
        //        [XmlElement("Wipe", typeof(Wipe))]
        //        public object Effect;
        //#endif
    }
}
