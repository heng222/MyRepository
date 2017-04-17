namespace DirectEncodeNET
{
    using System;
    using System.Runtime.CompilerServices;
    using System.Runtime.InteropServices;

    [ComImport, InterfaceType((short) 1), Guid("B196B28D-BAB4-101A-B69C-00AA00341D07")]
    public interface IPropertyPage
    {
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void SetPageSite([In, MarshalAs(UnmanagedType.Interface)] IPropertyPageSite pPageSite);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Activate([In, ComAliasName("DirectEncodeNET.wireHWND")] ref _RemotableHandle hWndParent, [In] ref tagRECT pRect, [In] int bModal);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Deactivate();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void GetPageInfo(out tagPROPPAGEINFO pPageInfo);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void SetObjects([In] uint cObjects, [In, MarshalAs(UnmanagedType.IUnknown)] ref object ppUnk);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Show([In] uint nCmdShow);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Move([In] ref tagRECT pRect);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void IsPageDirty();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Apply();
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void Help([In, MarshalAs(UnmanagedType.LPWStr)] string pszHelpDir);
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType=MethodCodeType.Runtime)]
        void TranslateAccelerator([In] ref tagMSG pMsg);
    }
}

