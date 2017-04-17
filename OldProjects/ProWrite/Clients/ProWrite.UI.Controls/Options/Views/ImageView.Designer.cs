namespace ProWrite.UI.Controls.Options.Views
{
    partial class ImageView
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
            this.lblFitToSign = new DevExpress.XtraEditors.LabelControl();
            this.lblSizeMode = new DevExpress.XtraEditors.LabelControl();
            this.lblWidth = new DevExpress.XtraEditors.LabelControl();
            this.txtWidth = new DevExpress.XtraEditors.TextEdit();
            this.txtHeight = new DevExpress.XtraEditors.TextEdit();
            this.lblHeight = new DevExpress.XtraEditors.LabelControl();
            this.ddlFitToSign = new DevExpress.XtraEditors.ComboBoxEdit();
            this.ddlSizeMode = new DevExpress.XtraEditors.ComboBoxEdit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lblFitToSign
            // 
            this.lblFitToSign.Location = new System.Drawing.Point(12, 97);
            this.lblFitToSign.Name = "lblFitToSign";
            this.lblFitToSign.Size = new System.Drawing.Size(54, 13);
            this.lblFitToSign.TabIndex = 1;
            this.lblFitToSign.Text = "Fit To Sign:";
            // 
            // lblSizeMode
            // 
            this.lblSizeMode.Location = new System.Drawing.Point(12, 142);
            this.lblSizeMode.Name = "lblSizeMode";
            this.lblSizeMode.Size = new System.Drawing.Size(52, 13);
            this.lblSizeMode.TabIndex = 2;
            this.lblSizeMode.Text = "Size Mode:";
            // 
            // lblWidth
            // 
            this.lblWidth.Location = new System.Drawing.Point(12, 52);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(32, 13);
            this.lblWidth.TabIndex = 7;
            this.lblWidth.Text = "Width:";
            // 
            // txtWidth
            // 
            this.txtWidth.Location = new System.Drawing.Point(12, 71);
            this.txtWidth.Name = "txtWidth";
            this.txtWidth.Size = new System.Drawing.Size(100, 20);
            this.txtWidth.TabIndex = 6;
            // 
            // txtHeight
            // 
            this.txtHeight.Location = new System.Drawing.Point(12, 25);
            this.txtHeight.Name = "txtHeight";
            this.txtHeight.Size = new System.Drawing.Size(100, 20);
            this.txtHeight.TabIndex = 5;
            // 
            // lblHeight
            // 
            this.lblHeight.Location = new System.Drawing.Point(12, 5);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(35, 13);
            this.lblHeight.TabIndex = 4;
            this.lblHeight.Text = "Height:";
            // 
            // ddlFitToSign
            // 
            this.ddlFitToSign.EditValue = "False";
            this.ddlFitToSign.Location = new System.Drawing.Point(12, 116);
            this.ddlFitToSign.Name = "ddlFitToSign";
            this.ddlFitToSign.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlFitToSign.Properties.Items.AddRange(new object[] {
            "True",
            "False"});
            this.ddlFitToSign.Size = new System.Drawing.Size(100, 20);
            this.ddlFitToSign.TabIndex = 8;
            // 
            // ddlSizeMode
            // 
            this.ddlSizeMode.Location = new System.Drawing.Point(12, 161);
            this.ddlSizeMode.Name = "ddlSizeMode";
            this.ddlSizeMode.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSizeMode.Size = new System.Drawing.Size(100, 20);
            this.ddlSizeMode.TabIndex = 9;
            // 
            // ImageView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ddlSizeMode);
            this.Controls.Add(this.ddlFitToSign);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.txtWidth);
            this.Controls.Add(this.txtHeight);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.lblSizeMode);
            this.Controls.Add(this.lblFitToSign);
            this.Name = "ImageView";
            this.Size = new System.Drawing.Size(136, 199);
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.LabelControl lblFitToSign;
        private DevExpress.XtraEditors.LabelControl lblSizeMode;
        private DevExpress.XtraEditors.LabelControl lblWidth;
        private DevExpress.XtraEditors.TextEdit txtWidth;
        private DevExpress.XtraEditors.TextEdit txtHeight;
        private DevExpress.XtraEditors.LabelControl lblHeight;
        private DevExpress.XtraEditors.ComboBoxEdit ddlFitToSign;
        private DevExpress.XtraEditors.ComboBoxEdit ddlSizeMode;
    }
}
