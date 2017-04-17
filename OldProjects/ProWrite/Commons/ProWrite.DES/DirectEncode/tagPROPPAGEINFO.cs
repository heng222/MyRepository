namespace DirectEncodeNET
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential, Pack=4)]
    public struct tagPROPPAGEINFO
    {
        public uint cb;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string pszTitle;
        public tagSIZE size;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string pszDocString;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string pszHelpFile;
        public uint dwHelpContext;
    }
}

