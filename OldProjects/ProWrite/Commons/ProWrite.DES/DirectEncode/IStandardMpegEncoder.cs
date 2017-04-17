namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("91D3D934-6DEE-42C5-A687-6F81E1162559"), InterfaceType((short) 1), TypeLibType((short) 0x40)]
    public interface IStandardMpegEncoder
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        void GetProfile([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint, [MarshalAs(UnmanagedType.Interface)] out StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        void GetSelectedProfile([MarshalAs(UnmanagedType.Interface)] out StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        void SelectProfile([In, MarshalAs(UnmanagedType.Interface)] StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        void SelectFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        void SetFilterLicenseKey([In, MarshalAs(UnmanagedType.BStr)] string strLicense);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        void SaveSettings([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        void LoadSettings([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        void PassThruCmd([In, MarshalAs(UnmanagedType.BStr)] string strCmd, [In] int nCmd, [In] double dCmd, out byte pCmd);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        void SetErrorBoxDisplay([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        void SetPass([In] int n);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        void SetSourceFramerate([In] double dSourceFramerate, out double dRequiredInputFramerate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        void ActivateAudioVideoOutputPins([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        void GetAudioVideoOutputPinsActivated(out int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        void EnableFramerateCorrection([In] int bCorrectVideo, [In] int bCorrectAudio);
    }
}

