namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucSnow
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
            this.tracAmount = new DevExpress.XtraEditors.TrackBarControl();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(199, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Amount";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(60, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Rate";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(60, 13);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "Color";
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(112, 8);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(180, 21);
            this.ddlColor.TabIndex = 5;
            // 
            // tracRate
            // 
            this.tracRate.EditValue = null;
            this.tracRate.Location = new System.Drawing.Point(112, 47);
            this.tracRate.Name = "tracRate";
            this.tracRate.Properties.AutoSize = false;
            this.tracRate.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracRate.Properties.Maximum = 32;
            this.tracRate.Properties.Minimum = 1;
            this.tracRate.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracRate.Size = new System.Drawing.Size(32, 113);
            this.tracRate.TabIndex = 7;
            // 
            // tracAmount
            // 
            this.tracAmount.EditValue = null;
            this.tracAmount.Location = new System.Drawing.Point(260, 47);
            this.tracAmount.Name = "tracAmount";
            this.tracAmount.Properties.AutoSize = false;
            this.tracAmount.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.Simple;
            this.tracAmount.Properties.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tracAmount.Size = new System.Drawing.Size(32, 113);
            this.tracAmount.TabIndex = 8;
            this.tracAmount.Properties.Minimum = 3;
            // 
            // ucSnow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tracAmount);
            this.Controls.Add(this.tracRate);
            this.Controls.Add(this.ddlColor);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "ucSnow";
            this.Size = new System.Drawing.Size(370, 170);
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tracAmount)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private PWColorEdit ddlColor;
        private DevExpress.XtraEditors.TrackBarControl tracRate;
        private DevExpress.XtraEditors.TrackBarControl tracAmount;
    }
}
