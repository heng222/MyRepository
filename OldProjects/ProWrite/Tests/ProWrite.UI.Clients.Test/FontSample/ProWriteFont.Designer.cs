namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class ProWriteFont
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
            this.cbxFont = new System.Windows.Forms.ComboBox();
            this.tbFontSize = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblDisplayContent = new System.Windows.Forms.Label();
            this.btnOK = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.cbxFontType = new System.Windows.Forms.ComboBox();
            this.fontEdit1 = new DevExpress.XtraEditors.FontEdit();
            ((System.ComponentModel.ISupportInitialize)(this.fontEdit1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // cbxFont
            // 
            this.cbxFont.FormattingEnabled = true;
            this.cbxFont.Location = new System.Drawing.Point(124, 50);
            this.cbxFont.Name = "cbxFont";
            this.cbxFont.Size = new System.Drawing.Size(121, 21);
            this.cbxFont.TabIndex = 0;
            // 
            // tbFontSize
            // 
            this.tbFontSize.Location = new System.Drawing.Point(124, 88);
            this.tbFontSize.Name = "tbFontSize";
            this.tbFontSize.Size = new System.Drawing.Size(100, 20);
            this.tbFontSize.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Select Font";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 88);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Font Size";
            // 
            // lblDisplayContent
            // 
            this.lblDisplayContent.AutoSize = true;
            this.lblDisplayContent.Location = new System.Drawing.Point(121, 193);
            this.lblDisplayContent.Name = "lblDisplayContent";
            this.lblDisplayContent.Size = new System.Drawing.Size(28, 13);
            this.lblDisplayContent.TabIndex = 4;
            this.lblDisplayContent.Text = "ABC";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(69, 134);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 5;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "FontType";
            // 
            // cbxFontType
            // 
            this.cbxFontType.FormattingEnabled = true;
            this.cbxFontType.Items.AddRange(new object[] {
            "Private",
            "Public"});
            this.cbxFontType.Location = new System.Drawing.Point(124, 9);
            this.cbxFontType.Name = "cbxFontType";
            this.cbxFontType.Size = new System.Drawing.Size(121, 21);
            this.cbxFontType.TabIndex = 7;
            this.cbxFontType.SelectedIndexChanged += new System.EventHandler(this.cbxFontType_SelectedIndexChanged);
            // 
            // fontEdit1
            // 
            this.fontEdit1.Location = new System.Drawing.Point(169, 137);
            this.fontEdit1.Name = "fontEdit1";
            this.fontEdit1.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.fontEdit1.Size = new System.Drawing.Size(100, 20);
            this.fontEdit1.TabIndex = 8;
            // 
            // ProWriteFont
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.fontEdit1);
            this.Controls.Add(this.cbxFontType);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.lblDisplayContent);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbFontSize);
            this.Controls.Add(this.cbxFont);
            this.Name = "ProWriteFont";
            this.Text = "ProWriteFont";
            ((System.ComponentModel.ISupportInitialize)(this.fontEdit1.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbxFont;
        private System.Windows.Forms.TextBox tbFontSize;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblDisplayContent;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbxFontType;
        private DevExpress.XtraEditors.FontEdit fontEdit1;
    }
}