using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ProWrite.Unsafe
{
	public class ImageHelper
	{
        int _newWidth;
        int _newHeight;

		/// <summary>
		/// ReSizeImage filter to an srcImage
		/// </summary>
		/// <param name="srcImage">Source image to apply filter to</param>
		/// <param name="destImageWidth">Width of new srcImage</param>
		/// <param name="destImageHeight">Height of new srcImage</param>
		/// <returns>Returns filter's result obtained by applying the filter to the source srcImage</returns>
		public static Bitmap ReSizeImage(Image srcImage, int destImageWidth, int destImageHeight)
		{
            if (destImageWidth <= 0)
                destImageWidth = 1;

            if (destImageHeight <= 0)
                destImageHeight = 1;

            //srcImage.Save("D:\\f1.jpg");

            //my code
            //Bitmap destImage = new Bitmap(destImageWidth, destImageHeight);
            //int zone = srcImage.Width / destImage.Width;

            //if (srcImage != null)
            //{
            //    using (Graphics g = Graphics.FromImage(destImage))
            //    {
            //        Bitmap tmp = (Bitmap)srcImage.Clone();
            //        if (PixelateHelper.Pixelate2(ref tmp, 16))
            //        {
            //            g.InterpolationMode = InterpolationMode.NearestNeighbor;
            //            g.DrawImage(tmp, new RectangleF(0, 0, destImageWidth, destImageHeight), new RectangleF(0, 0, tmp.Width, tmp.Height), GraphicsUnit.Pixel);
            //            tmp.Dispose();
            //        }
            //        g.Dispose();
            //    }
            //}

            ////destImage.Save("D:\\f2.jpg");

            //return destImage;
           
            
            // old code
            //srcImage.Save("D:\\f1.jpg");
            Bitmap destImage = new Bitmap(destImageWidth, destImageHeight);
            using (Graphics g = Graphics.FromImage(destImage))
            {
                g.InterpolationMode = InterpolationMode.NearestNeighbor;
                float x = (float)(-0.5 + 0.5 * srcImage.Width / destImage.Width);
                float y = (float)(-0.5 + 0.5 * srcImage.Height / destImage.Height);
                g.DrawImage(srcImage,
                    new RectangleF(new PointF(0f, 0f), destImage.Size),
                    new RectangleF(new PointF(x, y)
                                            , srcImage.Size),
                    GraphicsUnit.Pixel);
            }
            //destImage.Save("D:\\f2.jpg");
            return destImage; 
            
		}

        /// <summary>
        /// ReSizeImage filter to an srcImage
        /// </summary>
        /// <param name="srcImage">Source image to apply filter to</param>
        /// <param name="destImageWidth">Width of new srcImage</param>
        /// <param name="destImageHeight">Height of new srcImage</param>
        /// <returns>Returns filter's result obtained by applying the filter to the source srcImage</returns>
        public static Bitmap ReSizeImagePlaylist(Image srcImage, int destImageWidth, int destImageHeight)
        {


            if (destImageWidth <= 0)
                destImageWidth = 1;

            if (destImageHeight <= 0)
                destImageHeight = 1;

            Bitmap destImage = new Bitmap(destImageWidth, destImageHeight);
            using (Graphics g = Graphics.FromImage(destImage))
            {
                g.InterpolationMode = InterpolationMode.NearestNeighbor;
                g.DrawImage(srcImage,
                    new RectangleF(new PointF(0f, 0f), destImage.Size),
                    new RectangleF(new PointF(0,0), srcImage.Size),
                    GraphicsUnit.Pixel);
            }

            return destImage;
        }

		/// <summary>
		/// ReSizeImage filter to an image
		/// </summary>
		/// 
		/// <param name="imageData">Source image to apply filter to</param>
		/// 
		/// <returns>Returns filter's result obtained by applying the filter to the source image</returns>
		/// 
		Bitmap ReSizeImage(BitmapData imageData)
		{
			if (
				(imageData.PixelFormat != PixelFormat.Format24bppRgb) &&
				(imageData.PixelFormat != PixelFormat.Format8bppIndexed)
				)
				throw new ArgumentException();

			// get new image dimension
			Size newSize = CalculateNewImageSize(imageData);

			// create new image
			Bitmap dstImage = new Bitmap(newSize.Width, newSize.Height, imageData.PixelFormat);

			// lock destination bitmap data
			BitmapData dstData = dstImage.LockBits(
				new Rectangle(0, 0, newSize.Width, newSize.Height),
				ImageLockMode.ReadWrite, imageData.PixelFormat);

			// process the filter
            ResizeBilinear(imageData, dstData);
            //ResizeBicubic(imageData, dstData);

			// unlock destination images
			dstImage.UnlockBits(dstData);

			return dstImage;
		}

        // Scale Image to desired sizes keeping aspect ratio
        public static Image ScaleImage(Image source, int MaxWidth, int MaxHeight)
        {
            float MaxRatio = MaxWidth / (float)MaxHeight;
            float ImgRatio = source.Width / (float)source.Height;

            if (source.Width > MaxWidth)
                return new Bitmap(source, new Size(MaxWidth, (int)Math.Round(MaxWidth / ImgRatio, 0)));

            if (source.Height > MaxHeight)
                return new Bitmap(source, new Size((int)Math.Round(MaxWidth * ImgRatio, 0), MaxHeight));

            if (MaxRatio >= ImgRatio)
                return new Bitmap(source, new Size((int)Math.Round(1.0 * source.Width * (MaxHeight / source.Height)), MaxHeight));

            if (MaxRatio < ImgRatio)
                return new Bitmap(source, new Size(MaxWidth, (int)Math.Round(1.0 * source.Height * MaxWidth / source.Width)));

            return source;
        }

        // Scale Image to desired sizes keeping aspect ratio
        public static Image ScaleImage(Image source, double scaleFactor)
        {
            if (scaleFactor <= 0) return null;
            int w = (int)(source.Width / scaleFactor);
            w = w < 1 ? 1 : w;
            int h = (int)(source.Height / scaleFactor);
            h = h < 1 ? 1 : h;
            return new Bitmap(source, new Size(w, h));
        }

        #region create the Gif image with transparent background color
        public static Bitmap ReColorGif(Image image)
        {
            int nColors = 16;

            int w = image.Width;
            int h = image.Height;

            Bitmap bitmap = new Bitmap(w, h, PixelFormat.Format8bppIndexed);
            ColorPalette pal = GetColorPalette();

            for (int i = 0; i < nColors; i++)
                pal.Entries[i] = Color.FromArgb(255, 100, 100, 100);

            pal.Entries[0] = Color.FromArgb(255, 0, 0, 0);
            pal.Entries[1] = Color.FromArgb(255, 255, 0, 0);
            pal.Entries[2] = Color.FromArgb(255, 0, 255, 0);
            pal.Entries[3] = Color.FromArgb(255, 0, 0, 255);
            pal.Entries[4] = Color.FromArgb(255, 204, 204, 204);
            pal.Entries[nColors - 1] = Color.FromArgb(0, 255, 255, 255);

            //web safe palette use values =
            // 00 51 102 153 204 255 

            //Set the palette into the new Bitmap object.
            bitmap.Palette = pal;

            Bitmap bmpcopy = new Bitmap(w, h, PixelFormat.Format32bppArgb);
            Graphics g = Graphics.FromImage(bmpcopy);
            g.PageUnit = GraphicsUnit.Pixel;

            //Transfer the Image to the Bitmap.
            g.DrawImage(image, 0, 0, w, h);

            // Force g to release its resources, namely BmpCopy.
            g.Dispose();
            image.Dispose();
            //Lock a rectangular portion of the bitmap for writing.
            BitmapData bitmapData;
            Rectangle rect = new Rectangle(0, 0, w, h);
            bitmapData = bitmap.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);

            // Copy the pixels from the source image 
            IntPtr pixels = bitmapData.Scan0;
            int pBits;

            if (bitmapData.Stride > 0)
                pBits = pixels.ToInt32();
            else
                pBits = pixels.ToInt32() + bitmapData.Stride * (h - 1);

            int stride = Math.Abs(bitmapData.Stride);
            byte[] bits = new byte[h * stride];

            for (int row = 0; row < h; row++)
                for (int col = 0; col < w; col++)
                {
                    int i8BppPixel = row * stride + col;
                    Color pixel = bmpcopy.GetPixel(col, row);

                    //                bits(i8BppPixel) = CByte(colorIndex)
                    double colorIndex;
                    if (pixel.R == 0 && pixel.G == 0 && pixel.B == 0)
                        colorIndex = 0;
                    else if (pixel.R > 100 && pixel.G == 0 && pixel.B == 0)
                        colorIndex = 1;
                    else if (pixel.G > 100 && pixel.B == 0 && pixel.R == 0)
                        colorIndex = 2;
                    else if (pixel.B > 100 && pixel.R == 0 && pixel.B == 0)
                        colorIndex = 3;
                    else if (pixel.B == 204 && pixel.R == 204 && pixel.G == 204)
                        colorIndex = 4;
                    else
                        colorIndex = nColors - 1;

                    bits[i8BppPixel] = Convert.ToByte(colorIndex);

                }

            //Put the image bits definition into the bitmap.
            CopyArrayTo(pBits, bits, h * stride);
            bitmap.UnlockBits(bitmapData);
            bmpcopy.Dispose();

            return bitmap;
        }

        private static ColorPalette GetColorPalette()
        {
            Bitmap map = new Bitmap(1, 1, PixelFormat.Format8bppIndexed);
            ColorPalette palette = map.Palette;
            map.Dispose();

            return palette;
        }
       
        [DllImport("KERNEL32.DLL", EntryPoint = "RtlMoveMemory", SetLastError = true
           , CharSet = CharSet.Auto, ExactSpelling = true, CallingConvention = CallingConvention.StdCall)]
        private static extern void CopyArrayTo([In(), MarshalAs(UnmanagedType.I4)] 
        Int32 hpvDest, [In(), Out()] byte[] hpvSource, int cbCopy);
        #endregion

        /// <summary>
        /// Calculates new image size
        /// </summary>
        /// <param name="sourceData">Source image data</param>
        /// <returns>New image size</returns>
        Size CalculateNewImageSize( BitmapData sourceData )
        {
            return new Size( _newWidth, _newHeight );
        }

		/// <summary>
        /// Process the filter on the specified image
        /// </summary>
        /// <param name="sourceData">Source image data</param>
        /// <param name="destinationData">Destination image data</param>
		unsafe void ResizeBilinear( BitmapData sourceData, BitmapData destinationData )
        {
            // get source image size
            int width   = sourceData.Width;
            int height  = sourceData.Height;

            int pixelSize = ( sourceData.PixelFormat == PixelFormat.Format8bppIndexed ) ? 1 : 3;
            int srcStride = sourceData.Stride;
            int dstOffset = destinationData.Stride - pixelSize * _newWidth;
            double xFactor = (double) width / _newWidth;
            double yFactor = (double) height / _newHeight;

            // do the job
            byte* src = (byte*) sourceData.Scan0.ToPointer( );
            byte* dst = (byte*) destinationData.Scan0.ToPointer( );

            // coordinates of source points
            double  ox, oy, dx1, dy1, dx2, dy2;
            int     ox1, oy1, ox2, oy2;
            // width and height decreased by 1
            int ymax = height - 1;
            int xmax = width - 1;
            // temporary pointers
            byte* tp1, tp2;
            byte* p1, p2, p3, p4;

            // for each line
            for ( int y = 0; y < _newHeight; y++ )
            {
                // Y coordinates
                oy  = (double) y * yFactor;
                oy1 = (int) oy;
                oy2 = ( oy1 == ymax ) ? oy1 : oy1 + 1;
                dy1 = oy - (double) oy1;
                dy2 = 1.0 - dy1;

                // get temp pointers
                tp1 = src + oy1 * srcStride;
                tp2 = src + oy2 * srcStride;

                // for each pixel
                for ( int x = 0; x < _newWidth; x++ )
                {
                    // X coordinates
                    ox  = (double) x * xFactor;
                    ox1 = (int) ox;
                    ox2 = ( ox1 == xmax ) ? ox1 : ox1 + 1;
                    dx1 = ox - (double) ox1;
                    dx2 = 1.0 - dx1;

                    // get four points
                    p1 = tp1 + ox1 * pixelSize;
                    p2 = tp1 + ox2 * pixelSize;
                    p3 = tp2 + ox1 * pixelSize;
                    p4 = tp2 + ox2 * pixelSize;

                    // interpolate using 4 points
                    for ( int i = 0; i < pixelSize; i++, dst++, p1++, p2++, p3++, p4++ )
                    {
                        *dst = (byte) (
                            dy2 * ( dx2 * ( *p1 ) + dx1 * ( *p2 ) ) +
                            dy1 * ( dx2 * ( *p3 ) + dx1 * ( *p4 ) ) );
                    }
                }
                dst += dstOffset;
            }
        }

		/// <summary>
		/// Process the filter on the specified image
		/// </summary>
		/// 
		/// <param name="sourceData">Source image data</param>
		/// <param name="destinationData">Destination image data</param>
		/// 
		unsafe void ResizeBicubic(BitmapData sourceData, BitmapData destinationData)
		{
			Color fillColor = Color.FromArgb( 0, 0, 0 );
			double angle = 0;
			// get source image size
			int width = sourceData.Width;
			int height = sourceData.Height;
			double halfWidth = (double)width / 2;
			double halfHeight = (double)height / 2;

			// get destination image size
			int newWidth = destinationData.Width;
			int newHeight = destinationData.Height;
			double halfNewWidth = (double)newWidth / 2;
			double halfNewHeight = (double)newHeight / 2;

			// angle's sine and cosine
			double angleRad = angle * Math.PI / 180;
			double angleCos = Math.Cos(angleRad);
			double angleSin = Math.Sin(angleRad);

			int srcStride = sourceData.Stride;
			int dstOffset = destinationData.Stride -
				((destinationData.PixelFormat == PixelFormat.Format8bppIndexed) ? newWidth : newWidth * 3);

			// fill values
			byte fillR = fillColor.R;
			byte fillG = fillColor.G;
			byte fillB = fillColor.B;

			// do the job
			byte* src = (byte*)sourceData.Scan0.ToPointer();
			byte* dst = (byte*)destinationData.Scan0.ToPointer();

			// destination pixel's coordinate relative to image center
			double cx, cy;
			// coordinates of source points and cooefficiens
			double ox, oy, dx, dy, k1, k2;
			int ox1, oy1, ox2, oy2;
			// destination pixel values
			double r, g, b;
			// width and height decreased by 1
			int ymax = height - 1;
			int xmax = width - 1;
			// temporary pointer
			byte* p;

			if (destinationData.PixelFormat == PixelFormat.Format8bppIndexed)
			{
				// grayscale
				cy = -halfNewHeight;
				for (int y = 0; y < newHeight; y++)
				{
					cx = -halfNewWidth;
					for (int x = 0; x < newWidth; x++, dst++)
					{
						// coordinates of source point
						ox = angleCos * cx + angleSin * cy + halfWidth;
						oy = -angleSin * cx + angleCos * cy + halfHeight;

						ox1 = (int)ox;
						oy1 = (int)oy;

						// validate source pixel's coordinates
						if ((ox1 < 0) || (oy1 < 0) || (ox1 >= width) || (oy1 >= height))
						{
							// fill destination image with filler
							*dst = fillG;
						}
						else
						{
							dx = ox - (double)ox1;
							dy = oy - (double)oy1;

							// initial pixel value
							g = 0;

							for (int n = -1; n < 3; n++)
							{
								// get Y cooefficient
								k1 = Interpolation.BiCubicKernel(dy - (double)n);

								oy2 = oy1 + n;
								if (oy2 < 0)
									oy2 = 0;
								if (oy2 > ymax)
									oy2 = ymax;

								for (int m = -1; m < 3; m++)
								{
									// get X cooefficient
									k2 = k1 * Interpolation.BiCubicKernel((double)m - dx);

									ox2 = ox1 + m;
									if (ox2 < 0)
										ox2 = 0;
									if (ox2 > xmax)
										ox2 = xmax;

									g += k2 * src[oy2 * srcStride + ox2];
								}
							}
							*dst = (byte)g;
						}
						cx++;
					}
					cy++;
					dst += dstOffset;
				}
			}
			else
			{
				// RGB
				cy = -halfNewHeight;
				for (int y = 0; y < newHeight; y++)
				{
					cx = -halfNewWidth;
					for (int x = 0; x < newWidth; x++, dst += 3)
					{
						// coordinates of source point
						ox = angleCos * cx + angleSin * cy + halfWidth;
						oy = -angleSin * cx + angleCos * cy + halfHeight;

						ox1 = (int)ox;
						oy1 = (int)oy;

						// validate source pixel's coordinates
						if ((ox1 < 0) || (oy1 < 0) || (ox1 >= width) || (oy1 >= height))
						{
							// fill destination image with filler
							dst[RGB.R] = fillR;
							dst[RGB.G] = fillG;
							dst[RGB.B] = fillB;
						}
						else
						{
							dx = ox - (float)ox1;
							dy = oy - (float)oy1;

							// initial pixel value
							r = g = b = 0;

							for (int n = -1; n < 3; n++)
							{
								// get Y cooefficient
								k1 = Interpolation.BiCubicKernel(dy - (float)n);

								oy2 = oy1 + n;
								if (oy2 < 0)
									oy2 = 0;
								if (oy2 > ymax)
									oy2 = ymax;

								for (int m = -1; m < 3; m++)
								{
									// get X cooefficient
									k2 = k1 * Interpolation.BiCubicKernel((float)m - dx);

									ox2 = ox1 + m;
									if (ox2 < 0)
										ox2 = 0;
									if (ox2 > xmax)
										ox2 = xmax;

									// get pixel of original image
									p = src + oy2 * srcStride + ox2 * 3;

									r += k2 * p[RGB.R];
									g += k2 * p[RGB.G];
									b += k2 * p[RGB.B];
								}
							}
							dst[RGB.R] = (byte)r;
							dst[RGB.G] = (byte)g;
							dst[RGB.B] = (byte)b;
						}
						cx++;
					}
					cy++;
					dst += dstOffset;
				}
			}
		}

	}
}
