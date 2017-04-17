namespace ProWrite.UI.Controls.Options.Views
{
    partial class TextView
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
            this.txtWidth = new DevExpress.XtraEditors.TextEdit();
            this.txtHeight = new DevExpress.XtraEditors.TextEdit();
            this.lblHeight = new DevExpress.XtraEditors.LabelControl();
            this.lblSizeMode = new DevExpress.XtraEditors.LabelControl();
            this.lblFitToSign = new DevExpress.XtraEditors.LabelControl();
            this.lblBackGroundColor = new DevExpress.XtraEditors.LabelControl();
            this.lblForeColor = new DevExpress.XtraEditors.LabelControl();
            this.colorBackGround = new DevExpress.XtraEditors.ColorEdit();
            this.colorFore = new DevExpress.XtraEditors.ColorEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorBackGround.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorFore.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlSizeMode
            // 
            this.ddlSizeMode.Location = new System.Drawing.Point(17, 253);
            this.ddlSizeMode.Name = "ddlSizeMode";
            this.ddlSizeMode.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSizeMode.Size = new System.Drawing.Size(100, 20);
            this.ddlSizeMode.TabIndex = 17;
            // 
            // ddlFitToSign
            // 
            this.ddlFitToSign.EditValue = "False";
            this.ddlFitToSign.Location = new System.Drawing.Point(17, 208);
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
            this.lblWidth.Location = new System.Drawing.Point(17, 53);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(32, 13);
            this.lblWidth.TabIndex = 15;
            this.lblWidth.Text = "Width:";
            // 
            // txtWidth
            // 
            this.txtWidth.Location = new System.Drawing.Point(17, 72);
            this.txtWidth.Name = "txtWidth";
            this.txtWidth.Size = new System.Drawing.Size(100, 20);
            this.txtWidth.TabIndex = 14;
            // 
            // txtHeight
            // 
            this.txtHeight.Location = new System.Drawing.Point(17, 27);
            this.txtHeight.Name = "txtHeight";
            this.txtHeight.Size = new System.Drawing.Size(100, 20);
            this.txtHeight.TabIndex = 13;
            // 
            // lblHeight
            // 
            this.lblHeight.Location = new System.Drawing.Point(17, 8);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(35, 13);
            this.lblHeight.TabIndex = 12;
            this.lblHeight.Text = "Height:";
            // 
            // lblSizeMode
            // 
            this.lblSizeMode.Location = new System.Drawing.Point(17, 234);
            this.lblSizeMode.Name = "lblSizeMode";
            this.lblSizeMode.Size = new System.Drawing.Size(52, 13);
            this.lblSizeMode.TabIndex = 11;
            this.lblSizeMode.Text = "Size Mode:";
            // 
            // lblFitToSign
            // 
            this.lblFitToSign.Location = new System.Drawing.Point(17, 189);
            this.lblFitToSign.Name = "lblFitToSign";
            this.lblFitToSign.Size = new System.Drawing.Size(54, 13);
            this.lblFitToSign.TabIndex = 10;
            this.lblFitToSign.Text = "Fit To Sign:";
            // 
            // lblBackGroundColor
            // 
            this.lblBackGroundColor.Location = new System.Drawing.Point(17, 98);
            this.lblBackGroundColor.Name = "lblBackGroundColor";
            this.lblBackGroundColor.Size = new System.Drawing.Size(89, 13);
            this.lblBackGroundColor.TabIndex = 18;
            this.lblBackGroundColor.Text = "BackGround Color:";
            // 
            // lblForeColor
            // 
            this.lblForeColor.Location = new System.Drawing.Point(17, 144);
            this.lblForeColor.Name = "lblForeColor";
            this.lblForeColor.Size = new System.Drawing.Size(54, 13);
            this.lblForeColor.TabIndex = 19;
            this.lblForeColor.Text = "Fore Color:";
            // 
            // colorBackGround
            // 
            this.colorBackGround.EditValue = System.Drawing.Color.Empty;
            this.colorBackGround.Location = new System.Drawing.Point(17, 118);
            this.colorBackGround.Name = "colorBackGround";
            this.colorBackGround.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorBackGround.Size = new System.Drawing.Size(100, 20);
            this.colorBackGround.TabIndex = 20;
            // 
            // colorFore
            // 
            this.colorFore.EditValue = System.Drawing.Color.Empty;
            this.colorFore.Location = new System.Drawing.Point(17, 163);
            this.colorFore.Name = "colorFore";
            this.colorFore.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorFore.Size = new System.Drawing.Size(100, 20);
            this.colorFore.TabIndex = 21;
            // 
            // TextView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.colorFore);
            this.Controls.Add(this.colorBackGround);
            this.Controls.Add(this.lblForeColor);
            this.Controls.Add(this.lblBackGroundColor);
            this.Controls.Add(this.ddlSizeMode);
            this.Controls.Add(this.ddlFitToSign);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.txtWidth);
            this.Controls.Add(this.txtHeight);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.lblSizeMode);
            this.Controls.Add(this.lblFitToSign);
            this.Name = "TextView";
            this.Size = new System.Drawing.Size(140, 294);
            ((System.ComponentModel.ISupportInitialize)(this.ddlSizeMode.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFitToSign.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorBackGround.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorFore.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ComboBoxEdit ddlSizeMode;
        private DevExpress.XtraEditors.ComboBoxEdit ddlFitToSign;
        private DevExpress.XtraEditors.LabelControl lblWidth;
        private DevExpress.XtraEditors.TextEdit txtWidth;
        private DevExpress.XtraEditors.TextEdit txtHeight;
        private DevExpress.XtraEditors.LabelControl lblHeight;
        private DevExpress.XtraEditors.LabelControl lblSizeMode;
        private DevExpress.XtraEditors.LabelControl lblFitToSign;
        private DevExpress.XtraEditors.LabelControl lblBackGroundColor;
        private DevExpress.XtraEditors.LabelControl lblForeColor;
        private DevExpress.XtraEditors.ColorEdit colorBackGround;
        private DevExpress.XtraEditors.ColorEdit colorFore;
    }
}
