using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public struct MasterLayerType
    {

        [XmlElement(IsNullable = false, ElementName = "DisplayTime")]
        public float Length;
        [XmlElement(ElementName = "BackgroundColor")]
        public string SignBackgroundColor;
        [XmlElement("EntryTransitionEffect")]
        public TransitionEffectType? EntryEffect;
        [XmlElement("EmphasisTransitionEffect")]
        public EmphasisEffectType? EmphasisEffect;
        [XmlElement("ExitTransitionEffect")]
        public TransitionEffectType? ExitEffect;
    }
}
