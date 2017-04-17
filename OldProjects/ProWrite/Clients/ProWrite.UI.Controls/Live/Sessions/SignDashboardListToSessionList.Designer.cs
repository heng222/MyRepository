namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class SignDashboardListToSessionList
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
            this.lbcDashboard = new DevExpress.XtraEditors.ListBoxControl();
            this.btnAdd = new DevExpress.XtraEditors.SimpleButton();
            this.btnRemove = new DevExpress.XtraEditors.SimpleButton();
            this.lbcSession = new DevExpress.XtraEditors.ListBoxControl();
            this.grpDashboard = new DevExpress.XtraEditors.GroupControl();
            this.grpSession = new DevExpress.XtraEditors.GroupControl();
            this.btnDown = new DevExpress.XtraEditors.SimpleButton();
            this.btnUp = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.lbcDashboard)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lbcSession)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grpDashboard)).BeginInit();
            this.grpDashboard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.grpSession)).BeginInit();
            this.grpSession.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbcDashboard
            // 
            this.lbcDashboard.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lbcDashboard.Location = new System.Drawing.Point(2, 20);
            this.lbcDashboard.Name = "lbcDashboard";
            this.lbcDashboard.Size = new System.Drawing.Size(196, 205);
            this.lbcDashboard.TabIndex = 0;
            this.lbcDashboard.DoubleClick += new System.EventHandler(this.lbcDashboard_DoubleClick);
            this.lbcDashboard.SelectedIndexChanged += new System.EventHandler(this.lbcDashboard_SelectedIndexChanged);
            // 
            // btnAdd
            // 
            this.btnAdd.Enabled = false;
            this.btnAdd.Location = new System.Drawing.Point(226, 70);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(75, 23);
            this.btnAdd.TabIndex = 1;
            this.btnAdd.Text = "Add >>";
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnRemove
            // 
            this.btnRemove.Enabled = false;
            this.btnRemove.Location = new System.Drawing.Point(226, 128);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(75, 23);
            this.btnRemove.TabIndex = 2;
            this.btnRemove.Text = "<< Remove";
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // lbcSession
            // 
            this.lbcSession.Dock = System.Windows.Forms.DockStyle.Left;
            this.lbcSession.Location = new System.Drawing.Point(2, 20);
            this.lbcSession.Name = "lbcSession";
            this.lbcSession.Size = new System.Drawing.Size(178, 205);
            this.lbcSession.TabIndex = 3;
            this.lbcSession.DoubleClick += new System.EventHandler(this.lbcSession_DoubleClick);
            this.lbcSession.SelectedIndexChanged += new System.EventHandler(this.lbcSession_SelectedIndexChanged);
            // 
            // grpDashboard
            // 
            this.grpDashboard.AppearanceCaption.Options.UseTextOptions = true;
            this.grpDashboard.AppearanceCaption.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.grpDashboard.Controls.Add(this.lbcDashboard);
            this.grpDashboard.Location = new System.Drawing.Point(20, 16);
            this.grpDashboard.Name = "grpDashboard";
            this.grpDashboard.Size = new System.Drawing.Size(200, 227);
            this.grpDashboard.TabIndex = 4;
            this.grpDashboard.Text = "DASHBOARD LIST";
            // 
            // grpSession
            // 
            this.grpSession.AppearanceCaption.Options.UseTextOptions = true;
            this.grpSession.AppearanceCaption.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.grpSession.Controls.Add(this.btnDown);
            this.grpSession.Controls.Add(this.btnUp);
            this.grpSession.Controls.Add(this.lbcSession);
            this.grpSession.Location = new System.Drawing.Point(307, 16);
            this.grpSession.Name = "grpSession";
            this.grpSession.Size = new System.Drawing.Size(228, 227);
            this.grpSession.TabIndex = 4;
            this.grpSession.Text = "SESSION LIST";
            // 
            // btnDown
            // 
            this.btnDown.Enabled = false;
            this.btnDown.Location = new System.Drawing.Point(187, 95);
            this.btnDown.Name = "btnDown";
            this.btnDown.Size = new System.Drawing.Size(36, 23);
            this.btnDown.TabIndex = 4;
            this.btnDown.Text = "Dn";
            this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
            // 
            // btnUp
            // 
            this.btnUp.Enabled = false;
            this.btnUp.Location = new System.Drawing.Point(187, 54);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(36, 23);
            this.btnUp.TabIndex = 4;
            this.btnUp.Text = "Up";
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            // 
            // SignDashboardListToSessionList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.grpSession);
            this.Controls.Add(this.grpDashboard);
            this.Controls.Add(this.btnRemove);
            this.Controls.Add(this.btnAdd);
            this.Name = "SignDashboardListToSessionList";
            this.Size = new System.Drawing.Size(559, 268);
            ((System.ComponentModel.ISupportInitialize)(this.lbcDashboard)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lbcSession)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grpDashboard)).EndInit();
            this.grpDashboard.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.grpSession)).EndInit();
            this.grpSession.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.ListBoxControl lbcDashboard;
        private DevExpress.XtraEditors.SimpleButton btnAdd;
        private DevExpress.XtraEditors.SimpleButton btnRemove;
        private DevExpress.XtraEditors.ListBoxControl lbcSession;
        private DevExpress.XtraEditors.GroupControl grpDashboard;
        private DevExpress.XtraEditors.GroupControl grpSession;
        private DevExpress.XtraEditors.SimpleButton btnDown;
        private DevExpress.XtraEditors.SimpleButton btnUp;
    }
}
