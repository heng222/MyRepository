using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Data;
using System.Drawing.Imaging;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Entity.DES;

namespace ProWrite.DES
{
	/// <summary>
	/// A callback interface that can be implemented by callers to DESCombine 
	/// who wish to perform processing on video or audio frames.
	/// </summary>
	/// <remarks>
	/// Classes which implement this interfaces can be passed to <see cref="DESCombine.RenderToWindow"/>
	/// or <see cref="DESCombine.RenderToAVI"/>.  Each audio or video frame that is processed by DES
	/// will be passed to this callback which can perform additional processing.
	/// </remarks>
	public interface IDESCombineCB
	{
		/// <summary>
		/// Callback routine - called once for each audio or video frame
		/// </summary>
		/// <remarks>
		/// The buffer can be examined or modified.
		/// </remarks>
		/// <param name="sFileName">Filename currently being processed</param>
		/// <param name="SampleTime">Time stamp in seconds</param>
		/// <param name="pBuffer">Pointer to the buffer</param>
		/// <param name="BufferLen">Length of the buffer</param>
		/// <returns>Return S_OK if successful, or an HRESULT error code otherwise.  This value is sent as 
		/// the return value to ISampleGrabberCB::BufferCB</returns>
		int BufferCB(
			string sFileName,
			double SampleTime,
			System.IntPtr pBuffer,
			int BufferLen
			);
	}

	internal class DESCallback : ISampleGrabberCB
	{
		#region Data members
		List<Layer> MarqueeDS;

		/// Client callback routine
		/// </summary>
		protected IDESCombineCB m_pCallback;

		// The list of files
		protected DESGroup m_DESGroup;

		// The event sink (used to notify on end of file)
		protected IMediaEventSink m_pEventSink;

		// The event code to be used for end of file
		protected EventCode m_ec;

		// Holds the index into m_Files we are currently processing
		protected int m_iCurFile;

		// Which frame number we are currently processing
		protected int m_iCurFrame;

		// Maximum frame number for the current file
		protected int m_iMaxFrame;

		// File name of the currently processing file
		protected string m_CurFileName;

		//定义字幕的偏移数组
		protected float[] OffsetArrX;
		protected float[] OffsetArrY;
		#endregion

		/// <summary>
		/// 
		/// </summary>
		/// <param name="pDESGroup">Timeline DESGroup info</param>
		/// <param name="pCallback">Client callback</param>
		/// <param name="pEventSink">Event sync to call on file complete</param>
		/// <param name="ec">Event code to send on file completion</param>
		public DESCallback(
			DESGroup pDESGroup,
			IDESCombineCB pCallback,
			IMediaEventSink pEventSink,
			EventCode ec,
			List<Layer> myDS
			)
		{
			m_pCallback = pCallback;
			m_DESGroup = pDESGroup;
			m_pEventSink = pEventSink;
			m_ec = ec;
			MarqueeDS = myDS;
			m_iCurFrame = 0;
			m_iCurFile = 0;
			MediaFile mf = m_DESGroup.File(m_iCurFile);
			if (mf != null)
			{
				m_CurFileName = mf.FileName;
				m_iMaxFrame = mf.LengthInFrames;
			}
			else
			{
				m_CurFileName = null;
				m_iMaxFrame = int.MaxValue;
			}
			OffsetArrX = new float[MarqueeDS.Count];
			OffsetArrY = new float[MarqueeDS.Count];
		}


		// ISampleGrabberCB methods
		public int SampleCB(double SampleTime, IMediaSample pSample)
		{
			Marshal.ReleaseComObject(pSample);
			return 0;
		}
		public int BufferCB(double SampleTime, System.IntPtr pBuffer, int BufferLen)
		{
			// Call the client
			int iRet = 1;

			if (m_pCallback != null)
			{
				iRet = m_pCallback.BufferCB(m_CurFileName, SampleTime, pBuffer, BufferLen);
			}
			else
			{
				iRet = 0;
			}

			m_iCurFrame++;

			// Have we finished the current file?
			if (m_iCurFrame >= m_iMaxFrame)
			{
				// Send the notification
				int hr = m_pEventSink.Notify(m_ec, new IntPtr(m_iCurFile), new IntPtr(m_iCurFrame));

				// Find the next file
				m_iCurFile++;
				if (m_iCurFile < m_DESGroup.Count)
				{
					MediaFile mf = m_DESGroup.File(m_iCurFile);
					m_CurFileName = mf.FileName;
					m_iMaxFrame += mf.LengthInFrames;
				}
				else
				{
					// A failsafe
					m_iMaxFrame = int.MaxValue;
				}
			}

			int curTime = m_iCurFrame / (int)DESConsts.FPS;

            ////构造字幕输出数据
            //int i = 0;
            //foreach (Layer item in MarqueeDS)
            //{
            //    if (item.StartTime <= curTime && item.EndTime >= curTime)
            //    {
            //        SetupBitmap(item);
            //        DrawText(pBuffer, item,ref OffsetArrX[i],ref OffsetArrY[i]);
            //    }
            //    i++;
            //}
			return iRet;
		}

		#region add by michael==============================

		private int m_videoWidth;
		private int m_videoHeight;
		private int m_stride;
		private int m_Count;

		private Bitmap bitmapOverlay;
		private Font fontOverlay;
		private Font transparentFont;
		private SolidBrush transparentBrush;

		/// <summary> Read and store the properties </summary>
		public void SaveSizeInfo(ISampleGrabber sampGrabber,int Width,int Height)
		{
			int hr = 0;

			// Get the media type from the SampleGrabber
			AMMediaType media = DESHelper.GetVideoMediaType(DESConsts.BitCount, Width, Height);

			DsError.ThrowExceptionForHR(hr);

			if ((media.formatType != FormatType.VideoInfo) || (media.formatPtr == IntPtr.Zero))
			{
				throw new NotSupportedException("Unknown Grabber Media Format");
			}

			// Grab the size info
			VideoInfoHeader videoInfoHeader = (VideoInfoHeader)Marshal.PtrToStructure(media.formatPtr, typeof(VideoInfoHeader));
			m_videoWidth = videoInfoHeader.BmiHeader.Width;
			m_videoHeight = videoInfoHeader.BmiHeader.Height;
			m_stride = m_videoWidth * (videoInfoHeader.BmiHeader.BitCount / 8);

			DsUtils.FreeAMMediaType(media);
			media = null;
		}

		public void SetupBitmap(Layer layer)
		{
			//m_videoWidth = item.Rect.Width;
			//m_videoHeight = item.Rect.Height;
			//m_stride = m_videoWidth * (DESConsts.BitCount / 8);

            //int fSize = item.TextInfo.Size;
            //BitmapOverlay = new Bitmap(item.Rect.Width, item.Rect.Height, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            //fontOverlay = new Font(item.TextInfo.Font, fSize, item.TextInfo.FontStyle,System.Drawing.GraphicsUnit.Point);

            //// scale the font size in some portion to the video shape
            //fSize = 5 * (item.Rect.Width / 64);
            //if (fSize == 0)
            //    fSize = 13;
            //transparentFont = new Font(item.TextInfo.Font, fSize, item.TextInfo.FontStyle,System.Drawing.GraphicsUnit.Point);
            //transparentBrush = new SolidBrush(Color.FromArgb(96, 0, 0, 255));
		}

        //public void DrawText(IntPtr pBuffer, Layer item, ref float offsetX, ref float offsetY)
        //{
        //    Graphics g;
        //    SizeF d;
        //    float sLeft;
        //    float sTop;
        //    g = Graphics.FromImage(BitmapOverlay);
        //    g.Clear(System.Drawing.Color.Transparent);
        //    g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
        //    if (item.TextInfo.BackColor != Color.Empty)
        //    {
        //        Brush b = new SolidBrush(item.TextInfo.BackColor);
        //        g.FillRectangle(b, 0, 0, item.Rect.Width, item.Rect.Height);
        //    }
        //    // Prepare to put the specified string on the shape
        //    g.DrawRectangle(System.Drawing.Pens.Transparent, 0, 1, m_videoWidth-1, m_videoHeight-2);

        //    d = g.MeasureString(item.TextInfo.Text, fontOverlay);

        //    sLeft = DESHelper.GetOffsetX(item.Rect.Width, item, ref offsetX, item.TextInfo.RollRate, d.Width);
        //    sTop = DESHelper.GetOffsetY(item.Rect.Height, item, ref offsetY, item.TextInfo.RollRate, d.Height);
            
        //    using(Brush brush = new SolidBrush(item.TextInfo.Color))
        //        g.DrawString(item.TextInfo.Text, fontOverlay, brush,sLeft, sTop, System.Drawing.StringFormat.GenericTypographic);

        //    // need to flip the bitmap so it's the same orientation as the
        //    // video buffer
        //    BitmapOverlay.RotateFlip(RotateFlipType.RotateNoneFlipY);

        //    // Increment frame number.  Done this way, frame are zero indexed.
        //    Bitmap v;
        //    v = new Bitmap(m_videoWidth, m_videoHeight, m_stride, PixelFormat.Format32bppArgb, pBuffer);
        //    g = Graphics.FromImage(v);
        //    g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            
        //    // draw the overlay bitmap over the video's bitmap
        //    g.DrawImage(BitmapOverlay, item.Rect.X, (m_videoHeight - item.Rect.Y - item.Rect.Height), item.Rect.Width, item.Rect.Height);
        //    // dispose of the various objects
        //    g.Dispose();
        //    v.Dispose();

        //    m_Count++;
        //}
		#endregion
	}
}