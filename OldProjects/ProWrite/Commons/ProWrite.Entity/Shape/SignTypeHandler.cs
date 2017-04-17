using System.Drawing;
using System.Drawing.Imaging;
using ProWrite.Core;
using System.Collections.Generic;
using System.Collections;
using System;
using System.Drawing.Drawing2D;
using System.ComponentModel;

namespace ProWrite.Entity.Shape
{
	public class SignTypeHandler
	{

        const float iRedSpectrum = 0.299f;
        const float iGreenSpectrum = 0.587f;
        const float iBlueSpectrum = 0114f;

        static readonly ColorMatrix[] matrixes = new ColorMatrix[]{

            //RGB
            null,

            //Red
            new ColorMatrix(new float[][]{
                new float[]{iRedSpectrum,     0, 0, 0, 0},
                new float[]{iGreenSpectrum,     0, 0, 0, 0},
                new float[]{iBlueSpectrum,     0, 0, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),

            //Amber
            new ColorMatrix(new float[][]{
                new float[]{iRedSpectrum,     iRedSpectrum*0.8f, 0, 0, 0},
                new float[]{iGreenSpectrum,     iGreenSpectrum*0.8f, 0, 0, 0},
                new float[]{iBlueSpectrum,     iGreenSpectrum*0.8f, 0, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),

                //Green
            new ColorMatrix(new float[][]{
                new float[]{0,     iRedSpectrum, 0, 0, 0},
                new float[]{0,     iGreenSpectrum, 0, 0, 0},
                new float[]{0,     iBlueSpectrum, 0, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),

                //Blue
            new ColorMatrix(new float[][]{
                new float[]{0,     0, iRedSpectrum, 0, 0},
                new float[]{0,     0, iGreenSpectrum, 0, 0},
                new float[]{0,     0, iBlueSpectrum, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),

                //White
            new ColorMatrix(new float[][]{

                new float[]{iRedSpectrum,     iRedSpectrum, iRedSpectrum, 0, 0},
                new float[]{iGreenSpectrum,     iGreenSpectrum, iGreenSpectrum, 0, 0},
                new float[]{iBlueSpectrum,     iBlueSpectrum, iBlueSpectrum, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),

                //BlueGreen
            new ColorMatrix(new float[][]{
                new float[]{0,     iRedSpectrum, iRedSpectrum, 0, 0},
                new float[]{0,     1, 0, 0, 0},
                new float[]{0,     0, 1, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),


                //RedGreen
            new ColorMatrix(new float[][]{
                new float[]{1,     0, 0, 0, 0},
                new float[]{0,     1, 0, 0, 0},
                new float[]{iBlueSpectrum,     iBlueSpectrum, 0, 0, 0},
                new float[]{0,     0, 0, 1, 0},
                new float[]{0,     0, 0, 0, 1}}),
        };



        private static Color getWhiteShiftPixel(int in_greyscale)
        {
            return Color.FromArgb(in_greyscale, in_greyscale, in_greyscale);
        }

        private static Color getRedShiftPixel(int in_greyscale)
        {
            return Color.FromArgb(in_greyscale, 0, 0);
        }

        private static Color getGreenShiftPixel(int in_greyscale)
        {
            return Color.FromArgb(0, in_greyscale, 0);
        }

        private static Color getBlueShiftPixel(int in_greyscale)
        {
            return Color.FromArgb(0, 0, in_greyscale);
        }

        private static int getGreyScale(Color color)
        {
            return (int)(color.R * 0.299 + color.G * 0.587 + color.B * 0.114);
        }

        private static Color getBlueGreenShiftPixel(Color color)
        {
            int g = (int)(color.G + color.R * 0.299) & 0XFF;
            int b = (int)(color.B + color.R * 0.299) & 0XFF;

            return Color.FromArgb(0,g,b);
        }

        private static Color getRedGreenShiftPixel(Color color)
        {
            int r = (int)(color.R + color.B * 0.114) & 0XFF;
            int g = (int)(color.G + color.B * 0.114) & 0XFF;
            return Color.FromArgb(r, g, 0);
        }

        private static Color getAmberShiftPixel(int in_greyscale)
        {

            int g = (int)(((long)(in_greyscale * 204) >> 8) & 0xFF);
            return Color.FromArgb(in_greyscale, g, 0);
        }

        public static Color ConvertToMonoColor(Color color, SignType signType)
        {
            if (color == Color.Transparent)
                return color;
            switch (signType)
            {
                case SignType.Red:
                    return ConvertRedSign(color);
                    break;
                case SignType.Green:
                    return ConvertGreenSign(color);
                    break;
                case SignType.Blue:
                    return ConvertBlueSign(color);
                    break;
                case SignType.Amber:
                    return ConvertAmberSign(color);
                    break;
                default:
                    return color;
                    break;
            }
        }

        #region cellColorsAmber
        static Color[] cellColorsAmber = new Color[] {
                                                         Color.FromArgb(255,188,62),
                                                         Color.FromArgb(250,184,61),
                                                         Color.FromArgb(245,180,60),
                                                         Color.FromArgb(240,176,59),
                                                         Color.FromArgb(235,172,58),

                                                         Color.FromArgb(230,168,57),
                                                         Color.FromArgb(225,164,56),
                                                         Color.FromArgb(220,160,55),
                                                         Color.FromArgb(211,156,51),

                                                         Color.FromArgb(206,152,50),
                                                         Color.FromArgb(201,148,49),
                                                         Color.FromArgb(196,144,48),
                                                         Color.FromArgb(191,140,47),
                                                         Color.FromArgb(186,136,46),

                                                         Color.FromArgb(181,132,45),
                                                         Color.FromArgb(176,128,44),
                                                         Color.FromArgb(167,124,40),
                                                         Color.FromArgb(162,120,39),

                                                         Color.FromArgb(157,116,38),
                                                         Color.FromArgb(152,112,37),
                                                         Color.FromArgb(147,108,36),
                                                         Color.FromArgb(142,104,35),
                                                         Color.FromArgb(137,100,34),

                                                         Color.FromArgb(132,96,33),
                                                         Color.FromArgb(123,92,29),
                                                         Color.FromArgb(118,88,28),
                                                         Color.FromArgb(113,84,27),

                                                         Color.FromArgb(108,80,26),
                                                         Color.FromArgb(103,76,25),
                                                         Color.FromArgb(98,72,24),
                                                         Color.FromArgb(93,68,23),
                                                         Color.FromArgb(88,64,22) ,

                                                         Color.FromArgb(79,60,18),
                                                         Color.FromArgb(74,56,17),
                                                         Color.FromArgb(69,52,16),
                                                         Color.FromArgb(64,48,15),

                                                         Color.FromArgb(59,44,14),
                                                         Color.FromArgb(54,40,13),
                                                         Color.FromArgb(49,36,12),
                                                         Color.FromArgb(44,32,11),
                                                         Color.FromArgb(35,28,7),

                                                         Color.FromArgb(30,24,6),
                                                         Color.FromArgb(25,20,5),
                                                         Color.FromArgb(20,16,4),
                                                         Color.FromArgb(15,12,3),

                                                         Color.FromArgb(10,8,2),
                                                         Color.FromArgb(5,4,1) ,
                                                         Color.FromArgb( 0 , 0 ,0 ) 
                                                                                             
                                                     };
        #endregion cellColorsWhite

        #region cellColorsWhite
        static Color[] cellColorsWhite = new Color[] {
                                                         Color.FromArgb(255, 255,255),
                                                         Color.FromArgb(250, 250,250),
                                                         Color.FromArgb(245, 245,245),
                                                         Color.FromArgb(240, 240,240),
                                                         Color.FromArgb(235, 235,235),

                                                         Color.FromArgb( 229, 229,229),
                                                         Color.FromArgb( 224, 224,224),
                                                         Color.FromArgb( 216, 216,216),
                                                         Color.FromArgb( 211, 211,211),

                                                         Color.FromArgb( 205, 205,205),
                                                         Color.FromArgb( 200, 200,200),
                                                         Color.FromArgb( 195, 195,195),
                                                         Color.FromArgb( 190, 190,190),
                                                         Color.FromArgb( 185, 185,185),

                                                         Color.FromArgb( 179, 179,179),
                                                         Color.FromArgb( 174, 174,174),
                                                         Color.FromArgb( 169, 169,169),
                                                         Color.FromArgb( 164, 164,164),

                                                         Color.FromArgb( 158, 158,158),
                                                         Color.FromArgb( 153, 153,153),
                                                         Color.FromArgb( 148, 148,148),
                                                         Color.FromArgb( 143, 143,143),
                                                         Color.FromArgb( 138, 138,138),

                                                         Color.FromArgb( 132, 132,132),
                                                         Color.FromArgb( 127, 127,127),
                                                         Color.FromArgb( 122, 122,122),
                                                         Color.FromArgb( 117, 117,117),

                                                         Color.FromArgb( 111, 111,111),
                                                         Color.FromArgb( 106, 106,106),
                                                         Color.FromArgb( 101, 101,101),
                                                         Color.FromArgb( 96 , 96 ,96 ),
                                                         Color.FromArgb( 91 , 91 ,91 ) ,

                                                         Color.FromArgb( 85, 85,85),
                                                         Color.FromArgb( 80, 80,80),
                                                         Color.FromArgb( 75, 75,75),
                                                         Color.FromArgb( 70, 70,70),

                                                         Color.FromArgb( 64, 64,64),
                                                         Color.FromArgb( 59, 59,59),
                                                         Color.FromArgb( 54, 54,54),
                                                         Color.FromArgb( 49, 49,49),
                                                         Color.FromArgb( 44, 44,44),

                                                         Color.FromArgb( 38, 38,38),
                                                         Color.FromArgb( 32, 32,32),
                                                         Color.FromArgb( 26, 26,26),
                                                         Color.FromArgb( 20, 20,20),

                                                         Color.FromArgb( 14, 14,14),
                                                         Color.FromArgb( 7 , 7 ,7 ) ,
                                                         Color.FromArgb( 0 , 0 ,0 ) 
                                                                                             
                                                     };
        #endregion cellColorsWhite

        private static Color ConvertAmberSign(Color color)
        {
            int index = Array.FindIndex(cellColorsAmber, (c) => c == color);
            if(index != -1)
            {
                return cellColorsWhite[index];
            }
            else
            {
                return cellColorsWhite[0];
            }
        }

	    private static Color ConvertRedSign(Color color)
        {
            string c = color.R.ToString();
            return Color.FromArgb(255, Convert.ToInt32(c), Convert.ToInt32(c), Convert.ToInt32(c));
        }
        private static Color ConvertGreenSign(Color color)
        {
            string c = color.G.ToString();
            return Color.FromArgb(255, Convert.ToInt32(c), Convert.ToInt32(c), Convert.ToInt32(c));
        }
        private static Color ConvertBlueSign(Color color)
        {
            string c = color.B.ToString();
            return Color.FromArgb(255, Convert.ToInt32(c), Convert.ToInt32(c), Convert.ToInt32(c));
        }

	    public static Color ConvertColor(Color color, SignType outChannelType)
		{if (color == Color.Transparent)
		    return color;
            
            int y = getGreyScale(color);
            switch (outChannelType)
            {
                case SignType.Red:
                    return getRedShiftPixel(y);
                case SignType.Green:
                    return getGreenShiftPixel(y);
                case SignType.Blue:
                    return getBlueGreenShiftPixel(color);
                case SignType.Amber:
                    return getAmberShiftPixel(y);
                case SignType.White:
                    return getWhiteShiftPixel(y);
                //case SignType.BlueGreen:
                //    return getBlueGreenShiftPixel(color);
                //case SignType.RedGreen:
                //    return getRedGreenShiftPixel(color);
                default: return color;
            }
            return color;
		}


        public static void SetOutChannel2(Graphics graphics, Image image, SignType outChannelType, RectangleF destBounds,
                                        RectangleF srcBounds)
        {

            ImageAttributes imageAttributes = new ImageAttributes();
            ColorMatrix colorMatrix = matrixes[(int)outChannelType];

            imageAttributes.ClearColorMatrix(ColorAdjustType.Bitmap);


            if (colorMatrix != null)
                imageAttributes.SetColorMatrix(
                    colorMatrix,
                    ColorMatrixFlag.Default,
                    ColorAdjustType.Bitmap);

            Rectangle rect = Rectangle.Round(srcBounds);
            graphics.DrawImage(image, Rectangle.Round(destBounds),
                               rect.X, rect.Y, rect.Width, rect.Height, GraphicsUnit.Pixel, imageAttributes);
        }


        public static void SetOutChannel(Graphics graphics, Image image, SignType outChannelType, RectangleF destBounds,
                                     RectangleF srcBounds)
        {
            int width = image.Width;
            int height = image.Height;

            Bitmap bitmap = new Bitmap(image);
            BitmapData bmData = bitmap.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            int stride = bmData.Stride;

            unsafe
            {
                byte* p = (byte*)bmData.Scan0.ToPointer();
                int nOffset = stride - width * 3;

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        var color = ConvertColor(Color.FromArgb(p[2], p[1], p[0]), outChannelType);
                        p[2] = color.R;
                        p[1] = color.G;
                        p[0] = color.B;

                        p += 3;
                    }
                    p += nOffset;
                }
            }
            bitmap.UnlockBits(bmData);

            Rectangle rect = Rectangle.Round(srcBounds);
            graphics.DrawImage(bitmap, Rectangle.Round(destBounds),
                               rect.X, rect.Y, rect.Width, rect.Height, GraphicsUnit.Pixel);
            bitmap.Dispose();

        }
	}

    public class ResourceCache : IDisposable
    {
        Dictionary<int, Brush> solidBrushes;
        Dictionary<int, Pen> pens;
        Dictionary<string, Font> fonts;
        
        class IntComparer : IEqualityComparer<int>
        {
            public bool Equals(int x, int y)
            {
                return x == y;
            }
            public int GetHashCode(int obj)
            {
                return obj;
            }
        }

        private ResourceCache()
        {
            this.solidBrushes = new Dictionary<int, Brush>(new IntComparer());
            this.pens = new Dictionary<int, Pen>(new IntComparer());
        }
        [ThreadStatic]
        static ResourceCache defaultCache;
        public static ResourceCache DefaultCache
        {
            get
            {
                if (defaultCache == null) defaultCache = new ResourceCache();
                return defaultCache;
            }
        }
        const int MaxCount = 1000;
        public virtual void CheckCache()
        {
            if (Pens.Count > MaxCount) ClearHashtable(Pens);
            if (SolidBrushes.Count > MaxCount) ClearHashtable(SolidBrushes);
            if (this.fonts != null && fonts.Count > MaxCount) ClearHashtable(this.fonts);
        }
        public void Dispose()
        {
            Clear();
        }
        public void Clear()
        {
            ClearHashtable(SolidBrushes);
            ClearHashtable(Pens);
            ClearHashtable(this.fonts);
        }
        public Font GetFont(Font font, FontStyle style)
        {
            if (font.Style == style) return font;
            return GetFont(font, font.Size, style);
        }
        public Font GetFont(Font font, float size, FontStyle style)
        {
            //if (font.Style == style && font.Size == size) return font;
            //string key = GetFontKey(font, style, size);
            //var res = Fonts[key];
            //if (res == null)
            {
                return new Font(font.FontFamily, size, style);
                //Fonts[key] = font;
                //return font;
            }
            //return res;
        }
        protected string GetFontKey(Font font, FontStyle style, float size)
        {
            return string.Format("{0}: {1} {2} {3}", new object[] { font.FontFamily, size, font.Unit, style });
        }
        protected Brush GetSystemBrush(Color color)
        {
            return SystemBrushes.FromSystemColor(color);
        }
        protected Pen GetSystemPen(Color color)
        {
            return SystemPens.FromSystemColor(color);
        }
        public Brush GetSolidBrush(Color color)
        {
            Brush brush = null;
            if (color.IsSystemColor) brush = GetSystemBrush(color);
            if (brush != null) return brush;
            int key = color.ToArgb();
            if (SolidBrushes.TryGetValue(key, out brush))
                return brush;
            brush = new SolidBrush(color);
            SolidBrushes.Add(key, brush);
            return brush;
        }
        public Pen GetPen(Color color)
        {
            return GetPen(color, 1, PenAlignment.Outset, DashStyle.Solid);
        }
        public Pen GetPen(Color color,int width)
        {
            return GetPen(color, width, PenAlignment.Outset, DashStyle.Solid);
        }
        public Pen GetPen(Color color, int width, PenAlignment alignment)
        {
            return GetPen(color, width, alignment, DashStyle.Solid);
        }
        public Pen GetPen(Color color, int width,PenAlignment alignment,DashStyle dashStyle)
        {
            Pen pen = new Pen(color, width);
            pen.Alignment = alignment;
            pen.DashStyle = dashStyle;
            return pen;
        }
       
        protected int GetPenHash(Color color, int width,PenAlignment alignment,DashStyle style)
        {
            return color.GetHashCode() ^ width ^ (int)alignment ^ (int)style;
        }
        
        protected Dictionary<int, Brush> SolidBrushes
        {
            get { return solidBrushes; }
        }
        protected Dictionary<int, Pen> Pens
        {
            get { return pens; }
        }
        protected Dictionary<string,Font> Fonts
        {
            get
            {
                if (fonts == null) fonts = new Dictionary<string, Font>();
                return fonts;
            }
        }
        protected void ClearHashtable(IDictionary hash)
        {
            if (hash == null) return;
            foreach (IDisposable obj in hash.Values)
            {
                obj.Dispose();
            }
            hash.Clear();
        }
        [Description("")]
        public int ResourceCount
        {
            get
            {
                return SolidBrushes.Count + Pens.Count + Fonts.Count;
            }
        }
    }
}