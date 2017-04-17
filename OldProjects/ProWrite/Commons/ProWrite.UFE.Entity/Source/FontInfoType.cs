using System;

namespace ProWrite.UFE.Entity
{
    /// <summary>
    /// 
    /// </summary>
    [Serializable]
    public struct FontInfoType
    {
        public string Font;
        public int FontSize;
        public string FontColor;
        public int FontKerning;
        public int FontLead;
        public bool? WordWrap; //??
        public string FontFile;//??
        public bool? Bold;
        public bool? Italic;
        public bool? Underline;//??
        public bool? Outline;
#if VERSION_1
		        public Align HorizontalJustify;
		        public Valign VerticalJustify;
		        public OutlineShadowType Effect;
#else
        public TextHorzJustify HorizontalJustify;
        public TextVertJustify VerticalJustify;
        public TextEffect Effect;
#endif

        public int ShadeXOffset;
        public int ShadeYOffset;
        public int BubbleSize;
        public string EffectColor;

        public string BackgroundColor;
    }
}
