namespace ProWrite.UI.Controls.Dashboard
{
    partial class DateTimeSet
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
            this.ddlDate = new DevExpress.XtraEditors.DateEdit();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.timeEdit1 = new DevExpress.XtraEditors.TimeEdit();
            this.btnSameTime = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDate.Properties.VistaTimeProperties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDate.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEdit1.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // ddlDate
            // 
            this.ddlDate.EditValue = new System.DateTime(2009, 2, 18, 0, 0, 0, 0);
            this.ddlDate.Location = new System.Drawing.Point(6, 12);
            this.ddlDate.Name = "ddlDate";
            this.ddlDate.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlDate.Properties.VistaTimeProperties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.ddlDate.Size = new System.Drawing.Size(102, 20);
            this.ddlDate.TabIndex = 0;
            // 
            // btnCancel
            // 
            this.btnCancel.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(208, 50);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(49, 24);
            this.btnCancel.TabIndex = 4;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnSave
            // 
            this.btnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.btnSave.Location = new System.Drawing.Point(153, 50);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(49, 24);
            this.btnSave.TabIndex = 3;
            this.btnSave.Text = "Send";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // timeEdit1
            // 
            this.timeEdit1.EditValue = new System.DateTime(2008, 12, 17, 0, 0, 0, 0);
            this.timeEdit1.Location = new System.Drawing.Point(133, 12);
            this.timeEdit1.Name = "timeEdit1";
            this.timeEdit1.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.timeEdit1.Size = new System.Drawing.Size(102, 20);
            this.timeEdit1.TabIndex = 1;
            // 
            // btnSameTime
            // 
            this.btnSameTime.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.btnSameTime.Location = new System.Drawing.Point(6, 50);
            this.btnSameTime.Name = "btnSameTime";
            this.btnSameTime.Size = new System.Drawing.Size(134, 24);
            this.btnSameTime.TabIndex = 2;
            this.btnSameTime.Text = "Same Date & Time with PC";
            this.btnSameTime.Click += new System.EventHandler(this.btnSameTime_Click);
            // 
            // DateTimeSet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(263, 88);
            this.Controls.Add(this.btnSameTime);
            this.Controls.Add(this.timeEdit1);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.ddlDate);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DateTimeSet";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Set Sign Date and Time";
            ((System.ComponentModel.ISupportInitialize)(this.ddlDate.Properties.VistaTimeProperties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlDate.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEdit1.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.DateEdit ddlDate;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private DevExpress.XtraEditors.TimeEdit timeEdit1;
        private DevExpress.XtraEditors.SimpleButton btnSameTime;
    }
}