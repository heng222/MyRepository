namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucSparkle
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
            this.ddlSize = new DevExpress.XtraEditors.SpinEdit();
            this.tracAmount = new DevExpress.XtraEditors.TrackBarControl();
            this.ddlColor = new PWColorEdit();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSize.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlSize
            // 
            this.ddlSize.EditValue = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.ddlSize.Location = new System.Drawing.Point(228, 63);
            this.ddlSize.Name = "ddlSize";
            this.ddlSize.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlSize.Properties.MaxValue = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.ddlSize.Properties.MinValue = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.ddlSize.Size = new System.Drawing.Size(44, 20);
            this.ddlSize.TabIndex = 14;
            // 
            // tracAmount
            // 
            this.tracAmount.EditValue = 20;
            this.tracAmount.Location = new System.Drawing.Point(95, 14);
            this.tracAmount.Name = "tracAmount";
            this.tracAmount.Properties.AutoSize = false;
            this.tracAmount.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracAmount.Properties.Maximum = 100;
            this.tracAmount.Properties.Minimum = 1;
            this.tracAmount.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracAmount.Size = new System.Drawing.Size(32, 158);
            this.tracAmount.TabIndex = 13;
            this.tracAmount.Value = 20;
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(228, 13);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(110, 20);
            this.ddlColor.TabIndex = 12;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(178, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Color";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(34, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Amount";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(178, 68);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Size";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(286, 68);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(34, 13);
            this.label7.TabIndex = 17;
            this.label7.Text = "(1-20)";
            // 
            // eucSparkle
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label7);
            this.Controls.Add(this.ddlSize);
            this.Controls.Add(this.tracAmount);
            this.Controls.Add(this.ddlColor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "eucSparkle";
            ((System.ComponentModel.ISupportInitialize)(this.ddlSize.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit ddlSize;
        private DevExpress.XtraEditors.TrackBarControl tracAmount;
        private PWColorEdit ddlColor;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label7;

    }
}
