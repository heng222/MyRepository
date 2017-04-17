namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, ClassInterface((short) 0), Guid("DCD4E0B0-FE55-44C6-9B4C-1E78FA2D6D2C"), TypeLibType((short) 2)]
    public class StandardMpegEncoderVideoPropsClass : IPropertyPage, StandardMpegEncoderVideoProps
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Activate([In, ComAliasName("DirectEncodeNET.wireHWND")] ref _RemotableHandle hWndParent, [In] ref tagRECT pRect, [In] int bModal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Apply();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Deactivate();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void GetPageInfo(out tagPROPPAGEINFO pPageInfo);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Help([In, MarshalAs(UnmanagedType.LPWStr)] string pszHelpDir);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void IsPageDirty();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Move([In] ref tagRECT pRect);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void SetObjects([In] uint cObjects, [In, MarshalAs(UnmanagedType.IUnknown)] ref object ppUnk);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void SetPageSite([In, MarshalAs(UnmanagedType.Interface)] IPropertyPageSite pPageSite);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void Show([In] uint nCmdShow);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        public virtual extern void TranslateAccelerator([In] ref tagMSG pMsg);
    }
}

