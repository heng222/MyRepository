namespace ProWrite.UI.Controls.Editor.Effect
{
    partial class eucVenetian
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
            this.ddlDirection = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label4 = new System.Windows.Forms.Label();
            this.spBlindWidth = new DevExpress.XtraEditors.SpinEdit();
            this.lblWidth = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spBlindWidth.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlDirection
            // 
            this.ddlDirection.Location = new System.Drawing.Point(115, 18);
            this.ddlDirection.Name = "ddlDirection";
            this.ddlDirection.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDirection.Size = new System.Drawing.Size(96, 20);
            this.ddlDirection.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(38, 23);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Direction:";
            // 
            // spBlindWidth
            // 
            this.spBlindWidth.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spBlindWidth.Location = new System.Drawing.Point(115, 58);
            this.spBlindWidth.Name = "spBlindWidth";
            this.spBlindWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spBlindWidth.Properties.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.spBlindWidth.Size = new System.Drawing.Size(96, 20);
            this.spBlindWidth.TabIndex = 16;
            
            // 
            // lblWidth
            // 
            this.lblWidth.Location = new System.Drawing.Point(41, 61);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(54, 13);
            this.lblWidth.TabIndex = 15;
            this.lblWidth.Text = "Blind Width:";
            // 
            // eucVenetian
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.spBlindWidth);
            this.Controls.Add(this.lblWidth);
            this.Controls.Add(this.ddlDirection);
            this.Controls.Add(this.label4);
            this.Name = "eucVenetian";
            this.Size = new System.Drawing.Size(283, 112);
            ((System.ComponentModel.ISupportInitialize)(this.ddlDirection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spBlindWidth.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.ComboBoxEdit ddlDirection;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.SpinEdit spBlindWidth;
        private DevExpress.XtraEditors.LabelControl lblWidth;
    }
}
