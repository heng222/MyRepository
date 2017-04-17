namespace ProWrite.UI.Controls.Dashboard
{
	partial class CurrentClip
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CurrentClip));
            this.picCurrent = new DevExpress.XtraEditors.PictureEdit();
            this.lblMessage = new System.Windows.Forms.Label();
            this.lblScheduler = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtMessage = new DevExpress.XtraEditors.TextEdit();
            this.txtSchedule = new DevExpress.XtraEditors.TextEdit();
            this.txtPlaylist = new DevExpress.XtraEditors.TextEdit();
            this.panel1 = new System.Windows.Forms.Panel();
            this.lblNA = new DevExpress.XtraEditors.LabelControl();
            this.btnRefresh = new DevExpress.XtraEditors.SimpleButton();
            this.lblLastUpdate = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.picCurrent.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtMessage.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtSchedule.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPlaylist.Properties)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // picCurrent
            // 
            this.picCurrent.Dock = System.Windows.Forms.DockStyle.Top;
            this.picCurrent.Location = new System.Drawing.Point(0, 0);
            this.picCurrent.Name = "picCurrent";
            this.picCurrent.Properties.ShowMenu = false;
            this.picCurrent.Properties.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;
            this.picCurrent.Size = new System.Drawing.Size(199, 142);
            this.picCurrent.TabIndex = 2;
            this.picCurrent.ToolTip = "Current Clip";
            // 
            // lblMessage
            // 
            this.lblMessage.AutoSize = true;
            this.lblMessage.Location = new System.Drawing.Point(4, 171);
            this.lblMessage.Name = "lblMessage";
            this.lblMessage.Size = new System.Drawing.Size(53, 13);
            this.lblMessage.TabIndex = 3;
            this.lblMessage.Text = "Message:";
            // 
            // lblScheduler
            // 
            this.lblScheduler.AutoSize = true;
            this.lblScheduler.Location = new System.Drawing.Point(4, 210);
            this.lblScheduler.Name = "lblScheduler";
            this.lblScheduler.Size = new System.Drawing.Size(54, 13);
            this.lblScheduler.TabIndex = 3;
            this.lblScheduler.Text = "Schedule:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 248);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Playlist:";
            // 
            // txtMessage
            // 
            this.txtMessage.EditValue = "N/A";
            this.txtMessage.Location = new System.Drawing.Point(3, 187);
            this.txtMessage.Name = "txtMessage";
            this.txtMessage.Size = new System.Drawing.Size(182, 20);
            this.txtMessage.TabIndex = 4;
            // 
            // txtSchedule
            // 
            this.txtSchedule.EditValue = "N/A";
            this.txtSchedule.Location = new System.Drawing.Point(3, 226);
            this.txtSchedule.Name = "txtSchedule";
            this.txtSchedule.Size = new System.Drawing.Size(182, 20);
            this.txtSchedule.TabIndex = 4;
            // 
            // txtPlaylist
            // 
            this.txtPlaylist.EditValue = "N/A";
            this.txtPlaylist.Location = new System.Drawing.Point(3, 265);
            this.txtPlaylist.Name = "txtPlaylist";
            this.txtPlaylist.Size = new System.Drawing.Size(182, 20);
            this.txtPlaylist.TabIndex = 4;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.lblNA);
            this.panel1.Controls.Add(this.btnRefresh);
            this.panel1.Controls.Add(this.lblLastUpdate);
            this.panel1.Controls.Add(this.picCurrent);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(199, 168);
            this.panel1.TabIndex = 5;
            // 
            // lblNA
            // 
            this.lblNA.Enabled = false;
            this.lblNA.Location = new System.Drawing.Point(103, 150);
            this.lblNA.Name = "lblNA";
            this.lblNA.Size = new System.Drawing.Size(18, 13);
            this.lblNA.TabIndex = 22;
            this.lblNA.Text = "N/A";
            // 
            // btnRefresh
            // 
            this.btnRefresh.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.btnRefresh.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnRefresh.Enabled = false;
            this.btnRefresh.Image = ((System.Drawing.Image)(resources.GetObject("btnRefresh.Image")));
            this.btnRefresh.Location = new System.Drawing.Point(5, 148);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(22, 16);
            this.btnRefresh.TabIndex = 20;
            this.btnRefresh.ToolTip = "Refresh";
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // lblLastUpdate
            // 
            this.lblLastUpdate.Enabled = false;
            this.lblLastUpdate.Location = new System.Drawing.Point(33, 150);
            this.lblLastUpdate.Name = "lblLastUpdate";
            this.lblLastUpdate.Size = new System.Drawing.Size(68, 13);
            this.lblLastUpdate.TabIndex = 21;
            this.lblLastUpdate.Text = "Last Updated:";
            // 
            // CurrentClip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.txtPlaylist);
            this.Controls.Add(this.txtSchedule);
            this.Controls.Add(this.txtMessage);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblScheduler);
            this.Controls.Add(this.lblMessage);
            this.Name = "CurrentClip";
            this.Size = new System.Drawing.Size(199, 289);
            ((System.ComponentModel.ISupportInitialize)(this.picCurrent.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtMessage.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtSchedule.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPlaylist.Properties)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private DevExpress.XtraEditors.PictureEdit picCurrent;
        private System.Windows.Forms.Label lblMessage;
        private System.Windows.Forms.Label lblScheduler;
        private System.Windows.Forms.Label label2;
        private DevExpress.XtraEditors.TextEdit txtMessage;
        private DevExpress.XtraEditors.TextEdit txtSchedule;
        private DevExpress.XtraEditors.TextEdit txtPlaylist;
        private System.Windows.Forms.Panel panel1;
        private DevExpress.XtraEditors.LabelControl lblNA;
        private DevExpress.XtraEditors.SimpleButton btnRefresh;
        private DevExpress.XtraEditors.LabelControl lblLastUpdate;
	}
}
