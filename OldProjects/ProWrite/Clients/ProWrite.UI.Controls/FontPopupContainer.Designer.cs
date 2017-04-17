namespace ProWrite.UI.Controls
{
    partial class FontPopupContainer
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
            this.ckEditBitmapFontOnly = new DevExpress.XtraEditors.CheckEdit();
            this.imgLstfonts = new DevExpress.XtraEditors.ImageListBoxControl();
            ((System.ComponentModel.ISupportInitialize)(this.ckEditBitmapFontOnly.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgLstfonts)).BeginInit();
            this.SuspendLayout();
            // 
            // ckEditBitmapFontOnly
            // 
            this.ckEditBitmapFontOnly.Location = new System.Drawing.Point(5, 4);
            this.ckEditBitmapFontOnly.Name = "ckEditBitmapFontOnly";
            this.ckEditBitmapFontOnly.Properties.Caption = "Show Bitmap Fonts Only";
            this.ckEditBitmapFontOnly.Size = new System.Drawing.Size(228, 19);
            this.ckEditBitmapFontOnly.TabIndex = 0;
            this.ckEditBitmapFontOnly.Anchor = System.Windows.Forms.AnchorStyles.Top |
                                               System.Windows.Forms.AnchorStyles.Left;
            this.ckEditBitmapFontOnly.CheckedChanged += new System.EventHandler(ckEditBitmapFontOnly_CheckedChanged);
            // 
            // imgLstfonts
            // 
            this.imgLstfonts.Location = new System.Drawing.Point(4, 29);
            this.imgLstfonts.Name = "imgLstfonts";
            this.imgLstfonts.Size = new System.Drawing.Size(233, 175);
            this.imgLstfonts.TabIndex = 2;
            this.imgLstfonts.Anchor = System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Top |
                                      System.Windows.Forms.AnchorStyles.Right | System.Windows.Forms.AnchorStyles.Bottom;
            this.imgLstfonts.KeyDown += new System.Windows.Forms.KeyEventHandler(imgLstfonts_KeyDown);
            this.imgLstfonts.DoubleClick += new System.EventHandler(imgLstfonts_DoubleClick);
            // 
            // FontPopupContainer
            // 
            this.Controls.Add(this.imgLstfonts);
            this.Controls.Add(this.ckEditBitmapFontOnly);
            this.Name = "FontPopupContainer";
            this.Size = new System.Drawing.Size(241, 207);
            ((System.ComponentModel.ISupportInitialize)(this.ckEditBitmapFontOnly.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgLstfonts)).EndInit();
            this.ResumeLayout(false);

        }



        #endregion

        private DevExpress.XtraEditors.CheckEdit ckEditBitmapFontOnly;
        private DevExpress.XtraEditors.ImageListBoxControl imgLstfonts;
    }
}
