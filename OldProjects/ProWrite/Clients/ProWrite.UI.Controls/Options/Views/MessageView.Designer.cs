namespace ProWrite.UI.Controls.Options.Views
{
    partial class MessageView
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
            this.spinDisPlayTime = new DevExpress.XtraEditors.SpinEdit();
            this.lblBackGroundColor = new DevExpress.XtraEditors.LabelControl();
            this.colorBackGround = new DevExpress.XtraEditors.ColorEdit();
            this.lblDisplayTime = new DevExpress.XtraEditors.LabelControl();
            this.lblIsShowGrid = new DevExpress.XtraEditors.LabelControl();
            this.ddlIsShowGrid = new DevExpress.XtraEditors.ComboBoxEdit();
            ((System.ComponentModel.ISupportInitialize)(this.spinDisPlayTime.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorBackGround.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlIsShowGrid.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // spinDisPlayTime
            // 
            this.spinDisPlayTime.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spinDisPlayTime.Location = new System.Drawing.Point(15, 80);
            this.spinDisPlayTime.Name = "spinDisPlayTime";
            this.spinDisPlayTime.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinDisPlayTime.Properties.IsFloatValue = false;
            this.spinDisPlayTime.Properties.Mask.EditMask = "N00";
            this.spinDisPlayTime.Properties.MaxLength = 4;
            this.spinDisPlayTime.Properties.MaxValue = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.spinDisPlayTime.Size = new System.Drawing.Size(100, 20);
            this.spinDisPlayTime.TabIndex = 13;
            // 
            // lblBackGroundColor
            // 
            this.lblBackGroundColor.Location = new System.Drawing.Point(15, 11);
            this.lblBackGroundColor.Name = "lblBackGroundColor";
            this.lblBackGroundColor.Size = new System.Drawing.Size(92, 13);
            this.lblBackGroundColor.TabIndex = 14;
            this.lblBackGroundColor.Text = "Back Ground Color:";
            // 
            // colorEdit1
            // 
            this.colorBackGround.EditValue = System.Drawing.Color.Empty;
            this.colorBackGround.Location = new System.Drawing.Point(15, 30);
            this.colorBackGround.Name = "colorEdit1";
            this.colorBackGround.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.colorBackGround.Size = new System.Drawing.Size(100, 20);
            this.colorBackGround.TabIndex = 15;
            // 
            // lblDisplayTime
            // 
            this.lblDisplayTime.Location = new System.Drawing.Point(15, 61);
            this.lblDisplayTime.Name = "lblDisplayTime";
            this.lblDisplayTime.Size = new System.Drawing.Size(76, 13);
            this.lblDisplayTime.TabIndex = 16;
            this.lblDisplayTime.Text = "Display Time(s):";
            // 
            // lblIsShowGrid
            // 
            this.lblIsShowGrid.Location = new System.Drawing.Point(15, 106);
            this.lblIsShowGrid.Name = "lblIsShowGrid";
            this.lblIsShowGrid.Size = new System.Drawing.Size(64, 13);
            this.lblIsShowGrid.TabIndex = 17;
            this.lblIsShowGrid.Text = "Is Show Grid:";
            // 
            // ddlIsShowGrid
            // 
            this.ddlIsShowGrid.EditValue = "True";
            this.ddlIsShowGrid.Location = new System.Drawing.Point(15, 125);
            this.ddlIsShowGrid.Name = "ddlIsShowGrid";
            this.ddlIsShowGrid.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlIsShowGrid.Properties.Items.AddRange(new object[] {
            "True",
            "False"});
            this.ddlIsShowGrid.Size = new System.Drawing.Size(100, 20);
            this.ddlIsShowGrid.TabIndex = 18;
            // 
            // MessageView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ddlIsShowGrid);
            this.Controls.Add(this.lblIsShowGrid);
            this.Controls.Add(this.lblDisplayTime);
            this.Controls.Add(this.colorBackGround);
            this.Controls.Add(this.lblBackGroundColor);
            this.Controls.Add(this.spinDisPlayTime);
            this.Name = "MessageView";
            this.Size = new System.Drawing.Size(148, 175);
            ((System.ComponentModel.ISupportInitialize)(this.spinDisPlayTime.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.colorBackGround.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlIsShowGrid.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit spinDisPlayTime;
        private DevExpress.XtraEditors.LabelControl lblBackGroundColor;
        private DevExpress.XtraEditors.ColorEdit colorBackGround;
        private DevExpress.XtraEditors.LabelControl lblDisplayTime;
        private DevExpress.XtraEditors.LabelControl lblIsShowGrid;
        private DevExpress.XtraEditors.ComboBoxEdit ddlIsShowGrid;
    }
}
