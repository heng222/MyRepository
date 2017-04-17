namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, InterfaceType((short) 1), Guid("7E772181-B7ED-4D9D-A364-0E8771AAFF70"), TypeLibType((short) 0x40)]
    public interface IStandardMpegMultiplexerProfile
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        void SetDeleteElementaryStreams([In] int bDelete);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        void GetDeleteElementaryStreams(out int bDelete);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        void SetMultiplexRate([In] int nRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        void GetMultiplexRate(out int pnMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        void SetMultiplexPacketSize([In] int nSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        void GetMultiplexPacketSize(out int pnSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        void SetMultiplexPreload([In] float fPreload);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        void GetMultiplexPreload(out float pfPreload);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        void SetMultiplexMaxDelay([In] float fMaxDelay);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        void SetMultiplexStreams([In] int bMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        void GetMultiplexStreams(out int bMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        void SetMultiplexFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat format);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        void GetMultiplexFormat([ComAliasName("DirectEncodeNET.SystemsOutputFormat")] out SystemsOutputFormat format);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        void AddMultiplexFile([In, MarshalAs(UnmanagedType.BStr)] string strPath);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000e)]
        void SetOnFlyMultiplex([In] int bOnFlyMultiplex);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000f)]
        void GetOnFlyMultiplex(out int pbOnFlyMultiplex);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010010)]
        void SetMultiplexFrameBalance([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010011)]
        void SetMultiplexOnStop([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010012)]
        void GetMultiplexProgress(out double dProgress);
    }
}

