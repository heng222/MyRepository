namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, TypeLibType((short) 2), Guid("D4D68F8A-B665-41D4-94D1-E8843001E346"), ClassInterface((short) 0)]
    public class StandardMpegEncoderProfileClass : IStandardMpegEncoderProfile, StandardMpegEncoderProfile
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        public virtual extern void ConfigureForSystemsFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000e)]
        public virtual extern void GetAspectRatio([ComAliasName("DirectEncodeNET.AspectRatio")] out AspectRatio pAspectMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001e)]
        public virtual extern void GetAudioBitrate(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010022)]
        public virtual extern void GetAudioBitrateMax(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010020)]
        public virtual extern void GetAudioBitrateMin(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010032)]
        public virtual extern void GetAudioChannels(out int pnChannelCount);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        public virtual extern void GetAudioFormat([ComAliasName("DirectEncodeNET.AudioOutputFormat")] out AudioOutputFormat audioFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010030)]
        public virtual extern void GetAudioSampleRate(out int pnSampleRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002a)]
        public virtual extern void GetAudioVBRMode([ComAliasName("DirectEncodeNET.BitrateMode")] out BitrateMode pvbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010018)]
        public virtual extern void GetAutoSelectBitrate(out int pbVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010010)]
        public virtual extern void GetAutoSelectDimensions(out int pbVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003f)]
        public virtual extern void GetClosedGOP(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        public virtual extern void GetConstraint([ComAliasName("DirectEncodeNET.Constraint")] out Constraint systemsConstraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003c)]
        public virtual extern void GetDetectSceneChange(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010037)]
        public virtual extern void GetEncodeMode([ComAliasName("DirectEncodeNET.EncodeMode")] out EncodeMode pnValue);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002e)]
        public virtual extern void GetFramerate(out double fps);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003a)]
        public virtual extern void GetGOPSize(out int nGOPSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010043)]
        public virtual extern void GetGOPStructure([MarshalAs(UnmanagedType.BStr)] out string pstrStructure);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010013)]
        public virtual extern void GetHeight(out int pnHeight);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004e)]
        public virtual extern void GetInterlaceMode(out int bPreProcessDeinterlace, out int bInterlacedOutputDCT, out int bInterlacedOutputME);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010048)]
        public virtual extern void GetMotionSearchPrecision(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010041)]
        public virtual extern void GetOutputIntervalOfSequenceHeader([In] ref int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010046)]
        public virtual extern void GetProfileAndLevel([MarshalAs(UnmanagedType.BStr)] out string pstrProfileAndLevel);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        public virtual extern void GetProfileName([MarshalAs(UnmanagedType.BStr)] out string strName);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004c)]
        public virtual extern void GetQuantFactor(out float pfQuantFactor);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        public virtual extern void GetSystemsFormat([ComAliasName("DirectEncodeNET.SystemsOutputFormat")] out SystemsOutputFormat systemsFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010016)]
        public virtual extern void GetVideoBitrate(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001c)]
        public virtual extern void GetVideoBitrateMax(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001a)]
        public virtual extern void GetVideoBitrateMin(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        public virtual extern void GetVideoFormat([ComAliasName("DirectEncodeNET.VideoOutputFormat")] out VideoOutputFormat videoFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010024)]
        public virtual extern void GetVideoQuality(out int nQualityPercent);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010026)]
        public virtual extern void GetVideoVBRMode([ComAliasName("DirectEncodeNET.BitrateMode")] out BitrateMode pvbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010028)]
        public virtual extern void GetVideoVBVBufferSize(out int vbvlen);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010012)]
        public virtual extern void GetWidth(out int nWidth);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        public virtual extern void LoadProfile([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        public virtual extern void SaveProfile([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002b)]
        public virtual extern void Set2PassLogFile([In, MarshalAs(UnmanagedType.BStr)] string Path);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        public virtual extern void SetAspectRatio([In, ComAliasName("DirectEncodeNET.AspectRatio")] AspectRatio aspectMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001d)]
        public virtual extern void SetAudioBitrate([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010021)]
        public virtual extern void SetAudioBitrateMax([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001f)]
        public virtual extern void SetAudioBitrateMin([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010031)]
        public virtual extern void SetAudioChannels([In] int nChannelCount);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010033)]
        public virtual extern void SetAudioFlags([In] int bErrorProtection, [In] int bOriginal, [In] int bCopyright, [In] int bPrivate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        public virtual extern void SetAudioFormat([In, ComAliasName("DirectEncodeNET.AudioOutputFormat")] AudioOutputFormat audioFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002f)]
        public virtual extern void SetAudioSampleRate([In] int nSampleRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010029)]
        public virtual extern void SetAudioVBRMode([In, ComAliasName("DirectEncodeNET.BitrateMode")] BitrateMode vbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010017)]
        public virtual extern void SetAutoSelectBitrate([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000f)]
        public virtual extern void SetAutoSelectDimensions([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010038)]
        public virtual extern void SetBWVideo([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003e)]
        public virtual extern void SetClosedGOP([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010034)]
        public virtual extern void SetComments([In, MarshalAs(UnmanagedType.BStr)] string strVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        public virtual extern void SetConstraint([In, ComAliasName("DirectEncodeNET.Constraint")] Constraint systemsConstraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003b)]
        public virtual extern void SetDetectSceneChange([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010036)]
        public virtual extern void SetEncodeMode([In, ComAliasName("DirectEncodeNET.EncodeMode")] EncodeMode nValue);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002d)]
        public virtual extern void SetFramerate([In] double fps);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010039)]
        public virtual extern void SetGOPSize([In] int nGOPSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010042)]
        public virtual extern void SetGOPStructure([In, MarshalAs(UnmanagedType.BStr)] string strStructure);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010014)]
        public virtual extern void SetHeight([In] int nHeight);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004a)]
        public virtual extern void SetIDCT([In] int n);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010035)]
        public virtual extern void SetInformation([In, MarshalAs(UnmanagedType.BStr)] string strTitle, [In, MarshalAs(UnmanagedType.BStr)] string strAuthor, [In, MarshalAs(UnmanagedType.BStr)] string strCopyright);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004d)]
        public virtual extern void SetInterlaceMode([In] int bPreProcessDeinterlace, [In] int bInterlacedOutputDCT, [In] int bInterlacedOutputME);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010047)]
        public virtual extern void SetMotionSearchPrecision([In] int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010040)]
        public virtual extern void SetOutputIntervalOfSequenceHeader([In] int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010045)]
        public virtual extern void SetProfileAndLevel([In, MarshalAs(UnmanagedType.BStr)] string strProfileAndLevel);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        public virtual extern void SetProfileName([In, MarshalAs(UnmanagedType.BStr)] string strName);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010049)]
        public virtual extern void SetQuantBias([In] int nIntra, [In] int nInter);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004b)]
        public virtual extern void SetQuantFactor([In] float fQuantFactor);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003d)]
        public virtual extern void SetSceneChangeThreshold([In] float f);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010044)]
        public virtual extern void SetStrictGOP([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        public virtual extern void SetSystemsFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010015)]
        public virtual extern void SetVideoBitrate([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001b)]
        public virtual extern void SetVideoBitrateMax([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010019)]
        public virtual extern void SetVideoBitrateMin([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        public virtual extern void SetVideoFormat([In, ComAliasName("DirectEncodeNET.VideoOutputFormat")] VideoOutputFormat videoFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010023)]
        public virtual extern void SetVideoQuality([In] int nQualityPercent);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002c)]
        public virtual extern void SetVideoQualityRange([In] int nMin, [In] int nMax);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010025)]
        public virtual extern void SetVideoVBRMode([In, ComAliasName("DirectEncodeNET.BitrateMode")] BitrateMode vbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010027)]
        public virtual extern void SetVideoVBVBufferSize([In] int vbvlen);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010011)]
        public virtual extern void SetWidth([In] int nWidth);
    }
}

