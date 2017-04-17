using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Security;
using Microsoft.Win32.SafeHandles;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.ComponentModel;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public enum FontSmoothing
    {
        /// <summary>
        /// Specifies that text should be anti-aliased, but sharp. This should employ
        /// the same method that the OS uses for UI text, albeit with AA forced on.
        /// </summary>
        /// <remarks>
        /// On Windows, this uses GDI for rendering. ClearType is not used.
        /// </remarks>
        Sharp,

        /// <summary>
        /// Specifies that text should be anti-aliased in a smoother manner.
        /// </summary>
        /// <remarks>
        /// On Windows, this uses GDI+ for rendering. ClearType is not used.
        /// </remarks>
        Smooth
    }

    [SuppressUnmanagedCodeSecurity]
    internal static class SafeNativeMethods
    {
        [DllImport("kernel32.dll", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool IsProcessorFeaturePresent(uint ProcessorFeature);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool DrawMenuBar(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = false)]
        internal static extern IntPtr GetSystemMenu(
            IntPtr hWnd,
            [MarshalAs(UnmanagedType.Bool)] bool bRevert);

        [DllImport("user32.dll", SetLastError = false)]
        internal static extern int EnableMenuItem(
            IntPtr hMenu,
            uint uIDEnableItem,
            uint uEnable);

        [DllImport("user32.dll", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool FlashWindow(
            IntPtr hWnd,
            [MarshalAs(UnmanagedType.Bool)] bool bInvert);

        [DllImport("dwmapi.dll")]
        internal unsafe static extern int DwmGetWindowAttribute(
            IntPtr hwnd,
            uint dwAttribute,
            void* pvAttribute,
            uint cbAttribute);

        [DllImport("kernel32.dll", SetLastError = false)]
        internal static extern IntPtr GetCurrentThread();

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetThreadPriority(
            IntPtr hThread,
            int nPriority);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr CreateFileMappingW(
            IntPtr hFile,
            IntPtr lpFileMappingAttributes,
            uint flProtect,
            uint dwMaximumSizeHigh,
            uint dwMaximumSizeLow,
            [MarshalAs(UnmanagedType.LPTStr)] string lpName);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr MapViewOfFile(
            IntPtr hFileMappingObject,
            uint dwDesiredAccess,
            uint dwFileOffsetHigh,
            uint dwFileOffsetLow,
            UIntPtr dwNumberOfBytesToMap);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool UnmapViewOfFile(IntPtr lpBaseAddress);


        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool ShowScrollBar(
            IntPtr hWnd,
            int wBar,
            [MarshalAs(UnmanagedType.Bool)] bool bShow);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GetVersionEx(ref NativeStructs.OSVERSIONINFOEX lpVersionInfo);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GetLayeredWindowAttributes(
            IntPtr hwnd,
            out uint pcrKey,
            out byte pbAlpha,
            out uint pdwFlags);

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Portability", "CA1901:PInvokeDeclarationsShouldBePortable", MessageId = "2")]
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetLayeredWindowAttributes(
            IntPtr hwnd,
            uint crKey,
            byte bAlpha,
            uint dwFlags);

        [DllImport("gdi32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr CreateFontW(
            int nHeight,
            int nWidth,
            int nEscapement,
            int nOrientation,
            int fnWeight,
            uint fdwItalic,
            uint fdwUnderline,
            uint fdwStrikeOut,
            uint fdwCharSet,
            uint fdwOutputPrecision,
            uint fdwClipPrecision,
            uint fdwQuality,
            uint fdwPitchAndFamily,
            string lpszFace);

        [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern int DrawTextW(
            IntPtr hdc,
            string lpString,
            int nCount,
            ref NativeStructs.RECT lpRect,
            uint uFormat);

        [DllImport("gdi32.dll", SetLastError = true)]
        internal static extern IntPtr CreateDIBSection(
            IntPtr hdc,
            ref NativeStructs.BITMAPINFO pbmi,
            uint iUsage,
            out IntPtr ppvBits,
            IntPtr hSection,
            uint dwOffset);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr CreateFileW(
            string lpFileName,
            uint dwDesiredAccess,
            uint dwShareMode,
            IntPtr lpSecurityAttributes,
            uint dwCreationDisposition,
            uint dwFlagsAndAttributes,
            IntPtr hTemplateFile);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal unsafe static extern bool WriteFile(
            IntPtr hFile,
            void* lpBuffer,
            uint nNumberOfBytesToWrite,
            out uint lpNumberOfBytesWritten,
            IntPtr lpOverlapped);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal unsafe static extern bool ReadFile(
            SafeFileHandle sfhFile,
            void* lpBuffer,
            uint nNumberOfBytesToRead,
            out uint lpNumberOfBytesRead,
            IntPtr lpOverlapped);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetHandleInformation(
            IntPtr hObject,
            uint dwMask,
            uint dwFlags);

        [DllImport("user32.dll", SetLastError = false)]
        internal static extern int GetUpdateRgn(
            IntPtr hWnd,
            IntPtr hRgn,
            [MarshalAs(UnmanagedType.Bool)] bool bErase);

        [DllImport("user32.dll", SetLastError = false)]
        internal static extern uint GetWindowThreadProcessId(
            IntPtr hWnd,
            out uint lpdwProcessId);

        [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr FindWindowW(
            [MarshalAs(UnmanagedType.LPWStr)] string lpClassName,
            [MarshalAs(UnmanagedType.LPWStr)] string lpWindowName);

        [DllImport("user32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr FindWindowExW(
            IntPtr hwndParent,
            IntPtr hwndChildAfter,
            [MarshalAs(UnmanagedType.LPWStr)] string lpszClass,
            [MarshalAs(UnmanagedType.LPWStr)] string lpszWindow);

        [DllImport("user32.dll", SetLastError = false)]
        internal static extern IntPtr SendMessageW(
            IntPtr hWnd,
            uint msg,
            IntPtr wParam,
            IntPtr lParam);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal extern static bool PostMessageW(
            IntPtr handle,
            uint msg,
            IntPtr wParam,
            IntPtr lParam);

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern uint GetWindowLongW(
            IntPtr hWnd,
            int nIndex);

        [DllImport("user32.dll", SetLastError = true)]
        internal static extern uint SetWindowLongW(
            IntPtr hWnd,
            int nIndex,
            uint dwNewLong);


        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool QueryPerformanceCounter(out ulong lpPerformanceCount);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool QueryPerformanceFrequency(out ulong lpFrequency);

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        internal static extern unsafe void memcpy(void* dst, void* src, UIntPtr length);

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        internal static extern unsafe void memset(void* dst, int c, UIntPtr length);

        [DllImport("User32.dll", SetLastError = false)]
        internal static extern int GetSystemMetrics(int nIndex);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern uint WaitForSingleObject(
            IntPtr hHandle,
            uint dwMilliseconds);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern uint WaitForMultipleObjects(
            uint nCount,
            IntPtr[] lpHandles,
            [MarshalAs(UnmanagedType.Bool)] bool bWaitAll,
            uint dwMilliseconds);

        internal static uint WaitForMultipleObjects(IntPtr[] lpHandles, bool bWaitAll, uint dwMilliseconds)
        {
            return WaitForMultipleObjects((uint)lpHandles.Length, lpHandles, bWaitAll, dwMilliseconds);
        }

        [DllImport("wtsapi32.dll", SetLastError = true)]
        internal static extern uint WTSRegisterSessionNotification(IntPtr hWnd, uint dwFlags);

        [DllImport("wtsapi32.dll", SetLastError = true)]
        internal static extern uint WTSUnRegisterSessionNotification(IntPtr hWnd);

        [DllImport("Gdi32.dll", SetLastError = true)]
        internal unsafe static extern uint GetRegionData(
            IntPtr hRgn,
            uint dwCount,
            NativeStructs.RGNDATA* lpRgnData);

        [DllImport("Gdi32.dll", SetLastError = true)]
        internal unsafe static extern IntPtr CreateRectRgn(
            int nLeftRect,
            int nTopRect,
            int nRightRect,
            int nBottomRect);

        [DllImport("Gdi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal extern static bool MoveToEx(
            IntPtr hdc,
            int X,
            int Y,
            out NativeStructs.POINT lpPoint);

        [DllImport("Gdi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal extern static bool LineTo(
            IntPtr hdc,
            int nXEnd,
            int nYEnd);

        [DllImport("User32.dll", SetLastError = true)]
        internal extern static int FillRect(
            IntPtr hDC,
            ref NativeStructs.RECT lprc,
            IntPtr hbr);

        [DllImport("Gdi32.dll", SetLastError = true)]
        internal extern static IntPtr CreatePen(
            int fnPenStyle,
            int nWidth,
            uint crColor);

        [DllImport("Gdi32.dll", SetLastError = true)]
        internal extern static IntPtr CreateSolidBrush(uint crColor);

        [DllImport("Gdi32.dll", SetLastError = false)]
        internal extern static IntPtr SelectObject(
            IntPtr hdc,
            IntPtr hgdiobj);

        [DllImport("Gdi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal extern static bool DeleteObject(IntPtr hObject);

        [DllImport("Gdi32.dll", SetLastError = true)]
        internal extern static uint DeleteDC(IntPtr hdc);

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static IntPtr CreateCompatibleDC(IntPtr hdc);

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static uint BitBlt(
            IntPtr hdcDest,
            int nXDest,
            int nYDest,
            int nWidth,
            int nHeight,
            IntPtr hdcSrc,
            int nXSrc,
            int nYSrc,
            uint dwRop);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern IntPtr VirtualAlloc(
            IntPtr lpAddress,
            UIntPtr dwSize,
            uint flAllocationType,
            uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool VirtualFree(
            IntPtr lpAddress,
            UIntPtr dwSize,
            uint dwFreeType);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool VirtualProtect(
            IntPtr lpAddress,
            UIntPtr dwSize,
            uint flNewProtect,
            out uint lpflOldProtect);

        [DllImport("Kernel32.dll", SetLastError = false)]
        internal static extern IntPtr HeapAlloc(IntPtr hHeap, uint dwFlags, UIntPtr dwBytes);

        [DllImport("Kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool HeapFree(IntPtr hHeap, uint dwFlags, IntPtr lpMem);

        [DllImport("Kernel32.dll", SetLastError = false)]
        internal static extern UIntPtr HeapSize(IntPtr hHeap, uint dwFlags, IntPtr lpMem);

        [DllImport("Kernel32.dll", SetLastError = true)]
        internal static extern IntPtr HeapCreate(
            uint flOptions,
            [MarshalAs(UnmanagedType.SysUInt)] IntPtr dwInitialSize,
            [MarshalAs(UnmanagedType.SysUInt)] IntPtr dwMaximumSize
            );

        [DllImport("Kernel32.dll", SetLastError = true)]
        internal static extern uint HeapDestroy(IntPtr hHeap);

        [DllImport("Kernel32.Dll", SetLastError = true)]
        internal unsafe static extern uint HeapSetInformation(
            IntPtr HeapHandle,
            int HeapInformationClass,
            void* HeapInformation,
            uint HeapInformationLength
            );

        [DllImport("winhttp.dll", CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool WinHttpGetIEProxyConfigForCurrentUser(ref NativeStructs.WINHTTP_CURRENT_USER_IE_PROXY_CONFIG pProxyConfig);

        [DllImport("kernel32.dll", SetLastError = true)]
        internal static extern IntPtr GlobalFree(IntPtr hMem);

        [DllImport("user32.dll", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool IsIconic(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static uint StretchBlt(
             IntPtr hdcDest,      // handle to destination DC
              int nXOriginDest, // x-coord of destination upper-left corner
              int nYOriginDest, // y-coord of destination upper-left corner
              int nWidthDest,   // width of destination rectangle
              int nHeightDest,  // height of destination rectangle
              IntPtr hdcSrc,       // handle to source DC
              int nXOriginSrc,  // x-coord of source upper-left corner
              int nYOriginSrc,  // y-coord of source upper-left corner
              int nWidthSrc,    // width of source rectangle
              int nHeightSrc,   // height of source rectangle
              uint dwRop       // raster operation code
            );

        [DllImport("Msimg32.dll", SetLastError = true)]
        internal extern static bool TransparentBlt(
            IntPtr hdcDest,        // handle to destination DC
            int nXOriginDest,   // x-coord of destination upper-left corner
            int nYOriginDest,   // y-coord of destination upper-left corner
            int nWidthDest,     // width of destination rectangle
            int hHeightDest,    // height of destination rectangle
            IntPtr hdcSrc,         // handle to source DC
            int nXOriginSrc,    // x-coord of source upper-left corner
            int nYOriginSrc,    // y-coord of source upper-left corner
            int nWidthSrc,      // width of source rectangle
            int nHeightSrc,     // height of source rectangle
            NativeStructs.RGBQUAD crTransparent  // color to make transparent

            );

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static bool SetBkColor(
            IntPtr hdc,           // handle to DC
            NativeStructs.RGBQUAD crColor   // background color value


            );

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static IntPtr CreateCompatibleBitmap(
            IntPtr hdc,
            int nWidth,
            int nHeight);

        [DllImport("Gdi32.Dll", SetLastError = true)]
        internal extern static NativeStructs.RGBQUAD SetTextColor(
            IntPtr hdc,           // handle to DC
            NativeStructs.RGBQUAD crColor   // text color

            );
    }

    internal static class NativeStructs
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct PROCESS_INFORMATION
        {
            public IntPtr hProcess;
            public IntPtr hThread;
            public uint dwProcessId;
            public uint dwThreadId;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct STATSTG
        {
            public IntPtr pwcsName;
            public NativeConstants.STGTY type;
            public ulong cbSize;
            public System.Runtime.InteropServices.ComTypes.FILETIME mtime;
            public System.Runtime.InteropServices.ComTypes.FILETIME ctime;
            public System.Runtime.InteropServices.ComTypes.FILETIME atime;
            public uint grfMode;
            public uint grfLocksSupported;
            public Guid clsid;
            public uint grfStateBits;
            public uint reserved;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 4)]
        internal struct KNOWNFOLDER_DEFINITION
        {
            public NativeConstants.KF_CATEGORY category;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszName;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszCreator;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszDescription;
            public Guid fidParent;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszRelativePath;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszParsingName;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszToolTip;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszLocalizedName;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszIcon;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszSecurity;
            public uint dwAttributes;
            public NativeConstants.KF_DEFINITION_FLAGS kfdFlags;
            public Guid ftidType;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        internal struct PROPERTYKEY
        {
            public Guid fmtid;
            public uint pid;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 4)]
        internal struct COMDLG_FILTERSPEC
        {
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszName;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string pszSpec;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct SYSTEM_INFO
        {
            public ushort wProcessorArchitecture;
            public ushort wReserved;
            public uint dwPageSize;
            public IntPtr lpMinimumApplicationAddress;
            public IntPtr lpMaximumApplicationAddress;
            public UIntPtr dwActiveProcessorMask;
            public uint dwNumberOfProcessors;
            public uint dwProcessorType;
            public uint dwAllocationGranularity;
            public ushort wProcessorLevel;
            public ushort wProcessorRevision;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct OSVERSIONINFOEX
        {
            public static int SizeOf
            {
                get
                {
                    return Marshal.SizeOf(typeof(OSVERSIONINFOEX));
                }
            }

            public uint dwOSVersionInfoSize;
            public uint dwMajorVersion;
            public uint dwMinorVersion;
            public uint dwBuildNumber;
            public uint dwPlatformId;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
            public string szCSDVersion;

            public ushort wServicePackMajor;

            public ushort wServicePackMinor;
            public ushort wSuiteMask;
            public byte wProductType;
            public byte wReserved;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct COPYDATASTRUCT
        {
            internal UIntPtr dwData;
            internal uint cbData;
            internal IntPtr lpData;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct SHELLEXECUTEINFO
        {
            internal uint cbSize;
            internal uint fMask;
            internal IntPtr hwnd;
            [MarshalAs(UnmanagedType.LPTStr)]
            internal string lpVerb;
            [MarshalAs(UnmanagedType.LPTStr)]
            internal string lpFile;
            [MarshalAs(UnmanagedType.LPTStr)]
            internal string lpParameters;
            [MarshalAs(UnmanagedType.LPTStr)]
            internal string lpDirectory;
            internal int nShow;
            internal IntPtr hInstApp;
            internal IntPtr lpIDList;
            [MarshalAs(UnmanagedType.LPTStr)]
            internal string lpClass;
            internal IntPtr hkeyClass;
            internal uint dwHotKey;
            internal IntPtr hIcon_or_hMonitor;
            internal IntPtr hProcess;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct MEMORYSTATUSEX
        {
            internal uint dwLength;
            internal uint dwMemoryLoad;
            internal ulong ullTotalPhys;
            internal ulong ullAvailPhys;
            internal ulong ullTotalPageFile;
            internal ulong ullAvailPageFile;
            internal ulong ullTotalVirtual;
            internal ulong ullAvailVirtual;
            internal ulong ullAvailExtendedVirtual;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct OVERLAPPED
        {
            internal UIntPtr Internal;
            internal UIntPtr InternalHigh;
            internal uint Offset;
            internal uint OffsetHigh;
            internal IntPtr hEvent;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct RGBQUAD
        {
            internal byte rgbBlue;
            internal byte rgbGreen;
            internal byte rgbRed;
            internal byte rgbReserved;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct BITMAPINFOHEADER
        {
            internal uint biSize;
            internal int biWidth;
            internal int biHeight;
            internal ushort biPlanes;
            internal ushort biBitCount;
            internal uint biCompression;
            internal uint biSizeImage;
            internal int biXPelsPerMeter;
            internal int biYPelsPerMeter;
            internal uint biClrUsed;
            internal uint biClrImportant;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct BITMAPINFO
        {
            internal BITMAPINFOHEADER bmiHeader;
            internal RGBQUAD bmiColors;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal unsafe struct MEMORY_BASIC_INFORMATION
        {
            internal void* BaseAddress;
            internal void* AllocationBase;
            internal uint AllocationProtect;
            internal UIntPtr RegionSize;
            internal uint State;
            internal uint Protect;
            internal uint Type;
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal class LOGFONT
        {
            internal int lfHeight = 0;
            internal int lfWidth = 0;
            internal int lfEscapement = 0;
            internal int lfOrientation = 0;
            internal int lfWeight = 0;
            internal byte lfItalic = 0;
            internal byte lfUnderline = 0;
            internal byte lfStrikeOut = 0;
            internal byte lfCharSet = 0;
            internal byte lfOutPrecision = 0;
            internal byte lfClipPrecision = 0;
            internal byte lfQuality = 0;
            internal byte lfPitchAndFamily = 0;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            internal string lfFaceName = string.Empty;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct LOGBRUSH
        {
            internal uint lbStyle;
            internal uint lbColor;
            internal int lbHatch;
        };

        [StructLayout(LayoutKind.Sequential)]
        internal struct RGNDATAHEADER
        {
            internal uint dwSize;
            internal uint iType;
            internal uint nCount;
            internal uint nRgnSize;
            internal RECT rcBound;
        };

        [StructLayout(LayoutKind.Sequential)]
        internal struct RGNDATA
        {
            internal RGNDATAHEADER rdh;

            internal unsafe static RECT* GetRectsPointer(RGNDATA* me)
            {
                return (RECT*)((byte*)me + sizeof(RGNDATAHEADER));
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct POINT
        {
            internal int x;
            internal int y;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct RECT
        {
            internal int left;
            internal int top;
            internal int right;
            internal int bottom;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal unsafe struct PropertyItem
        {
            internal int id;
            internal uint length;
            internal short type;
            internal void* value;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal unsafe struct WINTRUST_DATA
        {
            internal uint cbStruct;
            internal IntPtr pPolicyCallbackData;
            internal IntPtr pSIPClientData;
            internal uint dwUIChoice;
            internal uint fdwRevocationChecks;
            internal uint dwUnionChoice;
            internal void* pInfo; // pFile, pCatalog, pBlob, pSgnr, or pCert
            internal uint dwStateAction;
            internal IntPtr hWVTStateData;
            internal IntPtr pwszURLReference;
            internal uint dwProvFlags;
            internal uint dwUIContext;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal unsafe struct WINTRUST_FILE_INFO
        {
            internal uint cbStruct;
            internal char* pcwszFilePath;
            internal IntPtr hFile;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        internal struct WINHTTP_CURRENT_USER_IE_PROXY_CONFIG
        {
            internal bool fAutoDetect;
            internal IntPtr lpszAutoConfigUrl;
            internal IntPtr lpszProxy;
            internal IntPtr lpszProxyBypass;
        };

        [StructLayout(LayoutKind.Sequential)]
        internal struct SP_DEVINFO_DATA
        {
            public uint cbSize;
            public Guid ClassGuid;
            public uint DevInst;
            public UIntPtr Reserved;
        }
    }

    public static class Fonts
    {
        /// <summary>
        /// Determines whether a font uses the 'symbol' character set.
        /// </summary>
        /// <remarks>
        /// Symbol fonts do not typically contain glyphs that represent letters of the alphabet.
        /// Instead they might contain pictures and symbols. As such, they are not useful for
        /// drawing text. Which means you can't use a symbol font to write out its own name for
        /// illustrative purposes (like for the font drop-down chooser).
        /// </remarks>
        public static bool IsSymbolFont(Font font)
        {
            NativeStructs.LOGFONT logFont = new NativeStructs.LOGFONT();
            font.ToLogFont(logFont);
            return logFont.lfCharSet == NativeConstants.SYMBOL_CHARSET;
        }

        public static IntPtr CreateFontObject(Font font, bool antiAliasing)
        {
            NativeStructs.LOGFONT logFont = new NativeStructs.LOGFONT();
            font.ToLogFont(logFont);

            int nHeight = logFont.lfHeight;
            int nWidth = logFont.lfWidth;
            int nEscapement = logFont.lfEscapement;
            int nOrientation = logFont.lfOrientation;
            int fnWeight = logFont.lfWeight;
            uint fdwItalic = logFont.lfItalic;
            uint fdwUnderline = logFont.lfUnderline;
            uint fdwStrikeOut = logFont.lfStrikeOut;
            uint fdwCharSet = logFont.lfCharSet;
            uint fdwOutputPrecision = logFont.lfOutPrecision;
            uint fdwClipPrecision = logFont.lfClipPrecision;
            uint fdwQuality;

            if (antiAliasing)
            {
                fdwQuality = NativeConstants.ANTIALIASED_QUALITY;
            }
            else
            {
                fdwQuality = NativeConstants.NONANTIALIASED_QUALITY;
            }

            uint fdwPitchAndFamily = logFont.lfPitchAndFamily;
            string lpszFace = logFont.lfFaceName;

            IntPtr hFont = SafeNativeMethods.CreateFontW(
                nHeight,
                nWidth,
                nEscapement,
                nOrientation,
                fnWeight,
                fdwItalic,
                fdwUnderline,
                fdwStrikeOut,
                fdwCharSet,
                fdwOutputPrecision,
                fdwClipPrecision,
                fdwQuality,
                fdwPitchAndFamily,
                lpszFace);

            if (hFont == IntPtr.Zero)
            {
                NativeMethods.ThrowOnWin32Error("CreateFontW returned NULL");
            }

            return hFont;
        }

        /// <summary>
        /// Measures text with the given graphics context, font, string, location, and anti-aliasing flag.
        /// </summary>
        /// <param name="g">The Graphics context to measure for.</param>
        /// <param name="font">The Font to measure with.</param>
        /// <param name="text">The string of text to measure.</param>
        /// <param name="antiAliasing">Whether the font should be rendered with anti-aliasing.</param>
        public static Size MeasureString(Graphics g, Font font, string text, bool antiAliasing, FontSmoothing fontSmoothing)
        {
            if (fontSmoothing == FontSmoothing.Smooth && antiAliasing)
            {
                PixelOffsetMode oldPOM = g.PixelOffsetMode;
                g.PixelOffsetMode = PixelOffsetMode.Half;

                TextRenderingHint oldTRH = g.TextRenderingHint;
                g.TextRenderingHint = TextRenderingHint.AntiAlias;

                StringFormat format = (StringFormat)StringFormat.GenericTypographic.Clone();
                format.FormatFlags |= StringFormatFlags.MeasureTrailingSpaces;

                SizeF sf = g.MeasureString(text, font, new PointF(0, 0), format);
                sf.Height = font.GetHeight();

                g.PixelOffsetMode = oldPOM;
                g.TextRenderingHint = oldTRH;
                return Size.Ceiling(sf);
            }
            else if (fontSmoothing == FontSmoothing.Sharp || !antiAliasing)
            {
                IntPtr hdc = IntPtr.Zero;
                IntPtr hFont = IntPtr.Zero;
                IntPtr hOldObject = IntPtr.Zero;

                try
                {
                    hdc = g.GetHdc();
                    hFont = CreateFontObject(font, antiAliasing);
                    hOldObject = SafeNativeMethods.SelectObject(hdc, hFont);

                    NativeStructs.RECT rect = new NativeStructs.RECT();
                    rect.left = 0;
                    rect.top = 0;
                    rect.right = rect.left;
                    rect.bottom = rect.top;

                    int result = SafeNativeMethods.DrawTextW(
                        hdc,
                        text,
                        text.Length,
                        ref rect,
                        NativeConstants.DT_CALCRECT |
                            NativeConstants.DT_LEFT |
                            NativeConstants.DT_NOCLIP |
                            NativeConstants.DT_NOPREFIX |
                            NativeConstants.DT_SINGLELINE |
                            NativeConstants.DT_TOP);

                    if (result == 0)
                    {
                        NativeMethods.ThrowOnWin32Error("DrawTextW returned 0");
                    }

                    return new Size(rect.right - rect.left, rect.bottom - rect.top);
                }

                finally
                {
                    if (hOldObject != IntPtr.Zero)
                    {
                        SafeNativeMethods.SelectObject(hdc, hOldObject);
                        hOldObject = IntPtr.Zero;
                    }

                    if (hFont != IntPtr.Zero)
                    {
                        SafeNativeMethods.DeleteObject(hFont);
                        hFont = IntPtr.Zero;
                    }

                    if (hdc != IntPtr.Zero)
                    {
                        g.ReleaseHdc(hdc);
                        hdc = IntPtr.Zero;
                    }
                }
            }
            else
            {
                throw new InvalidEnumArgumentException("fontSmoothing = " + (int)fontSmoothing);
            }
        }

        /// <summary>
        /// Renders text with the given graphics context, font, string, location, and anti-aliasing flag.
        /// </summary>
        /// <param name="g">The Graphics context to render to.</param>
        /// <param name="font">The Font to render with.</param>
        /// <param name="text">The string of text to draw.</param>
        /// <param name="pt">The offset of where to start drawing (upper-left of rendering rectangle).</param>
        /// <param name="antiAliasing">Whether the font should be rendered with anti-aliasing.</param>
        public static void DrawText(Graphics g, Font font, string text, Point pt, bool antiAliasing, FontSmoothing fontSmoothing)
        {
            if (fontSmoothing == FontSmoothing.Smooth && antiAliasing)
            {
                PixelOffsetMode oldPOM = g.PixelOffsetMode;
                g.PixelOffsetMode = PixelOffsetMode.Half;

                TextRenderingHint oldTRH = g.TextRenderingHint;
                g.TextRenderingHint = TextRenderingHint.AntiAlias;

                StringFormat format = (StringFormat)StringFormat.GenericTypographic.Clone();
                format.FormatFlags |= StringFormatFlags.MeasureTrailingSpaces;

                g.DrawString(text, font, Brushes.Black, pt, format);

                g.PixelOffsetMode = oldPOM;
                g.TextRenderingHint = oldTRH;
            }
            else if (fontSmoothing == FontSmoothing.Sharp || !antiAliasing)
            {
                IntPtr hdc = IntPtr.Zero;
                IntPtr hFont = IntPtr.Zero;
                IntPtr hOldObject = IntPtr.Zero;

                try
                {
                    hdc = g.GetHdc();
                    hFont = CreateFontObject(font, antiAliasing);
                    hOldObject = SafeNativeMethods.SelectObject(hdc, hFont);

                    NativeStructs.RECT rect = new NativeStructs.RECT();
                    rect.left = pt.X;
                    rect.top = pt.Y;
                    rect.right = rect.left;
                    rect.bottom = rect.top;

                    int result = SafeNativeMethods.DrawTextW(
                        hdc,
                        text,
                        text.Length,
                        ref rect,
                        NativeConstants.DT_LEFT |
                            NativeConstants.DT_NOCLIP |
                            NativeConstants.DT_NOPREFIX |
                            NativeConstants.DT_SINGLELINE |
                            NativeConstants.DT_TOP);

                    //uint result1 = SafeNativeMethods.StretchBlt(
                    //    0,
                    //    0,
                    //    20,
                    //    20,
                    //    hdc,
                    //    0,
                    //    0,
                    //    20 * 1000,
                    //    20 * 1000,
                    //    NativeConstants.SRCCOPY);

                    if (result == 0)
                    {
                        NativeMethods.ThrowOnWin32Error("DrawTextW returned 0");
                    }
                }

                finally
                {
                    if (hOldObject != IntPtr.Zero)
                    {
                        SafeNativeMethods.SelectObject(hdc, hOldObject);
                        hOldObject = IntPtr.Zero;
                    }

                    if (hFont != IntPtr.Zero)
                    {
                        SafeNativeMethods.DeleteObject(hFont);
                        hFont = IntPtr.Zero;
                    }

                    if (hdc != IntPtr.Zero)
                    {
                        g.ReleaseHdc(hdc);
                        hdc = IntPtr.Zero;
                    }
                }
            }
            else
            {
                throw new InvalidEnumArgumentException("fontSmoothing = " + (int)fontSmoothing);
            }
        }
    }

    internal static class NativeConstants
    {
        public const int MAX_PATH = 260;

        public const int CSIDL_DESKTOP_DIRECTORY = 0x0010;        // C:\Users\[user]\Desktop\
        public const int CSIDL_MYPICTURES = 0x0027;
        public const int CSIDL_PERSONAL = 0x0005;

        public const int CSIDL_PROGRAM_FILES = 0x0026;            // C:\Program Files\
        public const int CSIDL_APPDATA = 0x001a;                  // C:\Users\[user]\AppData\Roaming\
        public const int CSIDL_LOCAL_APPDATA = 0x001c;            // C:\Users\[user]\AppData\Local\
        public const int CSIDL_COMMON_DESKTOPDIRECTORY = 0x0019;  // C:\Users\All Users\Desktop

        public const int CSIDL_FLAG_CREATE = 0x8000;    // new for Win2K, or this in to force creation of folder

        public const uint SHGFP_TYPE_CURRENT = 0;
        public const uint SHGFP_TYPE_DEFAULT = 1;

        public const int BP_COMMANDLINK = 6;

        public const int CMDLS_NORMAL = 1;
        public const int CMDLS_HOT = 2;
        public const int CMDLS_PRESSED = 3;
        public const int CMDLS_DISABLED = 4;
        public const int CMDLS_DEFAULTED = 5;
        public const int CMDLS_DEFAULTED_ANIMATING = 6;

        public enum SECURITY_IMPERSONATION_LEVEL
        {
            SecurityAnonymous = 0,
            SecurityIdentification = 1,
            SecurityImpersonation = 2,
            SecurityDelegation = 3
        }

        public enum TOKEN_TYPE
        {
            TokenPrimary = 1,
            TokenImpersonation = 2
        }

        public const uint TOKEN_ASSIGN_PRIMARY = 0x0001;
        public const uint TOKEN_DUPLICATE = 0x0002;
        public const uint TOKEN_IMPERSONATE = 0x0004;
        public const uint TOKEN_QUERY = 0x0008;
        public const uint TOKEN_QUERY_SOURCE = 0x0010;
        public const uint TOKEN_ADJUST_PRIVILEGES = 0x0020;
        public const uint TOKEN_ADJUST_GROUPS = 0x0040;
        public const uint TOKEN_ADJUST_DEFAULT = 0x0080;
        public const uint TOKEN_ADJUST_SESSIONID = 0x0100;

        public const uint TOKEN_ALL_ACCESS_P =
            STANDARD_RIGHTS_REQUIRED |
            TOKEN_ASSIGN_PRIMARY |
            TOKEN_DUPLICATE |
            TOKEN_IMPERSONATE |
            TOKEN_QUERY |
            TOKEN_QUERY_SOURCE |
            TOKEN_ADJUST_PRIVILEGES |
            TOKEN_ADJUST_GROUPS |
            TOKEN_ADJUST_DEFAULT;

        public const uint TOKEN_ALL_ACCESS = TOKEN_ALL_ACCESS_P | TOKEN_ADJUST_SESSIONID;
        public const uint TOKEN_READ = STANDARD_RIGHTS_READ | TOKEN_QUERY;
        public const uint TOKEN_WRITE = STANDARD_RIGHTS_WRITE | TOKEN_ADJUST_PRIVILEGES | TOKEN_ADJUST_GROUPS | TOKEN_ADJUST_DEFAULT;
        public const uint TOKEN_EXECUTE = STANDARD_RIGHTS_EXECUTE;

        public const uint MAXIMUM_ALLOWED = 0x02000000;

        public const uint PROCESS_TERMINATE = 0x0001;
        public const uint PROCESS_CREATE_THREAD = 0x0002;
        public const uint PROCESS_SET_SESSIONID = 0x0004;
        public const uint PROCESS_VM_OPERATION = 0x0008;
        public const uint PROCESS_VM_READ = 0x0010;
        public const uint PROCESS_VM_WRITE = 0x0020;
        public const uint PROCESS_DUP_HANDLE = 0x0040;
        public const uint PROCESS_CREATE_PROCESS = 0x0080;
        public const uint PROCESS_SET_QUOTA = 0x0100;
        public const uint PROCESS_SET_INFORMATION = 0x0200;
        public const uint PROCESS_QUERY_INFORMATION = 0x0400;
        public const uint PROCESS_SUSPEND_RESUME = 0x0800;
        public const uint PROCESS_QUERY_LIMITED_INFORMATION = 0x1000;
        public const uint PROCESS_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF;

        public const uint PF_NX_ENABLED = 12;
        public const uint PF_XMMI_INSTRUCTIONS_AVAILABLE = 6;
        public const uint PF_XMMI64_INSTRUCTIONS_AVAILABLE = 10;
        public const uint PF_SSE3_INSTRUCTIONS_AVAILABLE = 13;

        public const uint CF_ENHMETAFILE = 14;

        public static Guid BHID_Stream
        {
            get
            {
                return new Guid(0x1cebb3ab, 0x7c10, 0x499a, 0xa4, 0x17, 0x92, 0xca, 0x16, 0xc4, 0xcb, 0x83);
            }
        }

        public const string IID_IOleWindow = "00000114-0000-0000-C000-000000000046";
        public const string IID_IModalWindow = "b4db1657-70d7-485e-8e3e-6fcb5a5c1802";
        public const string IID_IFileDialog = "42f85136-db7e-439c-85f1-e4075d135fc8";
        public const string IID_IFileOpenDialog = "d57c7288-d4ad-4768-be02-9d969532d960";
        public const string IID_IFileSaveDialog = "84bccd23-5fde-4cdb-aea4-af64b83d78ab";
        public const string IID_IFileDialogEvents = "973510DB-7D7F-452B-8975-74A85828D354";
        public const string IID_IFileDialogControlEvents = "36116642-D713-4b97-9B83-7484A9D00433";
        public const string IID_IFileDialogCustomize = "8016b7b3-3d49-4504-a0aa-2a37494e606f";
        public const string IID_IShellItem = "43826D1E-E718-42EE-BC55-A1E261C37BFE";
        public const string IID_IShellItemArray = "B63EA76D-1F85-456F-A19C-48159EFA858B";
        public const string IID_IKnownFolder = "38521333-6A87-46A7-AE10-0F16706816C3";
        public const string IID_IKnownFolderManager = "44BEAAEC-24F4-4E90-B3F0-23D258FBB146";
        public const string IID_IPropertyStore = "886D8EEB-8CF2-4446-8D02-CDBA1DBDCF99";

        public const string IID_ISequentialStream = "0c733a30-2a1c-11ce-ade5-00aa0044773d";
        public const string IID_IStream = "0000000C-0000-0000-C000-000000000046";

        public const string IID_IFileOperation = "947aab5f-0a5c-4c13-b4d6-4bf7836fc9f8";
        public const string IID_IFileOperationProgressSink = "04b0f1a7-9490-44bc-96e1-4296a31252e2";

        public const string CLSID_FileOpenDialog = "DC1C5A9C-E88A-4dde-A5A1-60F82A20AEF7";
        public const string CLSID_FileSaveDialog = "C0B4E2F3-BA21-4773-8DBA-335EC946EB8B";
        public const string CLSID_KnownFolderManager = "4df0c730-df9d-4ae3-9153-aa6b82e9795a";
        public const string CLSID_FileOperation = "3ad05575-8857-4850-9277-11b85bdb8e09";

        public enum FOF
            : uint
        {
            FOF_MULTIDESTFILES = 0x0001,
            FOF_CONFIRMMOUSE = 0x0002,
            FOF_SILENT = 0x0004,                // don't display progress UI (confirm prompts may be displayed still)
            FOF_RENAMEONCOLLISION = 0x0008,     // automatically rename the source files to avoid the collisions
            FOF_NOCONFIRMATION = 0x0010,        // don't display confirmation UI, assume "yes" for cases that can be bypassed, "no" for those that can not
            FOF_WANTMAPPINGHANDLE = 0x0020,     // Fill in SHFILEOPSTRUCT.hNameMappings
            // Must be freed using SHFreeNameMappings
            FOF_ALLOWUNDO = 0x0040,             // enable undo including Recycle behavior for IFileOperation::Delete()
            FOF_FILESONLY = 0x0080,             // only operate on the files (non folders), both files and folders are assumed without this
            FOF_SIMPLEPROGRESS = 0x0100,        // means don't show names of files
            FOF_NOCONFIRMMKDIR = 0x0200,        // don't dispplay confirmatino UI before making any needed directories, assume "Yes" in these cases
            FOF_NOERRORUI = 0x0400,             // don't put up error UI, other UI may be displayed, progress, confirmations
            FOF_NOCOPYSECURITYATTRIBS = 0x0800, // dont copy file security attributes (ACLs)
            FOF_NORECURSION = 0x1000,           // don't recurse into directories for operations that would recurse
            FOF_NO_CONNECTED_ELEMENTS = 0x2000, // don't operate on connected elements ("xxx_files" folders that go with .htm files)
            FOF_WANTNUKEWARNING = 0x4000,       // during delete operation, warn if nuking instead of recycling (partially overrides FOF_NOCONFIRMATION)
            FOF_NORECURSEREPARSE = 0x8000,      // deprecated; the operations engine always does the right thing on FolderLink objects (symlinks, reparse points, folder shortcuts)

            FOF_NO_UI = (FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR), // don't display any UI at all

            FOFX_NOSKIPJUNCTIONS = 0x00010000,        // Don't avoid binding to junctions (like Task folder, Recycle-Bin)
            FOFX_PREFERHARDLINK = 0x00020000,         // Create hard link if possible
            FOFX_SHOWELEVATIONPROMPT = 0x00040000,    // Show elevation prompts when error UI is disabled (use with FOF_NOERRORUI)
            FOFX_EARLYFAILURE = 0x00100000,           // Fail operation as soon as a single error occurs rather than trying to process other items (applies only when using FOF_NOERRORUI)
            FOFX_PRESERVEFILEEXTENSIONS = 0x00200000, // Rename collisions preserve file extns (use with FOF_RENAMEONCOLLISION)
            FOFX_KEEPNEWERFILE = 0x00400000,          // Keep newer file on naming conflicts
            FOFX_NOCOPYHOOKS = 0x00800000,            // Don't use copy hooks
            FOFX_NOMINIMIZEBOX = 0x01000000,          // Don't allow minimizing the progress dialog
            FOFX_MOVEACLSACROSSVOLUMES = 0x02000000,  // Copy security information when performing a cross-volume move operation
            FOFX_DONTDISPLAYSOURCEPATH = 0x04000000,  // Don't display the path of source file in progress dialog
            FOFX_DONTDISPLAYDESTPATH = 0x08000000,    // Don't display the path of destination file in progress dialog
        }

        public enum STATFLAG
            : uint
        {
            STATFLAG_DEFAULT = 0,
            STATFLAG_NONAME = 1,
            STATFLAG_NOOPEN = 2
        }

        public enum STGTY
            : uint
        {
            STGTY_STORAGE = 1,
            STGTY_STREAM = 2,
            STGTY_LOCKBYTES = 3,
            STGTY_PROPERTY = 4
        }

        [Flags]
        public enum STGC
            : uint
        {
            STGC_DEFAULT = 0,
            STGC_OVERWRITE = 1,
            STGC_ONLYIFCURRENT = 2,
            STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4,
            STGC_CONSOLIDATE = 8
        }

        public enum CDCONTROLSTATE
        {
            CDCS_INACTIVE = 0x00000000,
            CDCS_ENABLED = 0x00000001,
            CDCS_VISIBLE = 0x00000002
        }

        public enum FFFP_MODE
        {
            FFFP_EXACTMATCH,
            FFFP_NEARESTPARENTMATCH
        }

        public enum SIATTRIBFLAGS
        {
            SIATTRIBFLAGS_AND = 0x00000001, // if multiple items and the attirbutes together.
            SIATTRIBFLAGS_OR = 0x00000002, // if multiple items or the attributes together.
            SIATTRIBFLAGS_APPCOMPAT = 0x00000003, // Call GetAttributes directly on the ShellFolder for multiple attributes
        }

        public enum SIGDN : uint
        {
            SIGDN_NORMALDISPLAY = 0x00000000,                 // SHGDN_NORMAL
            SIGDN_PARENTRELATIVEPARSING = 0x80018001,         // SHGDN_INFOLDER | SHGDN_FORPARSING
            SIGDN_DESKTOPABSOLUTEPARSING = 0x80028000,        // SHGDN_FORPARSING
            SIGDN_PARENTRELATIVEEDITING = 0x80031001,         // SHGDN_INFOLDER | SHGDN_FOREDITING
            SIGDN_DESKTOPABSOLUTEEDITING = 0x8004c000,        // SHGDN_FORPARSING | SHGDN_FORADDRESSBAR
            SIGDN_FILESYSPATH = 0x80058000,                   // SHGDN_FORPARSING
            SIGDN_URL = 0x80068000,                           // SHGDN_FORPARSING
            SIGDN_PARENTRELATIVEFORADDRESSBAR = 0x8007c001,   // SHGDN_INFOLDER | SHGDN_FORPARSING | SHGDN_FORADDRESSBAR
            SIGDN_PARENTRELATIVE = 0x80080001                 // SHGDN_INFOLDER
        }

        public const uint DROPEFFECT_COPY = 1;
        public const uint DROPEFFECT_MOVE = 2;
        public const uint DROPEFFECT_LINK = 4;

        [Flags]
        public enum SFGAO : uint
        {
            SFGAO_CANCOPY = DROPEFFECT_COPY,        // Objects can be copied (0x1)
            SFGAO_CANMOVE = DROPEFFECT_MOVE,        // Objects can be moved (0x2)
            SFGAO_CANLINK = DROPEFFECT_LINK,        // Objects can be linked (0x4)
            SFGAO_STORAGE = 0x00000008,             // supports BindToObject(IID_IStorage)
            SFGAO_CANRENAME = 0x00000010,           // Objects can be renamed
            SFGAO_CANDELETE = 0x00000020,           // Objects can be deleted
            SFGAO_HASPROPSHEET = 0x00000040,        // Objects have property sheets
            SFGAO_DROPTARGET = 0x00000100,          // Objects are drop target
            SFGAO_CAPABILITYMASK = 0x00000177,
            SFGAO_ENCRYPTED = 0x00002000,           // Object is encrypted (use alt color)
            SFGAO_ISSLOW = 0x00004000,              // 'Slow' object
            SFGAO_GHOSTED = 0x00008000,             // Ghosted icon
            SFGAO_LINK = 0x00010000,                // Shortcut (link)
            SFGAO_SHARE = 0x00020000,               // Shared
            SFGAO_READONLY = 0x00040000,            // Read-only
            SFGAO_HIDDEN = 0x00080000,              // Hidden object
            SFGAO_DISPLAYATTRMASK = 0x000FC000,
            SFGAO_FILESYSANCESTOR = 0x10000000,     // May contain children with SFGAO_FILESYSTEM
            SFGAO_FOLDER = 0x20000000,              // Support BindToObject(IID_IShellFolder)
            SFGAO_FILESYSTEM = 0x40000000,          // Is a win32 file system object (file/folder/root)
            SFGAO_HASSUBFOLDER = 0x80000000,        // May contain children with SFGAO_FOLDER (may be slow)
            SFGAO_CONTENTSMASK = 0x80000000,
            SFGAO_VALIDATE = 0x01000000,            // Invalidate cached information (may be slow)
            SFGAO_REMOVABLE = 0x02000000,           // Is this removeable media?
            SFGAO_COMPRESSED = 0x04000000,          // Object is compressed (use alt color)
            SFGAO_BROWSABLE = 0x08000000,           // Supports IShellFolder, but only implements CreateViewObject() (non-folder view)
            SFGAO_NONENUMERATED = 0x00100000,       // Is a non-enumerated object (should be hidden)
            SFGAO_NEWCONTENT = 0x00200000,          // Should show bold in explorer tree
            SFGAO_STREAM = 0x00400000,              // Supports BindToObject(IID_IStream)
            SFGAO_CANMONIKER = 0x00400000,          // Obsolete
            SFGAO_HASSTORAGE = 0x00400000,          // Obsolete
            SFGAO_STORAGEANCESTOR = 0x00800000,     // May contain children with SFGAO_STORAGE or SFGAO_STREAM
            SFGAO_STORAGECAPMASK = 0x70C50008,      // For determining storage capabilities, ie for open/save semantics
            SFGAO_PKEYSFGAOMASK = 0x81044010        // Attributes that are masked out for PKEY_SFGAOFlags because they are considered to cause slow calculations or lack context (SFGAO_VALIDATE | SFGAO_ISSLOW | SFGAO_HASSUBFOLDER and others)
        }

        public enum FDE_OVERWRITE_RESPONSE
        {
            FDEOR_DEFAULT = 0x00000000,
            FDEOR_ACCEPT = 0x00000001,
            FDEOR_REFUSE = 0x00000002
        }

        public enum FDE_SHAREVIOLATION_RESPONSE
        {
            FDESVR_DEFAULT = 0x00000000,
            FDESVR_ACCEPT = 0x00000001,
            FDESVR_REFUSE = 0x00000002
        }

        public enum FDAP
        {
            FDAP_BOTTOM = 0x00000000,
            FDAP_TOP = 0x00000001,
        }

        [Flags]
        public enum FOS : uint
        {
            FOS_OVERWRITEPROMPT = 0x00000002,
            FOS_STRICTFILETYPES = 0x00000004,
            FOS_NOCHANGEDIR = 0x00000008,
            FOS_PICKFOLDERS = 0x00000020,
            FOS_FORCEFILESYSTEM = 0x00000040, // Ensure that items returned are filesystem items.
            FOS_ALLNONSTORAGEITEMS = 0x00000080, // Allow choosing items that have no storage.
            FOS_NOVALIDATE = 0x00000100,
            FOS_ALLOWMULTISELECT = 0x00000200,
            FOS_PATHMUSTEXIST = 0x00000800,
            FOS_FILEMUSTEXIST = 0x00001000,
            FOS_CREATEPROMPT = 0x00002000,
            FOS_SHAREAWARE = 0x00004000,
            FOS_NOREADONLYRETURN = 0x00008000,
            FOS_NOTESTFILECREATE = 0x00010000,
            FOS_HIDEMRUPLACES = 0x00020000,
            FOS_HIDEPINNEDPLACES = 0x00040000,
            FOS_NODEREFERENCELINKS = 0x00100000,
            FOS_DONTADDTORECENT = 0x02000000,
            FOS_FORCESHOWHIDDEN = 0x10000000,
            FOS_DEFAULTNOMINIMODE = 0x20000000
        }

        public enum KF_CATEGORY
        {
            KF_CATEGORY_VIRTUAL = 0x00000001,
            KF_CATEGORY_FIXED = 0x00000002,
            KF_CATEGORY_COMMON = 0x00000003,
            KF_CATEGORY_PERUSER = 0x00000004
        }

        [Flags]
        public enum KF_DEFINITION_FLAGS
        {
            KFDF_PERSONALIZE = 0x00000001,
            KFDF_LOCAL_REDIRECT_ONLY = 0x00000002,
            KFDF_ROAMABLE = 0x00000004,
        }

        public const uint DWMWA_NCRENDERING_ENABLED = 1;           // [get] Is non-client rendering enabled/disabled
        public const uint DWMWA_NCRENDERING_POLICY = 2;            // [set] Non-client rendering policy
        public const uint DWMWA_TRANSITIONS_FORCEDISABLED = 3;     // [set] Potentially enable/forcibly disable transitions
        public const uint DWMWA_ALLOW_NCPAINT = 4;                 // [set] Allow contents rendered in the non-client area to be visible on the DWM-drawn frame.
        public const uint DWMWA_CAPTION_BUTTON_BOUNDS = 5;         // [get] Bounds of the caption button area in window-relative space.
        public const uint DWMWA_NONCLIENT_RTL_LAYOUT = 6;          // [set] Is non-client content RTL mirrored
        public const uint DWMWA_FORCE_ICONIC_REPRESENTATION = 7;   // [set] Force this window to display iconic thumbnails.
        public const uint DWMWA_FLIP3D_POLICY = 8;                 // [set] Designates how Flip3D will treat the window.
        public const uint DWMWA_EXTENDED_FRAME_BOUNDS = 9;         // [get] Gets the extended frame bounds rectangle in screen space
        public const uint DWMWA_LAST = 10;

        public const uint DWMNCRP_USEWINDOWSTYLE = 0;
        public const uint DWMNCRP_DISABLED = 1;
        public const uint DWMNCRP_ENABLED = 2;
        public const uint DWMNCRP_LAST = 3;

        public const byte VER_EQUAL = 1;
        public const byte VER_GREATER = 2;
        public const byte VER_GREATER_EQUAL = 3;
        public const byte VER_LESS = 4;
        public const byte VER_LESS_EQUAL = 5;
        public const byte VER_AND = 6;
        public const byte VER_OR = 7;

        public const uint VER_CONDITION_MASK = 7;
        public const uint VER_NUM_BITS_PER_CONDITION_MASK = 3;

        public const uint VER_MINORVERSION = 0x0000001;
        public const uint VER_MAJORVERSION = 0x0000002;
        public const uint VER_BUILDNUMBER = 0x0000004;
        public const uint VER_PLATFORMID = 0x0000008;
        public const uint VER_SERVICEPACKMINOR = 0x0000010;
        public const uint VER_SERVICEPACKMAJOR = 0x0000020;
        public const uint VER_SUITENAME = 0x0000040;
        public const uint VER_PRODUCT_TYPE = 0x0000080;

        public const uint VER_PLATFORM_WIN32s = 0;
        public const uint VER_PLATFORM_WIN32_WINDOWS = 1;
        public const uint VER_PLATFORM_WIN32_NT = 2;

        public const int THREAD_MODE_BACKGROUND_BEGIN = 0x10000;
        public const int THREAD_MODE_BACKGROUND_END = 0x20000;

        private static uint CTL_CODE(uint deviceType, uint function, uint method, uint access)
        {
            return (deviceType << 16) | (access << 14) | (function << 2) | method;
        }

        public const uint FILE_DEVICE_FILE_SYSTEM = 0x00000009;
        public const uint METHOD_BUFFERED = 0;

        public static readonly uint FSCTL_SET_COMPRESSION =
            CTL_CODE(FILE_DEVICE_FILE_SYSTEM, 16, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA);

        public static ushort COMPRESSION_FORMAT_DEFAULT = 1;

        public const int SW_HIDE = 0;
        public const int SW_SHOWNORMAL = 1;
        public const int SW_NORMAL = 1;
        public const int SW_SHOWMINIMIZED = 2;
        public const int SW_SHOWMAXIMIZED = 3;
        public const int SW_MAXIMIZE = 3;
        public const int SW_SHOWNOACTIVATE = 4;
        public const int SW_SHOW = 5;
        public const int SW_MINIMIZE = 6;
        public const int SW_SHOWMINNOACTIVE = 7;
        public const int SW_SHOWNA = 8;
        public const int SW_RESTORE = 9;
        public const int SW_SHOWDEFAULT = 10;
        public const int SW_FORCEMINIMIZE = 11;
        public const int SW_MAX = 11;

        public const uint MF_BYCOMMAND = 0;
        public const uint MF_GRAYED = 1;
        public const uint MF_DISABLED = 2;
        public const uint SC_CLOSE = 0xf060;

        public const uint SEE_MASK_CLASSNAME = 0x00000001;
        public const uint SEE_MASK_CLASSKEY = 0x00000003;
        public const uint SEE_MASK_IDLIST = 0x00000004;
        public const uint SEE_MASK_INVOKEIDLIST = 0x0000000c;
        public const uint SEE_MASK_ICON = 0x00000010;
        public const uint SEE_MASK_HOTKEY = 0x00000020;
        public const uint SEE_MASK_NOCLOSEPROCESS = 0x00000040;
        public const uint SEE_MASK_CONNECTNETDRV = 0x00000080;
        public const uint SEE_MASK_FLAG_DDEWAIT = 0x00000100;
        public const uint SEE_MASK_DOENVSUBST = 0x00000200;
        public const uint SEE_MASK_FLAG_NO_UI = 0x00000400;
        public const uint SEE_MASK_UNICODE = 0x00004000;
        public const uint SEE_MASK_NO_CONSOLE = 0x00008000;
        public const uint SEE_MASK_ASYNCOK = 0x00100000;
        public const uint SEE_MASK_HMONITOR = 0x00200000;
        public const uint SEE_MASK_NOZONECHECKS = 0x00800000;
        public const uint SEE_MASK_NOQUERYCLASSSTORE = 0x01000000;
        public const uint SEE_MASK_WAITFORINPUTIDLE = 0x02000000;
        public const uint SEE_MASK_FLAG_LOG_USAGE = 0x04000000;

        public const uint SHARD_PIDL = 0x00000001;
        public const uint SHARD_PATHA = 0x00000002;
        public const uint SHARD_PATHW = 0x00000003;

        public const uint VER_NT_WORKSTATION = 0x0000001;
        public const uint VER_NT_DOMAIN_CONTROLLER = 0x0000002;
        public const uint VER_NT_SERVER = 0x0000003;

        public const uint LWA_COLORKEY = 0x00000001;
        public const uint LWA_ALPHA = 0x00000002;
        public const uint WS_EX_LAYERED = 0x00080000;

        public const ushort PROCESSOR_ARCHITECTURE_INTEL = 0;
        public const ushort PROCESSOR_ARCHITECTURE_IA64 = 6;
        public const ushort PROCESSOR_ARCHITECTURE_AMD64 = 9;
        public const ushort PROCESSOR_ARCHITECTURE_UNKNOWN = 0xFFFF;

        public const uint SHVIEW_THUMBNAIL = 0x702d;

        public const uint MA_ACTIVATE = 1;
        public const uint MA_ACTIVATEANDEAT = 2;
        public const uint MA_NOACTIVATE = 3;
        public const uint MA_NOACTIVATEANDEAT = 4;

        public const uint IDI_APPLICATION = 32512;

        public const int ERROR_SUCCESS = 0;
        public const int ERROR_ALREADY_EXISTS = 183;
        public const int ERROR_CANCELLED = 1223;
        public const int ERROR_IO_PENDING = 0x3e5;
        public const int ERROR_NO_MORE_ITEMS = 259;
        public const int ERROR_TIMEOUT = 1460;

        public const uint DIGCF_PRESENT = 2;

        public const int GWL_STYLE = -16;
        public const int GWL_EXSTYLE = -20;

        public const int GWLP_WNDPROC = -4;
        public const int GWLP_HINSTANCE = -6;
        public const int GWLP_HWNDPARENT = -8;
        public const int GWLP_USERDATA = -21;
        public const int GWLP_ID = -12;

        public const uint PBS_SMOOTH = 0x01;
        public const uint PBS_MARQUEE = 0x08;
        public const int PBM_SETMARQUEE = WM_USER + 10;

        public const int SBM_SETPOS = 0x00E0;
        public const int SBM_SETRANGE = 0x00E2;
        public const int SBM_SETRANGEREDRAW = 0x00E6;
        public const int SBM_SETSCROLLINFO = 0x00E9;

        public const int BCM_FIRST = 0x1600;
        public const int BCM_SETSHIELD = BCM_FIRST + 0x000C;

        public const int CB_SHOWDROPDOWN = 0x014f;

        public const uint WM_COMMAND = 0x111;
        public const uint WM_MOUSEACTIVATE = 0x21;
        public const uint WM_COPYDATA = 0x004a;

        public const uint SMTO_NORMAL = 0x0000;
        public const uint SMTO_BLOCK = 0x0001;
        public const uint SMTO_ABORTIFHUNG = 0x0002;
        public const uint SMTO_NOTIMEOUTIFNOTHUNG = 0x0008;

        public const int WM_USER = 0x400;
        public const int WM_HSCROLL = 0x114;
        public const int WM_VSCROLL = 0x115;
        public const int WM_SETFOCUS = 7;
        public const int WM_QUERYENDSESSION = 0x0011;
        public const int WM_ACTIVATE = 0x006;
        public const int WM_ACTIVATEAPP = 0x01C;
        public const int WM_PAINT = 0x000f;
        public const int WM_NCPAINT = 0x0085;
        public const int WM_NCACTIVATE = 0x086;
        public const int WM_SETREDRAW = 0x000B;

        public const uint WS_VSCROLL = 0x00200000;
        public const uint WS_HSCROLL = 0x00100000;

        public const uint BS_MULTILINE = 0x00002000;

        public const uint ANSI_CHARSET = 0;
        public const uint DEFAULT_CHARSET = 1;
        public const uint SYMBOL_CHARSET = 2;
        public const uint SHIFTJIS_CHARSET = 128;
        public const uint HANGEUL_CHARSET = 129;
        public const uint HANGUL_CHARSET = 129;
        public const uint GB2312_CHARSET = 134;
        public const uint CHINESEBIG5_CHARSET = 136;
        public const uint OEM_CHARSET = 255;
        public const uint JOHAB_CHARSET = 130;
        public const uint HEBREW_CHARSET = 177;
        public const uint ARABIC_CHARSET = 178;
        public const uint GREEK_CHARSET = 161;
        public const uint TURKISH_CHARSET = 162;
        public const uint VIETNAMESE_CHARSET = 163;
        public const uint THAI_CHARSET = 222;
        public const uint EASTEUROPE_CHARSET = 238;
        public const uint RUSSIAN_CHARSET = 204;
        public const uint MAC_CHARSET = 77;
        public const uint BALTIC_CHARSET = 186;

        public const uint SPI_GETBEEP = 0x0001;
        public const uint SPI_SETBEEP = 0x0002;
        public const uint SPI_GETMOUSE = 0x0003;
        public const uint SPI_SETMOUSE = 0x0004;
        public const uint SPI_GETBORDER = 0x0005;
        public const uint SPI_SETBORDER = 0x0006;
        public const uint SPI_GETKEYBOARDSPEED = 0x000A;
        public const uint SPI_SETKEYBOARDSPEED = 0x000B;
        public const uint SPI_LANGDRIVER = 0x000C;
        public const uint SPI_ICONHORIZONTALSPACING = 0x000D;
        public const uint SPI_GETSCREENSAVETIMEOUT = 0x000E;
        public const uint SPI_SETSCREENSAVETIMEOUT = 0x000F;
        public const uint SPI_GETSCREENSAVEACTIVE = 0x0010;
        public const uint SPI_SETSCREENSAVEACTIVE = 0x0011;
        public const uint SPI_GETGRIDGRANULARITY = 0x0012;
        public const uint SPI_SETGRIDGRANULARITY = 0x0013;
        public const uint SPI_SETDESKWALLPAPER = 0x0014;
        public const uint SPI_SETDESKPATTERN = 0x0015;
        public const uint SPI_GETKEYBOARDDELAY = 0x0016;
        public const uint SPI_SETKEYBOARDDELAY = 0x0017;
        public const uint SPI_ICONVERTICALSPACING = 0x0018;
        public const uint SPI_GETICONTITLEWRAP = 0x0019;
        public const uint SPI_SETICONTITLEWRAP = 0x001A;
        public const uint SPI_GETMENUDROPALIGNMENT = 0x001B;
        public const uint SPI_SETMENUDROPALIGNMENT = 0x001C;
        public const uint SPI_SETDOUBLECLKWIDTH = 0x001D;
        public const uint SPI_SETDOUBLECLKHEIGHT = 0x001E;
        public const uint SPI_GETICONTITLELOGFONT = 0x001F;
        public const uint SPI_SETDOUBLECLICKTIME = 0x0020;
        public const uint SPI_SETMOUSEBUTTONSWAP = 0x0021;
        public const uint SPI_SETICONTITLELOGFONT = 0x0022;
        public const uint SPI_GETFASTTASKSWITCH = 0x0023;
        public const uint SPI_SETFASTTASKSWITCH = 0x0024;
        public const uint SPI_SETDRAGFULLWINDOWS = 0x0025;
        public const uint SPI_GETDRAGFULLWINDOWS = 0x0026;
        public const uint SPI_GETNONCLIENTMETRICS = 0x0029;
        public const uint SPI_SETNONCLIENTMETRICS = 0x002A;
        public const uint SPI_GETMINIMIZEDMETRICS = 0x002B;
        public const uint SPI_SETMINIMIZEDMETRICS = 0x002C;
        public const uint SPI_GETICONMETRICS = 0x002D;
        public const uint SPI_SETICONMETRICS = 0x002E;
        public const uint SPI_SETWORKAREA = 0x002F;
        public const uint SPI_GETWORKAREA = 0x0030;
        public const uint SPI_SETPENWINDOWS = 0x0031;
        public const uint SPI_GETHIGHCONTRAST = 0x0042;
        public const uint SPI_SETHIGHCONTRAST = 0x0043;
        public const uint SPI_GETKEYBOARDPREF = 0x0044;
        public const uint SPI_SETKEYBOARDPREF = 0x0045;
        public const uint SPI_GETSCREENREADER = 0x0046;
        public const uint SPI_SETSCREENREADER = 0x0047;
        public const uint SPI_GETANIMATION = 0x0048;
        public const uint SPI_SETANIMATION = 0x0049;
        public const uint SPI_GETFONTSMOOTHING = 0x004A;
        public const uint SPI_SETFONTSMOOTHING = 0x004B;
        public const uint SPI_SETDRAGWIDTH = 0x004C;
        public const uint SPI_SETDRAGHEIGHT = 0x004D;
        public const uint SPI_SETHANDHELD = 0x004E;
        public const uint SPI_GETLOWPOWERTIMEOUT = 0x004F;
        public const uint SPI_GETPOWEROFFTIMEOUT = 0x0050;
        public const uint SPI_SETLOWPOWERTIMEOUT = 0x0051;
        public const uint SPI_SETPOWEROFFTIMEOUT = 0x0052;
        public const uint SPI_GETLOWPOWERACTIVE = 0x0053;
        public const uint SPI_GETPOWEROFFACTIVE = 0x0054;
        public const uint SPI_SETLOWPOWERACTIVE = 0x0055;
        public const uint SPI_SETPOWEROFFACTIVE = 0x0056;
        public const uint SPI_SETCURSORS = 0x0057;
        public const uint SPI_SETICONS = 0x0058;
        public const uint SPI_GETDEFAULTINPUTLANG = 0x0059;
        public const uint SPI_SETDEFAULTINPUTLANG = 0x005A;
        public const uint SPI_SETLANGTOGGLE = 0x005B;
        public const uint SPI_GETWINDOWSEXTENSION = 0x005C;
        public const uint SPI_SETMOUSETRAILS = 0x005D;
        public const uint SPI_GETMOUSETRAILS = 0x005E;
        public const uint SPI_SETSCREENSAVERRUNNING = 0x0061;
        public const uint SPI_SCREENSAVERRUNNING = SPI_SETSCREENSAVERRUNNING;
        public const uint SPI_GETFILTERKEYS = 0x0032;
        public const uint SPI_SETFILTERKEYS = 0x0033;
        public const uint SPI_GETTOGGLEKEYS = 0x0034;
        public const uint SPI_SETTOGGLEKEYS = 0x0035;
        public const uint SPI_GETMOUSEKEYS = 0x0036;
        public const uint SPI_SETMOUSEKEYS = 0x0037;
        public const uint SPI_GETSHOWSOUNDS = 0x0038;
        public const uint SPI_SETSHOWSOUNDS = 0x0039;
        public const uint SPI_GETSTICKYKEYS = 0x003A;
        public const uint SPI_SETSTICKYKEYS = 0x003B;
        public const uint SPI_GETACCESSTIMEOUT = 0x003C;
        public const uint SPI_SETACCESSTIMEOUT = 0x003D;
        public const uint SPI_GETSERIALKEYS = 0x003E;
        public const uint SPI_SETSERIALKEYS = 0x003F;
        public const uint SPI_GETSOUNDSENTRY = 0x0040;
        public const uint SPI_SETSOUNDSENTRY = 0x0041;
        public const uint SPI_GETSNAPTODEFBUTTON = 0x005F;
        public const uint SPI_SETSNAPTODEFBUTTON = 0x0060;
        public const uint SPI_GETMOUSEHOVERWIDTH = 0x0062;
        public const uint SPI_SETMOUSEHOVERWIDTH = 0x0063;
        public const uint SPI_GETMOUSEHOVERHEIGHT = 0x0064;
        public const uint SPI_SETMOUSEHOVERHEIGHT = 0x0065;
        public const uint SPI_GETMOUSEHOVERTIME = 0x0066;
        public const uint SPI_SETMOUSEHOVERTIME = 0x0067;
        public const uint SPI_GETWHEELSCROLLLINES = 0x0068;
        public const uint SPI_SETWHEELSCROLLLINES = 0x0069;
        public const uint SPI_GETMENUSHOWDELAY = 0x006A;
        public const uint SPI_SETMENUSHOWDELAY = 0x006B;
        public const uint SPI_GETSHOWIMEUI = 0x006E;
        public const uint SPI_SETSHOWIMEUI = 0x006F;
        public const uint SPI_GETMOUSESPEED = 0x0070;
        public const uint SPI_SETMOUSESPEED = 0x0071;
        public const uint SPI_GETSCREENSAVERRUNNING = 0x0072;
        public const uint SPI_GETDESKWALLPAPER = 0x0073;
        public const uint SPI_GETACTIVEWINDOWTRACKING = 0x1000;
        public const uint SPI_SETACTIVEWINDOWTRACKING = 0x1001;
        public const uint SPI_GETMENUANIMATION = 0x1002;
        public const uint SPI_SETMENUANIMATION = 0x1003;
        public const uint SPI_GETCOMBOBOXANIMATION = 0x1004;
        public const uint SPI_SETCOMBOBOXANIMATION = 0x1005;
        public const uint SPI_GETLISTBOXSMOOTHSCROLLING = 0x1006;
        public const uint SPI_SETLISTBOXSMOOTHSCROLLING = 0x1007;
        public const uint SPI_GETGRADIENTCAPTIONS = 0x1008;
        public const uint SPI_SETGRADIENTCAPTIONS = 0x1009;
        public const uint SPI_GETKEYBOARDCUES = 0x100A;
        public const uint SPI_SETKEYBOARDCUES = 0x100B;
        public const uint SPI_GETMENUUNDERLINES = SPI_GETKEYBOARDCUES;
        public const uint SPI_SETMENUUNDERLINES = SPI_SETKEYBOARDCUES;
        public const uint SPI_GETACTIVEWNDTRKZORDER = 0x100C;
        public const uint SPI_SETACTIVEWNDTRKZORDER = 0x100D;
        public const uint SPI_GETHOTTRACKING = 0x100E;
        public const uint SPI_SETHOTTRACKING = 0x100F;
        public const uint SPI_GETMENUFADE = 0x1012;
        public const uint SPI_SETMENUFADE = 0x1013;
        public const uint SPI_GETSELECTIONFADE = 0x1014;
        public const uint SPI_SETSELECTIONFADE = 0x1015;
        public const uint SPI_GETTOOLTIPANIMATION = 0x1016;
        public const uint SPI_SETTOOLTIPANIMATION = 0x1017;
        public const uint SPI_GETTOOLTIPFADE = 0x1018;
        public const uint SPI_SETTOOLTIPFADE = 0x1019;
        public const uint SPI_GETCURSORSHADOW = 0x101A;
        public const uint SPI_SETCURSORSHADOW = 0x101B;
        public const uint SPI_GETMOUSESONAR = 0x101C;
        public const uint SPI_SETMOUSESONAR = 0x101D;
        public const uint SPI_GETMOUSECLICKLOCK = 0x101E;
        public const uint SPI_SETMOUSECLICKLOCK = 0x101F;
        public const uint SPI_GETMOUSEVANISH = 0x1020;
        public const uint SPI_SETMOUSEVANISH = 0x1021;
        public const uint SPI_GETFLATMENU = 0x1022;
        public const uint SPI_SETFLATMENU = 0x1023;
        public const uint SPI_GETDROPSHADOW = 0x1024;
        public const uint SPI_SETDROPSHADOW = 0x1025;
        public const uint SPI_GETBLOCKSENDINPUTRESETS = 0x1026;
        public const uint SPI_SETBLOCKSENDINPUTRESETS = 0x1027;
        public const uint SPI_GETUIEFFECTS = 0x103E;
        public const uint SPI_SETUIEFFECTS = 0x103F;
        public const uint SPI_GETFOREGROUNDLOCKTIMEOUT = 0x2000;
        public const uint SPI_SETFOREGROUNDLOCKTIMEOUT = 0x2001;
        public const uint SPI_GETACTIVEWNDTRKTIMEOUT = 0x2002;
        public const uint SPI_SETACTIVEWNDTRKTIMEOUT = 0x2003;
        public const uint SPI_GETFOREGROUNDFLASHCOUNT = 0x2004;
        public const uint SPI_SETFOREGROUNDFLASHCOUNT = 0x2005;
        public const uint SPI_GETCARETWIDTH = 0x2006;
        public const uint SPI_SETCARETWIDTH = 0x2007;
        public const uint SPI_GETMOUSECLICKLOCKTIME = 0x2008;
        public const uint SPI_SETMOUSECLICKLOCKTIME = 0x2009;
        public const uint SPI_GETFONTSMOOTHINGTYPE = 0x200A;
        public const uint SPI_SETFONTSMOOTHINGTYPE = 0x200B;
        public const uint SPI_GETFONTSMOOTHINGCONTRAST = 0x200C;
        public const uint SPI_SETFONTSMOOTHINGCONTRAST = 0x200D;
        public const uint SPI_GETFOCUSBORDERWIDTH = 0x200E;
        public const uint SPI_SETFOCUSBORDERWIDTH = 0x200F;
        public const uint SPI_GETFOCUSBORDERHEIGHT = 0x2010;
        public const uint SPI_SETFOCUSBORDERHEIGHT = 0x2011;
        public const uint SPI_GETFONTSMOOTHINGORIENTATION = 0x2012;
        public const uint SPI_SETFONTSMOOTHINGORIENTATION = 0x2013;

        public const uint INFINITE = 0xffffffff;
        public const uint STATUS_WAIT_0 = 0;
        public const uint STATUS_ABANDONED_WAIT_0 = 0x80;
        public const uint WAIT_FAILED = 0xffffffff;
        public const uint WAIT_TIMEOUT = 258;
        public const uint WAIT_ABANDONED = STATUS_ABANDONED_WAIT_0 + 0;
        public const uint WAIT_OBJECT_0 = STATUS_WAIT_0 + 0;
        public const uint WAIT_ABANDONED_0 = STATUS_ABANDONED_WAIT_0 + 0;
        public const uint STATUS_USER_APC = 0x000000C0;
        public const uint WAIT_IO_COMPLETION = STATUS_USER_APC;

        public const int SM_REMOTESESSION = 0x1000;
        public const int WM_WTSSESSION_CHANGE = 0x2b1;
        public const int WM_MOVING = 0x0216;
        public const uint NOTIFY_FOR_ALL_SESSIONS = 1;
        public const uint NOTIFY_FOR_THIS_SESSION = 0;

        public const int BP_PUSHBUTTON = 1;
        public const int PBS_NORMAL = 1;
        public const int PBS_HOT = 2;
        public const int PBS_PRESSED = 3;
        public const int PBS_DISABLED = 4;
        public const int PBS_DEFAULTED = 5;

        public const int PS_SOLID = 0;
        public const int PS_DASH = 1;             /* -------  */
        public const int PS_DOT = 2;              /* .......  */
        public const int PS_DASHDOT = 3;          /* _._._._  */
        public const int PS_DASHDOTDOT = 4;       /* _.._.._  */
        public const int PS_NULL = 5;
        public const int PS_INSIDEFRAME = 6;
        public const int PS_USERSTYLE = 7;
        public const int PS_ALTERNATE = 8;

        public const int PS_ENDCAP_ROUND = 0x00000000;
        public const int PS_ENDCAP_SQUARE = 0x00000100;
        public const int PS_ENDCAP_FLAT = 0x00000200;
        public const int PS_ENDCAP_MASK = 0x00000F00;

        public const int PS_JOIN_ROUND = 0x00000000;
        public const int PS_JOIN_BEVEL = 0x00001000;
        public const int PS_JOIN_MITER = 0x00002000;
        public const int PS_JOIN_MASK = 0x0000F000;

        public const int PS_COSMETIC = 0x00000000;
        public const int PS_GEOMETRIC = 0x00010000;
        public const int PS_TYPE_MASK = 0x000F0000;

        public const int BS_SOLID = 0;
        public const int BS_NULL = 1;
        public const int BS_HOLLOW = BS_NULL;
        public const int BS_HATCHED = 2;
        public const int BS_PATTERN = 3;
        public const int BS_INDEXED = 4;
        public const int BS_DIBPATTERN = 5;
        public const int BS_DIBPATTERNPT = 6;
        public const int BS_PATTERN8X8 = 7;
        public const int BS_DIBPATTERN8X8 = 8;
        public const int BS_MONOPATTERN = 9;

        public const uint SRCCOPY = 0x00CC0020;     /* dest = source  */
        public const uint SRCPAINT = 0x00EE0086;    /* dest = source OR dest */
        public const uint SRCAND = 0x008800C6;      /* dest = source AND dest */
        public const uint SRCINVERT = 0x00660046;   /* dest = source XOR dest */
        public const uint SRCERASE = 0x00440328;    /* dest = source AND (NOT dest ) */
        public const uint NOTSRCCOPY = 0x00330008;  /* dest = (NOT source) */
        public const uint NOTSRCERASE = 0x001100A6; /* dest = (NOT src) AND (NOT dest) */
        public const uint MERGECOPY = 0x00C000CA;   /* dest = (source AND pattern) */
        public const uint MERGEPAINT = 0x00BB0226;  /* dest = (NOT source) OR dest */
        public const uint PATCOPY = 0x00F00021;     /* dest = pattern  */
        public const uint PATPAINT = 0x00FB0A09;    /* dest = DPSnoo  */
        public const uint PATINVERT = 0x005A0049;   /* dest = pattern XOR dest */
        public const uint DSTINVERT = 0x00550009;   /* dest = (NOT dest) */
        public const uint BLACKNESS = 0x00000042;   /* dest = BLACK  */
        public const uint WHITENESS = 0x00FF0062;   /* dest = WHITE  */

        public const uint NOMIRRORBITMAP = 0x80000000; /* Do not Mirror the bitmap in this call */
        public const uint CAPTUREBLT = 0x40000000;     /* Include layered windows */

        // StretchBlt() Modes
        public const int BLACKONWHITE = 1;
        public const int WHITEONBLACK = 2;
        public const int COLORONCOLOR = 3;
        public const int HALFTONE = 4;
        public const int MAXSTRETCHBLTMODE = 4;

        public const int HeapCompatibilityInformation = 0;
        public const uint HEAP_NO_SERIALIZE = 0x00000001;
        public const uint HEAP_GROWABLE = 0x00000002;
        public const uint HEAP_GENERATE_EXCEPTIONS = 0x00000004;
        public const uint HEAP_ZERO_MEMORY = 0x00000008;
        public const uint HEAP_REALLOC_IN_PLACE_ONLY = 0x00000010;
        public const uint HEAP_TAIL_CHECKING_ENABLED = 0x00000020;
        public const uint HEAP_FREE_CHECKING_ENABLED = 0x00000040;
        public const uint HEAP_DISABLE_COALESCE_ON_FREE = 0x00000080;
        public const uint HEAP_CREATE_ALIGN_16 = 0x00010000;
        public const uint HEAP_CREATE_ENABLE_TRACING = 0x00020000;
        public const uint HEAP_MAXIMUM_TAG = 0x0FFF;
        public const uint HEAP_PSEUDO_TAG_FLAG = 0x8000;
        public const uint HEAP_TAG_SHIFT = 18;

        public const int SM_TABLETPC = 86;

        public const uint MONITOR_DEFAULTTONULL = 0x00000000;
        public const uint MONITOR_DEFAULTTOPRIMARY = 0x00000001;
        public const uint MONITOR_DEFAULTTONEAREST = 0x00000002;

        public const uint WTD_UI_ALL = 1;
        public const uint WTD_UI_NONE = 2;
        public const uint WTD_UI_NOBAD = 3;
        public const uint WTD_UI_NOGOOD = 4;

        public const uint WTD_REVOKE_NONE = 0;
        public const uint WTD_REVOKE_WHOLECHAIN = 1;

        public const uint WTD_CHOICE_FILE = 1;
        public const uint WTD_CHOICE_CATALOG = 2;
        public const uint WTD_CHOICE_BLOB = 3;
        public const uint WTD_CHOICE_SIGNER = 4;
        public const uint WTD_CHOICE_CERT = 5;

        public const uint WTD_STATEACTION_IGNORE = 0;
        public const uint WTD_STATEACTION_VERIFY = 1;
        public const uint WTD_STATEACTION_CLOSE = 2;
        public const uint WTD_STATEACTION_AUTO_CACHE = 3;
        public const uint WTD_STATEACTION_AUTO_CACHE_FLUSH = 4;

        public const uint WTD_PROV_FLAGS_MASK = 0x0000FFFF;
        public const uint WTD_USE_IE4_TRUST_FLAG = 0x00000001;
        public const uint WTD_NO_IE4_CHAIN_FLAG = 0x00000002;
        public const uint WTD_NO_POLICY_USAGE_FLAG = 0x00000004;
        public const uint WTD_REVOCATION_CHECK_NONE = 0x00000010;
        public const uint WTD_REVOCATION_CHECK_END_CERT = 0x00000020;
        public const uint WTD_REVOCATION_CHECK_CHAIN = 0x00000040;
        public const uint WTD_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT = 0x00000080;
        public const uint WTD_SAFER_FLAG = 0x00000100;
        public const uint WTD_HASH_ONLY_FLAG = 0x00000200;
        public const uint WTD_USE_DEFAULT_OSVER_CHECK = 0x00000400;
        public const uint WTD_LIFETIME_SIGNING_FLAG = 0x00000800;
        public const uint WTD_CACHE_ONLY_URL_RETRIEVAL = 0x00001000;

        public static Guid WINTRUST_ACTION_GENERIC_VERIFY_V2
        {
            get
            {
                return new Guid(0xaac56b, 0xcd44, 0x11d0, 0x8c, 0xc2, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee);
            }
        }

        public const uint FILE_SHARE_READ = 0x00000001;
        public const uint FILE_SHARE_WRITE = 0x00000002;
        public const uint FILE_SHARE_DELETE = 0x00000004;

        public const uint FILE_READ_DATA = 0x0001;
        public const uint FILE_LIST_DIRECTORY = 0x0001;
        public const uint FILE_WRITE_DATA = 0x0002;
        public const uint FILE_ADD_FILE = 0x0002;
        public const uint FILE_APPEND_DATA = 0x0004;
        public const uint FILE_ADD_SUBDIRECTORY = 0x0004;
        public const uint FILE_CREATE_PIPE_INSTANCE = 0x0004;

        public const uint FILE_READ_EA = 0x0008;
        public const uint FILE_WRITE_EA = 0x0010;
        public const uint FILE_EXECUTE = 0x0020;
        public const uint FILE_TRAVERSE = 0x0020;
        public const uint FILE_DELETE_CHILD = 0x0040;
        public const uint FILE_READ_ATTRIBUTES = 0x0080;
        public const uint FILE_WRITE_ATTRIBUTES = 0x0100;
        public const uint FILE_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF);
        public const uint FILE_GENERIC_READ = (STANDARD_RIGHTS_READ | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_READ_EA | SYNCHRONIZE);
        public const uint FILE_GENERIC_WRITE = (STANDARD_RIGHTS_WRITE | FILE_WRITE_DATA | FILE_WRITE_ATTRIBUTES | FILE_WRITE_EA | FILE_APPEND_DATA | SYNCHRONIZE);
        public const uint FILE_GENERIC_EXECUTE = (STANDARD_RIGHTS_EXECUTE | FILE_READ_ATTRIBUTES | FILE_EXECUTE | SYNCHRONIZE);

        public const uint READ_CONTROL = 0x00020000;
        public const uint SYNCHRONIZE = 0x00100000;
        public const uint STANDARD_RIGHTS_READ = READ_CONTROL;
        public const uint STANDARD_RIGHTS_WRITE = READ_CONTROL;
        public const uint STANDARD_RIGHTS_EXECUTE = READ_CONTROL;
        public const uint STANDARD_RIGHTS_REQUIRED = 0x000F0000;

        public const uint GENERIC_READ = 0x80000000;
        public const uint GENERIC_WRITE = 0x40000000;
        public const uint GENERIC_EXECUTE = 0x20000000;

        public const uint CREATE_NEW = 1;
        public const uint CREATE_ALWAYS = 2;
        public const uint OPEN_EXISTING = 3;
        public const uint OPEN_ALWAYS = 4;
        public const uint TRUNCATE_EXISTING = 5;

        public const uint FILE_ATTRIBUTE_READONLY = 0x00000001;
        public const uint FILE_ATTRIBUTE_HIDDEN = 0x00000002;
        public const uint FILE_ATTRIBUTE_SYSTEM = 0x00000004;
        public const uint FILE_ATTRIBUTE_DIRECTORY = 0x00000010;
        public const uint FILE_ATTRIBUTE_ARCHIVE = 0x00000020;
        public const uint FILE_ATTRIBUTE_DEVICE = 0x00000040;
        public const uint FILE_ATTRIBUTE_NORMAL = 0x00000080;
        public const uint FILE_ATTRIBUTE_TEMPORARY = 0x00000100;
        public const uint FILE_ATTRIBUTE_SPARSE_FILE = 0x00000200;
        public const uint FILE_ATTRIBUTE_REPARSE_POINT = 0x00000400;
        public const uint FILE_ATTRIBUTE_COMPRESSED = 0x00000800;
        public const uint FILE_ATTRIBUTE_OFFLINE = 0x00001000;
        public const uint FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x00002000;
        public const uint FILE_ATTRIBUTE_ENCRYPTED = 0x00004000;

        public const uint FILE_FLAG_WRITE_THROUGH = 0x80000000;
        public const uint FILE_FLAG_OVERLAPPED = 0x40000000;
        public const uint FILE_FLAG_NO_BUFFERING = 0x20000000;
        public const uint FILE_FLAG_RANDOM_ACCESS = 0x10000000;
        public const uint FILE_FLAG_SEQUENTIAL_SCAN = 0x08000000;
        public const uint FILE_FLAG_DELETE_ON_CLOSE = 0x04000000;
        public const uint FILE_FLAG_BACKUP_SEMANTICS = 0x02000000;
        public const uint FILE_FLAG_POSIX_SEMANTICS = 0x01000000;
        public const uint FILE_FLAG_OPEN_REPARSE_POINT = 0x00200000;
        public const uint FILE_FLAG_OPEN_NO_RECALL = 0x00100000;
        public const uint FILE_FLAG_FIRST_PIPE_INSTANCE = 0x00080000;

        public const uint FILE_BEGIN = 0;
        public const uint FILE_CURRENT = 1;
        public const uint FILE_END = 2;

        public static readonly IntPtr INVALID_HANDLE_VALUE = new IntPtr(-1);

        public const uint HANDLE_FLAG_INHERIT = 0x1;
        public const uint HANDLE_FLAG_PROTECT_FROM_CLOSE = 0x2;

        public const uint MEM_COMMIT = 0x1000;
        public const uint MEM_RESERVE = 0x2000;
        public const uint MEM_DECOMMIT = 0x4000;
        public const uint MEM_RELEASE = 0x8000;
        public const uint MEM_RESET = 0x80000;
        public const uint MEM_TOP_DOWN = 0x100000;
        public const uint MEM_PHYSICAL = 0x400000;

        public const uint PAGE_NOACCESS = 0x01;
        public const uint PAGE_READONLY = 0x02;
        public const uint PAGE_READWRITE = 0x04;
        public const uint PAGE_WRITECOPY = 0x08;
        public const uint PAGE_EXECUTE = 0x10;
        public const uint PAGE_EXECUTE_READ = 0x20;
        public const uint PAGE_EXECUTE_READWRITE = 0x40;
        public const uint PAGE_EXECUTE_WRITECOPY = 0x80;
        public const uint PAGE_GUARD = 0x100;
        public const uint PAGE_NOCACHE = 0x200;
        public const uint PAGE_WRITECOMBINE = 0x400;

        public const uint SEC_IMAGE = 0x1000000;
        public const uint SEC_RESERVE = 0x4000000;
        public const uint SEC_COMMIT = 0x8000000;
        public const uint SEC_NOCACHE = 0x10000000;

        public const uint SECTION_QUERY = 0x0001;
        public const uint SECTION_MAP_WRITE = 0x0002;
        public const uint SECTION_MAP_READ = 0x0004;
        public const uint SECTION_MAP_EXECUTE_EXPLICIT = 0x0020;

        public const uint FILE_MAP_COPY = SECTION_QUERY;
        public const uint FILE_MAP_WRITE = SECTION_MAP_WRITE;
        public const uint FILE_MAP_READ = SECTION_MAP_READ;
        public const uint FILE_MAP_EXECUTE = SECTION_MAP_EXECUTE_EXPLICIT;

        public const uint GMEM_FIXED = 0x0000;
        public const uint GMEM_MOVEABLE = 0x0002;
        public const uint GMEM_ZEROINIT = 0x0040;
        public const uint GHND = 0x0042;
        public const uint GPTR = 0x0040;

        public const uint DIB_RGB_COLORS = 0; /* color table in RGBs */
        public const uint DIB_PAL_COLORS = 1; /* color table in palette indices */

        public const uint BI_RGB = 0;
        public const uint BI_RLE8 = 1;
        public const uint BI_RLE4 = 2;
        public const uint BI_BITFIELDS = 3;
        public const uint BI_JPEG = 4;
        public const uint BI_PNG = 5;

        public const uint DT_TOP = 0x00000000;
        public const uint DT_LEFT = 0x00000000;
        public const uint DT_CENTER = 0x00000001;
        public const uint DT_RIGHT = 0x00000002;
        public const uint DT_VCENTER = 0x00000004;
        public const uint DT_BOTTOM = 0x00000008;
        public const uint DT_WORDBREAK = 0x00000010;
        public const uint DT_SINGLELINE = 0x00000020;
        public const uint DT_EXPANDTABS = 0x00000040;
        public const uint DT_TABSTOP = 0x00000080;
        public const uint DT_NOCLIP = 0x00000100;
        public const uint DT_EXTERNALLEADING = 0x00000200;
        public const uint DT_CALCRECT = 0x00000400;
        public const uint DT_NOPREFIX = 0x00000800;
        public const uint DT_public = 0x00001000;

        public const uint DT_EDITCONTROL = 0x00002000;
        public const uint DT_PATH_ELLIPSIS = 0x00004000;
        public const uint DT_END_ELLIPSIS = 0x00008000;
        public const uint DT_MODIFYSTRING = 0x00010000;
        public const uint DT_RTLREADING = 0x00020000;
        public const uint DT_WORD_ELLIPSIS = 0x00040000;
        public const uint DT_NOFULLWIDTHCHARBREAK = 0x00080000;
        public const uint DT_HIDEPREFIX = 0x00100000;
        public const uint DT_PREFIXONLY = 0x00200000;

        public const uint FW_DONTCARE = 0;
        public const uint FW_THIN = 100;
        public const uint FW_EXTRALIGHT = 200;
        public const uint FW_LIGHT = 300;
        public const uint FW_NORMAL = 400;
        public const uint FW_MEDIUM = 500;
        public const uint FW_SEMIBOLD = 600;
        public const uint FW_BOLD = 700;
        public const uint FW_EXTRABOLD = 800;
        public const uint FW_HEAVY = 900;

        public const uint OUT_DEFAULT_PRECIS = 0;
        public const uint OUT_STRING_PRECIS = 1;
        public const uint OUT_CHARACTER_PRECIS = 2;
        public const uint OUT_STROKE_PRECIS = 3;
        public const uint OUT_TT_PRECIS = 4;
        public const uint OUT_DEVICE_PRECIS = 5;
        public const uint OUT_RASTER_PRECIS = 6;
        public const uint OUT_TT_ONLY_PRECIS = 7;
        public const uint OUT_OUTLINE_PRECIS = 8;
        public const uint OUT_SCREEN_OUTLINE_PRECIS = 9;
        public const uint OUT_PS_ONLY_PRECIS = 10;

        public const uint CLIP_DEFAULT_PRECIS = 0;
        public const uint CLIP_CHARACTER_PRECIS = 1;
        public const uint CLIP_STROKE_PRECIS = 2;
        public const uint CLIP_MASK = 0xf;
        public const uint CLIP_LH_ANGLES = (1 << 4);
        public const uint CLIP_TT_ALWAYS = (2 << 4);
        public const uint CLIP_EMBEDDED = (8 << 4);

        public const uint DEFAULT_QUALITY = 0;
        public const uint DRAFT_QUALITY = 1;
        public const uint PROOF_QUALITY = 2;
        public const uint NONANTIALIASED_QUALITY = 3;
        public const uint ANTIALIASED_QUALITY = 4;

        public const uint CLEARTYPE_QUALITY = 5;

        public const uint CLEARTYPE_NATURAL_QUALITY = 6;

        public const uint DEFAULT_PITCH = 0;
        public const uint FIXED_PITCH = 1;
        public const uint VARIABLE_PITCH = 2;
        public const uint MONO_FONT = 8;

        public const uint FF_DONTCARE = (0 << 4);
        public const uint FF_ROMAN = (1 << 4);
        public const uint FF_SWISS = (2 << 4);
        public const uint FF_MODERN = (3 << 4);
        public const uint FF_SCRIPT = (4 << 4);
        public const uint FF_DECORATIVE = (5 << 4);

        public const int SB_HORZ = 0;

        public const int S_OK = 0;
        public const int S_FALSE = 1;
        public const int E_NOTIMPL = unchecked((int)0x80004001);
    }

    internal static class NativeMethods
    {
        internal static bool SUCCEEDED(int hr)
        {
            return hr >= 0;
        }

        [DllImport("shell32.dll", CharSet = CharSet.Unicode, PreserveSig = false)]
        internal static extern void SHGetFolderPathW(
            IntPtr hwndOwner,
            int nFolder,
            IntPtr hToken,
            uint dwFlags,
            StringBuilder lpszPath);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DeleteFileW(
            [MarshalAs(UnmanagedType.LPWStr)] string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool RemoveDirectoryW(
            [MarshalAs(UnmanagedType.LPWStr)] string lpPathName);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern uint WaitForInputIdle(
            IntPtr hProcess,
            uint dwMilliseconds);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool EnumWindows(
            [MarshalAs(UnmanagedType.FunctionPtr)] NativeDelegates.EnumWindowsProc lpEnumFunc,
            IntPtr lParam);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr OpenProcess(
            uint dwDesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle,
            uint dwProcessId);

        [DllImport("advapi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool OpenProcessToken(
            IntPtr ProcessHandle,
            uint DesiredAccess,
            out IntPtr TokenHandle);

        [DllImport("advapi32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DuplicateTokenEx(
            IntPtr hExistingToken,
            uint dwDesiredAccess,
            IntPtr lpTokenAttributes,
            NativeConstants.SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
            NativeConstants.TOKEN_TYPE TokenType,
            out IntPtr phNewToken);

        [DllImport("advapi32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CreateProcessWithTokenW(
            IntPtr hToken,
            uint dwLogonFlags,
            IntPtr lpApplicationName,
            IntPtr lpCommandLine,
            uint dwCreationFlags,
            IntPtr lpEnvironment,
            IntPtr lpCurrentDirectory,
            IntPtr lpStartupInfo,
            out NativeStructs.PROCESS_INFORMATION lpProcessInfo);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool OpenClipboard(IntPtr hWndNewOwner);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CloseClipboard();

        [DllImport("user32.dll", SetLastError = true)]
        public static extern IntPtr GetClipboardData(uint format);

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool IsClipboardFormatAvailable(uint format);

        [DllImport("shell32.dll", CharSet = CharSet.Unicode, PreserveSig = false)]
        internal static extern void SHCreateItemFromParsingName(
            [MarshalAs(UnmanagedType.LPWStr)] string pszPath,
            IntPtr pbc,
            ref Guid riid,
            out IntPtr ppv);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool VerifyVersionInfo(
            ref NativeStructs.OSVERSIONINFOEX lpVersionInfo,
            uint dwTypeMask,
            ulong dwlConditionMask);

        [DllImport("kernel32.dll")]
        internal static extern ulong VerSetConditionMask(
            ulong dwlConditionMask,
            uint dwTypeBitMask,
            byte dwConditionMask);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool DeviceIoControl(
            IntPtr hDevice,
            uint dwIoControlCode,
            IntPtr lpInBuffer,
            uint nInBufferSize,
            IntPtr lpOutBuffer,
            uint nOutBufferSize,
            ref uint lpBytesReturned,
            IntPtr lpOverlapped);

        [DllImport("shell32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool ShellExecuteExW(ref NativeStructs.SHELLEXECUTEINFO lpExecInfo);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GlobalMemoryStatusEx(ref NativeStructs.MEMORYSTATUSEX lpBuffer);

        [DllImport("shell32.dll", SetLastError = false)]
        internal static extern void SHAddToRecentDocs(uint uFlags, IntPtr pv);

        [DllImport("kernel32.dll", SetLastError = false)]
        internal static extern void GetSystemInfo(ref NativeStructs.SYSTEM_INFO lpSystemInfo);

        [DllImport("kernel32.dll", SetLastError = false)]
        internal static extern void GetNativeSystemInfo(ref NativeStructs.SYSTEM_INFO lpSystemInfo);

        [DllImport("Wintrust.dll", PreserveSig = true, SetLastError = false)]
        internal extern static unsafe int WinVerifyTrust(
            IntPtr hWnd,
            ref Guid pgActionID,
            ref NativeStructs.WINTRUST_DATA pWinTrustData
            );

        [DllImport("SetupApi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr SetupDiGetClassDevsW(
            ref Guid ClassGuid,
            [MarshalAs(UnmanagedType.LPWStr)] string Enumerator,
            IntPtr hwndParent,
            uint Flags);

        [DllImport("SetupApi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetupDiDestroyDeviceInfoList(IntPtr DeviceInfoSet);

        [DllImport("SetupApi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetupDiEnumDeviceInfo(
            IntPtr DeviceInfoSet,
            uint MemberIndex,
            ref NativeStructs.SP_DEVINFO_DATA DeviceInfoData);

        [DllImport("SetupApi.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool SetupDiGetDeviceInstanceIdW(
            IntPtr DeviceInfoSet,
            ref NativeStructs.SP_DEVINFO_DATA DeviceInfoData,
            IntPtr DeviceInstanceId,
            uint DeviceInstanceIdSize,
            out uint RequiredSize);

        internal static void ThrowOnWin32Error(string message)
        {
            int lastWin32Error = Marshal.GetLastWin32Error();
            ThrowOnWin32Error(message, lastWin32Error);
        }

        internal static void ThrowOnWin32Error(string message, NativeErrors lastWin32Error)
        {
            ThrowOnWin32Error(message, (int)lastWin32Error);
        }

        internal static void ThrowOnWin32Error(string message, int lastWin32Error)
        {
            if (lastWin32Error != NativeConstants.ERROR_SUCCESS)
            {
                string exMessageFormat = "{0} ({1}, {2})";
                string exMessage = string.Format(exMessageFormat, message, lastWin32Error, ((NativeErrors)lastWin32Error).ToString());

                throw new Win32Exception(lastWin32Error, exMessage);
            }
        }
    }

    internal static class NativeDelegates
    {
        [return: MarshalAs(UnmanagedType.Bool)]
        public delegate bool EnumWindowsProc(IntPtr hwnd, IntPtr lParam);
    }

    internal enum NativeErrors
    {
        ERROR_SUCCESS = 0,
        ERROR_INVALID_FUNCTION = 1,
        ERROR_FILE_NOT_FOUND = 2,
        ERROR_PATH_NOT_FOUND = 3,
        ERROR_TOO_MANY_OPEN_FILES = 4,
        ERROR_ACCESS_DENIED = 5,
        ERROR_INVALID_HANDLE = 6,
        ERROR_ARENA_TRASHED = 7,
        ERROR_NOT_ENOUGH_MEMORY = 8,
        ERROR_INVALID_BLOCK = 9,
        ERROR_BAD_ENVIRONMENT = 10,
        ERROR_BAD_FORMAT = 11,
        ERROR_INVALID_ACCESS = 12,
        ERROR_INVALID_DATA = 13,
        ERROR_OUTOFMEMORY = 14,
        ERROR_INVALID_DRIVE = 15,
        ERROR_CURRENT_DIRECTORY = 16,
        ERROR_NOT_SAME_DEVICE = 17,
        ERROR_NO_MORE_FILES = 18,
        ERROR_WRITE_PROTECT = 19,
        ERROR_BAD_UNIT = 20,
        ERROR_NOT_READY = 21,
        ERROR_BAD_COMMAND = 22,
        ERROR_CRC = 23,
        ERROR_BAD_LENGTH = 24,
        ERROR_SEEK = 25,
        ERROR_NOT_DOS_DISK = 26,
        ERROR_SECTOR_NOT_FOUND = 27,
        ERROR_OUT_OF_PAPER = 28,
        ERROR_WRITE_FAULT = 29,
        ERROR_READ_FAULT = 30,
        ERROR_GEN_FAILURE = 31,
        ERROR_SHARING_VIOLATION = 32,
        ERROR_LOCK_VIOLATION = 33,
        ERROR_WRONG_DISK = 34,
        ERROR_SHARING_BUFFER_EXCEEDED = 36,
        ERROR_HANDLE_EOF = 38,
        ERROR_HANDLE_DISK_FULL = 39,
        ERROR_NOT_SUPPORTED = 50,
        ERROR_REM_NOT_LIST = 51,
        ERROR_DUP_NAME = 52,
        ERROR_BAD_NETPATH = 53,
        ERROR_NETWORK_BUSY = 54,
        ERROR_DEV_NOT_EXIST = 55,
        ERROR_TOO_MANY_CMDS = 56,
        ERROR_ADAP_HDW_ERR = 57,
        ERROR_BAD_NET_RESP = 58,
        ERROR_UNEXP_NET_ERR = 59,
        ERROR_BAD_REM_ADAP = 60,
        ERROR_PRINTQ_FULL = 61,
        ERROR_NO_SPOOL_SPACE = 62,
        ERROR_PRINT_CANCELLED = 63,
        ERROR_NETNAME_DELETED = 64,
        ERROR_NETWORK_ACCESS_DENIED = 65,
        ERROR_BAD_DEV_TYPE = 66,
        ERROR_BAD_NET_NAME = 67,
        ERROR_TOO_MANY_NAMES = 68,
        ERROR_TOO_MANY_SESS = 69,
        ERROR_SHARING_PAUSED = 70,
        ERROR_REQ_NOT_ACCEP = 71,
        ERROR_REDIR_PAUSED = 72,
        ERROR_FILE_EXISTS = 80,
        ERROR_CANNOT_MAKE = 82,
        ERROR_FAIL_I24 = 83,
        ERROR_OUT_OF_STRUCTURES = 84,
        ERROR_ALREADY_ASSIGNED = 85,
        ERROR_INVALID_PASSWORD = 86,
        ERROR_INVALID_PARAMETER = 87,
        ERROR_NET_WRITE_FAULT = 88,
        ERROR_NO_PROC_SLOTS = 89,
        ERROR_TOO_MANY_SEMAPHORES = 100,
        ERROR_EXCL_SEM_ALREADY_OWNED = 101,
        ERROR_SEM_IS_SET = 102,
        ERROR_TOO_MANY_SEM_REQUESTS = 103,
        ERROR_INVALID_AT_INTERRUPT_TIME = 104,
        ERROR_SEM_OWNER_DIED = 105,
        ERROR_SEM_USER_LIMIT = 106,
        ERROR_DISK_CHANGE = 107,
        ERROR_DRIVE_LOCKED = 108,
        ERROR_BROKEN_PIPE = 109,
        ERROR_OPEN_FAILED = 110,
        ERROR_BUFFER_OVERFLOW = 111,
        ERROR_DISK_FULL = 112,
        ERROR_NO_MORE_SEARCH_HANDLES = 113,
        ERROR_INVALID_TARGET_HANDLE = 114,
        ERROR_INVALID_CATEGORY = 117,
        ERROR_INVALID_VERIFY_SWITCH = 118,
        ERROR_BAD_DRIVER_LEVEL = 119,
        ERROR_CALL_NOT_IMPLEMENTED = 120,
        ERROR_SEM_TIMEOUT = 121,
        ERROR_INSUFFICIENT_BUFFER = 122,
        ERROR_INVALID_NAME = 123,
        ERROR_INVALID_LEVEL = 124,
        ERROR_NO_VOLUME_LABEL = 125,
        ERROR_MOD_NOT_FOUND = 126,
        ERROR_PROC_NOT_FOUND = 127,
        ERROR_WAIT_NO_CHILDREN = 128,
        ERROR_CHILD_NOT_COMPLETE = 129,
        ERROR_DIRECT_ACCESS_HANDLE = 130,
        ERROR_NEGATIVE_SEEK = 131,
        ERROR_SEEK_ON_DEVICE = 132,
        ERROR_IS_JOIN_TARGET = 133,
        ERROR_IS_JOINED = 134,
        ERROR_IS_SUBSTED = 135,
        ERROR_NOT_JOINED = 136,
        ERROR_NOT_SUBSTED = 137,
        ERROR_JOIN_TO_JOIN = 138,
        ERROR_SUBST_TO_SUBST = 139,
        ERROR_JOIN_TO_SUBST = 140,
        ERROR_SUBST_TO_JOIN = 141,
        ERROR_BUSY_DRIVE = 142,
        ERROR_SAME_DRIVE = 143,
        ERROR_DIR_NOT_ROOT = 144,
        ERROR_DIR_NOT_EMPTY = 145,
        ERROR_IS_SUBST_PATH = 146,
        ERROR_IS_JOIN_PATH = 147,
        ERROR_PATH_BUSY = 148,
        ERROR_IS_SUBST_TARGET = 149,
        ERROR_SYSTEM_TRACE = 150,
        ERROR_INVALID_EVENT_COUNT = 151,
        ERROR_TOO_MANY_MUXWAITERS = 152,
        ERROR_INVALID_LIST_FORMAT = 153,
        ERROR_LABEL_TOO_LONG = 154,
        ERROR_TOO_MANY_TCBS = 155,
        ERROR_SIGNAL_REFUSED = 156,
        ERROR_DISCARDED = 157,
        ERROR_NOT_LOCKED = 158,
        ERROR_BAD_THREADID_ADDR = 159,
        ERROR_BAD_ARGUMENTS = 160,
        ERROR_BAD_PATHNAME = 161,
        ERROR_SIGNAL_PENDING = 162,
        ERROR_MAX_THRDS_REACHED = 164,
        ERROR_LOCK_FAILED = 167,
        ERROR_BUSY = 170,
        ERROR_CANCEL_VIOLATION = 173,
        ERROR_ATOMIC_LOCKS_NOT_SUPPORTED = 174,
        ERROR_INVALID_SEGMENT_NUMBER = 180,
        ERROR_INVALID_ORDINAL = 182,
        ERROR_ALREADY_EXISTS = 183,
        ERROR_INVALID_FLAG_NUMBER = 186,
        ERROR_SEM_NOT_FOUND = 187,
        ERROR_INVALID_STARTING_CODESEG = 188,
        ERROR_INVALID_STACKSEG = 189,
        ERROR_INVALID_MODULETYPE = 190,
        ERROR_INVALID_EXE_SIGNATURE = 191,
        ERROR_EXE_MARKED_INVALID = 192,
        ERROR_BAD_EXE_FORMAT = 193,
        ERROR_ITERATED_DATA_EXCEEDS_64k = 194,
        ERROR_INVALID_MINALLOCSIZE = 195,
        ERROR_DYNLINK_FROM_INVALID_RING = 196,
        ERROR_IOPL_NOT_ENABLED = 197,
        ERROR_INVALID_SEGDPL = 198,
        ERROR_AUTODATASEG_EXCEEDS_64k = 199,
        ERROR_RING2SEG_MUST_BE_MOVABLE = 200,
        ERROR_RELOC_CHAIN_XEEDS_SEGLIM = 201,
        ERROR_INFLOOP_IN_RELOC_CHAIN = 202,
        ERROR_ENVVAR_NOT_FOUND = 203,
        ERROR_NO_SIGNAL_SENT = 205,
        ERROR_FILENAME_EXCED_RANGE = 206,
        ERROR_RING2_STACK_IN_USE = 207,
        ERROR_META_EXPANSION_TOO_LONG = 208,
        ERROR_INVALID_SIGNAL_NUMBER = 209,
        ERROR_THREAD_1_INACTIVE = 210,
        ERROR_LOCKED = 212,
        ERROR_TOO_MANY_MODULES = 214,
        ERROR_NESTING_NOT_ALLOWED = 215,
        ERROR_EXE_MACHINE_TYPE_MISMATCH = 216,
        ERROR_BAD_PIPE = 230,
        ERROR_PIPE_BUSY = 231,
        ERROR_NO_DATA = 232,
        ERROR_PIPE_NOT_CONNECTED = 233,
        ERROR_MORE_DATA = 234,
        ERROR_VC_DISCONNECTED = 240,
        ERROR_INVALID_EA_NAME = 254,
        ERROR_EA_LIST_INCONSISTENT = 255,
        WAIT_TIMEOUT = 258,
        ERROR_NO_MORE_ITEMS = 259,
        ERROR_CANNOT_COPY = 266,
        ERROR_DIRECTORY = 267,
        ERROR_EAS_DIDNT_FIT = 275,
        ERROR_EA_FILE_CORRUPT = 276,
        ERROR_EA_TABLE_FULL = 277,
        ERROR_INVALID_EA_HANDLE = 278,
        ERROR_EAS_NOT_SUPPORTED = 282,
        ERROR_NOT_OWNER = 288,
        ERROR_TOO_MANY_POSTS = 298,
        ERROR_PARTIAL_COPY = 299,
        ERROR_OPLOCK_NOT_GRANTED = 300,
        ERROR_INVALID_OPLOCK_PROTOCOL = 301,
        ERROR_DISK_TOO_FRAGMENTED = 302,
        ERROR_DELETE_PENDING = 303,
        ERROR_MR_MID_NOT_FOUND = 317,
        ERROR_INVALID_ADDRESS = 487,
        ERROR_ARITHMETIC_OVERFLOW = 534,
        ERROR_PIPE_CONNECTED = 535,
        ERROR_PIPE_LISTENING = 536,
        ERROR_EA_ACCESS_DENIED = 994,
        ERROR_OPERATION_ABORTED = 995,
        ERROR_IO_INCOMPLETE = 996,
        ERROR_IO_PENDING = 997,
        ERROR_NOACCESS = 998,
        ERROR_SWAPERROR = 999,
        ERROR_STACK_OVERFLOW = 1001,
        ERROR_INVALID_MESSAGE = 1002,
        ERROR_CAN_NOT_COMPLETE = 1003,
        ERROR_INVALID_FLAGS = 1004,
        ERROR_UNRECOGNIZED_VOLUME = 1005,
        ERROR_FILE_INVALID = 1006,
        ERROR_FULLSCREEN_MODE = 1007,
        ERROR_NO_TOKEN = 1008,
        ERROR_BADDB = 1009,
        ERROR_BADKEY = 1010,
        ERROR_CANTOPEN = 1011,
        ERROR_CANTREAD = 1012,
        ERROR_CANTWRITE = 1013,
        ERROR_REGISTRY_RECOVERED = 1014,
        ERROR_REGISTRY_CORRUPT = 1015,
        ERROR_REGISTRY_IO_FAILED = 1016,
        ERROR_NOT_REGISTRY_FILE = 1017,
        ERROR_KEY_DELETED = 1018,
        ERROR_NO_LOG_SPACE = 1019,
        ERROR_KEY_HAS_CHILDREN = 1020,
        ERROR_CHILD_MUST_BE_VOLATILE = 1021,
        ERROR_NOTIFY_ENUM_DIR = 1022,
        ERROR_DEPENDENT_SERVICES_RUNNING = 1051,
        ERROR_INVALID_SERVICE_CONTROL = 1052,
        ERROR_SERVICE_REQUEST_TIMEOUT = 1053,
        ERROR_SERVICE_NO_THREAD = 1054,
        ERROR_SERVICE_DATABASE_LOCKED = 1055,
        ERROR_SERVICE_ALREADY_RUNNING = 1056,
        ERROR_INVALID_SERVICE_ACCOUNT = 1057,
        ERROR_SERVICE_DISABLED = 1058,
        ERROR_CIRCULAR_DEPENDENCY = 1059,
        ERROR_SERVICE_DOES_NOT_EXIST = 1060,
        ERROR_SERVICE_CANNOT_ACCEPT_CTRL = 1061,
        ERROR_SERVICE_NOT_ACTIVE = 1062,
        ERROR_FAILED_SERVICE_CONTROLLER_CONNECT = 1063,
        ERROR_EXCEPTION_IN_SERVICE = 1064,
        ERROR_DATABASE_DOES_NOT_EXIST = 1065,
        ERROR_SERVICE_SPECIFIC_ERROR = 1066,
        ERROR_PROCESS_ABORTED = 1067,
        ERROR_SERVICE_DEPENDENCY_FAIL = 1068,
        ERROR_SERVICE_LOGON_FAILED = 1069,
        ERROR_SERVICE_START_HANG = 1070,
        ERROR_INVALID_SERVICE_LOCK = 1071,
        ERROR_SERVICE_MARKED_FOR_DELETE = 1072,
        ERROR_SERVICE_EXISTS = 1073,
        ERROR_ALREADY_RUNNING_LKG = 1074,
        ERROR_SERVICE_DEPENDENCY_DELETED = 1075,
        ERROR_BOOT_ALREADY_ACCEPTED = 1076,
        ERROR_SERVICE_NEVER_STARTED = 1077,
        ERROR_DUPLICATE_SERVICE_NAME = 1078,
        ERROR_DIFFERENT_SERVICE_ACCOUNT = 1079,
        ERROR_CANNOT_DETECT_DRIVER_FAILURE = 1080,
        ERROR_CANNOT_DETECT_PROCESS_ABORT = 1081,
        ERROR_NO_RECOVERY_PROGRAM = 1082,
        ERROR_SERVICE_NOT_IN_EXE = 1083,
        ERROR_NOT_SAFEBOOT_SERVICE = 1084,
        ERROR_END_OF_MEDIA = 1100,
        ERROR_FILEMARK_DETECTED = 1101,
        ERROR_BEGINNING_OF_MEDIA = 1102,
        ERROR_SETMARK_DETECTED = 1103,
        ERROR_NO_DATA_DETECTED = 1104,
        ERROR_PARTITION_FAILURE = 1105,
        ERROR_INVALID_BLOCK_LENGTH = 1106,
        ERROR_DEVICE_NOT_PARTITIONED = 1107,
        ERROR_UNABLE_TO_LOCK_MEDIA = 1108,
        ERROR_UNABLE_TO_UNLOAD_MEDIA = 1109,
        ERROR_MEDIA_CHANGED = 1110,
        ERROR_BUS_RESET = 1111,
        ERROR_NO_MEDIA_IN_DRIVE = 1112,
        ERROR_NO_UNICODE_TRANSLATION = 1113,
        ERROR_DLL_INIT_FAILED = 1114,
        ERROR_SHUTDOWN_IN_PROGRESS = 1115,
        ERROR_NO_SHUTDOWN_IN_PROGRESS = 1116,
        ERROR_IO_DEVICE = 1117,
        ERROR_SERIAL_NO_DEVICE = 1118,
        ERROR_IRQ_BUSY = 1119,
        ERROR_MORE_WRITES = 1120,
        ERROR_COUNTER_TIMEOUT = 1121,
        ERROR_FLOPPY_ID_MARK_NOT_FOUND = 1122,
        ERROR_FLOPPY_WRONG_CYLINDER = 1123,
        ERROR_FLOPPY_UNKNOWN_ERROR = 1124,
        ERROR_FLOPPY_BAD_REGISTERS = 1125,
        ERROR_DISK_RECALIBRATE_FAILED = 1126,
        ERROR_DISK_OPERATION_FAILED = 1127,
        ERROR_DISK_RESET_FAILED = 1128,
        ERROR_EOM_OVERFLOW = 1129,
        ERROR_NOT_ENOUGH_SERVER_MEMORY = 1130,
        ERROR_POSSIBLE_DEADLOCK = 1131,
        ERROR_MAPPED_ALIGNMENT = 1132,
        ERROR_SET_POWER_STATE_VETOED = 1140,
        ERROR_SET_POWER_STATE_FAILED = 1141,
        ERROR_TOO_MANY_LINKS = 1142,
        ERROR_OLD_WIN_VERSION = 1150,
        ERROR_APP_WRONG_OS = 1151,
        ERROR_SINGLE_INSTANCE_APP = 1152,
        ERROR_RMODE_APP = 1153,
        ERROR_INVALID_DLL = 1154,
        ERROR_NO_ASSOCIATION = 1155,
        ERROR_DDE_FAIL = 1156,
        ERROR_DLL_NOT_FOUND = 1157,
        ERROR_NO_MORE_USER_HANDLES = 1158,
        ERROR_MESSAGE_SYNC_ONLY = 1159,
        ERROR_SOURCE_ELEMENT_EMPTY = 1160,
        ERROR_DESTINATION_ELEMENT_FULL = 1161,
        ERROR_ILLEGAL_ELEMENT_ADDRESS = 1162,
        ERROR_MAGAZINE_NOT_PRESENT = 1163,
        ERROR_DEVICE_REINITIALIZATION_NEEDED = 1164,
        ERROR_DEVICE_REQUIRES_CLEANING = 1165,
        ERROR_DEVICE_DOOR_OPEN = 1166,
        ERROR_DEVICE_NOT_CONNECTED = 1167,
        ERROR_NOT_FOUND = 1168,
        ERROR_NO_MATCH = 1169,
        ERROR_SET_NOT_FOUND = 1170,
        ERROR_POINT_NOT_FOUND = 1171,
        ERROR_NO_TRACKING_SERVICE = 1172,
        ERROR_NO_VOLUME_ID = 1173,
        ERROR_UNABLE_TO_REMOVE_REPLACED = 1175,
        ERROR_UNABLE_TO_MOVE_REPLACEMENT = 1176,
        ERROR_UNABLE_TO_MOVE_REPLACEMENT_2 = 1177,
        ERROR_JOURNAL_DELETE_IN_PROGRESS = 1178,
        ERROR_JOURNAL_NOT_ACTIVE = 1179,
        ERROR_POTENTIAL_FILE_FOUND = 1180,
        ERROR_JOURNAL_ENTRY_DELETED = 1181,
        ERROR_BAD_DEVICE = 1200,
        ERROR_CONNECTION_UNAVAIL = 1201,
        ERROR_DEVICE_ALREADY_REMEMBERED = 1202,
        ERROR_NO_NET_OR_BAD_PATH = 1203,
        ERROR_BAD_PROVIDER = 1204,
        ERROR_CANNOT_OPEN_PROFILE = 1205,
        ERROR_BAD_PROFILE = 1206,
        ERROR_NOT_CONTAINER = 1207,
        ERROR_EXTENDED_ERROR = 1208,
        ERROR_INVALID_GROUPNAME = 1209,
        ERROR_INVALID_COMPUTERNAME = 1210,
        ERROR_INVALID_EVENTNAME = 1211,
        ERROR_INVALID_DOMAINNAME = 1212,
        ERROR_INVALID_SERVICENAME = 1213,
        ERROR_INVALID_NETNAME = 1214,
        ERROR_INVALID_SHARENAME = 1215,
        ERROR_INVALID_PASSWORDNAME = 1216,
        ERROR_INVALID_MESSAGENAME = 1217,
        ERROR_INVALID_MESSAGEDEST = 1218,
        ERROR_SESSION_CREDENTIAL_CONFLICT = 1219,
        ERROR_REMOTE_SESSION_LIMIT_EXCEEDED = 1220,
        ERROR_DUP_DOMAINNAME = 1221,
        ERROR_NO_NETWORK = 1222,
        ERROR_CANCELLED = 1223,
        ERROR_USER_MAPPED_FILE = 1224,
        ERROR_CONNECTION_REFUSED = 1225,
        ERROR_GRACEFUL_DISCONNECT = 1226,
        ERROR_ADDRESS_ALREADY_ASSOCIATED = 1227,
        ERROR_ADDRESS_NOT_ASSOCIATED = 1228,
        ERROR_CONNECTION_INVALID = 1229,
        ERROR_CONNECTION_ACTIVE = 1230,
        ERROR_NETWORK_UNREACHABLE = 1231,
        ERROR_HOST_UNREACHABLE = 1232,
        ERROR_PROTOCOL_UNREACHABLE = 1233,
        ERROR_PORT_UNREACHABLE = 1234,
        ERROR_REQUEST_ABORTED = 1235,
        ERROR_CONNECTION_ABORTED = 1236,
        ERROR_RETRY = 1237,
        ERROR_CONNECTION_COUNT_LIMIT = 1238,
        ERROR_LOGIN_TIME_RESTRICTION = 1239,
        ERROR_LOGIN_WKSTA_RESTRICTION = 1240,
        ERROR_INCORRECT_ADDRESS = 1241,
        ERROR_ALREADY_REGISTERED = 1242,
        ERROR_SERVICE_NOT_FOUND = 1243,
        ERROR_NOT_AUTHENTICATED = 1244,
        ERROR_NOT_LOGGED_ON = 1245,
        ERROR_CONTINUE = 1246,
        ERROR_ALREADY_INITIALIZED = 1247,
        ERROR_NO_MORE_DEVICES = 1248,
        ERROR_NO_SUCH_SITE = 1249,
        ERROR_DOMAIN_CONTROLLER_EXISTS = 1250,
        ERROR_ONLY_IF_CONNECTED = 1251,
        ERROR_OVERRIDE_NOCHANGES = 1252,
        ERROR_BAD_USER_PROFILE = 1253,
        ERROR_NOT_SUPPORTED_ON_SBS = 1254,
        ERROR_SERVER_SHUTDOWN_IN_PROGRESS = 1255,
        ERROR_HOST_DOWN = 1256,
        ERROR_NON_ACCOUNT_SID = 1257,
        ERROR_NON_DOMAIN_SID = 1258,
        ERROR_APPHELP_BLOCK = 1259,
        ERROR_ACCESS_DISABLED_BY_POLICY = 1260,
        ERROR_REG_NAT_CONSUMPTION = 1261,
        ERROR_CSCSHARE_OFFLINE = 1262,
        ERROR_PKINIT_FAILURE = 1263,
        ERROR_SMARTCARD_SUBSYSTEM_FAILURE = 1264,
        ERROR_DOWNGRADE_DETECTED = 1265,
        SEC_E_SMARTCARD_CERT_REVOKED = 1266,
        SEC_E_ISSUING_CA_UNTRUSTED = 1267,
        SEC_E_REVOCATION_OFFLINE_C = 1268,
        SEC_E_PKINIT_CLIENT_FAILUR = 1269,
        SEC_E_SMARTCARD_CERT_EXPIRED = 1270,
        ERROR_MACHINE_LOCKED = 1271,
        ERROR_CALLBACK_SUPPLIED_INVALID_DATA = 1273,
        ERROR_SYNC_FOREGROUND_REFRESH_REQUIRED = 1274,
        ERROR_DRIVER_BLOCKED = 1275,
        ERROR_INVALID_IMPORT_OF_NON_DLL = 1276,
        ERROR_NOT_ALL_ASSIGNED = 1300,
        ERROR_SOME_NOT_MAPPED = 1301,
        ERROR_NO_QUOTAS_FOR_ACCOUNT = 1302,
        ERROR_LOCAL_USER_SESSION_KEY = 1303,
        ERROR_NULL_LM_PASSWORD = 1304,
        ERROR_UNKNOWN_REVISION = 1305,
        ERROR_REVISION_MISMATCH = 1306,
        ERROR_INVALID_OWNER = 1307,
        ERROR_INVALID_PRIMARY_GROUP = 1308,
        ERROR_NO_IMPERSONATION_TOKEN = 1309,
        ERROR_CANT_DISABLE_MANDATORY = 1310,
        ERROR_NO_LOGON_SERVERS = 1311,
        ERROR_NO_SUCH_LOGON_SESSION = 1312,
        ERROR_NO_SUCH_PRIVILEGE = 1313,
        ERROR_PRIVILEGE_NOT_HELD = 1314,
        ERROR_INVALID_ACCOUNT_NAME = 1315,
        ERROR_USER_EXISTS = 1316,
        ERROR_NO_SUCH_USER = 1317,
        ERROR_GROUP_EXISTS = 1318,
        ERROR_NO_SUCH_GROUP = 1319,
        ERROR_MEMBER_IN_GROUP = 1320,
        ERROR_MEMBER_NOT_IN_GROUP = 1321,
        ERROR_LAST_ADMIN = 1322,
        ERROR_WRONG_PASSWORD = 1323,
        ERROR_ILL_FORMED_PASSWORD = 1324,
        ERROR_PASSWORD_RESTRICTION = 1325,
        ERROR_LOGON_FAILURE = 1326,
        ERROR_ACCOUNT_RESTRICTION = 1327,
        ERROR_INVALID_LOGON_HOURS = 1328,
        ERROR_INVALID_WORKSTATION = 1329,
        ERROR_PASSWORD_EXPIRED = 1330,
        ERROR_ACCOUNT_DISABLED = 1331,
        ERROR_NONE_MAPPED = 1332,
        ERROR_TOO_MANY_LUIDS_REQUESTED = 1333,
        ERROR_LUIDS_EXHAUSTED = 1334,
        ERROR_INVALID_SUB_AUTHORITY = 1335,
        ERROR_INVALID_ACL = 1336,
        ERROR_INVALID_SID = 1337,
        ERROR_INVALID_SECURITY_DESCR = 1338,
        ERROR_BAD_INHERITANCE_ACL = 1340,
        ERROR_SERVER_DISABLED = 1341,
        ERROR_SERVER_NOT_DISABLED = 1342,
        ERROR_INVALID_ID_AUTHORITY = 1343,
        ERROR_ALLOTTED_SPACE_EXCEEDED = 1344,
        ERROR_INVALID_GROUP_ATTRIBUTES = 1345,
        ERROR_BAD_IMPERSONATION_LEVEL = 1346,
        ERROR_CANT_OPEN_ANONYMOUS = 1347,
        ERROR_BAD_VALIDATION_CLASS = 1348,
        ERROR_BAD_TOKEN_TYPE = 1349,
        ERROR_NO_SECURITY_ON_OBJECT = 1350,
        ERROR_CANT_ACCESS_DOMAIN_INFO = 1351,
        ERROR_INVALID_SERVER_STATE = 1352,
        ERROR_INVALID_DOMAIN_STATE = 1353,
        ERROR_INVALID_DOMAIN_ROLE = 1354,
        ERROR_NO_SUCH_DOMAIN = 1355,
        ERROR_DOMAIN_EXISTS = 1356,
        ERROR_DOMAIN_LIMIT_EXCEEDED = 1357,
        ERROR_INTERNAL_DB_CORRUPTION = 1358,
        ERROR_INTERNAL_ERROR = 1359,
        ERROR_GENERIC_NOT_MAPPED = 1360,
        ERROR_BAD_DESCRIPTOR_FORMAT = 1361,
        ERROR_NOT_LOGON_PROCESS = 1362,
        ERROR_LOGON_SESSION_EXISTS = 1363,
        ERROR_NO_SUCH_PACKAGE = 1364,
        ERROR_BAD_LOGON_SESSION_STATE = 1365,
        ERROR_LOGON_SESSION_COLLISION = 1366,
        ERROR_INVALID_LOGON_TYPE = 1367,
        ERROR_CANNOT_IMPERSONATE = 1368,
        ERROR_RXACT_INVALID_STATE = 1369,
        ERROR_RXACT_COMMIT_FAILURE = 1370,
        ERROR_SPECIAL_ACCOUNT = 1371,
        ERROR_SPECIAL_GROUP = 1372,
        ERROR_SPECIAL_USER = 1373,
        ERROR_MEMBERS_PRIMARY_GROUP = 1374,
        ERROR_TOKEN_ALREADY_IN_USE = 1375,
        ERROR_NO_SUCH_ALIAS = 1376,
        ERROR_MEMBER_NOT_IN_ALIAS = 1377,
        ERROR_MEMBER_IN_ALIAS = 1378,
        ERROR_ALIAS_EXISTS = 1379,
        ERROR_LOGON_NOT_GRANTED = 1380,
        ERROR_TOO_MANY_SECRETS = 1381,
        ERROR_SECRET_TOO_LONG = 1382,
        ERROR_INTERNAL_DB_ERROR = 1383,
        ERROR_TOO_MANY_CONTEXT_IDS = 1384,
        ERROR_LOGON_TYPE_NOT_GRANTED = 1385,
        ERROR_NT_CROSS_ENCRYPTION_REQUIRED = 1386,
        ERROR_NO_SUCH_MEMBER = 1387,
        ERROR_INVALID_MEMBER = 1388,
        ERROR_TOO_MANY_SIDS = 1389,
        ERROR_LM_CROSS_ENCRYPTION_REQUIRED = 1390,
        ERROR_NO_INHERITANCE = 1391,
        ERROR_FILE_CORRUPT = 1392,
        ERROR_DISK_CORRUPT = 1393,
        ERROR_NO_USER_SESSION_KEY = 1394,
        ERROR_LICENSE_QUOTA_EXCEEDED = 1395,
        ERROR_WRONG_TARGET_NAME = 1396,
        ERROR_MUTUAL_AUTH_FAILED = 1397,
        ERROR_TIME_SKEW = 1398,
        ERROR_CURRENT_DOMAIN_NOT_ALLOWED = 1399,
        ERROR_INVALID_WINDOW_HANDLE = 1400,
        ERROR_INVALID_MENU_HANDLE = 1401,
        ERROR_INVALID_CURSOR_HANDLE = 1402,
        ERROR_INVALID_ACCEL_HANDLE = 1403,
        ERROR_INVALID_HOOK_HANDLE = 1404,
        ERROR_INVALID_DWP_HANDLE = 1405,
        ERROR_TLW_WITH_WSCHILD = 1406,
        ERROR_CANNOT_FIND_WND_CLASS = 1407,
        ERROR_WINDOW_OF_OTHER_THREAD = 1408,
        ERROR_HOTKEY_ALREADY_REGISTERED = 1409,
        ERROR_CLASS_ALREADY_EXISTS = 1410,
        ERROR_CLASS_DOES_NOT_EXIST = 1411,
        ERROR_CLASS_HAS_WINDOWS = 1412,
        ERROR_INVALID_INDEX = 1413,
        ERROR_INVALID_ICON_HANDLE = 1414,
        ERROR_PRIVATE_DIALOG_INDEX = 1415,
        ERROR_LISTBOX_ID_NOT_FOUND = 1416,
        ERROR_NO_WILDCARD_CHARACTERS = 1417,
        ERROR_CLIPBOARD_NOT_OPEN = 1418,
        ERROR_HOTKEY_NOT_REGISTERED = 1419,
        ERROR_WINDOW_NOT_DIALOG = 1420,
        ERROR_CONTROL_ID_NOT_FOUND = 1421,
        ERROR_INVALID_COMBOBOX_MESSAGE = 1422,
        ERROR_WINDOW_NOT_COMBOBOX = 1423,
        ERROR_INVALID_EDIT_HEIGHT = 1424,
        ERROR_DC_NOT_FOUND = 1425,
        ERROR_INVALID_HOOK_FILTER = 1426,
        ERROR_INVALID_FILTER_PROC = 1427,
        ERROR_HOOK_NEEDS_HMOD = 1428,
        ERROR_GLOBAL_ONLY_HOOK = 1429,
        ERROR_JOURNAL_HOOK_SET = 1430,
        ERROR_HOOK_NOT_INSTALLED = 1431,
        ERROR_INVALID_LB_MESSAGE = 1432,
        ERROR_SETCOUNT_ON_BAD_LB = 1433,
        ERROR_LB_WITHOUT_TABSTOPS = 1434,
        ERROR_DESTROY_OBJECT_OF_OTHER_THREAD = 1435,
        ERROR_CHILD_WINDOW_MENU = 1436,
        ERROR_NO_SYSTEM_MENU = 1437,
        ERROR_INVALID_MSGBOX_STYLE = 1438,
        ERROR_INVALID_SPI_VALUE = 1439,
        ERROR_SCREEN_ALREADY_LOCKED = 1440,
        ERROR_HWNDS_HAVE_DIFF_PARENT = 1441,
        ERROR_NOT_CHILD_WINDOW = 1442,
        ERROR_INVALID_GW_COMMAND = 1443,
        ERROR_INVALID_THREAD_ID = 1444,
        ERROR_NON_MDICHILD_WINDOW = 1445,
        ERROR_POPUP_ALREADY_ACTIVE = 1446,
        ERROR_NO_SCROLLBARS = 1447,
        ERROR_INVALID_SCROLLBAR_RANGE = 1448,
        ERROR_INVALID_SHOWWIN_COMMAND = 1449,
        ERROR_NO_SYSTEM_RESOURCES = 1450,
        ERROR_NONPAGED_SYSTEM_RESOURCES = 1451,
        ERROR_PAGED_SYSTEM_RESOURCES = 1452,
        ERROR_WORKING_SET_QUOTA = 1453,
        ERROR_PAGEFILE_QUOTA = 1454,
        ERROR_COMMITMENT_LIMIT = 1455,
        ERROR_MENU_ITEM_NOT_FOUND = 1456,
        ERROR_INVALID_KEYBOARD_HANDLE = 1457,
        ERROR_HOOK_TYPE_NOT_ALLOWED = 1458,
        ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION = 1459,
        ERROR_TIMEOUT = 1460,
        ERROR_INVALID_MONITOR_HANDLE = 1461,
        ERROR_EVENTLOG_FILE_CORRUPT = 1500,
        ERROR_EVENTLOG_CANT_START = 1501,
        ERROR_LOG_FILE_FULL = 1502,
        ERROR_EVENTLOG_FILE_CHANGED = 1503,
        ERROR_INSTALL_SERVICE_FAILURE = 1601,
        ERROR_INSTALL_USEREXIT = 1602,
        ERROR_INSTALL_FAILURE = 1603,
        ERROR_INSTALL_SUSPEND = 1604,
        ERROR_UNKNOWN_PRODUCT = 1605,
        ERROR_UNKNOWN_FEATURE = 1606,
        ERROR_UNKNOWN_COMPONENT = 1607,
        ERROR_UNKNOWN_PROPERTY = 1608,
        ERROR_INVALID_HANDLE_STATE = 1609,
        ERROR_BAD_CONFIGURATION = 1610,
        ERROR_INDEX_ABSENT = 1611,
        ERROR_INSTALL_SOURCE_ABSENT = 1612,
        ERROR_INSTALL_PACKAGE_VERSION = 1613,
        ERROR_PRODUCT_UNINSTALLED = 1614,
        ERROR_BAD_QUERY_SYNTAX = 1615,
        ERROR_INVALID_FIELD = 1616,
        ERROR_DEVICE_REMOVED = 1617,
        ERROR_INSTALL_ALREADY_RUNNING = 1618,
        ERROR_INSTALL_PACKAGE_OPEN_FAILED = 1619,
        ERROR_INSTALL_PACKAGE_INVALID = 1620,
        ERROR_INSTALL_UI_FAILURE = 1621,
        ERROR_INSTALL_LOG_FAILURE = 1622,
        ERROR_INSTALL_LANGUAGE_UNSUPPORTED = 1623,
        ERROR_INSTALL_TRANSFORM_FAILURE = 1624,
        ERROR_INSTALL_PACKAGE_REJECTED = 1625,
        ERROR_FUNCTION_NOT_CALLED = 1626,
        ERROR_FUNCTION_FAILED = 1627,
        ERROR_INVALID_TABLE = 1628,
        ERROR_DATATYPE_MISMATCH = 1629,
        ERROR_UNSUPPORTED_TYPE = 1630,
        ERROR_CREATE_FAILED = 1631,
        ERROR_INSTALL_TEMP_UNWRITABLE = 1632,
        ERROR_INSTALL_PLATFORM_UNSUPPORTED = 1633,
        ERROR_INSTALL_NOTUSED = 1634,
        ERROR_PATCH_PACKAGE_OPEN_FAILED = 1635,
        ERROR_PATCH_PACKAGE_INVALID = 1636,
        ERROR_PATCH_PACKAGE_UNSUPPORTED = 1637,
        ERROR_PRODUCT_VERSION = 1638,
        ERROR_INVALID_COMMAND_LINE = 1639,
        ERROR_INSTALL_REMOTE_DISALLOWED = 1640,
        ERROR_SUCCESS_REBOOT_INITIATED = 1641,
        ERROR_PATCH_TARGET_NOT_FOUND = 1642,
        ERROR_PATCH_PACKAGE_REJECTED = 1643,
        ERROR_INSTALL_TRANSFORM_REJECTED = 1644,
        RPC_S_INVALID_STRING_BINDING = 1700,
        RPC_S_WRONG_KIND_OF_BINDING = 1701,
        RPC_S_INVALID_BINDING = 1702,
        RPC_S_PROTSEQ_NOT_SUPPORTED = 1703,
        RPC_S_INVALID_RPC_PROTSEQ = 1704,
        RPC_S_INVALID_STRING_UUID = 1705,
        RPC_S_INVALID_ENDPOINT_FORMAT = 1706,
        RPC_S_INVALID_NET_ADDR = 1707,
        RPC_S_NO_ENDPOINT_FOUND = 1708,
        RPC_S_INVALID_TIMEOUT = 1709,
        RPC_S_OBJECT_NOT_FOUND = 1710,
        RPC_S_ALREADY_REGISTERED = 1711,
        RPC_S_TYPE_ALREADY_REGISTERED = 1712,
        RPC_S_ALREADY_LISTENING = 1713,
        RPC_S_NO_PROTSEQS_REGISTERED = 1714,
        RPC_S_NOT_LISTENING = 1715,
        RPC_S_UNKNOWN_MGR_TYPE = 1716,
        RPC_S_UNKNOWN_IF = 1717,
        RPC_S_NO_BINDINGS = 1718,
        RPC_S_NO_PROTSEQS = 1719,
        RPC_S_CANT_CREATE_ENDPOINT = 1720,
        RPC_S_OUT_OF_RESOURCES = 1721,
        RPC_S_SERVER_UNAVAILABLE = 1722,
        RPC_S_SERVER_TOO_BUSY = 1723,
        RPC_S_INVALID_NETWORK_OPTIONS = 1724,
        RPC_S_NO_CALL_ACTIVE = 1725,
        RPC_S_CALL_FAILED = 1726,
        RPC_S_CALL_FAILED_DNE = 1727,
        RPC_S_PROTOCOL_ERROR = 1728,
        RPC_S_UNSUPPORTED_TRANS_SYN = 1730,
        RPC_S_UNSUPPORTED_TYPE = 1732,
        RPC_S_INVALID_TAG = 1733,
        RPC_S_INVALID_BOUND = 1734,
        RPC_S_NO_ENTRY_NAME = 1735,
        RPC_S_INVALID_NAME_SYNTAX = 1736,
        RPC_S_UNSUPPORTED_NAME_SYNTAX = 1737,
        RPC_S_UUID_NO_ADDRESS = 1739,
        RPC_S_DUPLICATE_ENDPOINT = 1740,
        RPC_S_UNKNOWN_AUTHN_TYPE = 1741,
        RPC_S_MAX_CALLS_TOO_SMALL = 1742,
        RPC_S_STRING_TOO_LONG = 1743,
        RPC_S_PROTSEQ_NOT_FOUND = 1744,
        RPC_S_PROCNUM_OUT_OF_RANGE = 1745,
        RPC_S_BINDING_HAS_NO_AUTH = 1746,
        RPC_S_UNKNOWN_AUTHN_SERVICE = 1747,
        RPC_S_UNKNOWN_AUTHN_LEVEL = 1748,
        RPC_S_INVALID_AUTH_IDENTITY = 1749,
        RPC_S_UNKNOWN_AUTHZ_SERVICE = 1750,
        EPT_S_INVALID_ENTRY = 1751,
        EPT_S_CANT_PERFORM_OP = 1752,
        EPT_S_NOT_REGISTERED = 1753,
        RPC_S_NOTHING_TO_EXPORT = 1754,
        RPC_S_INCOMPLETE_NAME = 1755,
        RPC_S_INVALID_VERS_OPTION = 1756,
        RPC_S_NO_MORE_MEMBERS = 1757,
        RPC_S_NOT_ALL_OBJS_UNEXPORTED = 1758,
        RPC_S_INTERFACE_NOT_FOUND = 1759,
        RPC_S_ENTRY_ALREADY_EXISTS = 1760,
        RPC_S_ENTRY_NOT_FOUND = 1761,
        RPC_S_NAME_SERVICE_UNAVAILABLE = 1762,
        RPC_S_INVALID_NAF_ID = 1763,
        RPC_S_CANNOT_SUPPORT = 1764,
        RPC_S_NO_CONTEXT_AVAILABLE = 1765,
        RPC_S_INTERNAL_ERROR = 1766,
        RPC_S_ZERO_DIVIDE = 1767,
        RPC_S_ADDRESS_ERROR = 1768,
        RPC_S_FP_DIV_ZERO = 1769,
        RPC_S_FP_UNDERFLOW = 1770,
        RPC_S_FP_OVERFLOW = 1771,
        RPC_X_NO_MORE_ENTRIES = 1772,
        RPC_X_SS_CHAR_TRANS_OPEN_FAIL = 1773,
        RPC_X_SS_CHAR_TRANS_SHORT_FILE = 1774,
        RPC_X_SS_IN_NULL_CONTEXT = 1775,
        RPC_X_SS_CONTEXT_DAMAGED = 1777,
        RPC_X_SS_HANDLES_MISMATCH = 1778,
        RPC_X_SS_CANNOT_GET_CALL_HANDLE = 1779,
        RPC_X_NULL_REF_POINTER = 1780,
        RPC_X_ENUM_VALUE_OUT_OF_RANGE = 1781,
        RPC_X_BYTE_COUNT_TOO_SMALL = 1782,
        RPC_X_BAD_STUB_DATA = 1783,
        ERROR_INVALID_USER_BUFFER = 1784,
        ERROR_UNRECOGNIZED_MEDIA = 1785,
        ERROR_NO_TRUST_LSA_SECRET = 1786,
        ERROR_NO_TRUST_SAM_ACCOUNT = 1787,
        ERROR_TRUSTED_DOMAIN_FAILURE = 1788,
        ERROR_TRUSTED_RELATIONSHIP_FAILURE = 1789,
        ERROR_TRUST_FAILURE = 1790,
        RPC_S_CALL_IN_PROGRESS = 1791,
        ERROR_NETLOGON_NOT_STARTED = 1792,
        ERROR_ACCOUNT_EXPIRED = 1793,
        ERROR_REDIRECTOR_HAS_OPEN_HANDLES = 1794,
        ERROR_PRINTER_DRIVER_ALREADY_INSTALLED = 1795,
        ERROR_UNKNOWN_PORT = 1796,
        ERROR_UNKNOWN_PRINTER_DRIVER = 1797,
        ERROR_UNKNOWN_PRINTPROCESSOR = 1798,
        ERROR_INVALID_SEPARATOR_FILE = 1799,
        ERROR_INVALID_PRIORITY = 1800,
        ERROR_INVALID_PRINTER_NAME = 1801,
        ERROR_PRINTER_ALREADY_EXISTS = 1802,
        ERROR_INVALID_PRINTER_COMMAND = 1803,
        ERROR_INVALID_DATATYPE = 1804,
        ERROR_INVALID_ENVIRONMENT = 1805,
        RPC_S_NO_MORE_BINDINGS = 1806,
        ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT = 1807,
        ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT = 1808,
        ERROR_NOLOGON_SERVER_TRUST_ACCOUNT = 1809,
        ERROR_DOMAIN_TRUST_INCONSISTENT = 1810,
        ERROR_SERVER_HAS_OPEN_HANDLES = 1811,
        ERROR_RESOURCE_DATA_NOT_FOUND = 1812,
        ERROR_RESOURCE_TYPE_NOT_FOUND = 1813,
        ERROR_RESOURCE_NAME_NOT_FOUND = 1814,
        ERROR_RESOURCE_LANG_NOT_FOUND = 1815,
        ERROR_NOT_ENOUGH_QUOTA = 1816,
        RPC_S_NO_INTERFACES = 1817,
        RPC_S_CALL_CANCELLED = 1818,
        RPC_S_BINDING_INCOMPLETE = 1819,
        RPC_S_COMM_FAILURE = 1820,
        RPC_S_UNSUPPORTED_AUTHN_LEVEL = 1821,
        RPC_S_NO_PRINC_NAME = 1822,
        RPC_S_NOT_RPC_ERROR = 1823,
        RPC_S_UUID_LOCAL_ONLY = 1824,
        RPC_S_SEC_PKG_ERROR = 1825,
        RPC_S_NOT_CANCELLED = 1826,
        RPC_X_INVALID_ES_ACTION = 1827,
        RPC_X_WRONG_ES_VERSION = 1828,
        RPC_X_WRONG_STUB_VERSION = 1829,
        RPC_X_INVALID_PIPE_OBJECT = 1830,
        RPC_X_WRONG_PIPE_ORDER = 1831,
        RPC_X_WRONG_PIPE_VERSION = 1832,
        RPC_S_GROUP_MEMBER_NOT_FOUND = 1898,
        EPT_S_CANT_CREATE = 1899,
        RPC_S_INVALID_OBJECT = 1900,
        ERROR_INVALID_TIME = 1901,
        ERROR_INVALID_FORM_NAME = 1902,
        ERROR_INVALID_FORM_SIZE = 1903,
        ERROR_ALREADY_WAITING = 1904,
        ERROR_PRINTER_DELETED = 1905,
        ERROR_INVALID_PRINTER_STATE = 1906,
        ERROR_PASSWORD_MUST_CHANGE = 1907,
        ERROR_DOMAIN_CONTROLLER_NOT_FOUND = 1908,
        ERROR_ACCOUNT_LOCKED_OUT = 1909,
        OR_INVALID_OXID = 1910,
        OR_INVALID_OID = 1911,
        OR_INVALID_SET = 1912,
        RPC_S_SEND_INCOMPLETE = 1913,
        RPC_S_INVALID_ASYNC_HANDLE = 1914,
        RPC_S_INVALID_ASYNC_CALL = 1915,
        RPC_X_PIPE_CLOSED = 1916,
        RPC_X_PIPE_DISCIPLINE_ERROR = 1917,
        RPC_X_PIPE_EMPTY = 1918,
        ERROR_NO_SITENAME = 1919,
        ERROR_CANT_ACCESS_FILE = 1920,
        ERROR_CANT_RESOLVE_FILENAME = 1921,
        RPC_S_ENTRY_TYPE_MISMATCH = 1922,
        RPC_S_NOT_ALL_OBJS_EXPORTED = 1923,
        RPC_S_INTERFACE_NOT_EXPORTED = 1924,
        RPC_S_PROFILE_NOT_ADDED = 1925,
        RPC_S_PRF_ELT_NOT_ADDED = 1926,
        RPC_S_PRF_ELT_NOT_REMOVED = 1927,
        RPC_S_GRP_ELT_NOT_ADDED = 1928,
        RPC_S_GRP_ELT_NOT_REMOVED = 1929,
        ERROR_KM_DRIVER_BLOCKED = 1930,
        ERROR_CONTEXT_EXPIRED = 1931,
        ERROR_INVALID_PIXEL_FORMAT = 2000,
        ERROR_BAD_DRIVER = 2001,
        ERROR_INVALID_WINDOW_STYLE = 2002,
        ERROR_METAFILE_NOT_SUPPORTED = 2003,
        ERROR_TRANSFORM_NOT_SUPPORTED = 2004,
        ERROR_CLIPPING_NOT_SUPPORTED = 2005,
        ERROR_INVALID_CMM = 2010,
        ERROR_INVALID_PROFILE = 2011,
        ERROR_TAG_NOT_FOUND = 2012,
        ERROR_TAG_NOT_PRESENT = 2013,
        ERROR_DUPLICATE_TAG = 2014,
        ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE = 2015,
        ERROR_PROFILE_NOT_FOUND = 2016,
        ERROR_INVALID_COLORSPACE = 2017,
        ERROR_ICM_NOT_ENABLED = 2018,
        ERROR_DELETING_ICM_XFORM = 2019,
        ERROR_INVALID_TRANSFORM = 2020,
        ERROR_COLORSPACE_MISMATCH = 2021,
        ERROR_INVALID_COLORINDEX = 2022,
        ERROR_CONNECTED_OTHER_PASSWORD = 2108,
        ERROR_CONNECTED_OTHER_PASSWORD_DEFAULT = 2109,
        ERROR_BAD_USERNAME = 2202,
        ERROR_NOT_CONNECTED = 2250,
        ERROR_OPEN_FILES = 2401,
        ERROR_ACTIVE_CONNECTIONS = 2402,
        ERROR_DEVICE_IN_USE = 2404,
        ERROR_UNKNOWN_PRINT_MONITOR = 3000,
        ERROR_PRINTER_DRIVER_IN_USE = 3001,
        ERROR_SPOOL_FILE_NOT_FOUND = 3002,
        ERROR_SPL_NO_STARTDOC = 3003,
        ERROR_SPL_NO_ADDJOB = 3004,
        ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED = 3005,
        ERROR_PRINT_MONITOR_ALREADY_INSTALLED = 3006,
        ERROR_INVALID_PRINT_MONITOR = 3007,
        ERROR_PRINT_MONITOR_IN_USE = 3008,
        ERROR_PRINTER_HAS_JOBS_QUEUED = 3009,
        ERROR_SUCCESS_REBOOT_REQUIRED = 3010,
        ERROR_SUCCESS_RESTART_REQUIRED = 3011,
        ERROR_PRINTER_NOT_FOUND = 3012,
        ERROR_PRINTER_DRIVER_WARNED = 3013,
        ERROR_PRINTER_DRIVER_BLOCKED = 3014,
        ERROR_WINS_INTERNAL = 4000,
        ERROR_CAN_NOT_DEL_LOCAL_WINS = 4001,
        ERROR_STATIC_INIT = 4002,
        ERROR_INC_BACKUP = 4003,
        ERROR_FULL_BACKUP = 4004,
        ERROR_REC_NON_EXISTENT = 4005,
        ERROR_RPL_NOT_ALLOWED = 4006,
        ERROR_DHCP_ADDRESS_CONFLICT = 4100,
        ERROR_WMI_GUID_NOT_FOUND = 4200,
        ERROR_WMI_INSTANCE_NOT_FOUND = 4201,
        ERROR_WMI_ITEMID_NOT_FOUND = 4202,
        ERROR_WMI_TRY_AGAIN = 4203,
        ERROR_WMI_DP_NOT_FOUND = 4204,
        ERROR_WMI_UNRESOLVED_INSTANCE_REF = 4205,
        ERROR_WMI_ALREADY_ENABLED = 4206,
        ERROR_WMI_GUID_DISCONNECTED = 4207,
        ERROR_WMI_SERVER_UNAVAILABLE = 4208,
        ERROR_WMI_DP_FAILED = 4209,
        ERROR_WMI_INVALID_MOF = 4210,
        ERROR_WMI_INVALID_REGINFO = 4211,
        ERROR_WMI_ALREADY_DISABLED = 4212,
        ERROR_WMI_READ_ONLY = 4213,
        ERROR_WMI_SET_FAILURE = 4214,
        ERROR_INVALID_MEDIA = 4300,
        ERROR_INVALID_LIBRARY = 4301,
        ERROR_INVALID_MEDIA_POOL = 4302,
        ERROR_DRIVE_MEDIA_MISMATCH = 4303,
        ERROR_MEDIA_OFFLINE = 4304,
        ERROR_LIBRARY_OFFLINE = 4305,
        ERROR_EMPTY = 4306,
        ERROR_NOT_EMPTY = 4307,
        ERROR_MEDIA_UNAVAILABLE = 4308,
        ERROR_RESOURCE_DISABLED = 4309,
        ERROR_INVALID_CLEANER = 4310,
        ERROR_UNABLE_TO_CLEAN = 4311,
        ERROR_OBJECT_NOT_FOUND = 4312,
        ERROR_DATABASE_FAILURE = 4313,
        ERROR_DATABASE_FULL = 4314,
        ERROR_MEDIA_INCOMPATIBLE = 4315,
        ERROR_RESOURCE_NOT_PRESENT = 4316,
        ERROR_INVALID_OPERATION = 4317,
        ERROR_MEDIA_NOT_AVAILABLE = 4318,
        ERROR_DEVICE_NOT_AVAILABLE = 4319,
        ERROR_REQUEST_REFUSED = 4320,
        ERROR_INVALID_DRIVE_OBJECT = 4321,
        ERROR_LIBRARY_FULL = 4322,
        ERROR_MEDIUM_NOT_ACCESSIBLE = 4323,
        ERROR_UNABLE_TO_LOAD_MEDIUM = 4324,
        ERROR_UNABLE_TO_INVENTORY_DRIVE = 4325,
        ERROR_UNABLE_TO_INVENTORY_SLOT = 4326,
        ERROR_UNABLE_TO_INVENTORY_TRANSPORT = 4327,
        ERROR_TRANSPORT_FULL = 4328,
        ERROR_CONTROLLING_IEPORT = 4329,
        ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA = 4330,
        ERROR_CLEANER_SLOT_SET = 4331,
        ERROR_CLEANER_SLOT_NOT_SET = 4332,
        ERROR_CLEANER_CARTRIDGE_SPENT = 4333,
        ERROR_UNEXPECTED_OMID = 4334,
        ERROR_CANT_DELETE_LAST_ITEM = 4335,
        ERROR_MESSAGE_EXCEEDS_MAX_SIZE = 4336,
        ERROR_VOLUME_CONTAINS_SYS_FILES = 4337,
        ERROR_INDIGENOUS_TYPE = 4338,
        ERROR_NO_SUPPORTING_DRIVES = 4339,
        ERROR_CLEANER_CARTRIDGE_INSTALLED = 4340,
        ERROR_FILE_OFFLINE = 4350,
        ERROR_REMOTE_STORAGE_NOT_ACTIVE = 4351,
        ERROR_REMOTE_STORAGE_MEDIA_ERROR = 4352,
        ERROR_NOT_A_REPARSE_POINT = 4390,
        ERROR_REPARSE_ATTRIBUTE_CONFLICT = 4391,
        ERROR_INVALID_REPARSE_DATA = 4392,
        ERROR_REPARSE_TAG_INVALID = 4393,
        ERROR_REPARSE_TAG_MISMATCH = 4394,
        ERROR_VOLUME_NOT_SIS_ENABLED = 4500,
        ERROR_DEPENDENT_RESOURCE_EXISTS = 5001,
        ERROR_DEPENDENCY_NOT_FOUND = 5002,
        ERROR_DEPENDENCY_ALREADY_EXISTS = 5003,
        ERROR_RESOURCE_NOT_ONLINE = 5004,
        ERROR_HOST_NODE_NOT_AVAILABLE = 5005,
        ERROR_RESOURCE_NOT_AVAILABLE = 5006,
        ERROR_RESOURCE_NOT_FOUND = 5007,
        ERROR_SHUTDOWN_CLUSTER = 5008,
        ERROR_CANT_EVICT_ACTIVE_NODE = 5009,
        ERROR_OBJECT_ALREADY_EXISTS = 5010,
        ERROR_OBJECT_IN_LIST = 5011,
        ERROR_GROUP_NOT_AVAILABLE = 5012,
        ERROR_GROUP_NOT_FOUND = 5013,
        ERROR_GROUP_NOT_ONLINE = 5014,
        ERROR_HOST_NODE_NOT_RESOURCE_OWNER = 5015,
        ERROR_HOST_NODE_NOT_GROUP_OWNER = 5016,
        ERROR_RESMON_CREATE_FAILED = 5017,
        ERROR_RESMON_ONLINE_FAILED = 5018,
        ERROR_RESOURCE_ONLINE = 5019,
        ERROR_QUORUM_RESOURCE = 5020,
        ERROR_NOT_QUORUM_CAPABLE = 5021,
        ERROR_CLUSTER_SHUTTING_DOWN = 5022,
        ERROR_INVALID_STATE = 5023,
        ERROR_RESOURCE_PROPERTIES_STORED = 5024,
        ERROR_NOT_QUORUM_CLASS = 5025,
        ERROR_CORE_RESOURCE = 5026,
        ERROR_QUORUM_RESOURCE_ONLINE_FAILED = 5027,
        ERROR_QUORUMLOG_OPEN_FAILED = 5028,
        ERROR_CLUSTERLOG_CORRUPT = 5029,
        ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE = 5030,
        ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE = 5031,
        ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND = 5032,
        ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE = 5033,
        ERROR_QUORUM_OWNER_ALIVE = 5034,
        ERROR_NETWORK_NOT_AVAILABLE = 5035,
        ERROR_NODE_NOT_AVAILABLE = 5036,
        ERROR_ALL_NODES_NOT_AVAILABLE = 5037,
        ERROR_RESOURCE_FAILED = 5038,
        ERROR_CLUSTER_INVALID_NODE = 5039,
        ERROR_CLUSTER_NODE_EXISTS = 5040,
        ERROR_CLUSTER_JOIN_IN_PROGRESS = 5041,
        ERROR_CLUSTER_NODE_NOT_FOUND = 5042,
        ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND = 5043,
        ERROR_CLUSTER_NETWORK_EXISTS = 5044,
        ERROR_CLUSTER_NETWORK_NOT_FOUND = 5045,
        ERROR_CLUSTER_NETINTERFACE_EXISTS = 5046,
        ERROR_CLUSTER_NETINTERFACE_NOT_FOUND = 5047,
        ERROR_CLUSTER_INVALID_REQUEST = 5048,
        ERROR_CLUSTER_INVALID_NETWORK_PROVIDER = 5049,
        ERROR_CLUSTER_NODE_DOWN = 5050,
        ERROR_CLUSTER_NODE_UNREACHABLE = 5051,
        ERROR_CLUSTER_NODE_NOT_MEMBER = 5052,
        ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS = 5053,
        ERROR_CLUSTER_INVALID_NETWORK = 5054,
        ERROR_CLUSTER_NODE_UP = 5056,
        ERROR_CLUSTER_IPADDR_IN_USE = 5057,
        ERROR_CLUSTER_NODE_NOT_PAUSED = 5058,
        ERROR_CLUSTER_NO_SECURITY_CONTEXT = 5059,
        ERROR_CLUSTER_NETWORK_NOT_INTERNAL = 5060,
        ERROR_CLUSTER_NODE_ALREADY_UP = 5061,
        ERROR_CLUSTER_NODE_ALREADY_DOWN = 5062,
        ERROR_CLUSTER_NETWORK_ALREADY_ONLINE = 5063,
        ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE = 5064,
        ERROR_CLUSTER_NODE_ALREADY_MEMBER = 5065,
        ERROR_CLUSTER_LAST_INTERNAL_NETWORK = 5066,
        ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS = 5067,
        ERROR_INVALID_OPERATION_ON_QUORUM = 5068,
        ERROR_DEPENDENCY_NOT_ALLOWED = 5069,
        ERROR_CLUSTER_NODE_PAUSED = 5070,
        ERROR_NODE_CANT_HOST_RESOURCE = 5071,
        ERROR_CLUSTER_NODE_NOT_READY = 5072,
        ERROR_CLUSTER_NODE_SHUTTING_DOWN = 5073,
        ERROR_CLUSTER_JOIN_ABORTED = 5074,
        ERROR_CLUSTER_INCOMPATIBLE_VERSIONS = 5075,
        ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED = 5076,
        ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED = 5077,
        ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND = 5078,
        ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED = 5079,
        ERROR_CLUSTER_RESNAME_NOT_FOUND = 5080,
        ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED = 5081,
        ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST = 5082,
        ERROR_CLUSTER_DATABASE_SEQMISMATCH = 5083,
        ERROR_RESMON_INVALID_STATE = 5084,
        ERROR_CLUSTER_GUM_NOT_LOCKER = 5085,
        ERROR_QUORUM_DISK_NOT_FOUND = 5086,
        ERROR_DATABASE_BACKUP_CORRUPT = 5087,
        ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT = 5088,
        ERROR_RESOURCE_PROPERTY_UNCHANGEABLE = 5089,
        ERROR_CLUSTER_MEMBERSHIP_INVALID_STATE = 5890,
        ERROR_CLUSTER_QUORUMLOG_NOT_FOUND = 5891,
        ERROR_CLUSTER_MEMBERSHIP_HALT = 5892,
        ERROR_CLUSTER_INSTANCE_ID_MISMATCH = 5893,
        ERROR_CLUSTER_NETWORK_NOT_FOUND_FOR_IP = 5894,
        ERROR_CLUSTER_PROPERTY_DATA_TYPE_MISMATCH = 5895,
        ERROR_CLUSTER_EVICT_WITHOUT_CLEANUP = 5896,
        ERROR_CLUSTER_PARAMETER_MISMATCH = 5897,
        ERROR_NODE_CANNOT_BE_CLUSTERED = 5898,
        ERROR_CLUSTER_WRONG_OS_VERSION = 5899,
        ERROR_CLUSTER_CANT_CREATE_DUP_CLUSTER_NAME = 5900,
        ERROR_ENCRYPTION_FAILED = 6000,
        ERROR_DECRYPTION_FAILED = 6001,
        ERROR_FILE_ENCRYPTED = 6002,
        ERROR_NO_RECOVERY_POLICY = 6003,
        ERROR_NO_EFS = 6004,
        ERROR_WRONG_EFS = 6005,
        ERROR_NO_USER_KEYS = 6006,
        ERROR_FILE_NOT_ENCRYPTED = 6007,
        ERROR_NOT_EXPORT_FORMAT = 6008,
        ERROR_FILE_READ_ONLY = 6009,
        ERROR_DIR_EFS_DISALLOWED = 6010,
        ERROR_EFS_SERVER_NOT_TRUSTED = 6011,
        ERROR_BAD_RECOVERY_POLICY = 6012,
        ERROR_EFS_ALG_BLOB_TOO_BIG = 6013,
        ERROR_VOLUME_NOT_SUPPORT_EFS = 6014,
        ERROR_EFS_DISABLED = 6015,
        ERROR_EFS_VERSION_NOT_SUPPORT = 6016,
        ERROR_NO_BROWSER_SERVERS_FOUND = 6118,
        SCHED_E_SERVICE_NOT_LOCALSYSTEM = 6200,
        ERROR_CTX_WINSTATION_NAME_INVALID = 7001,
        ERROR_CTX_INVALID_PD = 7002,
        ERROR_CTX_PD_NOT_FOUND = 7003,
        ERROR_CTX_WD_NOT_FOUND = 7004,
        ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY = 7005,
        ERROR_CTX_SERVICE_NAME_COLLISION = 7006,
        ERROR_CTX_CLOSE_PENDING = 7007,
        ERROR_CTX_NO_OUTBUF = 7008,
        ERROR_CTX_MODEM_INF_NOT_FOUND = 7009,
        ERROR_CTX_INVALID_MODEMNAME = 7010,
        ERROR_CTX_MODEM_RESPONSE_ERROR = 7011,
        ERROR_CTX_MODEM_RESPONSE_TIMEOUT = 7012,
        ERROR_CTX_MODEM_RESPONSE_NO_CARRIER = 7013,
        ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE = 7014,
        ERROR_CTX_MODEM_RESPONSE_BUSY = 7015,
        ERROR_CTX_MODEM_RESPONSE_VOICE = 7016,
        ERROR_CTX_TD_ERROR = 7017,
        ERROR_CTX_WINSTATION_NOT_FOUND = 7022,
        ERROR_CTX_WINSTATION_ALREADY_EXISTS = 7023,
        ERROR_CTX_WINSTATION_BUSY = 7024,
        ERROR_CTX_BAD_VIDEO_MODE = 7025,
        ERROR_CTX_GRAPHICS_INVALID = 7035,
        ERROR_CTX_LOGON_DISABLED = 7037,
        ERROR_CTX_NOT_CONSOLE = 7038,
        ERROR_CTX_CLIENT_QUERY_TIMEOUT = 7040,
        ERROR_CTX_CONSOLE_DISCONNECT = 7041,
        ERROR_CTX_CONSOLE_CONNECT = 7042,
        ERROR_CTX_SHADOW_DENIED = 7044,
        ERROR_CTX_WINSTATION_ACCESS_DENIED = 7045,
        ERROR_CTX_INVALID_WD = 7049,
        ERROR_CTX_SHADOW_INVALID = 7050,
        ERROR_CTX_SHADOW_DISABLED = 7051,
        ERROR_CTX_CLIENT_LICENSE_IN_USE = 7052,
        ERROR_CTX_CLIENT_LICENSE_NOT_SET = 7053,
        ERROR_CTX_LICENSE_NOT_AVAILABLE = 7054,
        ERROR_CTX_LICENSE_CLIENT_INVALID = 7055,
        ERROR_CTX_LICENSE_EXPIRED = 7056,
        ERROR_CTX_SHADOW_NOT_RUNNING = 7057,
        ERROR_CTX_SHADOW_ENDED_BY_MODE_CHANGE = 7058,
        FRS_ERR_INVALID_API_SEQUENCE = 8001,
        FRS_ERR_STARTING_SERVICE = 8002,
        FRS_ERR_STOPPING_SERVICE = 8003,
        FRS_ERR_INTERNAL_API = 8004,
        FRS_ERR_INTERNAL = 8005,
        FRS_ERR_SERVICE_COMM = 8006,
        FRS_ERR_INSUFFICIENT_PRIV = 8007,
        FRS_ERR_AUTHENTICATION = 8008,
        FRS_ERR_PARENT_INSUFFICIENT_PRIV = 8009,
        FRS_ERR_PARENT_AUTHENTICATION = 8010,
        FRS_ERR_CHILD_TO_PARENT_COMM = 8011,
        FRS_ERR_PARENT_TO_CHILD_COMM = 8012,
        FRS_ERR_SYSVOL_POPULATE = 8013,
        FRS_ERR_SYSVOL_POPULATE_TIMEOUT = 8014,
        FRS_ERR_SYSVOL_IS_BUSY = 8015,
        FRS_ERR_SYSVOL_DEMOTE = 8016,
        FRS_ERR_INVALID_SERVICE_PARAMETER = 8017,
        ERROR_DS_NOT_INSTALLED = 8200,
        ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY = 8201,
        ERROR_DS_NO_ATTRIBUTE_OR_VALUE = 8202,
        ERROR_DS_INVALID_ATTRIBUTE_SYNTAX = 8203,
        ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED = 8204,
        ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS = 8205,
        ERROR_DS_BUSY = 8206,
        ERROR_DS_UNAVAILABLE = 8207,
        ERROR_DS_NO_RIDS_ALLOCATED = 8208,
        ERROR_DS_NO_MORE_RIDS = 8209,
        ERROR_DS_INCORRECT_ROLE_OWNER = 8210,
        ERROR_DS_RIDMGR_INIT_ERROR = 8211,
        ERROR_DS_OBJ_CLASS_VIOLATION = 8212,
        ERROR_DS_CANT_ON_NON_LEAF = 8213,
        ERROR_DS_CANT_ON_RDN = 8214,
        ERROR_DS_CANT_MOD_OBJ_CLASS = 8215,
        ERROR_DS_CROSS_DOM_MOVE_ERROR = 8216,
        ERROR_DS_GC_NOT_AVAILABLE = 8217,
        ERROR_SHARED_POLICY = 8218,
        ERROR_POLICY_OBJECT_NOT_FOUND = 8219,
        ERROR_POLICY_ONLY_IN_DS = 8220,
        ERROR_PROMOTION_ACTIVE = 8221,
        ERROR_NO_PROMOTION_ACTIVE = 8222,
        ERROR_DS_OPERATIONS_ERROR = 8224,
        ERROR_DS_PROTOCOL_ERROR = 8225,
        ERROR_DS_TIMELIMIT_EXCEEDED = 8226,
        ERROR_DS_SIZELIMIT_EXCEEDED = 8227,
        ERROR_DS_ADMIN_LIMIT_EXCEEDED = 8228,
        ERROR_DS_COMPARE_FALSE = 8229,
        ERROR_DS_COMPARE_TRUE = 8230,
        ERROR_DS_AUTH_METHOD_NOT_SUPPORTED = 8231,
        ERROR_DS_STRONG_AUTH_REQUIRED = 8232,
        ERROR_DS_INAPPROPRIATE_AUTH = 8233,
        ERROR_DS_AUTH_UNKNOWN = 8234,
        ERROR_DS_REFERRAL = 8235,
        ERROR_DS_UNAVAILABLE_CRIT_EXTENSION = 8236,
        ERROR_DS_CONFIDENTIALITY_REQUIRED = 8237,
        ERROR_DS_INAPPROPRIATE_MATCHING = 8238,
        ERROR_DS_CONSTRAINT_VIOLATION = 8239,
        ERROR_DS_NO_SUCH_OBJECT = 8240,
        ERROR_DS_ALIAS_PROBLEM = 8241,
        ERROR_DS_INVALID_DN_SYNTAX = 8242,
        ERROR_DS_IS_LEAF = 8243,
        ERROR_DS_ALIAS_DEREF_PROBLEM = 8244,
        ERROR_DS_UNWILLING_TO_PERFORM = 8245,
        ERROR_DS_LOOP_DETECT = 8246,
        ERROR_DS_NAMING_VIOLATION = 8247,
        ERROR_DS_OBJECT_RESULTS_TOO_LARGE = 8248,
        ERROR_DS_AFFECTS_MULTIPLE_DSAS = 8249,
        ERROR_DS_SERVER_DOWN = 8250,
        ERROR_DS_LOCAL_ERROR = 8251,
        ERROR_DS_ENCODING_ERROR = 8252,
        ERROR_DS_DECODING_ERROR = 8253,
        ERROR_DS_FILTER_UNKNOWN = 8254,
        ERROR_DS_PARAM_ERROR = 8255,
        ERROR_DS_NOT_SUPPORTED = 8256,
        ERROR_DS_NO_RESULTS_RETURNED = 8257,
        ERROR_DS_CONTROL_NOT_FOUND = 8258,
        ERROR_DS_CLIENT_LOOP = 8259,
        ERROR_DS_REFERRAL_LIMIT_EXCEEDED = 8260,
        ERROR_DS_SORT_CONTROL_MISSING = 8261,
        ERROR_DS_OFFSET_RANGE_ERROR = 8262,
        ERROR_DS_ROOT_MUST_BE_NC = 8301,
        ERROR_DS_ADD_REPLICA_INHIBITED = 8302,
        ERROR_DS_ATT_NOT_DEF_IN_SCHEMA = 8303,
        ERROR_DS_MAX_OBJ_SIZE_EXCEEDED = 8304,
        ERROR_DS_OBJ_STRING_NAME_EXISTS = 8305,
        ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA = 8306,
        ERROR_DS_RDN_DOESNT_MATCH_SCHEMA = 8307,
        ERROR_DS_NO_REQUESTED_ATTS_FOUND = 8308,
        ERROR_DS_USER_BUFFER_TO_SMALL = 8309,
        ERROR_DS_ATT_IS_NOT_ON_OBJ = 8310,
        ERROR_DS_ILLEGAL_MOD_OPERATION = 8311,
        ERROR_DS_OBJ_TOO_LARGE = 8312,
        ERROR_DS_BAD_INSTANCE_TYPE = 8313,
        ERROR_DS_MASTERDSA_REQUIRED = 8314,
        ERROR_DS_OBJECT_CLASS_REQUIRED = 8315,
        ERROR_DS_MISSING_REQUIRED_ATT = 8316,
        ERROR_DS_ATT_NOT_DEF_FOR_CLASS = 8317,
        ERROR_DS_ATT_ALREADY_EXISTS = 8318,
        ERROR_DS_CANT_ADD_ATT_VALUES = 8320,
        ERROR_DS_SINGLE_VALUE_CONSTRAINT = 8321,
        ERROR_DS_RANGE_CONSTRAINT = 8322,
        ERROR_DS_ATT_VAL_ALREADY_EXISTS = 8323,
        ERROR_DS_CANT_REM_MISSING_ATT = 8324,
        ERROR_DS_CANT_REM_MISSING_ATT_VAL = 8325,
        ERROR_DS_ROOT_CANT_BE_SUBREF = 8326,
        ERROR_DS_NO_CHAINING = 8327,
        ERROR_DS_NO_CHAINED_EVAL = 8328,
        ERROR_DS_NO_PARENT_OBJECT = 8329,
        ERROR_DS_PARENT_IS_AN_ALIAS = 8330,
        ERROR_DS_CANT_MIX_MASTER_AND_REPS = 8331,
        ERROR_DS_CHILDREN_EXIST = 8332,
        ERROR_DS_OBJ_NOT_FOUND = 8333,
        ERROR_DS_ALIASED_OBJ_MISSING = 8334,
        ERROR_DS_BAD_NAME_SYNTAX = 8335,
        ERROR_DS_ALIAS_POINTS_TO_ALIAS = 8336,
        ERROR_DS_CANT_DEREF_ALIAS = 8337,
        ERROR_DS_OUT_OF_SCOPE = 8338,
        ERROR_DS_OBJECT_BEING_REMOVED = 8339,
        ERROR_DS_CANT_DELETE_DSA_OBJ = 8340,
        ERROR_DS_GENERIC_ERROR = 8341,
        ERROR_DS_DSA_MUST_BE_INT_MASTER = 8342,
        ERROR_DS_CLASS_NOT_DSA = 8343,
        ERROR_DS_INSUFF_ACCESS_RIGHTS = 8344,
        ERROR_DS_ILLEGAL_SUPERIOR = 8345,
        ERROR_DS_ATTRIBUTE_OWNED_BY_SAM = 8346,
        ERROR_DS_NAME_TOO_MANY_PARTS = 8347,
        ERROR_DS_NAME_TOO_LONG = 8348,
        ERROR_DS_NAME_VALUE_TOO_LONG = 8349,
        ERROR_DS_NAME_UNPARSEABLE = 8350,
        ERROR_DS_NAME_TYPE_UNKNOWN = 8351,
        ERROR_DS_NOT_AN_OBJECT = 8352,
        ERROR_DS_SEC_DESC_TOO_SHORT = 8353,
        ERROR_DS_SEC_DESC_INVALID = 8354,
        ERROR_DS_NO_DELETED_NAME = 8355,
        ERROR_DS_SUBREF_MUST_HAVE_PARENT = 8356,
        ERROR_DS_NCNAME_MUST_BE_NC = 8357,
        ERROR_DS_CANT_ADD_SYSTEM_ONLY = 8358,
        ERROR_DS_CLASS_MUST_BE_CONCRETE = 8359,
        ERROR_DS_INVALID_DMD = 8360,
        ERROR_DS_OBJ_GUID_EXISTS = 8361,
        ERROR_DS_NOT_ON_BACKLINK = 8362,
        ERROR_DS_NO_CROSSREF_FOR_NC = 8363,
        ERROR_DS_SHUTTING_DOWN = 8364,
        ERROR_DS_UNKNOWN_OPERATION = 8365,
        ERROR_DS_INVALID_ROLE_OWNER = 8366,
        ERROR_DS_COULDNT_CONTACT_FSMO = 8367,
        ERROR_DS_CROSS_NC_DN_RENAME = 8368,
        ERROR_DS_CANT_MOD_SYSTEM_ONLY = 8369,
        ERROR_DS_REPLICATOR_ONLY = 8370,
        ERROR_DS_OBJ_CLASS_NOT_DEFINED = 8371,
        ERROR_DS_OBJ_CLASS_NOT_SUBCLASS = 8372,
        ERROR_DS_NAME_REFERENCE_INVALID = 8373,
        ERROR_DS_CROSS_REF_EXISTS = 8374,
        ERROR_DS_CANT_DEL_MASTER_CROSSREF = 8375,
        ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD = 8376,
        ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX = 8377,
        ERROR_DS_DUP_RDN = 8378,
        ERROR_DS_DUP_OID = 8379,
        ERROR_DS_DUP_MAPI_ID = 8380,
        ERROR_DS_DUP_SCHEMA_ID_GUID = 8381,
        ERROR_DS_DUP_LDAP_DISPLAY_NAME = 8382,
        ERROR_DS_SEMANTIC_ATT_TEST = 8383,
        ERROR_DS_SYNTAX_MISMATCH = 8384,
        ERROR_DS_EXISTS_IN_MUST_HAVE = 8385,
        ERROR_DS_EXISTS_IN_MAY_HAVE = 8386,
        ERROR_DS_NONEXISTENT_MAY_HAVE = 8387,
        ERROR_DS_NONEXISTENT_MUST_HAVE = 8388,
        ERROR_DS_AUX_CLS_TEST_FAIL = 8389,
        ERROR_DS_NONEXISTENT_POSS_SUP = 8390,
        ERROR_DS_SUB_CLS_TEST_FAIL = 8391,
        ERROR_DS_BAD_RDN_ATT_ID_SYNTAX = 8392,
        ERROR_DS_EXISTS_IN_AUX_CLS = 8393,
        ERROR_DS_EXISTS_IN_SUB_CLS = 8394,
        ERROR_DS_EXISTS_IN_POSS_SUP = 8395,
        ERROR_DS_RECALCSCHEMA_FAILED = 8396,
        ERROR_DS_TREE_DELETE_NOT_FINISHED = 8397,
        ERROR_DS_CANT_DELETE = 8398,
        ERROR_DS_ATT_SCHEMA_REQ_ID = 8399,
        ERROR_DS_BAD_ATT_SCHEMA_SYNTAX = 8400,
        ERROR_DS_CANT_CACHE_ATT = 8401,
        ERROR_DS_CANT_CACHE_CLASS = 8402,
        ERROR_DS_CANT_REMOVE_ATT_CACHE = 8403,
        ERROR_DS_CANT_REMOVE_CLASS_CACHE = 8404,
        ERROR_DS_CANT_RETRIEVE_DN = 8405,
        ERROR_DS_MISSING_SUPREF = 8406,
        ERROR_DS_CANT_RETRIEVE_INSTANCE = 8407,
        ERROR_DS_CODE_INCONSISTENCY = 8408,
        ERROR_DS_DATABASE_ERROR = 8409,
        ERROR_DS_GOVERNSID_MISSING = 8410,
        ERROR_DS_MISSING_EXPECTED_ATT = 8411,
        ERROR_DS_NCNAME_MISSING_CR_REF = 8412,
        ERROR_DS_SECURITY_CHECKING_ERROR = 8413,
        ERROR_DS_SCHEMA_NOT_LOADED = 8414,
        ERROR_DS_SCHEMA_ALLOC_FAILED = 8415,
        ERROR_DS_ATT_SCHEMA_REQ_SYNTAX = 8416,
        ERROR_DS_GCVERIFY_ERROR = 8417,
        ERROR_DS_DRA_SCHEMA_MISMATCH = 8418,
        ERROR_DS_CANT_FIND_DSA_OBJ = 8419,
        ERROR_DS_CANT_FIND_EXPECTED_NC = 8420,
        ERROR_DS_CANT_FIND_NC_IN_CACHE = 8421,
        ERROR_DS_CANT_RETRIEVE_CHILD = 8422,
        ERROR_DS_SECURITY_ILLEGAL_MODIFY = 8423,
        ERROR_DS_CANT_REPLACE_HIDDEN_REC = 8424,
        ERROR_DS_BAD_HIERARCHY_FILE = 8425,
        ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED = 8426,
        ERROR_DS_CONFIG_PARAM_MISSING = 8427,
        ERROR_DS_COUNTING_AB_INDICES_FAILED = 8428,
        ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED = 8429,
        ERROR_DS_INTERNAL_FAILURE = 8430,
        ERROR_DS_UNKNOWN_ERROR = 8431,
        ERROR_DS_ROOT_REQUIRES_CLASS_TOP = 8432,
        ERROR_DS_REFUSING_FSMO_ROLES = 8433,
        ERROR_DS_MISSING_FSMO_SETTINGS = 8434,
        ERROR_DS_UNABLE_TO_SURRENDER_ROLES = 8435,
        ERROR_DS_DRA_GENERIC = 8436,
        ERROR_DS_DRA_INVALID_PARAMETER = 8437,
        ERROR_DS_DRA_BUSY = 8438,
        ERROR_DS_DRA_BAD_DN = 8439,
        ERROR_DS_DRA_BAD_NC = 8440,
        ERROR_DS_DRA_DN_EXISTS = 8441,
        ERROR_DS_DRA_INTERNAL_ERROR = 8442,
        ERROR_DS_DRA_INCONSISTENT_DIT = 8443,
        ERROR_DS_DRA_CONNECTION_FAILED = 8444,
        ERROR_DS_DRA_BAD_INSTANCE_TYPE = 8445,
        ERROR_DS_DRA_OUT_OF_MEM = 8446,
        ERROR_DS_DRA_MAIL_PROBLEM = 8447,
        ERROR_DS_DRA_REF_ALREADY_EXISTS = 8448,
        ERROR_DS_DRA_REF_NOT_FOUND = 8449,
        ERROR_DS_DRA_OBJ_IS_REP_SOURCE = 8450,
        ERROR_DS_DRA_DB_ERROR = 8451,
        ERROR_DS_DRA_NO_REPLICA = 8452,
        ERROR_DS_DRA_ACCESS_DENIED = 8453,
        ERROR_DS_DRA_NOT_SUPPORTED = 8454,
        ERROR_DS_DRA_RPC_CANCELLED = 8455,
        ERROR_DS_DRA_SOURCE_DISABLED = 8456,
        ERROR_DS_DRA_SINK_DISABLED = 8457,
        ERROR_DS_DRA_NAME_COLLISION = 8458,
        ERROR_DS_DRA_SOURCE_REINSTALLED = 8459,
        ERROR_DS_DRA_MISSING_PARENT = 8460,
        ERROR_DS_DRA_PREEMPTED = 8461,
        ERROR_DS_DRA_ABANDON_SYNC = 8462,
        ERROR_DS_DRA_SHUTDOWN = 8463,
        ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET = 8464,
        ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA = 8465,
        ERROR_DS_DRA_EXTN_CONNECTION_FAILED = 8466,
        ERROR_DS_INSTALL_SCHEMA_MISMATCH = 8467,
        ERROR_DS_DUP_LINK_ID = 8468,
        ERROR_DS_NAME_ERROR_RESOLVING = 8469,
        ERROR_DS_NAME_ERROR_NOT_FOUND = 8470,
        ERROR_DS_NAME_ERROR_NOT_UNIQUE = 8471,
        ERROR_DS_NAME_ERROR_NO_MAPPING = 8472,
        ERROR_DS_NAME_ERROR_DOMAIN_ONLY = 8473,
        ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING = 8474,
        ERROR_DS_CONSTRUCTED_ATT_MOD = 8475,
        ERROR_DS_WRONG_OM_OBJ_CLASS = 8476,
        ERROR_DS_DRA_REPL_PENDING = 8477,
        ERROR_DS_DS_REQUIRED = 8478,
        ERROR_DS_INVALID_LDAP_DISPLAY_NAME = 8479,
        ERROR_DS_NON_BASE_SEARCH = 8480,
        ERROR_DS_CANT_RETRIEVE_ATTS = 8481,
        ERROR_DS_BACKLINK_WITHOUT_LINK = 8482,
        ERROR_DS_EPOCH_MISMATCH = 8483,
        ERROR_DS_SRC_NAME_MISMATCH = 8484,
        ERROR_DS_SRC_AND_DST_NC_IDENTICAL = 8485,
        ERROR_DS_DST_NC_MISMATCH = 8486,
        ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC = 8487,
        ERROR_DS_SRC_GUID_MISMATCH = 8488,
        ERROR_DS_CANT_MOVE_DELETED_OBJECT = 8489,
        ERROR_DS_PDC_OPERATION_IN_PROGRESS = 8490,
        ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD = 8491,
        ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION = 8492,
        ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS = 8493,
        ERROR_DS_NC_MUST_HAVE_NC_PARENT = 8494,
        ERROR_DS_DST_DOMAIN_NOT_NATIVE = 8496,
        ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER = 8497,
        ERROR_DS_CANT_MOVE_ACCOUNT_GROUP = 8498,
        ERROR_DS_CANT_MOVE_RESOURCE_GROUP = 8499,
        ERROR_DS_INVALID_SEARCH_FLAG = 8500,
        ERROR_DS_NO_TREE_DELETE_ABOVE_NC = 8501,
        ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE = 8502,
        ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE = 8503,
        ERROR_DS_SAM_INIT_FAILURE = 8504,
        ERROR_DS_SENSITIVE_GROUP_VIOLATION = 8505,
        ERROR_DS_CANT_MOD_PRIMARYGROUPID = 8506,
        ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD = 8507,
        ERROR_DS_NONSAFE_SCHEMA_CHANGE = 8508,
        ERROR_DS_SCHEMA_UPDATE_DISALLOWED = 8509,
        ERROR_DS_CANT_CREATE_UNDER_SCHEMA = 8510,
        ERROR_DS_INSTALL_NO_SRC_SCH_VERSION = 8511,
        ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE = 8512,
        ERROR_DS_INVALID_GROUP_TYPE = 8513,
        ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN = 8514,
        ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN = 8515,
        ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER = 8516,
        ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER = 8517,
        ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER = 8518,
        ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER = 8519,
        ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER = 8520,
        ERROR_DS_HAVE_PRIMARY_MEMBERS = 8521,
        ERROR_DS_STRING_SD_CONVERSION_FAILED = 8522,
        ERROR_DS_NAMING_MASTER_GC = 8523,
        ERROR_DS_LOOKUP_FAILURE = 8524,
        ERROR_DS_COULDNT_UPDATE_SPNS = 8525,
        ERROR_DS_CANT_RETRIEVE_SD = 8526,
        ERROR_DS_KEY_NOT_UNIQUE = 8527,
        ERROR_DS_WRONG_LINKED_ATT_SYNTAX = 8528,
        ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD = 8529,
        ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY = 8530,
        ERROR_DS_CANT_START = 8531,
        ERROR_DS_INIT_FAILURE = 8532,
        ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION = 8533,
        ERROR_DS_SOURCE_DOMAIN_IN_FOREST = 8534,
        ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST = 8535,
        ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED = 8536,
        ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN = 8537,
        ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER = 8538,
        ERROR_DS_SRC_SID_EXISTS_IN_FOREST = 8539,
        ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH = 8540,
        ERROR_SAM_INIT_FAILURE = 8541,
        ERROR_DS_DRA_SCHEMA_INFO_SHIP = 8542,
        ERROR_DS_DRA_SCHEMA_CONFLICT = 8543,
        ERROR_DS_DRA_EARLIER_SCHEMA_CONLICT = 8544,
        ERROR_DS_DRA_OBJ_NC_MISMATCH = 8545,
        ERROR_DS_NC_STILL_HAS_DSAS = 8546,
        ERROR_DS_GC_REQUIRED = 8547,
        ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY = 8548,
        ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS = 8549,
        ERROR_DS_CANT_ADD_TO_GC = 8550,
        ERROR_DS_NO_CHECKPOINT_WITH_PDC = 8551,
        ERROR_DS_SOURCE_AUDITING_NOT_ENABLED = 8552,
        ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC = 8553,
        ERROR_DS_INVALID_NAME_FOR_SPN = 8554,
        ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS = 8555,
        ERROR_DS_UNICODEPWD_NOT_IN_QUOTES = 8556,
        ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED = 8557,
        ERROR_DS_MUST_BE_RUN_ON_DST_DC = 8558,
        ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER = 8559,
        ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ = 8560,
        ERROR_DS_INIT_FAILURE_CONSOLE = 8561,
        ERROR_DS_SAM_INIT_FAILURE_CONSOLE = 8562,
        ERROR_DS_FOREST_VERSION_TOO_HIGH = 8563,
        ERROR_DS_DOMAIN_VERSION_TOO_HIGH = 8564,
        ERROR_DS_FOREST_VERSION_TOO_LOW = 8565,
        ERROR_DS_DOMAIN_VERSION_TOO_LOW = 8566,
        ERROR_DS_INCOMPATIBLE_VERSION = 8567,
        ERROR_DS_LOW_DSA_VERSION = 8568,
        ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN = 8569,
        ERROR_DS_NOT_SUPPORTED_SORT_ORDER = 8570,
        ERROR_DS_NAME_NOT_UNIQUE = 8571,
        ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4 = 8572,
        ERROR_DS_OUT_OF_VERSION_STORE = 8573,
        ERROR_DS_INCOMPATIBLE_CONTROLS_USED = 8574,
        ERROR_DS_NO_REF_DOMAIN = 8575,
        ERROR_DS_RESERVED_LINK_ID = 8576,
        ERROR_DS_LINK_ID_NOT_AVAILABLE = 8577,
        ERROR_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER = 8578,
        ERROR_DS_MODIFYDN_DISALLOWED_BY_INSTANCE_TYPE = 8579,
        ERROR_DS_NO_OBJECT_MOVE_IN_SCHEMA_NC = 8580,
        ERROR_DS_MODIFYDN_DISALLOWED_BY_FLAG = 8581,
        ERROR_DS_MODIFYDN_WRONG_GRANDPARENT = 8582,
        ERROR_DS_NAME_ERROR_TRUST_REFERRAL = 8583,
        ERROR_NOT_SUPPORTED_ON_STANDARD_SERVER = 8584,
        ERROR_DS_CANT_ACCESS_REMOTE_PART_OF_AD = 8585,
        ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE = 8586,
        ERROR_DS_THREAD_LIMIT_EXCEEDED = 8587,
        ERROR_DS_NOT_CLOSEST = 8588,
        ERROR_DS_CANT_DERIVE_SPN_WITHOUT_SERVER_REF = 8589,
        ERROR_DS_SINGLE_USER_MODE_FAILED = 8590,
        ERROR_DS_NTDSCRIPT_SYNTAX_ERROR = 8591,
        ERROR_DS_NTDSCRIPT_PROCESS_ERROR = 8592,
        ERROR_DS_DIFFERENT_REPL_EPOCHS = 8593,
        ERROR_DS_DRS_EXTENSIONS_CHANGED = 8594,
        ERROR_DS_REPLICA_SET_CHANGE_NOT_ALLOWED_ON_DISABLED_CR = 8595,
        ERROR_DS_NO_MSDS_INTID = 8596,
        ERROR_DS_DUP_MSDS_INTID = 8597,
        ERROR_DS_EXISTS_IN_RDNATTID = 8598,
        ERROR_DS_AUTHORIZATION_FAILED = 8599,
        ERROR_DS_INVALID_SCRIPT = 8600,
        ERROR_DS_REMOTE_CROSSREF_OP_FAILED = 8601,
        DNS_ERROR_RCODE_FORMAT_ERROR = 9001,
        DNS_ERROR_RCODE_SERVER_FAILURE = 9002,
        DNS_ERROR_RCODE_NAME_ERROR = 9003,
        DNS_ERROR_RCODE_NOT_IMPLEMENTED = 9004,
        DNS_ERROR_RCODE_REFUSED = 9005,
        DNS_ERROR_RCODE_YXDOMAIN = 9006,
        DNS_ERROR_RCODE_YXRRSET = 9007,
        DNS_ERROR_RCODE_NXRRSET = 9008,
        DNS_ERROR_RCODE_NOTAUTH = 9009,
        DNS_ERROR_RCODE_NOTZONE = 9010,
        DNS_ERROR_RCODE_BADSIG = 9016,
        DNS_ERROR_RCODE_BADKEY = 9017,
        DNS_ERROR_RCODE_BADTIME = 9018,
        DNS_INFO_NO_RECORDS = 9501,
        DNS_ERROR_BAD_PACKET = 9502,
        DNS_ERROR_NO_PACKET = 9503,
        DNS_ERROR_RCODE = 9504,
        DNS_ERROR_UNSECURE_PACKET = 9505,
        DNS_ERROR_INVALID_TYPE = 9551,
        DNS_ERROR_INVALID_IP_ADDRESS = 9552,
        DNS_ERROR_INVALID_PROPERTY = 9553,
        DNS_ERROR_TRY_AGAIN_LATER = 9554,
        DNS_ERROR_NOT_UNIQUE = 9555,
        DNS_ERROR_NON_RFC_NAME = 9556,
        DNS_STATUS_FQDN = 9557,
        DNS_STATUS_DOTTED_NAME = 9558,
        DNS_STATUS_SINGLE_PART_NAME = 9559,
        DNS_ERROR_INVALID_NAME_CHAR = 9560,
        DNS_ERROR_NUMERIC_NAME = 9561,
        DNS_ERROR_NOT_ALLOWED_ON_ROOT_SERVER = 9562,
        DNS_ERROR_ZONE_DOES_NOT_EXIST = 9601,
        DNS_ERROR_NO_ZONE_INFO = 9602,
        DNS_ERROR_INVALID_ZONE_OPERATION = 9603,
        DNS_ERROR_ZONE_CONFIGURATION_ERROR = 9604,
        DNS_ERROR_ZONE_HAS_NO_SOA_RECORD = 9605,
        DNS_ERROR_ZONE_HAS_NO_NS_RECORDS = 9606,
        DNS_ERROR_ZONE_LOCKED = 9607,
        DNS_ERROR_ZONE_CREATION_FAILED = 9608,
        DNS_ERROR_ZONE_ALREADY_EXISTS = 9609,
        DNS_ERROR_AUTOZONE_ALREADY_EXISTS = 9610,
        DNS_ERROR_INVALID_ZONE_TYPE = 9611,
        DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP = 9612,
        DNS_ERROR_ZONE_NOT_SECONDARY = 9613,
        DNS_ERROR_NEED_SECONDARY_ADDRESSES = 9614,
        DNS_ERROR_WINS_INIT_FAILED = 9615,
        DNS_ERROR_NEED_WINS_SERVERS = 9616,
        DNS_ERROR_NBSTAT_INIT_FAILED = 9617,
        DNS_ERROR_SOA_DELETE_INVALID = 9618,
        DNS_ERROR_FORWARDER_ALREADY_EXISTS = 9619,
        DNS_ERROR_ZONE_REQUIRES_MASTER_IP = 9620,
        DNS_ERROR_ZONE_IS_SHUTDOWN = 9621,
        DNS_ERROR_PRIMARY_REQUIRES_DATAFILE = 9651,
        DNS_ERROR_INVALID_DATAFILE_NAME = 9652,
        DNS_ERROR_DATAFILE_OPEN_FAILURE = 9653,
        DNS_ERROR_FILE_WRITEBACK_FAILED = 9654,
        DNS_ERROR_DATAFILE_PARSING = 9655,
        DNS_ERROR_RECORD_DOES_NOT_EXIST = 9701,
        DNS_ERROR_RECORD_FORMAT = 9702,
        DNS_ERROR_NODE_CREATION_FAILED = 9703,
        DNS_ERROR_UNKNOWN_RECORD_TYPE = 9704,
        DNS_ERROR_RECORD_TIMED_OUT = 9705,
        DNS_ERROR_NAME_NOT_IN_ZONE = 9706,
        DNS_ERROR_CNAME_LOOP = 9707,
        DNS_ERROR_NODE_IS_CNAME = 9708,
        DNS_ERROR_CNAME_COLLISION = 9709,
        DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT = 9710,
        DNS_ERROR_RECORD_ALREADY_EXISTS = 9711,
        DNS_ERROR_SECONDARY_DATA = 9712,
        DNS_ERROR_NO_CREATE_CACHE_DATA = 9713,
        DNS_ERROR_NAME_DOES_NOT_EXIST = 9714,
        DNS_WARNING_PTR_CREATE_FAILED = 9715,
        DNS_WARNING_DOMAIN_UNDELETED = 9716,
        DNS_ERROR_DS_UNAVAILABLE = 9717,
        DNS_ERROR_DS_ZONE_ALREADY_EXISTS = 9718,
        DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE = 9719,
        DNS_INFO_AXFR_COMPLETE = 9751,
        DNS_ERROR_AXFR = 9752,
        DNS_INFO_ADDED_LOCAL_WINS = 9753,
        DNS_STATUS_CONTINUE_NEEDED = 9801,
        DNS_ERROR_NO_TCPIP = 9851,
        DNS_ERROR_NO_DNS_SERVERS = 9852,
        DNS_ERROR_DP_DOES_NOT_EXIST = 9901,
        DNS_ERROR_DP_ALREADY_EXISTS = 9902,
        DNS_ERROR_DP_NOT_ENLISTED = 9903,
        DNS_ERROR_DP_ALREADY_ENLISTED = 9904,
        WSAEINTR = 10004,
        WSAEBADF = 10009,
        WSAEACCES = 10013,
        WSAEFAULT = 10014,
        WSAEINVAL = 10022,
        WSAEMFILE = 10024,
        WSAEWOULDBLOCK = 10035,
        WSAEINPROGRESS = 10036,
        WSAEALREADY = 10037,
        WSAENOTSOCK = 10038,
        WSAEDESTADDRREQ = 10039,
        WSAEMSGSIZE = 10040,
        WSAEPROTOTYPE = 10041,
        WSAENOPROTOOPT = 10042,
        WSAEPROTONOSUPPORT = 10043,
        WSAESOCKTNOSUPPORT = 10044,
        WSAEOPNOTSUPP = 10045,
        WSAEPFNOSUPPORT = 10046,
        WSAEAFNOSUPPORT = 10047,
        WSAEADDRINUSE = 10048,
        WSAEADDRNOTAVAIL = 10049,
        WSAENETDOWN = 10050,
        WSAENETUNREACH = 10051,
        WSAENETRESET = 10052,
        WSAECONNABORTED = 10053,
        WSAECONNRESET = 10054,
        WSAENOBUFS = 10055,
        WSAEISCONN = 10056,
        WSAENOTCONN = 10057,
        WSAESHUTDOWN = 10058,
        WSAETOOMANYREFS = 10059,
        WSAETIMEDOUT = 10060,
        WSAECONNREFUSED = 10061,
        WSAELOOP = 10062,
        WSAENAMETOOLONG = 10063,
        WSAEHOSTDOWN = 10064,
        WSAEHOSTUNREACH = 10065,
        WSAENOTEMPTY = 10066,
        WSAEPROCLIM = 10067,
        WSAEUSERS = 10068,
        WSAEDQUOT = 10069,
        WSAESTALE = 10070,
        WSAEREMOTE = 10071,
        WSASYSNOTREADY = 10091,
        WSAVERNOTSUPPORTED = 10092,
        WSANOTINITIALISED = 10093,
        WSAEDISCON = 10101,
        WSAENOMORE = 10102,
        WSAECANCELLED = 10103,
        WSAEINVALIDPROCTABLE = 10104,
        WSAEINVALIDPROVIDER = 10105,
        WSAEPROVIDERFAILEDINIT = 10106,
        WSASYSCALLFAILURE = 10107,
        WSASERVICE_NOT_FOUND = 10108,
        WSATYPE_NOT_FOUND = 10109,
        WSA_E_NO_MORE = 10110,
        WSA_E_CANCELLED = 10111,
        WSAEREFUSED = 10112,
        WSAHOST_NOT_FOUND = 11001,
        WSATRY_AGAIN = 11002,
        WSANO_RECOVERY = 11003,
        WSANO_DATA = 11004,
        WSA_QOS_RECEIVERS = 11005,
        WSA_QOS_SENDERS = 11006,
        WSA_QOS_NO_SENDERS = 11007,
        WSA_QOS_NO_RECEIVERS = 11008,
        WSA_QOS_REQUEST_CONFIRMED = 11009,
        WSA_QOS_ADMISSION_FAILURE = 11010,
        WSA_QOS_POLICY_FAILURE = 11011,
        WSA_QOS_BAD_STYLE = 11012,
        WSA_QOS_BAD_OBJECT = 11013,
        WSA_QOS_TRAFFIC_CTRL_ERROR = 11014,
        WSA_QOS_GENERIC_ERROR = 11015,
        WSA_QOS_ESERVICETYPE = 11016,
        WSA_QOS_EFLOWSPEC = 11017,
        WSA_QOS_EPROVSPECBUF = 11018,
        WSA_QOS_EFILTERSTYLE = 11019,
        WSA_QOS_EFILTERTYPE = 11020,
        WSA_QOS_EFILTERCOUNT = 11021,
        WSA_QOS_EOBJLENGTH = 11022,
        WSA_QOS_EFLOWCOUNT = 11023,
        WSA_QOS_EUNKNOWNPSOBJ = 11024,
        WSA_QOS_EPOLICYOBJ = 11025,
        WSA_QOS_EFLOWDESC = 11026,
        WSA_QOS_EPSFLOWSPEC = 11027,
        WSA_QOS_EPSFILTERSPEC = 11028,
        WSA_QOS_ESDMODEOBJ = 11029,
        WSA_QOS_ESHAPERATEOBJ = 11030,
        WSA_QOS_RESERVED_PETYPE = 11031,
        ERROR_IPSEC_QM_POLICY_EXISTS = 13000,
        ERROR_IPSEC_QM_POLICY_NOT_FOUND = 13001,
        ERROR_IPSEC_QM_POLICY_IN_USE = 13002,
        ERROR_IPSEC_MM_POLICY_EXISTS = 13003,
        ERROR_IPSEC_MM_POLICY_NOT_FOUND = 13004,
        ERROR_IPSEC_MM_POLICY_IN_USE = 13005,
        ERROR_IPSEC_MM_FILTER_EXISTS = 13006,
        ERROR_IPSEC_MM_FILTER_NOT_FOUND = 13007,
        ERROR_IPSEC_TRANSPORT_FILTER_EXISTS = 13008,
        ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND = 13009,
        ERROR_IPSEC_MM_AUTH_EXISTS = 13010,
        ERROR_IPSEC_MM_AUTH_NOT_FOUND = 13011,
        ERROR_IPSEC_MM_AUTH_IN_USE = 13012,
        ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND = 13013,
        ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND = 13014,
        ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND = 13015,
        ERROR_IPSEC_TUNNEL_FILTER_EXISTS = 13016,
        ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND = 13017,
        ERROR_IPSEC_MM_FILTER_PENDING_DELETION = 13018,
        ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION = 13019,
        ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION = 13020,
        ERROR_IPSEC_MM_POLICY_PENDING_DELETION = 13021,
        ERROR_IPSEC_MM_AUTH_PENDING_DELETION = 13022,
        ERROR_IPSEC_QM_POLICY_PENDING_DELETION = 13023,
        ERROR_IPSEC_IKE_AUTH_FAIL = 13801,
        ERROR_IPSEC_IKE_ATTRIB_FAIL = 13802,
        ERROR_IPSEC_IKE_NEGOTIATION_PENDING = 13803,
        ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR = 13804,
        ERROR_IPSEC_IKE_TIMED_OUT = 13805,
        ERROR_IPSEC_IKE_NO_CERT = 13806,
        ERROR_IPSEC_IKE_SA_DELETED = 13807,
        ERROR_IPSEC_IKE_SA_REAPED = 13808,
        ERROR_IPSEC_IKE_MM_ACQUIRE_DROP = 13809,
        ERROR_IPSEC_IKE_QM_ACQUIRE_DROP = 13810,
        ERROR_IPSEC_IKE_QUEUE_DROP_MM = 13811,
        ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM = 13812,
        ERROR_IPSEC_IKE_DROP_NO_RESPONSE = 13813,
        ERROR_IPSEC_IKE_MM_DELAY_DROP = 13814,
        ERROR_IPSEC_IKE_QM_DELAY_DROP = 13815,
        ERROR_IPSEC_IKE_ERROR = 13816,
        ERROR_IPSEC_IKE_CRL_FAILED = 13817,
        ERROR_IPSEC_IKE_INVALID_KEY_USAGE = 13818,
        ERROR_IPSEC_IKE_INVALID_CERT_TYPE = 13819,
        ERROR_IPSEC_IKE_NO_PRIVATE_KEY = 13820,
        ERROR_IPSEC_IKE_DH_FAIL = 13822,
        ERROR_IPSEC_IKE_INVALID_HEADER = 13824,
        ERROR_IPSEC_IKE_NO_POLICY = 13825,
        ERROR_IPSEC_IKE_INVALID_SIGNATURE = 13826,
        ERROR_IPSEC_IKE_KERBEROS_ERROR = 13827,
        ERROR_IPSEC_IKE_NO_PUBLIC_KEY = 13828,
        ERROR_IPSEC_IKE_PROCESS_ERR = 13829,
        ERROR_IPSEC_IKE_PROCESS_ERR_SA = 13830,
        ERROR_IPSEC_IKE_PROCESS_ERR_PROP = 13831,
        ERROR_IPSEC_IKE_PROCESS_ERR_TRANS = 13832,
        ERROR_IPSEC_IKE_PROCESS_ERR_KE = 13833,
        ERROR_IPSEC_IKE_PROCESS_ERR_ID = 13834,
        ERROR_IPSEC_IKE_PROCESS_ERR_CERT = 13835,
        ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ = 13836,
        ERROR_IPSEC_IKE_PROCESS_ERR_HASH = 13837,
        ERROR_IPSEC_IKE_PROCESS_ERR_SIG = 13838,
        ERROR_IPSEC_IKE_PROCESS_ERR_NONCE = 13839,
        ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY = 13840,
        ERROR_IPSEC_IKE_PROCESS_ERR_DELETE = 13841,
        ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR = 13842,
        ERROR_IPSEC_IKE_INVALID_PAYLOAD = 13843,
        ERROR_IPSEC_IKE_LOAD_SOFT_SA = 13844,
        ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN = 13845,
        ERROR_IPSEC_IKE_INVALID_COOKIE = 13846,
        ERROR_IPSEC_IKE_NO_PEER_CERT = 13847,
        ERROR_IPSEC_IKE_PEER_CRL_FAILED = 13848,
        ERROR_IPSEC_IKE_POLICY_CHANGE = 13849,
        ERROR_IPSEC_IKE_NO_MM_POLICY = 13850,
        ERROR_IPSEC_IKE_NOTCBPRIV = 13851,
        ERROR_IPSEC_IKE_SECLOADFAIL = 13852,
        ERROR_IPSEC_IKE_FAILSSPINIT = 13853,
        ERROR_IPSEC_IKE_FAILQUERYSSP = 13854,
        ERROR_IPSEC_IKE_SRVACQFAIL = 13855,
        ERROR_IPSEC_IKE_SRVQUERYCRED = 13856,
        ERROR_IPSEC_IKE_GETSPIFAIL = 13857,
        ERROR_IPSEC_IKE_INVALID_FILTER = 13858,
        ERROR_IPSEC_IKE_OUT_OF_MEMORY = 13859,
        ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED = 13860,
        ERROR_IPSEC_IKE_INVALID_POLICY = 13861,
        ERROR_IPSEC_IKE_UNKNOWN_DOI = 13862,
        ERROR_IPSEC_IKE_INVALID_SITUATION = 13863,
        ERROR_IPSEC_IKE_DH_FAILURE = 13864,
        ERROR_IPSEC_IKE_INVALID_GROUP = 13865,
        ERROR_IPSEC_IKE_ENCRYPT = 13866,
        ERROR_IPSEC_IKE_DECRYPT = 13867,
        ERROR_IPSEC_IKE_POLICY_MATCH = 13868,
        ERROR_IPSEC_IKE_UNSUPPORTED_ID = 13869,
        ERROR_IPSEC_IKE_INVALID_HASH = 13870,
        ERROR_IPSEC_IKE_INVALID_HASH_ALG = 13871,
        ERROR_IPSEC_IKE_INVALID_HASH_SIZE = 13872,
        ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG = 13873,
        ERROR_IPSEC_IKE_INVALID_AUTH_ALG = 13874,
        ERROR_IPSEC_IKE_INVALID_SIG = 13875,
        ERROR_IPSEC_IKE_LOAD_FAILED = 13876,
        ERROR_IPSEC_IKE_RPC_DELETE = 13877,
        ERROR_IPSEC_IKE_BENIGN_REINIT = 13878,
        ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY = 13879,
        ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN = 13881,
        ERROR_IPSEC_IKE_MM_LIMIT = 13882,
        ERROR_IPSEC_IKE_NEGOTIATION_DISABLED = 13883,
        ERROR_IPSEC_IKE_NEG_STATUS_END = 13884,
        ERROR_SXS_SECTION_NOT_FOUND = 14000,
        ERROR_SXS_CANT_GEN_ACTCTX = 14001,
        ERROR_SXS_INVALID_ACTCTXDATA_FORMAT = 14002,
        ERROR_SXS_ASSEMBLY_NOT_FOUND = 14003,
        ERROR_SXS_MANIFEST_FORMAT_ERROR = 14004,
        ERROR_SXS_MANIFEST_PARSE_ERROR = 14005,
        ERROR_SXS_ACTIVATION_CONTEXT_DISABLED = 14006,
        ERROR_SXS_KEY_NOT_FOUND = 14007,
        ERROR_SXS_VERSION_CONFLICT = 14008,
        ERROR_SXS_WRONG_SECTION_TYPE = 14009,
        ERROR_SXS_THREAD_QUERIES_DISABLED = 14010,
        ERROR_SXS_PROCESS_DEFAULT_ALREADY_SET = 14011,
        ERROR_SXS_UNKNOWN_ENCODING_GROUP = 14012,
        ERROR_SXS_UNKNOWN_ENCODING = 14013,
        ERROR_SXS_INVALID_XML_NAMESPACE_URI = 14014,
        ERROR_SXS_ROOT_MANIFEST_DEPENDENCY_NOT_INSTALLED = 14015,
        ERROR_SXS_LEAF_MANIFEST_DEPENDENCY_NOT_INSTALLED = 14016,
        ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE = 14017,
        ERROR_SXS_MANIFEST_MISSING_REQUIRED_DEFAULT_NAMESPACE = 14018,
        ERROR_SXS_MANIFEST_INVALID_REQUIRED_DEFAULT_NAMESPACE = 14019,
        ERROR_SXS_PRIVATE_MANIFEST_CROSS_PATH_WITH_REPARSE_POINT = 14020,
        ERROR_SXS_DUPLICATE_DLL_NAME = 14021,
        ERROR_SXS_DUPLICATE_WINDOWCLASS_NAME = 14022,
        ERROR_SXS_DUPLICATE_CLSID = 14023,
        ERROR_SXS_DUPLICATE_IID = 14024,
        ERROR_SXS_DUPLICATE_TLBID = 14025,
        ERROR_SXS_DUPLICATE_PROGID = 14026,
        ERROR_SXS_DUPLICATE_ASSEMBLY_NAME = 14027,
        ERROR_SXS_FILE_HASH_MISMATCH = 14028,
        ERROR_SXS_POLICY_PARSE_ERROR = 14029,
        ERROR_SXS_XML_E_MISSINGQUOTE = 14030,
        ERROR_SXS_XML_E_COMMENTSYNTAX = 14031,
        ERROR_SXS_XML_E_BADSTARTNAMECHAR = 14032,
        ERROR_SXS_XML_E_BADNAMECHAR = 14033,
        ERROR_SXS_XML_E_BADCHARINSTRING = 14034,
        ERROR_SXS_XML_E_XMLDECLSYNTAX = 14035,
        ERROR_SXS_XML_E_BADCHARDATA = 14036,
        ERROR_SXS_XML_E_MISSINGWHITESPACE = 14037,
        ERROR_SXS_XML_E_EXPECTINGTAGEND = 14038,
        ERROR_SXS_XML_E_MISSINGSEMICOLON = 14039,
        ERROR_SXS_XML_E_UNBALANCEDPAREN = 14040,
        ERROR_SXS_XML_E_INTERNALERROR = 14041,
        ERROR_SXS_XML_E_UNEXPECTED_WHITESPACE = 14042,
        ERROR_SXS_XML_E_INCOMPLETE_ENCODING = 14043,
        ERROR_SXS_XML_E_MISSING_PAREN = 14044,
        ERROR_SXS_XML_E_EXPECTINGCLOSEQUOTE = 14045,
        ERROR_SXS_XML_E_MULTIPLE_COLONS = 14046,
        ERROR_SXS_XML_E_INVALID_DECIMAL = 14047,
        ERROR_SXS_XML_E_INVALID_HEXIDECIMAL = 14048,
        ERROR_SXS_XML_E_INVALID_UNICODE = 14049,
        ERROR_SXS_XML_E_WHITESPACEORQUESTIONMARK = 14050,
        ERROR_SXS_XML_E_UNEXPECTEDENDTAG = 14051,
        ERROR_SXS_XML_E_UNCLOSEDTAG = 14052,
        ERROR_SXS_XML_E_DUPLICATEATTRIBUTE = 14053,
        ERROR_SXS_XML_E_MULTIPLEROOTS = 14054,
        ERROR_SXS_XML_E_INVALIDATROOTLEVEL = 14055,
        ERROR_SXS_XML_E_BADXMLDECL = 14056,
        ERROR_SXS_XML_E_MISSINGROOT = 14057,
        ERROR_SXS_XML_E_UNEXPECTEDEOF = 14058,
        ERROR_SXS_XML_E_BADPEREFINSUBSET = 14059,
        ERROR_SXS_XML_E_UNCLOSEDSTARTTAG = 14060,
        ERROR_SXS_XML_E_UNCLOSEDENDTAG = 14061,
        ERROR_SXS_XML_E_UNCLOSEDSTRING = 14062,
        ERROR_SXS_XML_E_UNCLOSEDCOMMENT = 14063,
        ERROR_SXS_XML_E_UNCLOSEDDECL = 14064,
        ERROR_SXS_XML_E_UNCLOSEDCDATA = 14065,
        ERROR_SXS_XML_E_RESERVEDNAMESPACE = 14066,
        ERROR_SXS_XML_E_INVALIDENCODING = 14067,
        ERROR_SXS_XML_E_INVALIDSWITCH = 14068,
        ERROR_SXS_XML_E_BADXMLCASE = 14069,
        ERROR_SXS_XML_E_INVALID_STANDALONE = 14070,
        ERROR_SXS_XML_E_UNEXPECTED_STANDALONE = 14071,
        ERROR_SXS_XML_E_INVALID_VERSION = 14072,
        ERROR_SXS_XML_E_MISSINGEQUALS = 14073,
        ERROR_SXS_PROTECTION_RECOVERY_FAILED = 14074,
        ERROR_SXS_PROTECTION_PUBLIC_KEY_TOO_SHORT = 14075,
        ERROR_SXS_PROTECTION_CATALOG_NOT_VALID = 14076,
        ERROR_SXS_UNTRANSLATABLE_HRESULT = 14077,
        ERROR_SXS_PROTECTION_CATALOG_FILE_MISSING = 14078,
        ERROR_SXS_MISSING_ASSEMBLY_IDENTITY_ATTRIBUTE = 14079,
        ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME = 14080
    }
}
