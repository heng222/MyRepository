namespace ProWrite.UI.Controls.Editor
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
            this.chkFontType = new DevExpress.XtraEditors.CheckEdit();
            this.sbtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnOK = new DevExpress.XtraEditors.SimpleButton();
            this.lblFontSize = new DevExpress.XtraEditors.LabelControl();
            this.lblFontStyle = new DevExpress.XtraEditors.LabelControl();
            this.lstFontStyle = new DevExpress.XtraEditors.ListBoxControl();
            this.lblFontName = new DevExpress.XtraEditors.LabelControl();
            this.lstFontName = new DevExpress.XtraEditors.ListBoxControl();
            this.seFontSize = new DevExpress.XtraEditors.SpinEdit();
            this.popupContainerControl1 = new DevExpress.XtraEditors.PopupContainerControl();
            this.iblFont = new DevExpress.XtraEditors.ImageListBoxControl();
            this.ckeditBitmapFontOnly = new DevExpress.XtraEditors.CheckEdit();
            this.popupContainerEdit1 = new DevExpress.XtraEditors.PopupContainerEdit();
            ((System.ComponentModel.ISupportInitialize)(this.chkFontType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontStyle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.seFontSize.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerControl1)).BeginInit();
            this.popupContainerControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.iblFont)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ckeditBitmapFontOnly.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerEdit1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // chkFontType
            // 
            this.chkFontType.Location = new System.Drawing.Point(10, 12);
            this.chkFontType.Name = "chkFontType";
            this.chkFontType.Properties.Caption = "";
            this.chkFontType.Size = new System.Drawing.Size(166, 19);
            this.chkFontType.TabIndex = 17;
            this.chkFontType.CheckedChanged += new System.EventHandler(this.chkFontType_CheckedChanged);
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.sbtnCancel.Location = new System.Drawing.Point(246, 166);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(75, 23);
            this.sbtnCancel.TabIndex = 16;
            this.sbtnCancel.Click += new System.EventHandler(this.sbtnCancel_Click);
            // 
            // sbtnOK
            // 
            this.sbtnOK.Location = new System.Drawing.Point(140, 166);
            this.sbtnOK.Name = "sbtnOK";
            this.sbtnOK.Size = new System.Drawing.Size(75, 23);
            this.sbtnOK.TabIndex = 15;
            this.sbtnOK.Click += new System.EventHandler(this.sbtnOK_Click);
            // 
            // lblFontSize
            // 
            this.lblFontSize.Location = new System.Drawing.Point(267, 35);
            this.lblFontSize.Name = "lblFontSize";
            this.lblFontSize.Size = new System.Drawing.Size(0, 13);
            this.lblFontSize.TabIndex = 13;
            // 
            // lblFontStyle
            // 
            this.lblFontStyle.Location = new System.Drawing.Point(141, 35);
            this.lblFontStyle.Name = "lblFontStyle";
            this.lblFontStyle.Size = new System.Drawing.Size(0, 13);
            this.lblFontStyle.TabIndex = 12;
            // 
            // lstFontStyle
            // 
            this.lstFontStyle.Location = new System.Drawing.Point(138, 55);
            this.lstFontStyle.Name = "lstFontStyle";
            this.lstFontStyle.Size = new System.Drawing.Size(120, 95);
            this.lstFontStyle.TabIndex = 11;
            // 
            // lblFontName
            // 
            this.lblFontName.Location = new System.Drawing.Point(12, 35);
            this.lblFontName.Name = "lblFontName";
            this.lblFontName.Size = new System.Drawing.Size(0, 13);
            this.lblFontName.TabIndex = 10;
            // 
            // lstFontName
            // 
            this.lstFontName.Location = new System.Drawing.Point(12, 55);
            this.lstFontName.Name = "lstFontName";
            this.lstFontName.Size = new System.Drawing.Size(120, 95);
            this.lstFontName.TabIndex = 9;
            // 
            // seFontSize
            // 
            this.seFontSize.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.seFontSize.Location = new System.Drawing.Point(264, 54);
            this.seFontSize.Name = "seFontSize";
            this.seFontSize.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.seFontSize.Size = new System.Drawing.Size(57, 20);
            this.seFontSize.TabIndex = 18;
            // 
            // popupContainerControl1
            // 
            this.popupContainerControl1.Controls.Add(this.ckeditBitmapFontOnly);
            this.popupContainerControl1.Controls.Add(this.iblFont);
            this.popupContainerControl1.Location = new System.Drawing.Point(59, 248);
            this.popupContainerControl1.Name = "popupContainerControl1";
            this.popupContainerControl1.Size = new System.Drawing.Size(173, 209);
            this.popupContainerControl1.TabIndex = 19;
            // 
            // iblFont
            // 
            this.iblFont.Location = new System.Drawing.Point(4, 22);
            this.iblFont.Name = "iblFont";
            this.iblFont.Size = new System.Drawing.Size(166, 184);
            this.iblFont.TabIndex = 0;
            // 
            // ckeditBitmapFontOnly
            // 
            this.ckeditBitmapFontOnly.Location = new System.Drawing.Point(4, 3);
            this.ckeditBitmapFontOnly.Name = "ckeditBitmapFontOnly";
            this.ckeditBitmapFontOnly.Properties.Caption = "Show Bitmap Font Only";
            this.ckeditBitmapFontOnly.Size = new System.Drawing.Size(166, 19);
            this.ckeditBitmapFontOnly.TabIndex = 1;
            // 
            // popupContainerEdit1
            // 
            this.popupContainerEdit1.Location = new System.Drawing.Point(63, 212);
            this.popupContainerEdit1.Name = "popupContainerEdit1";
            this.popupContainerEdit1.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.popupContainerEdit1.Properties.PopupControl = this.popupContainerControl1;
            this.popupContainerEdit1.Size = new System.Drawing.Size(166, 20);
            this.popupContainerEdit1.TabIndex = 20;
            // 
            // FontSelectForm
            // 
            this.AcceptButton = this.sbtnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.sbtnCancel;
            this.ClientSize = new System.Drawing.Size(555, 469);
            this.Controls.Add(this.popupContainerEdit1);
            this.Controls.Add(this.popupContainerControl1);
            this.Controls.Add(this.seFontSize);
            this.Controls.Add(this.chkFontType);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.sbtnOK);
            this.Controls.Add(this.lblFontSize);
            this.Controls.Add(this.lblFontStyle);
            this.Controls.Add(this.lstFontStyle);
            this.Controls.Add(this.lblFontName);
            this.Controls.Add(this.lstFontName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FontSelectForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Font ";
            ((System.ComponentModel.ISupportInitialize)(this.chkFontType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontStyle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lstFontName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.seFontSize.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerControl1)).EndInit();
            this.popupContainerControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.iblFont)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ckeditBitmapFontOnly.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerEdit1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.CheckEdit chkFontType;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.SimpleButton sbtnOK;
        private DevExpress.XtraEditors.LabelControl lblFontSize;
        private DevExpress.XtraEditors.LabelControl lblFontStyle;
        private DevExpress.XtraEditors.ListBoxControl lstFontStyle;
        private DevExpress.XtraEditors.LabelControl lblFontName;
        private DevExpress.XtraEditors.ListBoxControl lstFontName;
        private DevExpress.XtraEditors.SpinEdit seFontSize;
        private DevExpress.XtraEditors.PopupContainerControl popupContainerControl1;
        private DevExpress.XtraEditors.ImageListBoxControl iblFont;
        private DevExpress.XtraEditors.CheckEdit ckeditBitmapFontOnly;
        private DevExpress.XtraEditors.PopupContainerEdit popupContainerEdit1;


    }
}