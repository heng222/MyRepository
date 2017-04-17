using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.DES
{
	public class DESVideoCallBack : IDESCombineCB
	{
		//private EventArgs ca = new EventArgs();
		private System.Windows.Forms.TrackBar m_PlayBar = null;
        private System.Windows.Forms.Label m_MediaTime = null;
		public int m_FrameCount = 0;
		public int m_RunTime = 0;

        public Action OnCallBack;

		public DESVideoCallBack()
		{
			m_FrameCount = 0;
		}

		public DESVideoCallBack(System.Windows.Forms.TrackBar playBar)
		{
			m_FrameCount = 0;
			m_PlayBar = playBar;
		}

        public DESVideoCallBack(int RunTime, System.Windows.Forms.TrackBar playBar, System.Windows.Forms.Label pMediaTime)
		{
			m_RunTime = RunTime;
			m_PlayBar = playBar;
            m_MediaTime = pMediaTime;
		}

		public int BufferCB(string sFilename, double SampleTime, System.IntPtr pBuffer, int BufferLen)
		{
			if (m_PlayBar != null)
			{
                m_PlayBar.Value = (int)((m_RunTime + SampleTime) * DESConsts.FPS);
                //m_PlayBar.Value = m_RunTime * (int)DESConsts.FPS + (int)(SampleTime * DESConsts.FPS);
            }
            if (m_MediaTime != null)
            {
                m_MediaTime.Text = DESHelper.FormatTimeToMinute(long.Parse(SampleTime.ToString("0")));
            }
			m_FrameCount++;
            if (OnCallBack != null)
                OnCallBack();
			return 0;
		}
	}
}