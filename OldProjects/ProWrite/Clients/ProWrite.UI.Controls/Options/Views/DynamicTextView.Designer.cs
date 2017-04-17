namespace ProWrite.UI.Controls.Options.Views
{
    partial class DynamicTextView
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
            this.ddlSizeMode = new DevExpress.XtraEditors.ComboBoxEdit();
            this.ddlFitToSign = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblWidth = new DevExpress.XtraEditors.LabelControl();
            this.textEdit2 = new DevExpress.XtraEditors.TextEdit();
            this.textEdit1 = new DevExpress.XtraEditors.TextEdit();
            this.lblHeight = new DevExpress.XtraEditors.LabelControl();
            this.lblSizeMode = new DevExpress.XtraEditors.LabelControl();
            this.lblFitToSign = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textEdit2.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textEdit1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlSizeMode
            // 
            this.ddlSizeMode.Location = new System.Drawing.Point(15, 76);
            this.ddlSizeMode.Name = "ddlSizeMode";
            this.ddlSizeMode.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSizeMode.Size = new System.Drawing.Size(100, 20);
            this.ddlSizeMode.TabIndex = 17;
            // 
            // ddlFitToSign
            // 
            this.ddlFitToSign.EditValue = "False";
            this.ddlFitToSign.Location = new System.Drawing.Point(15, 31);
            this.ddlFitToSign.Name = "ddlFitToSign";
            this.ddlFitToSign.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlFitToSign.Properties.Items.AddRange(new object[] {
            "True",
            "False"});
            this.ddlFitToSign.Size = new System.Drawing.Size(100, 20);
            this.ddlFitToSign.TabIndex = 16;
            // 
            // lblWidth
            // 
            this.lblWidth.Location = new System.Drawing.Point(15, 149);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(32, 13);
            this.lblWidth.TabIndex = 15;
            this.lblWidth.Text = "Width:";
            // 
            // textEdit2
            // 
            this.textEdit2.Location = new System.Drawing.Point(15, 168);
            this.textEdit2.Name = "textEdit2";
            this.textEdit2.Size = new System.Drawing.Size(100, 20);
            this.textEdit2.TabIndex = 14;
            // 
            // textEdit1
            // 
            this.textEdit1.Location = new System.Drawing.Point(15, 122);
            this.textEdit1.Name = "textEdit1";
            this.textEdit1.Size = new System.Drawing.Size(100, 20);
            this.textEdit1.TabIndex = 13;
            // 
            // lblHeight
            // 
            this.lblHeight.Location = new System.Drawing.Point(15, 102);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(35, 13);
            this.lblHeight.TabIndex = 12;
            this.lblHeight.Text = "Height:";
            // 
            // lblSizeMode
            // 
            this.lblSizeMode.Location = new System.Drawing.Point(15, 57);
            this.lblSizeMode.Name = "lblSizeMode";
            this.lblSizeMode.Size = new System.Drawing.Size(52, 13);
            this.lblSizeMode.TabIndex = 11;
            this.lblSizeMode.Text = "Size Mode:";
            // 
            // lblFitToSign
            // 
            this.lblFitToSign.Location = new System.Drawing.Point(15, 12);
            this.lblFitToSign.Name = "lblFitToSign";
            this.lblFitToSign.Size = new System.Drawing.Size(54, 13);
            this.lblFitToSign.TabIndex = 10;
            this.lblFitToSign.Text = "Fit To Sign:";
            // 
            // DynamicTextView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ddlSizeMode);
            this.Controls.Add(this.ddlFitToSign);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.textEdit2);
            this.Controls.Add(this.textEdit1);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.lblSizeMode);
            this.Controls.Add(this.lblFitToSign);
            this.Name = "DynamicTextView";
            this.Size = new System.Drawing.Size(209, 258);
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textEdit2.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textEdit1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ComboBoxEdit ddlSizeMode;
        private DevExpress.XtraEditors.ComboBoxEdit ddlFitToSign;
        private DevExpress.XtraEditors.LabelControl lblWidth;
        private DevExpress.XtraEditors.TextEdit textEdit2;
        private DevExpress.XtraEditors.TextEdit textEdit1;
        private DevExpress.XtraEditors.LabelControl lblHeight;
        private DevExpress.XtraEditors.LabelControl lblSizeMode;
        private DevExpress.XtraEditors.LabelControl lblFitToSign;
    }
}
