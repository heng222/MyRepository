using SignInfo=ProWrite.Entity.Dashboard.SignInfo;

namespace ProWrite.UI.Controls.Dashboard
{
    partial class SignFormNew
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConnectionProgress));
            this.components = new System.ComponentModel.Container();

            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl4 = new DevExpress.XtraEditors.LabelControl();
            this.lblError = new DevExpress.XtraEditors.LabelControl();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.btnRetry = new DevExpress.XtraEditors.SimpleButton();
            this.picCommunication = new DevExpress.XtraEditors.PictureEdit();
            this.picNetWork = new DevExpress.XtraEditors.PictureEdit();
            this.picConnection = new DevExpress.XtraEditors.PictureEdit();
            this.picSuccess = new DevExpress.XtraEditors.PictureEdit();
            this.picError = new DevExpress.XtraEditors.PictureEdit();
            this.picProgerss = new DevExpress.XtraEditors.PictureEdit();
            ((System.ComponentModel.ISupportInitialize)(this.picCommunication.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picNetWork.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picConnection.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picSuccess.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picError.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picProgerss.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(67, 112);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(162, 13);
            this.labelControl1.TabIndex = 0;
            this.labelControl1.Text = "Established secure communication";
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(67, 172);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(131, 13);
            this.labelControl2.TabIndex = 1;
            this.labelControl2.Text = "Established sign connection";
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(67, 140);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(151, 13);
            this.labelControl3.TabIndex = 2;
            this.labelControl3.Text = "Established network connection";
            // 
            // labelControl4
            // 
            this.labelControl4.Location = new System.Drawing.Point(67, 202);
            this.labelControl4.Name = "labelControl4";
            this.labelControl4.Size = new System.Drawing.Size(108, 13);
            this.labelControl4.TabIndex = 3;
            this.labelControl4.Text = "Successfully logged on";
            // 
            // lblError
            // 
            this.lblError.Location = new System.Drawing.Point(67, 237);
            this.lblError.Name = "lblError";
            this.lblError.Size = new System.Drawing.Size(303, 13);
            this.lblError.TabIndex = 4;
            this.lblError.Text = "Unable to connect-connection timed out after multiple attempts";
            this.lblError.Visible = false;
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(295, 264);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 5;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnRetry
            // 
            this.btnRetry.Location = new System.Drawing.Point(202, 264);
            this.btnRetry.Name = "btnRetry";
            this.btnRetry.Size = new System.Drawing.Size(62, 23);
            this.btnRetry.TabIndex = 6;
            this.btnRetry.Text = "Retry";
            this.btnRetry.Click += new System.EventHandler(this.btnRetry_Click);
            // 
            // picCommunication
            // 
            this.picCommunication.EditValue = ((object)(resources.GetObject("picCommunication.EditValue")));
            this.picCommunication.Location = new System.Drawing.Point(28, 109);
            this.picCommunication.Name = "picCommunication";
            this.picCommunication.Properties.ReadOnly = true;
            this.picCommunication.Properties.ShowMenu = false;
            this.picCommunication.Size = new System.Drawing.Size(16, 16);
            this.picCommunication.TabIndex = 7;
            // 
            // picNetWork
            // 
            this.picNetWork.EditValue = ((object)(resources.GetObject("picNetWork.EditValue")));
            this.picNetWork.Location = new System.Drawing.Point(28, 139);
            this.picNetWork.Name = "picNetWork";
            this.picNetWork.Properties.ReadOnly = true;
            this.picNetWork.Properties.ShowMenu = false;
            this.picNetWork.Size = new System.Drawing.Size(16, 16);
            this.picNetWork.TabIndex = 8;
            // 
            // picConnection
            // 
            this.picConnection.EditValue = ((object)(resources.GetObject("picConnection.EditValue")));
            this.picConnection.Location = new System.Drawing.Point(28, 169);
            this.picConnection.Name = "picConnection";
            this.picConnection.Properties.ReadOnly = true;
            this.picConnection.Properties.ShowMenu = false;
            this.picConnection.Size = new System.Drawing.Size(16, 16);
            this.picConnection.TabIndex = 9;
            // 
            // picSuccess
            // 
            this.picSuccess.EditValue = ((object)(resources.GetObject("picSuccess.EditValue")));
            this.picSuccess.Location = new System.Drawing.Point(28, 201);
            this.picSuccess.Name = "picSuccess";
            this.picSuccess.Properties.ReadOnly = true;
            this.picSuccess.Properties.ShowMenu = false;
            this.picSuccess.Size = new System.Drawing.Size(16, 16);
            this.picSuccess.TabIndex = 10;
            this.picSuccess.ImageChanged += new System.EventHandler(this.picSuccess_ImageChanged);
            // 
            // picError
            // 
            this.picError.EditValue = ((object)(resources.GetObject("picError.EditValue")));
            this.picError.Location = new System.Drawing.Point(23, 223);
            this.picError.Name = "picError";
            this.picError.Properties.ReadOnly = true;
            this.picError.Properties.ShowMenu = false;
            this.picError.Size = new System.Drawing.Size(32, 32);
            this.picError.TabIndex = 11;
            this.picError.Visible = false;
            // 
            // picProgerss
            // 
            this.picProgerss.EditValue = ((object)(resources.GetObject("picProgerss.EditValue")));
            this.picProgerss.Location = new System.Drawing.Point(23, 12);
            this.picProgerss.Name = "picProgerss";
            this.picProgerss.Properties.ReadOnly = true;
            this.picProgerss.Properties.ShowMenu = false;
            this.picProgerss.Size = new System.Drawing.Size(347, 79);
            this.picProgerss.TabIndex = 12;


            // 
            // SignFormNew
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(387, 299);
            this.Controls.Add(this.picProgerss);
            this.Controls.Add(this.picError);
            this.Controls.Add(this.picSuccess);
            this.Controls.Add(this.picConnection);
            this.Controls.Add(this.picNetWork);
            this.Controls.Add(this.picCommunication);
            this.Controls.Add(this.btnRetry);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.lblError);
            this.Controls.Add(this.labelControl4);
            this.Controls.Add(this.labelControl3);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.labelControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "SignFormNew";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Connecting";
            ((System.ComponentModel.ISupportInitialize)(this.picCommunication.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picNetWork.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picConnection.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picSuccess.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picError.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picProgerss.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraEditors.LabelControl labelControl4;
        private DevExpress.XtraEditors.LabelControl lblError;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SimpleButton btnRetry;
        private DevExpress.XtraEditors.PictureEdit picCommunication;
        private DevExpress.XtraEditors.PictureEdit picNetWork;
        private DevExpress.XtraEditors.PictureEdit picConnection;
        private DevExpress.XtraEditors.PictureEdit picSuccess;
        private DevExpress.XtraEditors.PictureEdit picError;
        private DevExpress.XtraEditors.PictureEdit picProgerss;
    }
}