using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmFontZoomAPI : Form
    {
        public frmFontZoomAPI()
        {
            InitializeComponent();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            #region memo
            //Form1.ActiveForm.Handle
            //e.Graphics.GetHdc();
            
            //Brush brush = new SolidBrush(Color.Black);
            //string _durationTxt = "A";
            ////Font font = new Font("Fixedsys", 10.0f, FontStyle.Regular, GraphicsUnit.Pixel);
            //Font font = new Font("PL 07 Donna", 6.0f, FontStyle.Regular, GraphicsUnit.Point);
            ////e.Graphics.CompositingQuality = CompositingQuality.Invalid;
            ////e.Graphics.ScaleTransform(1000, 1000);

            ////e.Graphics.SmoothingMode = SmoothingMode.None;
            ////e.Graphics.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixelGridFit;
            ////e.Graphics.
            ////e.Graphics.DrawString(_durationTxt, font, brush, 0, 0);
            ////e.Graphics.DrawImage(
            ////g.DrawImage(_image, destBounds, imageBounds, GraphicsUnit.Pixel);
            ////Bitmap bitmap = new Bitmap(width, height);   
            ////global

            
            

            ////Image image = new Bitmap(39,41);
            //Image image =  Image.FromFile("c:\\a111.bmp");
            
            ////Graphics g = Graphics.FromImage(image);
            ////g.CompositingQuality = CompositingQuality.HighQuality;
            ////g.SmoothingMode = SmoothingMode.AntiAlias;
            ////g.DrawString(_durationTxt, font, brush, 0, 0);
            ////e.Graphics.CompositingQuality= CompositingQuality.HighQuality;
            ////e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            //////e.Graphics.PageScale = 50f;
            ////e.Graphics.ScaleTransform(20f, 20f);
            ////RectangleF imageBounds = new RectangleF(0, 0, image.Width * 50f, image.Height * 50f);
            ////e.Graphics.DrawImage(image, imageBounds);
            
            
            //e.Graphics.DrawImage(image, 0, 0);
            
            ////RectangleF imageBounds = RectangleF.Empty;
            ////imageBounds = new RectangleF(0, 0, width, height);
            ////e.Graphics.DrawImage(image, 0f, 0f);

            //CDC* pdc = wnd->GetDC();

            //Brush brush = new SolidBrush(Color.Black);
            //string _durationTxt = "A";
                       

            //Font font = new Font("Fixedsys", 6.0f, FontStyle.Regular, GraphicsUnit.Pixel);

            //Image image = new Bitmap(20, 20);
            //e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;
            //Graphics g = Graphics.FromImage(image);
            
            
            ////g.DrawString(
            ////g.DrawString(_durationTxt, font, brush, 0, 0);
            //RectangleF sourceBounds = new RectangleF(0f, 0f, 100f, 100f);
            //e.Graphics.DrawString(_durationTxt, font, brush, sourceBounds);

            

            //RectangleF sourceBounds = new RectangleF(0f, 0f, 20f, 20f);
            //RectangleF destBounds = new RectangleF(0f, 0f, 20 * 10f, 20 * 10f);

            //e.Graphics.DrawImage(image, destBounds, sourceBounds,GraphicsUnit.Pixel);

            //e.Graphics.DrawString(
            //e.Graphics.ScaleTransform(30f, 30f);
            //e.Graphics.DrawImage(image, 0f, 0f);
            #endregion

            //Font font = new Font("Fixedsys", 10.0f, FontStyle.Regular, GraphicsUnit.Pixel);
            //Fonts.DrawText(e.Graphics, font, "A", new Point(0, 0), false, FontSmoothing.Sharp);
            DrawFunction(e);
            AutoSize();
        }


        private void DrawFunction(PaintEventArgs e)
        {
            //Define font
            //Define string
            string drawText = "ABC";
            //Define XY
            Point pt = new Point(0, 0);
            //Define anti
            bool antiAliasing = false;
            //Define Smoothing
            FontSmoothing smoothType = FontSmoothing.Sharp;

            //Fonts.DrawText(e.Graphics, font, "A", new Point(0, 0), false, FontSmoothing.Sharp);

            // Panel handle
            IntPtr destDC = IntPtr.Zero;
            IntPtr hOldObject = IntPtr.Zero;
            IntPtr dcMemery = IntPtr.Zero;   
            IntPtr pbitmap = IntPtr.Zero;
            //IntPtr pTemp = IntPtr.Zero;
            Graphics g = e.Graphics;
            NativeStructs.RECT destBounds = new NativeStructs.RECT();
            destBounds.left = 0;
            destBounds.top = 0;
            destBounds.bottom = 20;
            destBounds.right = 20;
            
            destDC = g.GetHdc();

            //pTemp = SafeNativeMethods.CreateCompatibleDC(destDC);
            dcMemery = SafeNativeMethods.CreateCompatibleDC(destDC);

            // Font
            Font font = new Font("宋体", 10.0f, FontStyle.Regular, GraphicsUnit.Pixel);
            IntPtr hFont = IntPtr.Zero;
            hFont = Fonts.CreateFontObject(font, antiAliasing);
            SafeNativeMethods.SelectObject(dcMemery, hFont);


            pbitmap = SafeNativeMethods.CreateCompatibleBitmap(destDC, 20, 20);

            SafeNativeMethods.SelectObject(dcMemery, pbitmap);
            
            NativeStructs.RGBQUAD rgb = new NativeStructs.RGBQUAD();
            rgb.rgbBlue = 255;

            NativeStructs.RGBQUAD rgbBG = new NativeStructs.RGBQUAD();
            rgbBG.rgbBlue = 0;
            rgbBG.rgbRed = 0;
            rgbBG.rgbGreen = 0;

            //Graphics gSource = new Graphics();
            //gSource.
            //IntPtr gPtr = gSource.GetHdc();
            //gPtr = dcMemery;
            //gSource

            SafeNativeMethods.SetTextColor(dcMemery, rgb);
            SafeNativeMethods.SetBkColor(dcMemery, rgbBG);
            SafeNativeMethods.DrawTextW(dcMemery, drawText, drawText.Length, ref destBounds, NativeConstants.DT_CENTER);

            //SafeNativeMethods.TransparentBlt(pTemp, destBounds.left, destBounds.top, destBounds.right, destBounds.bottom, dcMemery, destBounds.left, destBounds.top, destBounds.right, destBounds.bottom, 0);

            SafeNativeMethods.StretchBlt(destDC, 0, 0, 20 * 10, 20 * 10, dcMemery, 0, 0, 20, 20, NativeConstants.SRCCOPY);

            //dcMemery.

            //pbitmap = bit.GetHbitmap();

            //dcMemery = SafeNativeMethods.CreateCompatibleBitmap(pdc, 20, 20);


            //SafeNativeMethods.

            //hFont = CreateFontObject(font, antiAliasing);
            //hOldObject = SafeNativeMethods.SelectObject(pdc, hFont);

            

            //SafeNativeMethods.CreateCompatibleDC(pdc);
            //uint result1 = SafeNativeMethods.StretchBlt(
            //    0,
            //    0,
            //    20,
            //    20,
            //    pdc,
            //    0,
            //    0,
            //    20 * 1000,
            //    20 * 1000,
            //    NativeConstants.SRCCOPY);

        }

        #region test auto size 
        private void AutoSize()
        {
            FontFamily fontFamily = new FontFamily("Arial");
            string outtxt= "abcdefghijklmnopqrst";
            //创建一个大小为16像素的Aria字体
            Font font = new Font(fontFamily, 16, FontStyle.Regular, GraphicsUnit.Pixel);
            int a = outtxt.Length * font.Height;
            textBox1.Text = a.ToString();
            label1.Font = font;
            label1.Text = outtxt;
            //textBox2.Text = label1.Text.ToString();

        }
        #endregion

        #region Strech text by API
        /// <summary>
        /// Function: Strech text
        /// Author  : Jerry Xu
        /// Date    : 2008-8-2
        /// </summary>
        /// <param name="g">Graphics:destination graphics</param>
        /// <param name="drawText">string:destination text</param>
        /// <param name="font">Font</param>
        /// <param name="sourceBounds">source rectangle</param>
        /// <param name="antiAliasing">bool</param>
        private static void StrechText(Graphics g, string drawText, Font font, Color foreColor, Color backColor, Rectangle sourceBounds, float zoom, bool antiAliasing)
        {
            //Define InPtr(point)
            IntPtr destDC = IntPtr.Zero;
            IntPtr dcMemery = IntPtr.Zero;
            IntPtr pbitmap = IntPtr.Zero;
            IntPtr hFont = IntPtr.Zero;
            //Define destination bound
            Rectangle destBounds;

            try
            {
                //Destionation DC
                destDC = g.GetHdc();

                //Temp DC
                dcMemery = SafeNativeMethods.CreateCompatibleDC(destDC);

                //Init font
                font = new Font("宋体", 14.0f, FontStyle.Regular, GraphicsUnit.Pixel);

                //Set font to temp DC
                hFont = font.ToHfont();
                SafeNativeMethods.SelectObject(dcMemery, hFont);

                //Create image and get image DC
                pbitmap = SafeNativeMethods.CreateCompatibleBitmap(destDC, sourceBounds.Width, sourceBounds.Height);

                //Set image DC to temp DC
                SafeNativeMethods.SelectObject(dcMemery, pbitmap);

                //Set fore color
                NativeStructs.RGBQUAD rgb = new NativeStructs.RGBQUAD();
                rgb.rgbBlue = foreColor.B;
                rgb.rgbRed = foreColor.R;
                rgb.rgbGreen = foreColor.G;
                
                SafeNativeMethods.SetTextColor(dcMemery, rgb);

                //Set back color
                NativeStructs.RGBQUAD rgbBG = new NativeStructs.RGBQUAD();
                rgbBG.rgbBlue = backColor.B;
                rgbBG.rgbRed = backColor.R;
                rgbBG.rgbGreen = backColor.G;
                
                SafeNativeMethods.SetBkColor(dcMemery, rgbBG);

                //Draw text to temp Rectangle
                NativeStructs.RECT rect = ConvertRectangleToRECT(sourceBounds);

                SafeNativeMethods.DrawTextW(dcMemery, drawText, drawText.Length, ref rect, NativeConstants.DT_CENTER);

                //Zoom Rectangle
                destBounds = new Rectangle(sourceBounds.X, sourceBounds.Y, (int)(sourceBounds.Width * zoom), (int)(sourceBounds.Height*zoom));

                //Draw temp Rectangle to zoom Rectangle
                SafeNativeMethods.StretchBlt(destDC, destBounds.X, destBounds.Y, destBounds.Width, destBounds.Height, dcMemery, sourceBounds.X, sourceBounds.Y, sourceBounds.Width, sourceBounds.Height, NativeConstants.SRCCOPY);

            }
            catch
            {
            }
            finally
            {
                //Disponse resource
                if (pbitmap != IntPtr.Zero)
                {
                    SafeNativeMethods.SelectObject(dcMemery, pbitmap);
                    pbitmap = IntPtr.Zero;
                }

                if (dcMemery != IntPtr.Zero)
                {
                    SafeNativeMethods.SelectObject(destDC, dcMemery);
                    dcMemery = IntPtr.Zero;
                }

                if (hFont != IntPtr.Zero)
                {
                    SafeNativeMethods.DeleteObject(hFont);
                    hFont = IntPtr.Zero;
                }

                if (destDC != IntPtr.Zero)
                {
                    g.ReleaseHdc(destDC);
                    destDC = IntPtr.Zero;
                }
            }
        }
        #endregion

        #region Convert Rectangle to NativeStructs.RECT
        /// <summary>
        /// Function: Convert Rectangle to NativeStructs.RECT
        /// Author  : Jerry Xu
        /// Date    : 2008-8-2
        /// </summary>
        /// <param name="source">Rectangle</param>
        /// <returns>NativeStructs.RECT</returns>
        private static NativeStructs.RECT ConvertRectangleToRECT(Rectangle source)
        {
            NativeStructs.RECT target = new NativeStructs.RECT();
            target.left = source.Left;
            target.top = source.Top;
            target.bottom = source.Right;
            target.right = source.Bottom;
            return target;
        }
        #endregion
    }
}