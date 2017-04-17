namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("1C356305-4D1C-45E1-AA93-1AE16C7DE429"), TypeLibType((short) 2), ClassInterface((short) 0)]
    public class StandardMpegEncoderStatsClass : IStandardMpegEncoderStats, StandardMpegEncoderStats
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        public virtual extern void GetAudioTimeCorrected(out double dTimeCorrected);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        public virtual extern void GetFramesEncoded(out int lFramesEncoded);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        public virtual extern void GetStatusString([MarshalAs(UnmanagedType.BStr)] out string strValue);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        public virtual extern void GetVideoFramesDropped(out int lFramesDropped);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        public virtual extern void GetWrittenBytes(out int lBytesWritten);
    }
}

