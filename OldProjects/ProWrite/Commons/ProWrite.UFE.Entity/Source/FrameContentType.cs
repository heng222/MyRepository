using System;
using System.Xml.Serialization;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// Layer info
    /// </summary>
    [Serializable]
    public class FrameContentType
    {
        [XmlElement(IsNullable = false, ElementName = "UniqueIdentifier")]
        public string Id;

#if VERSION_1
		        [XmlIgnore]
#endif
        public string HumanReadableName;

        [XmlElement(IsNullable = false)]
        public ContentType Type;
        [XmlElement(IsNullable = false, ElementName = "Dimension")]
        public Rectangle Bounds;
        [XmlElement(IsNullable = false, ElementName = "TimeOffset")]
        public float StartTime;
        [XmlElement(IsNullable = false, ElementName = "TimeDisplayLength")]
        public float Length;

        [XmlElement("FileName")]
        public string FileName;

        public TextType? Text;

        public int DLTSource;
        public int DLTField;
        public bool DLTisLocal;

        //effect arg set
        [XmlElement("EntryTransitionEffect")]
        public TransitionEffectType? EntryEffect;
        [XmlElement("EmphasisTransitionEffect")]
        public EmphasisEffectType? EmphasisEffect;
        [XmlElement("ExitTransitionEffect")]
        public TransitionEffectType? ExitEffect;
        [XmlElement("ScrollInformation")]
        public ScrollEffectType? ScrollEffect;

        public FrameContentType()
        {
            Id = Guid.NewGuid().ToString().Replace("-", "");
        }
    }
}
