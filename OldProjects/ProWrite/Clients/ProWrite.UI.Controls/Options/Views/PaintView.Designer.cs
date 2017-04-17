namespace ProWrite.UI.Controls.Options.Views
{
    partial class PaintView
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
            this.spinWidth = new DevExpress.XtraEditors.SpinEdit();
            this.lblLineColor = new DevExpress.XtraEditors.LabelControl();
            this.colorLine = new DevExpress.XtraEditors.ColorEdit();
            this.ddlDashStyle = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblLineDashStyle = new DevExpress.XtraEditors.LabelControl();
            this.lblLineWidth = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.spinWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorLine.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDashStyle.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // spinWidth
            // 
            this.spinWidth.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.spinWidth.Location = new System.Drawing.Point(15, 126);
            this.spinWidth.Name = "spinWidth";
            this.spinWidth.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinWidth.Size = new System.Drawing.Size(100, 20);
            this.spinWidth.TabIndex = 0;
            // 
            // lblLineColor
            // 
            this.lblLineColor.Location = new System.Drawing.Point(17, 12);
            this.lblLineColor.Name = "lblLineColor";
            this.lblLineColor.Size = new System.Drawing.Size(51, 13);
            this.lblLineColor.TabIndex = 1;
            this.lblLineColor.Text = "Line Color:";
            // 
            // colorLine
            // 
            this.colorLine.EditValue = System.Drawing.Color.Empty;
            this.colorLine.Location = new System.Drawing.Point(17, 32);
            this.colorLine.Name = "colorLine";
            this.colorLine.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorLine.Size = new System.Drawing.Size(100, 20);
            this.colorLine.TabIndex = 2;
            // 
            // ddlDashStyle
            // 
            this.ddlDashStyle.Location = new System.Drawing.Point(15, 77);
            this.ddlDashStyle.Name = "ddlDashStyle";
            this.ddlDashStyle.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDashStyle.Size = new System.Drawing.Size(100, 20);
            this.ddlDashStyle.TabIndex = 3;
            // 
            // lblLineDashStyle
            // 
            this.lblLineDashStyle.Location = new System.Drawing.Point(17, 58);
            this.lblLineDashStyle.Name = "lblLineDashStyle";
            this.lblLineDashStyle.Size = new System.Drawing.Size(77, 13);
            this.lblLineDashStyle.TabIndex = 4;
            this.lblLineDashStyle.Text = "Line Dash Style:";
            // 
            // lblLineWidth
            // 
            this.lblLineWidth.Location = new System.Drawing.Point(15, 103);
            this.lblLineWidth.Name = "lblLineWidth";
            this.lblLineWidth.Size = new System.Drawing.Size(54, 13);
            this.lblLineWidth.TabIndex = 5;
            this.lblLineWidth.Text = "Line Width:";
            // 
            // PaintView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lblLineWidth);
            this.Controls.Add(this.lblLineDashStyle);
            this.Controls.Add(this.ddlDashStyle);
            this.Controls.Add(this.colorLine);
            this.Controls.Add(this.lblLineColor);
            this.Controls.Add(this.spinWidth);
            this.Name = "PaintView";
            this.Size = new System.Drawing.Size(160, 164);
            ((System.ComponentModel.ISupportInitialize)(this.spinWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorLine.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDashStyle.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit spinWidth;
        private DevExpress.XtraEditors.LabelControl lblLineColor;
        private DevExpress.XtraEditors.ColorEdit colorLine;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDashStyle;
        private DevExpress.XtraEditors.LabelControl lblLineDashStyle;
        private DevExpress.XtraEditors.LabelControl lblLineWidth;
    }
}
