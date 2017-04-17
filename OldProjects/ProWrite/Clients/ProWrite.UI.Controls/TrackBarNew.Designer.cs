namespace ProWrite.UI.Controls
{
    partial class TrackBarNew
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
            this.lblTimes = new System.Windows.Forms.Label();
            this.lblInnerSlide = new System.Windows.Forms.Label();
            this.playTrackBarCtrl = new DevExpress.XtraEditors.TrackBarControl();
            ((System.ComponentModel.ISupportInitialize)(this.playTrackBarCtrl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.playTrackBarCtrl.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lblTimes
            // 
            this.lblTimes.BackColor = System.Drawing.Color.Black;
            this.lblTimes.Location = new System.Drawing.Point(26, 5);
            this.lblTimes.Name = "lblTimes";
            this.lblTimes.Size = new System.Drawing.Size(1, 31);
            this.lblTimes.TabIndex = 21;
            this.lblTimes.Text = "label1";
            // 
            // lblInnerSlide
            // 
            this.lblInnerSlide.BackColor = System.Drawing.SystemColors.ControlText;
            this.lblInnerSlide.Location = new System.Drawing.Point(11, 29);
            this.lblInnerSlide.Name = "lblInnerSlide";
            this.lblInnerSlide.Size = new System.Drawing.Size(1, 40);
            this.lblInnerSlide.TabIndex = 22;
            // 
            // playTrackBarCtrl
            // 
            this.playTrackBarCtrl.EditValue = null;
            this.playTrackBarCtrl.Location = new System.Drawing.Point(2, 13);
            this.playTrackBarCtrl.Name = "playTrackBarCtrl";
            this.playTrackBarCtrl.Properties.AllowFocused = false;
            this.playTrackBarCtrl.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.playTrackBarCtrl.Properties.LargeChange = 14;
            this.playTrackBarCtrl.Properties.Maximum = 100;
            this.playTrackBarCtrl.Properties.SmallChange = 14;
            this.playTrackBarCtrl.Properties.TickFrequency = 5;
            this.playTrackBarCtrl.Properties.TickStyle = System.Windows.Forms.TickStyle.None;
            this.playTrackBarCtrl.Properties.ShowValueToolTip = true;
            this.playTrackBarCtrl.Size = new System.Drawing.Size(513, 42);
            this.playTrackBarCtrl.TabIndex = 20;
            this.playTrackBarCtrl.ValueChanged += new System.EventHandler(this.playTrackBarCtrl_ValueChanged);
            // 
            // TrackBarNew
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lblTimes);
            this.Controls.Add(this.lblInnerSlide);
            this.Controls.Add(this.playTrackBarCtrl);
            this.Name = "TrackBarNew";
            this.Size = new System.Drawing.Size(516, 59);
            this.Resize += new System.EventHandler(this.TrackBarNew_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.playTrackBarCtrl.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.playTrackBarCtrl)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lblTimes;
        public System.Windows.Forms.Label lblInnerSlide;
        private DevExpress.XtraEditors.TrackBarControl playTrackBarCtrl;
    }
}
