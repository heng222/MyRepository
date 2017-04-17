using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace ProWrite.Core
{
    #region TransitionEffectType
    [Serializable]
    public struct None { }
    [Serializable]
    public struct Automatic { }
    [Serializable]
    public struct Blank { }
    [Serializable]
    public struct Bounce { }
    [Serializable]
    public struct BlackHole
    {
        public int? LocationX;
        public int? LocationY;
    }
    [Serializable]
    public struct Coalesce
    {
        public int? EntityWidth;
        public int? EntityHeight;
    }
    [Serializable]
    public struct Copy { }
    [Serializable]
    public struct Fade { }
    [Serializable]
    public struct Filter
    {
        public int? LineWidth;
        public int? LineSpacing;
    }
    [Serializable]
    public struct Interleave
    {
        public EffectDirectionType Direction;
        public int? LineWidth;
        public LineLocationType? LineOrientation;
    }


    [Serializable]
    public struct Line
    {
        public EffectDirectionType Direction;
        public int? LineWidth;
        public int? LineStagger;
        public LineLocationType? Location;

       
    }

    public enum LineLocationType
    {
        VERTICAL,
        HORIZONTAL,
    }

    [Serializable]
    public struct MultiWipe
    {
        public int? HorizontalWipes;
        public int? VerticalWipes;
    }
    [Serializable]
    public struct Radar
    {
        public EffectDirectionType Direction;
        public bool? EdgeVisible;
        public int? EdgeColor;
    }
    [Serializable]
    public struct Rain
    {
        public int? Amount;
        public int? Color;
    }
    [Serializable]
    public struct Slide
    {
        public EffectDirectionType Direction;
    }
    [Serializable]
    public struct Slot { }
    [Serializable]
    public struct Venetian
    {
        public EffectDirectionType Direction;

        public int? BlindWidth;
    }
    [Serializable]
    public struct Wipe
    {
        public EffectDirectionType Direction;
    }
    #endregion

    #region EmphasisEffectType
    [Serializable]
    public struct Bijou
    {
        public EffectDirectionType Direction;
        public int? Thickness;
        public int? On;
        public int? Off; 
        public int? Length;
        public int? Rate;
        public int? Color;
        public int? GapColor;
    }
    [Serializable]
    public struct Flash
    {
        public float? OnTime;
        public float? OffTime;
        public FlashStyle FlashType;

    }

    public enum FlashStyle
    {
        BlankFlash = 0,
        InvertFlash = 1,
        //RandomFlash = 2
    }
    
    [Serializable]
    public struct Snow
    {
        public int? Amount;
        public int? FallRate;
        public int? Color;
    }
    [Serializable]
    public struct Sparkle
    {
        public int? Amount;
        public int? Size;
       // TODO:???
        public int? Style;
        //TODO:???
        public int? Rate;
    }
    [Serializable]
    public struct Travel
    {
        public EffectDirectionType Direction;
        public bool? Circular;
        public int? Spacing;
        public int? Speed;
        //???not exists
        public int? RotateLetters;
    }
    [Serializable]
    public struct Wraparound
    {
        public EffectDirectionType Direction;
        public int? Rate;
        public int? Spacing;
    }
    #endregion

    public enum EffectDirectionType
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        IN,
        OUT,
        UPLEFT,
        UPRIGHT,
        LOWLEFT,
        LOWRIGHT,
        UPCENTER,
        LOWCENTER,
        UPCORNERS,
        LOWCORNERS,
        CENTER,
        ALLCORNERS,
        CLOCKWISE,
        COUNTERCW,
        ALTERNATING,
        UP_DOWN,
        LEFT_RIGHT,
        IN_OUT,
        UPLEFT_LOWRIGHT,
        LOWLEFT_UPRIGHT,
    }

}
