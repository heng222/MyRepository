namespace ProWrite.UI.Controls.Dashboard
{
    partial class ConnectTcpIpForm
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
            this.grpLogin = new DevExpress.XtraEditors.GroupControl();
            this.lblState = new System.Windows.Forms.Label();
            this.chkStoreUserIfo = new DevExpress.XtraEditors.CheckEdit();
            this.chkAutoLogin = new DevExpress.XtraEditors.CheckEdit();
            this.btnLoginCancel = new DevExpress.XtraEditors.SimpleButton();
            this.timer = new System.Windows.Forms.Timer();
            this.btnLogin = new DevExpress.XtraEditors.SimpleButton();
            this.label7 = new System.Windows.Forms.Label();
            this.txtPasswordLogin = new DevExpress.XtraEditors.TextEdit();
            this.label8 = new System.Windows.Forms.Label();
            this.txtUserNameLogin = new DevExpress.XtraEditors.TextEdit();
            this.grpConnect = new DevExpress.XtraEditors.GroupControl();
            this.panProxy = new DevExpress.XtraEditors.PanelControl();
            this.ddlProxyType = new DevExpress.XtraEditors.ComboBoxEdit();
            this.label12 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtProxyUserName = new DevExpress.XtraEditors.TextEdit();
            this.label9 = new System.Windows.Forms.Label();
            this.txtProxyIpAddress = new DevExpress.XtraEditors.TextEdit();
            this.txtProxyPassword = new DevExpress.XtraEditors.TextEdit();
            this.txtProxyPortNumber = new DevExpress.XtraEditors.TextEdit();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.btnTestProxy = new DevExpress.XtraEditors.SimpleButton();
            this.label4 = new System.Windows.Forms.Label();
            this.txtConnectionUserName = new DevExpress.XtraEditors.TextEdit();
            this.chkStoreSignPWD = new DevExpress.XtraEditors.CheckEdit();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.btnUseProxy = new DevExpress.XtraEditors.SimpleButton();
            this.btnConnect = new DevExpress.XtraEditors.SimpleButton();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtPortNumber = new DevExpress.XtraEditors.TextEdit();
            this.txtConnectionPassword = new DevExpress.XtraEditors.TextEdit();
            this.txtIpAddress = new DevExpress.XtraEditors.TextEdit();
            ((System.ComponentModel.ISupportInitialize)(this.grpLogin)).BeginInit();
            this.grpLogin.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chkStoreUserIfo.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkAutoLogin.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPasswordLogin.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtUserNameLogin.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grpConnect)).BeginInit();
            this.grpConnect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panProxy)).BeginInit();
            this.panProxy.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlProxyType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyUserName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyIpAddress.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPassword.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPortNumber.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectionUserName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkStoreSignPWD.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPortNumber.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectionPassword.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtIpAddress.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // grpLogin
            // 
            this.grpLogin.Controls.Add(this.lblState);
            this.grpLogin.Controls.Add(this.chkStoreUserIfo);
            this.grpLogin.Controls.Add(this.chkAutoLogin);
            this.grpLogin.Controls.Add(this.btnLoginCancel);
            this.grpLogin.Controls.Add(this.btnLogin);
            this.grpLogin.Controls.Add(this.label7);
            this.grpLogin.Controls.Add(this.txtPasswordLogin);
            this.grpLogin.Controls.Add(this.label8);
            this.grpLogin.Controls.Add(this.txtUserNameLogin);
            this.grpLogin.Dock = System.Windows.Forms.DockStyle.Top;
            this.grpLogin.Location = new System.Drawing.Point(0, 0);
            this.grpLogin.Name = "grpLogin";
            this.grpLogin.Size = new System.Drawing.Size(440, 170);
            //this.grpLogin.m
            this.grpLogin.TabIndex = 17;
            this.grpLogin.Text = "";
            this.grpLogin.ShowCaption = false;
            // 
            // lblState
            // 
            this.lblState.AutoSize = true;
            this.lblState.Location = new System.Drawing.Point(22, 95);
            this.lblState.Name = "lblState";
            this.lblState.Size = new System.Drawing.Size(0, 13);
            this.lblState.TabIndex = 21;
            // 
            // chkStoreUserIfo
            // 
            this.chkStoreUserIfo.Location = new System.Drawing.Point(290, 54);
            this.chkStoreUserIfo.Name = "chkStoreUserIfo";
            this.chkStoreUserIfo.Properties.Caption = "Store User Information";
            this.chkStoreUserIfo.Size = new System.Drawing.Size(146, 19);
            this.chkStoreUserIfo.TabIndex = 19;
            this.chkStoreUserIfo.CheckedChanged += new System.EventHandler(chkStoreUserIfo_CheckedChanged);
            // 
            // chkAutoLogin
            // 
            this.chkAutoLogin.Location = new System.Drawing.Point(290, 20);
            this.chkAutoLogin.Name = "chkAutoLogin";
            this.chkAutoLogin.Properties.Caption = "Automatically login";
            this.chkAutoLogin.Size = new System.Drawing.Size(120, 19);
            this.chkAutoLogin.TabIndex = 18;
            this.chkAutoLogin.CheckedChanged += new System.EventHandler(chkAutoLogin_CheckedChanged);
            // 
            // btnLoginCancel
            // 
            this.btnLoginCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnLoginCancel.Location = new System.Drawing.Point(347, 95);
            this.btnLoginCancel.Name = "btnLoginCancel";
            this.btnLoginCancel.Size = new System.Drawing.Size(53, 22);
            this.btnLoginCancel.TabIndex = 16;
            this.btnLoginCancel.Text = "Cancel";
            this.btnLoginCancel.Click += new System.EventHandler(this.btnLoginCancel_Click);
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(270, 95);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(51, 22);
            this.btnLogin.TabIndex = 15;
            this.btnLogin.Text = "Login";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(17, 57);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(50, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Password:";
            // 
            // txtPasswordLogin
            // 
            this.txtPasswordLogin.Location = new System.Drawing.Point(92, 54);
            this.txtPasswordLogin.Name = "txtPasswordLogin";
            this.txtPasswordLogin.Properties.PasswordChar = '*';
            this.txtPasswordLogin.Size = new System.Drawing.Size(181, 20);
            this.txtPasswordLogin.TabIndex = 13;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(17, 22);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(50, 13);
            this.label8.TabIndex = 13;
            this.label8.Text = "User Name:";
            // 
            // txtUserNameLogin
            // 
            this.txtUserNameLogin.Location = new System.Drawing.Point(92, 19);
            this.txtUserNameLogin.Name = "txtUserNameLogin";
            this.txtUserNameLogin.Size = new System.Drawing.Size(181, 20);
            this.txtUserNameLogin.TabIndex = 12;
            // 
            // grpConnect
            // 
            this.grpConnect.Controls.Add(this.panProxy);
            this.grpConnect.Controls.Add(this.label4);
            this.grpConnect.Controls.Add(this.txtConnectionUserName);
            this.grpConnect.Controls.Add(this.chkStoreSignPWD);
            this.grpConnect.Controls.Add(this.btnCancel);
            this.grpConnect.Controls.Add(this.btnUseProxy);
            this.grpConnect.Controls.Add(this.btnConnect);
            this.grpConnect.Controls.Add(this.label3);
            this.grpConnect.Controls.Add(this.label2);
            this.grpConnect.Controls.Add(this.label1);
            this.grpConnect.Controls.Add(this.txtPortNumber);
            this.grpConnect.Controls.Add(this.txtConnectionPassword);
            this.grpConnect.Controls.Add(this.txtIpAddress);
            this.grpConnect.Location = new System.Drawing.Point(0, 169);
            this.grpConnect.Name = "grpConnect";
            this.grpConnect.Size = new System.Drawing.Size(440, 313);
            this.grpConnect.TabIndex = 16;
            this.grpConnect.Text = "Connection Info";
            // 
            // panProxy
            // 
            this.panProxy.Controls.Add(this.ddlProxyType);
            this.panProxy.Controls.Add(this.label12);
            this.panProxy.Controls.Add(this.label6);
            this.panProxy.Controls.Add(this.txtProxyUserName);
            this.panProxy.Controls.Add(this.label9);
            this.panProxy.Controls.Add(this.txtProxyIpAddress);
            this.panProxy.Controls.Add(this.txtProxyPassword);
            this.panProxy.Controls.Add(this.txtProxyPortNumber);
            this.panProxy.Controls.Add(this.label10);
            this.panProxy.Controls.Add(this.label11);
            this.panProxy.Controls.Add(this.btnTestProxy);
            this.panProxy.Location = new System.Drawing.Point(36, 169);
            this.panProxy.Name = "panProxy";
            this.panProxy.Size = new System.Drawing.Size(366, 138);
            this.panProxy.TabIndex = 20;
            this.panProxy.Visible = false;
            // 
            // ddlProxyType
            // 
            this.ddlProxyType.Location = new System.Drawing.Point(75, 5);
            this.ddlProxyType.Name = "ddlProxyType";
            this.ddlProxyType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlProxyType.Properties.Items.AddRange(new object[] {
            "Http Proxy",
            "Socks5 Proxy"});
            this.ddlProxyType.Size = new System.Drawing.Size(102, 20);
            this.ddlProxyType.TabIndex = 7;
            this.ddlProxyType.SelectedIndexChanged += new System.EventHandler(this.ddlProxyType_SelectedIndexChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(2, 78);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(63, 13);
            this.label12.TabIndex = 19;
            this.label12.Text = "User Name:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(2, 8);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(63, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "Proxy Type:";
            // 
            // txtProxyUserName
            // 
            this.txtProxyUserName.Location = new System.Drawing.Point(74, 75);
            this.txtProxyUserName.Name = "txtProxyUserName";
            this.txtProxyUserName.Size = new System.Drawing.Size(103, 20);
            this.txtProxyUserName.TabIndex = 10;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(5, 43);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(60, 13);
            this.label9.TabIndex = 13;
            this.label9.Text = "Ip Address:";
            // 
            // txtProxyIpAddress
            // 
            this.txtProxyIpAddress.Location = new System.Drawing.Point(74, 40);
            this.txtProxyIpAddress.Name = "txtProxyIpAddress";
            this.txtProxyIpAddress.Size = new System.Drawing.Size(103, 20);
            this.txtProxyIpAddress.TabIndex = 8;
            this.txtProxyIpAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtIpAddressUser_KeyPress);
            // 
            // txtProxyPassword
            // 
            this.txtProxyPassword.Location = new System.Drawing.Point(258, 75);
            this.txtProxyPassword.Name = "txtProxyPassword";
            this.txtProxyPassword.Properties.PasswordChar = '*';
            this.txtProxyPassword.Size = new System.Drawing.Size(98, 20);
            this.txtProxyPassword.TabIndex = 11;
            // 
            // txtProxyPortNumber
            // 
            this.txtProxyPortNumber.Location = new System.Drawing.Point(258, 40);
            this.txtProxyPortNumber.Name = "txtProxyPortNumber";
            this.txtProxyPortNumber.Properties.EditFormat.FormatString = "@\'^0|[0-9]*[1-9][0-9]*$\'";
            this.txtProxyPortNumber.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.txtProxyPortNumber.Size = new System.Drawing.Size(98, 20);
            this.txtProxyPortNumber.TabIndex = 9;
            this.txtProxyPortNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtPortNumber_KeyPress);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(196, 78);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 13);
            this.label10.TabIndex = 13;
            this.label10.Text = "Password:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(183, 43);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(69, 13);
            this.label11.TabIndex = 13;
            this.label11.Text = "Port Number:";
            // 
            // btnTestProxy
            // 
            this.btnTestProxy.Enabled = false;
            this.btnTestProxy.Location = new System.Drawing.Point(256, 108);
            this.btnTestProxy.Name = "btnTestProxy";
            this.btnTestProxy.Size = new System.Drawing.Size(51, 22);
            this.btnTestProxy.TabIndex = 5;
            this.btnTestProxy.Text = "Test";
            this.btnTestProxy.Click += new System.EventHandler(this.btnTestProxy_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(2, 65);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = "CXC LogName:";
            // 
            // txtConnectionUserName
            // 
            this.txtConnectionUserName.Location = new System.Drawing.Point(82, 62);
            this.txtConnectionUserName.Name = "txtConnectionUserName";
            this.txtConnectionUserName.Size = new System.Drawing.Size(137, 20);
            this.txtConnectionUserName.TabIndex = 2;
            // 
            // chkStoreSignPWD
            // 
            this.chkStoreSignPWD.Location = new System.Drawing.Point(205, 126);
            this.chkStoreSignPWD.Name = "chkStoreSignPWD";
            this.chkStoreSignPWD.Properties.Caption = "Store Sign Password";
            this.chkStoreSignPWD.Size = new System.Drawing.Size(132, 19);
            this.chkStoreSignPWD.TabIndex = 17;
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(288, 151);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(53, 22);
            this.btnCancel.TabIndex = 6;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Visible = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnUseProxy
            // 
            this.btnUseProxy.Location = new System.Drawing.Point(343, 123);
            this.btnUseProxy.Name = "btnUseProxy";
            this.btnUseProxy.Size = new System.Drawing.Size(73, 22);
            this.btnUseProxy.TabIndex = 4;
            this.btnUseProxy.Text = "Use Proxy";
            this.btnUseProxy.Click += new System.EventHandler(this.btnUseProxy_Click);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(215, 151);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(51, 22);
            this.btnConnect.TabIndex = 5;
            this.btnConnect.Text = "Connect";
            this.btnConnect.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(222, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Port Number:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(235, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 13;
            this.label2.Text = "Password:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "Ip Address:";
            // 
            // txtPortNumber
            // 
            this.txtPortNumber.Location = new System.Drawing.Point(298, 27);
            this.txtPortNumber.Name = "txtPortNumber";
            this.txtPortNumber.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.txtPortNumber.Size = new System.Drawing.Size(118, 20);
            this.txtPortNumber.TabIndex = 1;
            this.txtPortNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtPortNumber_KeyPress);
            // 
            // txtConnectionPassword
            // 
            this.txtConnectionPassword.Location = new System.Drawing.Point(298, 62);
            this.txtConnectionPassword.Name = "txtConnectionPassword";
            this.txtConnectionPassword.Properties.PasswordChar = '*';
            this.txtConnectionPassword.Size = new System.Drawing.Size(118, 20);
            this.txtConnectionPassword.TabIndex = 3;
            // 
            // txtIpAddress
            // 
            this.txtIpAddress.Location = new System.Drawing.Point(82, 23);
            this.txtIpAddress.Name = "txtIpAddress";
            this.txtIpAddress.Size = new System.Drawing.Size(135, 20);
            this.txtIpAddress.TabIndex = 0;
            this.txtIpAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtIpAddressUser_KeyPress);
            // 
            // ConnectTcpIpForm
            // 
            this.AcceptButton = this.btnLogin;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(430, 481);
            this.Controls.Add(this.grpLogin);
            this.Controls.Add(this.grpConnect);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ConnectTcpIpForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "User Login";
            this.ShowIcon = false;
            ((System.ComponentModel.ISupportInitialize)(this.grpLogin)).EndInit();
            this.grpLogin.ResumeLayout(false);
            this.grpLogin.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chkStoreUserIfo.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkAutoLogin.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPasswordLogin.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtUserNameLogin.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grpConnect)).EndInit();
            this.grpConnect.ResumeLayout(false);
            this.grpConnect.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panProxy)).EndInit();
            this.panProxy.ResumeLayout(false);
            this.panProxy.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlProxyType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyUserName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyIpAddress.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPassword.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPortNumber.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectionUserName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.chkStoreSignPWD.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPortNumber.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectionPassword.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtIpAddress.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.GroupControl grpLogin;
        private DevExpress.XtraEditors.SimpleButton btnLoginCancel;
        private DevExpress.XtraEditors.SimpleButton btnLogin;
        private System.Windows.Forms.Label label7;
        private DevExpress.XtraEditors.TextEdit txtPasswordLogin;
        private System.Windows.Forms.Label label8;
        private DevExpress.XtraEditors.TextEdit txtUserNameLogin;
        private DevExpress.XtraEditors.GroupControl grpConnect;
        private DevExpress.XtraEditors.CheckEdit chkStoreSignPWD;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SimpleButton btnConnect;
        private DevExpress.XtraEditors.SimpleButton btnTestProxy;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private DevExpress.XtraEditors.TextEdit txtPortNumber;
        private DevExpress.XtraEditors.TextEdit txtConnectionPassword;
        private DevExpress.XtraEditors.TextEdit txtIpAddress;
        private System.Windows.Forms.Label label4;
        private DevExpress.XtraEditors.TextEdit txtConnectionUserName;
        private DevExpress.XtraEditors.PanelControl panProxy;
        private DevExpress.XtraEditors.ComboBoxEdit ddlProxyType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label12;
        private DevExpress.XtraEditors.TextEdit txtProxyUserName;
        private System.Windows.Forms.Label label9;
        private DevExpress.XtraEditors.TextEdit txtProxyIpAddress;
        private DevExpress.XtraEditors.TextEdit txtProxyPassword;
        private DevExpress.XtraEditors.TextEdit txtProxyPortNumber;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private DevExpress.XtraEditors.SimpleButton btnUseProxy;
        private DevExpress.XtraEditors.CheckEdit chkStoreUserIfo;
        private DevExpress.XtraEditors.CheckEdit chkAutoLogin;
        private System.Windows.Forms.Label lblState;
        private System.Windows.Forms.Timer timer;
    }
}