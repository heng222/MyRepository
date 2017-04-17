namespace DirectEncodeNET
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential, Pack=4), ComConversionLoss]
    public struct tagMSG
    {
        [ComAliasName("DirectEncodeNET.wireHWND"), ComConversionLoss]
        public IntPtr hwnd;
        public uint message;
        public uint wParam;
        public int lParam;
        public uint time;
        public tagPOINT pt;
    }
}

