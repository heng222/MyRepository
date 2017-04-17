namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class FontSelectForm
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
            this.lstFontName = new DevExpress.XtraEditors.ListBoxControl();
            this.lblFontName = new DevExpress.XtraEditors.LabelControl();
            this.lblFontStyle = new DevExpress.XtraEditors.LabelControl();
            this.lstFontStyle = new DevExpress.XtraEditors.ListBoxControl();
            this.lblFontSize = new DevExpress.XtraEditors.LabelControl();
            this.txteFontSize = new DevExpress.XtraEditors.TextEdit();
            this.sbtnOK = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.chkFontType = new DevExpress.XtraEditors.CheckEdit();
            this.spinEdit1 = new DevExpress.XtraEditors.SpinEdit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontStyle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txteFontSize.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkFontType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lstFontName
            // 
            this.lstFontName.Location = new System.Drawing.Point(8, 56);
            this.lstFontName.Name = "lstFontName";
            this.lstFontName.Size = new System.Drawing.Size(120, 95);
            this.lstFontName.TabIndex = 0;
            // 
            // lblFontName
            // 
            this.lblFontName.Location = new System.Drawing.Point(8, 36);
            this.lblFontName.Name = "lblFontName";
            this.lblFontName.Size = new System.Drawing.Size(26, 13);
            this.lblFontName.TabIndex = 1;
            this.lblFontName.Text = "Font:";
            // 
            // lblFontStyle
            // 
            this.lblFontStyle.Location = new System.Drawing.Point(144, 36);
            this.lblFontStyle.Name = "lblFontStyle";
            this.lblFontStyle.Size = new System.Drawing.Size(52, 13);
            this.lblFontStyle.TabIndex = 3;
            this.lblFontStyle.Text = "Font style:";
            // 
            // lstFontStyle
            // 
            this.lstFontStyle.Location = new System.Drawing.Point(144, 56);
            this.lstFontStyle.Name = "lstFontStyle";
            this.lstFontStyle.Size = new System.Drawing.Size(120, 95);
            this.lstFontStyle.TabIndex = 2;
            // 
            // lblFontSize
            // 
            this.lblFontSize.Location = new System.Drawing.Point(279, 36);
            this.lblFontSize.Name = "lblFontSize";
            this.lblFontSize.Size = new System.Drawing.Size(23, 13);
            this.lblFontSize.TabIndex = 4;
            this.lblFontSize.Text = "Size:";
            // 
            // txteFontSize
            // 
            this.txteFontSize.Location = new System.Drawing.Point(279, 56);
            this.txteFontSize.Name = "txteFontSize";
            this.txteFontSize.Size = new System.Drawing.Size(48, 20);
            this.txteFontSize.TabIndex = 5;
            // 
            // sbtnOK
            // 
            this.sbtnOK.Location = new System.Drawing.Point(48, 167);
            this.sbtnOK.Name = "sbtnOK";
            this.sbtnOK.Size = new System.Drawing.Size(75, 23);
            this.sbtnOK.TabIndex = 6;
            this.sbtnOK.Text = "OK";
            this.sbtnOK.Click += new System.EventHandler(this.sbtnOK_Click);
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.Location = new System.Drawing.Point(154, 167);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(75, 23);
            this.sbtnCancel.TabIndex = 7;
            this.sbtnCancel.Text = "Cancel";
            this.sbtnCancel.Click += new System.EventHandler(this.sbtnCancel_Click);
            // 
            // chkFontType
            // 
            this.chkFontType.Location = new System.Drawing.Point(8, 13);
            this.chkFontType.Name = "chkFontType";
            this.chkFontType.Properties.Caption = "ProWrite defined fonts only";
            this.chkFontType.Size = new System.Drawing.Size(166, 19);
            this.chkFontType.TabIndex = 8;
            this.chkFontType.CheckedChanged += new System.EventHandler(this.chkFontType_CheckedChanged);
            // 
            // spinEdit1
            // 
            this.spinEdit1.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spinEdit1.Location = new System.Drawing.Point(236, 157);
            this.spinEdit1.Name = "spinEdit1";
            this.spinEdit1.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinEdit1.Properties.Mask.EditMask = "f0";
            this.spinEdit1.Properties.Mask.ShowPlaceHolders = false;
            this.spinEdit1.Properties.MaxValue = new decimal(new int[] {
            72,
            0,
            0,
            0});
            this.spinEdit1.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spinEdit1.Properties.NullText = "1";
            this.spinEdit1.Size = new System.Drawing.Size(100, 20);
            this.spinEdit1.TabIndex = 9;
            // 
            // FontSelectForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(348, 196);
            this.Controls.Add(this.spinEdit1);
            this.Controls.Add(this.chkFontType);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.sbtnOK);
            this.Controls.Add(this.txteFontSize);
            this.Controls.Add(this.lblFontSize);
            this.Controls.Add(this.lblFontStyle);
            this.Controls.Add(this.lstFontStyle);
            this.Controls.Add(this.lblFontName);
            this.Controls.Add(this.lstFontName);
            this.Name = "FontSelectForm";
            this.Text = "FontSelectForm";
            ((System.ComponentModel.ISupportInitialize)(this.lstFontName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontStyle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txteFontSize.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkFontType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spinEdit1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ListBoxControl lstFontName;
        private DevExpress.XtraEditors.LabelControl lblFontName;
        private DevExpress.XtraEditors.LabelControl lblFontStyle;
        private DevExpress.XtraEditors.ListBoxControl lstFontStyle;
        private DevExpress.XtraEditors.LabelControl lblFontSize;
        private DevExpress.XtraEditors.TextEdit txteFontSize;
        private DevExpress.XtraEditors.SimpleButton sbtnOK;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.CheckEdit chkFontType;
        private DevExpress.XtraEditors.SpinEdit spinEdit1;
    }
}