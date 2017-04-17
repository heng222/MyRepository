using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Text;
//using FONTTOBMPLib;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmTextShadow : Form
    {
        public frmTextShadow()
        {
            InitializeComponent();
            
        }

        private void SetTextShadow()
        {
            string text = "ABC";
            Graphics graphics = this.CreateGraphics();
            graphics.Clear(Color.White);
            //���ı�ʹ��ȥ��ݵı�Ե����
            graphics.TextRenderingHint = TextRenderingHint.AntiAlias;

            FontFamily fontFamily = new FontFamily("Arial");
            Font font = new Font(fontFamily, 30, FontStyle.Bold, GraphicsUnit.Pixel);

            //�ı������
            RectangleF textout = new RectangleF(font.Height,
                this.ClientSize.Height / 2, this.ClientSize.Width, this.ClientSize.Height);

            Rectangle rect = new Rectangle();
            rect.X = 12;
            rect.Y = 12;
            rect.Width = (int)textout.Width;
            rect.Height = (int)textout.Height;
            Rectangle rect1 = new Rectangle();
            rect1 = rect;
            rect1.X = 27;
            rect1.Y = 27;

            StrechText(graphics, text, font, Color.Red, Color.Transparent, rect, 1f, true);
            StrechText(graphics, text, font, Color.Green, Color.Transparent, rect1, 1f, true);

            //��������ͬ��λ�û����ı����γ���Ӱ
            //solidBrush��ɫ��͸����Ϊ100������
            //SolidBrush solidBrush = new SolidBrush(Color.FromArgb(100, Color.Black));
            //SolidBrush redBrush = new SolidBrush(Color.Red);
            //graphics.DrawString("��Ӱ��", font, solidBrush,
            //    new PointF(27.0f, 27.0f));
            //graphics.DrawString("��Ӱ��", font, redBrush,
            //    new PointF(12.0f, 20.0f));
        }

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
            //IntPtr destDC1 = IntPtr.Zero;
            IntPtr dcMemery = IntPtr.Zero;
            IntPtr pbitmap = IntPtr.Zero;
            IntPtr hFont = IntPtr.Zero;
            //Define destination bound
            Rectangle destBounds;

            try
            {
                //Destionation DC
                destDC = g.GetHdc();

                //destDC1 = g.GetHdc();

                //Temp DC
                dcMemery = SafeNativeMethods.CreateCompatibleDC(destDC);

                //Init font
                //font = new Font("����", 14.0f, FontStyle.Regular, GraphicsUnit.Pixel);

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
                destBounds = new Rectangle(sourceBounds.X, sourceBounds.Y, (int)(sourceBounds.Width * zoom), (int)(sourceBounds.Height * zoom));

                //Draw temp Rectangle to zoom Rectangle
                SafeNativeMethods.StretchBlt(destDC, destBounds.X, destBounds.Y, destBounds.Width, destBounds.Height, dcMemery, sourceBounds.X, sourceBounds.Y, sourceBounds.Width, sourceBounds.Height, NativeConstants.SRCCOPY);

                //SafeNativeMethods.TransparentBlt(destDC1, destBounds.X, destBounds.Y, destBounds.Width, destBounds.Height, destDC, sourceBounds.X, sourceBounds.Y, sourceBounds.Width, sourceBounds.Height, rgbBG);
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

                //if (destDC1 != IntPtr.Zero)
                //{
                //    g.ReleaseHdc(destDC1);
                //    destDC1 = IntPtr.Zero;
                //}
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

        private void frmTextShadow_Paint(object sender, PaintEventArgs e)
        {
            SetTextShadow();
            //FONTTOBMPLib.FontBmpGenClass a = new FontBmpGenClass();
            
            
            
        }
    }
}