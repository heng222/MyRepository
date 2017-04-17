using DevExpress.XtraNavBar;
namespace ProWrite.UI.Controls.Editor
{
    partial class MessageControl
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
            UnSubscribeEvent();
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MessageControl));
            this.splitContainer = new DevExpress.XtraEditors.SplitContainerControl();
            this.playPanel = new System.Windows.Forms.Panel();
            this.editPanel = new System.Windows.Forms.Panel();
            this.shapeControl = new ProWrite.UI.Controls.Editor.Canvas();
            this.lblSlide = new System.Windows.Forms.Label();
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.lblRecycle = new DevExpress.XtraEditors.SimpleButton();
            this.btnThumbNailImage = new DevExpress.XtraEditors.SimpleButton();

            this.lblNew = new DevExpress.XtraEditors.SimpleButton();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.hScrollBar = new DevExpress.XtraEditors.HScrollBar();
            this.layerEditor = new DevExpress.XtraNavBar.NavBarControl();
            this.dynamicGroup = new DevExpress.XtraNavBar.NavBarGroup();
            //this.masterLayerGroup = new DevExpress.XtraNavBar.NavBarGroup();

            this._dynamicContainer = new DevExpress.XtraNavBar.NavBarGroupControlContainer();
            this._staticContainer = new DevExpress.XtraNavBar.NavBarGroupControlContainer();
            //this._masterLayerContainer = new DevExpress.XtraNavBar.NavBarGroupControlContainer();

            this.staticGroup = new DevExpress.XtraNavBar.NavBarGroup();
            this.panelControl2 = new DevExpress.XtraEditors.PanelControl();
            this.playStopBar = new ProWrite.UI.Controls.PlayStopBar();
            //this.trackBar1 = new ProWrite.UI.Controls.TrackBar();
            this.trackBar1 = new ProWrite.UI.Controls.TrackBarNew();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
            this.splitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.layerEditor)).BeginInit();
            this.layerEditor.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).BeginInit();
            this.panelControl2.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer
            // 

            this.splitContainer.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Horizontal = false;
            this.splitContainer.Location = new System.Drawing.Point(0, 0);
            this.splitContainer.Name = "splitContainer";
            this.splitContainer.Panel1.Controls.Add(this.editPanel);
            this.splitContainer.Panel1.Text = "Panel1";
            this.splitContainer.Panel2.Controls.Add(this.lblSlide);
            this.splitContainer.Panel2.Controls.Add(this.panelControl1);
            this.splitContainer.Panel2.Controls.Add(this.layerEditor);
            this.splitContainer.Panel2.Controls.Add(this.panelControl2);
            this.splitContainer.Panel2.Text = "Panel2";
            this.splitContainer.Size = new System.Drawing.Size(723, 628);
            this.splitContainer.SplitterPosition = 250;
            this.splitContainer.TabIndex = 3;
            this.splitContainer.Text = "splitContainerControl1";
            this.splitContainer.Panel1.Resize += new System.EventHandler(this.splitContainer_Resize);
            this.splitContainer.Panel2.Resize += new System.EventHandler(Panel2_Resize);
            // 
            // playPanel
            // 
            this.playPanel.Location = new System.Drawing.Point(26, 30);
            this.playPanel.Name = "playPanel";
            this.playPanel.Size = new System.Drawing.Size(50, 30);
            this.playPanel.TabIndex = 4;

            // 
            // editPanel
            // 
            this.editPanel.AutoScroll = true;
            this.editPanel.Name = "editPanel";
            this.editPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.editPanel.Location = new System.Drawing.Point(0, 0);
            this.editPanel.Controls.Add(this.playPanel);
            this.editPanel.Controls.Add(this.shapeControl);
            this.editPanel.TabIndex = 2;

            // 
            // shapeControl
            // 
            this.shapeControl.AllowDrop = true;
            this.shapeControl.BackColor = System.Drawing.Color.Black;
            this.shapeControl.ForeColor = System.Drawing.SystemColors.ActiveBorder;
            this.shapeControl.Location = new System.Drawing.Point(17, 28);
            this.shapeControl.Name = "shapeControl";
            this.shapeControl.Size = new System.Drawing.Size(522, 174);
            this.shapeControl.TabIndex = 3;
            this.shapeControl.Text = "container1";
            // 
            // lblSlide
            // 
            this.lblSlide.BackColor = System.Drawing.Color.Black;
            this.lblSlide.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblSlide.Location = new System.Drawing.Point(201, 37);
            this.lblSlide.Name = "lblSlide";
            this.lblSlide.Size = new System.Drawing.Size(1, 208);
            this.lblSlide.TabIndex = 19;
            // 
            // panelControl1
            // 
            this.panelControl1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.panelControl1.Controls.Add(this.lblRecycle);
            this.panelControl1.Controls.Add(this.btnThumbNailImage);
            this.panelControl1.Controls.Add(this.btnSave);
            this.panelControl1.Controls.Add(this.lblNew);
            this.panelControl1.Controls.Add(this.hScrollBar);
            this.panelControl1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelControl1.Location = new System.Drawing.Point(0, 333);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(719, 35);
            this.panelControl1.Resize += new System.EventHandler(this.panelControl1_Resize);
            this.panelControl1.TabIndex = 22;
            // 
            // lblRecycle
            // 
            this.lblRecycle.AllowDrop = true;
            this.lblRecycle.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblRecycle.Location = new System.Drawing.Point(68, 2);
            this.lblRecycle.Name = "lblRecycle";
            this.lblRecycle.Size = new System.Drawing.Size(25, 31);
            this.lblRecycle.TabIndex = 15;
            this.lblRecycle.ToolTip = "Delete";
            // 
            // btnThumbNailImage
            // 
            this.btnThumbNailImage.AllowDrop = true;
            this.btnThumbNailImage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnThumbNailImage.Location = new System.Drawing.Point(168, 5);
            this.btnThumbNailImage.Name = "btnThumbNailImage";
            this.btnThumbNailImage.Size = new System.Drawing.Size(25, 25);
            this.btnThumbNailImage.TabIndex = 15;
            this.btnThumbNailImage.ToolTip = "Set Thumbnail Image";
            this.btnThumbNailImage.Image = Resources.Resource.GetImage(Resources.Resource.Images.Xiangji16);
            this.btnThumbNailImage.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleCenter;
            this.btnThumbNailImage.Click += new System.EventHandler(btnThumbNailImage_Click);
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleCenter;
            this.btnSave.Location = new System.Drawing.Point(37, 2);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(25, 31);
            this.btnSave.TabIndex = 14;
            this.btnSave.ToolTip = "Save";
            // 
            // lblNew
            // 
            this.lblNew.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblNew.Location = new System.Drawing.Point(6, 2);
            this.lblNew.Name = "lblNew";
            this.lblNew.Size = new System.Drawing.Size(25, 31);
            this.lblNew.TabIndex = 13;
            this.lblNew.ToolTip = "Add";
            // 
            // hScrollBar
            // 
            //this.hScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
            //            | System.Windows.Forms.AnchorStyles.Right)));
            this.hScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        )));
            this.hScrollBar.LargeChange = 20;
            this.hScrollBar.Location = new System.Drawing.Point(203, 8);
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.LookAndFeel.UseDefaultLookAndFeel = false;
            this.hScrollBar.LookAndFeel.SkinName = "Blue"; 
            this.hScrollBar.Size = new System.Drawing.Size(511, 18);
            this.hScrollBar.SmallChange = 10;
            this.hScrollBar.TabIndex = 1;

            // layerEditor
            // 
            this.layerEditor.ActiveGroup = this.dynamicGroup;
            this.layerEditor.ContentButtonHint = null;
            this.layerEditor.Controls.Add(this._dynamicContainer);
            this.layerEditor.Controls.Add(this._staticContainer);
            //this.layerEditor.Controls.Add(this._masterLayerContainer);
            this.layerEditor.Dock = System.Windows.Forms.DockStyle.Top;
            this.layerEditor.Groups.AddRange(new DevExpress.XtraNavBar.NavBarGroup[] {
            this.dynamicGroup,
            this.staticGroup/*,
            this.masterLayerGroup*/});
            this.layerEditor.Location = new System.Drawing.Point(0, 46);
            this.layerEditor.Name = "layerEditor";
            this.layerEditor.OptionsNavPane.ExpandedWidth = 696;
            this.layerEditor.Size = new System.Drawing.Size(719, 268);
            this.layerEditor.TabIndex = 21;
            this.layerEditor.Text = "frameLayerContainerNew1";
            this.layerEditor.SkinExplorerBarViewScrollStyle = SkinExplorerBarViewScrollStyle.ScrollBar;
            // 
            // dynamicGroup
            // 
            this.dynamicGroup.Caption = "Dynamic Layers";
            this.dynamicGroup.ControlContainer = this._dynamicContainer;
            this.dynamicGroup.GroupClientHeight = 215;
            this.dynamicGroup.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.dynamicGroup.Name = "dynamicGroup";
            // 
            // _dynamicContainer
            // 
            this._dynamicContainer.Name = "_dynamicContainer";
            this._dynamicContainer.Size = new System.Drawing.Size(715, 215);
            this._dynamicContainer.TabIndex = 0;
            // 
            // _staticContainer
            // 
            this._staticContainer.Name = "_staticContainer";
            this._staticContainer.Size = new System.Drawing.Size(715, 215);
            this._staticContainer.TabIndex = 1;
            //
            // _masterLayerContainer
            // 
            //this._masterLayerContainer.Name = "_masterLayerContainer";
            //this._masterLayerContainer.Size = new System.Drawing.Size(715, 40);
            //this._masterLayerContainer.TabIndex = 2;
            // 
            // staticGroup
            // 
            this.staticGroup.Caption = "Static Layers";
            this.staticGroup.ControlContainer = this._staticContainer;
            this.staticGroup.Expanded = true;
            this.staticGroup.GroupClientHeight = 215;
            this.staticGroup.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.staticGroup.Name = "staticGroup";
            //
            // masterLayersGroup
            //
            //this.masterLayerGroup.Caption = "Master Layer";
            //this.masterLayerGroup.ControlContainer = this._masterLayerContainer;
            //this.masterLayerGroup.Expanded = true;
            //this.masterLayerGroup.GroupClientHeight = 30;
            //this.masterLayerGroup.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            //this.masterLayerGroup.Name = "masterLayerGroup";
            // 
            // panelControl2
            // 
            this.panelControl2.Appearance.BackColor = System.Drawing.SystemColors.Control;
            this.panelControl2.Appearance.Options.UseBackColor = true;
            this.panelControl2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.panelControl2.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panelControl2.Controls.Add(this.playStopBar);
            this.panelControl2.Controls.Add(this.trackBar1);
            this.panelControl2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelControl2.Location = new System.Drawing.Point(0, 0);
            this.panelControl2.Name = "panelControl2";
            this.panelControl2.Size = new System.Drawing.Size(719, 46);
            this.panelControl2.TabIndex = 20;
            // 
            // playStopBar
            // 
			//this.playStopBar.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("playStopBar.BackgroundImage")));
            this.playStopBar.IsSupportGlobalization = false;
            this.playStopBar.Location = new System.Drawing.Point(1, 2);
            this.playStopBar.Name = "playStopBar";
            this.playStopBar.Size = new System.Drawing.Size(194, 44);
            this.playStopBar.TabIndex = 5;
            // 
            // TrackBar
            // 
            this.trackBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trackBar1.BackColor = System.Drawing.Color.Transparent;
            //this.trackBar1.InitialStep = 5;
            //this.trackBar1.LargeChange = 14;
            this.trackBar1.LblSlide = null;
            this.trackBar1.Location = new System.Drawing.Point(189, 2);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.PlayValue = 0;
            //this.trackBar1.ScaleBarCurrentPosition = 12;
            this.trackBar1.Size = new System.Drawing.Size(528, 44);
            this.trackBar1.SlideOffset = 0;
            //this.trackBar1.SlideRelativeValue = 9;
            //this.trackBar1.SlideValue = 12;
            //this.trackBar1.SmallChange = 14;
            this.trackBar1.TabIndex = 8;
            //this.trackBar1.TickFrequency = 5;
            this.trackBar1.TimeEnd = 0;
            // 
            // MessageControlNew
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer);
            this.Name = "MessageControlNew";
            this.Size = new System.Drawing.Size(723, 628);

            ((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
            this.splitContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.layerEditor)).EndInit();
            this.layerEditor.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).EndInit();
            this.panelControl2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.SplitContainerControl splitContainer;
        private System.Windows.Forms.Panel playPanel;
        private System.Windows.Forms.Panel editPanel;
        private Canvas shapeControl;
        private PlayStopBar playStopBar;
        private System.Windows.Forms.Label lblSlide;
        private DevExpress.XtraEditors.PanelControl panelControl2;
        //private TrackBar trackBar1;
        private TrackBarNew trackBar1;
        private NavBarControl layerEditor;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.SimpleButton lblRecycle;
        private DevExpress.XtraEditors.SimpleButton lblNew;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private DevExpress.XtraEditors.SimpleButton btnThumbNailImage;
        private DevExpress.XtraEditors.HScrollBar hScrollBar;
        private NavBarGroup dynamicGroup;
        private NavBarGroupControlContainer _dynamicContainer;
        private NavBarGroupControlContainer _staticContainer;
        //private NavBarGroupControlContainer _masterLayerContainer;
        private NavBarGroup staticGroup;
        //private NavBarGroup masterLayerGroup;
    }
}
