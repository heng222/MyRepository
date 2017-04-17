namespace ProWrite.UI.Controls.Playlist
{
    partial class TimeSliceGroupEditForm
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
            this.rgIsRandom = new DevExpress.XtraEditors.RadioGroup();
            this.lcIsRandom = new DevExpress.XtraEditors.LabelControl();
            this.lcLength = new DevExpress.XtraEditors.LabelControl();
            this.lcName = new DevExpress.XtraEditors.LabelControl();
            this.teName = new DevExpress.XtraEditors.TextEdit();
            this.sbtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnSave = new DevExpress.XtraEditors.SimpleButton();
            this.teLength = new DevExpress.XtraEditors.SpinEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.rgIsRandom.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teLength.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // rgIsRandom
            // 
            this.rgIsRandom.EditValue = false;
            this.rgIsRandom.Location = new System.Drawing.Point(69, 83);
            this.rgIsRandom.Name = "rgIsRandom";
            this.rgIsRandom.Properties.Appearance.ForeColor = System.Drawing.Color.Black;
            this.rgIsRandom.Properties.Appearance.Options.UseForeColor = true;
            this.rgIsRandom.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(false, "Order"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(true, "Random")});
            this.rgIsRandom.Size = new System.Drawing.Size(127, 26);
            this.rgIsRandom.TabIndex = 2;
            // 
            // lcIsRandom
            // 
            this.lcIsRandom.Location = new System.Drawing.Point(12, 86);
            this.lcIsRandom.Name = "lcIsRandom";
            this.lcIsRandom.Size = new System.Drawing.Size(38, 13);
            this.lcIsRandom.TabIndex = 16;
            this.lcIsRandom.Text = "Playing:";
            // 
            // lcLength
            // 
            this.lcLength.Location = new System.Drawing.Point(12, 54);
            this.lcLength.Name = "lcLength";
            this.lcLength.Size = new System.Drawing.Size(37, 13);
            this.lcLength.TabIndex = 15;
            this.lcLength.Text = "Length:";
            // 
            // lcName
            // 
            this.lcName.Location = new System.Drawing.Point(12, 23);
            this.lcName.Name = "lcName";
            this.lcName.Size = new System.Drawing.Size(31, 13);
            this.lcName.TabIndex = 14;
            this.lcName.Text = "Name:";
            // 
            // teName
            // 
            this.teName.Location = new System.Drawing.Point(69, 20);
            this.teName.Name = "teName";
            this.teName.Properties.MaxLength = 60;
            this.teName.Size = new System.Drawing.Size(157, 20);
            this.teName.TabIndex = 0;
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.CausesValidation = false;
            this.sbtnCancel.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.sbtnCancel.Location = new System.Drawing.Point(154, 120);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(72, 24);
            this.sbtnCancel.TabIndex = 4;
            this.sbtnCancel.ToolTip = "Cancel";
            this.sbtnCancel.Click += new System.EventHandler(this.sbtnCancel_Click);
            // 
            // sbtnSave
            // 
            this.sbtnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.sbtnSave.Location = new System.Drawing.Point(81, 120);
            this.sbtnSave.Name = "sbtnSave";
            this.sbtnSave.Size = new System.Drawing.Size(67, 24);
            this.sbtnSave.TabIndex = 3;
            this.sbtnSave.ToolTip = "Save";
            this.sbtnSave.Click += new System.EventHandler(this.sbtnSave_Click);
            // 
            // teLength
            // 
            this.teLength.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.teLength.Location = new System.Drawing.Point(69, 51);
            this.teLength.Name = "teLength";
            this.teLength.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.teLength.Size = new System.Drawing.Size(57, 20);
            this.teLength.TabIndex = 1;
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(132, 54);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(5, 13);
            this.labelControl1.TabIndex = 20;
            this.labelControl1.Text = "s";
            // 
            // TimeSliceGroupEditForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(241, 154);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.teLength);
            this.Controls.Add(this.rgIsRandom);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.lcIsRandom);
            this.Controls.Add(this.sbtnSave);
            this.Controls.Add(this.lcLength);
            this.Controls.Add(this.teName);
            this.Controls.Add(this.lcName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TimeSliceGroupEditForm";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Edit Time Slice Group";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.TimeSliceGroupEditForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.rgIsRandom.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teLength.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

		private DevExpress.XtraEditors.LabelControl lcName;
        //private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.TextEdit teName;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.SimpleButton sbtnSave;
        private DevExpress.XtraEditors.LabelControl lcIsRandom;
        private DevExpress.XtraEditors.LabelControl lcLength;
        private DevExpress.XtraEditors.RadioGroup rgIsRandom;
        private DevExpress.XtraEditors.SpinEdit teLength;
        private DevExpress.XtraEditors.LabelControl labelControl1;

    }
}