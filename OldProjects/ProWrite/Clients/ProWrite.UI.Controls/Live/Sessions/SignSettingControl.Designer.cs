namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class SignSettingControl
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
            this.chkSignEnable = new DevExpress.XtraEditors.CheckEdit();
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.txtMedia = new DevExpress.XtraEditors.TextEdit();
            this.btnLoadMedia = new DevExpress.XtraEditors.SimpleButton();
            this.chkButtonGraphic = new DevExpress.XtraEditors.CheckEdit();
            this.lblSignName = new DevExpress.XtraEditors.LabelControl();
            this.panelControl2 = new DevExpress.XtraEditors.PanelControl();
            this.rdoMediaControl = new DevExpress.XtraEditors.RadioGroup();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.panelControl3 = new DevExpress.XtraEditors.PanelControl();
            this.chkQueueControl = new DevExpress.XtraEditors.CheckedListBoxControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.panelControl4 = new DevExpress.XtraEditors.PanelControl();
            this.label1 = new System.Windows.Forms.Label();
            this.btnClear = new DevExpress.XtraEditors.SimpleButton();
            this.picMedia = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.chkSignEnable.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtMedia.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkButtonGraphic.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).BeginInit();
            this.panelControl2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rdoMediaControl.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).BeginInit();
            this.panelControl3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chkQueueControl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl4)).BeginInit();
            this.panelControl4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picMedia)).BeginInit();
            this.SuspendLayout();
            // 
            // chkSignEnable
            // 
            this.chkSignEnable.Location = new System.Drawing.Point(12, 66);
            this.chkSignEnable.Name = "chkSignEnable";
            this.chkSignEnable.Properties.Caption = "";
            this.chkSignEnable.Size = new System.Drawing.Size(20, 19);
            this.chkSignEnable.TabIndex = 0;
            this.chkSignEnable.CheckedChanged += new System.EventHandler(this.chkSignEnable_CheckedChanged);
            // 
            // panelControl1
            // 
            this.panelControl1.Controls.Add(this.picMedia);
            this.panelControl1.Controls.Add(this.btnClear);
            this.panelControl1.Controls.Add(this.txtMedia);
            this.panelControl1.Controls.Add(this.btnLoadMedia);
            this.panelControl1.Controls.Add(this.chkButtonGraphic);
            this.panelControl1.Controls.Add(this.lblSignName);
            this.panelControl1.Location = new System.Drawing.Point(43, -1);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(324, 161);
            this.panelControl1.TabIndex = 1;
            // 
            // txtMedia
            // 
            this.txtMedia.Location = new System.Drawing.Point(142, 34);
            this.txtMedia.Name = "txtMedia";
            this.txtMedia.Size = new System.Drawing.Size(88, 20);
            this.txtMedia.TabIndex = 5;
            // 
            // btnLoadMedia
            // 
            this.btnLoadMedia.Location = new System.Drawing.Point(236, 34);
            this.btnLoadMedia.Name = "btnLoadMedia";
            this.btnLoadMedia.Size = new System.Drawing.Size(36, 20);
            this.btnLoadMedia.TabIndex = 4;
            this.btnLoadMedia.Text = "...";
            this.btnLoadMedia.Click += new System.EventHandler(this.btnLoadMedia_Click);
            // 
            // chkButtonGraphic
            // 
            this.chkButtonGraphic.Location = new System.Drawing.Point(140, 60);
            this.chkButtonGraphic.Name = "chkButtonGraphic";
            this.chkButtonGraphic.Properties.Caption = "Use thumbnail as button graphic";
            this.chkButtonGraphic.Size = new System.Drawing.Size(177, 19);
            this.chkButtonGraphic.TabIndex = 3;
            this.chkButtonGraphic.CheckedChanged += new System.EventHandler(chkButtonGraphic_CheckedChanged);
            // 
            // lblSignName
            // 
            this.lblSignName.Location = new System.Drawing.Point(9, 11);
            this.lblSignName.Name = "lblSignName";
            this.lblSignName.Size = new System.Drawing.Size(47, 13);
            this.lblSignName.TabIndex = 0;
            this.lblSignName.Text = "SignName";
            // 
            // panelControl2
            // 
            this.panelControl2.Controls.Add(this.rdoMediaControl);
            this.panelControl2.Controls.Add(this.labelControl1);
            this.panelControl2.Location = new System.Drawing.Point(363, -1);
            this.panelControl2.Name = "panelControl2";
            this.panelControl2.Size = new System.Drawing.Size(139, 161);
            this.panelControl2.TabIndex = 2;
            // 
            // rdoMediaControl
            // 
            this.rdoMediaControl.Location = new System.Drawing.Point(5, 34);
            this.rdoMediaControl.Name = "rdoMediaControl";
            this.rdoMediaControl.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.rdoMediaControl.Properties.Appearance.Options.UseBackColor = true;
            this.rdoMediaControl.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.rdoMediaControl.Size = new System.Drawing.Size(128, 123);
            this.rdoMediaControl.TabIndex = 2;
            this.rdoMediaControl.SelectedIndexChanged += new System.EventHandler(this.rdoMediaControl_SelectedIndexChanged);
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(11, 11);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(66, 13);
            this.labelControl1.TabIndex = 1;
            this.labelControl1.Text = "Media Control";
            // 
            // panelControl3
            // 
            this.panelControl3.Controls.Add(this.chkQueueControl);
            this.panelControl3.Controls.Add(this.labelControl2);
            this.panelControl3.Location = new System.Drawing.Point(499, -1);
            this.panelControl3.Name = "panelControl3";
            this.panelControl3.Size = new System.Drawing.Size(131, 162);
            this.panelControl3.TabIndex = 3;
            // 
            // chkQueueControl
            // 
            this.chkQueueControl.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.chkQueueControl.Location = new System.Drawing.Point(9, 32);
            this.chkQueueControl.Name = "chkQueueControl";
            this.chkQueueControl.Size = new System.Drawing.Size(113, 125);
            this.chkQueueControl.TabIndex = 3;
            this.chkQueueControl.SelectedIndexChanged += new System.EventHandler(this.chkQueueControl_SelectedIndexChanged);
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(13, 11);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(70, 13);
            this.labelControl2.TabIndex = 2;
            this.labelControl2.Text = "Queue Control";
            // 
            // panelControl4
            // 
            this.panelControl4.Controls.Add(this.label1);
            this.panelControl4.Controls.Add(this.chkSignEnable);
            this.panelControl4.Location = new System.Drawing.Point(-1, -1);
            this.panelControl4.Name = "panelControl4";
            this.panelControl4.Size = new System.Drawing.Size(45, 161);
            this.panelControl4.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(2, 88);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Enable";
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(277, 34);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(36, 20);
            this.btnClear.TabIndex = 6;
            this.btnClear.Text = "Clear";
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // picMedia
            // 
            this.picMedia.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picMedia.Location = new System.Drawing.Point(9, 37);
            this.picMedia.Name = "picMedia";
            this.picMedia.Size = new System.Drawing.Size(116, 101);
            this.picMedia.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picMedia.TabIndex = 7;
            this.picMedia.TabStop = false;
            // 
            // SignSettingControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.panelControl4);
            this.Controls.Add(this.panelControl3);
            this.Controls.Add(this.panelControl2);
            this.Controls.Add(this.panelControl1);
            this.Name = "SignSettingControl";
            this.Size = new System.Drawing.Size(629, 160);
            ((System.ComponentModel.ISupportInitialize)(this.chkSignEnable.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            this.panelControl1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtMedia.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkButtonGraphic.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).EndInit();
            this.panelControl2.ResumeLayout(false);
            this.panelControl2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rdoMediaControl.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).EndInit();
            this.panelControl3.ResumeLayout(false);
            this.panelControl3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chkQueueControl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl4)).EndInit();
            this.panelControl4.ResumeLayout(false);
            this.panelControl4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picMedia)).EndInit();
            this.ResumeLayout(false);

        }


        #endregion

        private DevExpress.XtraEditors.CheckEdit chkSignEnable;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.LabelControl lblSignName;
        private DevExpress.XtraEditors.CheckEdit chkButtonGraphic;
        private DevExpress.XtraEditors.PanelControl panelControl2;
        private DevExpress.XtraEditors.RadioGroup rdoMediaControl;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.PanelControl panelControl3;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.CheckedListBoxControl chkQueueControl;
        private DevExpress.XtraEditors.PanelControl panelControl4;
        private DevExpress.XtraEditors.SimpleButton btnLoadMedia;
        private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.TextEdit txtMedia;
        private DevExpress.XtraEditors.SimpleButton btnClear;
        private System.Windows.Forms.PictureBox picMedia;
    }
}
