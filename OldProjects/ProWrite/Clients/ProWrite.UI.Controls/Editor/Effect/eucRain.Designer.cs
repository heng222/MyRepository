namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucRain
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
            this.tracAmount = new DevExpress.XtraEditors.TrackBarControl();
            this.ddlAngle = new DevExpress.XtraEditors.SpinEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlAngle.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(160, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Angle";
            this.label1.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(47, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Amount";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(160, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "Color";
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(213, 10);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(100, 21);
            this.ddlColor.TabIndex = 5;
            // 
            // tracAmount
            // 
            this.tracAmount.EditValue = null;
            this.tracAmount.Location = new System.Drawing.Point(97, 11);
            this.tracAmount.Name = "tracAmount";
            this.tracAmount.Properties.AutoSize = false;
            this.tracAmount.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracAmount.Properties.Minimum = 1;
            this.tracAmount.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracAmount.Size = new System.Drawing.Size(32, 146);
            this.tracAmount.TabIndex = 7;
            this.tracAmount.Value = 1;
            // 
            // ddlAngle
            // 
            this.ddlAngle.EditValue = new decimal(new int[] {
            90,
            0,
            0,
            0});
            this.ddlAngle.Location = new System.Drawing.Point(213, 56);
            this.ddlAngle.Name = "ddlAngle";
            this.ddlAngle.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlAngle.Properties.MaxValue = new decimal(new int[] {
            150,
            0,
            0,
            0});
            this.ddlAngle.Properties.MinValue = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.ddlAngle.Size = new System.Drawing.Size(100, 21);
            this.ddlAngle.TabIndex = 8;
            ddlAngle.Visible = false;
            // 
            // eucRain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ddlAngle);
            this.Controls.Add(this.tracAmount);
            this.Controls.Add(this.ddlColor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "eucRain";
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlAngle.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private PWColorEdit ddlColor;
        private DevExpress.XtraEditors.TrackBarControl tracAmount;
        private DevExpress.XtraEditors.SpinEdit ddlAngle;
    }
}
