using System;
using System.Collections.Generic;
using System.Text;
using DirectShowLib;

namespace ProWrite.DES
{
	public class DESConsts
	{
		public const long MILLISECONDS = (1000);            // 10 ^ 3
		public const long NANOSECONDS = (1000000000);       // 10 ^ 9
		public const long UNITS = (NANOSECONDS / 100);      // 10 ^ 7
		public const double FPS = 30;
		public const short BitCount = 32;
		/// <summary>
		/// Event code indicating a video file has finished being processed
		/// </summary>
		public const EventCode EC_VideoFileComplete = (EventCode)0x8000;

		/// <summary>
		/// Event code indicating an audio file has finished being processed
		/// </summary>
		public const EventCode EC_AudioFileComplete = (EventCode)0x8001;

		//Effect GUID
        public static readonly Guid GUID_EF_WMTFX = new Guid("B4DC8DD9-2CC1-4081-9B2B-20D7030234EF");
        public static readonly Guid GUID_EF_Blur = new Guid("7312498D-E87A-11D1-81E0-0000F87557DB");
        public static readonly Guid GUID_EF_BrightNess = new Guid("5A20FD6F-F8FE-4a22-9EE7-307D72D09E6E");
        public static readonly Guid GUID_EF_Fade = new Guid("EC85D8F1-1C4E-46e4-A748-7AA04E7C0496");
		public static readonly Guid GUID_EF_Film = new Guid("ADEADEB8-E54B-11d1-9A72-0000F875EADE");
		public static readonly Guid GUID_EF_Filter = new Guid("E673DCF2-C316-4c6f-AA96-4E4DC6DC291E");
		public static readonly Guid GUID_EF_Pixelate = new Guid("4CCEA634-FBE0-11D1-906A-00C04FD9189D");
		public static readonly Guid GUID_EF_Sign = new Guid("5317AB02-6923-492d-ABFC-742B6194B739");
        public static readonly Guid GUID_EF_TextTravel = new Guid("0740D73C-0676-4AFC-BEB9-07F3AE6A8FA3");
        public static readonly Guid GUID_EF_Alpha = new Guid("506D89AE-909A-44f7-9444-ABD575896E35");

		//Transitions GUID
        public static readonly Guid GUID_TR_WMTFX = new Guid("C63344D8-70D3-4032-9B32-7A3CAD5091A5");
        public static readonly Guid GUID_TR_DxtKey = new Guid("C5B19592-145E-11D3-9F04-006008039E37");
        public static readonly Guid GUID_TR_Compositor = new Guid("BB44391D-6ABD-422F-9E2E-385C9DFF51FC");
        public static readonly Guid GUID_TR_ColorSource = new Guid("0cfdd070-581a-11d2-9ee6-006008039e37");
	}
}