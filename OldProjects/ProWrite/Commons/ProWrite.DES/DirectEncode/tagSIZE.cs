namespace DirectEncodeNET
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential, Pack=4)]
    public struct tagSIZE
    {
        public int cx;
        public int cy;
    }
}

