////---------------------------------------------------------------------
////
//// File: TrackBar.cs
////
//// Description:
//// The control is to track the playlist.
////
//// Author: Jerry Xu
////
//// DateTime:2008-5-14
////
//// Modify history:
////      Jerry Xu 2008-6-19 Add the message of PlayListsZoomPlayBarMessage ,and event.
////      Jerry Xu 2008-6-20 Delete the property of "public Control PlayListsBarCtrl".
////      Jerry Xu 2008-6-24 Change ZoomType reference from SysEnumType to Prowrite.Core.Entity.      
////      Jerry Xu 2008-6-24 Delete the property of the TimeEnd.
////      Jerry Xu 2008-6-24 Delete the property of SlideOffset
////      Jerry Xu 2008-6-24 Delete the property of SlideRelativeValue 
////      Jerry Xu 2008-6-26 Delete the property of PlayListsBarCtrl
////      Jerry Xu 2008-6-26 Delete the property of PlayTrackBarControl
////      Jerry Xu 2008-6-26 Inherit ControlBase
////      Jerry Xu 2008-6-27 Log
////      Jerry Xu 2008-7-1  Record the system exception to the log  
////      Jerry Xu 2008-7-1  Support Globalization
////      Jerry Xu 2008-7-1  Delete the property of LblSlide
////      Jerry Xu 2008-7-2  Add new property of LabelSlideFLag
////      Jerry Xu 2008-7-4  Rename PlayListsTrackBar to PlaylistTrackBar
////      Jerry Xu 2008-7-4  Delete some try catch
////      Jerry Xu 2008-7-4  Rename playList L to l
////      Jerry Xu 2008-8-25 Code restruct
////
//// Copyright (C) 2008 by Trans-Lux All rights reserved.
//// 
////---------------------------------------------------------------------

//using System;
//using System.Collections.Generic;
//using System.ComponentModel;
//using System.Drawing;
//using System.Data;
//using System.Text;
//using System.Windows.Forms;
//using System.Drawing.Drawing2D;
//using ProWrite.UI.Common;
//using ProWrite.UI.Common.Messages;

//using ProWrite.Resources;
//using ProWrite.Core;
//using ProWrite.UI.Controls.PlayLists;
//using ProWrite.UI.Controls.Editor;

//namespace ProWrite.UI.Controls
//{
//    /// <summary>
//    /// Track bar control
//    /// </summary>
//    public partial class TrackBar : ControlBase
//    {
//        #region Delegates

//        public delegate void ValueChangedDelegate(int value);

//        #endregion

//        #region Variant define
//        private int _scaleBarHalfWidth = 0;//Halt width of scale bar at Track bar
//        private bool _labelSlideFLag = false;//LabelSlide FLag
//        private int _actualStartPosition = 0;//Track bar actual start position(track bar left + _scaleBarHalfWidth)
//        private int _unitWidth = Constance.TrackBar.UnitWidth;//Track bar UNITWIDTH(Per scroll pixel)
//        private int _tick = Constance.TrackBar.Tick;//Track bar tick(Time unit)
//        private ZoomType _zoomaction = ZoomType.ZoomNone;//Zoom type
//        private int timeBeginPos = 0;
//        private int timeEnd = 0;
//        private int slideOffset = 0;
//        private Label lblSlide = null;
//        #endregion

//        public TrackBar()
//        {
//            InitializeComponent();
//            if (!DesignMode)
//                Init();
//        }

//        #region Properties define
//        public int TimeEnd
//        {
//            get { return timeEnd; }
//            set
//            {
//                timeEnd = value;
//                if (timeEnd > 0)
//                {
//                    //lblTimes.Visible = true;
//                    lblTimes.Left = timeBeginPos + timeEnd;
//                }
//            }
//        }

//        public Label LblSlide
//        {
//            get { return lblSlide; }
//            set { lblSlide = value; }
//        }

//        public int SlideOffset
//        {
//            get { return slideOffset; }
//            set { slideOffset = value; }
//        }

//        /// <summary>
//        /// Track bar zoom type
//        /// </summary>
//        public ZoomType ZoomAction
//        {
//            set { _zoomaction = value; }
//            get { return _zoomaction; }
//        }

//        /// <summary>
//        /// lblSlide init left
//        /// </summary>
//        public int InitStartPosition
//        {
//            get { return _actualStartPosition + this.Left; }
//        }

//        private int _scaleBarCurrentPosition = 0;
//        /// <summary>
//        /// track bar current position
//        /// </summary>
//        public int ScaleBarCurrentPosition
//        {
//            get
//            {
//                _scaleBarCurrentPosition = lblInnerSlide.Left;
//                return _scaleBarCurrentPosition;
//            }
//            set { _scaleBarCurrentPosition = value; lblInnerSlide.Left = _scaleBarCurrentPosition; }
//        }

//        private int _initialStep = 5;
//        /// <summary>
//        ///  Initial step value(Scroll step)
//        /// </summary>
//        public int InitialStep
//        {
//            get { return _initialStep; }
//            set { _initialStep = value; }
//        }

//        private int _stepSpan = 5;
//        /// <summary>
//        /// Step span
//        /// </summary>
//        public int StepSpan
//        {
//            get { return _stepSpan; }
//            set { _stepSpan = value; }
//        }

//        /// <summary>
//        /// Unit width
//        /// </summary>
//        public int UnitWidth
//        {
//            get { return _unitWidth; }
//            set { _unitWidth = value; }
//        }

//        /// <summary>
//        /// Time scale
//        /// </summary>
//        public int Tick
//        {
//            get { return _tick; }
//            set { _tick = value; }
//        }

//        public bool LabelSlideFLag
//        {
//            get { return _labelSlideFLag; }
//            set { _labelSlideFLag = value; }
//        }

//        private int _playValue = 0;
//        /// <summary>
//        /// track bar value
//        /// </summary>
//        public int PlayValue
//        {
//            get
//            {
//                _playValue = playTrackBarCtrl.Value;
//                return _playValue;
//            }
//            set
//            {
//                _playValue = value;
//                playTrackBarCtrl.Value = _playValue;
//            }
//        }

//        private int _orgiPlaylistTrackBarLeft = 0;
//        /// <summary>
//        /// PlaylistTrackBar left at container
//        /// </summary>
//        public int OrgiPlaylistTrackBarLeft
//        {
//            get { return _orgiPlaylistTrackBarLeft; }
//            set { _orgiPlaylistTrackBarLeft = value; }
//        }

//        private int _tickFrequency = 5;
//        /// <summary>
//        /// Tick Frequency
//        /// </summary>
//        public int TickFrequency
//        {
//            get { return _tickFrequency; }
//            set { _tickFrequency = value; playTrackBarCtrl.Properties.TickFrequency = _tickFrequency; }
//        }

//        private int _largeChange = Constance.TrackBar.UnitWidth;
//        /// <summary>
//        /// Track bar large change
//        /// </summary>
//        public int LargeChange
//        {
//            get { return _largeChange; }
//            set { _largeChange = value; playTrackBarCtrl.Properties.LargeChange = _largeChange; }
//        }

//        private int _smallChange = Constance.TrackBar.UnitWidth;
//        /// <summary>
//        /// Track bar small change
//        /// </summary>
//        public int SmallChange
//        {
//            get { return _smallChange; }
//            set { _smallChange = value; playTrackBarCtrl.Properties.SmallChange = _smallChange; }
//        }
//        /// <summary>
//        /// is active control
//        /// </summary>
//        public bool IsActive
//        {
//            get
//            {
//                return PlaylistControl.Current.PlaylistEditorCtrl.TrackBarCtrl == this;
//            }
//        }

//        private int _maxLength = 0;
//        public int MaxLength
//        {
//            set { _maxLength = value; InitTimeValueLabel(_maxLength*_unitWidth); }
//            get { return _maxLength; }
//        }
//        #endregion

//        #region Functions define
//        #region init
//        protected override void Init()
//        {
//            base.Init();
//            //Init resources
//            InitializeResource();
//            //PlayValue
//            //Track bar control scale value
//            playTrackBarCtrl.Value = _playValue = 0;
//            //Scale bar current position
//            _scaleBarCurrentPosition = 12;
//            lblInnerSlide.Left = _scaleBarCurrentPosition;

//            //Tick
//            _tick = Constance.TrackBar.Tick;
//            //UnitWidth
//            _unitWidth = Constance.TrackBar.UnitWidth;
            
//            lblInnerSlide.Visible = false;
//            _scaleBarHalfWidth = lblInnerSlide.Left - playTrackBarCtrl.Left;
//            _actualStartPosition = playTrackBarCtrl.Left + _scaleBarHalfWidth;
//            lblTimes.Visible = false;
//            lblTimes.Left = _actualStartPosition;
//            _zoomaction = ZoomType.ZoomNone;
//            this.Width = Constance.MaxZoomLength + Constance.PlaylistsUsableWidth;
//            _maxLength = this.Width / _unitWidth;
//            InitTimeValueLabel(this.Width);
//            LocalMessageBus.Subject<PlaylistsZoomPlayBarMessage>().Observers += OnZoomPlayBar;
//        }
//        #endregion

//        #region ISupportGlobalization
//        /// <summary>
//        /// Initialize resource information
//        /// </summary>
//        public override void InitializeResource()
//        {
//            //Init Resource

//        }
//        #endregion //ISupportGlobalization

//        #region Clear time lable
//        /// <summary>
//        /// Function:Clear time lable
//        /// Author: Jerry Xu
//        /// Date:2008-5-9
//        /// </summary>
//        private void ClearTimeLabel()
//        {
//            for (int i = this.Controls.Count - 1; i >= 0; i--)
//            {
//                //if (this.Controls[i].Name.Length > 12)
//                //{
//                //    if (this.Controls[i].Name.Substring(0, 12) == "lblTimeValue")
//                //        this.Controls.RemoveAt(i);
//                //}
//                ValueLabel lbl = Controls[i] as ValueLabel;
//                if (lbl != null)
//                    Controls.RemoveAt(i);

//            }
//        }
//        #endregion

//        #region Init time value with label
//        /// <summary>
//        /// Function:Init time value with label
//        /// Author: Jerry Xu
//        /// Date:2008-5-9
//        /// </summary>
//        /// <param name="PlayBarCtrlWidth">Track bar width</param>
//        public void InitTimeValueLabel(int PlayBarCtrlWidth)
//        {
//            try
//            {
//                //Clear time lable
//                ClearTimeLabel();
//                //Envaluate to the track bar control's width
//                playTrackBarCtrl.Width = PlayBarCtrlWidth - playTrackBarCtrl.Left;
//                int maximum = playTrackBarCtrl.Width - 2 * _scaleBarHalfWidth;
//                //Envaluate to track bar control's maximum property 
//                playTrackBarCtrl.Properties.Maximum = maximum;
//                //Envaluate to track bar control's minimum property
//                playTrackBarCtrl.Properties.Minimum = 0;
//                playTrackBarCtrl.Properties.TickFrequency = _tickFrequency;
//                playTrackBarCtrl.Properties.SmallChange = _smallChange;
//                playTrackBarCtrl.Properties.LargeChange = _largeChange;
//                //Per step moved unit                                            
//                int step = _stepSpan;

//                //start position
//                int start = _actualStartPosition;
//                //Start step
//                int i = _initialStep;
//                string name = "";
//                string value = "";
//                StringBuilder sb = new StringBuilder();
//                //Total steps
//                int steps = maximum / _unitWidth;

//                //Envaluate to label
//                for (; i < steps; i += step)
//                {
//                    ValueLabel lblTimeValue = new ValueLabel();
//                    //name = string.Format("lblTimeValue{0:D}", i / step);
//                    lblTimeValue.Value = i;
//                    start += step * _unitWidth;
//                    sb.Remove(0, sb.Length);

//                    //When time < tick(60 second)
//                    if (i < _tick)
//                    {
//                        sb.AppendFormat("{0:D2}", i);
//                    }
//                    else if (i < _tick * _tick)//When time < tick*tick(60 minutes)
//                    {
//                        sb.AppendFormat("{0:D}.", i / _tick);
//                        sb.AppendFormat("{0:D2}", i % _tick);
//                    }
//                    else//When time >= 1 hours
//                    {
//                        sb.AppendFormat("{0:D}.", i / (_tick * _tick));
//                        sb.AppendFormat("{0:D2}.", (i % (_tick * _tick)) / _tick);
//                        sb.AppendFormat("{0:D2}", (i % (_tick * _tick)) % _tick);
//                    }

//                    value = sb.ToString();
//                    lblTimeValue.AutoSize = true;
//                    lblTimeValue.Location = new System.Drawing.Point(start - _scaleBarHalfWidth, 2);
//                    //lblTimeValue.Name = name;
//                    lblTimeValue.Size = new System.Drawing.Size(2, 2);
//                    lblTimeValue.TabIndex = 10;
//                    lblTimeValue.Text = value;
//                    this.Controls.Add(lblTimeValue);
//                }
//            }
//            catch (Exception ex)
//            {
//                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlaylistPlaylistTrackBarInitTimeValueLabelException), ex);
//            }
//        }
//        #endregion

//        #region Zoom
//        /// <summary>
//        /// Function:Zoom
//        /// Author: Jerry Xu
//        /// Date:2008-5-9 
//        /// </summary>
//        public void Zoom()
//        {
//            try
//            {
//                //Zoom out
//                if (_zoomaction == ZoomType.ZoomOut)
//                {
//                    _unitWidth = _unitWidth * 2;
//                }
//                //Zoom in
//                if (_zoomaction == ZoomType.ZoomIn)
//                {
//                    _unitWidth = _unitWidth / 2;
//                }
//                //Reinit label time value by zoom type
//                _smallChange = _unitWidth;
//                _largeChange = _unitWidth;
//                InitTimeValueLabel(this.Width);
//            }
//            catch (Exception ex)
//            {
//                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlaylistPlaylistTrackBarZoomException), ex);
//            }
//        }
//        #endregion
//        #endregion

//        #region Events define
//        public event ValueChangedDelegate ValueChanged;

//        protected virtual void OnValueChanged()
//        {
//            if (ValueChanged != null)
//                ValueChanged(lblSlide.Left);
//        }
//        private void playTrackBarCtrl_ValueChanged(object sender, EventArgs e)
//        {
//            if (ModuleManager.CurrentModuleName == ModuleNames.Playlists)
//            {


//                try
//                {
//                    lblInnerSlide.Left = playTrackBarCtrl.Left + _scaleBarHalfWidth + playTrackBarCtrl.Value;
//                    if (_labelSlideFLag)
//                    {
//                        int lblSliedeLeft = 0;
//                        //LblSlide.Visible = true;
//                        lblSliedeLeft = lblInnerSlide.Left + this.Left;

//                        string strPos = string.Empty;
//                        int intPos = 0;
//                        StringBuilder sb = new StringBuilder();
//                        //intPos = (playTrackBarCtrl.Value) / _unitWidth;
//                        intPos = playTrackBarCtrl.Value;
//                        LocalMessageBus.Send(this, new PlaylistsUpdateCurrentPositionLabelMessage(Commons.Helper.ConvertPixelToLabelTime(intPos, _unitWidth, _tick), lblSliedeLeft));
//                    }
//                }
//                catch (Exception ex)
//                {
//                    DataGate.Log.Error(Resource.GetString(Resource.Strings.PlaylistPlaylistTrackBarPlayTrackBarCtrlValueChangedEventException), ex);
//                }
//            }
//            if (ModuleManager.CurrentModuleName == ModuleNames.Editor)
//            {
//                lblInnerSlide.Left = playTrackBarCtrl.Left + _scaleBarHalfWidth + playTrackBarCtrl.Value;

//                if (LblSlide != null)
//                {
//                    LblSlide.Visible = true;
//                    LblSlide.Left = lblInnerSlide.Left + this.Left;

//                    OnValueChanged();
//                }
//            }

//        }

//        #region Zoom event
//        /// <summary>
//        /// Zoom event
//        /// Author: Jerry Xu
//        /// Date:2008-6-18 
//        /// </summary>
//        /// <param name="sender"></param>
//        /// <param name="e"></param>
//        private void OnZoomPlayBar(object sender, PlaylistsZoomPlayBarMessage e)
//        {
//            try
//            {
//                if (IsActive)
//                {
//                    _zoomaction = e.Zoom;
//                    Zoom();
//                }
//            }
//            catch
//            {
//            }
//        }

        
//        #endregion

//        #region Nested type: ValueLabel

//        private class ValueLabel : Label
//        {
//            public int Value;

//            public ValueLabel()
//            {
//            }
//        }
//        #endregion

//        #endregion
//    }
//}
