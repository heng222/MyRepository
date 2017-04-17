using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;

using ProWrite.UI.Texts;
using System.Drawing.Text;
using System.Drawing.Imaging;
using System.IO;
using ProWrite.SSL;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmCLIForm : Form
    {
        static TextMgr _FontMgr = new TextMgr();
        List<Image> m_virtualImage = new List<Image>();
        List<Image> m_actualImage = new List<Image>();
        List<String> m_strList = new List<String>();
        //static String m_strText = "Microsoft Developer Studio Workspace File";
        static String m_strText = "Text";
        Point m_ptStart = new Point(10,40);

        
        public frmCLIForm()
        {
            //FontManager.Initialize("C:\\FontPackage.xml");
            // ---------- common attributes -------------------
            _FontMgr.ScaleIndex = 3;
            _FontMgr.SetStyle(true, false);
            _FontMgr.Alignment = Align.CENTER;
            _FontMgr.LineAlignment = Valign.MIDDLE;
            _FontMgr.KernAmount = 1 * _FontMgr.ScaleIndex;
            //_FontMgr.LeadAmount = 5 * _FontMgr.ScaleIndex;
            //_FontMgr.Underline = true;
            //_FontMgr.Bold = true;
            //_FontMgr.Italic = true;
            _FontMgr.BackColor = Color.Transparent;
            _FontMgr.TextColor = Color.White;
            _FontMgr.Text = m_strText;
            //_FontMgr.Text = "Text";
            _FontMgr.SignSize = new Size(1000, 1000);
            _FontMgr.FrameSize = _FontMgr.SignSize;
            _FontMgr.FontHeight = 5 * _FontMgr.ScaleIndex;
			//_FontMgr.FontHeight = 16;
            //_FontMgr.FontName = "PL 07 Danielle";
            _FontMgr.FontName = "Arial";// MS Sans Serif
            //_FontMgr.FontName = FontManager.GetProWriteFonts()[0];
            //_FontMgr.FontName = "PL 07 Sans"; // Trans-Lux Pictorials
            //_FontMgr.FontName = "Trans-Lux Pictorials";// MS Sans Serif
            _FontMgr.ShowGrid = true;

            // 
            InitializeComponent();

            //
            int iWidth = this.ClientSize.Width - m_ptStart.X;
            int iHeight = this.ClientSize.Height - m_ptStart.Y;
            
            // 新的尺寸必须为ScalIndex的整数倍
            iWidth = (iWidth / (int)(_FontMgr.ScaleIndex)) * (int)_FontMgr.ScaleIndex;
            iHeight = (iHeight / (int)_FontMgr.ScaleIndex) * (int)_FontMgr.ScaleIndex;
            _FontMgr.FrameSize = new Size(iWidth, iHeight);
        }



        private void frmCLIForm_SizeChanged(object sender, EventArgs e)
        {
            int iWidth = this.ClientSize.Width - m_ptStart.X;
            int iHeight = this.ClientSize.Height - m_ptStart.Y;

            // 新的尺寸必须为ScalIndex的整数倍
            iWidth = (iWidth /(int)(_FontMgr.ScaleIndex))*(int)_FontMgr.ScaleIndex;
            iHeight = (iHeight / (int)_FontMgr.ScaleIndex)*(int)_FontMgr.ScaleIndex;

            //
            _FontMgr.FrameSize = new Size(iWidth, iHeight);
            //_FontMgr.ScaleIndex = 10f;

            bool bFlag = _FontMgr.GenerateBmps(m_actualImage,m_virtualImage, m_strList);

            if (m_virtualImage.Count > 0)
            {
                DrawFrameImage(m_virtualImage[0]);

                //int i = 1;
                //foreach (Image item in m_imageList)
                //{
                //    item.Save("c:\\" + i.ToString() + ".png", ImageFormat.Png);
                //    i++;
                //}

                int iVHeight = _FontMgr.FontHeight;
                int iAPointHeight = iVHeight / _FontMgr.ScaleIndex;
                int iAPixHeight = _FontMgr.FontHeight / _FontMgr.ScaleIndex;
                //Console.WriteLine("\nActualPointHeight=" + iAPointHeight +
                    //", ActualPixelHeight=" + iAPixHeight);
                //Console.WriteLine(_FontMgr.FontName);

            }
            
        }

        // Non effect
        private void NonEffect_Click(object sender, EventArgs e)
        {

            // ------------- Non-Effect ---------------------------------
            //_FontMgr.BackColor = Color.White;
            _FontMgr.BackColor = Color.Transparent;
            _FontMgr.TextColor = Color.Red;
            _FontMgr.Text = m_strText;
            _FontMgr.CancelTextEffect();

            // 
            bool bFlag = _FontMgr.GenerateBmps(m_actualImage,m_virtualImage, m_strList);
            if (m_virtualImage.Count > 0)
            {
                DrawFrameImage(m_virtualImage[0]);
            }

            int i = 1;
            foreach (Bitmap item in m_actualImage)
            {
                //item.Save("c:\\Actual" + i.ToString() + ".png", ImageFormat.Png);
                
                //
                if (((Color)_FontMgr.BackColor).A == 0)
                {
                    Bitmap gif = ConvertTransparancyGif(item, (Color)_FontMgr.BackColor);
                    gif.Save("c:\\Actual" + i.ToString() + ".gif", ImageFormat.Gif);
                }
                else
                {
                    item.Save("c:\\Actual" + i.ToString() + ".gif", ImageFormat.Gif);
                }

                i++;
            }

            //foreach (String item in m_strList)
            //{
            Console.WriteLine(_FontMgr.FontName);
            Console.WriteLine(_FontMgr.FontFileName+"\n\n");
            //}
        }

        // Shadow effect
        private void button1_Click(object sender, EventArgs e)
        {
            // ------------- Shadow Effect ----------------------------
            _FontMgr.BackColor = Color.White;
            _FontMgr.TextColor = Color.Red;
            _FontMgr.SetShadowAttri(Color.LightGray, 3 * _FontMgr.ScaleIndex, -5 * _FontMgr.ScaleIndex);
            // 
            _FontMgr.GenerateBmps(m_actualImage,m_virtualImage, m_strList);
            if (m_virtualImage.Count > 0)
            {
                DrawFrameImage(m_virtualImage[0]);
                m_actualImage[0].Save("c:\\shadow.png", ImageFormat.Png);
            }


#if false
            // Get ISEFonts
            List<String> fontName = null;

            // 得到字体
            fontName = null;
            fontName = FontManager.GetSystemFonts();
            foreach (string item in fontName)
            {
                Console.WriteLine(item);
            }

            // 得到指定字体的可用显示尺寸
            List<int> fontSize = null;
            fontSize = FontManager.GetSpecifiedFontHeight("System");
            foreach (int item in fontSize)
            {
                Console.WriteLine(item);
            }

#endif

            // 使用GDI+枚举系统的所有字体
#if _ENUM_SYSFONTS_GDIP_
            pictureBox1.Visible = false;
            FontFamily fontFamily = new FontFamily("Arial");
            Font font = new Font(
               fontFamily,
               8,
               FontStyle.Regular,
               GraphicsUnit.Point);
            RectangleF rectF = new RectangleF(10, 10, 500, 500);
            SolidBrush solidBrush = new SolidBrush(Color.Black);

            string familyName;
            string familyList = "";
            FontFamily[] fontFamilies;

            InstalledFontCollection installedFontCollection = new InstalledFontCollection();

            // Get the array of FontFamily objects.
            fontFamilies = installedFontCollection.Families;

            // The loop below creates a large string that is a comma-separated
            // list of all font family names.

            int count = fontFamilies.Length;
            for (int j = 0; j < count; ++j)
            {
                familyName = fontFamilies[j].Name;
                familyList = familyList + familyName;
                familyList = familyList + ",  ";
            }

            // Draw the large string (list of all families) in a rectangle.
            CreateGraphics().DrawString(familyList, font, solidBrush, rectF);
#endif

        }

        // outline
        private void btn_outline_Click(object sender, EventArgs e)
        {
            // ------------- Outline Effect ---------------------------
            _FontMgr.BackColor = Color.Blue;
            _FontMgr.TextColor = Color.Red;
            _FontMgr.SetOutlineAttri(Color.White, (ushort)(0*_FontMgr.ScaleIndex));
            // 
            _FontMgr.GenerateBmps(m_actualImage,m_virtualImage, m_strList);
            if (m_virtualImage.Count > 0)
            {
                DrawFrameImage(m_virtualImage[0]);
            }
        }

        // Draw Image
        public void DrawFrameImage(Image bmpFrame)
        {
            Graphics g = this.CreateGraphics();
            //g.Clear(this.BackColor);
            
            Rectangle destR = new Rectangle(m_ptStart.X, m_ptStart.Y, bmpFrame.Width, bmpFrame.Height);

            if (((Color)(_FontMgr.BackColor)).A==0)
            {
                ImageAttributes imgAttri = new ImageAttributes();
                imgAttri.SetColorKey((Color)_FontMgr.ColorKey, (Color)_FontMgr.ColorKey);
                
                // 
                g.DrawImage(bmpFrame, destR,0 ,0, bmpFrame.Width, bmpFrame.Height,
                    GraphicsUnit.Pixel, imgAttri);
            }
            else
            {
                g.DrawImage(bmpFrame, destR);
            }
            //g.Dispose();
        }

        // Convert to Gif
        public static unsafe Bitmap ConvertTransparancyGif(Bitmap imgSrc, Color clrKey)
        {
            int width = imgSrc.Width;
            int height = imgSrc.Height;

            // new gif
            MemoryStream memStream = new MemoryStream();
            imgSrc.Save(memStream, ImageFormat.Gif);
            Bitmap gifSrc = (Bitmap)Image.FromStream(memStream, false, false);

            // result gif
            Bitmap gifDest = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            if (clrKey.A == 0)
            {
                clrKey = Color.FromArgb(255,Color.Black);
            }

            // convert the palette
            int colorIndex = -1;
            ColorPalette dstPalette = gifDest.Palette;
            for (int n = 0; n < gifSrc.Palette.Entries.Length; n++)
            {
                Color tc = gifSrc.Palette.Entries[n];
                if (tc == clrKey)
                {
                    colorIndex = n;
                }
                dstPalette.Entries[n] = Color.FromArgb(255, tc);
                //dstPalette.Entries[n] = tc;
            }
            if (colorIndex != -1)
            {
                dstPalette.Entries[colorIndex] = Color.FromArgb(0, clrKey);
            }
            gifDest.Palette = dstPalette;
                
            
            

            // now to copy the actual bitmap data 
            BitmapData srcBmpData = gifSrc.LockBits(
                new Rectangle(0, 0, width, height),
                ImageLockMode.ReadOnly,
                gifSrc.PixelFormat );

            BitmapData dstBmpData = gifDest.LockBits(
                new Rectangle(0, 0, width, height),
                ImageLockMode.WriteOnly,
                gifDest.PixelFormat );

            byte* pSrc = (byte*)srcBmpData.Scan0.ToPointer();
            byte* pDst = (byte*)dstBmpData.Scan0.ToPointer();

            // steps through each pixel 
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    pDst[x] = pSrc[x];
                }
                pDst += srcBmpData.Stride;
                pSrc += srcBmpData.Stride;
            }

            // unlock the bitmaps 
            gifSrc.UnlockBits(srcBmpData);
            gifDest.UnlockBits(dstBmpData);

            // dispose
            gifSrc.Dispose();
            memStream.Dispose();


            return gifDest;

        }

    }
}
