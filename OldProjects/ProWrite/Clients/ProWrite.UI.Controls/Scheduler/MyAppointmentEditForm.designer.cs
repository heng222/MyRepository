namespace ProWrite.UI.Controls.Scheduler
{
    partial class MyAppointmentEditForm
    {
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnOK = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.btnReccurrence = new DevExpress.XtraEditors.SimpleButton();
            this.lblSubject = new System.Windows.Forms.Label();
            this.txSubject = new DevExpress.XtraEditors.TextEdit();
            this.lblStart = new System.Windows.Forms.Label();
            this.lblEnd = new System.Windows.Forms.Label();
            this.dtStart = new DevExpress.XtraEditors.DateEdit();
            this.dtEnd = new DevExpress.XtraEditors.DateEdit();
            this.timeStart = new DevExpress.XtraEditors.TimeEdit();
            this.timeEnd = new DevExpress.XtraEditors.TimeEdit();
            this.checkAllDay = new DevExpress.XtraEditors.CheckEdit();
            this.lblType = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.checkEdit1 = new DevExpress.XtraEditors.CheckEdit();
            this.chkPlayOnce = new DevExpress.XtraEditors.CheckEdit();
            ((System.ComponentModel.ISupportInitialize)(this.txSubject.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtStart.Properties.VistaTimeProperties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtStart.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtEnd.Properties.VistaTimeProperties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtEnd.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeStart.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEnd.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.checkAllDay.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.checkEdit1.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkPlayOnce.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(62, 163);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(64, 25);
            this.btnOK.TabIndex = 10;
            this.btnOK.Text = "OK";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(131, 163);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(64, 25);
            this.btnCancel.TabIndex = 11;
            this.btnCancel.Text = "Cancel";
            // 
            // btnReccurrence
            // 
            this.btnReccurrence.Location = new System.Drawing.Point(201, 161);
            this.btnReccurrence.Name = "btnReccurrence";
            this.btnReccurrence.Size = new System.Drawing.Size(64, 27);
            this.btnReccurrence.TabIndex = 12;
            this.btnReccurrence.Text = "Recurrence";
            this.btnReccurrence.Click += new System.EventHandler(this.btnAddRec_Click);
            // 
            // lblSubject
            // 
            this.lblSubject.Location = new System.Drawing.Point(7, 13);
            this.lblSubject.Name = "lblSubject";
            this.lblSubject.Size = new System.Drawing.Size(38, 18);
            this.lblSubject.TabIndex = 4;
            this.lblSubject.Text = "Name:";
            // 
            // txSubject
            // 
            this.txSubject.EditValue = "";
            this.txSubject.Location = new System.Drawing.Point(62, 11);
            this.txSubject.Name = "txSubject";
            this.txSubject.Properties.ReadOnly = true;
            this.txSubject.Size = new System.Drawing.Size(116, 20);
            this.txSubject.TabIndex = 0;
            // 
            // lblStart
            // 
            this.lblStart.Location = new System.Drawing.Point(10, 59);
            this.lblStart.Name = "lblStart";
            this.lblStart.Size = new System.Drawing.Size(35, 18);
            this.lblStart.TabIndex = 12;
            this.lblStart.Text = "Start:";
            // 
            // lblEnd
            // 
            this.lblEnd.Location = new System.Drawing.Point(16, 79);
            this.lblEnd.Name = "lblEnd";
            this.lblEnd.Size = new System.Drawing.Size(29, 17);
            this.lblEnd.TabIndex = 13;
            this.lblEnd.Text = "End:";
            // 
            // dtStart
            // 
            this.dtStart.EditValue = new System.DateTime(2005, 11, 25, 0, 0, 0, 0);
            this.dtStart.Location = new System.Drawing.Point(62, 57);
            this.dtStart.Name = "dtStart";
            this.dtStart.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.dtStart.Properties.VistaTimeProperties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.dtStart.Size = new System.Drawing.Size(96, 20);
            this.dtStart.TabIndex = 1;
            this.dtStart.EditValueChanged += new System.EventHandler(this.dtStart_EditValueChanged);
            // 
            // dtEnd
            // 
            this.dtEnd.EditValue = new System.DateTime(2005, 11, 25, 0, 0, 0, 0);
            this.dtEnd.Location = new System.Drawing.Point(62, 80);
            this.dtEnd.Name = "dtEnd";
            this.dtEnd.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.dtEnd.Properties.VistaTimeProperties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.dtEnd.Size = new System.Drawing.Size(96, 20);
            this.dtEnd.TabIndex = 3;
            this.dtEnd.EditValueChanged += new System.EventHandler(this.dtEnd_EditValueChanged);
            // 
            // timeStart
            // 
            this.timeStart.EditValue = new System.DateTime(2006, 3, 28, 0, 0, 0, 0);
            this.timeStart.Location = new System.Drawing.Point(179, 57);
            this.timeStart.Name = "timeStart";
            this.timeStart.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.timeStart.Size = new System.Drawing.Size(80, 20);
            this.timeStart.TabIndex = 2;
            this.timeStart.EditValueChanged += new System.EventHandler(this.timeStart_EditValueChanged);
            // 
            // timeEnd
            // 
            this.timeEnd.EditValue = new System.DateTime(2006, 3, 28, 0, 0, 0, 0);
            this.timeEnd.Location = new System.Drawing.Point(179, 80);
            this.timeEnd.Name = "timeEnd";
            this.timeEnd.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.timeEnd.Size = new System.Drawing.Size(80, 20);
            this.timeEnd.TabIndex = 4;
            this.timeEnd.EditValueChanged += new System.EventHandler(this.timeEnd_EditValueChanged);
            // 
            // checkAllDay
            // 
            this.checkAllDay.Location = new System.Drawing.Point(60, 111);
            this.checkAllDay.Name = "checkAllDay";
            this.checkAllDay.Properties.Caption = "All day event";
            this.checkAllDay.Size = new System.Drawing.Size(87, 19);
            this.checkAllDay.TabIndex = 5;
            this.checkAllDay.CheckedChanged += new System.EventHandler(this.checkAllDay_CheckedChanged);
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(62, 36);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(31, 13);
            this.lblType.TabIndex = 11;
            this.lblType.Text = "Type";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(10, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 18);
            this.label1.TabIndex = 14;
            this.label1.Text = "Type:";
            // 
            // checkEdit1
            // 
            this.checkEdit1.Location = new System.Drawing.Point(157, 111);
            this.checkEdit1.Name = "checkEdit1";
            this.checkEdit1.Properties.Caption = "Exact Start Time";
            this.checkEdit1.Size = new System.Drawing.Size(108, 19);
            this.checkEdit1.TabIndex = 15;
            // 
            // chkPlayOnce
            // 
            this.chkPlayOnce.Location = new System.Drawing.Point(60, 136);
            this.chkPlayOnce.Name = "chkPlayOnce";
            this.chkPlayOnce.Properties.Caption = "Play Message Once";
            this.chkPlayOnce.Size = new System.Drawing.Size(118, 19);
            this.chkPlayOnce.TabIndex = 16;
            this.chkPlayOnce.CheckedChanged += new System.EventHandler(this.chkPlayOnce_CheckedChanged);
            // 
            // MyAppointmentEditForm
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 14);
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(273, 198);
            this.Controls.Add(this.chkPlayOnce);
            this.Controls.Add(this.checkEdit1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.checkAllDay);
            this.Controls.Add(this.timeEnd);
            this.Controls.Add(this.timeStart);
            this.Controls.Add(this.dtEnd);
            this.Controls.Add(this.dtStart);
            this.Controls.Add(this.lblEnd);
            this.Controls.Add(this.lblStart);
            this.Controls.Add(this.lblType);
            this.Controls.Add(this.txSubject);
            this.Controls.Add(this.lblSubject);
            this.Controls.Add(this.btnReccurrence);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MyAppointmentEditForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Schedule Details";
            this.Activated += new System.EventHandler(this.MyAppointmentEditForm_Activated);
            ((System.ComponentModel.ISupportInitialize)(this.txSubject.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtStart.Properties.VistaTimeProperties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtStart.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtEnd.Properties.VistaTimeProperties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dtEnd.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeStart.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.timeEnd.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.checkAllDay.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.checkEdit1.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkPlayOnce.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

    

        #endregion
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;
        private DevExpress.XtraEditors.SimpleButton btnOK;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.TextEdit txSubject;
		private DevExpress.XtraEditors.SimpleButton btnReccurrence;
		private System.Windows.Forms.Label lblSubject;
        private System.Windows.Forms.Label lblStart;
        private System.Windows.Forms.Label lblEnd;
        private DevExpress.XtraEditors.DateEdit dtStart;
        private DevExpress.XtraEditors.DateEdit dtEnd;
        private DevExpress.XtraEditors.TimeEdit timeStart;
        private DevExpress.XtraEditors.TimeEdit timeEnd;
		private System.Windows.Forms.Label lblType;
		private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.CheckEdit checkEdit1;
        private DevExpress.XtraEditors.CheckEdit chkPlayOnce;
    }
}
