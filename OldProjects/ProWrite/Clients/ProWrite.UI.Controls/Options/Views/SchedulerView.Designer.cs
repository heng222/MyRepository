namespace ProWrite.UI.Controls.Options.Views
{
    partial class SchedulerView
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
            this.lblPlaylist = new DevExpress.XtraEditors.LabelControl();
            this.lblTimeSliceGroup = new DevExpress.XtraEditors.LabelControl();
            this.spinPlaylist = new DevExpress.XtraEditors.SpinEdit();
            this.spinTimeSliceGroup = new DevExpress.XtraEditors.SpinEdit();
            ((System.ComponentModel.ISupportInitialize)(this.spinPlaylist.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinTimeSliceGroup.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lblPlaylist
            // 
            this.lblPlaylist.Location = new System.Drawing.Point(15, 5);
            this.lblPlaylist.Name = "lblPlaylist";
            this.lblPlaylist.Size = new System.Drawing.Size(116, 13);
            this.lblPlaylist.TabIndex = 0;
            this.lblPlaylist.Text = "PlayList Display Time(h):";
            // 
            // lblTimeSliceGroup
            // 
            this.lblTimeSliceGroup.Location = new System.Drawing.Point(15, 50);
            this.lblTimeSliceGroup.Name = "lblTimeSliceGroup";
            this.lblTimeSliceGroup.Size = new System.Drawing.Size(158, 13);
            this.lblTimeSliceGroup.TabIndex = 1;
            this.lblTimeSliceGroup.Text = "Time Slice Group Display Time(h):";
            // 
            // spinPlaylist
            // 
            this.spinPlaylist.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinPlaylist.Location = new System.Drawing.Point(15, 24);
            this.spinPlaylist.Name = "spinPlaylist";
            this.spinPlaylist.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinPlaylist.Size = new System.Drawing.Size(116, 20);
            this.spinPlaylist.TabIndex = 2;
            // 
            // spinTimeSliceGroup
            // 
            this.spinTimeSliceGroup.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinTimeSliceGroup.Location = new System.Drawing.Point(15, 69);
            this.spinTimeSliceGroup.Name = "spinTimeSliceGroup";
            this.spinTimeSliceGroup.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinTimeSliceGroup.Size = new System.Drawing.Size(116, 20);
            this.spinTimeSliceGroup.TabIndex = 3;
            // 
            // SchedulerView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.spinTimeSliceGroup);
            this.Controls.Add(this.spinPlaylist);
            this.Controls.Add(this.lblTimeSliceGroup);
            this.Controls.Add(this.lblPlaylist);
            this.Name = "SchedulerView";
            this.Size = new System.Drawing.Size(199, 106);
            ((System.ComponentModel.ISupportInitialize)(this.spinPlaylist.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinTimeSliceGroup.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.LabelControl lblPlaylist;
        private DevExpress.XtraEditors.LabelControl lblTimeSliceGroup;
        private DevExpress.XtraEditors.SpinEdit spinPlaylist;
        private DevExpress.XtraEditors.SpinEdit spinTimeSliceGroup;
    }
}
