namespace ProWrite.UI.Controls.Options.Views
{
    partial class SignView
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
            this.lbnSignType = new System.Windows.Forms.Label();
            this.lblWidth = new System.Windows.Forms.Label();
            this.lblImage = new System.Windows.Forms.Label();
            this.ddlSignType = new DevExpress.XtraEditors.ComboBoxEdit();
            this.txtWidth = new DevExpress.XtraEditors.TextEdit();
            this.btSignImage = new DevExpress.XtraEditors.ButtonEdit();
            this.lblHeight = new System.Windows.Forms.Label();
            this.txtHeight = new DevExpress.XtraEditors.TextEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.btSignImage.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lbnSignType
            // 
            this.lbnSignType.AutoSize = true;
            this.lbnSignType.Location = new System.Drawing.Point(20, 52);
            this.lbnSignType.Name = "lbnSignType";
            this.lbnSignType.Size = new System.Drawing.Size(58, 13);
            this.lbnSignType.TabIndex = 9;
            this.lbnSignType.Text = "Sign Type:";
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(21, 91);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(38, 13);
            this.lblWidth.TabIndex = 10;
            this.lblWidth.Text = "Width:";
            // 
            // lblImage
            // 
            this.lblImage.AutoSize = true;
            this.lblImage.Location = new System.Drawing.Point(20, 13);
            this.lblImage.Name = "lblImage";
            this.lblImage.Size = new System.Drawing.Size(39, 13);
            this.lblImage.TabIndex = 7;
            this.lblImage.Text = "Image:";
            // 
            // ddlSignType
            // 
            this.ddlSignType.Location = new System.Drawing.Point(23, 68);
            this.ddlSignType.Name = "ddlSignType";
            this.ddlSignType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSignType.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlSignType.Size = new System.Drawing.Size(140, 20);
            this.ddlSignType.TabIndex = 12;
            // 
            // txtWidth
            // 
            this.txtWidth.Location = new System.Drawing.Point(23, 107);
            this.txtWidth.Name = "txtWidth";
            this.txtWidth.Properties.MaxLength = 4;
            this.txtWidth.Size = new System.Drawing.Size(140, 20);
            this.txtWidth.TabIndex = 13;
            // 
            // btSignImage
            // 
            this.btSignImage.EditValue = "";
            this.btSignImage.Location = new System.Drawing.Point(23, 29);
            this.btSignImage.Name = "btSignImage";
            this.btSignImage.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.btSignImage.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.btSignImage.Size = new System.Drawing.Size(140, 20);
            this.btSignImage.TabIndex = 11;
            this.btSignImage.Click += new System.EventHandler(this.btSignImage_Click);
            // 
            // lblHeight
            // 
            this.lblHeight.AutoSize = true;
            this.lblHeight.Location = new System.Drawing.Point(21, 130);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(41, 13);
            this.lblHeight.TabIndex = 8;
            this.lblHeight.Text = "Height:";
            // 
            // txtHeight
            // 
            this.txtHeight.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtHeight.Location = new System.Drawing.Point(23, 146);
            this.txtHeight.Name = "txtHeight";
            this.txtHeight.Properties.MaxLength = 4;
            this.txtHeight.Size = new System.Drawing.Size(140, 20);
            this.txtHeight.TabIndex = 14;
            // 
            // SignView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lbnSignType);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.lblImage);
            this.Controls.Add(this.ddlSignType);
            this.Controls.Add(this.txtWidth);
            this.Controls.Add(this.btSignImage);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.txtHeight);
            this.Name = "SignView";
            this.Size = new System.Drawing.Size(179, 191);
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.btSignImage.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbnSignType;
        private System.Windows.Forms.Label lblWidth;
        private System.Windows.Forms.Label lblImage;
        private DevExpress.XtraEditors.ComboBoxEdit ddlSignType;
        private DevExpress.XtraEditors.TextEdit txtWidth;
        private DevExpress.XtraEditors.ButtonEdit btSignImage;
        private System.Windows.Forms.Label lblHeight;
        private DevExpress.XtraEditors.TextEdit txtHeight;
    }
}
