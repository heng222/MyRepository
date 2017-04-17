namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, Guid("4A6D5C73-270C-4C05-871A-28230F2A8BCC"), TypeLibType((short) 2), ClassInterface((short) 0)]
    public class StandardMpegEncoderGeneralPropsClass : IPropertyPage, StandardMpegEncoderGeneralProps
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

