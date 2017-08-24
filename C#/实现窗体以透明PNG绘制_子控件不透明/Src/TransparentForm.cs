using System;
using System.IO;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Windows.Forms;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace CoolImageDlg
{
    /// <summary>
    /// 支持PNG图片为背景的透明窗体。
    /// </summary>
    public class TransparentForm : Form
    {
        #region "Field"
        private string _wndClassName = Guid.NewGuid().ToString("N");

        private IntPtr _fakeWindowHandle;

        private WndProcDelegate _defWndProcDelegate;
        private WndProcDelegate _ctrlWndProcDelegate;

        /// <summary>
        /// 是否正在重绘中。
        /// </summary>
        private bool _refreshing = false;

        private Dictionary<IntPtr, IntPtr> _wndProcMap = new Dictionary<IntPtr, IntPtr>();
        #endregion


        #region "Properties"
        //public Image BackgroundImage { get; set; }
        #endregion


        #region "override methods"
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            if (BackgroundImage == null)  return;

            base.AllowTransparency = true;
            base.Opacity = 0.01; // 透明度如果设置为0的话窗口将不能移动
            base.FormBorderStyle = FormBorderStyle.None;
            base.Width = this.GetWidth();
            base.Height = this.GetHeight();

            this.Move += this.OnDlgMove;
            this.FormClosed += this.OnDlgClosed;

            _defWndProcDelegate = User32.DefWindowProc;
            _ctrlWndProcDelegate = this.CtrlWndProc;
            HookChildControl(this);

            CreateFakeWnd();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="msg"></param>
        protected override void WndProc(ref Message msg)
        {
            // make the window movable by drag on the client area
            if (msg.Msg == ((int)WindowsMessage.WM_LBUTTONDOWN))
            {
                msg.Msg = WindowsMessage.WM_NCLBUTTONDOWN;
                msg.LParam = IntPtr.Zero;
                msg.WParam = new IntPtr((int)MousePositionCodes.HTCAPTION);
            }
            base.WndProc(ref msg);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnVisibleChanged(EventArgs e)
        {
            User32.ShowWindow(_fakeWindowHandle, (int)(this.Visible ? WindowShowStyle.Show : WindowShowStyle.Hide));
        }
        #endregion

        #region "Private methods"

        private int GetWidth() 
        {
            //return this.BackgroundImage2.Width;
            return base.Width;
        }

        private int GetHeight()
        {
            //return this.BackgroundImage2.Height;
            return base.Height;
        }

        private void CreateFakeWnd()
        {
            var wndClsEx = new WNDCLASSEX();
            wndClsEx.Init();
            wndClsEx.style = WndClassType.CS_VREDRAW | WndClassType.CS_HREDRAW;
            wndClsEx.lpfnWndProc = _defWndProcDelegate;
            wndClsEx.cbClsExtra = 0;
            wndClsEx.cbWndExtra = 0;
            wndClsEx.hInstance = Kernel32.GetModuleHandle(null);
            wndClsEx.hIcon = IntPtr.Zero;
            wndClsEx.hIconSm = IntPtr.Zero;
            wndClsEx.hCursor = IntPtr.Zero;
            wndClsEx.hbrBackground = IntPtr.Zero;
            wndClsEx.lpszClassName = _wndClassName;
            wndClsEx.lpszMenuName = null;

            bool success = User32.RegisterClassEx(ref wndClsEx) != 0;

            Debug.Assert(success, "RegisterWndClass failed.");

            var dwExStyle = ExtendedWndStyle.WS_EX_LAYERED | ExtendedWndStyle.WS_EX_TRANSPARENT
                | ExtendedWndStyle.WS_EX_NOACTIVATE | ExtendedWndStyle.WS_EX_LEFT;

            var dwStyle = WndStyle.WS_VISIBLE | WndStyle.WS_OVERLAPPED;

            _fakeWindowHandle = User32.CreateWindowEx(dwExStyle, _wndClassName, null, dwStyle,
                this.Left, this.Top, this.GetWidth(), this.GetHeight()
                , this.Handle, IntPtr.Zero, Kernel32.GetModuleHandle(null), IntPtr.Zero);

            Debug.Assert(User32.IsWindow(_fakeWindowHandle), "CreateWindowEx failed.");
        }

        private void DestroyFakeWnd()
        {
            if (_fakeWindowHandle != IntPtr.Zero)
            {
                User32.DestroyWindow(_fakeWindowHandle);
                _fakeWindowHandle = IntPtr.Zero;

                User32.UnregisterClass(_wndClassName, Kernel32.GetModuleHandle(null));
            }
        }

        private void RefreshFakeWnd()
        {
            if (_refreshing) return;

            if (!User32.IsWindow(_fakeWindowHandle))  return;

            _refreshing = true;
            var ptSrc = new POINT(0, 0);
            var ptWinPos = new POINT(this.Left, this.Top);
            byte biAlpha = 0xFF;
            var stBlend = new BLENDFUNCTION(BlendOp.AC_SRC_OVER, 0, biAlpha, BlendOp.AC_SRC_ALPHA);

            IntPtr hDC = User32.GetDC(_fakeWindowHandle);
            if (hDC == IntPtr.Zero)
            {
                _refreshing = false;
                Debug.Assert(false, "GetDC failed.");
                return;
            }

            IntPtr hdcMemory = Gdi32.CreateCompatibleDC(hDC);

            int nBytesPerLine = ((this.GetWidth() * 32 + 31) & (~31)) >> 3;

            var stBmpInfoHeader = new BITMAPINFOHEADER();
            stBmpInfoHeader.Init();
            stBmpInfoHeader.biWidth = this.GetWidth();
            stBmpInfoHeader.biHeight = this.GetHeight();
            stBmpInfoHeader.biPlanes = 1;
            stBmpInfoHeader.biBitCount = 32;
            stBmpInfoHeader.biCompression = CompressionType.BI_RGB;
            stBmpInfoHeader.biClrUsed = 0;
            stBmpInfoHeader.biSizeImage = (uint)(nBytesPerLine * base.Height);

            IntPtr pvBits = IntPtr.Zero;
            IntPtr hbmpMem = Gdi32.CreateDIBSection(hDC, ref stBmpInfoHeader
                        , DIBColorTableIdentifier.DIB_RGB_COLORS, out pvBits, IntPtr.Zero, 0);
            Debug.Assert(hbmpMem != IntPtr.Zero, "CreateDIBSection failed.");

            if (hbmpMem != null)
            {
                var hbmpOld = Gdi32.SelectObject(hdcMemory, hbmpMem);

                var graphic = Graphics.FromHdcInternal(hdcMemory);

                graphic.DrawImage(this.BackgroundImage, 0, 0, GetWidth(), GetHeight());

                foreach (Control ctrl in this.Controls)
                {
                    if (!ctrl.Visible)  continue;

                    using (var bmp = new Bitmap(ctrl.Width, ctrl.Height))
                    {
                        var rect = new Rectangle(0, 0, ctrl.Width, ctrl.Height);
                        ctrl.DrawToBitmap(bmp, rect);

                        graphic.DrawImage(bmp, ctrl.Left, ctrl.Top, ctrl.Width, ctrl.Height);
                    }
                }

                GUITHREADINFO stGuiThreadInfo = new GUITHREADINFO();
                stGuiThreadInfo.Init();
                if (User32.GetGUIThreadInfo(Kernel32.GetCurrentThreadId(), ref stGuiThreadInfo))
                {
                    if (User32.IsWindow(stGuiThreadInfo.hwndCaret))
                    {
                        int height = stGuiThreadInfo.rcCaret.Bottom - stGuiThreadInfo.rcCaret.Top;
                        POINT ptCaret = new POINT(stGuiThreadInfo.rcCaret.Left, stGuiThreadInfo.rcCaret.Top);

                        User32.ClientToScreen(stGuiThreadInfo.hwndCaret, ref ptCaret);
                        User32.ScreenToClient(this.Handle, ref ptCaret);

                        graphic.DrawLine(new Pen(new SolidBrush(Color.Black)), ptCaret.X, ptCaret.Y, ptCaret.X, ptCaret.Y + height);
                    }
                }

                var szWin = new SIZE(this.GetWidth(), this.GetHeight());
                User32.UpdateLayeredWindow(_fakeWindowHandle, hDC, ref ptWinPos, ref szWin, hdcMemory, ref ptSrc, 0, ref stBlend, UpdateLayerWindowParameter.ULW_ALPHA);

                graphic.Dispose();
                Gdi32.SelectObject(hbmpMem, hbmpOld);
                Gdi32.DeleteObject(hbmpMem);
            }

            Gdi32.DeleteDC(hdcMemory);
            Gdi32.DeleteDC(hDC);

            _refreshing = false;
        }

        private void HookChildControl(Control ctrl)
        {
            if (User32.IsWindow(ctrl.Handle))
            {
                _wndProcMap[ctrl.Handle] = User32.GetWindowLongPtr(ctrl.Handle, WindowsLong.GWL_WNDPROC);

                User32.SetWindowLongPtr(ctrl.Handle, WindowsLong.GWL_WNDPROC, Marshal.GetFunctionPointerForDelegate(_ctrlWndProcDelegate));
            }

            if (!ctrl.HasChildren)  return;

            foreach (Control child in ctrl.Controls)
            {
                HookChildControl(child);
            }
        }

        private IntPtr CtrlWndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)
        {
            if (!_wndProcMap.ContainsKey(hWnd))
                return _defWndProcDelegate(hWnd, msg, wParam, lParam);

            IntPtr nRet = User32.CallWindowProc(_wndProcMap[hWnd], hWnd, msg, wParam, lParam);

            switch (msg)
            {
                case WindowsMessage.WM_PAINT:
                case WindowsMessage.WM_CTLCOLOREDIT:
                case WindowsMessage.WM_CTLCOLORBTN:
                case WindowsMessage.WM_CTLCOLORSTATIC:
                case WindowsMessage.WM_CTLCOLORMSGBOX:
                case WindowsMessage.WM_CTLCOLORDLG:
                case WindowsMessage.WM_CTLCOLORLISTBOX:
                case WindowsMessage.WM_CTLCOLORSCROLLBAR:
                case WindowsMessage.WM_CAPTURECHANGED:
                    RefreshFakeWnd();
                    break;

                default:
                    break;
            }

            return nRet;
        }

        #endregion


        #region "窗体事件处理函数"
        private void OnDlgClosed(object sender, FormClosedEventArgs e)
        {
            DestroyFakeWnd();
        }

        private void OnDlgMove(object sender, EventArgs e)
        {
            if (!User32.IsWindow(_fakeWindowHandle)) return;

            User32.MoveWindow(_fakeWindowHandle, this.Left, this.Top, this.Width, this.Height, false);

            RefreshFakeWnd();
        }
        #endregion

    }
}
