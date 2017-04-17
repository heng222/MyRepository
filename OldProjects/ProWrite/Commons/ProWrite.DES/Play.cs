//---------------------------------------------------------------------
//
// File: Play.cs
//
// Description:
// 此类主要实现视频的播放与控制 
//
// Author: michael
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
//
//Modify history:   
//  michael  2008-6-27 修改内容：修改暂停和继续播放的功能
//  michael  2008-7-18 修改内容：修改PLAYLIST中单个MESSAGE可以循环播放的功能
//---------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Data;
using System.Windows.Forms;
using ProWrite.Core;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Entity.DES;

namespace ProWrite.DES
{
	/// <summary>
	/// 实现视频播放和控制
	/// </summary>
    public class Play : DisposableObject
	{
		public event EventHandler PlayEvent = null;
		public event EventHandler PlayListCompleted = null;
		public event EventHandler PlayCompleted = null;

		private DESCombine des;
		private VideoLayerCollection[] dsArr;
        private VideoLayerCollection ds;
		private PlayState PlayState = PlayState.Stop;
		private DESVideoCallBack pVideo = null;
		private List<Layer> DynamicTextDS;
		private Control hWin;
		private TrackBar m_PlayBar;
        private Label m_MediaTime;
		private int curNum = 0;
        private long PlayLength = 0;
        private long curLength = 0;
        private Size MoveSize = Size.Empty;

		/// <summary>
		/// 构造和初始播放视频的数据
		/// </summary>
		/// <param name="ds"></param>
		/// <param name="myWin"></param>
		public Play(VideoLayerCollection myDS, DESVideoCallBack pVideoCallback, Control myWin)
		{
			hWin = myWin;
            ds = myDS;
			pVideo = pVideoCallback;
			ds.Sort(new SortComparer<Layer>("Level", false));
			des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, hWin.Width, hWin.Height,ds);
			DynamicTextDS = ds.FindAll(DynamicTextLayer);
		}

        public Play(VideoLayerCollection myDS, Size VideoSize)
        {
            ds = myDS;
            MoveSize = VideoSize;
            ds.Sort(new SortComparer<Layer>("Level", false));
            des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, MoveSize.Width, MoveSize.Height, ds);
            DynamicTextDS = ds.FindAll(DynamicTextLayer);
        }

		/// <summary>
		/// 构造和初始PLAYLIST的数据
		/// </summary>
		/// <param name="myDS"></param>
		/// <param name="myWin"></param>
		public Play(VideoLayerCollection[] myDS, System.Windows.Forms.TrackBar PlayBar,System.Windows.Forms.Label pMediaTime, Control myWin)
		{
			hWin = myWin;
			m_PlayBar = PlayBar;
            m_MediaTime = pMediaTime;
			dsArr = myDS;
		}

        ~Play()
		{
			Dispose();
		}

		/// <summary>
		///  Get Current Play Message SeqID
		/// </summary>
		public int SeqID
		{
			get
			{
				return curNum;
			}
		}

		/// <summary>
		///  Get Current Play State
		/// </summary>
		public PlayState CurentState
		{
			get
			{
				return PlayState;
			}
		}

		/// <summary>
		///  Run Message
		/// </summary>
		public void Run()
		{
			try
			{
				if (PlayCompleted != null)
					des.Completed += new EventHandler(PlayCompleted);
                des.RenderToFrame(hWin, pVideo, null, DynamicTextDS, new DsRect(new Rectangle(0, 0, ds.VideoSize.Width, ds.VideoSize.Height)), 0, ds.PlayLength);
				des.StartRendering();
				PlayState = PlayState.Run;
			}
			catch
			{
				des.Dispose();
				des = null;
			}
		}

		/// <summary>
		///  Run PlayList
		/// </summary>
		public void RunList()
        {
			Control.CheckForIllegalCrossThreadCalls = false;
			Thread th = new Thread(new ThreadStart(StartPlay));
			th.Name = "play list";
			th.Start();
		}

		/// <summary>
		///  Start PlayList
		/// </summary>
		private void StartPlay()
		{
			EventArgs ca = new EventArgs();
			int RunTime = 0;
			curNum = 0;
			PlayState = PlayState.Next;
			while (curNum >= 0 && curNum < dsArr.Length)
			{
				if (PlayState == PlayState.Stop)
				{
					if (des != null)
					{
						des.Cancel();
					}
					break;
				}

				if (PlayState == PlayState.Next)
				{
					dsArr[curNum].Sort(new SortComparer<Layer>("Level", false));
					des = new DESCombine(DESConsts.FPS, DESConsts.BitCount, hWin.Width, hWin.Height,dsArr[curNum]);
					DynamicTextDS = dsArr[curNum].FindAll(DynamicTextLayer);
					des.Completed += new EventHandler(Completed);
                    pVideo = new DESVideoCallBack(RunTime, m_PlayBar, m_MediaTime);
                    des.RenderToFrame(hWin, pVideo, null, DynamicTextDS, DsRect.FromRectangle(hWin.ClientRectangle), 0, dsArr[curNum].PlayLength);
					des.StartRendering();
					PlayState = PlayState.Run;
					PlayLength = DESHelper.FormatTime(dsArr[curNum].PlayLength);
				}
				else
				{
					if (PlayState == PlayState.Run)
						curLength += 1000000;
					if (curLength >= PlayLength)
					{
						RunTime += (int)dsArr[curNum].PlayLength;
						curNum++;
						curLength = 0;
						PlayState = PlayState.Next;
						if (curNum == dsArr.Length)
						{
							PlayState = PlayState.Stop;
						}
						if (des != null)
						{
							des.Stop();
						}
					}
					Thread.Sleep(100);
				}
			}

			if (des != null)
				des.Cancel();
			hWin.Refresh();
			if (PlayListCompleted != null)
				PlayListCompleted(this, ca);
		}

		/// <summary>
		///  Pause Play
		/// </summary>
		public void Pause()
		{
			try
			{
				if (des != null)
				{
					des.Pause();
				}
				PlayState = PlayState.Pause;
			}
			catch
			{
				PlayState = PlayState.Stop;
                Dispose();
			}
		}

		/// <summary>
		///  Stop Play
		/// </summary>
		public void Stop()
		{
			try
			{
				PlayState = PlayState.Stop;
                if (des != null)
                {
                    des.Cancel();
                }
			}
			catch
			{
				PlayState = PlayState.Stop;
                Dispose();
			}
		}

		/// <summary>
		///  continue Play
		/// </summary>
		public void ContinueRun()
		{
			try
			{
				PlayState = PlayState.Run;
				if (des != null)
				{
					des.Run();
				}
			}
			catch
			{
				PlayState = PlayState.Stop;
                Dispose();
			}
		}

		/// <summary>
		///  Run Next Message
		/// </summary>
		public void RunNext(int messageNum)
		{
			try
			{
				if (messageNum >= 0 && messageNum < dsArr.Length)
				{
					if (des != null)
						des.Stop();
					curNum = messageNum;
					curLength = 0;
					PlayState = PlayState.Next;
				}
			}
			catch
			{
				PlayState = PlayState.Stop;
                Dispose();
			}
		}

		/// <summary>
		///  Run previous Message
		/// </summary>
		public void RunPrev(int messageNum)
		{
			try
			{
				if (messageNum >= 0 && messageNum < dsArr.Length)
				{
					if (des != null)
						des.Stop();
					curNum = messageNum;
					curLength = 0;
					PlayState = PlayState.Next;
				}
			}
			catch
			{
				PlayState = PlayState.Stop;
                Dispose();
			}
		}

		/// <summary>
		/// PlayList播放完后触发此完成事件
		/// </summary>
		/// <param name="o"></param>
		/// <param name="e"></param>
		private void Completed(object o, System.EventArgs e)
		{
			CompletedArgs ca = e as CompletedArgs;
			if (curNum == dsArr.Length)
			{
				PlayState = PlayState.Stop;
			}
			else
			{
				PlayState = PlayState.Next;
			}
			GC.Collect(); GC.WaitForPendingFinalizers();
		}

		/// <summary>
		/// 当输出视频结束后触发此完成事件
		/// </summary>
		/// <param name="o"></param>
		/// <param name="e"></param>
		private void OutCompleted(object o, System.EventArgs e)
		{
			CompletedArgs ca = e as CompletedArgs;
            PlayState = PlayState.Stop;
			if (des != null)
				des.Dispose();
			des = null;
			GC.Collect(); GC.WaitForPendingFinalizers();
		}

		/// <summary>
		///  Set Play Screen Model
		/// </summary>
        public void ResizeVideoWindow(Size s)
		{
			if (des != null)
			{
                des.ResizeVideoWindow(s);
			}
		}

		/// <summary>
		/// 设置视频播放的起点时间
		/// </summary>
		/// <param name="curTime"></param>
		public void SetCurrentPosition(double lTime)
		{
			if (des != null)
			{
				des.put_CurrentPosition(lTime);
			}
		}

		/// <summary>
		/// 将视频中的一个片段输出成视频文件
		/// </summary>
		/// <param name="filename"></param>
        public bool OutputVideo(string filename, long start, long end)
		{
			try
			{
                bool result = false;

                if (MoveSize == Size.Empty)
                    return false;
				des.Completed += new EventHandler(OutCompleted);
				IBaseFilter ibfVideoCompressor = GetVideoCompressor("Indeo?video 5.10 Compression Filter");
                des.RenderToVideo(MediaSubType.Mpeg2Video, filename, ibfVideoCompressor, null, null, null, DynamicTextDS, start, end, MoveSize);
				des.StartRendering();
                PlayState = PlayState.Run;
                while (PlayState == PlayState.Run)
                {
                    Thread.Sleep(100);
                }
                if (System.IO.File.Exists(filename))
                    result = true;
                return result;
			}
			catch
			{
                if (des != null)
                {
                    PlayState = PlayState.Stop;
                    des.Dispose();
                    des = null;
                }
                return false;
			}
		}

		/// <summary>
		/// 在视频播放时并按下暂停按钮，进行视频截图
		/// </summary>
		/// <param name="FileName"></param>
		/// <param name="ImgFormat"></param>
		public Image GetImage()
		{
			Image img = null;
			if (des != null && PlayState == PlayState.Pause)
				img = des.GetImage();
			return img;
		}

		/// <summary>
		/// 指定时间来截取视频中的图片
		/// </summary>
		/// <param name="FileName"></param>
		/// <param name="ImgFormat"></param>
		/// <param name="lTime"></param>
		public Image GetImage(double lTime)
		{
			Image img = null;
			int MaxCount = lTime <= 0 ? DESConsts.BitCount : (int)lTime * DESConsts.BitCount;
            
			try
			{
				Panel pnl = new Panel();
				pVideo = new DESVideoCallBack();
				pnl.Width = this.hWin.Width;
				pnl.Height = this.hWin.Height;
                des.RenderToFrame(pnl, pVideo, null, DynamicTextDS, DsRect.FromRectangle(hWin.ClientRectangle), 0, ds.PlayLength);
				des.StartRendering();
				des.put_CurrentPosition(lTime);
				while (pVideo.m_FrameCount < MaxCount)
				{
					Thread.Sleep(100);
				}
				des.Pause();
				img = des.GetImage();
				des.Cancel();
			}
			catch
			{
				des.Cancel();
				des = null;
			}
			return img;
		}

		/// <summary>
		/// 根据名称返回相应的Filter
		/// </summary>
		/// <param name="sName"></param>
		private IBaseFilter GetVideoCompressor(string sName)
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

		/// <summary>
		/// 构造字幕层的查询条件
		/// </summary>
		/// <param name="sName"></param>
		private static bool DynamicTextLayer(Layer layer)
		{
			if (layer.Visible == true && layer.LayerType == LayerType.DynamicText)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

        /// <summary>
        /// 释放资源
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (des != null)
            {
                des.Dispose();
                des = null;
            }
            if (PlayEvent != null)
            {
                PlayEvent = null;
            }
            if (PlayListCompleted != null)
            {
                PlayListCompleted = null;
            }
            if (PlayCompleted != null)
            {
                PlayCompleted = null;
            }
            if (m_PlayBar != null)
            {
                m_PlayBar = null;
            }
            if (m_MediaTime != null)
            {
                m_MediaTime = null;
            }
            if (pVideo != null)
            {
                pVideo = null;
            }
            if (hWin != null)
            {
                hWin = null;
            }
        }
	}
}