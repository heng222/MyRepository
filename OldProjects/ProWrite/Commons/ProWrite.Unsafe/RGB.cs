using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Unsafe
{
	public class RGB
	{
		/// <summary>
		/// Index of red component
		/// </summary>
		public const short R = 2;
		/// <summary>
		/// Index of green component
		/// </summary>
		public const short G = 1;
		/// <summary>
		/// Index of blue component
		/// </summary>
		public const short B = 0;

		/// <summary>
		/// Red component
		/// </summary>
		public byte Red;

		/// <summary>
		/// Green component
		/// </summary>
		public byte Green;

		/// <summary>
		/// Blue component
		/// </summary>
		public byte Blue;

		/// <summary>
		/// <see cref="System.Drawing.Color">Color</see> value of the class 
		/// </summary>
		public System.Drawing.Color Color
		{
			get { return System.Drawing.Color.FromArgb(Red, Green, Blue); }
			set
			{
				Red = value.R;
				Green = value.G;
				Blue = value.B;
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="RGB"/> class
		/// </summary>
		public RGB() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="RGB"/> class
		/// </summary>
		/// 
		/// <param name="red">Red component</param>
		/// <param name="green">Green component</param>
		/// <param name="blue">Blue component</param>
		/// 
		public RGB(byte red, byte green, byte blue)
		{
			this.Red = red;
			this.Green = green;
			this.Blue = blue;
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="RGB"/> class
		/// </summary>
		/// 
		/// <param name="color">Initialize from specified <see cref="System.Drawing.Color">color</see></param>
		/// 
		public RGB(System.Drawing.Color color)
		{
			this.Red = color.R;
			this.Green = color.G;
			this.Blue = color.B;
		}
	};
}
