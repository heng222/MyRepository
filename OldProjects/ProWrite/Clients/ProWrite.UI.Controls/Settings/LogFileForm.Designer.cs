namespace ProWrite.UI.Controls.Settings
{
    partial class LogFileForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LogFileForm));
            this.btnDelete = new DevExpress.XtraEditors.SimpleButton();
            this.gridView1 = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.groupControl1 = new DevExpress.XtraEditors.GroupControl();
            this.gridEvent = new DevExpress.XtraGrid.GridControl();
            this.gridView2 = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.Event = new DevExpress.XtraGrid.Columns.GridColumn();
            this.Date = new DevExpress.XtraGrid.Columns.GridColumn();
            this.UserName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.gridMessage = new DevExpress.XtraGrid.GridControl();
            this.gridView3 = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.MessageName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.StartDate = new DevExpress.XtraGrid.Columns.GridColumn();
            this.FinishDate = new DevExpress.XtraGrid.Columns.GridColumn();
            this.WebCam = new DevExpress.XtraGrid.Columns.GridColumn();
            this.ErrorCodes = new DevExpress.XtraGrid.Columns.GridColumn();
            this.groupControl2 = new DevExpress.XtraEditors.GroupControl();
            this.rdbtMessage = new System.Windows.Forms.RadioButton();
            this.rdbtEvent = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupControl1)).BeginInit();
            this.groupControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridEvent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridMessage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupControl2)).BeginInit();
            this.groupControl2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnDelete
            // 
            this.btnDelete.AllowDrop = true;
            this.btnDelete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnDelete.Image = ((System.Drawing.Image)(resources.GetObject("btnDelete.Image")));
            this.btnDelete.Location = new System.Drawing.Point(5, 287);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(27, 31);
            this.btnDelete.TabIndex = 13;
            this.btnDelete.ToolTip = "Delete";
            // 
            // gridView1
            // 
            this.gridView1.Name = "gridView1";
            // 
            // groupControl1
            // 
            this.groupControl1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.groupControl1.Controls.Add(this.gridMessage);
            this.groupControl1.Controls.Add(this.gridEvent);
            this.groupControl1.Controls.Add(this.btnDelete);
            this.groupControl1.Location = new System.Drawing.Point(35, 87);
            this.groupControl1.Name = "groupControl1";
            this.groupControl1.Size = new System.Drawing.Size(512, 323);
            this.groupControl1.TabIndex = 14;
            this.groupControl1.Text = "User List";
            // 
            // gridEvent
            // 
            this.gridEvent.EmbeddedNavigator.Name = "";
            this.gridEvent.Location = new System.Drawing.Point(5, 23);
            this.gridEvent.MainView = this.gridView2;
            this.gridEvent.Name = "gridEvent";
            this.gridEvent.Size = new System.Drawing.Size(507, 258);
            this.gridEvent.TabIndex = 14;
            this.gridEvent.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView2});
            // 
            // gridView2
            // 
            this.gridView2.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.Event,
            this.Date,
            this.UserName});
            this.gridView2.GridControl = this.gridEvent;
            this.gridView2.Name = "gridView2";
            // 
            // Event
            // 
            this.Event.Caption = "Event";
            this.Event.FieldName = "Event";
            this.Event.Name = "Event";
            this.Event.Visible = true;
            this.Event.VisibleIndex = 0;
            // 
            // Date
            // 
            this.Date.Caption = "Date";
            this.Date.DisplayFormat.FormatString = "d";
            this.Date.DisplayFormat.FormatType = DevExpress.Utils.FormatType.DateTime;
            this.Date.FieldName = "Date";
            this.Date.GroupFormat.FormatString = "d";
            this.Date.GroupFormat.FormatType = DevExpress.Utils.FormatType.DateTime;
            this.Date.Name = "Date";
            this.Date.Visible = true;
            this.Date.VisibleIndex = 1;
            // 
            // UserName
            // 
            this.UserName.Caption = "UserName";
            this.UserName.FieldName = "UserName";
            this.UserName.Name = "UserName";
            this.UserName.Visible = true;
            this.UserName.VisibleIndex = 2;
            // 
            // gridMessage
            // 
            this.gridMessage.EmbeddedNavigator.Name = "";
            this.gridMessage.Location = new System.Drawing.Point(5, 24);
            this.gridMessage.MainView = this.gridView3;
            this.gridMessage.Name = "gridMessage";
            this.gridMessage.Size = new System.Drawing.Size(502, 257);
            this.gridMessage.TabIndex = 15;
            this.gridMessage.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView3});
            // 
            // gridView3
            // 
            this.gridView3.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.MessageName,
            this.StartDate,
            this.FinishDate,
            this.WebCam,
            this.ErrorCodes});
            this.gridView3.GridControl = this.gridMessage;
            this.gridView3.Name = "gridView3";
            // 
            // MessageName
            // 
            this.MessageName.Caption = "Message Name";
            this.MessageName.FieldName = "MessageName";
            this.MessageName.Name = "MessageName";
            this.MessageName.Visible = true;
            this.MessageName.VisibleIndex = 0;
            // 
            // StartDate
            // 
            this.StartDate.Caption = "Start DateTime";
            this.StartDate.FieldName = "StartDate";
            this.StartDate.Name = "StartDate";
            this.StartDate.Visible = true;
            this.StartDate.VisibleIndex = 1;
            // 
            // FinishDate
            // 
            this.FinishDate.Caption = "Finish Date";
            this.FinishDate.FieldName = "FinishDate";
            this.FinishDate.Name = "FinishDate";
            this.FinishDate.Visible = true;
            this.FinishDate.VisibleIndex = 2;
            // 
            // WebCam
            // 
            this.WebCam.Caption = "Web Cam Image";
            this.WebCam.FieldName = "WebCam";
            this.WebCam.Name = "WebCam";
            this.WebCam.Visible = true;
            this.WebCam.VisibleIndex = 3;
            // 
            // ErrorCodes
            // 
            this.ErrorCodes.Caption = "Error Codes";
            this.ErrorCodes.FieldName = "ErrorCodes";
            this.ErrorCodes.Name = "ErrorCodes";
            this.ErrorCodes.Visible = true;
            this.ErrorCodes.VisibleIndex = 4;
            // 
            // groupControl2
            // 
            this.groupControl2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.groupControl2.Controls.Add(this.rdbtEvent);
            this.groupControl2.Controls.Add(this.rdbtMessage);
            this.groupControl2.Location = new System.Drawing.Point(35, 27);
            this.groupControl2.Name = "groupControl2";
            this.groupControl2.Size = new System.Drawing.Size(512, 54);
            this.groupControl2.TabIndex = 13;
            this.groupControl2.Text = "Query Condition";
            // 
            // rdbtMessage
            // 
            this.rdbtMessage.AutoSize = true;
            this.rdbtMessage.Checked = true;
            this.rdbtMessage.Location = new System.Drawing.Point(103, 23);
            this.rdbtMessage.Name = "rdbtMessage";
            this.rdbtMessage.Size = new System.Drawing.Size(68, 17);
            this.rdbtMessage.TabIndex = 14;
            this.rdbtMessage.TabStop = true;
            this.rdbtMessage.Text = "Message";
            this.rdbtMessage.UseVisualStyleBackColor = true;
            // 
            // rdbtEvent
            // 
            this.rdbtEvent.AutoSize = true;
            this.rdbtEvent.Location = new System.Drawing.Point(231, 23);
            this.rdbtEvent.Name = "rdbtEvent";
            this.rdbtEvent.Size = new System.Drawing.Size(53, 17);
            this.rdbtEvent.TabIndex = 14;
            this.rdbtEvent.Text = "Event";
            this.rdbtEvent.UseVisualStyleBackColor = true;
            // 
            // LogFileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupControl1);
            this.Controls.Add(this.groupControl2);
            this.Name = "LogFileForm";
            this.Size = new System.Drawing.Size(583, 436);
            ((System.ComponentModel.ISupportInitialize)(this.gridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupControl1)).EndInit();
            this.groupControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.gridEvent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridMessage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupControl2)).EndInit();
            this.groupControl2.ResumeLayout(false);
            this.groupControl2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton btnDelete;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView1;
        private DevExpress.XtraEditors.GroupControl groupControl1;
        private DevExpress.XtraGrid.GridControl gridEvent;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView2;
        private DevExpress.XtraGrid.Columns.GridColumn Event;
        private DevExpress.XtraGrid.Columns.GridColumn Date;
        private DevExpress.XtraGrid.Columns.GridColumn UserName;
        private DevExpress.XtraGrid.GridControl gridMessage;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView3;
        private DevExpress.XtraGrid.Columns.GridColumn MessageName;
        private DevExpress.XtraGrid.Columns.GridColumn StartDate;
        private DevExpress.XtraGrid.Columns.GridColumn FinishDate;
        private DevExpress.XtraGrid.Columns.GridColumn WebCam;
        private DevExpress.XtraGrid.Columns.GridColumn ErrorCodes;
        private DevExpress.XtraEditors.GroupControl groupControl2;
        private System.Windows.Forms.RadioButton rdbtEvent;
        private System.Windows.Forms.RadioButton rdbtMessage;
    }
}
