namespace ProWrite.UI.Controls.Library
{
    partial class LibraryMessageItem
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
            this.lcSource = new DevExpress.XtraEditors.LabelControl();
            this.lcDest = new DevExpress.XtraEditors.LabelControl();
            this.teSource = new DevExpress.XtraEditors.TextEdit();
            this.teDest = new DevExpress.XtraEditors.TextEdit();
            this.sbtnCheck = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.teSource.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teDest.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lcSource
            // 
            this.lcSource.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lcSource.Location = new System.Drawing.Point(4, 4);
            this.lcSource.Name = "lcSource";
            this.lcSource.Size = new System.Drawing.Size(111, 13);
            this.lcSource.TabIndex = 0;
            this.lcSource.Text = "Source message name:";
            // 
            // lcDest
            // 
            this.lcDest.Location = new System.Drawing.Point(320, 3);
            this.lcDest.Name = "lcDest";
            this.lcDest.Size = new System.Drawing.Size(110, 13);
            this.lcDest.TabIndex = 1;
            this.lcDest.Text = "Target message name:";
            // 
            // teSource
            // 
            this.teSource.Location = new System.Drawing.Point(117, 3);
            this.teSource.Name = "teSource";
            this.teSource.Properties.ReadOnly = true;
            this.teSource.Size = new System.Drawing.Size(189, 20);
            this.teSource.TabIndex = 2;
            // 
            // teDest
            // 
            this.teDest.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.teDest.Location = new System.Drawing.Point(436, 3);
            this.teDest.Name = "teDest";
            this.teDest.Size = new System.Drawing.Size(186, 20);
            this.teDest.TabIndex = 3;
            this.teDest.TextChanged += new System.EventHandler(this.teDest_TextChanged);
            // 
            // sbtnCheck
            // 
            this.sbtnCheck.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnCheck.Location = new System.Drawing.Point(648, 2);
            this.sbtnCheck.Name = "sbtnCheck";
            this.sbtnCheck.Size = new System.Drawing.Size(75, 23);
            this.sbtnCheck.TabIndex = 4;
            this.sbtnCheck.Text = "Check";
            this.sbtnCheck.Click += new System.EventHandler(this.sbtnCheck_Click);
            // 
            // LibraryMessageItem
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lcSource);
            this.Controls.Add(this.sbtnCheck);
            this.Controls.Add(this.teDest);
            this.Controls.Add(this.teSource);
            this.Controls.Add(this.lcDest);
            this.Name = "LibraryMessageItem";
            this.Size = new System.Drawing.Size(730, 29);
            ((System.ComponentModel.ISupportInitialize)(this.teSource.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teDest.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton sbtnCheck;
        private DevExpress.XtraEditors.TextEdit teDest;
        private DevExpress.XtraEditors.LabelControl lcDest;
        private DevExpress.XtraEditors.TextEdit teSource;
        private DevExpress.XtraEditors.LabelControl lcSource;
    }
}
