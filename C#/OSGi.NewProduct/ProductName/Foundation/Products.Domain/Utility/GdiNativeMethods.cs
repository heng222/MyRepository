/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：产品名称
//
// 创 建 人：heng222_z
// 创建日期：2017/7/27 14:53:25 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2017 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

using Acl.Win32API;

namespace Products.Domain.Utility
{
    /// <summary>
    /// Gdi Namtive methods
    /// </summary>
    public static class GdiNativeMethods
    {
        #region "Public methods"
        /// <summary>
        /// 将指定的Control布局保存到文件中。
        /// </summary>
        /// <param name="screen">将要保存的Control。</param>
        /// <param name="fileName">文件路径及文件名称。</param>
        public static void PrintScreenToFile(Control screen, string fileName)
        {
            Graphics gcScreen = null, gcBitmap = null;
            Bitmap bitmap = null;

            try
            {
                // 获得当前屏幕的大小 
                var rect = Screen.GetWorkingArea(screen);

                // 创建一个以当前屏幕为模板的图象 
                gcScreen = screen.CreateGraphics();

                // 创建以屏幕大小为标准的位图 
                bitmap = new Bitmap(rect.Width, rect.Height, gcScreen);
                gcBitmap = Graphics.FromImage(bitmap);

                // 调用此API函数，实现屏幕捕获 
                Gdi32.BitBlt(gcBitmap.GetHdc(), 0, 0, rect.Width, rect.Height, gcScreen.GetHdc(), 0, 0, 0xCC0020); // #define SRCCOPY 0xCC0020

                // 保存 
                bitmap.Save(fileName, ImageFormat.Png);
            }
            catch (System.Exception)
            {
                throw;
            }
            finally
            {
                if (gcScreen != null) gcScreen.Dispose();
                if (gcBitmap != null) gcBitmap.Dispose();
                if (bitmap != null) bitmap.Dispose();
            }
        }
        #endregion

    }
}
