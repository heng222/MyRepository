using SignInfo=ProWrite.Entity.Dashboard.SignInfo;

namespace ProWrite.UI.Controls.Dashboard
{
    partial class SignForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SignForm));
            this.signPanel = new DevExpress.XtraEditors.PanelControl();
            this.rdbDemoSign = new System.Windows.Forms.RadioButton();
            this.rdbLiveSign = new System.Windows.Forms.RadioButton();
            this.rdbWebCam = new System.Windows.Forms.RadioButton();
            this.rdbPhotograph = new System.Windows.Forms.RadioButton();
            this.rdbTcpIp = new System.Windows.Forms.RadioButton();
            this.rdbModem= new System.Windows.Forms.RadioButton();
            this.rdbSerial= new System.Windows.Forms.RadioButton();
            this.lblParentGroup = new System.Windows.Forms.Label();
            this.ddlSignParent = new DevExpress.XtraEditors.ComboBoxEdit();
            this.ddlTemplate = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblSignName = new System.Windows.Forms.Label();
            this.lblTemplate = new System.Windows.Forms.Label();
            this.txtSignName = new DevExpress.XtraEditors.TextEdit();
            this.btSignImage = new DevExpress.XtraEditors.ButtonEdit();
            this.btnDeleteImage = new DevExpress.XtraEditors.SimpleButton();
            this.btnWebCam = new DevExpress.XtraEditors.SimpleButton();
            this.btnSignDetail = new DevExpress.XtraEditors.SimpleButton();
            this.lblImage = new System.Windows.Forms.Label();
            this.grConncet = new DevExpress.XtraEditors.GroupControl();
            this.panProxy = new DevExpress.XtraEditors.PanelControl();
            this.panConnect = new DevExpress.XtraEditors.PanelControl();
            this.panRadioImage = new DevExpress.XtraEditors.PanelControl();
            this.btnTestProxy = new DevExpress.XtraEditors.SimpleButton();
            this.label5 = new System.Windows.Forms.Label();
            this.lblProxyType = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lblUserName = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.txtProxyIpAdd = new DevExpress.XtraEditors.TextEdit();
            this.txtProxyPortNo = new DevExpress.XtraEditors.TextEdit();
            this.txtProxyPWD = new DevExpress.XtraEditors.TextEdit();
            this.txtProxyUserName = new DevExpress.XtraEditors.TextEdit();
            this.ddlProxyType = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblConncetState = new System.Windows.Forms.Label();
            this.btnUseProxy = new DevExpress.XtraEditors.SimpleButton();
            this.btnSSHLogin = new DevExpress.XtraEditors.SimpleButton();
            this.chkStorePWD = new System.Windows.Forms.CheckBox();
            this.lblConnectPortNumber = new System.Windows.Forms.Label();
            this.lblConnectIpAddress = new System.Windows.Forms.Label();
            this.lblServerName = new System.Windows.Forms.Label();
            this.lblConnectPassword = new System.Windows.Forms.Label();
            this.txtConnectIpAddress = new DevExpress.XtraEditors.TextEdit();
            this.txtConnectPortNo = new DevExpress.XtraEditors.TextEdit();
            this.txtConnectPWD = new DevExpress.XtraEditors.TextEdit();
            this.txtServerName = new DevExpress.XtraEditors.TextEdit();
            this.grSign = new DevExpress.XtraEditors.GroupControl();
            this.lbnSignType = new System.Windows.Forms.Label();
            this.lblHeight = new System.Windows.Forms.Label();
            this.ddlSignType = new DevExpress.XtraEditors.ComboBoxEdit();
            this.lblWidth = new System.Windows.Forms.Label();
            this.txtHeight = new DevExpress.XtraEditors.TextEdit();
            this.txtWidth = new DevExpress.XtraEditors.TextEdit();
            this.lblPx1 = new System.Windows.Forms.Label();
            this.lblPX = new System.Windows.Forms.Label();
            this.btnMoreDetail = new DevExpress.XtraEditors.SimpleButton();
            this.btnAddTemplate = new DevExpress.XtraEditors.SimpleButton();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.signPanel)).BeginInit();
            this.signPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignParent.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlTemplate.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtSignName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.btSignImage.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grConncet)).BeginInit();
            this.grConncet.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panProxy)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panConnect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panRadioImage)).BeginInit();
            this.panProxy.SuspendLayout();
            this.panConnect.SuspendLayout();
            this.panRadioImage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyIpAdd.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPortNo.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPWD.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyUserName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlProxyType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectIpAddress.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectPortNo.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectPWD.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtServerName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grSign)).BeginInit();
            this.grSign.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignType.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // signPanel
            // 
            this.signPanel.Controls.Add(this.rdbDemoSign);
            this.signPanel.Controls.Add(this.rdbLiveSign);
            //this.signPanel.Controls.Add(this.rdbPhotograph);
            //this.signPanel.Controls.Add(this.rdbWebCam);
            this.signPanel.Controls.Add(this.lblParentGroup);
            this.signPanel.Controls.Add(this.ddlSignParent);
            this.signPanel.Controls.Add(this.ddlTemplate);
            this.signPanel.Controls.Add(this.lblSignName);
            this.signPanel.Controls.Add(this.panRadioImage);

            this.signPanel.Controls.Add(this.lblTemplate);
            this.signPanel.Controls.Add(this.txtSignName);
            this.signPanel.Controls.Add(this.btSignImage);
            this.signPanel.Controls.Add(this.btnDeleteImage);
            //this.signPanel.Controls.Add(this.btnWebCam);
            this.signPanel.Controls.Add(this.btnSignDetail);
            this.signPanel.Controls.Add(this.lblImage);
            this.signPanel.Controls.Add(this.grConncet);
            this.signPanel.Controls.Add(this.grSign);
            this.signPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.signPanel.Location = new System.Drawing.Point(0, 0);
            this.signPanel.Name = "signPanel";
            this.signPanel.Size = new System.Drawing.Size(383, 322);
            this.signPanel.TabIndex = 0;
            // 
            // rdbDemoSign
            // 
            this.rdbDemoSign.AutoSize = true;
            this.rdbDemoSign.Checked = true;
            this.rdbDemoSign.Location = new System.Drawing.Point(178, 177);
            this.rdbDemoSign.Name = "rdbDemoSign";
            this.rdbDemoSign.Size = new System.Drawing.Size(77, 17);
            this.rdbDemoSign.TabIndex = 6;
            this.rdbDemoSign.TabStop = true;
            this.rdbDemoSign.Text = "Demo Sign";
            this.rdbDemoSign.UseVisualStyleBackColor = true;
            this.rdbDemoSign.CheckedChanged += new System.EventHandler(this.rdbDemoSign_CheckedChanged);
            // 
            // rdbLiveSign
            // 
            this.rdbLiveSign.AutoSize = true;
            this.rdbLiveSign.Location = new System.Drawing.Point(70, 177);
            this.rdbLiveSign.Name = "rdbLiveSign";
            this.rdbLiveSign.Size = new System.Drawing.Size(69, 17);
            this.rdbLiveSign.TabIndex = 6;
            this.rdbLiveSign.Text = "Live Sign";
            this.rdbLiveSign.UseVisualStyleBackColor = true;
            this.rdbLiveSign.CheckedChanged += new System.EventHandler(this.rdbLiveSign_CheckedChanged);
            // 
            // rdbPhotograph
            // 
            this.rdbPhotograph.AutoSize = true;
            this.rdbPhotograph.Checked = true;
            this.rdbPhotograph.Location = new System.Drawing.Point(0, 0);
            this.rdbPhotograph.Name = "rdbPhotograph";
            this.rdbPhotograph.Size = new System.Drawing.Size(82, 17);
            this.rdbPhotograph.TabIndex = 6;
            this.rdbPhotograph.TabStop = true;
            //this.rdbPhotograph.
            this.rdbPhotograph.Text = "Photograph";
            this.rdbPhotograph.UseVisualStyleBackColor = true;
            this.rdbPhotograph.CheckedChanged += new System.EventHandler(rdbPhotograph_CheckedChanged);
            // 
            // rdbWebCam
            // 
            this.rdbWebCam.AutoSize = true;
            //this.rdbWebCam.Checked = true;
            this.rdbWebCam.Location = new System.Drawing.Point(82, 0);
            this.rdbWebCam.Name = "rdbWebCam";
            this.rdbWebCam.Size = new System.Drawing.Size(90, 17);
            this.rdbWebCam.TabIndex = 6;
            this.rdbWebCam.TabStop = true;
            this.rdbWebCam.Text = "Web Camera";
            this.rdbWebCam.UseVisualStyleBackColor = true;
            this.rdbWebCam.CheckedChanged += new System.EventHandler(rdbWebCam_CheckedChanged);

            // 
            // rdbTcpIp
            // 
            this.rdbTcpIp.AutoSize = true;
            this.rdbTcpIp.Checked = true;
            this.rdbTcpIp.Location = new System.Drawing.Point(85, 23);
            this.rdbTcpIp.Name = "rdbTcpIp";
            this.rdbTcpIp.Size = new System.Drawing.Size(60, 17);
            this.rdbTcpIp.TabIndex = 6;
            this.rdbTcpIp.TabStop = true;
            this.rdbTcpIp.Text = "Tcp/Ip";
            this.rdbTcpIp.UseVisualStyleBackColor = true;
            this.rdbTcpIp.CheckedChanged += new System.EventHandler(rdbPhotograph_CheckedChanged);
            // 
            // rdbTcpIp
            // 
            this.rdbModem.AutoSize = true;
            this.rdbModem.Checked = false;
            this.rdbModem.Location = new System.Drawing.Point(146, 23);
            this.rdbModem.Name = "rdbModem";
            this.rdbModem.Size = new System.Drawing.Size(60, 17);
            this.rdbModem.TabIndex = 6;
            this.rdbModem.TabStop = true;
            this.rdbModem.Text = "Modem";
            this.rdbModem.UseVisualStyleBackColor = true;
            this.rdbModem.CheckedChanged += new System.EventHandler(rdbModem_CheckedChanged);
            // 
            // rdbSerial
            // 
            this.rdbSerial.AutoSize = true;
            this.rdbSerial.Checked = false;
            this.rdbSerial.Location = new System.Drawing.Point(207, 23);
            this.rdbSerial.Name = "rdbSerial";
            this.rdbSerial.Size = new System.Drawing.Size(60, 17);
            this.rdbSerial.TabIndex = 6;
            this.rdbSerial.TabStop = true;
            this.rdbSerial.Text = "Serial";
            this.rdbSerial.UseVisualStyleBackColor = true;
            this.rdbSerial.CheckedChanged += new System.EventHandler(rdbSerial_CheckedChanged);
            // 
            // lblParentGroup
            // 
            this.lblParentGroup.AutoSize = true;
            this.lblParentGroup.Location = new System.Drawing.Point(35, 42);
            this.lblParentGroup.Name = "lblParentGroup";
            this.lblParentGroup.Size = new System.Drawing.Size(73, 13);
            this.lblParentGroup.TabIndex = 2;
            this.lblParentGroup.Text = "Parent Group:";
            // 
            // ddlSignParent
            // 
            this.ddlSignParent.CausesValidation = false;
            this.ddlSignParent.Location = new System.Drawing.Point(124, 39);
            this.ddlSignParent.Name = "ddlSignParent";
            this.ddlSignParent.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSignParent.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlSignParent.Size = new System.Drawing.Size(161, 20);
            this.ddlSignParent.TabIndex = 2;
            this.ddlSignParent.SelectedValueChanged += new System.EventHandler(this.ddlSignParent_SelectedValueChanged);
            this.ddlSignParent.Popup += new System.EventHandler(this.ddlSignParent_Popup);
            // 
            // ddlTemplate
            // 
            this.ddlTemplate.Location = new System.Drawing.Point(124, 146);
            this.ddlTemplate.Name = "ddlTemplate";
            this.ddlTemplate.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlTemplate.Size = new System.Drawing.Size(161, 20);
            this.ddlTemplate.TabIndex = 5;
            this.ddlTemplate.SelectedIndexChanged += new System.EventHandler(this.ddlTemplate_SelectedIndexChanged);
            this.ddlTemplate.TextChanged += new System.EventHandler(this.ddlTemplate_TextChanged);
            
            // 
            // lblSignName
            // 
            this.lblSignName.AutoSize = true;
            this.lblSignName.Location = new System.Drawing.Point(35, 9);
            this.lblSignName.Name = "lblSignName";
            this.lblSignName.Size = new System.Drawing.Size(50, 13);
            this.lblSignName.TabIndex = 0;
            this.lblSignName.Text = "SignName:";
            // 
            // lblTemplate
            // 
            this.lblTemplate.AutoSize = true;
            this.lblTemplate.Location = new System.Drawing.Point(35, 145);
            this.lblTemplate.Name = "lblTemplate";
            this.lblTemplate.Size = new System.Drawing.Size(50, 13);
            this.lblTemplate.TabIndex = 6;
            this.lblTemplate.Text = "Use Template:";
            // 
            // txtSignName
            // 
            this.txtSignName.Location = new System.Drawing.Point(124, 5);
            this.txtSignName.Name = "txtSignName";
            this.txtSignName.Properties.MaxLength = 60;
            this.txtSignName.Size = new System.Drawing.Size(161, 20);
            this.txtSignName.TabIndex = 1;
            // 
            // btSignImage
            // 
            this.btSignImage.EditValue = "";
            this.btSignImage.Location = new System.Drawing.Point(124, 113);
            this.btSignImage.Name = "btSignImage";
            this.btSignImage.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.btSignImage.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.btSignImage.Size = new System.Drawing.Size(136, 20);
            this.btSignImage.TabIndex = 4;
            this.btSignImage.Click += new System.EventHandler(this.btSignImage_Click);
            // 
            // btnDeleteImage
            // 
            this.btnDeleteImage.Image = ((System.Drawing.Image)(resources.GetObject("btnDeleteImage.Image")));
            this.btnDeleteImage.Location = new System.Drawing.Point(261, 110);
            this.btnDeleteImage.Name = "btnDeleteImage";
            this.btnDeleteImage.Size = new System.Drawing.Size(26, 28);
            this.btnDeleteImage.TabIndex = 4;
            this.btnDeleteImage.ToolTip = "Delete the shape";
            this.btnDeleteImage.Click += new System.EventHandler(this.btnDeleteImage_Click);
            // 
            // btnDeleteImage
            // 
            this.btnWebCam.Image = Resources.Resource.GetImage(Resources.Resource.Images.Edit16);
            btnWebCam.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleCenter;
            this.btnWebCam.Location = new System.Drawing.Point(172, 0);
            this.btnWebCam.Name = "btnWebCam";
            this.btnWebCam.Size = new System.Drawing.Size(23, 23);
            this.btnWebCam.TabIndex = 4;
            this.btnWebCam.ToolTip = "Setup web camera";
            this.btnWebCam.Click += new System.EventHandler(btnWebCam_Click);
            // 
            // btnSignDetail
            // 
            this.btnSignDetail.Location = new System.Drawing.Point(10, BtnSaveHeight(false));
            this.btnSignDetail.Name = "btnSignDetail";
            this.btnSignDetail.Size = new System.Drawing.Size(100, 23);
            this.btnSignDetail.TabIndex = 52;
            this.btnSignDetail.Text = "Sign Detail Info";
            this.btnSignDetail.ToolTip = "Sign Detail Info";
            this.btnSignDetail.Click += new System.EventHandler(this.btnSignDetail_Click);
            // 
            // lblImage
            // 
            this.lblImage.AutoSize = true;
            this.lblImage.Location = new System.Drawing.Point(35, 76);
            this.lblImage.Name = "lblImage";
            this.lblImage.Size = new System.Drawing.Size(39, 13);
            this.lblImage.TabIndex = 4;
            this.lblImage.Text = "Image:";
            // 
            // grConncet
            // 
            this.grConncet.Controls.Add(this.panProxy);
            this.grConncet.Controls.Add(this.panConnect);
            this.grConncet.Controls.Add(this.rdbTcpIp);
            this.grConncet.Controls.Add(this.rdbModem);
            this.grConncet.Controls.Add(this.rdbSerial);
            this.grConncet.Location = new System.Drawing.Point(7, 200);
            this.grConncet.Name = "grConncet";
            this.grConncet.Size = new System.Drawing.Size(320, 153);
            this.grConncet.TabIndex = 22;
            this.grConncet.Text = "Connect";
            this.grConncet.Visible = false;

            // 
            // panProxy
            // 
            this.panProxy.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panProxy.Controls.Add(this.btnTestProxy);
            this.panProxy.Controls.Add(this.label5);
            this.panProxy.Controls.Add(this.lblProxyType);
            this.panProxy.Controls.Add(this.label6);
            this.panProxy.Controls.Add(this.lblUserName);
            this.panProxy.Controls.Add(this.label8);
            this.panProxy.Controls.Add(this.txtProxyIpAdd);
            this.panProxy.Controls.Add(this.txtProxyPortNo);
            this.panProxy.Controls.Add(this.txtProxyPWD);
            this.panProxy.Controls.Add(this.txtProxyUserName);
            this.panProxy.Controls.Add(this.ddlProxyType);
            //this.panProxy.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panProxy.Location = new System.Drawing.Point(2, 146);
            this.panProxy.Name = "panProxy";
            this.panProxy.Size = new System.Drawing.Size(314, 120);
            this.panProxy.TabIndex = 25;
            this.panProxy.Visible = false;
            // 
            // panConnect
            // 
            this.panConnect.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panConnect.Controls.Add(this.lblConncetState);
            this.panConnect.Controls.Add(this.btnUseProxy);
            this.panConnect.Controls.Add(this.btnSSHLogin);
            this.panConnect.Controls.Add(this.chkStorePWD);
            this.panConnect.Controls.Add(this.lblConnectPortNumber);
            this.panConnect.Controls.Add(this.lblConnectIpAddress);
            this.panConnect.Controls.Add(this.lblServerName);
            this.panConnect.Controls.Add(this.lblConnectPassword);
            this.panConnect.Controls.Add(this.txtConnectIpAddress);
            this.panConnect.Controls.Add(this.txtConnectPortNo);
            this.panConnect.Controls.Add(this.txtConnectPWD);
            this.panConnect.Controls.Add(this.txtServerName);
            //this.panConnect.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panConnect.Location = new System.Drawing.Point(2, 40);
            this.panConnect.Name = "panConnect";
            this.panConnect.Size = new System.Drawing.Size(314, 100);
            this.panConnect.TabIndex = 25;
            this.panConnect.Visible = true;
            // 
            // panProxy
            // 
            this.panRadioImage.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;

            this.panRadioImage.Controls.Add(this.rdbPhotograph);
            this.panRadioImage.Controls.Add(this.rdbWebCam);
            this.panRadioImage.Controls.Add(this.btnWebCam);
            this.panRadioImage.Location = new System.Drawing.Point(124, 78);
            this.panRadioImage.Name = "panRadioImage";
            this.panRadioImage.Size = new System.Drawing.Size(200, 25);
            this.panRadioImage.TabIndex = 25;
            this.panRadioImage.Visible = true;
            // 
            // btnTestProxy
            // 
            this.btnTestProxy.Location = new System.Drawing.Point(245, 97);
            this.btnTestProxy.Name = "btnTestProxy";
            this.btnTestProxy.Size = new System.Drawing.Size(57, 23);
            this.btnTestProxy.TabIndex = 24;
            this.btnTestProxy.Text = "Test";
            this.btnTestProxy.ToolTip = "Test";
            this.btnTestProxy.Click += new System.EventHandler(this.btnTestProxy_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(174, 41);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(69, 13);
            this.label5.TabIndex = 23;
            this.label5.Text = "Port Number:";
            // 
            // lblProxyType
            // 
            this.lblProxyType.AutoSize = true;
            this.lblProxyType.Location = new System.Drawing.Point(5, 10);
            this.lblProxyType.Name = "lblProxyType";
            this.lblProxyType.Size = new System.Drawing.Size(50, 13);
            this.lblProxyType.TabIndex = 22;
            this.lblProxyType.Text = "Proxy Type:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(5, 40);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(50, 13);
            this.label6.TabIndex = 22;
            this.label6.Text = "IP Address:";
            // 
            // lblUserName
            // 
            this.lblUserName.AutoSize = true;
            this.lblUserName.Location = new System.Drawing.Point(5, 75);
            this.lblUserName.Name = "lblUserName";
            this.lblUserName.Size = new System.Drawing.Size(50, 13);
            this.lblUserName.TabIndex = 21;
            this.lblUserName.Text = "User Name:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(174, 72);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(50, 13);
            this.label8.TabIndex = 20;
            this.label8.Text = "Password:";
            // 
            // txtProxyIpAdd
            // 
            this.txtProxyIpAdd.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtProxyIpAdd.Location = new System.Drawing.Point(85, 40);
            this.txtProxyIpAdd.Name = "txtProxyIpAdd";
            //this.txtProxyIpAdd.Properties.MaxLength = 4;
            this.txtProxyIpAdd.Size = new System.Drawing.Size(85, 20);
            this.txtProxyIpAdd.TabIndex = 19;
            this.txtProxyIpAdd.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtIpAddressUser_KeyPress);
            // 
            // txtProxyPortNo
            // 
            this.txtProxyPortNo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtProxyPortNo.Location = new System.Drawing.Point(256, 40);
            this.txtProxyPortNo.Name = "txtProxyPortNo";
            this.txtProxyPortNo.Properties.MaxLength = 4;
            this.txtProxyPortNo.Size = new System.Drawing.Size(58, 20);
            this.txtProxyPortNo.TabIndex = 18;
            this.txtProxyPortNo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtPortNumber_KeyPress);
            // 
            // txtProxyPWD
            // 
            this.txtProxyPWD.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtProxyPWD.Location = new System.Drawing.Point(256, 71);
            this.txtProxyPWD.Name = "txtProxyPWD";
            this.txtProxyPWD.Properties.MaxLength = 4;
            this.txtProxyPWD.Size = new System.Drawing.Size(58, 20);
            this.txtProxyPWD.TabIndex = 17;
            this.txtProxyPWD.Properties.PasswordChar = '*';
            // 
            // txtProxyUserName
            // 
            this.txtProxyUserName.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtProxyUserName.Location = new System.Drawing.Point(85, 74);
            this.txtProxyUserName.Name = "txtProxyUserName";
            this.txtProxyUserName.Properties.MaxLength = 50;
            this.txtProxyUserName.Size = new System.Drawing.Size(85, 20);
            this.txtProxyUserName.TabIndex = 16;
            // 
            // ddlProxyType
            // 
            this.ddlProxyType.CausesValidation = false;
            this.ddlProxyType.Location = new System.Drawing.Point(85, 9);
            this.ddlProxyType.Name = "ddlProxyType";
            this.ddlProxyType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlProxyType.Properties.Items.AddRange(new object[] {
            "None",
            "Socks4",
            "Socks5"});
            this.ddlProxyType.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlProxyType.Size = new System.Drawing.Size(81, 20);
            this.ddlProxyType.TabIndex = 3;
            this.ddlProxyType.SelectedIndexChanged += new System.EventHandler(this.ddlProxyType_SelectedIndexChanged);
            // 
            // lblConncetState
            // 
            this.lblConncetState.AutoSize = true;
            this.lblConncetState.Location = new System.Drawing.Point(14, 102);
            this.lblConncetState.Name = "lblConncetState";
            this.lblConncetState.Size = new System.Drawing.Size(0, 13);
            this.lblConncetState.TabIndex = 26;
            // 
            // btnUseProxy
            // 
            this.btnUseProxy.Location = new System.Drawing.Point(249, 78);
            this.btnUseProxy.Name = "btnUseProxy";
            this.btnUseProxy.Size = new System.Drawing.Size(65, 23);
            this.btnUseProxy.TabIndex = 25;
            this.btnUseProxy.Text = "Use Proxy";
            this.btnUseProxy.ToolTip = "Use Proxy";
            this.btnUseProxy.Click += new System.EventHandler(this.btnUseProxy_Click);
            // 
            // btnSSHLogin
            // 
            this.btnSSHLogin.Location = new System.Drawing.Point(10, 98);
            this.btnSSHLogin.Name = "btnSSHLogin";
            this.btnSSHLogin.Size = new System.Drawing.Size(65, 23);
            this.btnSSHLogin.TabIndex = 25;
            this.btnSSHLogin.Text = "SSH Acc";
            this.btnSSHLogin.ToolTip = "SSH Acc";
            this.btnSSHLogin.Visible = false;
            this.btnSSHLogin.Click += new System.EventHandler(btnSSHLogin_Click);
            // 
            // chkStorePWD
            // 
            this.chkStorePWD.AutoSize = true;
            this.chkStorePWD.Location = new System.Drawing.Point(117, 82);
            this.chkStorePWD.Name = "chkStorePWD";
            this.chkStorePWD.Size = new System.Drawing.Size(124, 17);
            this.chkStorePWD.TabIndex = 22;
            this.chkStorePWD.Text = "Store Sign Password";
            this.chkStorePWD.UseVisualStyleBackColor = true;
            this.chkStorePWD.Checked = true;
            // 
            // label4
            // 
            this.lblConnectPortNumber.AutoSize = true;
            this.lblConnectPortNumber.Location = new System.Drawing.Point(174, 14);
            this.lblConnectPortNumber.Name = "label4";
            this.lblConnectPortNumber.Size = new System.Drawing.Size(50, 13);
            this.lblConnectPortNumber.TabIndex = 15;
            this.lblConnectPortNumber.Text = "Port Number:";
            // 
            // label3
            // 
            this.lblConnectIpAddress.AutoSize = true;
            this.lblConnectIpAddress.Location = new System.Drawing.Point(5, 14);
            this.lblConnectIpAddress.Name = "label3";
            this.lblConnectIpAddress.Size = new System.Drawing.Size(50, 13);
            this.lblConnectIpAddress.TabIndex = 14;
            this.lblConnectIpAddress.Text = "IP Address:";
            // 
            // lblServerName
            // 
            this.lblServerName.AutoSize = true;
            this.lblServerName.Location = new System.Drawing.Point(5, 52);
            this.lblServerName.Name = "lblServerName";
            this.lblServerName.Size = new System.Drawing.Size(50, 13);
            this.lblServerName.TabIndex = 13;
            this.lblServerName.Text = "User Name:";
            // 
            // label1
            // 
            this.lblConnectPassword.AutoSize = true;
            this.lblConnectPassword.Location = new System.Drawing.Point(174, 53);
            this.lblConnectPassword.Name = "label1";
            this.lblConnectPassword.Size = new System.Drawing.Size(50, 13);
            this.lblConnectPassword.TabIndex = 12;
            this.lblConnectPassword.Text = "Password:";
            // 
            // textEdit4
            // 
            this.txtConnectIpAddress.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtConnectIpAddress.Location = new System.Drawing.Point(86, 11);
            this.txtConnectIpAddress.Name = "textEdit4";
            this.txtConnectIpAddress.Size = new System.Drawing.Size(85, 20);
            this.txtConnectIpAddress.TabIndex = 7;
            this.txtConnectIpAddress.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtIpAddressUser_KeyPress);
            // 
            // textEdit3
            // 
            this.txtConnectPortNo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtConnectPortNo.Location = new System.Drawing.Point(256, 11);
            this.txtConnectPortNo.Name = "textEdit3";
            this.txtConnectPortNo.Properties.MaxLength = 4;
            this.txtConnectPortNo.Size = new System.Drawing.Size(58, 20);
            this.txtConnectPortNo.TabIndex = 8;
            this.txtConnectPortNo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtPortNumber_KeyPress);
            // 
            // textEdit2
            // 
            this.txtConnectPWD.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtConnectPWD.Location = new System.Drawing.Point(256, 50);
            this.txtConnectPWD.Name = "textEdit2";
            this.txtConnectPWD.Size = new System.Drawing.Size(58, 20);
            this.txtConnectPWD.TabIndex = 10;
            this.txtConnectPWD.Properties.PasswordChar = '*';
            // 
            // textEdit1
            // 
            this.txtServerName.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtServerName.Location = new System.Drawing.Point(86, 49);
            this.txtServerName.Name = "textEdit1";
            this.txtServerName.Size = new System.Drawing.Size(85, 20);
            this.txtServerName.TabIndex = 9;
            // 
            // grSign
            // 
            this.grSign.Controls.Add(this.lbnSignType);
            this.grSign.Controls.Add(this.lblHeight);
            this.grSign.Controls.Add(this.ddlSignType);
            this.grSign.Controls.Add(this.lblWidth);
            this.grSign.Controls.Add(this.txtHeight);
            this.grSign.Controls.Add(this.txtWidth);
            this.grSign.Controls.Add(this.lblPx1);
            this.grSign.Controls.Add(this.lblPX);
            this.grSign.Location = new System.Drawing.Point(7, 200);
            this.grSign.Name = "grSign";
            this.grSign.Size = new System.Drawing.Size(320, 153);
            this.grSign.TabIndex = 24;
            this.grSign.Text = "Demo Sign";
            // 
            // lbnSignType
            // 
            this.lbnSignType.AutoSize = true;
            this.lbnSignType.Location = new System.Drawing.Point(28, 47);
            this.lbnSignType.Name = "lbnSignType";
            this.lbnSignType.Size = new System.Drawing.Size(50, 13);
            this.lbnSignType.TabIndex = 6;
            this.lbnSignType.Text = "Sign Type:";
            // 
            // lblHeight
            // 
            this.lblHeight.AutoSize = true;
            this.lblHeight.Location = new System.Drawing.Point(28, 81);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(41, 13);
            this.lblHeight.TabIndex = 10;
            this.lblHeight.Text = "Height:";
            // 
            // ddlSignType
            // 
            this.ddlSignType.CausesValidation = false;
            this.ddlSignType.Location = new System.Drawing.Point(115, 45);
            this.ddlSignType.Name = "ddlSignType";
            this.ddlSignType.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlSignType.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlSignType.Size = new System.Drawing.Size(161, 20);
            this.ddlSignType.TabIndex = 7;
            this.ddlSignType.SelectedValueChanged += new System.EventHandler(this.ddlSignType_SelectedValueChanged);
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(28, 112);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(38, 13);
            this.lblWidth.TabIndex = 8;
            this.lblWidth.Text = "Width:";
            // 
            // txtHeight
            // 
            this.txtHeight.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.txtHeight.Location = new System.Drawing.Point(115, 77);
            this.txtHeight.Name = "txtHeight";
            this.txtHeight.Properties.MaxLength = 4;
            this.txtHeight.Size = new System.Drawing.Size(161, 20);
            this.txtHeight.TabIndex = 8;
            // 
            // txtWidth
            // 
            this.txtWidth.Location = new System.Drawing.Point(115, 110);
            this.txtWidth.Name = "txtWidth";
            this.txtWidth.Properties.MaxLength = 4;
            this.txtWidth.Size = new System.Drawing.Size(161, 20);
            this.txtWidth.TabIndex = 9;
            // 
            // lblPx1
            // 
            this.lblPx1.AutoSize = true;
            this.lblPx1.Location = new System.Drawing.Point(278, 79);
            this.lblPx1.Name = "lblPx1";
            this.lblPx1.Size = new System.Drawing.Size(18, 13);
            this.lblPx1.TabIndex = 12;
            this.lblPx1.Text = "pixel";
            // 
            // lblPX
            // 
            this.lblPX.AutoSize = true;
            this.lblPX.Location = new System.Drawing.Point(278, 112);
            this.lblPX.Name = "lblPX";
            this.lblPX.Size = new System.Drawing.Size(18, 13);
            this.lblPX.TabIndex = 13;
            this.lblPX.Text = "pixel";
            // 
            // btnMoreDetail
            // 
            this.btnMoreDetail.Image = ((System.Drawing.Image)(resources.GetObject("btnMoreDetail.Image")));
            this.btnMoreDetail.Location = new System.Drawing.Point(393, 75);
            this.btnMoreDetail.Name = "btnMoreDetail";
            this.btnMoreDetail.Size = new System.Drawing.Size(26, 28);
            this.btnMoreDetail.TabIndex = 20;
            this.btnMoreDetail.ToolTip = "More Detail";
            this.btnMoreDetail.Click += new System.EventHandler(this.btnMoreDetail_Click);
            // 
            // btnAddTemplate
            // 
            this.btnAddTemplate.Image = ((System.Drawing.Image)(resources.GetObject("btnAddTemplate.Image")));
            this.btnAddTemplate.Location = new System.Drawing.Point(424, 75);
            this.btnAddTemplate.Name = "btnAddTemplate";
            this.btnAddTemplate.Size = new System.Drawing.Size(26, 28);
            this.btnAddTemplate.TabIndex = 21;
            this.btnAddTemplate.ToolTip = "Add Template";
            this.btnAddTemplate.Click += new System.EventHandler(this.btnAddTemplate_Click);
            // 
            // bindingSource1
            // 
            this.bindingSource1.DataSource = typeof(ProWrite.Entity.Dashboard.SignInfo);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "All supported picture files|*.jpg;*.jpeg;*.gif;*.png;*.bmp|Jpeg File(*.jpg,*.jpeg)|*.jpg;*.jpeg|Gif File(*.gif)|*.gif|Png File(*.png)|*.png|Bmp File(*.bmp)" +
                "|*.bmp";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog_FileOk);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(249, BtnSaveHeight(false));
            btnCancel.TabIndex = 10;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(176, BtnSaveHeight(false));
            btnSave.TabIndex = 9;
            // 
            // SignForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            //this.AcceptButton = this.btnSave;
            //this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(333, ClientHeight("0"));
            this.Controls.Add(this.signPanel);
            this.Controls.Add(this.btnAddTemplate);
            this.Controls.Add(this.btnMoreDetail);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SignForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            ((System.ComponentModel.ISupportInitialize)(this.signPanel)).EndInit();
            this.signPanel.ResumeLayout(false);
            this.signPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignParent.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlTemplate.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtSignName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.btSignImage.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grConncet)).EndInit();
            this.grConncet.ResumeLayout(false);
            this.grConncet.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panProxy)).EndInit();
            this.panProxy.ResumeLayout(false);
            this.panProxy.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyIpAdd.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPortNo.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyPWD.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtProxyUserName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlProxyType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectIpAddress.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectPortNo.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtConnectPWD.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtServerName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grSign)).EndInit();
            this.grSign.ResumeLayout(false);
            this.grSign.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlSignType.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            this.ResumeLayout(false);

        }



        #endregion

        private DevExpress.XtraEditors.PanelControl signPanel;
        private System.Windows.Forms.Label lblParentGroup;
        private DevExpress.XtraEditors.ComboBoxEdit ddlSignParent;
        private DevExpress.XtraEditors.TextEdit txtHeight;
        private DevExpress.XtraEditors.TextEdit txtWidth;
        private System.Windows.Forms.Label lblSignName;
        private System.Windows.Forms.Label lbnSignType;
        private System.Windows.Forms.Label lblTemplate;
        private DevExpress.XtraEditors.TextEdit txtSignName;
        private System.Windows.Forms.Label lblPX;
        private System.Windows.Forms.Label lblPx1;
        private System.Windows.Forms.Label lblWidth;
        private DevExpress.XtraEditors.ComboBoxEdit ddlSignType;
        private System.Windows.Forms.Label lblHeight;
        private DevExpress.XtraEditors.ButtonEdit btSignImage;
        private System.Windows.Forms.Label lblImage;
        //private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.SimpleButton btnDeleteImage;
        private DevExpress.XtraEditors.SimpleButton btnMoreDetail;
        private DevExpress.XtraEditors.SimpleButton btnAddTemplate;
        private DevExpress.XtraEditors.SimpleButton btnSignDetail;
        private DevExpress.XtraEditors.SimpleButton btnSSHLogin;
        private DevExpress.XtraEditors.SimpleButton btnWebCam;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private DevExpress.XtraEditors.ComboBoxEdit ddlTemplate;
        private System.Windows.Forms.RadioButton rdbDemoSign;
        private System.Windows.Forms.RadioButton rdbLiveSign;
        private System.Windows.Forms.RadioButton rdbWebCam;
        private System.Windows.Forms.RadioButton rdbPhotograph;
        private System.Windows.Forms.RadioButton rdbTcpIp;
        private System.Windows.Forms.RadioButton rdbModem;
        private System.Windows.Forms.RadioButton rdbSerial;
        private DevExpress.XtraEditors.PanelControl panRadioImage;
        private DevExpress.XtraEditors.GroupControl grSign;
        private System.Windows.Forms.Label lblConnectPortNumber;
        private System.Windows.Forms.Label lblConnectIpAddress;
        private System.Windows.Forms.Label lblServerName;
        private System.Windows.Forms.Label lblConnectPassword;
        private DevExpress.XtraEditors.TextEdit txtConnectIpAddress;
        private DevExpress.XtraEditors.TextEdit txtConnectPortNo;
        private DevExpress.XtraEditors.TextEdit txtConnectPWD;
        private DevExpress.XtraEditors.TextEdit txtServerName;
        private DevExpress.XtraEditors.GroupControl grConncet;
        private System.Windows.Forms.CheckBox chkStorePWD;
        private System.Windows.Forms.Label lblConncetState;
        private DevExpress.XtraEditors.SimpleButton btnUseProxy;
        private DevExpress.XtraEditors.PanelControl panProxy;
        private DevExpress.XtraEditors.PanelControl panConnect;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblProxyType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lblUserName;
        private System.Windows.Forms.Label label8;
        private DevExpress.XtraEditors.TextEdit txtProxyIpAdd;
        private DevExpress.XtraEditors.TextEdit txtProxyPortNo;
        private DevExpress.XtraEditors.TextEdit txtProxyPWD;
        private DevExpress.XtraEditors.TextEdit txtProxyUserName;
        private DevExpress.XtraEditors.ComboBoxEdit ddlProxyType;
        private DevExpress.XtraEditors.SimpleButton btnTestProxy;
        
        //private DevExpress.XtraEditors.SimpleButton btnSave;
        //private DevExpress.XtraEditors.SimpleButton btnCancel;
    }
}
