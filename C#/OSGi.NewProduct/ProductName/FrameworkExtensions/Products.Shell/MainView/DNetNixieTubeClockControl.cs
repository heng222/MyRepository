using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Acl.TimeDisplay;
using Products.Presentation;
using Products.Infrastructure;

namespace Products.Shell.MainView
{
    /// <summary>
    /// 数码管时钟控件。
    /// </summary>
    [ProductPart(ControlType = PresentationControlType.NixieTubeClock)]
    public partial class DNetNixieTubeClockControl : UserControl
    {
        private TimeDisplayControl _timeControl = new TimeDisplayControl();

        /// <summary>
        /// 构造函数。
        /// </summary>
        public DNetNixieTubeClockControl()
        {
            InitializeComponent();

            this.Dock = DockStyle.Fill;
            _timeControl.Dock = DockStyle.Fill;
            _timeControl.ScrollbarVisible = false;
            _timeControl.DateBrush = new SolidBrush(_timeControl.TimeColor);
            _timeControl.WeekBrush = _timeControl.DateBrush;
            _timeControl.DateWeekBackgroundBrush = Brushes.Black;

            this.Controls.Add(_timeControl);
        }
    }
}
