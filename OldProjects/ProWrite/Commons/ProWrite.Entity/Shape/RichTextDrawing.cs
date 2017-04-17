using System;
using System.Drawing;
using System.Runtime.InteropServices;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Shape
{
	/// <summary>
	/// // 2008-6-19, Kevin 迁移
	/// </summary>
	public class RichTextDrawing
	{
		//Convert the unit used by the .NET framework (1/100 inch) 
		//and the unit used by Win32 API calls (twips 1/1440 inch)
		// private const double anInch = 14.4;
		private const double anInch = 15;

		private const int EM_FORMATRANGE = WM_USER + 57;
		private const int WM_USER = 0x0400;

		public RichTextDrawing()
		{
		}

		[DllImport("USER32.dll")]
		private static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wp, IntPtr lp);

		// Render the contents of the RichTextBox for printing
		//	Return the last character printed + 1 (printing start from this point for next page)
		public int Print(int charFrom, int charTo, Graphics g, IntPtr handle, RectangleF rect)
		{
			//Calculate the area to render and print
			RECT rectToPrint;
			rectToPrint.Top = (int) rect.Top; // (rect.Top * anInch);
			rectToPrint.Bottom = (int) (rect.Bottom*anInch); //rect.Bottom;//
			rectToPrint.Left = (int) rect.Left; // (rect.Left * anInch);
			rectToPrint.Right = (int) (rect.Right*anInch); //rect.Right;//

			//Calculate the size of the page
			RECT rectPage;
			rectPage.Top = (int) rect.Top; // (rect.Top * anInch);
			rectPage.Bottom = (int) (rect.Bottom*anInch); //rect.Bottom;// 
			rectPage.Left = (int) rect.Left; // (rect.Left * anInch);
			rectPage.Right = (int) (rect.Right*anInch); //rect.Right;// 

			IntPtr hdc = g.GetHdc();

			FORMATRANGE fmtRange;
			fmtRange.chrg.cpMax = charTo; //Indicate character from to character to 
			fmtRange.chrg.cpMin = charFrom;
			fmtRange.hdc = hdc; //Use the same DC for measuring and rendering
			fmtRange.hdcTarget = hdc; //Point at printer hDC
			fmtRange.rc = rectToPrint; //Indicate the area on page to print
			fmtRange.rcPage = rectPage; //Indicate size of page

			IntPtr res = IntPtr.Zero;

			IntPtr wparam = IntPtr.Zero;
			wparam = new IntPtr(1);

			//Get the pointer to the FORMATRANGE structure in memory
			IntPtr lparam = IntPtr.Zero;
			lparam = Marshal.AllocCoTaskMem(Marshal.SizeOf(fmtRange));
			Marshal.StructureToPtr(fmtRange, lparam, false);

			//Send the rendered data for printing 
			res = SendMessage(handle, EM_FORMATRANGE, wparam, lparam);

			//Free the block of memory allocated
			Marshal.FreeCoTaskMem(lparam);

			//Release the device context handle obtained by a previous call
			g.ReleaseHdc(hdc);

			//Return last + 1 character printer
			return res.ToInt32();
		}

		public static bool MeasureStringSize(string text, Font font, RectangleF bounds, StringFormat stringFormat)
		{
			Image image = new Bitmap((int) bounds.Width, (int) bounds.Height);

			Graphics graphics = Graphics.FromImage(image);

			graphics.Clear(Color.White);

			int codepointsFitted = 0;
			int linesFilled = 0;

			SizeF stringSize = graphics.MeasureString(text,
			                                          font, bounds.Size,
			                                          stringFormat, out codepointsFitted, out linesFilled);

			return true; // text.Length != codepointsFitted;
		}


		public static FontWrapper GetFontMeasureStringSize(
			string text
			, FontWrapper font
			, RectangleF bounds
			, StringFormat stringFormat
			, bool wordWrap
			, Graphics graphics)
		{
			Font tmp = GetFontMeasureStringSize(text, font.ToFont(), bounds, stringFormat, wordWrap, graphics);
			font.FromFont(tmp);
			return font;
		}

		//计算在指定的区域中显示的字符总数及行数
		public static Font GetFontMeasureStringSize(
			string text
			, Font font
			, RectangleF bounds
			, StringFormat stringFormat
			,bool wordWrap
			, Graphics graphics)
		{
			if (font == null)
				font = new Font("Tahoma", 16);

			if (string.IsNullOrEmpty(text))
				return font;

			if (bounds.Width == double.NaN
			    || Double.NaN == bounds.Height
			    || bounds.Size == SizeF.Empty
			    || bounds.Width <= 0.0f
			    || bounds.Height <= 0.0f)
			{
				return font;
			}

			int width = 0;
			int height = 0;
			float widthf = 0f;
			float heightf = 0f;

			try
			{
                widthf = bounds.Width < 1 ? 1 : bounds.Width;
                heightf = bounds.Height < 1 ? 1 : bounds.Height;
				width = (int) widthf;
				height = (int) heightf;
			}
			catch
			{
				return font;
			}
			Font MeasureFont = new Font(font.FontFamily, font.Size, font.Style, GraphicsUnit.Pixel);
			float oldValue = MeasureFont.Size;
            //Image shape = new Bitmap(width * 2, height * 2);
			SizeF stringSize = new SizeF();
			int codepointsFitted = 0;
			int linesFilled = 0;
			if (stringFormat == null)
				stringFormat = new StringFormat();

			stringSize = graphics.MeasureString(text,
			                                    MeasureFont, bounds.Size,
			                                    stringFormat, out codepointsFitted, out linesFilled);
			if (text.Length <= codepointsFitted &&
			    ((wordWrap && stringSize.Height < bounds.Height)
			     || (!wordWrap && stringSize.Width < bounds.Height && stringSize.Height < bounds.Height)))
			{
				do
				{
					if (text.Length <= codepointsFitted &&
					    ((wordWrap && stringSize.Height < bounds.Height)
					     || (!wordWrap && stringSize.Width < bounds.Height && stringSize.Height < bounds.Height)))
					{
						oldValue = MeasureFont.Size;

						MeasureFont = new Font(font.FontFamily, MeasureFont.Size + 1, font.Style, GraphicsUnit.Pixel);

						//测量输出字符串所需要的矩形空间
						stringSize = graphics.MeasureString(text,
						                                    MeasureFont, bounds.Size,
						                                    stringFormat, out codepointsFitted, out linesFilled);
					}
					else
					{
						break;
					}
				} while (true);
			}
			else
			{
				do
				{
					if (text.Length > codepointsFitted || stringSize.Height > bounds.Height)
					{
						if (MeasureFont.Size - 1 > 0)
						{
							MeasureFont = new Font(font.FontFamily, MeasureFont.Size - 1, font.Style, GraphicsUnit.Pixel);
						}
						else
						{
							return MeasureFont;
						}

						//测量输出字符串所需要的矩形空间
						stringSize = graphics.MeasureString(text,
						                                    MeasureFont, bounds.Size,
						                                    stringFormat, out codepointsFitted, out linesFilled);
					}
					else
					{
						oldValue = MeasureFont.Size;
						break;
					}
				} while (true);
			}

			MeasureFont = new Font(font.FontFamily, oldValue, font.Style, GraphicsUnit.Pixel);

			return MeasureFont;
		}

		#region Nested type: CHARRANGE

		[StructLayout(LayoutKind.Sequential)]
		private struct CHARRANGE
		{
			public int cpMax; //Last character of range (-1 for end of doc)
			public int cpMin; //First character of range (0 for start of doc)
		}

		#endregion

		#region Nested type: FORMATRANGE

		[StructLayout(LayoutKind.Sequential)]
		private struct FORMATRANGE
		{
			public CHARRANGE chrg; //Range of text to draw (see earlier declaration)
			public IntPtr hdc; //Actual DC to draw on
			public IntPtr hdcTarget; //Target DC for determining text formatting
			public RECT rc; //Region of the DC to draw to (in twips)
			public RECT rcPage; //Region of the whole DC (page size) (in twips)
		}

		#endregion

		#region Nested type: RECT

		[StructLayout(LayoutKind.Sequential)]
		private struct RECT
		{
			public int Bottom;
			public int Left;
			public int Right;
			public int Top;
		}

		#endregion
	}
}