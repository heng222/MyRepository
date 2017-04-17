namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucFilter
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
            this.ddlWidth = new DevExpress.XtraEditors.SpinEdit();
            this.label1 = new System.Windows.Forms.Label();
            this.ddlHeight = new DevExpress.XtraEditors.SpinEdit();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlHeight.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlWidth
            // 
            this.ddlWidth.EditValue = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.ddlWidth.Location = new System.Drawing.Point(118, 12);
            this.ddlWidth.Name = "ddlWidth";
            this.ddlWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlWidth.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.ddlWidth.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlWidth.Size = new System.Drawing.Size(102, 21);
            this.ddlWidth.TabIndex = 16;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(60, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 15;
            this.label1.Text = "Width";
            // 
            // ddlHeight
            // 
            this.ddlHeight.EditValue = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.ddlHeight.Location = new System.Drawing.Point(118, 48);
            this.ddlHeight.Name = "ddlHeight";
            this.ddlHeight.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlHeight.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.ddlHeight.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ddlHeight.Size = new System.Drawing.Size(102, 21);
            this.ddlHeight.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(60, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 17;
            this.label2.Text = "Spacing";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(226, 17);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 19;
            this.label3.Text = "(1-100)";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(226, 53);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 21;
            this.label5.Text = "(1-100)";
            // 
            // eucFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ddlHeight);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ddlWidth);
            this.Controls.Add(this.label1);
            this.Name = "eucFilter";
            ((System.ComponentModel.ISupportInitialize)(this.ddlWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlHeight.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit ddlWidth;
        private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.SpinEdit ddlHeight;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
    }
}
