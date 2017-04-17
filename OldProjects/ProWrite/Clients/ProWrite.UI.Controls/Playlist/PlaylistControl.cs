//---------------------------------------------------------------------
//
// File: PlaylistControl.cs
//
// Description:
//      DragDrop Control
//
// Author: Jerry Xu
// Date  : 2008-10-22
//
//Modify History:
//      Jerry Xu 2009-3-12 Update Event:trackBar1_ValueChanged()
//      Jerry Xu 2009-3-16 Update event:trackBar1_ValueChanged()
//      Jerry Xu 2009-3-16 Add new variant:PlaylistItemControl _current
//      Jerry Xu 2009-3-17 Update event:playPanelContainer_Resize(object sender, EventArgs e)
//      Jerry Xu 2009-3-17 Delete variant:PlaylistItemControl _current,replace it with dragDropControl's currentItem
//      Jerry Xu 2009-3-23 Update event:playPanel_Paint(object sender, PaintEventArgs e)
//      Jerry Xu 2009-4-2  Update method:DoPopulate()
//                         Update event:playPanelContainer_SizeChanged(object sender, EventArgs e)
//      Jerry Xu 2009-5-21 Update method:Init(),SubscribeEvent()
//                         Insert method:FirstReview()
//                         Update event:playPanelContainer_SizeChanged(object sender, EventArgs e)
//      Jerry Xu 2009-7-8  Update method:PopulateSize()
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ProWrite.Resources;
using ProWrite.Entity.Library;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Diagnostics;

namespace ProWrite.UI.Controls.Playlist
{
    public partial class PlaylistControl : ControlPanel<PlaylistInfo, PlaylistControl>
        //ControlBase
    {
        #region Variants define
        private int orgiSlideOffset = -68;
        private int _initPlayLeft = 66;
        private int _initDragDropControlLeft = 78;
        private int _initMaxValue;
        private int _rightOffset = 735;
        private int _zoomCount = Constance.MinZoom;
        private PlayService _playService;
        private int _Zoom = 1;
        private bool _isResize = false;
        private Size _containerSize = Size.Empty;
        private int _resizeCount = 0;
        #endregion

        public event EventHandler SavePlaylist;

        #region Properties define
        public DragDropControl DragControl
        {
            get
            {
                return dragDropControl;
            }
        }
        #endregion

        #region Functions define
        public PlaylistControl()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
            RegisterHelp();
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.PlaylistsPreview);
        }

        protected override void Init()
        {
            base.Init();

            InitializeResource();
            SubscribeEvent();

            InitPlayControl();
            lblRecycle.Enabled = false;

            //Track bar
            trackBar1.LblSlide = lblSlide;
            trackBar1.SmallChange = Constance.TrackBar.SmallChange;
            trackBar1.LargeChange = Constance.TrackBar.LargeChange;
            trackBar1.Tick = Constance.TrackBar.Tick;
            trackBar1.UnitWidth = Constance.TrackBar.UnitWidth;

            //Scroll bar init value
            hScrollBar.Maximum = dragDropControl.Width - hScrollBar.Width;
            hScrollBar.Minimum = 0;
            hScrollBar.SmallChange = Constance.TrackBar.SmallChange;
            hScrollBar.LargeChange = Constance.TrackBar.LargeChange;
            _initMaxValue = hScrollBar.Maximum;

            //DragdropControl
            dragDropControl.Left = 80;
            dragDropControl.Height = 76;
            dragDropControl.Width = 600;
            _initDragDropControlLeft = dragDropControl.Left;
            dragDropControl.Init(this);

            

            //track bar
            trackBar1.Left = 69;
            trackBar1.Height = 103;
            trackBar1.SlideOffset = orgiSlideOffset;
            //lblSlide
            lblSlide.Top = 43;
            lblSlide.Left = 81;
            //_containerSize = playPanelContainer.res;
            _initPlayLeft = trackBar1.Left;

            //DragDropLine
            dragDropLine1.Visible = false;
            dragDropLine1.AutoSize = false;
            dragDropLine1.Size = new Size(8, dragDropControl.DisplayRectangle.Height-4);
            LocalMessageBus.Subject<MenuMessage>().Observers += new System.Communication.Messaging.ObserverHandler<MenuMessage>(MessageControl_Observers);
        }

        #region Set default button shape
        /// <summary>
        /// Function:Set default button shape
        /// Author: Jerry Xu
        /// Date:2008-5-15
        /// </summary>
        private void SetDefaultbtn()
        {
            lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleClose16);
            SetDefaultCursor();
        }
        #endregion

        #region Set default cursor
        /// <summary>
        /// Function:Set default cursor
        /// Author: Jerry Xu
        /// Date:2008-5-15
        /// </summary>
        private void SetDefaultCursor()
        {
            Cursor = Cursors.Default;
        }
        #endregion

        public override void SubscribeEvent()
        {
            base.SubscribeEvent();

            //LocalMessageBus.Subject<InsertMenuActionStateMessage>().Observers += new System.Communication.Messaging.ObserverHandler<InsertMenuActionStateMessage>(PlaylistControl_Observers);



            playPanel.Click += new EventHandler(playPanel_Click);
            playPanel.Paint += new PaintEventHandler(playPanel_Paint);
            //this.lblZoomIn.Click += new System.EventHandler(this.lblZoomIn_Click);
            //this.lblZoomOut.Click += new System.EventHandler(this.lblZoomOut_Click);
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            //this.pcActionTool.Resize += new System.EventHandler(this.pcActionTool_Resize);
            this.lblRecycle.DragDrop += new System.Windows.Forms.DragEventHandler(this.lblRecycle_DragDrop);
            //this.lblRecycle.DragLeave += new System.EventHandler(this.lblRecycle_DragLeave);
            this.lblRecycle.DragEnter += new System.Windows.Forms.DragEventHandler(this.lblRecycle_DragEnter);
            this.lblRecycle.DragLeave += new EventHandler(lblRecycle_DragLeave);
            this.lblRecycle.Click += new EventHandler(lblRecycle_Click);
            playPanelContainer.SizeChanged += new EventHandler(playPanelContainer_SizeChanged);
            //Track bar event
            trackBar1.ValueChanged += new TrackBarNew.ValueChangedDelegate(trackBar1_ValueChanged);

            //DragDrop event
            dragDropControl.UpdateTotalLength += new EventHandler<UpdateTotalLengthEventArgs>(dragDropControl_UpdateTotalLength);
            dragDropControl.UpdateMaxWidth += new EventHandler<UpdateTotalWidthEventArgs>(dragDropControl_UpdateMaxWidth);
            dragDropControl.ItemSelectChange += delegate
            {
                if (dragDropControl._rightMessageBtn != null)
                {
                    lblRecycle.Enabled = true;
                }
                else
                {
                    lblRecycle.Enabled = false;
                }
            };
            //Hscroll bar            

            hScrollBar.Scroll += hScrollBar_Scroll;
            hScrollBar.ValueChanged += hScrollBar_ValueChanged;

            this.pcActionTool.Resize += new EventHandler(pcActionTool_Resize);

            //Zoom 
            this.lblZoomOut.Click += new EventHandler(lblZoomOut_Click);
            this.lblZoomIn.Click += new EventHandler(lblZoomIn_Click);
        }

        public override void UnSubscribeEvent()
        {
            base.UnSubscribeEvent();

            //LocalMessageBus.Subject<InsertMenuActionStateMessage>().Observers -= new System.Communication.Messaging.ObserverHandler<InsertMenuActionStateMessage>(PlaylistControl_Observers);
            playPanel.Click -= playPanel_Click;
            playPanel.Paint -= new PaintEventHandler(playPanel_Paint);

            //playPanelContainer.Resize -= new EventHandler(playPanelContainer_Resize);
            playPanelContainer.SizeChanged -= new EventHandler(playPanelContainer_SizeChanged);

            this.btnSave.Click -= new System.EventHandler(this.btnSave_Click);
            this.lblRecycle.DragDrop -= new System.Windows.Forms.DragEventHandler(this.lblRecycle_DragDrop);
            this.lblRecycle.DragEnter -= new System.Windows.Forms.DragEventHandler(this.lblRecycle_DragEnter);
            this.lblRecycle.DragLeave -= new EventHandler(lblRecycle_DragLeave);
            this.lblRecycle.Click -= new EventHandler(lblRecycle_Click);

            //DragDrop event
            dragDropControl.UpdateTotalLength -= new EventHandler<UpdateTotalLengthEventArgs>(dragDropControl_UpdateTotalLength);
            dragDropControl.UpdateMaxWidth -= new EventHandler<UpdateTotalWidthEventArgs>(dragDropControl_UpdateMaxWidth);

            //HscrollBar
            hScrollBar.Scroll -= hScrollBar_Scroll;
            hScrollBar.ValueChanged -= hScrollBar_ValueChanged;

            this.pcActionTool.Resize -= new EventHandler(pcActionTool_Resize);

            //Zoom 
            this.lblZoomOut.Click -= new EventHandler(lblZoomOut_Click);
            this.lblZoomIn.Click -= new EventHandler(lblZoomIn_Click);
        }

        private void FirstReview()
        {
            
            PopulateSize();
            this.dragDropControl.PopulateSize();
            if (dragDropControl.CurrentItem != null && dragDropControl.CurrentItem.NailImage != null)
            {
                using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
                    g.DrawImage(dragDropControl.CurrentItem.NailImage, new Point(0, 0));
                //this.playPanel.BackgroundImage = dragDropControl.CurrentItem.NailImage; //dragDropControl.GetNailImage(dragDropControl.NailPlaylistItemItem);
            }
            else
            {
                if (dragDropControl.Controls.Count > 0)
                {
                    PlaylistItemControl item = dragDropControl.Controls[0] as PlaylistItemControl;
                    if (item.NailImage != null)
                        using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
                            g.DrawImage(item.NailImage, new Point(0, 0));
                    //this.playPanel.BackgroundImage = (dragDropControl.Controls[0] as PlaylistItemControl).NailImage;
                }
            }
        }

        private void PopulateSize()
        {
            //if(

            if (_signSize == Size.Empty)
                _signSize = new Size(ControlService.SignCombo.Current.Width, ControlService.SignCombo.Current.Height);
            if (_signSize != Size.Empty)
            {

                int wn = (int)(playPanelContainer.DisplayRectangle.Width * 1.0f / _signSize.Width);
                int hn = (int)((this.Height-pnBottom.Height) * 1.0f / _signSize.Height);
                _Zoom = wn < hn ? wn : hn;
                _Zoom = _Zoom < 1 ? 1 : _Zoom;
                int width = _Zoom * _signSize.Width;
                int height = _Zoom * _signSize.Height;
                playPanel.Size = new Size(width, height);
                playPanel.Top = (this.Height - pnBottom.Height - playPanel.Height) / 2;
                playPanel.Left = (this.Width - playPanel.Width) / 2;
                //playPanel.Left = (playPanelContainer.ClientRectangle.Width - playPanel.Width) / 2;
                //playPanel.Top = (playPanelContainer.ClientRectangle.Height - playPanel.Height) / 2;
            }
            else
            {
                playPanel.Bounds = playPanelContainer.ClientRectangle;
            }
        }

        #region Zoom
        /// <summary>
        /// Function:Zoom
        /// Author:Jerry Xu
        /// Date:2008-6-17
        /// </summary>
        /// <param name="pZoomType">ZoomType:Enum</param>
        public void Zoom(ZoomType pZoomType)
        {
            //int unitWidth;
            //Zoom the dragdraplayoutcontrol out
            //if (pZoomType == ZoomType.ZoomOut)
            //{
            //    dragDropControl.Width = dragDropControl.Width * 2;
            //    dragDropControl.UnitWidth = dragDropControl.UnitWidth * 2;
            //    //unitWidth = dragDropControl. _unitWidth * 2;
            //    for (int i = 0; i < dragDropControl.Controls.Count; i++)
            //    {
            //        dragDropControl.Controls[i].Width = dragDropControl.Controls[i].Width * 2;
            //        if (i != 0)
            //            dragDropControl.Controls[i].Left = dragDropControl.Controls[i - 1].Left + dragDropControl.Controls[i - 1].Width;

            //    }

            //    //trackBar1.Width = trackBar1.Width * 2;
            //}
            ////Zoom the dragdraplayoutcontrol in
            //if (pZoomType == ZoomType.ZoomIn)
            //{
            //    dragDropControl.Width = dragDropControl.Width / 2;
            //    dragDropControl.UnitWidth = dragDropControl.UnitWidth / 2;
            //    for (int i = 0; i < dragDropControl.Controls.Count; i++)
            //    {
            //        dragDropControl.Controls[i].Width = dragDropControl.Controls[i].Width / 2;
            //        if (i != 0)
            //            dragDropControl.Controls[i].Left = dragDropControl.Controls[i - 1].Left + dragDropControl.Controls[i - 1].Width;
            //    }
            //    //trackBar1.Width = trackBar1.Width / 2;
            //}
            dragDropControl.Zoom(pZoomType);
            trackBar1.Zoom(pZoomType);
            //unitWidth = dragDropControl.UnitWidth;

            //trackBar1.UnitWidth = unitWidth;
            //trackBar1.SmallChange = unitWidth;
            //trackBar1.LargeChange = unitWidth;
            hScrollBar.Maximum = dragDropControl.Width - hScrollBar.Width;
            hScrollBar.Minimum = 0;
        }
        #endregion

        public override void InitializeResource()
        {
            lblCurPos.Text = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);
            lblPos.Text = Resource.GetString(Resource.Strings.PlaylistTimeDefaultText);
            lblZoomIn.Image = Resource.GetImage(Resource.Images.ZoomInBar);
            lblZoomOut.Image = Resource.GetImage(Resource.Images.ZoomOutBar);
            btnSave.Image = Resource.GetImage(Resource.Images.Save16);
            btnSave.ToolTip = Resource.GetString(Resource.Strings.Save);
            lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleClose16);
            lblRecycle.ToolTip = Resource.GetString(Resource.Strings.Delete);
            if (_zoomCount == Constance.MinZoom)
                lblZoomIn.Enabled = false;

            if (_zoomCount == Constance.MaxZoom)
                lblZoomOut.Enabled = false;
        }

        protected override void DoPopulate()
        {
            //_isResize = false;
            FirstReview();
            dragDropControl.FirstRefreshView();
            playPanel.BorderStyle = BorderStyle.FixedSingle;
            playPanel.BackColor = ProWrite.Entity.Shape.SignTypeHandler.ConvertColor(_sign.Template.Message.BackGroundColor, _sign.Type);
            _resizeCount = 1;
            //_isResize = true;
            //PopulateSize();            
        }

        public override void LoadModelInfo()
        {
            foreach (PlaylistItemControl item in dragDropControl.Controls)
            {
                if (_model.ImagePath == null && item.PlaylistItem.Target.Image != null)
                {
                    _model.Image = item.PlaylistItem.Target.Image;
                    //_model.ImagePath = SaveNailImage(item.PlaylistItem.Target.Image);
                }
            }
        }

        private static string SaveNailImage(Image image)
        {
            if (image == null)
            {
                Debug.Assert(image != null, "image == null");
                return null;
            }

            string file = Constance.LibraryNailImageDir + DateTime.Now.Ticks.ToString() + ".jpg";
            Graphics g;
            Bitmap img = new Bitmap(image.Width, image.Height);
            g = Graphics.FromImage(img);
            g.DrawImage(image, new Point(0, 0));
            IOHelper.SaveImage(img, file);
            img.Dispose();
            g.Dispose();
            return file;
        }

        public void Delete()
        {
            dragDropControl.Delete();
        }

        private void EnableControl(bool flag)
        {
            //pcActionTool.Enabled = flag;
            //pcPlayListsToolbar.Enabled = flag;

            //ControlService.PropertyGrid.Enabled = flag;
        }

        public void OnPaint()
        {
            dragDropControl.OnPaint();
        }

        #endregion              

        #region Scroll code
        #region Set scrollbar value
        /// <summary>
        /// Function:Set scrollbar value
        /// Author: Jerry Xu
        /// Date:2008-5-15
        /// </summary>
        /// <param name="orgiLeft">Original left</param>
        /// <param name="Left">left</param>
        /// <param name="e"></param>
        /// <param name="xPos">Current position</param>
        /// <returns>bool</returns>
        private bool SetScrollBarValue(int orgiLeft, int Left, ScrollEventArgs e, ref int xPos)
        {
            bool bFlag = true;
            switch (e.Type)
            {
                case ScrollEventType.First:
                    xPos = orgiLeft;
                    break;
                case ScrollEventType.Last:
                    xPos = orgiLeft - hScrollBar.Maximum;
                    break;
                case ScrollEventType.SmallDecrement:
                    xPos = Left + hScrollBar.SmallChange;
                    break;
                case ScrollEventType.SmallIncrement:
                    xPos = Left - hScrollBar.SmallChange;
                    break;
                case ScrollEventType.LargeDecrement:
                    xPos = Left + hScrollBar.LargeChange;
                    break;
                case ScrollEventType.LargeIncrement:
                    xPos = Left - hScrollBar.LargeChange;
                    break;
                case ScrollEventType.ThumbPosition:
                    xPos = orgiLeft - hScrollBar.Value;
                    break;
                default:
                    bFlag = false;
                    break;
            }

            if (bFlag)
            {
                if (xPos > orgiLeft)
                {
                    xPos = orgiLeft;
                }
                else if (xPos < orgiLeft - hScrollBar.Maximum)
                {
                    xPos = orgiLeft - hScrollBar.Maximum;
                }

            }

            return bFlag;


        }
        #endregion       

        private void hScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            #region track bar new
            try
            {
                if (hScrollBar.Maximum <= _initMaxValue)
                    return;
                bool bFlag = true;
                int xDispPos = _initDragDropControlLeft;
                int xPlayDispPos = _initPlayLeft;

                if (dragDropControl.Controls.Count > 0)
                {
                    bFlag = SetScrollBarValue(_initDragDropControlLeft, dragDropControl.Left, e, ref xDispPos);
                }
                else
                    bFlag = false;
                if (bFlag)
                {
                    dragDropControl.Left = xDispPos;
                }

                bFlag = SetScrollBarValue(_initPlayLeft, trackBar1.Left, e, ref xPlayDispPos);

                if (bFlag)
                {
                    trackBar1.Left = xPlayDispPos;
                    lblSlide.Left = trackBar1.Left + trackBar1.SlideValue + 1;
                }
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarScrollBarScrollEventException), ex);
            }
            #endregion
        }

        private void hScrollBar_ValueChanged(object sender, EventArgs e)
        {
            if (hScrollBar.Maximum <= _initMaxValue)
                return;
            int xDispPos = _initDragDropControlLeft - hScrollBar.Value;

            if (xDispPos > _initDragDropControlLeft)
            {
                xDispPos = _initDragDropControlLeft;
            }
            else if (xDispPos < _initDragDropControlLeft - hScrollBar.Maximum)
            {
                xDispPos = _initDragDropControlLeft - hScrollBar.Maximum;
            }

            int xPlayDispPos = _initPlayLeft - hScrollBar.Value;

            if (xPlayDispPos > _initPlayLeft)
            {
                xPlayDispPos = _initPlayLeft;
            }
            else if (xPlayDispPos < _initPlayLeft - hScrollBar.Maximum)
            {
                xPlayDispPos = _initPlayLeft - hScrollBar.Maximum;
            }

            dragDropControl.Left = xDispPos;            

            trackBar1.Left = xPlayDispPos;
            trackBar1.SlideOffset = _initPlayLeft - trackBar1.Left + orgiSlideOffset;

            if (trackBar1.SlideValue < _initPlayLeft - trackBar1.Left)
            {
                lblSlide.Visible = false;
            }
            else
            {
                lblSlide.Visible = true;
                lblSlide.Left = trackBar1.Left + trackBar1.SlideValue;
            }
        }
        #endregion

        #region Events define

        void MessageControl_Observers(object sender, MenuMessage msg)
        {
            if (msg.Commands != null && msg.Commands.Length > 0)
            {
                foreach (MenuCommand item in msg.Commands)
                {
                    if (item.Command == MenuCommands.Save)
                        btnSave.Enabled = item.Enabled.Value;
                    if (item.Command == MenuCommands.Delete)
                        lblRecycle.Enabled = item.Enabled.Value;

                }
            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            LocalMessageBus.Send(this, new PWMessage<MenuCommands>(MenuCommands.Save));
        }

        void lblRecycle_DragLeave(object sender, EventArgs e)
        {
            SetDefaultbtn();
        }

        private void lblRecycle_DragEnter(object sender, DragEventArgs e)
        {
            try
            {
                int name = int.Parse(e.Data.GetData(typeof(int)).ToString());

                if (name >= 0)
                {
                    e.Effect = DragDropEffects.Move;
                    lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleOpen16);
                }
                else
                    Cursor = Cursors.No;
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarRecycleDragEnterEventException), ex);
            }
        }

        private void lblRecycle_DragDrop(object sender, DragEventArgs e)
        {
            try
            {
                int order = int.Parse(e.Data.GetData(typeof(int)).ToString());
                if ( MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes && order >= 0)
                {
                    dragDropControl.RemoveAt(order);
                    dragDropControl.Invalidate();
                }
                SetDefaultbtn();
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarRecycleDragDropEventException), ex);

            }
        }

        private void lblRecycle_Click(object sender, EventArgs e)
        {
            try
            {
                lblRecycle.Image = Resource.GetImage(Resource.Images.RecycleOpen16);

                if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
                {
                    dragDropControl.Delete();
                }
                SetDefaultbtn();
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarRecycleDragDropEventException), ex);
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            
        }

        void playPanelContainer_SizeChanged(object sender, EventArgs e)
        {
            try
            {
                FirstReview();

            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsSignTabPanelResizeEventException), ex);
            }
        }        

        void playStopBar_ValueChanged(object sender, TrackBarValueChangeEventArgs e)
        {
            this.trackBar1.PlayValue = e.PlayValue;
            foreach (PlaylistItemControl item in dragDropControl.Controls)
            {
                if (lblSlide.Left > item.Left && lblSlide.Right < item.Right)
                {
                    this.playPanel.BackgroundImage = dragDropControl.GetNailImage(item);
                    dragDropControl.NailImageIndex = item.TabIndex;
                    //if (ItemSelectChange != null)
                    //    ItemSelectChange(this, new EventArgs());
                }
            }
        }       

        private void lblZoomOut_Click(object sender, EventArgs e)
        {
            try
            {
                if (_zoomCount < Constance.MaxZoom)
                {
                    _zoomCount++;
                    if (_zoomCount == Constance.MaxZoom)
                        lblZoomOut.Enabled = false;
                    lblZoomIn.Enabled = true;
                    Zoom(ZoomType.ZoomOut);
                    
                }
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarZoomOutClickEventException), ex);
            }
        }        

        private void lblZoomIn_Click(object sender, EventArgs e)
        {
            try
            {
                if (_zoomCount > 0)
                {
                    _zoomCount--;
                    if (_zoomCount == 0)
                    {
                        lblZoomIn.Enabled = false;
                    }
                    lblZoomOut.Enabled = true;
                    Zoom(ZoomType.ZoomIn);
                }
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarZoomInClickEventException), ex);
            }
        }

        void pcActionTool_Resize(object sender, EventArgs e)
        {
            hScrollBar.Width = pcActionTool.DisplayRectangle.Width - hScrollBar.Left;
        }

        void dragDropControl_UpdateMaxWidth(object sender, UpdateTotalWidthEventArgs e)
        {
            trackBar1.Width += e.AddWidth;
            hScrollBar.Maximum = dragDropControl.Width - hScrollBar.Width;
            hScrollBar.Minimum = 0;
        }

        void dragDropControl_UpdateTotalLength(object sender, UpdateTotalLengthEventArgs e)
        {
            lblPos.Text = e.TotalLength;
        }

        void trackBar1_ValueChanged()
        {
            lblCurPos.Text = CommonHelper.ConvertTimeToLengthText(trackBar1.PlayValue, Constance.TrackBar.Tick);
            int left = 0;
            int right = 0;

            if ((dragDropControl.Controls.Count == 0 || lblSlide.Left < dragDropControl.Left || lblSlide.Right > dragDropControl.Left + dragDropControl.Controls[dragDropControl.Controls.Count - 1].Right) )
            {

                using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
                {
                    //Image img = new Bitmap(playPanel.Size.Width,playPanel.Size.Height);
                    //g.DrawImage(img, new Point(0, 0));
                    g.Clear(this.playPanel.BackColor);
                }
                dragDropControl.CurrentItem = null;
                return;
            }

            //if (_current == null)
            //{
            //    if (dragDropControl.Controls.Count > 0)
            //    {
            //        _current = dragDropControl.Controls[0] as PlaylistItemControl;
            //        this.playPanel.BackgroundImage = dragDropControl.GetNailImage(_current);
            //        dragDropControl.NailImageIndex = _current.TabIndex;
            //    }
            //    return;
            //}
            //if (_current == null)
            //    return;


            foreach (PlaylistItemControl item in dragDropControl.Controls)
            {
                left = dragDropControl.Left + item.Left;
                right = dragDropControl.Left + item.Right;
                if (lblSlide.Left > left && lblSlide.Right < right)
                {
                    if (dragDropControl.CurrentItem != item)
                    {
                        dragDropControl.CurrentItem = item;
                        //this.playPanel.BackgroundImage = item.NailImage;// dragDropControl.GetNailImage(item);
                        using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
                        {
                            if(item.NailImage!=null)
                                g.DrawImage(item.NailImage, new Point(0, 0));
                        }
                        //this.playPanel.Invalidate()
                        dragDropControl.NailImageIndex = item.TabIndex;
                        return;
                    }
                    //temp = dragDropControl.GetNailImage(item);
                    //if (this.playPanel.BackgroundImage != temp)
                    //{
                    //    this.playPanel.BackgroundImage = temp;
                    //    dragDropControl.NailImageIndex = item.TabIndex;
                    //}
                    //if (ItemSelectChange != null)
                    //    ItemSelectChange(this, new EventArgs());
                }
            }

            
        }        

        void playPanel_Click(object sender, EventArgs e)
        {
            ControlService.RefreshPropertyGrid(_model);
        }       

        private void playPanel_Paint(object sender, PaintEventArgs e)
        {
            OnPaint();
            //int left = 0;
            //int right = 0;

            //if ((dragDropControl.Controls.Count == 0 || lblSlide.Left < dragDropControl.Left || lblSlide.Right > dragDropControl.Left + dragDropControl.Controls[dragDropControl.Controls.Count - 1].Right))
            //{

            //    using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
            //    {
            //        //Image img = new Bitmap(playPanel.Size.Width,playPanel.Size.Height);
            //        //g.DrawImage(img, new Point(0, 0));
            //        g.Clear(this.playPanel.BackColor);
            //    }
            //    dragDropControl.CurrentItem = null;
            //    return;
            //}

            ////if (_current == null)
            ////{
            ////    if (dragDropControl.Controls.Count > 0)
            ////    {
            ////        _current = dragDropControl.Controls[0] as PlaylistItemControl;
            ////        this.playPanel.BackgroundImage = dragDropControl.GetNailImage(_current);
            ////        dragDropControl.NailImageIndex = _current.TabIndex;
            ////    }
            ////    return;
            ////}
            ////if (_current == null)
            ////    return;


            //foreach (PlaylistItemControl item in dragDropControl.Controls)
            //{
            //    left = dragDropControl.Left + item.Left;
            //    right = dragDropControl.Left + item.Right;
            //    if (lblSlide.Left > left && lblSlide.Right < right)
            //    {
            //        if (dragDropControl.CurrentItem != item)
            //        {
            //            dragDropControl.CurrentItem = item;
            //            //this.playPanel.BackgroundImage = item.NailImage;// dragDropControl.GetNailImage(item);
            //            using (Graphics g = Graphics.FromHwnd(playPanel.Handle))
            //                g.DrawImage(item.NailImage, new Point(0, 0));
            //            //this.playPanel.Invalidate()
            //            dragDropControl.NailImageIndex = item.TabIndex;
            //            return;
            //        }
            //        //temp = dragDropControl.GetNailImage(item);
            //        //if (this.playPanel.BackgroundImage != temp)
            //        //{
            //        //    this.playPanel.BackgroundImage = temp;
            //        //    dragDropControl.NailImageIndex = item.TabIndex;
            //        //}
            //        //if (ItemSelectChange != null)
            //        //    ItemSelectChange(this, new EventArgs());
            //    }
            //}
        }

        #endregion 
    }
}
