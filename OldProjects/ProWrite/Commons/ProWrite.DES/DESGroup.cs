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
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.DES
{
    /// <summary>
    /// Class containing information about the timeline groups (one
    /// for audio, one for video)
    /// </summary>
    internal class DESGroup : DisposableObject
    {
        #region Members
        private int m_Width;
        private int m_Height;

        /// <summary>
        /// Used to store the current length
        /// </summary>
        private long m_Length = 0;
        private long m_MaxLength = 0;
        private long m_RepeatNums = 1;

        /// <summary>
        /// An array holding the names and durations of the files to be processed
        /// </summary>
        private List<MediaFile> m_Files;
        /// <summary>
        /// Timeline to add items to
        /// </summary>
        private IAMTimeline m_pTimeline;

        /// <summary>
        /// Pointer to the track
        /// </summary>
        private IAMTimelineTrack[] m_TrackArr;
        private IAMTimelineComp[] m_CompArr;

        /// <summary>
        /// The count of files in the group
        /// </summary>
        /// <returns>The count</returns>
        public int Count
        {
            get
            {
                return m_Files.Count;
            }
        }

        /// <summary>
        /// Returns the length of the group in <see cref="DESCombine.UNITS"/>.
        /// </summary>
        public long Length
        {
            get
            {
                return m_Length;
            }
        }
        #endregion

        public DESGroup(AMMediaType mType, IAMTimeline pTimeline, VideoLayerCollection ds, int hWinWidth, int hWinHeight)
        {
            int hr;
            IAMTimelineObj pGroupObj;
            IAMTimelineGroup pGroup;
            m_Width = hWinWidth;
            m_Height = hWinHeight;
            m_Length = 0;
            m_Files = new List<MediaFile>();
            m_pTimeline = pTimeline;

            for (int i = 0; i < ds.Count; i++)
            {
                if (ds[i].EndTime > m_MaxLength)
                    m_MaxLength = ds[i].EndTime;
            }
            m_MaxLength = m_MaxLength == 0 ? ds.PlayLength : m_MaxLength;
            if (ds.PlayLength <= m_MaxLength)
            {
                m_RepeatNums = 1;
            }
            else
            {
                m_RepeatNums = ds.PlayLength / m_MaxLength + (ds.PlayLength % m_MaxLength == 0 ? 0 : 1);
            }

            // make the root group/composition
            hr = m_pTimeline.CreateEmptyNode(out pGroupObj, TimelineMajorType.Group);
            DESError.ThrowExceptionForHR(hr);


            try
            {
                pGroup = (IAMTimelineGroup)pGroupObj;
                // Set the media type we just created
                hr = pGroup.SetMediaType(mType);
                DESError.ThrowExceptionForHR(hr);
                DsUtils.FreeAMMediaType(mType);
                // add the video group to the timeline
                hr = m_pTimeline.AddGroup(pGroupObj);
                DESError.ThrowExceptionForHR(hr);
                List<Layer> ImageDS = ds.FindAll(ImageLayer);
                m_TrackArr = new IAMTimelineTrack[m_RepeatNums * ImageDS.Count + 2];
                m_CompArr = new IAMTimelineComp[m_RepeatNums * ImageDS.Count + 2];
                AddCompAndTrack(ds, pGroup);
            }
            finally
            {
                Marshal.ReleaseComObject(pGroupObj);
            }
        }

        ~DESGroup()
        {
            Dispose();
        }

        /// <summary>
        /// Add comp and track to timeline
        /// </summary>
        public void AddCompAndTrack(VideoLayerCollection ds, IAMTimelineGroup pGroup)
        {
            IAMTimelineObj pCompObj;
            IAMTimelineObj pTrackObj;
            int hr = 0;
            int i = 1;
            long m_StartTime = 0;

            // Create a composition object
            IAMTimelineComp pGroupComp = (IAMTimelineComp)pGroup;
            List<Layer> ImageDS = ds.FindAll(p => p.Visible == true
                && p.FilePath != ""
                && (p.LayerType == LayerType.Image || p.LayerType == LayerType.Video));

            //create backcolor item
            hr = m_pTimeline.CreateEmptyNode(out pCompObj, TimelineMajorType.Composite);
            hr = pGroupComp.VTrackInsBefore(pCompObj, -1);
            m_CompArr[0] = (IAMTimelineComp)pCompObj;
            hr = m_pTimeline.CreateEmptyNode(out pTrackObj, TimelineMajorType.Track);
            hr = m_CompArr[0].VTrackInsBefore(pTrackObj, -1);
            m_TrackArr[0] = (IAMTimelineTrack)pTrackObj;

            for (int m = 0; m < m_RepeatNums; m++)
            {
                m_StartTime = DESHelper.FormatTime(m * m_MaxLength);
                i = m * ImageDS.Count + 1;
                foreach (Layer layer in ImageDS)
                {
                    IAMTimelineComp tempComp = null;
                    hr = m_pTimeline.CreateEmptyNode(out pCompObj, TimelineMajorType.Composite);
                    hr = pGroupComp.VTrackInsBefore(pCompObj, -1);
                    m_CompArr[i] = (IAMTimelineComp)pCompObj;
                    DESTransition.SetDxtKey(ref m_pTimeline, m_CompArr[i], m_StartTime + DESHelper.FormatTime(layer.StartTime), m_StartTime + DESHelper.FormatTime(layer.EndTime));
                    //Set Sign Color
                    if (layer.LayerType == LayerType.Video || (layer.LayerType == LayerType.Image && DESHelper.GetMediaLength(layer.FilePath) > 0))
                    {
                        DESTransition.SetSign(ref m_pTimeline, m_CompArr[i], m_StartTime + DESHelper.FormatTime(layer.StartTime), m_StartTime + DESHelper.FormatTime(layer.EndTime), ds.SignType);
                        DESTransition.SetPixelate(ref m_pTimeline, m_CompArr[i], m_StartTime + DESHelper.FormatTime(layer.StartTime), m_StartTime + DESHelper.FormatTime(layer.EndTime), ds.Zoom);
                    }
                    //Set Layer Comsitor
                    if (layer.Rect.X != 0 || layer.Rect.Y!=0 || layer.Rect.Height != m_Height || layer.Rect.Width != m_Width)
                    {
                        hr = m_pTimeline.CreateEmptyNode(out pCompObj, TimelineMajorType.Composite);
                        hr = m_CompArr[i].VTrackInsBefore(pCompObj, -1);
                        tempComp = (IAMTimelineComp)pCompObj;

                        DESTransition.SetCompositor(ref m_pTimeline, tempComp, m_StartTime + DESHelper.FormatTime(layer.StartTime), m_StartTime + DESHelper.FormatTime(layer.EndTime), layer.Rect);
                        DESTransition.SetAlpha(ref m_pTimeline, tempComp, m_StartTime + DESHelper.FormatTime(layer.StartTime), m_StartTime + DESHelper.FormatTime(layer.EndTime));
                        hr = m_pTimeline.CreateEmptyNode(out pTrackObj, TimelineMajorType.Track);
                        hr = tempComp.VTrackInsBefore(pTrackObj, -1); // append to the end of the track list
                        m_TrackArr[i] = (IAMTimelineTrack)pTrackObj;
                    }
                    else
                    {
                        hr = m_pTimeline.CreateEmptyNode(out pTrackObj, TimelineMajorType.Track);
                        hr = m_CompArr[i].VTrackInsBefore(pTrackObj, -1); // append to the end of the track list
                        m_TrackArr[i] = (IAMTimelineTrack)pTrackObj;
                    }
                    i++;
                }
            }

            //create Sign Effect item
            hr = m_pTimeline.CreateEmptyNode(out pCompObj, TimelineMajorType.Composite);
            hr = pGroupComp.VTrackInsBefore(pCompObj, -1);
            m_CompArr[m_CompArr.Length - 1] = (IAMTimelineComp)pCompObj;
            hr = m_pTimeline.CreateEmptyNode(out pTrackObj, TimelineMajorType.Track);
            hr = m_CompArr[m_CompArr.Length - 1].VTrackInsBefore(pTrackObj, -1);
            m_TrackArr[m_TrackArr.Length - 1] = (IAMTimelineTrack)pTrackObj;
            DESTransition.SetDxtKey(ref m_pTimeline, m_CompArr[m_TrackArr.Length - 1], 0, DESHelper.FormatTime(ds.PlayLength));
        }

        private static bool ImageLayer(Layer layer)
        {
            return layer.Visible == true
                && layer.FilePath != ""
                && (layer.LayerType == LayerType.Image 
                    || layer.LayerType == LayerType.Video);
        }

        /// <summary>
        /// Add Source to video group
        /// </summary>
        public void LoadSource(VideoLayerCollection ds)
        {
            int i = 1;
            long lStart;
            long lEnd;
            long m_StartTime = 0;

            List<Layer> ImageDS = ds.FindAll(ImageLayer);
            for (int m = 0; m < m_RepeatNums; m++)
            {
                m_StartTime = DESHelper.FormatTime(m * m_MaxLength);
                i = m * ImageDS.Count + 1;
                foreach (Layer layer in ImageDS)
                {
                    lStart = m_StartTime + DESHelper.FormatTime(layer.StartTime);
                    lEnd = m_StartTime + DESHelper.FormatTime(layer.EndTime);

                    MediaFile mf = new MediaFile(layer.FilePath);
                    m_Files.Add(mf);
                    mf.LengthInFrames = (int)Math.Round(((lEnd - lStart) * DESConsts.FPS) / DESConsts.UNITS);

                    if (layer.LayerType == LayerType.Video)
                    {
                        long m_Len = DESHelper.GetMediaLength(layer.FilePath);
                        if (m_Len >= lEnd - lStart)
                        {
                            AddSource(m_TrackArr[i], layer.FilePath, lStart, lEnd);
                        }
                        else
                        {
                            for (long n = 0; n < (lEnd - lStart) / m_Len; n++)
                            {
                                AddSource(m_TrackArr[i], layer.FilePath, lStart + n * m_Len, lStart + (n + 1) * m_Len);
                            }
                            AddSource(m_TrackArr[i], layer.FilePath, lEnd - (lEnd - lStart) % m_Len, lEnd);
                        }
                    }
                    else
                    {
                        AddSource(m_TrackArr[i], layer.FilePath, lStart, lEnd);
                    }

                    m_Length += lEnd - lStart;
                    //add Transition and Effect
                    if (layer.TextInfo != null)
                    {
                        DESTransition.SetEffect(ref m_pTimeline, m_TrackArr[i], layer.TextInfo.GUID,
                                                m_StartTime + DESHelper.FormatTime(layer.TextInfo.StartTime),
                                                m_StartTime + DESHelper.FormatTime(layer.TextInfo.EndTime),
                                                layer.TextInfo.ToPropertyArray());
                        //DESTransition.SetPixelate(ref m_pTimeline, m_CompArr[i], m_StartTime + DESHelper.FormatTime(item.StartTime), m_StartTime + DESHelper.FormatTime(item.EndTime), ds.Zoom);
                    }
                    //DESTransition.SetTextTravel(ref m_pTimeline, m_TrackArr[i], lStart, lEnd, item.TextInfo);
                    if (layer.EntryEffect != null)
                        DESTransition.SetTransition(ref m_pTimeline, m_TrackArr[i], layer.EntryEffect.GUID, layer.EntryEffect.State, m_StartTime + DESHelper.FormatTime(layer.EntryEffect.StartTime), m_StartTime + DESHelper.FormatTime(layer.EntryEffect.EndTime), layer.EntryEffect.ToPropertyArray());
                    if (layer.ExitEffect != null)
                        DESTransition.SetTransition(ref m_pTimeline, m_TrackArr[i], layer.ExitEffect.GUID, layer.ExitEffect.State, m_StartTime + DESHelper.FormatTime(layer.ExitEffect.StartTime), m_StartTime + DESHelper.FormatTime(layer.ExitEffect.EndTime), layer.ExitEffect.ToPropertyArray());
                    if (layer.EmphasisEffect != null)
                        // edit by Louis, playing emphasis effect exactly start at emphasis effect, not include entry effect 
                        DESTransition.SetEffect(ref m_pTimeline, m_TrackArr[i], layer.EmphasisEffect.GUID, 
                                m_StartTime + DESHelper.FormatTime(layer.EmphasisEffect.StartTime), 
                                m_StartTime + DESHelper.FormatTime(layer.EmphasisEffect.EndTime), 
                                layer.EmphasisEffect.ToPropertyArray());
                    //DESTransition.SetEffect(ref m_pTimeline, m_TrackArr[i], item.EmphasisEffect.GUID.ToString(), m_StartTime + DESHelper.FormatTime(item.EntryEffect != null ? item.EntryEffect.StartTime : item.EmphasisEffect.StartTime), m_StartTime + DESHelper.FormatTime(item.ExitEffect != null ? item.ExitEffect.EndTime : item.EmphasisEffect.EndTime), item.EmphasisEffect.Property);

                    //不需要对所有的层进行像素化
                    //DESTransition.SetPixelate(ref m_pTimeline, m_CompArr[i], m_StartTime + DESHelper.FormatTime(item.StartTime), m_StartTime + DESHelper.FormatTime(item.EndTime), ds.Zoom);

                    i++;
                }
            }
            

            #if VERSION_2
            if (ds.MasterLayerVisual)
                AddColor(m_TrackArr[0], ds.BackColor, 0, DESHelper.FormatTime(ds.PlayLength));
            #else
            AddColor(m_TrackArr[0], ds.BackColor, 0, DESHelper.FormatTime(ds.PlayLength));
            #endif

            #if VERSION_2
            if (ds.EmphasisEffect != null)
            {
                if (ds.MasterLayerVisual)
                {
                    AddColor(m_TrackArr[m_TrackArr.Length - 1], Color.Empty, 0, DESHelper.FormatTime(ds.PlayLength));
                    DESTransition.SetEffect(ref m_pTimeline, m_TrackArr[m_TrackArr.Length - 1], ds.EmphasisEffect.GUID, 0, DESHelper.FormatTime(ds.PlayLength), ds.EmphasisEffect.ToPropertyArray());
                }
            }
            #else
            if (ds.EmphasisEffect != null)
            {
                AddColor(m_TrackArr[m_TrackArr.Length - 1], Color.Empty, 0, DESHelper.FormatTime(ds.PlayLength));
                DESTransition.SetEffect(ref m_pTimeline, m_TrackArr[m_TrackArr.Length - 1], ds.EmphasisEffect.GUID, 0, DESHelper.FormatTime(ds.PlayLength), ds.EmphasisEffect.ToPropertyArray());
            }   
            #endif
        }

        /// <summary>
        /// add Source to video group
        /// </summary>
        private void AddSource(IAMTimelineTrack myTrack, string SourceFile, long StartTime, long EndTime)
        {
            int hr;
            IAMTimelineObj pSource1Obj;
            // create the timeline source object
            hr = m_pTimeline.CreateEmptyNode(out pSource1Obj, TimelineMajorType.Source);
            DESError.ThrowExceptionForHR(hr);

            try
            {
                // set up source length
                hr = pSource1Obj.SetStartStop(StartTime, EndTime);
                DESError.ThrowExceptionForHR(hr);
                IAMTimelineSrc pSource1Src = (IAMTimelineSrc)pSource1Obj;
                // Set the file name
                hr = pSource1Src.SetMediaName(SourceFile);
                DESError.ThrowExceptionForHR(hr);
                // Set the start/end
                hr = pSource1Src.SetMediaLength(EndTime - StartTime);
                DESError.ThrowExceptionForHR(hr);
                hr = pSource1Src.SetStretchMode(0);
                // Set the times, get back the times adjusted to fit the frame rate
                hr = pSource1Src.FixMediaTimes(ref StartTime, ref EndTime);
                DESError.ThrowExceptionForHR(hr);
                // Connect the track to the source
                hr = myTrack.SrcAdd(pSource1Obj);
                DESError.ThrowExceptionForHR(hr);
            }
            finally
            {
                Marshal.ReleaseComObject(pSource1Obj);
            }
        }

        /// <summary>
        /// Add Color to video group on Layer
        /// </summary>
        private void AddColor(IAMTimelineTrack myTrack, Color sColor, long StartTime, long EndTime)
        {
            int hr;
            IAMTimelineObj pSource1Obj;
            // create the timeline source object
            hr = m_pTimeline.CreateEmptyNode(out pSource1Obj, TimelineMajorType.Source);
            DESError.ThrowExceptionForHR(hr);

            try
            {
                // set up source length
                hr = pSource1Obj.SetStartStop(StartTime, EndTime);
                DESError.ThrowExceptionForHR(hr);

                DESTransition.SetColor(pSource1Obj, sColor);
                // Connect the track to the source
                hr = myTrack.SrcAdd(pSource1Obj);
                DESError.ThrowExceptionForHR(hr);
            }
            finally
            {
                Marshal.ReleaseComObject(pSource1Obj);
            }
        }

        /// <summary>
        /// Returns the indexed file
        /// </summary>
        /// <param name="x">Zero based index into list of files in group</param>
        /// <returns>The specified MediaFile</returns>
        public MediaFile File(int x)
        {
            if (m_Files.Count > 0)
            {
                return (MediaFile)m_Files[x];
            }

            return null;
        }

        #region IDisposable Members

        /// <summary>
        /// Release everything
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (m_TrackArr != null)
            {
                int length = m_TrackArr.Length;
                for (int i = 0; i < length; i++)
                {
                    if (m_TrackArr[i] != null)
                    {
                        Marshal.ReleaseComObject(m_TrackArr[i]);
                        m_TrackArr[i] = null;
                    }
                }

                Array.Clear(m_TrackArr, 0, length);
                m_TrackArr = null;
            }

            if (m_CompArr != null)
            {
                int length = m_CompArr.Length;
                for (int i = 0; i < length; i++)
                {
                    if (m_CompArr[i] != null)
                    {
                        Marshal.ReleaseComObject(m_CompArr[i]);
                        m_CompArr[i] = null;
                    }
                }

                Array.Clear(m_CompArr, 0, length);
                m_CompArr = null;
            }

            if (m_Files != null)
            {
                m_Files.Clear();
                m_Files = null;
            }
            m_Length = 0;

            if (m_pTimeline != null)
            {
                Marshal.ReleaseComObject(m_pTimeline);
                m_pTimeline = null;
            }
        }

        #endregion
    }
}