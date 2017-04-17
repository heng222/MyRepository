namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucBlackHole
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
            this.ddlStartX = new DevExpress.XtraEditors.SpinEdit();
            this.label1 = new System.Windows.Forms.Label();
            this.ddlStartY = new DevExpress.XtraEditors.SpinEdit();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ddlStartX.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlStartY.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlStartX
            // 
            this.ddlStartX.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.ddlStartX.Location = new System.Drawing.Point(118, 12);
            this.ddlStartX.Name = "ddlStartX";
            this.ddlStartX.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlStartX.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.ddlStartX.Properties.MinValue = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.ddlStartX.Size = new System.Drawing.Size(102, 21);
            this.ddlStartX.TabIndex = 16;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(60, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 15;
            this.label1.Text = "StartX";
            // 
            // ddlStartY
            // 
            this.ddlStartY.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.ddlStartY.Location = new System.Drawing.Point(118, 48);
            this.ddlStartY.Name = "ddlStartY";
            this.ddlStartY.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlStartY.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.ddlStartY.Properties.MinValue = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.ddlStartY.Size = new System.Drawing.Size(102, 21);
            this.ddlStartY.TabIndex = 18;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(60, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 17;
            this.label2.Text = "StartY";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(226, 17);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 12);
            this.label3.TabIndex = 19;
            this.label3.Text = "(-1000-1000)";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(226, 51);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 20;
            this.label4.Text = "(-1000-1000)";
            // 
            // eucBlackHole
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ddlStartY);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ddlStartX);
            this.Controls.Add(this.label1);
            this.Name = "eucBlackHole";
            ((System.ComponentModel.ISupportInitialize)(this.ddlStartX.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlStartY.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        } 

        #endregion

        private DevExpress.XtraEditors.SpinEdit ddlStartX;
        private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.SpinEdit ddlStartY;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}
