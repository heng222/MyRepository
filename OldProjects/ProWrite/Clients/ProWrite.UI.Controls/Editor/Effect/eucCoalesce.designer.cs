namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucCoalesce
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
            this.lblWidth = new DevExpress.XtraEditors.LabelControl();
            this.lblHeight = new DevExpress.XtraEditors.LabelControl();
            this.spWidth = new DevExpress.XtraEditors.SpinEdit();
            this.spHeight = new DevExpress.XtraEditors.SpinEdit();
            ((System.ComponentModel.ISupportInitialize)(this.spWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spHeight.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lblWidth
            // 
            this.lblWidth.Location = new System.Drawing.Point(23, 21);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(32, 13);
            this.lblWidth.TabIndex = 1;
            this.lblWidth.Text = "Width:";
            // 
            // lblHeight
            // 
            this.lblHeight.Location = new System.Drawing.Point(23, 58);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(35, 13);
            this.lblHeight.TabIndex = 2;
            this.lblHeight.Text = "Height:";
            // 
            // spWidth
            // 
            this.spWidth.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spWidth.Location = new System.Drawing.Point(102, 18);
            this.spWidth.Name = "spWidth";
            this.spWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spWidth.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.spWidth.Size = new System.Drawing.Size(75, 20);
            this.spWidth.TabIndex = 3;
            // 
            // spHeight
            // 
            this.spHeight.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spHeight.Location = new System.Drawing.Point(102, 55);
            this.spHeight.Name = "spHeight";
            this.spHeight.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spHeight.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.spHeight.Size = new System.Drawing.Size(75, 20);
            this.spHeight.TabIndex = 4;
            // 
            // eucCoalesce
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.spHeight);
            this.Controls.Add(this.spWidth);
            this.Controls.Add(this.lblHeight);
            this.Controls.Add(this.lblWidth);
            this.Name = "eucCoalesce";
            this.Size = new System.Drawing.Size(203, 94);
            ((System.ComponentModel.ISupportInitialize)(this.spWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spHeight.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.LabelControl lblWidth;
        private DevExpress.XtraEditors.LabelControl lblHeight;
        private DevExpress.XtraEditors.SpinEdit spWidth;
        private DevExpress.XtraEditors.SpinEdit spHeight;
    }
}
