using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using ProWrite.Core;
using ProWrite.UI.Controls.Playlist;
using ProWrite.UI.Controls.Common;


namespace ProWrite.UI.Controls
{
    public partial class TrackBarNew : UserControl
    {

        #region Variant define
        private int slideSpan = 0;//Track bar Offset
        private Label lblSlide = null;
        private int _scaleBarStartPos = 2;//Track bar scalebar start position (unit:pixel)
        private const int stepSpan = 5;
        private int _orgiStep = 5;
        private int slideOffset = 0;
        private int timeEnd = 0;//lblTime position
        //private int _unitWidth = 12;//Constance.TrackBar.UnitWidth;//UnitWidth
        //private const int _tick = 60;//Constance.TrackBar.Tick;
        private int timeBeginPos = 0;//timeBeginPos = start pos
        private int slideRelativeValue = 0;//lblInnerSlide position(relative track bar)
        private int _trackBarCtrlLastWidth = 0;
        private int _trackBarCtrlWidth = 1000;
        private int _trackBarCtrlValueWidth = 0;
        private int _lastScalebarMaxStep = 0; //Last scale bar max step
        private int _lastScalebarMaxPosition = 0; //Last scale bar max position
        #endregion

        public TrackBarNew()
        {
            InitializeComponent();
            Init();
            lblInnerSlide.Visible = false;
            lblTimes.Visible = false;
            SlideValue = 0;
        }

        #region Properties define
        public int SlideRelativeValue
        {
            get
            {
                slideRelativeValue = playTrackBarCtrl.Value * _unitWidth + slideSpan;
                return slideRelativeValue;
            }
            set { slideRelativeValue = value; }
        }
        private int slideValue = 0;//lblInnerSlide.left

        public int SlideValue
        {
            get
            {
                slideValue = lblInnerSlide.Left;
                return slideValue;
            }
            set
            {
                slideValue = value; lblInnerSlide.Left = value;

            }
        }
        private int playValue = 0;//Track bar value

        public int PlayValue
        {
            get
            {
                playValue = playTrackBarCtrl.Value;
                return playValue;
            }
            set
            {
                playValue = value;
                playTrackBarCtrl.Value = playValue;
            }
        }


        private int _unitWidth = Constance.TrackBar.UnitWidth;
        /// <summary>
        /// Trackbar unit width which will change by zoom event
        /// </summary>
        public int UnitWidth
        {
            get { return _unitWidth; }
            set { _unitWidth = value; }
        }

        private int _tick = Constance.TrackBar.Tick;
        /// <summary>
        /// Trackbar tick
        /// </summary>
        public int Tick
        {
            get { return _tick; }
            set { _tick = value; }
        }

        public int TimeEnd
        {
            get
            {
                return timeEnd;
            }
            set
            {
                timeEnd = value;
                if (timeEnd > 0)
                {
                    //lblTimes.Visible = true;
                    lblTimes.Left = timeBeginPos + timeEnd;
                }
            }
        }



        public int SlideOffset
        {
            get { return slideOffset; }
            set { slideOffset = value; }
        }

        public Label LblSlide
        {
            get { return lblSlide; }
            set { lblSlide = value; }
        }
        private Control editorLayersCtrl = null;

        public Control EditorLayersCtrl
        {
            get { return editorLayersCtrl; }
            set { editorLayersCtrl = value; }
        }

        private int currentPos = 0;//=SlideRelativeValue

        public int CurrentPos
        {
            get
            {
                //currentPos = playTrackBarCtrl.Value * _unitWidth - slideSpan;
                currentPos = SlideValue - slideSpan;
                return currentPos;
            }
            // set { currentPos = value; }
        }

        private int _largeChange = Constance.TrackBar.LargeChange;
        /// <summary>
        /// Track bar large change
        /// </summary>
        public int LargeChange
        {
            get { return _largeChange; }
            set { _largeChange = value; playTrackBarCtrl.Properties.LargeChange = _largeChange; }
        }

        private int _smallChange = Constance.TrackBar.SmallChange;
        /// <summary>
        /// Track bar small change
        /// </summary>
        public int SmallChange
        {
            get { return _smallChange; }
            set { _smallChange = value; playTrackBarCtrl.Properties.SmallChange = _smallChange; }
        }
        #endregion

        #region Function define
        private void Init()
        {
            if (0 == slideSpan)
            {
                slideSpan = lblInnerSlide.Left - playTrackBarCtrl.Left;
            }

            if (0 == _scaleBarStartPos)
            {
                _scaleBarStartPos = playTrackBarCtrl.Left + slideSpan;
            }

            if (0 == timeBeginPos)
            {
                timeBeginPos = _scaleBarStartPos;
            }

            lblTimes.Left = _scaleBarStartPos;

            slideValue = lblInnerSlide.Left;
        }

        #region Clear time lable
        /// <summary>
        /// Function:Clear time lable
        /// Author: Jerry Xu
        /// Date:2008-5-9
        /// </summary>
        private void ClearTimeLabel()
        {
            int a = 0;
            for (int i = Controls.Count - 1; i > 0; i--)
            {
                if (int.TryParse(this.Controls[i].Name, out a))
                    this.Controls.RemoveAt(i);
            }
        }
        #endregion

        private void InitTimeValueLabel()
        {

            try
            {
                //ClearTimeLabel();
                //Init();
                //mutex.WaitOne();
                //Init track bar control properties
                int maximum = _trackBarCtrlValueWidth / _unitWidth; //(playTrackBarCtrl.Width - 2 * slideSpan) / unitWidth;
                playTrackBarCtrl.Properties.Maximum = maximum;
                playTrackBarCtrl.Properties.Minimum = 0;
                playTrackBarCtrl.Properties.TickFrequency = _tick;
                playTrackBarCtrl.Properties.SmallChange = _smallChange;
                playTrackBarCtrl.Properties.LargeChange = _largeChange;

                //step span is 5
                int step = stepSpan;

                //Scalebar start position
                int start = _scaleBarStartPos;

                //Original step is 5
                int i = _orgiStep;
                string name = "";
                string value = "";
                StringBuilder sb = new StringBuilder();
                int totalSteps = maximum;


                int lastScalebarMaxPosition = _scaleBarStartPos;
                int lastScalebarMaxStep = i;
                int maxValue = 0;
                int ctrlValue = 0;

                try
                {
                    #region memo
                    foreach (Control ctrl in this.Controls)
                    {
                        if (ctrl is Label && Char.IsNumber(ctrl.Name.Trim(), 0))
                        {
                            try
                            {
                                ctrlValue = Convert.ToInt32(ctrl.Name);
                            }
                            catch
                            {
                            }

                            if (ctrlValue > maxValue)
                            {
                                maxValue = ctrlValue;
                                //if (orgiStep < maxValue)
                                lastScalebarMaxStep = maxValue;
                                //else
                                //    currPosValue = orgiStep;
                                lastScalebarMaxPosition = ctrl.Left;
                            }
                        }
                    }

                    if (maxValue > 0)
                    {
                        i = lastScalebarMaxStep + step;
                        start = lastScalebarMaxPosition;
                    }
                    #endregion

                    //i = _lastScalebarMaxStep + step;
                    //start = _lastScalebarMaxPosition;

                    for (; i < totalSteps; i += step)
                    {

                        Label lblTimeValue = new Label();
                        name = string.Format("{0:D}", i);
                        start += step * _unitWidth;

                        sb.Remove(0, sb.Length);

                        if (i < _tick)
                        {
                            sb.AppendFormat("{0:D2}", i);
                        }
                        else if (i < _tick * _tick)
                        {
                            sb.AppendFormat("{0:D}:", i / _tick);
                            sb.AppendFormat("{0:D2}", i % _tick);
                        }
                        else
                        {
                            sb.AppendFormat("{0:D}:", i / (_tick * _tick));
                            sb.AppendFormat("{0:D2}:", (i % (_tick * _tick)) / _tick);
                            sb.AppendFormat("{0:D2}", (i % (_tick * _tick)) % _tick);

                        }

                        value = sb.ToString();
                        // lblTimeValue
                        // 
                        lblTimeValue.AutoSize = true;
                        lblTimeValue.Location = new System.Drawing.Point(start, 2);
                        lblTimeValue.Name = name;
                        lblTimeValue.Size = new System.Drawing.Size(2, 2);
                        lblTimeValue.TabIndex = 10;
                        lblTimeValue.Text = value;
                        this.Controls.Add(lblTimeValue);
                    }
                    //_lastScalebarMaxStep = i;
                    //_lastScalebarMaxPosition = start;
                }
                catch (Exception e)
                {
                    MsgBox.Warning(e.ToString());
                }

                _orgiStep = i;

                _scaleBarStartPos = start;

            }
            catch
            {
            }
            finally
            {
                //mutex.ReleaseMutex();
            }


        }
        #endregion

        #region Event define
        public delegate void ValueChangedDelegate();
        public event ValueChangedDelegate ValueChanged;

        protected virtual void OnValueChanged()
        {
            if (ValueChanged != null)
                ValueChanged();
        }

        private void playTrackBarCtrl_ValueChanged(object sender, EventArgs e)
        {
            //lblInnerSlide.Left = playTrackBarCtrl.Left + slideSpan + playTrackBarCtrl.Value * _unitWidth;
            lblInnerSlide.Left = playTrackBarCtrl.Left + slideSpan + playTrackBarCtrl.Value * _unitWidth;

            if (LblSlide != null)
            {
                LblSlide.Visible = true;
                LblSlide.Left = lblInnerSlide.Left - slideOffset;
                OnValueChanged();
            }
        }



        private void TrackBarNew_Resize(object sender, EventArgs e)
        {
            //Track bar current total width
            _trackBarCtrlWidth = this.DisplayRectangle.Width - playTrackBarCtrl.Left;

            //When track bar total width increase
            if (_trackBarCtrlWidth > _trackBarCtrlLastWidth)
            {
                //Total width = width + width error(2*slidespan+unitWidth - width % unitWidth)
                _trackBarCtrlValueWidth = _trackBarCtrlWidth + _unitWidth - _trackBarCtrlWidth % _unitWidth;
                _trackBarCtrlWidth = _trackBarCtrlValueWidth + 2 * slideSpan;
                playTrackBarCtrl.Width = _trackBarCtrlWidth;

                //Last width
                _trackBarCtrlLastWidth = _trackBarCtrlWidth;

                //Go on draw scale
                InitTimeValueLabel();
            }
        }

        static int count = 0;
        public void Zoom(ZoomType zoom)
        {
            ClearTimeLabel();
            _scaleBarStartPos = 0;
            _orgiStep = 5;
            count++;
            if (count == 10)
                count=0;
            if (zoom == ZoomType.ZoomOut)
            {
                _unitWidth = _unitWidth * 2;
                _smallChange = _unitWidth;
                _largeChange = _unitWidth;
                _trackBarCtrlLastWidth = 0;
                this.Width = this.Width * 2;
            }
            //Zoom the dragdraplayoutcontrol in
            if (zoom == ZoomType.ZoomIn)
            {
                _unitWidth = _unitWidth / 2;
                _smallChange = _unitWidth;
                _largeChange = _unitWidth;
                _trackBarCtrlLastWidth = 0;
                this.Width = this.Width / 2;
            }
            lblInnerSlide.Left = playTrackBarCtrl.Left + slideSpan + playTrackBarCtrl.Value * _unitWidth;

            if (LblSlide != null)
            {
                LblSlide.Visible = true;
                LblSlide.Left = lblInnerSlide.Left - slideOffset;
                OnValueChanged();
            }
        }

        #endregion
    }
}
