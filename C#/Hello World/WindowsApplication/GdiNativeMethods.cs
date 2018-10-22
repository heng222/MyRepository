using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication
{
    /// <summary>
    /// Gdi Namtive methods
    /// </summary>
    public static class GdiNativeMethods
    {
        #region "Public methods"
        //声明一个API函数 
        [DllImport("gdi32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool BitBlt(
            IntPtr hdcDest, int nXDest, int nYDest,
            int nWidth, int nHeight,
            IntPtr hdcSrc, int nXSrc, int nYSrc,
            Int32 dwRop
        );

        /// <summary>
        /// 将指定的Control布局保存到文件中。
        /// </summary>
        /// <param name="screen">将要保存的Control。</param>
        /// <param name="fileName">文件路径及文件名称。</param>
        public static void PrintScreenToFile(Control screen, string fileName)
        {
            //Graphics gcScreen = null, gcBitmap = null;
            //Bitmap bitmap = null;

            //try
            //{
            //    // 获得当前屏幕的大小 
            //    var rect = Screen.GetWorkingArea(screen);

            //    // 创建一个以当前屏幕为模板的图象 
            //    gcScreen = screen.CreateGraphics();

            //    // 创建以屏幕大小为标准的位图 
            //    bitmap = new Bitmap(rect.Width, rect.Height, gcScreen);
            //    gcBitmap = Graphics.FromImage(bitmap);

            //    // 调用此API函数，实现屏幕捕获 
            //    BitBlt(gcBitmap.GetHdc(), 0, 0, rect.Width, rect.Height, gcScreen.GetHdc(), 0, 0, 0xCC0020); // #define SRCCOPY 0xCC0020

            //    // 保存 
            //    bitmap.Save(fileName, ImageFormat.Png);
            //}
            //catch (System.Exception)
            //{
            //    throw;
            //}
            //finally
            //{
            //    if (gcScreen != null) gcScreen.Dispose();
            //    if (gcBitmap != null) gcBitmap.Dispose();
            //    if (bitmap != null) bitmap.Dispose();
            //}

            // 实例化一个和窗体一样大的bitmap            
            using (var bitmap = new Bitmap(screen.Width, screen.Height))
            {
                using (var gc = Graphics.FromImage(bitmap))
                {
                    gc.CompositingQuality = CompositingQuality.HighQuality; // 质量设为最高
                    gc.CopyFromScreen(screen.Left, screen.Top, 0, 0, new Size(screen.Width, screen.Height)); // 保存整个窗体为图片
                    bitmap.Save(fileName);
                }
            }
        }
        #endregion

    }
    
}
