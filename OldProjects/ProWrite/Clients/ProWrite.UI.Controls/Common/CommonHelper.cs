//---------------------------------------------------------------------
//
// File: CommonHelper.cs
//
// Description:
// Helper 
//
// Author: Michael
//
// DateTime:2008-4-23 
//
// Modify history:
//      Jerry Xu 2008-6-23 all the methods in Common and Dataches were replaced with these methods in DataGate
//      Jerry Xu 2008-6-26 Rename GetCurrentSecondByListIndexForBackward to GetCurrentSecondByListIndexForNext
//      Jerry Xu 2008-6-26 Rename GetCurrentSecondByListIndexForForward to GetCurrentSecondByListIndexForPrevious
//      Jerry Xu 2008-6-26 Resource
//      Jerry Xu 2008-6-26 PlayListProperty to PlayListsInfo
//      Jerry Xu 2008-6-26 PlayList and PlayLists to PlayListsInfo
//      Jerry Xu 2008-6-27 Log 
//      Jerry Xu 2008-6-28 Add the method of GetPlayListProperty
//      Jerry Xu 2008-6-30 Method's parameters's type is the same to their fields's type
//      Jerry Xu 2008-6-30 if the Method's return value is array then list
//      Jerry Xu 2008-7-1  Record the system exception to the log  
//      Jerry Xu 2008-7-1  Delete the method of GetPlayListProperty
//      Jerry Xu 2008-7-1  Move all methods in "/ProWriteNew/Clients/ProWrite.UI.Controls/PlayLists/CommonComde.cs" to
//          "/ProWriteNew/Clients/ProWrite.UI.Common/Helper.cs", then change method to static,then change their references 
//          these methods include:ConvertTimeToPixel,ConvertPixelToTime,ConvertLabelTimeToPixel,ConvertPixelToLabelTime,ConvertLabelTimeToTime,ConvertLabelTimeToSecond,ConvertTimeToSecond
//      Jerry Xu 2008-7-1  Move methods of GetCurrentSecondByListIndexForPrevious and GetCurrentSecondByListIndexForNext to "/ProWriteNew/Clients/ProWrite.UI.Controls/PlayLists/PlayListsBar.cs"
//      Jerry Xu 2008-7-7  Add the method of ConvertTimeToLengthText.
//      Jerry Xu 2008-7-9  ConvertTimeToLengthText's parameter pTime's type from long to type.
//      Jerry Xu 2009-1-4  Add method:IsVideoFile(string fileName)
//      Jerry Xu 2009-3-25 Update method:IsShowOpenDialog
//      Jerry Xu 2009-3-31 Update method:LibraryIsSaved(MemoryLibraryItem item)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Collections;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
using System.Reflection;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using ProWrite.Resources;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.DES;

namespace ProWrite.UI.Controls.Common
{

	/// <summary>
	/// Time£º2008-4-23
	/// Author£ºMichael
	/// Function£ºThis Class Offer All System Method,For example Format String.
	/// Update£º
	/// </summary>
	public sealed class CommonHelper
	{
		/// <summary>
		/// Time:2008-6-23
		/// Author:michael
		/// Function: Format Time in order to timeline use
		/// </summary>
		/// <param name="m_Second"></param>
		public static long FormatTime(long m_Second)
		{
			return Convert.ToInt64(Convert.ToDouble(m_Second) * DESConsts.UNITS);
		}

        public static string FormatTimeToMinute(long m_Second)
        {
            string m = (m_Second / 60) >= 10 ? (m_Second / 60).ToString() : "0" + (m_Second / 60);
            string s = (m_Second % 60) >= 10 ? (m_Second % 60).ToString() : "0" + (m_Second % 60);
            return m + ":" + s;
        }
        
		/// <summary>
		/// Time:2008-6-23
		/// Author:michael
		/// Function: Return the length of the media file
		/// </summary>
		/// <param name="m_FileName"></param>
		public static long GetMediaLength(string m_FileName)
		{
			int hr;
			double d;
			long i;
			try
			{
				IMediaDet imd = (IMediaDet)new MediaDet();
				// Set the name
				hr = imd.put_Filename(m_FileName);
				DESError.ThrowExceptionForHR(hr);
				// Read from stream zero
				hr = imd.put_CurrentStream(0);
				DESError.ThrowExceptionForHR(hr);
				// Get the length in seconds
				hr = imd.get_StreamLength(out d);
				DESError.ThrowExceptionForHR(hr);
				Marshal.ReleaseComObject(imd);
				// Convert to UNITS
				i = (long)(d * DESConsts.UNITS);
			}
			catch
			{
				i = 0;
			}
			return i;
		}

		/// <summary>
		/// Time:2008-8-15
		/// Author:michael
		/// Function: Check Video Source
		/// </summary>
		/// <param name="m_FileName"></param>
		public static bool IsVideoSource(string m_FileName, Guid MediaType)
		{
			bool result = false;
			try
			{
				int hr;
				Guid m_Type;
				IMediaDet imd = (IMediaDet)new MediaDet();
				hr = imd.put_Filename(m_FileName);
				hr = imd.get_StreamType(out m_Type);
				if (m_Type == MediaType)
					result = true;
			}
			catch
			{
				result = false;
			}
			return result;
		}

        /// <summary>
        /// Time:2008-8-15
        /// Author:michael
        /// Function: Check Video file valid
        /// </summary>
        /// <param name="m_FileName"></param>
        public static bool IsVideoSource(string fileName)
		{
			bool result = false;
			try
			{
				int hr;
				Guid m_Type;
				IMediaDet imd = (IMediaDet)new MediaDet();
				hr = imd.put_Filename(fileName);
				hr = imd.get_StreamType(out m_Type);
				if (m_Type != Guid.Empty)
					result = true;
			}
			catch
			{
				result = false;
			}
			if (!result)
			{
				MsgBox.Warning("Invalid format file");
			}
			return result;
		}

        /// <summary>
        /// Function: Check Video file valid
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4
        /// </summary>
        /// <param name="fileName">file name</param>
        public static bool IsVideoFile(string fileName)
        {
            bool result = false;
            try
            {
                int hr;
                Guid m_Type;
                IMediaDet imd = (IMediaDet)new MediaDet();
                hr = imd.put_Filename(fileName);
                hr = imd.get_StreamType(out m_Type);
                if (m_Type != Guid.Empty)
                    result = true;
            }
            catch
            {
                result = false;
            }
            return result;
        }

        public static void GetImageFromMedia(string mediaFile,string outImageFile,double time )
        {
            int hr;
            IMediaDet imd = (IMediaDet)new MediaDet();
            try
            {
                int width = 200;
                int height = 200;
                // Set the name
                hr = imd.put_Filename(mediaFile);
                DESError.ThrowExceptionForHR(hr);
                // Read from stream to get video size
                AMMediaType mediaType = new AMMediaType();
                imd.get_StreamMediaType(mediaType);
                VideoInfoHeader infoHeader = (VideoInfoHeader)Marshal.PtrToStructure(mediaType.formatPtr, typeof(VideoInfoHeader));
                width = infoHeader.BmiHeader.Width;
                height = infoHeader.BmiHeader.Height;
                // Get the length in seconds
                hr = imd.WriteBitmapBits(time, width, height, outImageFile);
                DESError.ThrowExceptionForHR(hr);
                Marshal.ReleaseComObject(imd);
            }
            catch
            {
                Marshal.ReleaseComObject(imd);
            }
        }

		/// <summary>
		/// Add Parameter to Effect
		/// </summary>
		public static void AddParameter(IPropertySetter ipro, string parName, object parValue)
		{
			DexterParam param;
			DexterValue[] value;

			param = new DexterParam();
			value = new DexterValue[1];
			param.Name = parName;
			param.dispID = 0;
			param.nValues = 1;
			value[0].v = parValue;
			value[0].rt = 0;
			value[0].dwInterp = Dexterf.Jump;
			ipro.AddProp(param, value);
		}

		/// <summary>
		/// Time:2008-5-23
		/// Author:michael
		/// Function: Create a video media type from a few parameters
		/// </summary>
		/// <param name="BitCount">Bits per pixel (16, 24, 32)</param>
		/// <param name="Width">Video width</param>
		/// <param name="Height">Video height</param>
		/// <returns>The constructed AMMediaType</returns>
		public static AMMediaType GetVideoMediaType(short BitCount, int Width, int Height)
		{
			Guid mediaSubType;
			AMMediaType VideoGroupType = new AMMediaType();

			// Calculate the SubType from the Bit count
			switch (BitCount)
			{
				case 16:
					mediaSubType = MediaSubType.RGB555;
					break;
				case 24:
					mediaSubType = MediaSubType.RGB24;
					break;
				case 32:
					mediaSubType = MediaSubType.ARGB32;
					break;
				default:
					throw new Exception("Unrecognized bit format");
			}

			VideoGroupType.majorType = MediaType.Video;
			VideoGroupType.subType = mediaSubType;
			VideoGroupType.formatType = FormatType.VideoInfo;
			VideoGroupType.fixedSizeSamples = true;

			VideoGroupType.formatSize = Marshal.SizeOf(typeof(VideoInfoHeader));
			VideoInfoHeader vif = new VideoInfoHeader();
			vif.BmiHeader = new BitmapInfoHeader();

			// The HEADER macro returns the BITMAPINFO within the VIDEOINFOHEADER
			vif.BmiHeader.Size = Marshal.SizeOf(typeof(BitmapInfoHeader));
			vif.BmiHeader.Compression = 0;
			vif.BmiHeader.BitCount = BitCount;
			vif.BmiHeader.Width = Width;
			vif.BmiHeader.Height = Height;
			vif.BmiHeader.Planes = 1;

			int iSampleSize = vif.BmiHeader.Width * vif.BmiHeader.Height * (vif.BmiHeader.BitCount / 8);
			vif.BmiHeader.ImageSize = iSampleSize;
			VideoGroupType.sampleSize = iSampleSize;
			VideoGroupType.formatPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(vif));

			Marshal.StructureToPtr(vif, VideoGroupType.formatPtr, false);

			return VideoGroupType;
		}

		
		/// <summary>
		/// Function:Convert time to pixel
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pTime">Time:string</param>
		/// <param name="pUnitWidth">Unit Width:int</param>
		/// <param name="pTick">Tick:int</param>
		/// <returns>Pixel:int</returns>
		public static int ConvertTimeToPixel(string pTime, int pUnitWidth, int pTick)
		{
			int iHour;//Hour
			int iMinute;//Minute
			int iSecond;//Second
			string tempTime;
			int tempUnitWidth;
			int tempTick;
			int rtnValue;//Return value            
			try
			{
				iHour = 0;
				iMinute = 0;
				iSecond = 0;
				tempTime = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Time default value
				tempUnitWidth = pUnitWidth;
				tempTick = pTick;
				rtnValue = 0;//Default return value

				tempTime = pTime;
				iHour = int.Parse(tempTime.Split(':')[0]);
				iMinute = int.Parse(tempTime.Split(':')[1]);
				iSecond = int.Parse(tempTime.Split(':')[2]);
				rtnValue = iSecond * tempUnitWidth + iMinute * tempTick * tempUnitWidth + iHour * tempTick * tempTick * tempUnitWidth;
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertTimeToPixelException), ex);
				return 0;
			}
		}

		/// <summary>
		/// Function:Convert pixel to time
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pPixel">Pixel:int</param>
		/// <param name="pUnitWidth">Unit Width:int</param>
		/// <param name="pTick">Tick:int</param>
		/// <returns>Time:string</returns>
		public static string ConvertPixelToTime(int pPixel, int pUnitWidth, int pTick)
		{
			string tempTime;
			int tempPixel;
			int tempUnitWidth;
			int tempTick;
			string rtnValue;//Return value
			try
			{
				tempTime = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Time default value
				tempPixel = 0;
				tempUnitWidth = pUnitWidth;
				tempTick = pTick;
				rtnValue = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default return value

				tempPixel = pPixel/pUnitWidth;
				if (tempPixel > 0)
				{
					//when time < 60 senconds
					if (tempPixel < tempTick)
					{
						if (tempPixel > 9)
						{
							tempTime = "0:00:" + tempPixel.ToString();
						}
						else
						{
							tempTime = "0:00:0" + tempPixel.ToString();
						}
					}
					else if (tempPixel < tempTick * tempTick)//when time < 60 minutes and >=1 minute
					{
						if (tempPixel / tempTick > 9)
						{
							int temp = tempPixel / tempTick;
							tempTime = "0:" + temp.ToString();
						}
						else
						{
							int temp = tempPixel / tempTick;
							tempTime = "0:0" + temp.ToString();
						}
						if (tempPixel % tempTick > 9)
						{
							int temp = tempPixel % tempTick;
							tempTime += ":" + temp.ToString();
						}
						else
						{
							int temp = tempPixel % tempTick;
							tempTime += ":0" + temp.ToString();
						}
					}
					else//when time >=60 minutes
					{
						int temptime = 0;
						temptime = tempPixel / (tempTick * tempTick);
						tempTime = temptime.ToString();
						if ((tempPixel % (tempTick * tempTick)) / tempTick > 9)
						{
							int temp = (tempPixel % (tempTick * tempTick)) / tempTick;
							tempTime += ":" + temp.ToString();
						}
						else
						{
							int temp = (tempPixel % (tempTick * tempTick)) / tempTick;
							tempTime += ":0" + temp.ToString();
						}
						if ((tempPixel % (tempTick * tempTick)) % tempTick > 9)
						{
							int temp = (tempPixel % (tempTick * tempTick)) % tempTick;
							tempTime += ":" + temp.ToString();
						}
						else
						{
							int temp = (tempPixel % (tempTick * tempTick)) % tempTick;
							tempTime += ":0" + temp.ToString();
						}
					}
					rtnValue = tempTime;
				}

                return DateTime.Parse(rtnValue).ToString("HH:mm:ss");
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertPixelToTimeException), ex);
				return Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);
			}
		}

		/// <summary>
		/// Function:Convert label time to pixel
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pTime">Time:string</param>
		/// <param name="pUnitWidth">Unit Width:int</param>
		/// <param name="pTick">Tick:int</param>
		/// <returns>Pixel:int</returns>
		public static int ConvertLabelTimeToPixel(string pTime, int pUnitWidth, int pTick)
		{
			int iHour;//Hour
			int iMinute;//Minute
			int iSecond;//Second
			string tempTime;
			int tempUnitWidth;
			int tempTick;
			int rtnValue;//Return value

			try
			{
				iHour = 0;
				iMinute = 0;
				iSecond = 0;
				tempTime = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default time value
				tempUnitWidth = pUnitWidth;
				tempTick = pTick;
				rtnValue = 0;//Default return value

				tempTime = pTime;
				iHour = int.Parse(tempTime.Split(';')[0]);
				iMinute = int.Parse(tempTime.Split(';')[1]);
				iSecond = int.Parse(tempTime.Split(';')[2]);
				rtnValue = iSecond * tempUnitWidth + iMinute * tempTick * tempUnitWidth + iHour * tempTick * tempTick * tempUnitWidth;
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertPixelToTimeException), ex);
				return 0;
			}
		}

		/// <summary>
		/// Function:Convert pixel to label time
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pPixel">Pixel:int</param>
		/// <param name="pUnitWidth">Unit Width:Tick</param>
		/// <param name="pTick">Tick:int</param>
		/// <returns>Time:string</returns>
		public static string ConvertPixelToLabelTime(int pPixel, int pUnitWidth, int pTick)
		{
			string tempTime;
			int tempPixel;
			int tempUnitWidth;
			int tempTick;
			string rtnValue;//Return value

			try
			{
				tempTime = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default time value
				tempPixel = 0;
				tempUnitWidth = pUnitWidth;
				tempTick = pTick;
				rtnValue = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default return value

				tempPixel = pPixel;
				int time = tempPixel / pUnitWidth;
				if (time > 0)
				{
					//when time < 60 senconds
					if (time < tempTick)
					{
						if (time > 9)
						{
							tempTime = "0;00;" + time.ToString();
						}
						else
						{
							tempTime = "0;00;0" + time.ToString();
						}
					}
					else if (time < tempTick * tempTick)//when time >= 60 senconds and < 60 minutes
					{
						if (time / tempTick > 9)
						{
							int temp = time / tempTick;
							tempTime = "0;" + temp.ToString();
						}
						else
						{
							int temp = time / tempTick;
							tempTime = "0;0" + temp.ToString();
						}
						if (time % tempTick > 9)
						{
							int temp = time % tempTick;
							tempTime += ";" + temp.ToString();
						}
						else
						{
							int temp = time % tempTick;
							tempTime += ";0" + temp.ToString();
						}
					}
					else//when time >= 60 minutes
					{
						int temptime = 0;
						temptime = time / (tempTick * tempTick);
						tempTime = temptime.ToString();
						if ((time % (tempTick * tempTick)) / tempTick > 9)
						{
							int temp = (time % (tempTick * tempTick)) / tempTick;
							tempTime += ";" + temp.ToString();
						}
						else
						{
							int temp = (time % (tempTick * tempTick)) / tempTick;
							tempTime += ";0" + temp.ToString();
						}
						if ((time % (tempTick * tempTick)) % tempTick > 9)
						{
							int temp = (tempPixel % (tempTick * tempTick)) % tempTick;
							tempTime += ";" + temp.ToString();
						}
						else
						{
							int temp = (time % (tempTick * tempTick)) % tempTick;
							tempTime += ";0" + temp.ToString();
						}
					}
					rtnValue = tempTime;
				}
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertPixelToLabelTimeException), ex);
				return Resource.GetString(Resource.Strings.PlayListLabelTimeDefaultText);
			}
		}

		/// <summary>
		/// Function:Convert label time to time
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pLabelTime">Label time:string</param>
		/// <returns>Time:string</returns>
		public static string ConvertLabelTimeToTime(string pLabelTime)
		{
			string rtnValue;//Return value
			try
			{
				rtnValue = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default return value
				if (int.Parse(pLabelTime.Split(';')[0]) > 9)
				{
					rtnValue = pLabelTime.Split(';')[0] + ":" + pLabelTime.Split(';')[1] + ":" + pLabelTime.Split(';')[2];
				}
				else
				{
					rtnValue = "0" + pLabelTime.Split(';')[0] + ":" + pLabelTime.Split(';')[1] + ":" + pLabelTime.Split(';')[2];
				}
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertLabelTimeToTimeException), ex);
				return Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);
			}
		}

		/// <summary>
		/// Function:Convert label time to second
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pLabelTime">Label time:string</param>
		/// <returns>Second:int</returns>
		public static int ConvertLabelTimeToSecond(string pLabelTime,int pTick)
		{
			int rtnValue;//Return value
			try
			{
				rtnValue = 0;//Default return value
				rtnValue = int.Parse(pLabelTime.Split(':')[0]) * 3600 + int.Parse(pLabelTime.Split(':')[1]) * 60 + int.Parse(pLabelTime.Split(':')[2]);
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertLabelTimeToSecondException), ex);
				return 0;
			}
		}

		/// <summary>
		/// Function:Convert time to second
		/// Author:Jerry Xu
		/// Date:2008-5-20
		/// </summary>
		/// <param name="pTime">Time:string</param>
		/// <returns>Second:int</returns>
		public static int ConvertTimeToSecond(string pTime)
		{
			int rtnValue;//Return value
			try
			{
				rtnValue = 0;//Default return value
				rtnValue = int.Parse(pTime.Split(':')[0]) * 3600 + int.Parse(pTime.Split(':')[1]) * 60 + int.Parse(pTime.Split(':')[2]);
				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertTimeToSecondException), ex);
				return 0;
			}
		}

		/// <summary>
		/// Function:Convert time to length text
		/// Author:Jerry Xu
		/// Date:2008-7-7
		/// </summary>
		/// <param name="pPixel">pTime:int</param>
		/// <param name="pTick">Tick:int</param>
		/// <returns>Time:string</returns>
		public static string ConvertTimeToLengthText(int pTime,int pTick)
		{
			int time = pTime;
			int tempTick = pTick;
			int tempHour;
			int tempMinute;
			int tempSecond;
			string rtnValue = string.Empty;//Return value

			try
			{
				tempTick = pTick;
                
				if (pTime > 0)
				{
					//Houre
					tempHour = time / (tempTick * tempTick);
					if (tempHour > 0)
					{
						if (tempHour > 9)
							rtnValue = tempHour.ToString();
						else
							rtnValue = "0" + tempHour.ToString();
						rtnValue += ":";
						//Minute
						tempMinute = (time % (tempTick * tempTick)) / 60;
						if (tempMinute > 9)
							rtnValue += tempMinute.ToString();
						else
							rtnValue += "0" + tempMinute.ToString();
						rtnValue += ":";
						//Second
						tempSecond = (time % (tempTick * tempTick)) % 60;
						if (tempSecond > 9)
							rtnValue += tempSecond.ToString();
						else
							rtnValue += "0" + tempSecond.ToString();
						rtnValue += ":";
					}
					else
					{
						//Houre
						rtnValue += "00:";
						//Minute
						tempMinute = (time % (tempTick * tempTick)) / 60;
						if (tempMinute > 9)
							rtnValue += tempMinute.ToString();
						else
							rtnValue += "0" + tempMinute.ToString();
						rtnValue += ":";
						//Second
						tempSecond = (time % (tempTick * tempTick)) % 60;
						if (tempSecond > 9)
							rtnValue += tempSecond.ToString();
						else
							rtnValue += "0" + tempSecond.ToString();
					}
				}
				else
				{
					rtnValue = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);//Default return value
				}

				return rtnValue;
			}
			catch (Exception ex)
			{
				DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListConvertPixelToLabelTimeException), ex);
				return Resource.GetString(Resource.Strings.PlayListLabelTimeDefaultText);
			}
		}

        public static Rectangle GetVirtualBoundsBySign(ShapeBase shape, Size signSize, int Zoom)
        {
            int width = signSize.Width / 4;
            int height = signSize.Height / 8;
            Point location = Point.Empty;

            decimal oldSizeRatio = decimal.Divide(shape.SignSize.Width, shape.SignSize.Height);
            decimal newSizeRatio = decimal.Divide(signSize.Width, signSize.Height);
            decimal tempZoom;
            int newWidth = 0, newHeight = 0;
            int widthOffset = 0, heightOffset = 0;
            if (oldSizeRatio <= newSizeRatio)
            {
                tempZoom = decimal.Divide(signSize.Height, shape.SignSize.Height);
                newWidth = (int)Math.Round(shape.SignSize.Width * tempZoom * Zoom);
                widthOffset = (int)Math.Round((double)(signSize.Width * Zoom - newWidth) / 2);
                location = new Point(widthOffset + (int)(shape.LocationX * tempZoom * Zoom), (int)(shape.LocationY * tempZoom * Zoom));
            }
            else
            {
                tempZoom = decimal.Divide(signSize.Width, shape.SignSize.Width);
                newHeight = (int)Math.Round(shape.SignSize.Height * tempZoom * Zoom);
                heightOffset = (int)Math.Round((double)(signSize.Height * Zoom - newHeight) / 2);
                location = new Point((int)(shape.LocationX * tempZoom * Zoom), heightOffset + (int)(shape.LocationY * tempZoom * Zoom));
            }
            width = (int)(shape.Width * tempZoom * Zoom);
            height = (int)(shape.Height * tempZoom * Zoom);
            return new Rectangle(location, new Size(width, height));
        }

        public static Rectangle GetRectangleBySign(Rectangle bounds,Size oldSignSize, Size newSignSize, int zoom)
        {
            int x, y, newWidth, newHeight, oldX, oldY, oldWidth, oldHeight = 1;
            oldWidth = bounds.Width / zoom;
            oldHeight = bounds.Height / zoom;
            oldX = bounds.X / zoom;
            oldY = bounds.Y / zoom;
            decimal wRate = decimal.Divide(oldSignSize.Width, newSignSize.Width);
            decimal hRate = decimal.Divide(oldSignSize.Height, newSignSize.Height);
            decimal Rate = 1;
            int widthOffset = 0, heightOffset = 0;

            if (wRate > hRate)
            {
                Rate = decimal.Divide(newSignSize.Width, oldSignSize.Width);
                Rate = Rate == 0 ? 1 : Rate;
                heightOffset = (newSignSize.Height - oldSignSize.Height) / 2;
            }
            else
            {
                Rate = decimal.Divide(newSignSize.Height, oldSignSize.Height);
                Rate = Rate == 0 ? 1 : Rate;
                widthOffset = (newSignSize.Width - oldSignSize.Width) / 2;
            }

            if (Rate >= 1)
            {
                x = (int)((oldX * Rate + widthOffset) * zoom);
                y = (int)((oldY * Rate + heightOffset) * zoom);
            }
            else
            {
                x = (int)((oldX * Rate) * zoom);
                y = (int)((oldY * Rate) * zoom);
            }

            newWidth = (int)(oldWidth * Rate * zoom);
            newHeight = (int)(oldHeight * Rate * zoom);
            return new Rectangle(x, y, newWidth, newHeight);
        }

        public static int FindMinWithDest(List<int> source, int dest)
        {
            int offset = int.MaxValue;
            int result = dest;
            foreach (int i in source)
            {
                if (Math.Abs(i - dest) < offset)
                {
                    result = i;
                    offset = Math.Abs(i - dest); 
                }
            }

            return result;
        }

        public static string ColorToString(Color _color)
        {
            string str = "0x";
            str += _color.A.ToString("X").Length > 1 ? _color.A.ToString("X") : "0" + _color.A.ToString("X");
            str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
            str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
            str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X");
            return str;
        }

        public static bool IsShowOpenDialog(LibraryType type)
        {
            bool canOpen = false;
            switch (type)
            {
                case LibraryType.Message:
                    canOpen = LibraryGroup.Current.Messages.Find(p => !p.IsOpen) != null;
                    break;
                case LibraryType.Playlist:
                    canOpen = LibraryGroup.Current.Playlists.Find(p => !p.IsOpen) != null;
                    break;
                case LibraryType.Schedule:
                    canOpen = LibraryGroup.Current.Schedulers.Find(p => !p.IsOpen) != null;
                    break;
            }
            return canOpen;
        }

        public static bool IsShowOpenDialog(string names)
        {
            switch (names)
            {
                case ModuleNames.Editor:
                    return LibraryGroup.Current.Messages.Find(p => !p.IsOpen) != null;
                case ModuleNames.Playlists:
                    return LibraryGroup.Current.Playlists.Find(p => !p.IsOpen) != null;
                case ModuleNames.Scheduler:
                    return LibraryGroup.Current.Schedulers.Find(p => !p.IsOpen) != null;
            }
            return false;
        }

        public static bool LibraryIsSaved(MemoryLibraryItem item)
        {
            if(item == null)
                return false;
            switch (item.Type)
            {
                case LibraryType.Message:
                    if((item as MessageInfo).Items==null || (item as MessageInfo).Items.Length==0)
                        return false;
                    break;
                case LibraryType.Playlist:
                    if ((item as PlaylistInfo).Items == null || (item as PlaylistInfo).Items.Length == 0)
                        return false;
                    break;
                case LibraryType.Schedule:
                    if ((item as SchedulerInfo).Items == null || (item as SchedulerInfo).Items.Length == 0)
                        return false;
                    break;
            }
            return true;
            
        }
        
	}
}