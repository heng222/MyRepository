namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("CFD87339-C61F-46CA-B6A1-F87D6B96243E"), ClassInterface((short) 0), TypeLibType((short) 2)]
    public class StandardMpegEncoderClass : IStandardMpegEncoder, StandardMpegEncoder
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        public virtual extern void ActivateAudioVideoOutputPins([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        public virtual extern void EnableFramerateCorrection([In] int bCorrectVideo, [In] int bCorrectAudio);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        public virtual extern void GetAudioVideoOutputPinsActivated(out int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        public virtual extern void GetProfile([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint, [MarshalAs(UnmanagedType.Interface)] out StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        public virtual extern void GetSelectedProfile([MarshalAs(UnmanagedType.Interface)] out StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        public virtual extern void LoadSettings([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        public virtual extern void PassThruCmd([In, MarshalAs(UnmanagedType.BStr)] string strCmd, [In] int nCmd, [In] double dCmd, out byte pCmd);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        public virtual extern void SaveSettings([In, MarshalAs(UnmanagedType.BStr)] string strKey);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        public virtual extern void SelectFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat systemsFormat, [In, ComAliasName("DirectEncodeNET.Constraint")] Constraint Constraint);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        public virtual extern void SelectProfile([In, MarshalAs(UnmanagedType.Interface)] StandardMpegEncoderProfile pProfile);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        public virtual extern void SetErrorBoxDisplay([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        public virtual extern void SetFilterLicenseKey([In, MarshalAs(UnmanagedType.BStr)] string strLicense);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        public virtual extern void SetPass([In] int n);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        public virtual extern void SetSourceFramerate([In] double dSourceFramerate, out double dRequiredInputFramerate);
    }
}

