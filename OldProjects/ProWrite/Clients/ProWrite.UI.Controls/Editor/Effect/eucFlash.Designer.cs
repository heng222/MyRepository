namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucFlash
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
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.ddlColor = new PWColorEdit();
            this.ddlOnTime = new DevExpress.XtraEditors.SpinEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.ddlFlashStyle = new DevExpress.XtraEditors.ComboBoxEdit();
            this.ddlOffTime = new DevExpress.XtraEditors.SpinEdit();
            this.label5 = new System.Windows.Forms.Label();
            this.ddlWED = new DevExpress.XtraEditors.SpinEdit();
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlOnTime.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFlashStyle.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlOffTime.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlWED.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "On Time";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(38, 153);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "BackColor";
            this.label3.Visible = false;
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(115, 147);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(128, 20);
            this.ddlColor.TabIndex = 5;
            // 
            // ddlOnTime
            // 
            this.ddlOnTime.EditValue = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.ddlOnTime.Location = new System.Drawing.Point(115, 42);
            this.ddlOnTime.Name = "ddlOnTime";
            this.ddlOnTime.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlOnTime.Properties.MaxValue = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.ddlOnTime.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlOnTime.Size = new System.Drawing.Size(128, 20);
            this.ddlOnTime.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(38, 13);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(55, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Flash Style";
            // 
            // ddlFlashStyle
            // 
            this.ddlFlashStyle.Location = new System.Drawing.Point(115, 8);
            this.ddlFlashStyle.Name = "ddlFlashStyle";
            this.ddlFlashStyle.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlFlashStyle.Size = new System.Drawing.Size(128, 20);
            this.ddlFlashStyle.TabIndex = 10;
            // 
            // ddlOffTime
            // 
            this.ddlOffTime.EditValue = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.ddlOffTime.Location = new System.Drawing.Point(115, 77);
            this.ddlOffTime.Name = "ddlOffTime";
            this.ddlOffTime.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlOffTime.Properties.MaxValue = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.ddlOffTime.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlOffTime.Size = new System.Drawing.Size(128, 20);
            this.ddlOffTime.TabIndex = 12;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(37, 82);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Off Time";
            // 
            // ddlWED
            // 
            this.ddlWED.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.ddlWED.Location = new System.Drawing.Point(115, 115);
            this.ddlWED.Name = "ddlWED";
            this.ddlWED.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlWED.Properties.MaxValue = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.ddlWED.Size = new System.Drawing.Size(128, 20);
            this.ddlWED.TabIndex = 14;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(37, 118);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "WED";
            this.label6.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(258, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "(1-10000ms)";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(258, 82);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 13);
            this.label7.TabIndex = 16;
            this.label7.Text = "(1-10000ms)";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(258, 118);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(40, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "(0-200)";
            this.label8.Visible = false;
            // 
            // eucFlash
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ddlWED);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.ddlOffTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ddlFlashStyle);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ddlOnTime);
            this.Controls.Add(this.ddlColor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Name = "eucFlash";
            this.Size = new System.Drawing.Size(326, 185);
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlOnTime.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlFlashStyle.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlOffTime.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlWED.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private PWColorEdit ddlColor;
        private DevExpress.XtraEditors.SpinEdit ddlOnTime;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.ComboBoxEdit ddlFlashStyle;
        private DevExpress.XtraEditors.SpinEdit ddlOffTime;
        private System.Windows.Forms.Label label5;
        private DevExpress.XtraEditors.SpinEdit ddlWED;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
    }
}
