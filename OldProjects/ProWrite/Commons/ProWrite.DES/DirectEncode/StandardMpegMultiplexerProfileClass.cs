namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("022A32A5-3689-4D5F-B8CC-C26655C2BA03"), ClassInterface((short) 0), TypeLibType((short) 2)]
    public class StandardMpegMultiplexerProfileClass : IStandardMpegMultiplexerProfile, StandardMpegMultiplexerProfile
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000d)]
        public virtual extern void AddMultiplexFile([In, MarshalAs(UnmanagedType.BStr)] string strPath);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010001)]
        public virtual extern void GetDeleteElementaryStreams(out int bDelete);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000c)]
        public virtual extern void GetMultiplexFormat([ComAliasName("DirectEncodeNET.SystemsOutputFormat")] out SystemsOutputFormat format);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010005)]
        public virtual extern void GetMultiplexPacketSize(out int pnSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010007)]
        public virtual extern void GetMultiplexPreload(out float pfPreload);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010012)]
        public virtual extern void GetMultiplexProgress(out double dProgress);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010003)]
        public virtual extern void GetMultiplexRate(out int pnMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000a)]
        public virtual extern void GetMultiplexStreams(out int bMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000f)]
        public virtual extern void GetOnFlyMultiplex(out int pbOnFlyMultiplex);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010000)]
        public virtual extern void SetDeleteElementaryStreams([In] int bDelete);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000b)]
        public virtual extern void SetMultiplexFormat([In, ComAliasName("DirectEncodeNET.SystemsOutputFormat")] SystemsOutputFormat format);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010010)]
        public virtual extern void SetMultiplexFrameBalance([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010008)]
        public virtual extern void SetMultiplexMaxDelay([In] float fMaxDelay);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010011)]
        public virtual extern void SetMultiplexOnStop([In] int bVal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010004)]
        public virtual extern void SetMultiplexPacketSize([In] int nSize);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010006)]
        public virtual extern void SetMultiplexPreload([In] float fPreload);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010002)]
        public virtual extern void SetMultiplexRate([In] int nRate);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x60010009)]
        public virtual extern void SetMultiplexStreams([In] int bMux);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime), DispId(0x6001000e)]
        public virtual extern void SetOnFlyMultiplex([In] int bOnFlyMultiplex);
    }
}

