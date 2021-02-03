using System;
using System.Drawing;
using System.Windows.Forms;

using Acl.TimeDisplay;

using Products.Presentation;

namespace Products.Shell.MainView
{
    /// <summary>
    /// 数码管时钟控件。
    /// </summary>
    [ProductPart("96DAB869-4741-45EE-8A1D-407E69DE7179", "数码管时钟控件", Dock = DockStyle.Top)]
    public partial class NixieTubeClockControl : UserControl
    {
        //private static readonly Brush DefaultBackgroundBrush = Brushes.Gray;

        #region "Field"
        private TimeDisplayControl _timeControl = null;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public NixieTubeClockControl()
        {
            InitializeComponent();

            //this.Dock = DockStyle.Fill;
            this.CreateTimeControl();

            InitializeUi();
        }
        #endregion

        #region "private methods"
        private void InitializeUi()
        {
            this.dateWeekVisableToolStripMenuItem.Checked = _timeControl.DateWeekVisable;
            this.progressbarToolStripMenuItem.Checked = _timeControl.ProgressBarVisible;
        }

        private void CreateTimeControl()
        {
            _timeControl = new TimeDisplayControl() { Dock = DockStyle.Fill };

            _timeControl.ProgressBarVisible = true;
            //_timeControl.SpliterColor = Color.WhiteSmoke;

            _timeControl.DateWeekVisable = true;
            //_timeControl.DateBrush = Brushes.White;
            //_timeControl.WeekBrush = Brushes.White;
            //_timeControl.DateWeekBackgroundBrush = DefaultBackgroundBrush;

            _timeControl.TimeColor = Color.FromArgb(0, 255, 0);
            //_timeControl.TimeBackgroundBrush = DefaultBackgroundBrush;

            this.Controls.Add(_timeControl);
        }
        #endregion

        #region "菜单事件响应函数"
        private void OnDateWeekVisableToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                _timeControl.DateWeekVisable = !_timeControl.DateWeekVisable;
                this.dateWeekVisableToolStripMenuItem.Checked = _timeControl.DateWeekVisable;
            }
            catch (Exception /*ex*/)
            {
            }
        }

        private void OnProgressbarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                _timeControl.ProgressBarVisible = !_timeControl.ProgressBarVisible;
                this.progressbarToolStripMenuItem.Checked = _timeControl.ProgressBarVisible;
            }
            catch (Exception /*ex*/)
            {
            }
        }
        #endregion
    }
}
