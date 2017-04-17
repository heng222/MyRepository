//---------------------------------------------------------------------
//
// File: FrameLayerContainerNew.cs
//
// Description:
// User Control of PlayStopBar 
//
// Author: 
//
// Date:
//
// Modify history:
//      Jerry Xu 2008-8-22 Add property:ForwardButtonVisible
//      Jerry Xu 2008-8-22 Add item move up and down
//      Jerry Xu 2008-8-22 Add method:MoveLayers
//      Jerry Xu 2008-8-22 Add event:frameLayer_DragLayer
//      Jerry Xu 2008-8-22 Add item move undo/redo uploadAction 
//      Jerry Xu 2008-8-25 Corrent stop button state ,shape state
// 
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
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Editor;
using ProWrite.Entity.DES;
using ProWrite.Resources;
using System.Drawing.Drawing2D;
using ProWrite.UI.Controls.Playlist;
using ProWrite.Core;

namespace ProWrite.UI.Controls
{
	public partial class PlayStopBar : ControlBase
    {
        #region Variant define
        private IPlayService _service;
        private VideoLayerCollection[] _messages;
        #endregion
        
        public PlayStopBar()
		{
			InitializeComponent();
			if(!DesignMode)
			{
                Init();
			}
        }

        #region Properties define
        /// <summary>
        /// If forward button and backward button can be used
        /// </summary>
        public bool SupportNext
        {            
            set
            {
                btnNext.Visible = value;
                btnPrevious.Visible = value;
            }
        }
        #endregion

        #region Functions define
        public void RegisterService(IPlayService service)
        {
            _service = service;
        }

        protected override void Init()
        {
            base.Init();
            InitializeResource();
            SubscribeEvent();
            btnStop.Enabled = false;
            btnStop.Visible = false;
            btnPrevious.Visible = false;
            btnNext.Visible = false;
        }


        public override void SubscribeEvent()
        {
            base.SubscribeEvent();
            btnPlay.Click += btnPlay_Click;
            btnPlay.Paint += new PaintEventHandler(btnPlay_Paint);
           
        }

        void btnPlay_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                GraphicsPath path = new GraphicsPath();
                path.AddEllipse(btnPlay.ClientRectangle);
                btnPlay.Region = new Region(path);
            }
            catch (Exception ex)
            {
                DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListPlayListsBarPlayPaintEventExceptiohn), ex);
            }
        }

        public override void UnSubscribeEvent()
        {
            base.UnSubscribeEvent();
            btnPlay.Click -= btnPlay_Click;
            btnPlay.Paint -= new PaintEventHandler(btnPlay_Paint);
        }

		public override void InitializeResource()
		{
			base.InitializeResource();
			this.BackgroundImage = Resources.Resource.GetImage(Resources.Resource.Images.PlayBarBackground);

			btnPlay.NormalImage = Resources.Resource.GetImage(Resources.Resource.Images.Play2Normal);
			btnPlay.HoverImage =Resources.Resource.GetImage(Resources.Resource.Images.Play2Hover);
			btnPlay.PushedImage =Resources.Resource.GetImage(Resources.Resource.Images.Play2Push);
			btnPlay.DisabledImage =Resources.Resource.GetImage(Resources.Resource.Images.Play2Disable);

			btnStop.NormalImage =Resources.Resource.GetImage(Resources.Resource.Images.StopNormal);
			btnStop.HoverImage =Resources.Resource.GetImage(Resources.Resource.Images.StopHover);
			btnStop.PushedImage =Resources.Resource.GetImage(Resources.Resource.Images.StopPush);
			btnStop.DisabledImage = Resources.Resource.GetImage(Resources.Resource.Images.StopDisable);

			btnPrevious.NormalImage = Resources.Resource.GetImage(Resources.Resource.Images.PreviousNormal);
			btnPrevious.HoverImage = Resources.Resource.GetImage(Resources.Resource.Images.PreviousHover);
			btnPrevious.PushedImage = Resources.Resource.GetImage(Resources.Resource.Images.PreviousPush);
			btnPrevious.DisabledImage = Resources.Resource.GetImage(Resources.Resource.Images.PreviousDisable);

			btnNext.NormalImage = Resources.Resource.GetImage(Resources.Resource.Images.NextNormal);
			btnNext.HoverImage = Resources.Resource.GetImage(Resources.Resource.Images.NextHover);
			btnNext.PushedImage = Resources.Resource.GetImage(Resources.Resource.Images.NextPush);
			btnNext.DisabledImage = Resources.Resource.GetImage(Resources.Resource.Images.NextDisable);

            btnPrevious.Enabled = false;
            btnNext.Enabled = false;

        }
        #endregion

        #region Events define
        void btnPlay_Click(object sender, EventArgs e)
        {
            if (_service == null)
                return;
            _messages = _service.OnPlay();
            if (_messages == null || _messages.Length < 1)
                return;
            
            PlayForm frmPlay = new PlayForm(_messages);
            frmPlay.SetPlayTitle(_service.Mode, _service.PlayName);
            frmPlay.ShowModalDialog();
        }
        #endregion
    }
}
