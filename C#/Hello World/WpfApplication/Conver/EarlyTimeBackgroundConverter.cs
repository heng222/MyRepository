using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Data;
using System.Windows.Media;

namespace WpfApplication
{
    /// <summary>
    /// 车次早晚点与背景色转换器
    /// </summary>
    public class EarlyTimeBackgroundConverter : IValueConverter
    {
        private Brush EarlyBackground = new SolidColorBrush(Colors.Green);
        private Brush LaterBackground = new SolidColorBrush(Colors.Red);
        /// <summary>
        /// 车次早晚点状态转换背景色
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            TimeSpan span = (TimeSpan)value;
            if (span.TotalSeconds > 120)
            {
                return EarlyBackground;
            }
            else if (span.TotalSeconds < 120)
            {
                return LaterBackground;
            }
            return Brushes.Transparent;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
