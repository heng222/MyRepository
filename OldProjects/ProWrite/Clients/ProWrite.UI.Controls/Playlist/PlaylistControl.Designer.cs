using System;
using ProWrite.Core;
namespace ProWrite.UI.Controls.Playlist
{
    partial class PlaylistControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlaylistControl));
            this.playPanelContainer = new System.Windows.Forms.Panel();
            this.playPanel = new System.Windows.Forms.Panel();
            this.pnBottom = new System.Windows.Forms.Panel();
            this.pcPlayToolbar = new DevExpress.XtraEditors.PanelControl();
            this.playStopBar = new ProWrite.UI.Controls.PlayStopBar();
            this.pcActionTool = new DevExpress.XtraEditors.PanelControl();
            this.hScrollBar = new DevExpress.XtraEditors.HScrollBar();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.lblRecycle = new DevExpress.XtraEditors.SimpleButton();
            this.pcPlayListsToolbar = new DevExpress.XtraEditors.PanelControl();
            this.dragDropLine1 = new ProWrite.UI.Controls.Playlist.DragDropLine(this.components);
            this.pcRightLayer = new DevExpress.XtraEditors.PanelControl();
            this.lblPos = new DevExpress.XtraEditors.LabelControl();
            this.pcLeftLayer = new DevExpress.XtraEditors.PanelControl();
            this.lblCurPos = new DevExpress.XtraEditors.LabelControl();
            this.lblZoomIn = new System.Windows.Forms.Label();
            this.lblZoomOut = new System.Windows.Forms.Label();
            //this.lblZoomIn = new DevExpress.XtraEditors.LabelControl();
            //this.lblZoomOut = new DevExpress.XtraEditors.LabelControl();
            this.lblSlide = new System.Windows.Forms.Label();
            this.dragDropControl = new ProWrite.UI.Controls.Playlist.PlaylistControl.DragDropControl();
            this.trackBar1 = new ProWrite.UI.Controls.TrackBarNew();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.playPanelContainer.SuspendLayout();
            this.pnBottom.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcPlayToolbar)).BeginInit();
            this.pcPlayToolbar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcActionTool)).BeginInit();
            this.pcActionTool.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcPlayListsToolbar)).BeginInit();
            this.pcPlayListsToolbar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcRightLayer)).BeginInit();
            this.pcRightLayer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcLeftLayer)).BeginInit();
            this.pcLeftLayer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dragDropControl)).BeginInit();
            this.SuspendLayout();
            // 
            // playPanelContainer
            // 
            this.playPanelContainer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.playPanelContainer.BackColor = System.Drawing.Color.Transparent;
            this.playPanelContainer.Controls.Add(this.playPanel);
            this.playPanelContainer.Location = new System.Drawing.Point(0, 0);
            this.playPanelContainer.Name = "playPanelContainer";
            this.playPanelContainer.Size = new System.Drawing.Size(748, 343);
            this.playPanelContainer.TabIndex = 3;
            // 
            // playPanel
            // 
            this.playPanel.BackColor = System.Drawing.Color.Black;
            this.playPanel.ForeColor = System.Drawing.SystemColors.ActiveBorder;
            this.playPanel.Location = new System.Drawing.Point(0, 0);
            this.playPanel.Name = "playPanel";
            this.playPanel.Size = new System.Drawing.Size(590, 287);
            this.playPanel.TabIndex = 0;
            // 
            // pnBottom
            // 
            this.pnBottom.Anchor = ((System.Windows.Forms.AnchorStyles)((( System.Windows.Forms.AnchorStyles.Bottom
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pnBottom.Controls.Add(this.pcPlayToolbar);
            this.pnBottom.Controls.Add(this.pcActionTool);
            this.pnBottom.Controls.Add(this.pcPlayListsToolbar);
            this.pnBottom.Location = new System.Drawing.Point(0, 350);
            this.pnBottom.Name = "pnBottom";
            
            this.pnBottom.Size = new System.Drawing.Size(748, 199);
            this.pnBottom.TabIndex = 4;
            // 
            // pcPlayToolbar
            // 
            this.pcPlayToolbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pcPlayToolbar.Controls.Add(this.playStopBar);
            this.pcPlayToolbar.Location = new System.Drawing.Point(0, 0);
            this.pcPlayToolbar.Name = "pcPlayToolbar";
            this.pcPlayToolbar.Size = new System.Drawing.Size(746, 41);
            this.pcPlayToolbar.TabIndex = 20;
            // 
            // playStopBar
            // 
            this.playStopBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.playStopBar.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("playStopBar.BackgroundImage")));
            this.playStopBar.IsSupportGlobalization = false;
            this.playStopBar.Location = new System.Drawing.Point(0, 0);
            this.playStopBar.Name = "playStopBar";
            this.playStopBar.Size = new System.Drawing.Size(748, 44);
            this.playStopBar.TabIndex = 6;
            // 
            // pcActionTool
            // 
            this.pcActionTool.Controls.Add(this.hScrollBar);
            this.pcActionTool.Controls.Add(this.btnSave);
            this.pcActionTool.Controls.Add(this.lblRecycle);
            this.pcActionTool.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pcActionTool.Location = new System.Drawing.Point(0, 155);
            this.pcActionTool.Name = "pcActionTool";
            this.pcActionTool.Size = new System.Drawing.Size(748, 44);
            this.pcActionTool.TabIndex = 18;
            // 
            // hScrollBar
            // 
            this.hScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.hScrollBar.Location = new System.Drawing.Point(80, 11);
            this.hScrollBar.LookAndFeel.SkinName = "Blue";
            this.hScrollBar.LookAndFeel.UseDefaultLookAndFeel = false;
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(671, 18);
            this.hScrollBar.TabIndex = 15;
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleCenter;
            this.btnSave.Location = new System.Drawing.Point(5, 10);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(27, 31);
            this.btnSave.TabIndex = 7;
            // 
            // lblRecycle
            // 
            this.lblRecycle.AllowDrop = true;
            this.lblRecycle.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblRecycle.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleCenter;
            this.lblRecycle.Location = new System.Drawing.Point(38, 10);
            this.lblRecycle.Name = "lblRecycle";
            this.lblRecycle.Size = new System.Drawing.Size(27, 31);
            this.lblRecycle.TabIndex = 14;
            // 
            // pcPlayListsToolbar
            // 
            this.pcPlayListsToolbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pcPlayListsToolbar.Controls.Add(this.dragDropLine1);
            this.pcPlayListsToolbar.Controls.Add(this.pcRightLayer);
            this.pcPlayListsToolbar.Controls.Add(this.pcLeftLayer);
            this.pcPlayListsToolbar.Controls.Add(this.lblSlide);
            this.pcPlayListsToolbar.Controls.Add(this.dragDropControl);
            this.pcPlayListsToolbar.Controls.Add(this.trackBar1);
            this.pcPlayListsToolbar.Location = new System.Drawing.Point(0, 37);
            this.pcPlayListsToolbar.Name = "pcPlayListsToolbar";
            this.pcPlayListsToolbar.Size = new System.Drawing.Size(750, 128);
            this.pcPlayListsToolbar.TabIndex = 19;
            // 
            // dragDropLine1
            // 
            this.dragDropLine1.Location = new System.Drawing.Point(0, 0);
            this.dragDropLine1.Name = "dragDropLine1";
            this.dragDropLine1.Size = new System.Drawing.Size(8, 76);
            this.dragDropLine1.TabIndex = 19;
            // 
            // pcRightLayer
            // 
            this.pcRightLayer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pcRightLayer.Controls.Add(this.lblPos);
            this.pcRightLayer.Location = new System.Drawing.Point(672, 0);
            this.pcRightLayer.Name = "pcRightLayer";
            this.pcRightLayer.Size = new System.Drawing.Size(76, 128);
            this.pcRightLayer.TabIndex = 20;
            // 
            // lblPos
            // 
            this.lblPos.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lblPos.Appearance.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold);
            this.lblPos.Appearance.Options.UseFont = true;
            this.lblPos.Location = new System.Drawing.Point(55, 10);
            this.lblPos.Name = "lblPos";
            this.lblPos.Size = new System.Drawing.Size(0, 13);
            this.lblPos.TabIndex = 10;
            // 
            // pcLeftLayer
            // 
            this.pcLeftLayer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.pcLeftLayer.Controls.Add(this.lblCurPos);
            this.pcLeftLayer.Controls.Add(this.lblZoomIn);
            this.pcLeftLayer.Controls.Add(this.lblZoomOut);
            this.pcLeftLayer.Location = new System.Drawing.Point(0, 0);
            this.pcLeftLayer.Name = "pcLeftLayer";
            this.pcLeftLayer.Size = new System.Drawing.Size(73, 124);
            this.pcLeftLayer.TabIndex = 19;
            // 
            // lblCurPos
            // 
            this.lblCurPos.Appearance.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold);
            this.lblCurPos.Appearance.Options.UseFont = true;
            this.lblCurPos.Location = new System.Drawing.Point(14, 5);
            this.lblCurPos.Name = "lblCurPos";
            this.lblCurPos.Size = new System.Drawing.Size(0, 13);
            this.lblCurPos.TabIndex = 8;
            // 
            // lblZoomIn
            // 
            this.lblZoomIn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblZoomIn.Location = new System.Drawing.Point(39, 41);
            this.lblZoomIn.Name = "lblZoomIn";
            this.lblZoomIn.Size = new System.Drawing.Size(33, 33);
            this.lblZoomIn.TabIndex = 18;
            this.toolTip1.SetToolTip(this.lblZoomIn, "Zoom Out");
            //this.lblZoomIn.ToolTip = "Zoom In";
            // 
            // lblZoomOut
            // 
            this.lblZoomOut.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblZoomOut.Location = new System.Drawing.Point(7, 39);
            this.lblZoomOut.Name = "lblZoomOut";
            this.lblZoomOut.Size = new System.Drawing.Size(32, 37);
            this.lblZoomOut.TabIndex = 17;
            this.toolTip1.SetToolTip(this.lblZoomOut, "Zoom In");
            //this.lblZoomOut.ToolTip = "Zoom Out";
            // 
            // lblSlide
            // 
            this.lblSlide.BackColor = System.Drawing.Color.Black;
            this.lblSlide.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblSlide.Location = new System.Drawing.Point(80, 40);
            this.lblSlide.Name = "lblSlide";
            this.lblSlide.Size = new System.Drawing.Size(1, 76);
            this.lblSlide.TabIndex = 16;
            // 
            // dragDropControl
            // 
            this.dragDropControl.AllowDrop = true;
            this.dragDropControl.CurrentItem = null;
            this.dragDropControl.Location = new System.Drawing.Point(80, 47);
            this.dragDropControl.Name = "dragDropControl";
            this.dragDropControl.Size = new System.Drawing.Size(600, 76);
            this.dragDropControl.TabIndex = 7;
            this.dragDropControl.Tick = 60;
            this.dragDropControl.UnitWidth = 8;
            // 
            // trackBar1
            // 
            this.trackBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBar1.EditorLayersCtrl = null;
            this.trackBar1.LargeChange = 5;
            this.trackBar1.LblSlide = null;
            this.trackBar1.Location = new System.Drawing.Point(65, 5);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.PlayValue = 0;
            this.trackBar1.Size = new System.Drawing.Size(600, 47);
            this.trackBar1.SlideOffset = 0;
            this.trackBar1.SlideRelativeValue = 9;
            this.trackBar1.SlideValue = 11;
            this.trackBar1.SmallChange = 5;
            this.trackBar1.TabIndex = 0;
            this.trackBar1.Tick = 60;
            this.trackBar1.TimeEnd = 0;
            this.trackBar1.UnitWidth = 8;
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // PlaylistControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pnBottom);
            this.Controls.Add(this.playPanelContainer);
            this.Name = "PlaylistControl";
            this.Size = new System.Drawing.Size(748, 550);
            this.playPanelContainer.ResumeLayout(false);
            this.pnBottom.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pcPlayToolbar)).EndInit();
            this.pcPlayToolbar.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pcActionTool)).EndInit();
            this.pcActionTool.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pcPlayListsToolbar)).EndInit();
            this.pcPlayListsToolbar.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pcRightLayer)).EndInit();
            this.pcRightLayer.ResumeLayout(false);
            this.pcRightLayer.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pcLeftLayer)).EndInit();
            this.pcLeftLayer.ResumeLayout(false);
            this.pcLeftLayer.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dragDropControl)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel playPanelContainer;
        private System.Windows.Forms.Panel playPanel;
        private System.Windows.Forms.Panel pnBottom;
        private DevExpress.XtraEditors.PanelControl pcActionTool;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private DevExpress.XtraEditors.SimpleButton lblRecycle;
        private DevExpress.XtraEditors.HScrollBar hScrollBar;
        private DevExpress.XtraEditors.PanelControl pcPlayToolbar;
        private DevExpress.XtraEditors.PanelControl pcPlayListsToolbar;
        private DevExpress.XtraEditors.PanelControl pcRightLayer;
        private DevExpress.XtraEditors.LabelControl lblPos;
        private DevExpress.XtraEditors.PanelControl pcLeftLayer;
        private DevExpress.XtraEditors.LabelControl lblCurPos;
        //private DevExpress.XtraEditors.LabelControl lblZoomIn;
        //private DevExpress.XtraEditors.LabelControl lblZoomOut;
        private System.Windows.Forms.Label lblZoomIn;
        private System.Windows.Forms.Label lblZoomOut;
        private System.Windows.Forms.Label lblSlide;
        private PlaylistControl.DragDropControl dragDropControl;
        private TrackBarNew trackBar1;
        private System.Windows.Forms.ImageList imageList1;
        private PlayStopBar playStopBar;
        private DragDropLine dragDropLine1;
        private System.Windows.Forms.ToolTip toolTip1;
    }
}
