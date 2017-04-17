using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ProWrite.UI.Controls
{
    public class API
    {
        public const int WM_COPYDATA = 0x004A;
        public struct COPYDATASTRUCT
        {
            public IntPtr dwData;
            public int cbData;
            [MarshalAs(UnmanagedType.LPStr)]
            public string lpData;
        }

        [DllImport("USER32.dll")]
        internal static extern int SendMessage(int hWnd, int msg, int wParam, ref COPYDATASTRUCT lParam);
        [DllImport("User32.dll")]
        internal static extern int FindWindow(string lpClassName, string lpWindowName);

        public static readonly string mainWindowName = "ProWrite";

    }
}
