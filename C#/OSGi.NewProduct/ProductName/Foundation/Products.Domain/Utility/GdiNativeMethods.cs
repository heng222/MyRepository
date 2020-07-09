/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2017/7/27 14:53:25 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2017 ��˾���ƣ���������Ȩ����
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
        /// ��ָ����Control���ֱ��浽�ļ��С�
        /// </summary>
        /// <param name="screen">��Ҫ�����Control��</param>
        /// <param name="fileName">�ļ�·�����ļ����ơ�</param>
        public static void PrintScreenToFile(Control screen, string fileName)
        {
            Graphics gcScreen = null, gcBitmap = null;
            Bitmap bitmap = null;

            try
            {
                // ��õ�ǰ��Ļ�Ĵ�С 
                var rect = Screen.GetWorkingArea(screen);

                // ����һ���Ե�ǰ��ĻΪģ���ͼ�� 
                gcScreen = screen.CreateGraphics();

                // ��������Ļ��СΪ��׼��λͼ 
                bitmap = new Bitmap(rect.Width, rect.Height, gcScreen);
                gcBitmap = Graphics.FromImage(bitmap);

                // ���ô�API������ʵ����Ļ���� 
                Gdi32.BitBlt(gcBitmap.GetHdc(), 0, 0, rect.Width, rect.Height, gcScreen.GetHdc(), 0, 0, 0xCC0020); // #define SRCCOPY 0xCC0020

                // ���� 
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
