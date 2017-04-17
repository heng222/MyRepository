using ProWrite.Resources;
using System.Windows.Forms;

namespace ProWrite.UI.Controls
{
    partial class PlayForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlayForm));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.pnlParent = new System.Windows.Forms.Panel();
            this.lblButton = new System.Windows.Forms.Label();
            this.lblTop = new System.Windows.Forms.Label();
            this.pnlPlay = new System.Windows.Forms.Panel();
            this.pnlPlayList = new DevExpress.XtraEditors.PanelControl();
            this.treeList1 = new DevExpress.XtraTreeList.TreeList();
            this.colName = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.colLength = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.colObject = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.imageCollection1 = new DevExpress.Utils.ImageCollection(this.components);
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.lblTitle = new System.Windows.Forms.Label();
            this.pnlTotal = new DevExpress.XtraEditors.PanelControl();
            this.lblTotalList = new System.Windows.Forms.Label();
            this.PlayBar = new System.Windows.Forms.TrackBar();
            this.pnlStatus = new System.Windows.Forms.Panel();
            this.lblCurName = new System.Windows.Forms.Label();
            this.lblSplit = new System.Windows.Forms.Label();
            this.lblTotalTime = new System.Windows.Forms.Label();
            this.lblCurTime = new System.Windows.Forms.Label();
            this.pnlPlayButton = new System.Windows.Forms.Panel();
            this.btnPlay = new ProWrite.UI.Controls.ImageButton();
            this.btnNext = new ProWrite.UI.Controls.ImageButton();
            this.btnPrevious = new ProWrite.UI.Controls.ImageButton();
            this.btnStop = new ProWrite.UI.Controls.ImageButton();
            this.picPlayBar = new System.Windows.Forms.PictureBox();
            this.btnToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.pnlParent.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlPlayList)).BeginInit();
            this.pnlPlayList.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.treeList1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollection1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlTotal)).BeginInit();
            this.pnlTotal.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlayBar)).BeginInit();
            this.pnlStatus.SuspendLayout();
            this.pnlPlayButton.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picPlayBar)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.pnlParent);
            this.splitContainer1.Panel1.Controls.Add(this.pnlPlayList);
            this.splitContainer1.Panel1.Controls.Add(this.PlayBar);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("splitContainer1.Panel2.BackgroundImage")));
            this.splitContainer1.Panel2.Controls.Add(this.pnlStatus);
            this.splitContainer1.Panel2.Controls.Add(this.pnlPlayButton);
            this.splitContainer1.Panel2.Controls.Add(this.picPlayBar);
            this.splitContainer1.Size = new System.Drawing.Size(665, 485);
            this.splitContainer1.SplitterDistance = 442;
            this.splitContainer1.SplitterWidth = 2;
            this.splitContainer1.TabIndex = 1;
            // 
            // pnlParent
            // 
            this.pnlParent.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.pnlParent.Controls.Add(this.lblButton);
            this.pnlParent.Controls.Add(this.lblTop);
            this.pnlParent.Controls.Add(this.pnlPlay);
            this.pnlParent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlParent.Location = new System.Drawing.Point(0, 0);
            this.pnlParent.Name = "pnlParent";
            this.pnlParent.Size = new System.Drawing.Size(455, 413);
            this.pnlParent.TabIndex = 6;
            // 
            // lblButton
            // 
            this.lblButton.BackColor = System.Drawing.Color.White;
            this.lblButton.Location = new System.Drawing.Point(0, 287);
            this.lblButton.Margin = new System.Windows.Forms.Padding(0);
            this.lblButton.Name = "lblButton";
            this.lblButton.Size = new System.Drawing.Size(475, 1);
            this.lblButton.TabIndex = 5;
            this.lblButton.Visible = false;
            // 
            // lblTop
            // 
            this.lblTop.BackColor = System.Drawing.Color.White;
            this.lblTop.Location = new System.Drawing.Point(0, 83);
            this.lblTop.Margin = new System.Windows.Forms.Padding(0);
            this.lblTop.Name = "lblTop";
            this.lblTop.Size = new System.Drawing.Size(475, 1);
            this.lblTop.TabIndex = 4;
            this.lblTop.Visible = false;
            // 
            // pnlPlay
            // 
            this.pnlPlay.BackColor = System.Drawing.SystemColors.ControlText;
            this.pnlPlay.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.pnlPlay.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlPlay.Location = new System.Drawing.Point(50, 88);
            this.pnlPlay.Name = "pnlPlay";
            this.pnlPlay.Size = new System.Drawing.Size(338, 195);
            this.pnlPlay.TabIndex = 3;
            // 
            // pnlPlayList
            // 
            this.pnlPlayList.Appearance.BackColor = System.Drawing.Color.WhiteSmoke;
            this.pnlPlayList.Appearance.ForeColor = System.Drawing.SystemColors.AppWorkspace;
            this.pnlPlayList.Appearance.Options.UseBackColor = true;
            this.pnlPlayList.Appearance.Options.UseForeColor = true;
            this.pnlPlayList.Controls.Add(this.treeList1);
            this.pnlPlayList.Controls.Add(this.panelControl1);
            this.pnlPlayList.Controls.Add(this.pnlTotal);
            this.pnlPlayList.Dock = System.Windows.Forms.DockStyle.Right;
            this.pnlPlayList.Location = new System.Drawing.Point(455, 0);
            this.pnlPlayList.Name = "pnlPlayList";
            this.pnlPlayList.Size = new System.Drawing.Size(210, 413);
            this.pnlPlayList.TabIndex = 5;
            // 
            // treeList1
            // 
            this.treeList1.Columns.AddRange(new DevExpress.XtraTreeList.Columns.TreeListColumn[] {
            this.colName,
            this.colLength,
            this.colObject});
            this.treeList1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeList1.Location = new System.Drawing.Point(2, 37);
            this.treeList1.Name = "treeList1";
            this.treeList1.OptionsBehavior.Editable = false;
            this.treeList1.OptionsMenu.EnableColumnMenu = false;
            this.treeList1.OptionsMenu.EnableFooterMenu = false;
            this.treeList1.OptionsSelection.EnableAppearanceFocusedCell = false;
            this.treeList1.OptionsView.ShowHorzLines = false;
            this.treeList1.OptionsView.ShowIndicator = false;
            this.treeList1.OptionsView.ShowVertLines = false;
            this.treeList1.Size = new System.Drawing.Size(206, 339);
            this.treeList1.StateImageList = this.imageCollection1;
            this.treeList1.TabIndex = 16;
            this.treeList1.AfterFocusNode += new DevExpress.XtraTreeList.NodeEventHandler(this.treeList1_AfterFocusNode);
            this.treeList1.BeforeFocusNode += new DevExpress.XtraTreeList.BeforeFocusNodeEventHandler(this.treeList1_BeforeFocusNode);
            this.treeList1.DragObjectStart += new DevExpress.XtraTreeList.DragObjectStartEventHandler(this.treeList1_DragObjectStart);
            // 
            // colName
            // 
            this.colName.Caption = "Name";
            this.colName.FieldName = "Name";
            this.colName.Name = "colName";
            this.colName.OptionsColumn.AllowSort = false;
            this.colName.Visible = true;
            this.colName.VisibleIndex = 0;
            // 
            // colLength
            // 
            this.colLength.Caption = "Length";
            this.colLength.FieldName = "Length";
            this.colLength.Name = "colLength";
            this.colLength.OptionsColumn.AllowSort = false;
            this.colLength.Visible = true;
            this.colLength.VisibleIndex = 1;
            // 
            // colObject
            // 
            this.colObject.Caption = "Message";
            this.colObject.FieldName = "Message";
            this.colObject.Name = "colObject";
            this.colObject.OptionsColumn.AllowSort = false;
            // 
            // imageCollection1
            // 
            this.imageCollection1.ImageStream = ((DevExpress.Utils.ImageCollectionStreamer)(resources.GetObject("imageCollection1.ImageStream")));
            // 
            // panelControl1
            // 
            this.panelControl1.Appearance.BackColor = System.Drawing.Color.LightGray;
            this.panelControl1.Appearance.Options.UseBackColor = true;
            this.panelControl1.Controls.Add(this.lblTitle);
            this.panelControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelControl1.Location = new System.Drawing.Point(2, 2);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(206, 35);
            this.panelControl1.TabIndex = 15;
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.BackColor = System.Drawing.Color.LightGray;
            this.lblTitle.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.lblTitle.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTitle.Location = new System.Drawing.Point(5, 10);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(119, 14);
            this.lblTitle.TabIndex = 9;
            this.lblTitle.Text = "CURRENT PLAYLIST";
            // 
            // pnlTotal
            // 
            this.pnlTotal.Appearance.BackColor = System.Drawing.Color.LightGray;
            this.pnlTotal.Appearance.Options.UseBackColor = true;
            this.pnlTotal.Controls.Add(this.lblTotalList);
            this.pnlTotal.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlTotal.Location = new System.Drawing.Point(2, 376);
            this.pnlTotal.Name = "pnlTotal";
            this.pnlTotal.Size = new System.Drawing.Size(206, 35);
            this.pnlTotal.TabIndex = 13;
            // 
            // lblTotalList
            // 
            this.lblTotalList.AutoSize = true;
            this.lblTotalList.BackColor = System.Drawing.Color.LightGray;
            this.lblTotalList.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.lblTotalList.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTotalList.Location = new System.Drawing.Point(19, 10);
            this.lblTotalList.Name = "lblTotalList";
            this.lblTotalList.Size = new System.Drawing.Size(49, 14);
            this.lblTotalList.TabIndex = 13;
            this.lblTotalList.Text = "Total:";
            // 
            // PlayBar
            // 
            this.PlayBar.AutoSize = false;
            this.PlayBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.PlayBar.Location = new System.Drawing.Point(0, 413);
            this.PlayBar.Name = "PlayBar";
            this.PlayBar.Size = new System.Drawing.Size(665, 29);
            this.PlayBar.TabIndex = 1;
            this.PlayBar.TickStyle = System.Windows.Forms.TickStyle.None;
            // 
            // pnlStatus
            // 
            this.pnlStatus.BackColor = System.Drawing.Color.Transparent;
            this.pnlStatus.Controls.Add(this.lblCurName);
            this.pnlStatus.Controls.Add(this.lblSplit);
            this.pnlStatus.Controls.Add(this.lblTotalTime);
            this.pnlStatus.Controls.Add(this.lblCurTime);
            this.pnlStatus.Dock = System.Windows.Forms.DockStyle.Right;
            this.pnlStatus.Location = new System.Drawing.Point(298, 0);
            this.pnlStatus.Name = "pnlStatus";
            this.pnlStatus.Size = new System.Drawing.Size(367, 41);
            this.pnlStatus.TabIndex = 9;
            // 
            // lblCurName
            // 
            this.lblCurName.AutoSize = true;
            this.lblCurName.Location = new System.Drawing.Point(22, 9);
            this.lblCurName.Name = "lblCurName";
            this.lblCurName.Size = new System.Drawing.Size(0, 13);
            this.lblCurName.TabIndex = 12;
            // 
            // lblSplit
            // 
            this.lblSplit.AutoSize = true;
            this.lblSplit.BackColor = System.Drawing.Color.Transparent;
            this.lblSplit.Location = new System.Drawing.Point(310, 10);
            this.lblSplit.Name = "lblSplit";
            this.lblSplit.Size = new System.Drawing.Size(11, 13);
            this.lblSplit.TabIndex = 11;
            this.lblSplit.Text = "/";
            // 
            // lblTotalTime
            // 
            this.lblTotalTime.AutoSize = true;
            this.lblTotalTime.BackColor = System.Drawing.Color.Transparent;
            this.lblTotalTime.Location = new System.Drawing.Point(326, 10);
            this.lblTotalTime.Name = "lblTotalTime";
            this.lblTotalTime.Size = new System.Drawing.Size(29, 13);
            this.lblTotalTime.TabIndex = 10;
            this.lblTotalTime.Text = "0:00";
            // 
            // lblCurTime
            // 
            this.lblCurTime.AutoSize = true;
            this.lblCurTime.BackColor = System.Drawing.Color.Transparent;
            this.lblCurTime.Location = new System.Drawing.Point(274, 10);
            this.lblCurTime.Name = "lblCurTime";
            this.lblCurTime.Size = new System.Drawing.Size(29, 13);
            this.lblCurTime.TabIndex = 9;
            this.lblCurTime.Text = "0:00";
            // 
            // pnlPlayButton
            // 
            this.pnlPlayButton.BackColor = System.Drawing.Color.Transparent;
            this.pnlPlayButton.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pnlPlayButton.BackgroundImage")));
            this.pnlPlayButton.Controls.Add(this.btnPlay);
            this.pnlPlayButton.Controls.Add(this.btnNext);
            this.pnlPlayButton.Controls.Add(this.btnPrevious);
            this.pnlPlayButton.Controls.Add(this.btnStop);
            this.pnlPlayButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlPlayButton.Location = new System.Drawing.Point(0, 0);
            this.pnlPlayButton.Name = "pnlPlayButton";
            this.pnlPlayButton.Size = new System.Drawing.Size(196, 41);
            this.pnlPlayButton.TabIndex = 5;
            // 
            // btnPlay
            // 
            this.btnPlay.BackColor = System.Drawing.Color.Transparent;
            this.btnPlay.DisabledImage = ((System.Drawing.Image)(resources.GetObject("btnPlay.DisabledImage")));
            this.btnPlay.HoverImage = ((System.Drawing.Image)(resources.GetObject("btnPlay.HoverImage")));
            this.btnPlay.Location = new System.Drawing.Point(15, 2);
            this.btnPlay.Name = "btnPlay";
            this.btnPlay.NormalImage = ((System.Drawing.Image)(resources.GetObject("btnPlay.NormalImage")));
            this.btnPlay.PushedImage = ((System.Drawing.Image)(resources.GetObject("btnPlay.PushedImage")));
            this.btnPlay.Size = new System.Drawing.Size(38, 41);
            this.btnPlay.TabIndex = 0;
            this.btnPlay.Text = "Play";
            this.btnToolTip.SetToolTip(this.btnPlay, "Play");
            this.btnPlay.Click += new System.EventHandler(this.btnPlay_Click);
            // 
            // btnNext
            // 
            this.btnNext.BackColor = System.Drawing.Color.Transparent;
            this.btnNext.DisabledImage = ((System.Drawing.Image)(resources.GetObject("btnNext.DisabledImage")));
            this.btnNext.HoverImage = ((System.Drawing.Image)(resources.GetObject("btnNext.HoverImage")));
            this.btnNext.Location = new System.Drawing.Point(124, 11);
            this.btnNext.Name = "btnNext";
            this.btnNext.NormalImage = ((System.Drawing.Image)(resources.GetObject("btnNext.NormalImage")));
            this.btnNext.PushedImage = ((System.Drawing.Image)(resources.GetObject("btnNext.PushedImage")));
            this.btnNext.Size = new System.Drawing.Size(27, 29);
            this.btnNext.TabIndex = 3;
            this.btnNext.Text = "Play Next";
            this.btnToolTip.SetToolTip(this.btnNext, "Play Next");
            this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
            // 
            // btnPrevious
            // 
            this.btnPrevious.BackColor = System.Drawing.Color.Transparent;
            this.btnPrevious.DisabledImage = ((System.Drawing.Image)(resources.GetObject("btnPrevious.DisabledImage")));
            this.btnPrevious.HoverImage = ((System.Drawing.Image)(resources.GetObject("btnPrevious.HoverImage")));
            this.btnPrevious.Location = new System.Drawing.Point(97, 11);
            this.btnPrevious.Name = "btnPrevious";
            this.btnPrevious.NormalImage = ((System.Drawing.Image)(resources.GetObject("btnPrevious.NormalImage")));
            this.btnPrevious.PushedImage = ((System.Drawing.Image)(resources.GetObject("btnPrevious.PushedImage")));
            this.btnPrevious.Size = new System.Drawing.Size(27, 29);
            this.btnPrevious.TabIndex = 2;
            this.btnPrevious.Text = "Play Previous";
            this.btnToolTip.SetToolTip(this.btnPrevious, "Play Previous");
            this.btnPrevious.Click += new System.EventHandler(this.btnPrevious_Click);
            // 
            // btnStop
            // 
            this.btnStop.BackColor = System.Drawing.Color.Transparent;
            this.btnStop.DisabledImage = ((System.Drawing.Image)(resources.GetObject("btnStop.DisabledImage")));
            this.btnStop.HoverImage = ((System.Drawing.Image)(resources.GetObject("btnStop.HoverImage")));
            this.btnStop.Location = new System.Drawing.Point(53, 2);
            this.btnStop.Name = "btnStop";
            this.btnStop.NormalImage = ((System.Drawing.Image)(resources.GetObject("btnStop.NormalImage")));
            this.btnStop.PushedImage = ((System.Drawing.Image)(resources.GetObject("btnStop.PushedImage")));
            this.btnStop.Size = new System.Drawing.Size(22, 41);
            this.btnStop.TabIndex = 1;
            this.btnStop.Text = "Stop";
            this.btnToolTip.SetToolTip(this.btnStop, "Stop");
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // picPlayBar
            // 
            this.picPlayBar.BackColor = System.Drawing.Color.Transparent;
            this.picPlayBar.Image = ((System.Drawing.Image)(resources.GetObject("picPlayBar.Image")));
            this.picPlayBar.Location = new System.Drawing.Point(194, 0);
            this.picPlayBar.Name = "picPlayBar";
            this.picPlayBar.Size = new System.Drawing.Size(98, 53);
            this.picPlayBar.TabIndex = 4;
            this.picPlayBar.TabStop = false;
            // 
            // PlayForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(665, 485);
            this.Controls.Add(this.splitContainer1);
            this.MinimumSize = new System.Drawing.Size(673, 505);
            this.Name = "PlayForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Playlist Player";
            this.Load += new System.EventHandler(this.PlayForm_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.PlayForm_FormClosed);
            this.Resize += new System.EventHandler(this.PlayForm_Resize);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.pnlParent.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pnlPlayList)).EndInit();
            this.pnlPlayList.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.treeList1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imageCollection1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            this.panelControl1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlTotal)).EndInit();
            this.pnlTotal.ResumeLayout(false);
            this.pnlTotal.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PlayBar)).EndInit();
            this.pnlStatus.ResumeLayout(false);
            this.pnlStatus.PerformLayout();
            this.pnlPlayButton.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picPlayBar)).EndInit();
            this.ResumeLayout(false);

        }


        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TrackBar PlayBar;
        private ImageButton btnPlay;
        private ImageButton btnStop;
        private ImageButton btnPrevious;
        private ImageButton btnNext;
        private ToolTip btnToolTip;
        private System.Windows.Forms.PictureBox picPlayBar;
        private System.Windows.Forms.Panel pnlPlayButton;
        private DevExpress.XtraEditors.PanelControl pnlPlayList;
        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.Panel pnlParent;
        private System.Windows.Forms.Panel pnlPlay;
        private System.Windows.Forms.Panel pnlStatus;
        private System.Windows.Forms.Label lblCurName;
        private System.Windows.Forms.Label lblSplit;
        private System.Windows.Forms.Label lblTotalTime;
        private System.Windows.Forms.Label lblCurTime;
        private DevExpress.XtraEditors.PanelControl pnlTotal;
        private System.Windows.Forms.Label lblTotalList;
        private System.Windows.Forms.Label lblButton;
        private System.Windows.Forms.Label lblTop;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraTreeList.TreeList treeList1;
        private DevExpress.XtraTreeList.Columns.TreeListColumn colName;
        private DevExpress.XtraTreeList.Columns.TreeListColumn colLength;
        private DevExpress.XtraTreeList.Columns.TreeListColumn colObject;
        private DevExpress.Utils.ImageCollection imageCollection1;
    }
}