namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucTravel
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
            this.rbtnCircular = new DevExpress.XtraEditors.RadioGroup();
            this.label7 = new System.Windows.Forms.Label();
            this.ddlSpeed = new DevExpress.XtraEditors.SpinEdit();
            this.label5 = new System.Windows.Forms.Label();
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.ddlSpacing = new DevExpress.XtraEditors.SpinEdit();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.rbtnCircular.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSpeed.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSpacing.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // rbtnCircular
            // 
            this.rbtnCircular.Location = new System.Drawing.Point(92, 116);
            this.rbtnCircular.Name = "rbtnCircular";
            this.rbtnCircular.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.rbtnCircular.Properties.Appearance.Options.UseBackColor = true;
            this.rbtnCircular.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.rbtnCircular.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(true, "Yes"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(false, "No")});
            this.rbtnCircular.Size = new System.Drawing.Size(100, 28);
            this.rbtnCircular.TabIndex = 26;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 122);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(60, 13);
            this.label7.TabIndex = 25;
            this.label7.Text = "Circular:";
            // 
            // ddlSpeed
            // 
            this.ddlSpeed.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.ddlSpeed.Location = new System.Drawing.Point(97, 82);
            this.ddlSpeed.Name = "ddlSpeed";
            this.ddlSpeed.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlSpeed.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.ddlSpeed.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.ddlSpeed.Size = new System.Drawing.Size(96, 20);
            this.ddlSpeed.TabIndex = 22;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(19, 87);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 13);
            this.label5.TabIndex = 21;
            this.label5.Text = "Speed:";
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(97, 13);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(96, 20);
            this.ddlDirection.TabIndex = 20;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 18);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = "Direction:";
            // 
            // ddlSpacing
            // 
            this.ddlSpacing.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlSpacing.Location = new System.Drawing.Point(97, 47);
            this.ddlSpacing.Name = "ddlSpacing";
            this.ddlSpacing.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlSpacing.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.ddlSpacing.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlSpacing.Size = new System.Drawing.Size(96, 20);
            this.ddlSpacing.TabIndex = 18;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 13);
            this.label1.TabIndex = 17;
            this.label1.Text = "Spacing:";
            // 
            // eucTravel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbtnCircular);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.ddlSpeed);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ddlSpacing);
            this.Controls.Add(this.label1);
            this.Name = "eucTravel";
            this.Size = new System.Drawing.Size(205, 156);
            ((System.ComponentModel.ISupportInitialize)(this.rbtnCircular.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSpeed.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSpacing.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.RadioGroup rbtnCircular;
        private System.Windows.Forms.Label label7;
        private DevExpress.XtraEditors.SpinEdit ddlSpeed;
        private System.Windows.Forms.Label label5;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.SpinEdit ddlSpacing;
        private System.Windows.Forms.Label label1;
    }
}
