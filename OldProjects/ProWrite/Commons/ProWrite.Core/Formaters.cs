using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.Core
{
    public sealed class Formaters
    {
        /// <summary>
        /// Function: format time length by separator
        /// Author: Kevin
        /// Date:   2008-7-10
        /// </summary>
        /// <param name="timeLen">time length</param>
        /// <param name="separator">separator</param>
        /// <returns></returns>
        public static string FormatTime(int timeLen, string separator)
        {
            if (timeLen <= 0)
                return Constance.TimeDefaultText;

            return string.Format("{0:D2}{3:D2}{1:D2}{3:D2}{2:D2}",
                                       timeLen / (Constance.TrackBar.Tick * Constance.TrackBar.Tick),
                                       (timeLen % (Constance.TrackBar.Tick * Constance.TrackBar.Tick)) / Constance.TrackBar.Tick,
                                       (timeLen % (Constance.TrackBar.Tick * Constance.TrackBar.Tick)) % Constance.TrackBar.Tick,
                                       separator);
        }

        public static string FormatTime(int timeLen)
        {
            if (timeLen <= 0)
                return Constance.TimeDefaultText;

            return string.Format("{0:D2}{3:D2}{1:D2}{3:D2}{2:D2}",
                                       timeLen / (Constance.TrackBar.Tick * Constance.TrackBar.Tick),
                                       (timeLen % (Constance.TrackBar.Tick * Constance.TrackBar.Tick)) / Constance.TrackBar.Tick,
                                       (timeLen % (Constance.TrackBar.Tick * Constance.TrackBar.Tick)) % Constance.TrackBar.Tick,
                                       Constance.TimeSeparator);
        }

        
    }
}
