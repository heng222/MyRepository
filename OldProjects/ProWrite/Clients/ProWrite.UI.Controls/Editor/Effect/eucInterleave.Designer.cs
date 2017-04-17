namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucInterleave
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
            this.ddlThickness = new DevExpress.XtraEditors.SpinEdit();
            this.label2 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.radLines = new DevExpress.XtraEditors.RadioGroup();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlThickness.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLines.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlThickness
            // 
            this.ddlThickness.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlThickness.Location = new System.Drawing.Point(124, 93);
            this.ddlThickness.Name = "ddlThickness";
            this.ddlThickness.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlThickness.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.ddlThickness.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlThickness.Size = new System.Drawing.Size(122, 20);
            this.ddlThickness.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(47, 96);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 17;
            this.label2.Text = "Thickness";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(252, 99);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 13);
            this.label5.TabIndex = 21;
            this.label5.Text = "(1-100)";
            this.label5.Visible = false;
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(124, 13);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(122, 20);
            this.ddlDirection.TabIndex = 23;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(47, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 13);
            this.label4.TabIndex = 22;
            this.label4.Text = "Direction";
            // 
            // radLines
            // 
            this.radLines.Location = new System.Drawing.Point(120, 49);
            this.radLines.Name = "radLines";
            this.radLines.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.radLines.Properties.Appearance.GradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
            this.radLines.Properties.Appearance.Options.UseBackColor = true;
            this.radLines.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.radLines.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(true, "Horizontal"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(false, "vertical")});
            this.radLines.Size = new System.Drawing.Size(182, 29);
            this.radLines.TabIndex = 25;
            this.radLines.SelectedIndexChanged += new System.EventHandler(this.radLines_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(47, 57);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 17;
            this.label1.Text = "Line";
            // 
            // eucInterleave
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.radLines);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ddlThickness);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Name = "eucInterleave";
            this.Size = new System.Drawing.Size(308, 134);
            ((System.ComponentModel.ISupportInitialize)(this.ddlThickness.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLines.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit ddlThickness;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.RadioGroup radLines;
        private System.Windows.Forms.Label label1;
    }
}
