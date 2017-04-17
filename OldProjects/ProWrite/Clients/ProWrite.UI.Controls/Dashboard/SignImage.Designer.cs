namespace ProWrite.UI.Controls.Dashboard
{
	partial class SignImage
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SignImage));
            this.xtraTabControl1 = new DevExpress.XtraTab.XtraTabControl();
            this.xtraTabPage1 = new DevExpress.XtraTab.XtraTabPage();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.simpleButton1 = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.picLiveView = new DevExpress.XtraEditors.PictureEdit();
            this.xtraTabPage2 = new DevExpress.XtraTab.XtraTabPage();
            this.lblNA = new DevExpress.XtraEditors.LabelControl();
            this.btnRefreshSignImage = new DevExpress.XtraEditors.SimpleButton();
            this.lblLastUpdate = new DevExpress.XtraEditors.LabelControl();
            this.picWebCam = new DevExpress.XtraEditors.PictureEdit();
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).BeginInit();
            this.xtraTabControl1.SuspendLayout();
            this.xtraTabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picLiveView.Properties)).BeginInit();
            this.xtraTabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picWebCam.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // xtraTabControl1
            // 
            this.xtraTabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.xtraTabControl1.HeaderLocation = DevExpress.XtraTab.TabHeaderLocation.Bottom;
            this.xtraTabControl1.Location = new System.Drawing.Point(0, 0);
            this.xtraTabControl1.Name = "xtraTabControl1";
            this.xtraTabControl1.SelectedTabPage = this.xtraTabPage1;
            this.xtraTabControl1.Size = new System.Drawing.Size(268, 242);
            this.xtraTabControl1.TabIndex = 9;
            this.xtraTabControl1.TabPages.AddRange(new DevExpress.XtraTab.XtraTabPage[] {
            this.xtraTabPage1,
            this.xtraTabPage2});
            // 
            // xtraTabPage1
            // 
            this.xtraTabPage1.Controls.Add(this.labelControl1);
            this.xtraTabPage1.Controls.Add(this.simpleButton1);
            this.xtraTabPage1.Controls.Add(this.labelControl2);
            this.xtraTabPage1.Controls.Add(this.picLiveView);
            this.xtraTabPage1.Name = "xtraTabPage1";
            this.xtraTabPage1.Size = new System.Drawing.Size(259, 211);
            this.xtraTabPage1.Text = "Sign Photo";
            // 
            // labelControl1
            // 
            this.labelControl1.Enabled = false;
            this.labelControl1.Location = new System.Drawing.Point(101, 192);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(18, 13);
            this.labelControl1.TabIndex = 19;
            this.labelControl1.Text = "N/A";
            // 
            // simpleButton1
            // 
            this.simpleButton1.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.simpleButton1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.simpleButton1.Enabled = false;
            this.simpleButton1.Image = ((System.Drawing.Image)(resources.GetObject("simpleButton1.Image")));
            this.simpleButton1.Location = new System.Drawing.Point(0, 190);
            this.simpleButton1.Name = "simpleButton1";
            this.simpleButton1.Size = new System.Drawing.Size(22, 16);
            this.simpleButton1.TabIndex = 17;
            this.simpleButton1.ToolTip = "Refresh";
            // 
            // labelControl2
            // 
            this.labelControl2.Enabled = false;
            this.labelControl2.Location = new System.Drawing.Point(27, 192);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(68, 13);
            this.labelControl2.TabIndex = 18;
            this.labelControl2.Text = "Last Updated:";
            // 
            // picLiveView
            // 
            this.picLiveView.Dock = System.Windows.Forms.DockStyle.Top;
            this.picLiveView.Location = new System.Drawing.Point(0, 0);
            this.picLiveView.Name = "picLiveView";
            this.picLiveView.Properties.ReadOnly = true;
            this.picLiveView.Properties.ShowMenu = false;
            this.picLiveView.Properties.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;
            this.picLiveView.Size = new System.Drawing.Size(259, 180);
            this.picLiveView.TabIndex = 13;
            this.picLiveView.ToolTip = "Sign Image";
            this.picLiveView.DoubleClick += new System.EventHandler(this.picLiveView_DoubleClick);
            // 
            // xtraTabPage2
            // 
            this.xtraTabPage2.Controls.Add(this.lblNA);
            this.xtraTabPage2.Controls.Add(this.btnRefreshSignImage);
            this.xtraTabPage2.Controls.Add(this.lblLastUpdate);
            this.xtraTabPage2.Controls.Add(this.picWebCam);
            this.xtraTabPage2.Name = "xtraTabPage2";
            this.xtraTabPage2.Size = new System.Drawing.Size(259, 211);
            this.xtraTabPage2.Text = "Web Cam";
            // 
            // lblNA
            // 
            this.lblNA.Enabled = false;
            this.lblNA.Location = new System.Drawing.Point(101, 192);
            this.lblNA.Name = "lblNA";
            this.lblNA.Size = new System.Drawing.Size(18, 13);
            this.lblNA.TabIndex = 19;
            this.lblNA.Text = "N/A";
            // 
            // btnRefreshSignImage
            // 
            this.btnRefreshSignImage.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.btnRefreshSignImage.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnRefreshSignImage.Image = ((System.Drawing.Image)(resources.GetObject("btnRefreshSignImage.Image")));
            this.btnRefreshSignImage.Location = new System.Drawing.Point(0, 190);
            this.btnRefreshSignImage.Name = "btnRefreshSignImage";
            this.btnRefreshSignImage.Size = new System.Drawing.Size(22, 16);
            this.btnRefreshSignImage.TabIndex = 17;
            this.btnRefreshSignImage.ToolTip = "Refresh";
            this.btnRefreshSignImage.Click += new System.EventHandler(this.btnRefreshSignImage_Click);
            // 
            // lblLastUpdate
            // 
            this.lblLastUpdate.Enabled = false;
            this.lblLastUpdate.Location = new System.Drawing.Point(27, 192);
            this.lblLastUpdate.Name = "lblLastUpdate";
            this.lblLastUpdate.Size = new System.Drawing.Size(68, 13);
            this.lblLastUpdate.TabIndex = 18;
            this.lblLastUpdate.Text = "Last Updated:";
            // 
            // picWebCam
            // 
            this.picWebCam.Dock = System.Windows.Forms.DockStyle.Top;
            this.picWebCam.Location = new System.Drawing.Point(0, 0);
            this.picWebCam.Name = "picWebCam";
            this.picWebCam.Properties.ReadOnly = true;
            this.picWebCam.Properties.ShowMenu = false;
            this.picWebCam.Properties.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;
            this.picWebCam.Size = new System.Drawing.Size(259, 180);
            this.picWebCam.TabIndex = 13;
            this.picWebCam.ToolTip = "Sign Image";
            // 
            // SignImage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.xtraTabControl1);
            this.Name = "SignImage";
            this.Size = new System.Drawing.Size(268, 242);
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).EndInit();
            this.xtraTabControl1.ResumeLayout(false);
            this.xtraTabPage1.ResumeLayout(false);
            this.xtraTabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picLiveView.Properties)).EndInit();
            this.xtraTabPage2.ResumeLayout(false);
            this.xtraTabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picWebCam.Properties)).EndInit();
            this.ResumeLayout(false);

		}

		#endregion

        private DevExpress.XtraTab.XtraTabControl xtraTabControl1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage2;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.SimpleButton simpleButton1;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.PictureEdit picLiveView;
        private DevExpress.XtraEditors.LabelControl lblNA;
        private DevExpress.XtraEditors.SimpleButton btnRefreshSignImage;
        private DevExpress.XtraEditors.LabelControl lblLastUpdate;
        private DevExpress.XtraEditors.PictureEdit picWebCam;
	}
}
