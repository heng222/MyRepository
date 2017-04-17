namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("182EB270-5FA5-46E8-83BA-40F7205C545B"), InterfaceType((short) 1), TypeLibType((short) 0x40)]
    public interface IStandardMpegEncoderProfile
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        void SaveProfile([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        void LoadProfile([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        void GetProfileName([MarshalAs(UnmanagedType.BStr)] out string strName);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        void SetProfileName([In, MarshalAs(UnmanagedType.BStr)] string strName);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        void SetAudioFormat([In, ComAliasName("DirectEncodeNET.AudioOutputFormat")] AudioOutputFormat audioFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        void GetAudioFormat([ComAliasName("DirectEncodeNET.AudioOutputFormat")] out AudioOutputFormat audioFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        void SetVideoFormat([In, ComAliasName("DirectEncodeNET.VideoOutputFormat")] VideoOutputFormat videoFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        void GetVideoFormat([ComAliasName("DirectEncodeNET.VideoOutputFormat")] out VideoOutputFormat videoFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        void SetSystemsFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        void GetSystemsFormat([ComAliasName("DirectEncodeNET.SystemsOutputFormat")] out SystemsOutputFormat systemsFormat);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        void ConfigureForSystemsFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        void SetConstraint([In, ComAliasName("DirectEncodeNET.Constraint")] Constraint systemsConstraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        void GetConstraint([ComAliasName("DirectEncodeNET.Constraint")] out Constraint systemsConstraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        void SetAspectRatio([In, ComAliasName("DirectEncodeNET.AspectRatio")] AspectRatio aspectMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000e)]
        void GetAspectRatio([ComAliasName("DirectEncodeNET.AspectRatio")] out AspectRatio pAspectMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000f)]
        void SetAutoSelectDimensions([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010010)]
        void GetAutoSelectDimensions(out int pbVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010011)]
        void SetWidth([In] int nWidth);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010012)]
        void GetWidth(out int nWidth);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010013)]
        void GetHeight(out int pnHeight);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010014)]
        void SetHeight([In] int nHeight);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010015)]
        void SetVideoBitrate([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010016)]
        void GetVideoBitrate(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010017)]
        void SetAutoSelectBitrate([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010018)]
        void GetAutoSelectBitrate(out int pbVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010019)]
        void SetVideoBitrateMin([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001a)]
        void GetVideoBitrateMin(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001b)]
        void SetVideoBitrateMax([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001c)]
        void GetVideoBitrateMax(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001d)]
        void SetAudioBitrate([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001e)]
        void GetAudioBitrate(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001001f)]
        void SetAudioBitrateMin([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010020)]
        void GetAudioBitrateMin(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010021)]
        void SetAudioBitrateMax([In] int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010022)]
        void GetAudioBitrateMax(out int nBitrate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010023)]
        void SetVideoQuality([In] int nQualityPercent);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010024)]
        void GetVideoQuality(out int nQualityPercent);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010025)]
        void SetVideoVBRMode([In, ComAliasName("DirectEncodeNET.BitrateMode")] BitrateMode vbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010026)]
        void GetVideoVBRMode([ComAliasName("DirectEncodeNET.BitrateMode")] out BitrateMode pvbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010027)]
        void SetVideoVBVBufferSize([In] int vbvlen);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010028)]
        void GetVideoVBVBufferSize(out int vbvlen);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010029)]
        void SetAudioVBRMode([In, ComAliasName("DirectEncodeNET.BitrateMode")] BitrateMode vbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002a)]
        void GetAudioVBRMode([ComAliasName("DirectEncodeNET.BitrateMode")] out BitrateMode pvbrMode);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002b)]
        void Set2PassLogFile([In, MarshalAs(UnmanagedType.BStr)] string Path);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002c)]
        void SetVideoQualityRange([In] int nMin, [In] int nMax);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002d)]
        void SetFramerate([In] double fps);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002e)]
        void GetFramerate(out double fps);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001002f)]
        void SetAudioSampleRate([In] int nSampleRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010030)]
        void GetAudioSampleRate(out int pnSampleRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010031)]
        void SetAudioChannels([In] int nChannelCount);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010032)]
        void GetAudioChannels(out int pnChannelCount);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010033)]
        void SetAudioFlags([In] int bErrorProtection, [In] int bOriginal, [In] int bCopyright, [In] int bPrivate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010034)]
        void SetComments([In, MarshalAs(UnmanagedType.BStr)] string strVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010035)]
        void SetInformation([In, MarshalAs(UnmanagedType.BStr)] string strTitle, [In, MarshalAs(UnmanagedType.BStr)] string strAuthor, [In, MarshalAs(UnmanagedType.BStr)] string strCopyright);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010036)]
        void SetEncodeMode([In, ComAliasName("DirectEncodeNET.EncodeMode")] EncodeMode nValue);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010037)]
        void GetEncodeMode([ComAliasName("DirectEncodeNET.EncodeMode")] out EncodeMode pnValue);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010038)]
        void SetBWVideo([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010039)]
        void SetGOPSize([In] int nGOPSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003a)]
        void GetGOPSize(out int nGOPSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003b)]
        void SetDetectSceneChange([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003c)]
        void GetDetectSceneChange(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003d)]
        void SetSceneChangeThreshold([In] float f);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003e)]
        void SetClosedGOP([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001003f)]
        void GetClosedGOP(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010040)]
        void SetOutputIntervalOfSequenceHeader([In] int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010041)]
        void GetOutputIntervalOfSequenceHeader([In] ref int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010042)]
        void SetGOPStructure([In, MarshalAs(UnmanagedType.BStr)] string strStructure);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010043)]
        void GetGOPStructure([MarshalAs(UnmanagedType.BStr)] out string pstrStructure);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010044)]
        void SetStrictGOP([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010045)]
        void SetProfileAndLevel([In, MarshalAs(UnmanagedType.BStr)] string strProfileAndLevel);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010046)]
        void GetProfileAndLevel([MarshalAs(UnmanagedType.BStr)] out string pstrProfileAndLevel);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010047)]
        void SetMotionSearchPrecision([In] int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010048)]
        void GetMotionSearchPrecision(out int nVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010049)]
        void SetQuantBias([In] int nIntra, [In] int nInter);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004a)]
        void SetIDCT([In] int n);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004b)]
        void SetQuantFactor([In] float fQuantFactor);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004c)]
        void GetQuantFactor(out float pfQuantFactor);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004d)]
        void SetInterlaceMode([In] int bPreProcessDeinterlace, [In] int bInterlacedOutputDCT, [In] int bInterlacedOutputME);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001004e)]
        void GetInterlaceMode(out int bPreProcessDeinterlace, out int bInterlacedOutputDCT, out int bInterlacedOutputME);
    }
}

