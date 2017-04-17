namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("C9510218-F457-4D51-8389-7386E6EDD0EF"), TypeLibType((short) 0x40), InterfaceType((short) 1)]
    public interface IStandardMpegEncoderStats
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        void GetFramesEncoded(out int lFramesEncoded);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        void GetVideoFramesDropped(out int lFramesDropped);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        void GetAudioTimeCorrected(out double dTimeCorrected);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        void GetWrittenBytes(out int lBytesWritten);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        void GetStatusString([MarshalAs(UnmanagedType.BStr)] out string strValue);
    }
}

