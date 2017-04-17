//---------------------------------------------------------------------
//
// File: Play.cs
//
// Description:
// 视频的播放引擎
//
// Author: michael
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
//
//Modify history:   
//  michael  2008-7-23 修改内容：增加设置播放起点时间的功能
//---------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using DirectShowLib;
using DirectShowLib.DES;
using log4net;
using ProWrite.Core;
using ProWrite.Entity.DES;
using DirectEncodeNET;

namespace ProWrite.DES
{
	/// <summary>Used by the <see cref="DESCombine.Completed"/> event.  
	/// Reports the event code that exited the graph.
	/// </summary>
	/// <remarks>Signals that all files have been rendered</remarks>
	public class CompletedArgs : System.EventArgs
	{
		/// <summary>The result of the rendering</summary>
		/// <remarks>
		/// This code will be a member of DirectShowLib.EventCode.  Typically it 
		/// will be EventCode.Complete, EventCode.ErrorAbort or EventCode.UserAbort.
		/// </remarks>
		public EventCode Result;

		/// <summary>
		/// Used to construct an instace of the class.
		/// </summary>
		/// <param name="ec"></param>
		internal CompletedArgs(EventCode ec)
		{
			Result = ec;
		}
	}

	/// <summary>
	/// Used by the <see cref="DESCombine.FileCompleted"/> event.  Reports 
	/// when a file has completed processing.
	/// </summary>
	/// <remarks>
	/// To determine whether you are receiving a notification for an audio
	/// or video file completing, examine the <see cref="FileCompletedArgs.Type"/> property.  Also, when
	/// using the RenderToWindow, dropped frames can result in late or missed notifications.
	/// </remarks>
	public class FileCompletedArgs : System.EventArgs
	{
		/// <summary>
		/// Type of the file that has completed (audio/video)
		/// </summary>
		public enum FileType
		{
			/// <summary>
			/// Type is video
			/// </summary>
			Video,

			/// <summary>
			/// Type is audio
			/// </summary>
			Audio
		}

		/// <summary>
		/// The file name that just completed
		/// </summary>
		/// <remarks>
		/// Use the <see cref="FileCompletedArgs.Type"/> to determine whether this is a video
		/// or audio file.
		/// </remarks>
		public string FileName;

		/// <summary>
		/// The type (audio/video) of file
		/// </summary>
		public FileType Type;

		/// <summary>
		/// Used to construct an instance of the class.
		/// </summary>
		/// <param name="sFilename">Filename that has been completed</param>
		/// <param name="eType">Type of the file (audio/video)</param>
		internal FileCompletedArgs(string sFilename, FileType eType)
		{
			FileName = sFilename;
			Type = eType;
		}
	}

    public class DESCombine : DisposableObject
	{
		#region Data Members
		// How much of the process of rendering the class has been completed
		volatile private ClassState m_State;
		private int m_VideoWidth;
		private int m_VideoHeight;
		private IBaseFilter vmr = null;
		private IVMRWindowlessControl windowlessCtrl = null;
        private IVideoWindow videoWindow = null;
        private IBaseFilter mpegEncodeFilter = null;
        private IBaseFilter fileWriter = null;

        private static readonly ILog log = LogManager.GetLogger(typeof(DESCombine));

		/// <summary>
		/// Status of the video timeline
		/// </summary>
		private DESGroup m_Video;

		/// <summary>
		/// Status of the audio timeline
		/// </summary>
		private DESGroup m_Audio;

		/// <summary>
		/// Pointer to the timeline containing the audio and video tracks
		/// </summary>
		private IAMTimeline m_pTimeline;

		/// <summary>
		/// IGraphBuilder object for the timeline
		/// </summary>
		private IGraphBuilder m_pGraph;

		/// <summary>
		/// Media control interface from m_pGraph
		/// </summary>
		private IMediaControl m_pControl;

		private IMediaPosition m_pPosition = null;
		/// <summary>
		/// Event code indicating a video file has finished being processed
		/// </summary>
		internal const EventCode EC_VideoFileComplete = (EventCode)0x8000;

		/// <summary>
		/// Event code indicating an audio file has finished being processed
		/// </summary>
		internal const EventCode EC_AudioFileComplete = (EventCode)0x8001;

		/// <summary>
		/// The engine to process the timeline (can't be released
		/// until the graph processing is complete)
		/// </summary>
		private IRenderEngine m_pRenderEngine;
		/// <summary>
		/// The engine to process the timeline (can't be released
		/// until the graph processing is complete)
		/// </summary>
#if DEBUG
		/// <summary>
		/// Used when adding the graph to the Running Object Table.
		/// This allows the graph to be inspected from GraphEdit using
		/// File/Connect
		/// </summary>
		private DsROTEntry m_rot;
#endif

		#endregion

		#region Dispose
		/// <summary>
		/// Release resources used by the class.
		/// </summary>
		/// <remarks>May fire events, so do not call from Form.Dispose().</remarks>
        protected override void Dispose(bool disposing)
		{
            try
            {
                Completed = null;
                FileCompleted = null;
               
                if (m_Video != null)
                {
                    m_Video.Dispose();
                    m_Video = null;
                }
                if (m_Audio != null)
                {
                    m_Audio.Dispose();
                    m_Audio = null;
                }

                if (m_pTimeline != null)
                {
                    Marshal.ReleaseComObject(m_pTimeline);
                    m_pTimeline = null;
                }

                if (m_pRenderEngine != null)
                {
                    Marshal.ReleaseComObject(m_pRenderEngine);
                    m_pRenderEngine = null;
                }
                if (vmr != null)
                {
                    Marshal.ReleaseComObject(vmr);
                    vmr = null;
                }

                if (windowlessCtrl != null)
                {
                    Marshal.ReleaseComObject(windowlessCtrl);
                    windowlessCtrl = null;
                }
#if DEBUG
                if (m_rot != null)
                {
                    m_rot.Dispose();
                    m_rot = null;
                }
#endif
                if (m_pControl != null)
                {
                    m_pControl.Stop();
                    m_pControl = null;
                }

                if (m_pGraph != null)
                {
                    if (mpegEncodeFilter != null)
                    {
                        m_pGraph.RemoveFilter(mpegEncodeFilter);
                        Marshal.ReleaseComObject(mpegEncodeFilter);
                        mpegEncodeFilter = null;
                    }
                    if (fileWriter != null)
                    {
                        m_pGraph.RemoveFilter(fileWriter);
                        Marshal.ReleaseComObject(fileWriter);
                        fileWriter = null;
                    }
                    Marshal.ReleaseComObject(m_pGraph);
                    m_pGraph = null;
                }
            }
            catch (Exception ex)
            {
                log.Error("DESCombine Dispose Exception:" + ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
		}
		#endregion

		#region User-defined Method
		public DESCombine(double FPS, short BitCount, int Width, int Height,VideoLayerCollection ds)
		{
			m_VideoWidth = Width;
			m_VideoHeight = Height;
			// Initialize the data members
			m_State =ClassState.Constructed;
			// Create the timeline
			m_pTimeline = (IAMTimeline)new AMTimeline();

			// Set the frames per second
			int hr = m_pTimeline.SetDefaultFPS(FPS);
			DESError.ThrowExceptionForHR(hr);

			// Init the video group
            m_Video = new DESGroup(DESHelper.GetVideoMediaType(BitCount, Width, Height), m_pTimeline, ds, Width, Height);
			if (m_State > ClassState.FilesAdded)
				throw new Exception("Can't add files since rendering method already selected");
			m_Video.LoadSource(ds);
            m_pTimeline.SetInterestRange(0, DESHelper.FormatTime(ds.PlayLength));
			// Init the audio group
			//m_Audio = new Group(GetAudioMediaType(), m_pTimeline, FPS, myChunk);
			m_State =ClassState.FilesAdded;
		}

		/// <summary>
		/// Configure the graph to output the results to an AVI file.
		/// </summary>
		/// <param name="sOutputFile">File name for output (must not be null)</param>
		/// <param name="ibfVideoCompressor">IBaseFilter of a video compressor to use (or null for none).  
		/// Note that <b><i>no</i></b> configuration of this compressor is done by this method.  It merely adds it
		/// to the graph in the appropriate place.  Also, the pointer is not invalidated, so any configuration
		/// of the compressor that needs to be done after being added to the graph can still be done.</param>
		/// <param name="ibfAudioCompressor">IBaseFilter of an audio compressor to use (or null for none).
		/// Note that <b><i>no</i></b> configuration of this compressor is done by this method.  It merely adds it
		/// to the graph in the appropriate place.  Also, the pointer is not invalidated, so any configuration
		/// of the compressor that needs to be done after being added to the graph can still be done.</param>
		/// <param name="pVideoCallback">Callback routine to be called for each video frame or null for no callback</param>
		/// <param name="pAudioCallback">Callback routine to be called for each audio frame or null for no callback</param>
		/// <remarks>
		/// The callback routines are invoked once for each sample.  This allows for additional processing to
		/// be performed on the video or audio buffers.
		/// </remarks>
		public void RenderToAvi(
			Guid VideoType, string sOutputFile,
			IBaseFilter ibfVideoCompressor,
			IBaseFilter ibfAudioCompressor,
			IDESCombineCB pVideoCallback,
			IDESCombineCB pAudioCallback,
			List<Layer> MarqueeDS, long Start, long End)
		{
			int hr;
			IPin pPin;
			if (sOutputFile == null)
			{
				throw new Exception("Output file name cannot be null");
			}
			// Perform initialization common to all render routines
			if (Start > 0 && End > 0 && End > Start)
				RenderCommon(Start, End);
			else
				RenderCommon();

			// Contains useful routines for creating the graph
			ICaptureGraphBuilder2 icgb = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();
			try
			{
				hr = icgb.SetFiltergraph(m_pGraph);
				DESError.ThrowExceptionForHR(hr);
				// Create the file writer
				IBaseFilter pMux;
				IFileSinkFilter pFilter;
				hr = icgb.SetOutputFileName(MediaSubType.Avi, sOutputFile, out pMux, out pFilter);
				DESError.ThrowExceptionForHR(hr);
				// We don't need this, so let it go
				Marshal.ReleaseComObject(pFilter);
				try
				{
					int NumGroups;
					hr = m_pTimeline.GetGroupCount(out NumGroups);
					DESError.ThrowExceptionForHR(hr);
					// Walk the groups.  For this class, there is one group that 
					// contains all the video, and a second group for the audio.
					for (int i = 0; i < NumGroups; i++)
					{
						IAMTimelineObj pGroup;
						hr = m_pTimeline.GetGroup(out pGroup, i);
						DESError.ThrowExceptionForHR(hr);
						try
						{
							// Inform the graph we will be writing to disk (rather than previewing)
							IAMTimelineGroup pTLGroup = (IAMTimelineGroup)pGroup;
							hr = pTLGroup.SetPreviewMode(false);
							DESError.ThrowExceptionForHR(hr);
						}
						finally
						{
							Marshal.ReleaseComObject(pGroup);
						}

						// Get the IPin for the current group
						hr = m_pRenderEngine.GetGroupOutputPin(i, out pPin);
						DESError.ThrowExceptionForHR(hr);
						try
						{
							if (IsVideo(pPin))
							{
								// Create a sample grabber, add it to the graph and connect it all up
								DESCallback mcb = new DESCallback(m_Video, pVideoCallback, (IMediaEventSink)m_pGraph, EC_VideoFileComplete, MarqueeDS);
								RenderDESHelper(icgb, mcb, "Video", pPin, ibfVideoCompressor, pMux);
							}
							else
							{
								// Create a sample grabber, add it to the graph and connect it all up
								DESCallback mcb = new DESCallback(m_Audio, pAudioCallback, (IMediaEventSink)m_pGraph, EC_AudioFileComplete, MarqueeDS);
								RenderDESHelper(icgb, mcb, "Audio", pPin, ibfAudioCompressor, pMux);
							}
						}
						finally
						{
							Marshal.ReleaseComObject(pPin);
						}
					}
				}
				finally
				{
					Marshal.ReleaseComObject(pMux);
				}
			}
			finally
			{
				Marshal.ReleaseComObject(icgb);
			}
		}
        
        /// <summary>
        /// Configure the graph to output the results to an AVI file.
        /// </summary>
        /// <param name="sOutputFile">File name for output (must not be null)</param>
        /// <param name="ibfVideoCompressor">IBaseFilter of a video compressor to use (or null for none).  
        /// Note that <b><i>no</i></b> configuration of this compressor is done by this method.  It merely adds it
        /// to the graph in the appropriate place.  Also, the pointer is not invalidated, so any configuration
        /// of the compressor that needs to be done after being added to the graph can still be done.</param>
        /// <param name="ibfAudioCompressor">IBaseFilter of an audio compressor to use (or null for none).
        /// Note that <b><i>no</i></b> configuration of this compressor is done by this method.  It merely adds it
        /// to the graph in the appropriate place.  Also, the pointer is not invalidated, so any configuration
        /// of the compressor that needs to be done after being added to the graph can still be done.</param>
        /// <param name="pVideoCallback">Callback routine to be called for each video frame or null for no callback</param>
        /// <param name="pAudioCallback">Callback routine to be called for each audio frame or null for no callback</param>
        /// <remarks>
        /// The callback routines are invoked once for each sample.  This allows for additional processing to
        /// be performed on the video or audio buffers.
        /// </remarks>
        public void RenderToVideo(
            Guid VideoType, string sOutputFile,
            IBaseFilter ibfVideoCompressor,
            IBaseFilter ibfAudioCompressor,
            IDESCombineCB pVideoCallback,
            IDESCombineCB pAudioCallback,
            List<Layer> MarqueeDS, long Start, long End,Size MoveSize)
        {
            int hr;
            IPin pPin;
            if (sOutputFile == null)
            {
                throw new Exception("Output file name cannot be null");
            }
            // Perform initialization common to all render routines
            if (Start >= 0 && End > 0 && End > Start)
                RenderCommon(Start, End);
            else
                RenderCommon();

            // Contains useful routines for creating the graph
            ICaptureGraphBuilder2 icgb = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();
            try
            {
                hr = icgb.SetFiltergraph(m_pGraph);
                DESError.ThrowExceptionForHR(hr);
                IFileSinkFilter fileFilter;
                SetEncodeFilter(out mpegEncodeFilter, MoveSize);
                hr = m_pGraph.AddFilter(mpegEncodeFilter, "Standard MPEG Encoder");
                DESError.ThrowExceptionForHR(hr);
                fileWriter = (IBaseFilter)new FileWriter();
                fileFilter = (IFileSinkFilter)fileWriter;
                hr = fileFilter.SetFileName(sOutputFile, null);
                hr = m_pGraph.AddFilter(fileWriter, "File Writer Filter");
                DESError.ThrowExceptionForHR(hr);
                try
                {
                    int NumGroups;
                    hr = m_pTimeline.GetGroupCount(out NumGroups);
                    DESError.ThrowExceptionForHR(hr);
                    // Walk the groups.  For this class, there is one group that 
                    // contains all the video, and a second group for the audio.
                    for (int i = 0; i < NumGroups; i++)
                    {
                        IAMTimelineObj pGroup;
                        hr = m_pTimeline.GetGroup(out pGroup, i);
                        DESError.ThrowExceptionForHR(hr);
                        try
                        {
                            // Inform the graph we will be writing to disk (rather than previewing)
                            IAMTimelineGroup pTLGroup = (IAMTimelineGroup)pGroup;
                            hr = pTLGroup.SetPreviewMode(false);
                            DESError.ThrowExceptionForHR(hr);
                        }
                        finally
                        {
                            Marshal.ReleaseComObject(pGroup);
                        }

                        // Get the IPin for the current group
                        hr = m_pRenderEngine.GetGroupOutputPin(i, out pPin);
                        DESError.ThrowExceptionForHR(hr);
                        try
                        {
                            if (IsVideo(pPin))
                            {
                                vmr = (IBaseFilter)new VideoMixingRenderer();
                                ConfigureVMRInWindowlessMode(null, new DsRect(new Rectangle(0, 0, MoveSize.Width, MoveSize.Height)));
                                // Create a sample grabber, add it to the graph and connect it all up
                                DESCallback mcb = new DESCallback(m_Video, pVideoCallback, (IMediaEventSink)m_pGraph, EC_VideoFileComplete, MarqueeDS);
                                RenderDESHelper(icgb, mcb, "Video", pPin, ibfVideoCompressor, mpegEncodeFilter);
                            }
                            else
                            {
                                // Create a sample grabber, add it to the graph and connect it all up
                                DESCallback mcb = new DESCallback(m_Audio, pAudioCallback, (IMediaEventSink)m_pGraph, EC_AudioFileComplete, MarqueeDS);
                                RenderDESHelper(icgb, mcb, "Audio", pPin, ibfAudioCompressor, mpegEncodeFilter);
                            }
                            
                            hr = icgb.RenderStream(null, null, mpegEncodeFilter, null, fileWriter);
                            DESError.ThrowExceptionForHR(hr);
                        }
                        finally
                        {
                            Marshal.ReleaseComObject(pPin);
                        }
                    }
                }
                finally
                {
                    Marshal.ReleaseComObject(fileFilter);
                }
            }
            finally
            {
                Marshal.ReleaseComObject(icgb);
            }
        }

        private void SetEncodeFilter(out IBaseFilter mpegFilter,Size MoveSize)
        {
            byte cmd = 0;
            Guid guid = new Guid("CFD87339-C61F-46ca-B6A1-F87D6B96243E");
            Type comtype = Type.GetTypeFromCLSID(guid);
            mpegFilter = (IBaseFilter)Activator.CreateInstance(comtype);
            IStandardMpegEncoder pIMPEGEncoder = (IStandardMpegEncoder)mpegFilter;
            DirectEncodeNET.SystemsOutputFormat m_systemsFormat;
            DirectEncodeNET.Constraint m_constraint;
            m_systemsFormat = DirectEncodeNET.SystemsOutputFormat.SYSTEMSFORMAT_MP4;
            m_constraint = DirectEncodeNET.Constraint.CONSTRAINT_PAL;

            //registration---------
            pIMPEGEncoder.SetFilterLicenseKey("EFOFZ-SXFPC-PSTFP-EOAUP-GAXJL-CVIOX");
            pIMPEGEncoder.PassThruCmd("mpeg1|mpeg2|vkb", 0, 0, out cmd);
            long nMinNow = System.Environment.TickCount / (1000 * 60); if (nMinNow > 256) nMinNow = nMinNow % 256;
            cmd = (byte)nMinNow;
            pIMPEGEncoder.PassThruCmd("mpeg1|mpeg2|vkb", cmd, 0, out cmd);
            //---------------------------------
            pIMPEGEncoder.SelectFormat(m_systemsFormat, m_constraint);
            StandardMpegEncoderProfile profile;
            pIMPEGEncoder.GetSelectedProfile(out profile);
            profile.SetWidth(MoveSize.Width);
            profile.SetHeight(MoveSize.Height);
            profile.SetFramerate(29);
        }

        public void RegisterLibrary()
        {
            long cmd = StandardMpegEncoderDll.MediaFilePassThruCmd("rkb", null, 400);
            long nMinNow = System.Environment.TickCount / (1000 * 60);
            if (nMinNow > 255) nMinNow = nMinNow % 255;
            StandardMpegEncoderDll.MediaFilePassThruCmd("vkb", null, nMinNow);
            StandardMpegEncoderDll.MediaFilePassThruCmd("EFOFZ-SXFPC-PSTFP-EOAUP-GAXJL-CVIOX", null, 836);
        }

		public void RenderTimeline(IntPtr hWnd, IDESCombineCB pVideoCallback, IDESCombineCB pAudioCallback)
		{
			IRenderEngine m_pRenderEngine = (IRenderEngine)new RenderEngine();
			m_pRenderEngine.SetTimelineObject(m_pTimeline);
			m_pRenderEngine.ConnectFrontEnd();
			m_pRenderEngine.RenderOutputPins();
		}

		/// <summary>
		/// Configure the graph to output the results to a video window.
		/// add by zhouzg
		/// </summary>
		/// <remarks>
		/// The callback routines are invoked once for each sample.  This allows for additional processing to
		/// be performed on the video or audio buffers.
		/// </remarks>
		/// <param name="hWnd">Window handle to render to, or IntPtr.Zero to render to its own window</param>
		/// <param name="pVideoCallback">Callback routine to be called for each video frame or null for no callback</param>
		/// <param name="pAudioCallback">Callback routine to be called for each audio frame or null for no callback</param>
		public void RenderToWindow(System.Windows.Forms.Control hWin, IDESCombineCB pVideoCallback, IDESCombineCB pAudioCallback, List<Layer> MarqueeDS, DsRect rc)
		{
			int hr;
			IPin pPin;
			IVideoWindow pVidWindow;
			IAMTimelineObj pGroup;

			// Perform initialization common to all render routines
			RenderCommon();

			// Contains useful routines for creating the graph
			ICaptureGraphBuilder2 icgb = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();

			try
			{
				hr = icgb.SetFiltergraph(m_pGraph);
				DESError.ThrowExceptionForHR(hr);

				int NumGroups;
				hr = m_pTimeline.GetGroupCount(out NumGroups);
				DESError.ThrowExceptionForHR(hr);

				// Walk the groups.  For DESCombine, there is one group that 
				// contains all the video, and a second group for the audio.
				for (int i = 0; i < NumGroups; i++)
				{
					hr = m_pTimeline.GetGroup(out pGroup, i);
					DESError.ThrowExceptionForHR(hr);

					try
					{
						// Inform the graph we will be previewing (rather than writing to disk)
						IAMTimelineGroup pTLGroup = (IAMTimelineGroup)pGroup;
						hr = pTLGroup.SetPreviewMode(true);
						DESError.ThrowExceptionForHR(hr);
					}
					finally
					{
						// Release the group
						Marshal.ReleaseComObject(pGroup);
					}

					// Get the IPin for the current group
					hr = m_pRenderEngine.GetGroupOutputPin(i, out pPin);
					DESError.ThrowExceptionForHR(hr);

					try
					{
						// If this is the video pin
						if (IsVideo(pPin))
						{
							// Get a video renderer
							IBaseFilter ibfVideoRenderer = (IBaseFilter)new VideoRenderer();

							try
							{
								// Create a sample grabber, add it to the graph and connect it all up
								DESCallback mcb = new DESCallback(m_Video, pVideoCallback, (IMediaEventSink)m_pGraph, DESConsts.EC_VideoFileComplete, MarqueeDS);
								RenderWindowDESHelper(icgb, mcb, "Video", pPin, ibfVideoRenderer);
							}
							finally
							{
								Marshal.ReleaseComObject(ibfVideoRenderer);
							}
						}
						else
						{
							// Get an audio renderer
							IBaseFilter ibfAudioRenderer = (IBaseFilter)new AudioRender();

							try
							{
								// Create a sample grabber, add it to the graph and connect it all up
								DESCallback mcb = new DESCallback(m_Audio, pAudioCallback, (IMediaEventSink)m_pGraph, DESConsts.EC_AudioFileComplete, MarqueeDS);
								RenderWindowDESHelper(icgb, mcb, "Audio", pPin, ibfAudioRenderer);
							}
							finally
							{
								Marshal.ReleaseComObject(ibfAudioRenderer);
							}
						}
					}
					finally
					{
						Marshal.ReleaseComObject(pPin);
					}
				}

				// Configure the video window
				pVidWindow = (IVideoWindow)m_pGraph;
				// If a window handle was supplied, use it
				hr = pVidWindow.put_Owner(hWin.Handle);
				ConfigureVideoWindow(hWin, false);
			}
			finally
			{
				Marshal.ReleaseComObject(icgb);
			}
		}

		/// <summary>
		/// Configure the graph to output the results to a video window.
		/// add by zhouzg
		/// </summary>
		/// <remarks>
		/// The callback routines are invoked once for each sample.  This allows for additional processing to
		/// be performed on the video or audio buffers.
		/// </remarks>
		/// <param name="hWnd">Window handle to render to, or IntPtr.Zero to render to its own window</param>
		/// <param name="pVideoCallback">Callback routine to be called for each video frame or null for no callback</param>
		/// <param name="pAudioCallback">Callback routine to be called for each audio frame or null for no callback</param>
		public void RenderToFrame(System.Windows.Forms.Control hWin, IDESCombineCB pVideoCallback, IDESCombineCB pAudioCallback, List<Layer> MarqueeDS, DsRect rc, long StartTime, long EndTime)
		{
			int hr;
			IPin pPin;
			IAMTimelineObj pGroup;
			// Perform initialization common to all render routines
            RenderCommon(StartTime, EndTime);
			// Contains useful routines for creating the graph
			ICaptureGraphBuilder2 icgb = (ICaptureGraphBuilder2)new CaptureGraphBuilder2();
            
			try
			{
				hr = icgb.SetFiltergraph(m_pGraph);
				DESError.ThrowExceptionForHR(hr);

				int NumGroups;
				hr = m_pTimeline.GetGroupCount(out NumGroups);
				DESError.ThrowExceptionForHR(hr);

				// Walk the groups.  For DESCombine, there is one group that 
				// contains all the video, and a second group for the audio.
				for (int i = 0; i < NumGroups; i++)
				{
					hr = m_pTimeline.GetGroup(out pGroup, i);
					DESError.ThrowExceptionForHR(hr);

					try
					{
						// Inform the graph we will be previewing (rather than writing to disk)
						IAMTimelineGroup pTLGroup = (IAMTimelineGroup)pGroup;
						hr = pTLGroup.SetPreviewMode(true);
						DESError.ThrowExceptionForHR(hr);
					}
					finally
					{
						// Release the group
						Marshal.ReleaseComObject(pGroup);
					}

					// Get the IPin for the current group
                    // pPin： group的输出口
					hr = m_pRenderEngine.GetGroupOutputPin(i, out pPin);
					DESError.ThrowExceptionForHR(hr);

					try
					{
						// If this is the video pin
						if (IsVideo(pPin))
						{
							// Get a video renderer
                            vmr = (IBaseFilter)new VideoMixingRenderer();
                            ConfigureVMRInWindowlessMode(hWin, rc);
							// Create a sample grabber, add it to the graph and connect it all up
							DESCallback mcb = new DESCallback(m_Video, pVideoCallback, (IMediaEventSink)m_pGraph, DESConsts.EC_VideoFileComplete, MarqueeDS);
							RenderWindowDESHelper(icgb, mcb, "Video", pPin, vmr);
						}
						else
						{
							// Get an audio renderer
							IBaseFilter ibfAudioRenderer = (IBaseFilter)new AudioRender();
							try
							{
								// Create a sample grabber, add it to the graph and connect it all up
								DESCallback mcb = new DESCallback(m_Audio, pAudioCallback, (IMediaEventSink)m_pGraph, DESConsts.EC_AudioFileComplete, MarqueeDS);
								RenderWindowDESHelper(icgb, mcb, "Audio", pPin, ibfAudioRenderer);
							}
							finally
							{
								Marshal.ReleaseComObject(ibfAudioRenderer);
							}
						}
                        // Configure the video window
                        
                        //videoWindow = (IVideoWindow)m_pGraph;
                        //// If a window handle was supplied, use it
                        //hr = videoWindow.put_Owner(hWin.Handle);
                        //ConfigureVideoWindow(hWin, false);
					}
					finally
					{
						Marshal.ReleaseComObject(pPin);
					}
				}
			}
			finally
			{
				Marshal.ReleaseComObject(icgb);
			}
		}

		/// <summary>
		/// Called from RenderTo* routines to perform common initialization
		/// </summary>
		private void RenderCommon()
		{
			int hr;

			if (m_State >= ClassState.RenderSelected)
			{
				throw new Exception("Graph rendering has already been selected");
			}

			if (m_State < ClassState.FilesAdded)
			{
				throw new Exception("No files added to render.");
			}

			m_State =ClassState.RenderSelected;

			// create the render engine
			m_pRenderEngine = (IRenderEngine)new RenderEngine();

			// tell the render engine about the timeline it should use
			hr = m_pRenderEngine.SetTimelineObject(m_pTimeline);
			DESError.ThrowExceptionForHR(hr);

			// connect up the front end
			hr = m_pRenderEngine.ConnectFrontEnd();
			DESError.ThrowExceptionForHR(hr);

			// Get the filtergraph - used all over the place
			hr = m_pRenderEngine.GetFilterGraph(out m_pGraph);
			DESError.ThrowExceptionForHR(hr);

#if DEBUG
			// Allow the graph to be connected to from GraphEdit
			m_rot = new DsROTEntry(m_pGraph);
#endif
		}

		/// <summary>
		/// Called from RenderTo* routines to perform common initialization
		/// </summary>
		private void RenderCommon(long start, long end)
		{
			int hr;

			if (m_State >= ClassState.RenderSelected)
			{
				throw new Exception("Graph rendering has already been selected");
			}

			if (m_State < ClassState.FilesAdded)
			{
				throw new Exception("No files added to render.");
			}

			m_State = ClassState.RenderSelected;

			// create the render engine
			m_pRenderEngine = (IRenderEngine)new RenderEngine();

			// tell the render engine about the timeline it should use
			hr = m_pRenderEngine.SetTimelineObject(m_pTimeline);
			DESError.ThrowExceptionForHR(hr);

			hr = m_pRenderEngine.SetRenderRange(DESHelper.FormatTime(start), DESHelper.FormatTime(end));
			DESError.ThrowExceptionForHR(hr);

			// connect up the front end
			hr = m_pRenderEngine.ConnectFrontEnd();
			DESError.ThrowExceptionForHR(hr);

			// Get the filtergraph - used all over the place
			hr = m_pRenderEngine.GetFilterGraph(out m_pGraph);
			DESError.ThrowExceptionForHR(hr);

#if DEBUG
			// Allow the graph to be connected to from GraphEdit
			m_rot = new DsROTEntry(m_pGraph);
#endif
		}

		/// <summary>
		/// Determine whether a specified pin is audio or video
		/// </summary>
		/// <param name="pPin">Pin to check</param>
		/// <returns>True if pin is video</returns>
		private bool IsVideo(IPin pPin)
		{
			int hr;
			bool bRet = false;
			AMMediaType[] pmt = new AMMediaType[1];
			IEnumMediaTypes ppEnum;

			// Walk the MediaTypes for the pin
			hr = pPin.EnumMediaTypes(out ppEnum);
			DESError.ThrowExceptionForHR(hr);

			try
			{
				// Just read the first one
				hr = ppEnum.Next(1, pmt, IntPtr.Zero);
				DESError.ThrowExceptionForHR(hr);

				bRet = pmt[0].majorType == MediaType.Video;
			}
			finally
			{
				Marshal.ReleaseComObject(ppEnum);
			}
			DsUtils.FreeAMMediaType(pmt[0]);

			return bRet;
		}

		/// <summary>
		/// Called from RenderWindow to add the renderer to the graph, create a sample grabber, add it 
		/// to the graph and connect it all up
		/// </summary>
		/// <param name="icgb">ICaptureGraphBuilder2 to use</param>
		/// <param name="pCallback">ICaptureGraphBuilder2 to use</param>
		/// <param name="sType">String to use in creating filter graph object descriptions</param>
		/// <param name="pPin">Pin to connect from</param>
		/// <param name="ibfRenderer">Renderer to add</param>
		private void RenderWindowDESHelper(ICaptureGraphBuilder2 icgb, DESCallback pCallback, string sType, IPin pPin, IBaseFilter ibfRenderer)
		{
			int hr;
			// Add the renderer to the graph
			hr = m_pGraph.AddFilter(ibfRenderer, sType + " Mixing Renderer");
			DESError.ThrowExceptionForHR(hr);
			// Do everything else
			RenderDESHelper(icgb, pCallback, sType, pPin, null, ibfRenderer);
		}

		/// <summary>
		/// Common routine used by RenderTo*  
		/// </summary>
		/// <param name="icgb">ICaptureGraphBuilder2 to use</param>
		/// <param name="pCallback">Callback to use (or null)</param>
		/// <param name="sType">string to use in creating filter graph object descriptions</param>
		/// <param name="pPin">Pin to connect from</param>
		/// <param name="ibfCompressor">Compressor to use, or null for none</param>
		/// <param name="pOutput">Endpoint (renderer or file writer) to connect to</param>
		private void RenderDESHelper(ICaptureGraphBuilder2 icgb,DESCallback pCallback, string sType, IPin pPin, IBaseFilter ibfCompressor, IBaseFilter pOutput)
		{
			int hr;
			IBaseFilter ibfSampleGrabber = null;
			ISampleGrabber isg = new SampleGrabber() as ISampleGrabber;

			try
			{
				// If no callback was provided, don't create a samplegrabber
				if (pCallback != null)
				{
					ibfSampleGrabber = (IBaseFilter)isg;
					hr = isg.SetCallback(pCallback, 1);
					DESError.ThrowExceptionForHR(hr);
					hr = m_pGraph.AddFilter(ibfSampleGrabber, sType + " sample grabber");
					DESError.ThrowExceptionForHR(hr);
					pCallback.SaveSizeInfo(isg, m_VideoWidth, m_VideoHeight);
				}

				// If a compressor was provided, add it to the graph and connect it up
				if (ibfCompressor != null)
				{
					// Connect the pin.
					hr = m_pGraph.AddFilter(ibfCompressor, sType + " Compressor");
					DESError.ThrowExceptionForHR(hr);

					hr = icgb.RenderStream(null, null, pPin, ibfSampleGrabber, ibfCompressor);
					DESError.ThrowExceptionForHR(hr);

					// Connect the pin.
					hr = icgb.RenderStream(null, null, ibfCompressor, null, pOutput);
					DESError.ThrowExceptionForHR(hr);
				}
				else
				{
					// Just connect the SampleGrabber (if any)
					hr = icgb.RenderStream(null, null, pPin, ibfSampleGrabber, pOutput);
					DESError.ThrowExceptionForHR(hr);
				}
			}
			finally
			{
				if (ibfSampleGrabber != null)
				{
					Marshal.ReleaseComObject(ibfSampleGrabber);
				}
			}
		}

		// add by zhouzg Configure the video window
		public void ConfigureVideoWindow(System.Windows.Forms.Control hWin,bool IsFullScreen)
		{
			int hr;
			videoWindow = (IVideoWindow)m_pGraph;
			// Set the output window
			if (IsFullScreen)
			{
				hr = videoWindow.put_Owner(IntPtr.Zero);
				hr = videoWindow.put_AutoShow(OABool.True);
				hr = videoWindow.put_WindowStyle((WindowStyle.Child | WindowStyle.ClipChildren | WindowStyle.ClipSiblings));
				// Position the playing location
				hr = videoWindow.SetWindowPosition(0, 0, Screen.PrimaryScreen.WorkingArea.Width, Screen.PrimaryScreen.WorkingArea.Height);
				DsError.ThrowExceptionForHR(hr);
			}
			else
			{
				hr = videoWindow.put_Owner(hWin.Handle);
				DsError.ThrowExceptionForHR(hr);
				// Set the window style
				hr = videoWindow.put_WindowStyle((WindowStyle.Child | WindowStyle.ClipChildren | WindowStyle.ClipSiblings));
				DsError.ThrowExceptionForHR(hr);
				// Position the playing location
				System.Drawing.Rectangle rc = hWin.ClientRectangle;
				hr = videoWindow.SetWindowPosition(0, 0, rc.Right, rc.Bottom);
				DsError.ThrowExceptionForHR(hr);
			}
			// Make the window visible
			hr = videoWindow.put_Visible(OABool.True);
			DsError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// Configure VMR
		/// </summary>
		public void ConfigureVMRInWindowlessMode(System.Windows.Forms.Control hWin,DsRect rc)
		{
			int hr;
			IVMRFilterConfig filterConfig = (IVMRFilterConfig)vmr;
			// Change VMR9 mode to Windowless
			hr = filterConfig.SetRenderingMode(VMRMode.Windowless);
			DsError.ThrowExceptionForHR(hr);
			windowlessCtrl = (IVMRWindowlessControl)vmr;
			// Set "Parent" window
            if (hWin != null)
            {
                hr = windowlessCtrl.SetVideoClippingWindow(hWin.Handle);
                DsError.ThrowExceptionForHR(hr);
            }
			// Set Aspect-Ratio
			hr = windowlessCtrl.SetAspectRatioMode(VMRAspectRatioMode.LetterBox);
			DsError.ThrowExceptionForHR(hr);
            //设置播放位置
            hr = windowlessCtrl.SetVideoPosition(null, rc);
			DsError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// Set Window Size
		/// </summary>
        public void ResizeVideoWindow(Size s)
		{
			try
			{
				int hr;
                if (windowlessCtrl != null)
				{
                    hr = windowlessCtrl.SetVideoPosition(null, new DsRect(0, 0, s.Width-1, s.Height-1));
					DsError.ThrowExceptionForHR(hr);
                    hr = windowlessCtrl.DisplayModeChanged();
				}
			}
			catch
			{
			}
		}

		/// <summary>
		/// save shape from video 
		/// </summary>
		/// <param name="FilePath">out shape path</param>
		/// <param name="ImageType">Out ImageType</param>
		public Image GetImage()
		{
			Bitmap bmp = null;
			IntPtr currentImage = IntPtr.Zero;
			if (windowlessCtrl != null)
			{
				try
				{
					int hr = windowlessCtrl.GetCurrentImage(out currentImage);
					DsError.ThrowExceptionForHR(hr);

					if (currentImage != IntPtr.Zero)
					{
						BitmapInfoHeader structure = new BitmapInfoHeader();
						Marshal.PtrToStructure(currentImage, structure);
						bmp = new Bitmap(structure.Width, structure.Height, (structure.BitCount / 8) * structure.Width, System.Drawing.Imaging.PixelFormat.Format32bppArgb, currentImage);
						bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);
					}
				}
				catch (Exception anyException)
				{
					MessageBox.Show("Failed getting shape: " + anyException.Message);
				}
				finally
				{
					Marshal.FreeCoTaskMem(currentImage);
				}
			}
			return (Image)bmp;
		}

		/// <summary>
		/// Returns the length of the timeline in <see cref="DESCombine.UNITS"/>.
		/// </summary>
		/// <remarks>
		/// This will return the longer of the video time line or the audio time line.
		/// </remarks>
		public long MediaLength
		{
			get
			{
				long len;
				int hr = m_pTimeline.GetDuration(out len);
				DESError.ThrowExceptionForHR(hr);

				return len;
			}
		}

		/// <summary>
		/// Returns the length of the video group in <see cref="DESCombine.UNITS"/>.
		/// </summary>
		/// <remarks>
		/// This will return the length of the video group.
		/// </remarks>
		public long VideoLength
		{
			get
			{
				return m_Video.Length;
			}
		}

        private Thread thread = null;
		/// <summary>
		/// Begins rendering and returns immediately.
		/// </summary>
		/// <remarks>
		/// Final status is sent as a <see cref="DESCombine.Completed"/> event.
		/// </remarks>
		public void StartRendering()
		{
			int hr;

			if (m_State <ClassState.RenderSelected)
			{
				throw new Exception("Render method not selected");
			}
			m_State = ClassState.GraphStarted;
			m_pPosition = (IMediaPosition)m_pGraph;
			m_pControl = (IMediaControl)m_pGraph;

			//Create a new thread to process events
            thread = new Thread(new ThreadStart(EventWait));
            thread.Name = "Media Event Thread";
            thread.Start();
			hr = m_pControl.Run();
			DESError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// 暂停播放
		/// </summary>
		public void Pause()
		{
			int hr;
			hr = m_pControl.Pause();
			DESError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// 停止播放
		/// </summary>
		public void Stop()
		{
			int hr;
			hr = m_pControl.Stop();
			DESError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// 播放视频
		/// </summary>
		public void Run()
		{
			int hr;
			hr = m_pControl.Run();
			DESError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// 设置视频播放的起点时间
		/// </summary>
		/// <param name="curTime"></param>
		public void put_CurrentPosition(double curTime)
		{
			int hr;
			hr = m_pPosition.put_CurrentPosition(curTime);
			DESError.ThrowExceptionForHR(hr);
		}

		/// <summary>
		/// Used to signal that the graph should be cancelled.
		/// </summary>
		/// <remarks>
		/// Only has meaning if called after <see cref="DESCombine.StartRendering"/>.
		/// </remarks>
		public void Cancel()
		{
			if (m_State < ClassState.GraphStarted)
			{
				throw new Exception("Graph not yet started");
			}

//#if DEBUG
//            if (m_rot != null)
//            {
//                m_rot.Dispose();
//                m_rot = null;
//            }
//#endif
			if (m_State < ClassState.GraphCompleting)
			{
				ChangeState(ClassState.Cancelling);
			}
		}

		/// <summary>
		/// Returns an XML description of the capture graph (as seen by DES).
		/// </summary>
		/// <remarks>
		/// This method can only be called after one
		/// of the render functions has been called.  Might be useful for debugging.  It is also possible (even easy) 
		/// to build the DES part of a graph from an XML file, however that functionality has not been implemented
		/// in this version of the library.
		/// </remarks>
		/// <returns>String containing XML</returns>
		public string GetXML()
		{
			if (m_State < ClassState.RenderSelected)
			{
				throw new Exception("No render method has been selected");
			}

			IXml2Dex pXML;
			string sRet;
			int hr;

			pXML = (IXml2Dex)new Xml2Dex();

			try
			{
				hr = pXML.WriteXML(m_pTimeline, out sRet);
				DESError.ThrowExceptionForHR(hr);
			}
			finally
			{
				Marshal.ReleaseComObject(pXML);
			}

			return sRet;
		}

		/// <summary>
		/// Called when the graph has finished running.
		/// </summary>
		/// <remarks>
		/// The <see cref="CompletedArgs"/>
		/// contains the result of running the graph (Completed, UserAborted,
		/// out of disk space, etc.)
		/// This code will be a member of DirectShowLib.EventCode.  Typically it 
		/// will be EventCode.Complete, EventCode.ErrorAbort or EventCode.UserAbort.
		/// </remarks>
		public event EventHandler Completed = null;
		/// <summary>
		/// Called when a file has finished processing.
		/// </summary>
		/// <remarks>
		/// The <see cref="FileCompletedArgs"/> contains the file name and type.
		/// Note that if RenderToWindow() is chosen, dropped frames can result in missed notifications.  This
		/// should not affect other RenderTo* methods.
		/// </remarks>
		public event EventHandler FileCompleted = null;

		/// <summary>
		/// Helps deal with potential conflicts between the eventing thread
		/// and client calls to Cancel()
		/// </summary>
		/// <param name="newState">State to change to</param>
		private void ChangeState(ClassState newState)
		{
			lock (this)
			{
				if (m_State ==ClassState.GraphStarted)
				{
					m_State = newState;
				}
			}
		}

		/// <summary>
		/// Called on a new thread to process events from the graph.  The thread
		/// exits when the graph finishes.  Cancelling is done here.
		/// </summary>
		private void EventWait()
		{
			// Returned when GetEvent is called but there are no events
			const int E_ABORT = unchecked((int)0x80004004);

			int hr;
			IntPtr p1, p2;
			EventCode ec;
			EventCode exitCode = 0;

			IMediaEvent pEvent = (IMediaEvent)m_pGraph;

			do
			{
				// Read the event
				for (
					hr = pEvent.GetEvent(out ec, out p1, out p2, 100);
					hr >= 0 && m_State < ClassState.GraphCompleted;
					hr = pEvent.GetEvent(out ec, out p1, out p2, 100)
					)
				{
					switch (ec)
					{
							// If the clip is finished playing
						case EventCode.Complete:
						case EventCode.ErrorAbort:
							ChangeState(ClassState.GraphCompleting);
							exitCode = ec;
							// Release any resources the message allocated
							hr = pEvent.FreeEventParams(ec, p1, p2);
							DESError.ThrowExceptionForHR(hr);
							break;

							// Walked past the end of a video file, send an event
						case DESConsts.EC_VideoFileComplete:
							if (FileCompleted != null)
							{
								MediaFile mf = m_Video.File(p1.ToInt32());
								FileCompletedArgs ca = new FileCompletedArgs(mf.FileName, FileCompletedArgs.FileType.Video);
								FileCompleted(this, ca);
							}
							break;

							// Walked past the end of a video file, send an event
						case DESConsts.EC_AudioFileComplete:
							if (FileCompleted != null)
							{
								MediaFile mf = m_Audio.File(p1.ToInt32());
								FileCompletedArgs ca = new FileCompletedArgs(mf.FileName, FileCompletedArgs.FileType.Audio);
								FileCompleted(this, ca);
							}
							break;

						default:
							// Release any resources the message allocated
							hr = pEvent.FreeEventParams(ec, p1, p2);
							DESError.ThrowExceptionForHR(hr);
							break;
					}
				}

				// If the error that exited the loop wasn't due to running out of events
				if (hr != E_ABORT)
				{
					DESError.ThrowExceptionForHR(hr);
				}
			} while (m_State < ClassState.GraphCompleting);

			// If the user cancelled
			if (m_State == ClassState.Cancelling)
			{
				// Stop the graph, send an appropriate exit code
                if(m_pControl!=null)
				    hr = m_pControl.Stop();
				exitCode = EventCode.UserAbort;
			}

            // Send an event saying we are complete
            if (Completed != null)
            {
                CompletedArgs ca = new CompletedArgs(exitCode);
                Completed(this, ca);
            }

			if (m_State == ClassState.GraphCompleting)
			{
				m_State = ClassState.GraphCompleted;
			}
			else
			{
				m_State = ClassState.Cancelled;
			}
		}
		#endregion
	}
}