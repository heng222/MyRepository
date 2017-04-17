namespace ProWrite.UI.Controls.Dashboard
{
    partial class Dimming
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblPercent = new DevExpress.XtraEditors.LabelControl();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.spinDimming = new DevExpress.XtraEditors.SpinEdit();
            this.timeEnd = new DevExpress.XtraEditors.TimeEdit();
            this.timeStart = new DevExpress.XtraEditors.TimeEdit();
            this.btnOk = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl5 = new DevExpress.XtraEditors.LabelControl();
            this.ddlDimmingType = new DevExpress.XtraEditors.ComboBoxEdit();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.spinDimming.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEnd.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeStart.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDimmingType.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.deleteToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(107, 26);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            // 
            // lblPercent
            // 
            this.lblPercent.Location = new System.Drawing.Point(199, 58);
            this.lblPercent.Name = "lblPercent";
            this.lblPercent.Size = new System.Drawing.Size(11, 13);
            this.lblPercent.TabIndex = 14;
            this.lblPercent.Text = "%";
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(35, 58);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(43, 13);
            this.labelControl3.TabIndex = 13;
            this.labelControl3.Text = "Dimming:";
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(31, 61);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(47, 13);
            this.labelControl2.TabIndex = 12;
            this.labelControl2.Text = "End Time:";
            this.labelControl2.Visible = false;
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(25, 21);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(53, 13);
            this.labelControl1.TabIndex = 11;
            this.labelControl1.Text = "Start Time:";
            this.labelControl1.Visible = false;
            // 
            // spinDimming
            // 
            this.spinDimming.EditValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spinDimming.Location = new System.Drawing.Point(106, 55);
            this.spinDimming.Name = "spinDimming";
            this.spinDimming.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.spinDimming.Properties.IsFloatValue = false;
            this.spinDimming.Properties.Mask.EditMask = "N00";
            this.spinDimming.Properties.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.spinDimming.Properties.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.spinDimming.Size = new System.Drawing.Size(87, 20);
            this.spinDimming.TabIndex = 9;
            // 
            // timeEnd
            // 
            this.timeEnd.EditValue = new System.DateTime(2008, 12, 8, 0, 0, 0, 0);
            this.timeEnd.Location = new System.Drawing.Point(106, 58);
            this.timeEnd.Name = "timeEnd";
            this.timeEnd.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.timeEnd.Size = new System.Drawing.Size(87, 20);
            this.timeEnd.TabIndex = 8;
            this.timeEnd.Visible = false;
            // 
            // timeStart
            // 
            this.timeStart.EditValue = new System.DateTime(2008, 12, 8, 0, 0, 0, 0);
            this.timeStart.Location = new System.Drawing.Point(106, 18);
            this.timeStart.Name = "timeStart";
            this.timeStart.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.timeStart.Size = new System.Drawing.Size(87, 20);
            this.timeStart.TabIndex = 7;
            this.timeStart.Visible = false;
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(73, 100);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(50, 23);
            this.btnOk.TabIndex = 7;
            this.btnOk.Text = "Send";
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(140, 100);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(53, 23);
            this.btnCancel.TabIndex = 8;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // labelControl5
            // 
            this.labelControl5.Location = new System.Drawing.Point(11, 21);
            this.labelControl5.Name = "labelControl5";
            this.labelControl5.Size = new System.Drawing.Size(67, 13);
            this.labelControl5.TabIndex = 13;
            this.labelControl5.Text = "DimmingType:";
            // 
            // ddlDimmingType
            // 
            this.ddlDimmingType.Location = new System.Drawing.Point(106, 18);
            this.ddlDimmingType.Name = "ddlDimmingType";
            this.ddlDimmingType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDimmingType.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlDimmingType.Size = new System.Drawing.Size(87, 20);
            this.ddlDimmingType.TabIndex = 15;
            this.ddlDimmingType.SelectedIndexChanged += new System.EventHandler(this.ddlDimmingType_SelectedIndexChanged);
            // 
            // Dimming
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(219, 138);
            this.Controls.Add(this.ddlDimmingType);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.lblPercent);
            this.Controls.Add(this.labelControl5);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.labelControl3);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.timeStart);
            this.Controls.Add(this.timeEnd);
            this.Controls.Add(this.spinDimming);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Dimming";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Set Sign Dimming";
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.spinDimming.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEnd.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeStart.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDimmingType.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SpinEdit spinDimming;
        private DevExpress.XtraEditors.TimeEdit timeEnd;
        private DevExpress.XtraEditors.TimeEdit timeStart;
        private DevExpress.XtraEditors.LabelControl lblPercent;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.SimpleButton btnOk;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private DevExpress.XtraEditors.ComboBoxEdit ddlDimmingType;
        private DevExpress.XtraEditors.LabelControl labelControl5;
    }
}

