namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class SessionSetupControl
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
            this.btnNew = new DevExpress.XtraEditors.SimpleButton();
            this.btnLoad = new DevExpress.XtraEditors.SimpleButton();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.tabSession = new DevExpress.XtraTab.XtraTabControl();
            this.tabpageGenal = new DevExpress.XtraTab.XtraTabPage();
            this.sessionGeneralControl1 = new ProWrite.UI.Controls.Live.Sessions.GeneralControl();
            this.tabpageSign = new DevExpress.XtraTab.XtraTabPage();
            this.signList1 = new ProWrite.UI.Controls.Live.Sessions.SignDashboardListToSessionList();
            this.tabpageCategories = new DevExpress.XtraTab.XtraTabPage();
            this.categoryControl1 = new ProWrite.UI.Controls.Live.Sessions.CategoryControl();
            this.tabpageHotButton = new DevExpress.XtraTab.XtraTabPage();
            this.hotButtonControl1 = new ProWrite.UI.Controls.Live.Sessions.HotButtonControl();
            ((System.ComponentModel.ISupportInitialize)(this.tabSession)).BeginInit();
            this.tabSession.SuspendLayout();
            this.tabpageGenal.SuspendLayout();
            this.tabpageSign.SuspendLayout();
            this.tabpageCategories.SuspendLayout();
            this.tabpageHotButton.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnNew
            // 
            this.btnNew.Location = new System.Drawing.Point(1, 3);
            this.btnNew.Name = "btnNew";
            this.btnNew.Size = new System.Drawing.Size(75, 23);
            this.btnNew.TabIndex = 0;
            this.btnNew.Text = "&New";
            this.btnNew.Click += new System.EventHandler(this.btnNew_Click);
            // 
            // btnLoad
            // 
            this.btnLoad.Location = new System.Drawing.Point(82, 3);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(75, 23);
            this.btnLoad.TabIndex = 1;
            this.btnLoad.Text = "&Load";
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(163, 3);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 2;
            this.btnSave.Text = "&Save";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // tabSession
            // 
            this.tabSession.Location = new System.Drawing.Point(1, 32);
            this.tabSession.Name = "tabSession";
            this.tabSession.SelectedTabPage = this.tabpageGenal;
            this.tabSession.Size = new System.Drawing.Size(611, 566);
            this.tabSession.TabIndex = 6;
            this.tabSession.TabPages.AddRange(new DevExpress.XtraTab.XtraTabPage[] {
            this.tabpageGenal,
            this.tabpageSign,
            this.tabpageCategories,
            this.tabpageHotButton});
            this.tabSession.SelectedPageChanged += new DevExpress.XtraTab.TabPageChangedEventHandler(tabSession_SelectedPageChanged);
            // 
            // tabpageGenal
            // 
            this.tabpageGenal.Controls.Add(this.sessionGeneralControl1);
            this.tabpageGenal.Name = "tabpageGenal";
            this.tabpageGenal.Size = new System.Drawing.Size(602, 535);
            this.tabpageGenal.Text = "General";
            // 
            // sessionGeneralControl1
            // 
            this.sessionGeneralControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.sessionGeneralControl1.IsSupportGlobalization = false;
            this.sessionGeneralControl1.Location = new System.Drawing.Point(0, 0);
            this.sessionGeneralControl1.Model = null;
            this.sessionGeneralControl1.Name = "sessionGeneralControl1";
            this.sessionGeneralControl1.Size = new System.Drawing.Size(602, 535);
            this.sessionGeneralControl1.TabIndex = 0;
            // 
            // tabpageSign
            // 
            this.tabpageSign.Controls.Add(this.signList1);
            this.tabpageSign.Name = "tabpageSign";
            this.tabpageSign.Size = new System.Drawing.Size(602, 535);
            this.tabpageSign.Text = "Sign";
            // 
            // signList1
            // 
            this.signList1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.signList1.Location = new System.Drawing.Point(0, 0);
            this.signList1.Name = "signList1";
            this.signList1.Size = new System.Drawing.Size(602, 535);
            this.signList1.TabIndex = 0;
            // 
            // tabpageCategories
            // 
            this.tabpageCategories.Controls.Add(this.categoryControl1);
            this.tabpageCategories.Name = "tabpageCategories";
            this.tabpageCategories.Size = new System.Drawing.Size(602, 535);
            this.tabpageCategories.Text = "Categories";
            // 
            // categoryControl1
            // 
            this.categoryControl1.Location = new System.Drawing.Point(3, 14);
            this.categoryControl1.Name = "categoryControl1";
            this.categoryControl1.Size = new System.Drawing.Size(596, 507);
            this.categoryControl1.TabIndex = 0;
            // 
            // tabpageHotButton
            // 
            this.tabpageHotButton.Controls.Add(this.hotButtonControl1);
            this.tabpageHotButton.Name = "tabpageHotButton";
            this.tabpageHotButton.Size = new System.Drawing.Size(602, 535);
            this.tabpageHotButton.Text = "Hot Button";
            // 
            // hotButtonControl1
            // 
            this.hotButtonControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.hotButtonControl1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.hotButtonControl1.Location = new System.Drawing.Point(9, 12);
            this.hotButtonControl1.Name = "hotButtonControl1";
            this.hotButtonControl1.Size = new System.Drawing.Size(473, 312);
            this.hotButtonControl1.TabIndex = 0;
            // 
            // SessionSetupControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabSession);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnLoad);
            this.Controls.Add(this.btnNew);
            this.Name = "SessionSetupControl";
            this.Size = new System.Drawing.Size(612, 597);
            ((System.ComponentModel.ISupportInitialize)(this.tabSession)).EndInit();
            this.tabSession.ResumeLayout(false);
            this.tabpageGenal.ResumeLayout(false);
            this.tabpageSign.ResumeLayout(false);
            this.tabpageCategories.ResumeLayout(false);
            this.tabpageHotButton.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton btnNew;
        private DevExpress.XtraEditors.SimpleButton btnLoad;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private DevExpress.XtraTab.XtraTabControl tabSession;
        private DevExpress.XtraTab.XtraTabPage tabpageGenal;
        private DevExpress.XtraTab.XtraTabPage tabpageSign;
        private DevExpress.XtraTab.XtraTabPage tabpageCategories;
        private GeneralControl sessionGeneralControl1;
        private SignDashboardListToSessionList signList1;
        private CategoryControl categoryControl1;
        private DevExpress.XtraTab.XtraTabPage tabpageHotButton;
        private HotButtonControl hotButtonControl1;
    }
}
