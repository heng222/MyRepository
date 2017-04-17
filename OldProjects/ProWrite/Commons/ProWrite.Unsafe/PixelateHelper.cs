using System;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Runtime.InteropServices;

namespace ProWrite.Unsafe
{
    public class PixelateHelper
    {
        public static bool Pixelate1(ref Bitmap bmp, int zone)
        {
            BmpProc32 src = new BmpProc32(bmp);

            if ((zone < 2) | (zone > 30)) return false;

            int w = bmp.Width;
            int h = bmp.Height;

            int ir, count, sumr, sumg, sumb;

            for (int y = 0; y < h; y += zone)
                for (int x = 0; x < w; x += zone)
                {
                    count = sumr = sumg = sumb = 0;

                    for (int iy = y; iy < y + zone; iy++)
                        for (int ix = x; ix < x + zone; ix++)
                        {
                            if ((iy > h - 1) | (ix > w - 1)) continue;

                            count++;

                            ir = src.IndexR(ix, iy);
                            sumr += src[ir];
                            sumg += src[ir - 1];
                            sumb += src[ir - 2];
                        }

                    sumr = sumr / count;
                    sumg = sumg / count;
                    sumb = sumb / count;

                    for (int iy = y; iy < y + zone; iy++)
                        for (int ix = x; ix < x + zone; ix++)
                        {
                            if ((iy > h - 1) | (ix > w - 1)) continue;

                            ir = src.IndexR(ix, iy);
                            src[ir] = (byte)sumr;
                            src[ir - 1] = (byte)sumg;
                            src[ir - 2] = (byte)sumb;
                        }
                }

            src.Dispose();

            return true;
        }

        public static bool Pixelate2(ref Bitmap bmp, int zone)
        {
            BmpProc32 src = new BmpProc32(bmp);

            if ((zone < 2) | (zone > 30)) return false;

            int w = bmp.Width;
            int h = bmp.Height;

            int ir, count, sumr, sumg, sumb;

            byte[,] rr = new byte[w / zone + 1, h / zone + 1];
            byte[,] gg = new byte[w / zone + 1, h / zone + 1];
            byte[,] bb = new byte[w / zone + 1, h / zone + 1];

            int countX, countY;

            byte rrr, ggg, bbb;

            countY = 0;

            for (int y = 0; y < h - 1; y += zone)
            {
                countX = 0;

                for (int x = 0; x < w - 1; x += zone)
                {
                    count = sumr = sumg = sumb = 0;

                    for (int iy = y; iy < y + zone; iy++)
                        for (int ix = x; ix < x + zone; ix++)
                        {
                            if ((iy > h - 1) | (ix > w - 1)) continue;

                            count++;

                            ir = src.IndexR(ix, iy);
                            sumr += src[ir];
                            sumg += src[ir - 1];
                            sumb += src[ir - 2];
                        }

                    sumr = sumr / count;
                    sumg = sumg / count;
                    sumb = sumb / count;

                    rr[countX, countY] = (byte)sumr;
                    gg[countX, countY] = (byte)sumg;
                    bb[countX, countY] = (byte)sumb;

                    rrr = (byte)sumr;
                    ggg = (byte)sumg;
                    bbb = (byte)sumb;

                    if ((sumr < 230) & (sumr > 15)) { rrr = (byte)(sumr - 15); }
                    if ((sumg < 230) & (sumg > 15)) { ggg = (byte)(sumg - 15); }
                    if ((sumb < 230) & (sumb > 15)) { bbb = (byte)(sumb - 15); }


                    for (int iy = y; iy < y + zone; iy++)
                        for (int ix = x; ix < x + zone; ix++)
                        {
                            if ((iy > h - 1) | (ix > w - 1)) continue;

                            ir = src.IndexR(ix, iy);
                            src[ir] = rrr;
                            src[ir - 1] = ggg;
                            src[ir - 2] = bbb;
                        }

                    countX++;

                }

                countY++;
            }

            src.Dispose();

            countY = 0;

            SolidBrush br = new SolidBrush(Color.Black);

            Point[] pt = new Point[3];

            Graphics g = Graphics.FromImage(bmp);
            g.SmoothingMode = SmoothingMode.AntiAlias;

            for (int y = 0; y < h - 1; y += zone)
            {
                countX = 0;

                for (int x = 0; x < w - 1; x += zone)
                {
                    rrr = rr[countX, countY]; ggg = gg[countX, countY];
                    bbb = bb[countX, countY];
                    if ((rrr < 230) & (rrr > 15)) { rrr = (byte)(rrr + 15); }
                    if ((ggg < 230) & (ggg > 15)) { ggg = (byte)(ggg + 15); }
                    if ((bbb < 230) & (bbb > 15)) { bbb = (byte)(bbb + 15); }
                    br.Color = Color.FromArgb(rrr, ggg, bbb);
                    pt[0].X = x; pt[0].Y = y;
                    pt[1].X = x + zone; pt[1].Y = y;
                    pt[2].X = x; pt[2].Y = y + zone;
                    g.FillPolygon(br, pt);

                    countX++;
                }

                countY++;
            }

            g.Dispose();
            br.Dispose();

            return true;
        }

        public enum eRGB
        {
            b, g, r, a
        }

        interface BmpProc : IDisposable
        {
            int IndexR(int x, int y);
            void SetXY(int x, int y);
            byte GetValue(int index);
            void SetValue(int index, byte value);
            new void Dispose();
        }

        public class BmpProc32 : BmpProc
        {
            private bool flagDispose = false;

            private Bitmap rbmp;
            private int w, h;
            private BitmapData bmpData;
            private IntPtr ptr;
            private int stride;
            private int bytes;
            private byte[] data;
            private int xyr, xyg, xyb, xya;

            public BmpProc32(Bitmap bmp)
            {
                rbmp = bmp;
                w = bmp.Width;
                h = bmp.Height;
                Rectangle rect = new Rectangle(0, 0, w, h);
                bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite,
                                              PixelFormat.Format32bppArgb);
                ptr = bmpData.Scan0;
                stride = Math.Abs(bmpData.Stride);

                bytes = stride * h;
                data = new byte[bytes];
                Marshal.Copy(ptr, data, 0, bytes);
            }

            public byte this[int x, int y, eRGB rgb]
            {
                get { return data[stride * y + x * 4 + (int)(rgb)]; }
                set { data[stride * y + x * 4 + (int)(rgb)] = value; }
            }

            public byte this[int index]
            {
                get { return data[index]; }
                set { data[index] = value; }
            }

            public byte GetValue(int index)
            {
                return this[index];
            }

            public void SetValue(int index, byte value)
            {
                this[index] = value;
            }

            public int IndexR(int x, int y)
            {
                return stride * y + x * 4 + 2; // a <- +1
            }

            public void SetXY(int x, int y)
            {
                xyb = stride * y + x * 4;
                xyg = xyb + 1;
                xyr = xyg + 1;
                xya = xyr + 1;
            }

            public byte R
            {
                get { return data[xyr]; }
                set { data[xyr] = value; }
            }

            public byte G
            {
                get { return data[xyg]; }
                set { data[xyg] = value; }
            }

            public byte B
            {
                get { return data[xyb]; }
                set { data[xyb] = value; }
            }

            public byte A
            {
                get { return data[xya]; }
                set { data[xya] = value; }
            }

            public int DataLength
            {
                get { return bytes; }
            }

            protected virtual void Dispose(bool flag)
            {
                if (!flagDispose)
                {
                    if (flag)
                    {
                        Marshal.Copy(data, 0, ptr, bytes);
                        rbmp.UnlockBits(bmpData);
                    }
                    this.flagDispose = true;
                }
            }

            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            ~BmpProc32()
            {
                Dispose(false);
            }
        }

        public class BmpProc24 : BmpProc
        {
            private bool flagDispose = false;

            private Bitmap rbmp;
            private int w, h;
            private BitmapData bmpData;
            private IntPtr ptr;
            private int stride;
            private int bytes;
            private byte[] data;
            private int xyr, xyg, xyb;

            public BmpProc24(Bitmap bmp)
            {
                rbmp = bmp;
                w = bmp.Width;
                h = bmp.Height;
                Rectangle rect = new Rectangle(0, 0, w, h);
                bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite,
                                              PixelFormat.Format24bppRgb);
                ptr = bmpData.Scan0;
                stride = Math.Abs(bmpData.Stride);

                bytes = stride * h;
                data = new byte[bytes];
                Marshal.Copy(ptr, data, 0, bytes);
            }

            public byte this[int x, int y, eRGB rgb]
            {
                get { return data[stride * y + x * 3 + (int)(rgb)]; }
                set { data[stride * y + x * 3 + (int)(rgb)] = value; }
            }

            public byte this[int index]
            {
                get { return data[index]; }
                set { data[index] = value; }
            }

            public byte GetValue(int index)
            {
                return this[index];
            }

            public void SetValue(int index, byte value)
            {
                this[index] = value;
            }

            public int IndexR(int x, int y)
            {
                return stride * y + x * 3 + 2;
            }

            public void SetXY(int x, int y)
            {
                xyb = stride * y + x * 3;
                xyg = xyb + 1;
                xyr = xyg + 1;
            }

            public byte R
            {
                get { return data[xyr]; }
                set { data[xyr] = value; }
            }

            public byte G
            {
                get { return data[xyg]; }
                set { data[xyg] = value; }
            }

            public byte B
            {
                get { return data[xyb]; }
                set { data[xyb] = value; }
            }

            public int DataLength
            {
                get { return bytes; }
            }

            protected virtual void Dispose(bool flag)
            {
                if (!flagDispose)
                {
                    if (flag)
                    {
                        Marshal.Copy(data, 0, ptr, bytes);
                        rbmp.UnlockBits(bmpData);
                    }
                    this.flagDispose = true;
                }
            }

            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            ~BmpProc24()
            {
                Dispose(false);
            }
        }      

    }
}
