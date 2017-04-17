namespace ProWrite.UI.Controls.Options.Views
{
    partial class TemperatureView
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
            this.ddlFitToSign = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblWidth = new DevExpress.XtraEditors.LabelControl();
            this.txtWidth = new DevExpress.XtraEditors.TextEdit();
            this.txtHeight = new DevExpress.XtraEditors.TextEdit();
            this.lblHeight = new DevExpress.XtraEditors.LabelControl();
            this.lblFitToSign = new DevExpress.XtraEditors.LabelControl();
            this.ddlDisplayFormat = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblDisplayFormat = new DevExpress.XtraEditors.LabelControl();
            this.lblForeColor = new DevExpress.XtraEditors.LabelControl();
            this.colorFore = new DevExpress.XtraEditors.ColorEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDisplayFormat.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorFore.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlFitToSign
            // 
            this.ddlFitToSign.EditValue = "False";
            this.ddlFitToSign.Location = new System.Drawing.Point(14, 160);
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
            this.lblWidth.Location = new System.Drawing.Point(17, 51);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(32, 13);
            this.lblWidth.TabIndex = 15;
            this.lblWidth.Text = "Width:";
            // 
            // txtWidth
            // 
            this.txtWidth.Location = new System.Drawing.Point(17, 70);
            this.txtWidth.Name = "txtWidth";
            this.txtWidth.Size = new System.Drawing.Size(100, 20);
            this.txtWidth.TabIndex = 14;
            // 
            // txtHeight
            // 
            this.txtHeight.Location = new System.Drawing.Point(17, 24);
            this.txtHeight.Name = "txtHeight";
            this.txtHeight.Size = new System.Drawing.Size(100, 20);
            this.txtHeight.TabIndex = 13;
            // 
            // lblHeight
            // 
            this.lblHeight.Location = new System.Drawing.Point(14, 5);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(35, 13);
            this.lblHeight.TabIndex = 12;
            this.lblHeight.Text = "Height:";
            // 
            // lblFitToSign
            // 
            this.lblFitToSign.Location = new System.Drawing.Point(14, 141);
            this.lblFitToSign.Name = "lblFitToSign";
            this.lblFitToSign.Size = new System.Drawing.Size(54, 13);
            this.lblFitToSign.TabIndex = 10;
            this.lblFitToSign.Text = "Fit To Sign:";
            // 
            // ddlDisplayFormat
            // 
            this.ddlDisplayFormat.Location = new System.Drawing.Point(14, 115);
            this.ddlDisplayFormat.Name = "ddlDisplayFormat";
            this.ddlDisplayFormat.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDisplayFormat.Size = new System.Drawing.Size(100, 20);
            this.ddlDisplayFormat.TabIndex = 19;
            // 
            // lblDisplayFormat
            // 
            this.lblDisplayFormat.Location = new System.Drawing.Point(17, 96);
            this.lblDisplayFormat.Name = "lblDisplayFormat";
            this.lblDisplayFormat.Size = new System.Drawing.Size(75, 13);
            this.lblDisplayFormat.TabIndex = 18;
            this.lblDisplayFormat.Text = "Display Format:";
            // 
            // lblForeColor
            // 
            this.lblForeColor.Location = new System.Drawing.Point(14, 186);
            this.lblForeColor.Name = "lblForeColor";
            this.lblForeColor.Size = new System.Drawing.Size(54, 13);
            this.lblForeColor.TabIndex = 20;
            this.lblForeColor.Text = "Fore Color:";
            // 
            // colorEdit1
            // 
            this.colorFore.EditValue = System.Drawing.Color.Empty;
            this.colorFore.Location = new System.Drawing.Point(14, 205);
            this.colorFore.Name = "colorEdit1";
            this.colorFore.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorFore.Size = new System.Drawing.Size(100, 20);
            this.colorFore.TabIndex = 21;
            // 
            // TemperatureView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.colorFore);
            this.Controls.Add(this.lblForeColor);
            this.Controls.Add(this.ddlDisplayFormat);
            this.Controls.Add(this.lblDisplayFormat);
            this.Controls.Add(this.ddlFitToSign);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.txtWidth);
            this.Controls.Add(this.txtHeight);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.lblFitToSign);
            this.Name = "TemperatureView";
            this.Size = new System.Drawing.Size(146, 246);
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDisplayFormat.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorFore.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ComboBoxEdit ddlFitToSign;
        private DevExpress.XtraEditors.LabelControl lblWidth;
        private DevExpress.XtraEditors.TextEdit txtWidth;
        private DevExpress.XtraEditors.TextEdit txtHeight;
        private DevExpress.XtraEditors.LabelControl lblHeight;
        private DevExpress.XtraEditors.LabelControl lblFitToSign;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDisplayFormat;
        private DevExpress.XtraEditors.LabelControl lblDisplayFormat;
        private DevExpress.XtraEditors.LabelControl lblForeColor;
        private DevExpress.XtraEditors.ColorEdit colorFore;
    }
}
