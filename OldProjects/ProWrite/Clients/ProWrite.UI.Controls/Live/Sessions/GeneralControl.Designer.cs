namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class GeneralControl
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
            this.lblSessionName = new DevExpress.XtraEditors.LabelControl();
            this.teSessionName = new DevExpress.XtraEditors.TextEdit();
            this.pnlSessionName = new DevExpress.XtraEditors.PanelControl();
            this.pnlCenter = new DevExpress.XtraEditors.PanelControl();
            this.sbtnDeleteSession = new DevExpress.XtraEditors.SimpleButton();
            this.panelControl2 = new DevExpress.XtraEditors.PanelControl();
            this.sbtnReport = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnReset = new DevExpress.XtraEditors.SimpleButton();
            this.rgNail = new DevExpress.XtraEditors.RadioGroup();
            this.rgCounter = new DevExpress.XtraEditors.RadioGroup();
            this.mnMessage = new ProWrite.UI.Controls.Live.Sessions.MessageNailControl();
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.lblAutoQueue = new DevExpress.XtraEditors.LabelControl();
            this.seAutoQueueCounter = new DevExpress.XtraEditors.SpinEdit();
            this.pnlCenterAlert = new DevExpress.XtraEditors.PanelControl();
            this.pnlCenterALertRed = new DevExpress.XtraEditors.PanelControl();
            this.scRed = new ProWrite.UI.Controls.Live.Sessions.SignConfigControl();
            this.seRed = new DevExpress.XtraEditors.SpinEdit();
            this.lblRed = new DevExpress.XtraEditors.LabelControl();
            this.pnlCenterALertYellow = new DevExpress.XtraEditors.PanelControl();
            this.scYello = new ProWrite.UI.Controls.Live.Sessions.SignConfigControl();
            this.seYellow = new DevExpress.XtraEditors.SpinEdit();
            this.lblYellowTitle = new DevExpress.XtraEditors.LabelControl();
            this.pnlCenterALertGreen = new DevExpress.XtraEditors.PanelControl();
            this.scGreen = new ProWrite.UI.Controls.Live.Sessions.SignConfigControl();
            this.lblGreenTitle = new DevExpress.XtraEditors.LabelControl();
            this.chkAlert = new DevExpress.XtraEditors.CheckEdit();
            ((System.ComponentModel.ISupportInitialize)(this.pnlSessionName)).BeginInit();
            this.pnlSessionName.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenter)).BeginInit();
            this.pnlCenter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).BeginInit();
            this.panelControl2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterAlert)).BeginInit();
            this.pnlCenterAlert.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertRed)).BeginInit();
            this.pnlCenterALertRed.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertYellow)).BeginInit();
            this.pnlCenterALertYellow.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertGreen)).BeginInit();
            this.pnlCenterALertGreen.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblSessionName
            // 
            this.lblSessionName.Location = new System.Drawing.Point(12, 12);
            this.lblSessionName.Name = "lblSessionName";
            this.lblSessionName.Size = new System.Drawing.Size(70, 13);
            this.lblSessionName.TabIndex = 0;
            this.lblSessionName.Text = "Session Name:";
            // 
            // teSessionName
            // 
            this.teSessionName.EditValue = "*.Required";
            this.teSessionName.Location = new System.Drawing.Point(89, 9);
            this.teSessionName.Name = "teSessionName";
            this.teSessionName.TabIndex = 1;
            this.teSessionName.TextChanged += new System.EventHandler(this.teSessionName_TextChanged);
            // 
            // pnlSessionName
            // 
            this.pnlSessionName.Controls.Add(this.lblSessionName);
            this.pnlSessionName.Controls.Add(this.teSessionName);
            this.pnlSessionName.Location = new System.Drawing.Point(3, 4);
            this.pnlSessionName.Name = "pnlSessionName";
            this.pnlSessionName.Size = new System.Drawing.Size(196, 39);
            this.pnlSessionName.TabIndex = 2;
            // 
            // pnlCenter
            // 
            this.pnlCenter.Controls.Add(this.sbtnDeleteSession);
            this.pnlCenter.Controls.Add(this.panelControl2);
            this.pnlCenter.Controls.Add(this.panelControl1);
            this.pnlCenter.Controls.Add(this.pnlCenterAlert);
            this.pnlCenter.Controls.Add(this.chkAlert);
            this.pnlCenter.Location = new System.Drawing.Point(3, 48);
            this.pnlCenter.Name = "pnlCenter";
            this.pnlCenter.Size = new System.Drawing.Size(594, 482);
            this.pnlCenter.TabIndex = 3;
            this.pnlCenter.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlCenter_Paint);
            // 
            // sbtnDeleteSession
            // 
            this.sbtnDeleteSession.Location = new System.Drawing.Point(450, 451);
            this.sbtnDeleteSession.Name = "sbtnDeleteSession";
            this.sbtnDeleteSession.Size = new System.Drawing.Size(136, 23);
            this.sbtnDeleteSession.TabIndex = 4;
            this.sbtnDeleteSession.Text = "Delete Current Session";
            this.sbtnDeleteSession.Click += new System.EventHandler(this.sbtnDeleteSession_Click);
            // 
            // panelControl2
            // 
            this.panelControl2.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.panelControl2.Appearance.Options.UseBackColor = true;
            this.panelControl2.Controls.Add(this.sbtnReport);
            this.panelControl2.Controls.Add(this.sbtnReset);
            this.panelControl2.Controls.Add(this.rgNail);
            this.panelControl2.Controls.Add(this.rgCounter);
            this.panelControl2.Controls.Add(this.mnMessage);
            this.panelControl2.Location = new System.Drawing.Point(8, 366);
            this.panelControl2.Name = "panelControl2";
            this.panelControl2.Size = new System.Drawing.Size(338, 108);
            this.panelControl2.TabIndex = 3;
            // 
            // sbtnReport
            // 
            this.sbtnReport.Location = new System.Drawing.Point(255, 39);
            this.sbtnReport.Name = "sbtnReport";
            this.sbtnReport.Size = new System.Drawing.Size(75, 23);
            this.sbtnReport.TabIndex = 4;
            this.sbtnReport.Text = "Run Report";
            // 
            // sbtnReset
            // 
            this.sbtnReset.Location = new System.Drawing.Point(255, 10);
            this.sbtnReset.Name = "sbtnReset";
            this.sbtnReset.Size = new System.Drawing.Size(75, 23);
            this.sbtnReset.TabIndex = 3;
            this.sbtnReset.Text = "Reset";
            // 
            // rgNail
            // 
            this.rgNail.Location = new System.Drawing.Point(153, 56);
            this.rgNail.Name = "rgNail";
            this.rgNail.Size = new System.Drawing.Size(76, 43);
            this.rgNail.TabIndex = 2;
            this.rgNail.SelectedIndexChanged += new System.EventHandler(this.rgNail_SelectedIndexChanged);
            // 
            // rgCounter
            // 
            this.rgCounter.Location = new System.Drawing.Point(153, 9);
            this.rgCounter.Name = "rgCounter";
            this.rgCounter.Size = new System.Drawing.Size(76, 43);
            this.rgCounter.TabIndex = 1;
            this.rgCounter.SelectedIndexChanged += new System.EventHandler(this.rgCounter_SelectedIndexChanged);
            // 
            // mnMessage
            // 
            this.mnMessage.BackColor = System.Drawing.Color.White;
            this.mnMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.mnMessage.Location = new System.Drawing.Point(5, 9);
            this.mnMessage.Name = "mnMessage";
            this.mnMessage.Size = new System.Drawing.Size(142, 90);
            this.mnMessage.TabIndex = 0;
            // 
            // panelControl1
            // 
            this.panelControl1.Controls.Add(this.lblAutoQueue);
            this.panelControl1.Controls.Add(this.seAutoQueueCounter);
            this.panelControl1.Location = new System.Drawing.Point(352, 32);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(234, 327);
            this.panelControl1.TabIndex = 2;
            // 
            // lblAutoQueue
            // 
            this.lblAutoQueue.Location = new System.Drawing.Point(59, 8);
            this.lblAutoQueue.Name = "lblAutoQueue";
            this.lblAutoQueue.Size = new System.Drawing.Size(171, 39);
            this.lblAutoQueue.TabIndex = 4;
            this.lblAutoQueue.Text = "Auto‐Queue will automatically add\r\ncontent to the lineup when the\r\nlineup list ge" +
                "ts below this setting.";
            // 
            // seAutoQueueCounter
            // 
            this.seAutoQueueCounter.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.seAutoQueueCounter.Location = new System.Drawing.Point(5, 9);
            this.seAutoQueueCounter.Name = "seAutoQueueCounter";
            this.seAutoQueueCounter.Size = new System.Drawing.Size(51, 20);
            this.seAutoQueueCounter.TabIndex = 3;
            this.seAutoQueueCounter.ValueChanged += new System.EventHandler(this.seAutoQueueCounter_ValueChanged);
            this.seAutoQueueCounter.EditValueChanging += new DevExpress.XtraEditors.Controls.ChangingEventHandler(this.SpinEdit_EditValueChanging);
            // 
            // pnlCenterAlert
            // 
            this.pnlCenterAlert.Controls.Add(this.pnlCenterALertRed);
            this.pnlCenterAlert.Controls.Add(this.pnlCenterALertYellow);
            this.pnlCenterAlert.Controls.Add(this.pnlCenterALertGreen);
            this.pnlCenterAlert.Location = new System.Drawing.Point(8, 32);
            this.pnlCenterAlert.Name = "pnlCenterAlert";
            this.pnlCenterAlert.Size = new System.Drawing.Size(338, 327);
            this.pnlCenterAlert.TabIndex = 1;
            // 
            // pnlCenterALertRed
            // 
            this.pnlCenterALertRed.Controls.Add(this.scRed);
            this.pnlCenterALertRed.Controls.Add(this.seRed);
            this.pnlCenterALertRed.Controls.Add(this.lblRed);
            this.pnlCenterALertRed.Location = new System.Drawing.Point(6, 218);
            this.pnlCenterALertRed.Name = "pnlCenterALertRed";
            this.pnlCenterALertRed.Size = new System.Drawing.Size(324, 100);
            this.pnlCenterALertRed.TabIndex = 2;
            // 
            // scRed
            // 
            this.scRed.BackColor = System.Drawing.Color.Red;
            this.scRed.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.scRed.IsSupportGlobalization = false;
            this.scRed.Location = new System.Drawing.Point(186, 5);
            this.scRed.Name = "scRed";
            this.scRed.Size = new System.Drawing.Size(127, 78);
            this.scRed.TabIndex = 4;
            // 
            // seRed
            // 
            this.seRed.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.seRed.Location = new System.Drawing.Point(5, 28);
            this.seRed.Name = "seRed";
            this.seRed.Size = new System.Drawing.Size(51, 20);
            this.seRed.TabIndex = 3;
            this.seRed.ValueChanged += new System.EventHandler(this.seRed_ValueChanged);
            this.seRed.EditValueChanging += new DevExpress.XtraEditors.Controls.ChangingEventHandler(this.SpinEdit_EditValueChanging);
            // 
            // lblRed
            // 
            this.lblRed.Location = new System.Drawing.Point(67, 7);
            this.lblRed.Name = "lblRed";
            this.lblRed.Size = new System.Drawing.Size(112, 65);
            this.lblRed.TabIndex = 2;
            this.lblRed.Text = "Red Threshold —\r\nMonitor turns red when\r\ntime remaining is equal\r\nto or below the" +
                " (≤) this\r\nsetting.";
            // 
            // pnlCenterALertYellow
            // 
            this.pnlCenterALertYellow.Controls.Add(this.scYello);
            this.pnlCenterALertYellow.Controls.Add(this.seYellow);
            this.pnlCenterALertYellow.Controls.Add(this.lblYellowTitle);
            this.pnlCenterALertYellow.Location = new System.Drawing.Point(6, 112);
            this.pnlCenterALertYellow.Name = "pnlCenterALertYellow";
            this.pnlCenterALertYellow.Size = new System.Drawing.Size(324, 100);
            this.pnlCenterALertYellow.TabIndex = 1;
            // 
            // scYello
            // 
            this.scYello.BackColor = System.Drawing.Color.Yellow;
            this.scYello.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.scYello.IsSupportGlobalization = false;
            this.scYello.Location = new System.Drawing.Point(186, 5);
            this.scYello.Name = "scYello";
            this.scYello.Size = new System.Drawing.Size(127, 78);
            this.scYello.TabIndex = 2;
            // 
            // seYellow
            // 
            this.seYellow.EditValue = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.seYellow.Location = new System.Drawing.Point(5, 30);
            this.seYellow.Name = "seYellow";
            this.seYellow.Size = new System.Drawing.Size(51, 20);
            this.seYellow.TabIndex = 2;
            this.seYellow.Properties.MaxValue = 65535;
            this.seYellow.Properties.MinValue = 0;
            this.seYellow.ValueChanged += new System.EventHandler(this.seYellow_ValueChanged);
            this.seYellow.EditValueChanging += new DevExpress.XtraEditors.Controls.ChangingEventHandler(this.SpinEdit_EditValueChanging);
            // 
            // lblYellowTitle
            // 
            this.lblYellowTitle.Location = new System.Drawing.Point(67, 8);
            this.lblYellowTitle.Name = "lblYellowTitle";
            this.lblYellowTitle.Size = new System.Drawing.Size(108, 65);
            this.lblYellowTitle.TabIndex = 1;
            this.lblYellowTitle.Text = "Yellow Threshold —\r\nmonitor turns yellow\r\nwhen time remaining is\r\nequal to or bel" +
                "ow (≤)\r\nthis setting.";
            // 
            // pnlCenterALertGreen
            // 
            this.pnlCenterALertGreen.Controls.Add(this.scGreen);
            this.pnlCenterALertGreen.Controls.Add(this.lblGreenTitle);
            this.pnlCenterALertGreen.Location = new System.Drawing.Point(6, 6);
            this.pnlCenterALertGreen.Name = "pnlCenterALertGreen";
            this.pnlCenterALertGreen.Size = new System.Drawing.Size(324, 100);
            this.pnlCenterALertGreen.TabIndex = 0;
            // 
            // scGreen
            // 
            this.scGreen.BackColor = System.Drawing.Color.Green;
            this.scGreen.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.scGreen.IsSupportGlobalization = false;
            this.scGreen.Location = new System.Drawing.Point(186, 6);
            this.scGreen.Name = "scGreen";
            this.scGreen.Size = new System.Drawing.Size(127, 78);
            this.scGreen.TabIndex = 1;
            // 
            // lblGreenTitle
            // 
            this.lblGreenTitle.Location = new System.Drawing.Point(67, 7);
            this.lblGreenTitle.Name = "lblGreenTitle";
            this.lblGreenTitle.Size = new System.Drawing.Size(117, 52);
            this.lblGreenTitle.TabIndex = 0;
            this.lblGreenTitle.Text = "Green Threshold —\r\nmonitor turns green\r\nwhen time remaining is\r\nabove Yellow Thre" +
                "shold.";
            // 
            // chkAlert
            // 
            this.chkAlert.Location = new System.Drawing.Point(8, 8);
            this.chkAlert.Name = "chkAlert";
            this.chkAlert.Size = new System.Drawing.Size(194, 19);
            this.chkAlert.TabIndex = 0;
            this.chkAlert.CheckedChanged += new System.EventHandler(this.chkAlert_CheckedChanged);
            // 
            // GeneralControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pnlCenter);
            this.Controls.Add(this.pnlSessionName);
            this.Name = "GeneralControl";
            this.Size = new System.Drawing.Size(600, 535);
            ((System.ComponentModel.ISupportInitialize)(this.pnlSessionName)).EndInit();
            this.pnlSessionName.ResumeLayout(false);
            this.pnlSessionName.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenter)).EndInit();
            this.pnlCenter.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).EndInit();
            this.panelControl2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            this.panelControl1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterAlert)).EndInit();
            this.pnlCenterAlert.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertRed)).EndInit();
            this.pnlCenterALertRed.ResumeLayout(false);
            this.pnlCenterALertRed.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertYellow)).EndInit();
            this.pnlCenterALertYellow.ResumeLayout(false);
            this.pnlCenterALertYellow.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlCenterALertGreen)).EndInit();
            this.pnlCenterALertGreen.ResumeLayout(false);
            this.pnlCenterALertGreen.PerformLayout();
            this.ResumeLayout(false);

        }



        #endregion

        private DevExpress.XtraEditors.LabelControl lblSessionName;
        private DevExpress.XtraEditors.TextEdit teSessionName;
        private DevExpress.XtraEditors.PanelControl pnlSessionName;
        private DevExpress.XtraEditors.PanelControl pnlCenter;
        private DevExpress.XtraEditors.CheckEdit chkAlert;
        private DevExpress.XtraEditors.PanelControl pnlCenterAlert;
        private DevExpress.XtraEditors.PanelControl pnlCenterALertRed;
        private DevExpress.XtraEditors.PanelControl pnlCenterALertYellow;
        private DevExpress.XtraEditors.PanelControl pnlCenterALertGreen;
        private DevExpress.XtraEditors.LabelControl lblRed;
        private DevExpress.XtraEditors.LabelControl lblYellowTitle;
        private DevExpress.XtraEditors.LabelControl lblGreenTitle;
        private DevExpress.XtraEditors.SpinEdit seRed;
        private DevExpress.XtraEditors.SpinEdit seYellow;
        private SignConfigControl scGreen;
        private SignConfigControl scRed;
        private SignConfigControl scYello;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.LabelControl lblAutoQueue;
        private DevExpress.XtraEditors.SpinEdit seAutoQueueCounter;
        private DevExpress.XtraEditors.PanelControl panelControl2;
        private MessageNailControl mnMessage;
        private DevExpress.XtraEditors.RadioGroup rgCounter;
        private DevExpress.XtraEditors.SimpleButton sbtnReport;
        private DevExpress.XtraEditors.SimpleButton sbtnReset;
        private DevExpress.XtraEditors.RadioGroup rgNail;
        private DevExpress.XtraEditors.SimpleButton sbtnDeleteSession;
    }
}
