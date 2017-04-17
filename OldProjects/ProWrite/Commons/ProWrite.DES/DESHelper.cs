//---------------------------------------------------------------------
//
// File: Helper.cs
//
// Description:
// Helper 
//
// Author: Michael
// Modify histories:
//      Jerry Xu 2009-3-12 Add method:PopulateDataBatchLoad(ShapeLayer[] layers),AppendLayer(ShapeLayer item)
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
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;

namespace ProWrite.DES
{
	/// <summary>
	/// Time：2008-4-23
	/// Author：Michael
	/// Function：This Class Offer All System Method,For example Format String.
	/// Update：
	/// </summary>
    public sealed class DESHelper
	{
        private static IDESPaintVisitor Visitor = new DESPaintVisitor();
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
		/// Function:Create new Grid shape
		/// Description:
		/// Author:michael
		/// Date:2008-10-27
		/// </summary>
		public static Image GetGridImage(int width, int height, Size size, Color backcolor)
		{
			Color linecolor = Color.FromArgb(100, 255 - backcolor.R, 255 - backcolor.G, 255 - backcolor.B);
			Bitmap img = new Bitmap(width, height);
            using(Pen pen = new Pen(linecolor))
            using (var g = Graphics.FromImage(img))
            {
                for (int x = 0; x <= width; x = x + size.Width)
                {
                    g.DrawLine(pen, new Point(x, 0), new Point(x, height));
                }
                for (int y = 0; y <= height; y = y + size.Width)
                {
                    g.DrawLine(pen, new Point(0, y), new Point(width, y));
                }
                g.DrawRectangle(pen, 0, 0, width, height);
            }
			return img;
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
			return result;
		}

		/// <summary>
		/// Time:2008-6-23
		/// Author:michael
		/// Function: Return Image from media file
		/// </summary>
		/// <param name="MediaFile"></param>
		/// <param name="OutImageFiler"></param>
		/// <param name="Width"></param>
		/// <param name="Height"></param>
		/// <param name="StreamTime"></param>
		public static void GetImageFromMedia(string MediaFile, string OutImageFile, int Width, int Height, double StreamTime)
		{
			int hr;
			IMediaDet imd = (IMediaDet)new MediaDet();
			try
			{
				// Set the name
				hr = imd.put_Filename(MediaFile);
				DESError.ThrowExceptionForHR(hr);
				// Read from stream zero
				hr = imd.put_CurrentStream(0);
				DESError.ThrowExceptionForHR(hr);
				// Get the length in seconds
				hr = imd.WriteBitmapBits(StreamTime, Width, Height, OutImageFile);
				DESError.ThrowExceptionForHR(hr);
				Marshal.ReleaseComObject(imd);
			}
			catch
			{
				OutImageFile = null;
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


        public static string ColorToString(Color _color)
        {
            string str = "0x";
            str += _color.A.ToString("X").Length > 1 ? _color.A.ToString("X") : "0" + _color.A.ToString("X");
            str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
            str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
            str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X"); 
            return str;
        }

        /// <summary>
        /// 根据名称返回相应的Filter
        /// </summary>
        /// <param name="sName"></param>
        public static IBaseFilter GetVideoCompressor(string sName)
        {
            IBaseFilter ibf = null;

            DsDevice[] dsd = DsDevice.GetDevicesOfCat(FilterCategory.VideoCompressorCategory);
            int x;

            for (x = 0; x < dsd.Length; x++)
            {
                if (dsd[x].Name == sName)
                {
                    Guid grf = typeof(IBaseFilter).GUID;
                    object o;
                    dsd[x].Mon.BindToObject(null, null, ref grf, out o);
                    ibf = o as IBaseFilter;
                    break;
                }
            }

            return ibf;
        }

        #region CreateVideo
        /// <summary>
        /// Time:2008-12-10
        /// Author:michael
        /// Function: Create Video
        /// </summary>
        /// <param name="mes"></param>
        /// <param name="fileurl"></param>
        public static bool CreateVideo(MessageInfo mes, string fileurl)
        {
            bool result = false;
            VideoLayerCollection video = null;
            video = PopulateData(mes.Items);
            video.BackColor = mes.BackColor;
            video.SignType = SignType.RGB;
            video.VideoSize = new Size(mes.Size.Width / mes.Zoom, mes.Size.Height / mes.Zoom);
            video.Name = mes.Name;
            video.Zoom = 1;
            video.PlayLength = mes.Length;
            video.ParentName = "";
            video.EmphasisEffect = mes.EmphasisEffect;
            Play MyPlay = new Play(video, video.VideoSize);
            result = MyPlay.OutputVideo(fileurl, 0, video.PlayLength);
            MyPlay.Dispose();
            return result;
        }

        private static ShapeLayer[] ReverseLayer(ShapeLayer[] items)
        {
            List<ShapeLayer> layers = new List<ShapeLayer>();
            foreach (ShapeLayer layer in items)
            {
                layers.Add(layer);
            }
            layers.Reverse();
            return layers.ToArray();
        }

        private static VideoLayerCollection PopulateData(ShapeLayer[] layers)
        {
            int level = 0;
            VideoLayerCollection videoLayers = new VideoLayerCollection();
            Layer Layer;

            long PlayLength = 0;
            if (layers == null || layers.Length < 1)
                return videoLayers;

            foreach (var item in layers)
            {
                if (item.IsVisible)
                {
                    if (item.Shape.Type != ShapeType.Temperature && item.Shape.Type != ShapeType.Time)
                    {
                        Layer = DESLayerConverter.Instance.Convert(item); //item.ToVideoLayer();
                        Layer.Level = level++;
                        videoLayers.Add(Layer);
                    }
                    if (item.EndTime > PlayLength)
                        PlayLength = (long)item.EndTime;
                }
            }
            
            videoLayers.PlayLength = PlayLength;
            return videoLayers;
        }
        #endregion

        #region Generate nail shape
        private VideoLayerCollection _videoLayers = new VideoLayerCollection();
        private short _level = 0;
        /// <summary>
        /// Function:Get VideoLayerCollection
        /// Description:
        /// Author:Kevin
        /// Date:2008-7-2
        /// </summary>
        /// <param name="layers">collection of layers</param>
        /// <returns>VideoLayerCollection</returns>
        public VideoLayerCollection PopulateDataBatchLoad(ShapeLayer[] layers)
        {
            _videoLayers = new VideoLayerCollection();
            long PlayLength = 0;
            if (layers == null || layers.Length < 1)
                return _videoLayers;

            _level = 0;

            foreach (ShapeLayer layer in layers)
            {
                if (layer.IsVisible)
                {
                    AppendLayer(layer);
                    if (layer.EndTime > PlayLength)
                        PlayLength = (long)layer.EndTime;
                }
            }

            //CheckMarquee();
            _videoLayers.PlayLength = PlayLength;
            return _videoLayers;
        }

        #region Append item
        /// <summary>
        /// Function:Append item
        /// Description:
        /// Author:Kevin
        /// Date:2008-7-2
        /// </summary>
        /// <param name="item">item</param>
        private void AppendLayer(ShapeLayer layer)
        {
            //layer.Accept(Visitor);
            Layer videoLayer = DESLayerConverter.Instance.Convert(layer);// layer.ToVideoLayer();
            if (videoLayer == null)
                return;

            videoLayer.Level = _level++;//(short)item.LayerIndex;
            _videoLayers.Add(videoLayer);
        }
        #endregion
        #endregion
    }
}