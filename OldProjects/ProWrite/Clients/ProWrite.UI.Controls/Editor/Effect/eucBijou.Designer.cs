namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucBijou
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
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.ddlColor = new PWColorEdit();
            this.tracRate = new DevExpress.XtraEditors.TrackBarControl();
            this.ddlLampHeight = new DevExpress.XtraEditors.SpinEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.ddlLampLength = new DevExpress.XtraEditors.SpinEdit();
            this.label5 = new System.Windows.Forms.Label();
            this.ddlGapLength = new DevExpress.XtraEditors.SpinEdit();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.radCornersOn = new DevExpress.XtraEditors.RadioGroup();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.colorGap = new PWColorEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLampHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLampLength.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlGapLength.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radCornersOn.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorGap.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 49);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Lamp Height";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(285, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Rate";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 188);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Lamp Color";
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(101, 185);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(96, 20);
            this.ddlColor.TabIndex = 5;
            // 
            // tracRate
            // 
            this.tracRate.EditValue = 1;
            this.tracRate.Location = new System.Drawing.Point(288, 34);
            this.tracRate.Name = "tracRate";
            this.tracRate.Properties.AutoSize = false;
            this.tracRate.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracRate.Properties.Maximum = 1000;
            this.tracRate.Properties.Minimum = 1;
            this.tracRate.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracRate.Size = new System.Drawing.Size(37, 135);
            this.tracRate.TabIndex = 7;
            this.tracRate.Value = 1;
            // 
            // ddlLampHeight
            // 
            this.ddlLampHeight.EditValue = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.ddlLampHeight.Location = new System.Drawing.Point(101, 43);
            this.ddlLampHeight.Name = "ddlLampHeight";
            this.ddlLampHeight.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlLampHeight.Properties.IsFloatValue = false;
            this.ddlLampHeight.Properties.Mask.EditMask = "N00";
            this.ddlLampHeight.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.ddlLampHeight.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLampHeight.Size = new System.Drawing.Size(96, 20);
            this.ddlLampHeight.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 14);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Direction";
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(101, 9);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(96, 20);
            this.ddlDirection.TabIndex = 10;
            // 
            // ddlLampLength
            // 
            this.ddlLampLength.EditValue = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.ddlLampLength.Location = new System.Drawing.Point(101, 78);
            this.ddlLampLength.Name = "ddlLampLength";
            this.ddlLampLength.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlLampLength.Properties.IsFloatValue = false;
            this.ddlLampLength.Properties.Mask.EditMask = "N00";
            this.ddlLampLength.Properties.MaxValue = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.ddlLampLength.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlLampLength.Size = new System.Drawing.Size(96, 20);
            this.ddlLampLength.TabIndex = 12;
            this.ddlLampLength.ValueChanged += new System.EventHandler(this.ddlLampLength_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 83);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(66, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Lamp Length";
            // 
            // ddlGapLength
            // 
            this.ddlGapLength.EditValue = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.ddlGapLength.Location = new System.Drawing.Point(101, 116);
            this.ddlGapLength.Name = "ddlGapLength";
            this.ddlGapLength.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlGapLength.Properties.IsFloatValue = false;
            this.ddlGapLength.Properties.Mask.EditMask = "N00";
            this.ddlGapLength.Properties.MaxValue = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.ddlGapLength.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlGapLength.Size = new System.Drawing.Size(96, 20);
            this.ddlGapLength.TabIndex = 14;
            this.ddlGapLength.ValueChanged += new System.EventHandler(this.ddlGapLength_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(23, 119);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(60, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "Gap Length";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(24, 156);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(38, 13);
            this.label7.TabIndex = 15;
            this.label7.Text = "Corner";
            // 
            // radCornersOn
            // 
            this.radCornersOn.Location = new System.Drawing.Point(97, 150);
            this.radCornersOn.Name = "radCornersOn";
            this.radCornersOn.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.radCornersOn.Properties.Appearance.Options.UseBackColor = true;
            this.radCornersOn.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.radCornersOn.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem(true, "On"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem(false, "Off")});
            this.radCornersOn.Size = new System.Drawing.Size(100, 28);
            this.radCornersOn.TabIndex = 16;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(208, 46);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "(1-1000)";
            this.label8.Visible = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(208, 83);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(46, 13);
            this.label9.TabIndex = 18;
            this.label9.Text = "(1-1000)";
            this.label9.Visible = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(208, 121);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(46, 13);
            this.label10.TabIndex = 19;
            this.label10.Text = "(1-1000)";
            this.label10.Visible = false;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(208, 188);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(51, 13);
            this.label11.TabIndex = 4;
            this.label11.Text = "Gap Color";
            // 
            // colorGap
            // 
            this.colorGap.EditValue = System.Drawing.Color.Empty;
            this.colorGap.Location = new System.Drawing.Point(265, 185);
            this.colorGap.Name = "colorGap";
            this.colorGap.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorGap.Size = new System.Drawing.Size(96, 20);
            this.colorGap.TabIndex = 5;
            // 
            // eucBijou
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.radCornersOn);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.ddlGapLength);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.ddlLampLength);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ddlLampHeight);
            this.Controls.Add(this.tracRate);
            this.Controls.Add(this.colorGap);
            this.Controls.Add(this.ddlColor);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "eucBijou";
            this.Size = new System.Drawing.Size(382, 220);
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLampHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlLampLength.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlGapLength.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radCornersOn.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorGap.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private PWColorEdit ddlColor;
        private DevExpress.XtraEditors.TrackBarControl tracRate;
        private DevExpress.XtraEditors.SpinEdit ddlLampHeight;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private DevExpress.XtraEditors.SpinEdit ddlLampLength;
        private System.Windows.Forms.Label label5;
        private DevExpress.XtraEditors.SpinEdit ddlGapLength;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private DevExpress.XtraEditors.RadioGroup radCornersOn;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private PWColorEdit colorGap;
    }
}
