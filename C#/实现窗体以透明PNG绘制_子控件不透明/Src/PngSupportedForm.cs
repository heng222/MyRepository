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

namespace CoolImageDlg
{
    /// <summary>
    /// 支持PNG图片为背景的窗体。
    /// </summary>
    public class PngSupportedForm : Form
    {
        #region "Field"
        private string m_WndClsName = Guid.NewGuid().ToString("N");
        private IntPtr m_FakeWndHandle;
        private WndProcDelegate m_DefWndProcDelegate;
        private WndProcDelegate m_CtrlWndProcDelegate;
        private bool m_bIsRefreshing = false;
        private Dictionary<IntPtr, IntPtr> m_WndProcMap = new Dictionary<IntPtr, IntPtr>();
        #endregion


        #region "Properties"
        /// <summary>
        /// 设置背景图像
        /// </summary>
        [Category("Appearance")]
        [Description("设置背景图像")]
        public Image BackgroundPng { get; set; }
        #endregion


        #region "override methods"
        /// <summary>
        /// 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            if (BackgroundPng == null)  return;

            base.AllowTransparency = true;
            base.Opacity = 0.01;//这个函数控制实体窗口的透明度如果设置程0.00的话窗口将不能移动
            base.FormBorderStyle = FormBorderStyle.None;
            base.Width = BackgroundPng.Width;
            base.Height = BackgroundPng.Height;

            this.Move += this.OnDlgMove;
            this.FormClosed += this.OnDlgClosed;

            m_DefWndProcDelegate = User32.DefWindowProc;
            m_CtrlWndProcDelegate = this.CtrlWndProc;
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
            User32.ShowWindow(m_FakeWndHandle
                , (int)(this.Visible ? WindowShowStyle.Show : WindowShowStyle.Hide));
        }
        #endregion

        #region "Private methods"
        private void CreateFakeWnd()
        {
            var wndClsEx = new WNDCLASSEX();
            wndClsEx.Init();
            wndClsEx.style = WndClassType.CS_VREDRAW | WndClassType.CS_HREDRAW;
            wndClsEx.lpfnWndProc = m_DefWndProcDelegate;
            wndClsEx.cbClsExtra = 0;
            wndClsEx.cbWndExtra = 0;
            wndClsEx.hInstance = Kernel32.GetModuleHandle(null);
            wndClsEx.hIcon = IntPtr.Zero;
            wndClsEx.hIconSm = IntPtr.Zero;
            wndClsEx.hCursor = IntPtr.Zero;
            wndClsEx.hbrBackground = IntPtr.Zero;
            wndClsEx.lpszClassName = m_WndClsName;
            wndClsEx.lpszMenuName = null;

            bool success = User32.RegisterClassEx(ref wndClsEx) != 0;

            Debug.Assert(success, "RegisterWndClass failed.");

            var dwExStyle = ExtendedWndStyle.WS_EX_LAYERED |
                ExtendedWndStyle.WS_EX_TRANSPARENT |
                ExtendedWndStyle.WS_EX_NOACTIVATE |
                ExtendedWndStyle.WS_EX_LEFT;

            var dwStyle = WndStyle.WS_VISIBLE | WndStyle.WS_OVERLAPPED;
            
            m_FakeWndHandle = User32.CreateWindowEx(dwExStyle
                , m_WndClsName
                , null
                , dwStyle
                , this.Left, this.Top
                , BackgroundPng.Width, BackgroundPng.Height
                , this.Handle
                , IntPtr.Zero
                , Kernel32.GetModuleHandle(null)
                , IntPtr.Zero);
            Debug.Assert(User32.IsWindow(m_FakeWndHandle), "CreateWindowEx failed.");
        }

        private void DestroyFakeWnd()
        {
            if (m_FakeWndHandle != IntPtr.Zero)
            {
                User32.DestroyWindow(m_FakeWndHandle);
                m_FakeWndHandle = IntPtr.Zero;

                User32.UnregisterClass(m_WndClsName, Kernel32.GetModuleHandle(null));
            }
        }

        private void RefreshFakeWnd()
        {
            if (m_bIsRefreshing)
                return;

            if (!User32.IsWindow(m_FakeWndHandle))
                return;

            m_bIsRefreshing = true;
            POINT ptSrc = new POINT(0, 0);
            POINT ptWinPos = new POINT(this.Left, this.Top);
            byte biAlpha = 0xFF;
            BLENDFUNCTION stBlend = new BLENDFUNCTION(BlendOp.AC_SRC_OVER, 0, biAlpha, BlendOp.AC_SRC_ALPHA);

            IntPtr hDC = User32.GetDC(m_FakeWndHandle);
            if (hDC == IntPtr.Zero)
            {
                m_bIsRefreshing = false;
                Debug.Assert(false, "GetDC failed.");
                return;
            }

            IntPtr hdcMemory = Gdi32.CreateCompatibleDC(hDC);

            int nBytesPerLine = ((BackgroundPng.Width * 32 + 31) & (~31)) >> 3;
            BITMAPINFOHEADER stBmpInfoHeader = new BITMAPINFOHEADER();
            stBmpInfoHeader.Init();
            stBmpInfoHeader.biWidth = BackgroundPng.Width;
            stBmpInfoHeader.biHeight = BackgroundPng.Height;
            stBmpInfoHeader.biPlanes = 1;
            stBmpInfoHeader.biBitCount = 32;
            stBmpInfoHeader.biCompression = CompressionType.BI_RGB;
            stBmpInfoHeader.biClrUsed = 0;
            stBmpInfoHeader.biSizeImage = (uint)(nBytesPerLine * BackgroundPng.Height);

            IntPtr pvBits = IntPtr.Zero;
            IntPtr hbmpMem = Gdi32.CreateDIBSection(hDC
                , ref stBmpInfoHeader
                , DIBColorTableIdentifier.DIB_RGB_COLORS
                , out pvBits
                , IntPtr.Zero
                , 0
                );
            Debug.Assert(hbmpMem != IntPtr.Zero, "CreateDIBSection failed.");

            if (hbmpMem != null)
            {
                IntPtr hbmpOld = Gdi32.SelectObject(hdcMemory, hbmpMem);

                Graphics graphic = Graphics.FromHdcInternal(hdcMemory);

                graphic.DrawImage(BackgroundPng, 0, 0, BackgroundPng.Width, BackgroundPng.Height);

                foreach (Control ctrl in this.Controls)
                {
                    if (!ctrl.Visible)
                        continue;

                    using (Bitmap bmp = new Bitmap(ctrl.Width, ctrl.Height))
                    {
                        Rectangle rect = new Rectangle(0, 0, ctrl.Width, ctrl.Height);
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

                var szWin = new SIZE(BackgroundPng.Width, BackgroundPng.Height);
                User32.UpdateLayeredWindow(m_FakeWndHandle, hDC, ref ptWinPos, ref szWin, hdcMemory, ref ptSrc, 0, ref stBlend, UpdateLayerWindowParameter.ULW_ALPHA);

                graphic.Dispose();
                Gdi32.SelectObject(hbmpMem, hbmpOld);
                Gdi32.DeleteObject(hbmpMem);
            }

            Gdi32.DeleteDC(hdcMemory);
            Gdi32.DeleteDC(hDC);

            m_bIsRefreshing = false;
        }

        private void HookChildControl(Control ctrl)
        {
            if (User32.IsWindow(ctrl.Handle))
            {
                m_WndProcMap[ctrl.Handle] = User32.GetWindowLongPtr(ctrl.Handle, WindowsLong.GWL_WNDPROC);

                User32.SetWindowLongPtr(ctrl.Handle, WindowsLong.GWL_WNDPROC, Marshal.GetFunctionPointerForDelegate(m_CtrlWndProcDelegate));
            }

            if (!ctrl.HasChildren)  return;

            foreach (Control child in ctrl.Controls)
            {
                HookChildControl(child);
            }
        }

        private IntPtr CtrlWndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)
        {
            if (!m_WndProcMap.ContainsKey(hWnd))
                return m_DefWndProcDelegate(hWnd, msg, wParam, lParam);

            IntPtr nRet = User32.CallWindowProc(m_WndProcMap[hWnd], hWnd, msg, wParam, lParam);

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
            BackgroundPng.Dispose();
            BackgroundPng = null;
        }

        private void OnDlgMove(object sender, EventArgs e)
        {
            if (!User32.IsWindow(m_FakeWndHandle)) return;

            User32.MoveWindow(m_FakeWndHandle, this.Left, this.Top, this.Width, this.Height, false);

            RefreshFakeWnd();
        }
        #endregion

    }
}
