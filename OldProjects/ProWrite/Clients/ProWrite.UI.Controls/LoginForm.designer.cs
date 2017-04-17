using ProWrite.Resources;
using System.Windows.Forms;
using System.Drawing;

namespace ProWrite.UI.Controls
{
    partial class LoginForm
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
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.txtRegFour = new System.Windows.Forms.TextBox();
            this.txtRegThree = new System.Windows.Forms.TextBox();
            this.txtRegTwo = new System.Windows.Forms.TextBox();
            this.txtRegOne = new System.Windows.Forms.TextBox();
            this.txtSalesNumber = new DevExpress.XtraEditors.TextEdit();
            this.layoutControl1 = new DevExpress.XtraLayout.LayoutControl();
            this.labelControl14 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl13 = new DevExpress.XtraEditors.LabelControl();
            this.chkLaunch = new DevExpress.XtraEditors.CheckEdit();
            this.labelControl12 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl11 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl9 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl8 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl7 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl6 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl5 = new DevExpress.XtraEditors.LabelControl();
            this.btnEmail = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl4 = new DevExpress.XtraEditors.LabelControl();
            this.lblHttp = new DevExpress.XtraEditors.LabelControl();
            this.lblHelpDesk = new DevExpress.XtraEditors.LabelControl();
            this.lblVersion = new DevExpress.XtraEditors.LabelControl();
            this.pictureEdit1 = new DevExpress.XtraEditors.PictureEdit();
            this.lblProWrite = new DevExpress.XtraEditors.LabelControl();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.btnCopy = new DevExpress.XtraEditors.SimpleButton();
            this.btnClose = new DevExpress.XtraEditors.SimpleButton();
            this.btnLogin = new DevExpress.XtraEditors.SimpleButton();
            this.btnReSet = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl10 = new DevExpress.XtraEditors.LabelControl();
            this.layoutControlGroup1 = new DevExpress.XtraLayout.LayoutControlGroup();
            this.emptySpaceItem4 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem2 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem3 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem4 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem5 = new DevExpress.XtraLayout.LayoutControlItem();
            this.lblErrorMSG = new DevExpress.XtraLayout.SimpleLabelItem();
            this.lblRegNumber = new DevExpress.XtraLayout.SimpleLabelItem();
            this.layoutControlItem10 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem12 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem13 = new DevExpress.XtraLayout.LayoutControlItem();
            this.emptySpaceItem3 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem6 = new DevExpress.XtraLayout.LayoutControlItem();
            this.emptySpaceItem6 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem14 = new DevExpress.XtraLayout.LayoutControlItem();
            this.itemVersion = new DevExpress.XtraLayout.LayoutControlItem();
            this.itemlHelpDesk = new DevExpress.XtraLayout.LayoutControlItem();
            this.itemHttp = new DevExpress.XtraLayout.LayoutControlItem();
            this.emptySpaceItem2 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.emptySpaceItem7 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.emptySpaceItem1 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem15 = new DevExpress.XtraLayout.LayoutControlItem();
            this.emptySpaceItem9 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem16 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem17 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem9 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem11 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem18 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem19 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem1 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem20 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem21 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem22 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem7 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem23 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem24 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem25 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem26 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem27 = new DevExpress.XtraLayout.LayoutControlItem();
            this.layoutControlItem28 = new DevExpress.XtraLayout.LayoutControlItem();
            this.emptySpaceItem5 = new DevExpress.XtraLayout.EmptySpaceItem();
            this.layoutControlItem8 = new DevExpress.XtraLayout.LayoutControlItem();
            ((System.ComponentModel.ISupportInitialize)(this.txtSalesNumber.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).BeginInit();
            this.layoutControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chkLaunch.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureEdit1.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblErrorMSG)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblRegNumber)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem10)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem12)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem13)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem6)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem14)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemVersion)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemlHelpDesk)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemHttp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem7)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem15)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem9)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem16)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem17)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem9)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem11)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem18)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem19)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem20)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem21)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem22)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem7)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem23)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem24)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem25)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem26)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem27)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem28)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem8)).BeginInit();
            this.SuspendLayout();
            // 
            // txtRegFour
            // 
            this.txtRegFour.Font = new System.Drawing.Font("Tahoma", 10F);
            this.txtRegFour.Location = new System.Drawing.Point(261, 350);
            this.txtRegFour.MaxLength = 4;
            this.txtRegFour.Name = "txtRegFour";
            this.txtRegFour.Size = new System.Drawing.Size(74, 20);
            this.txtRegFour.TabIndex = 3;
            this.txtRegFour.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtRegOne_KeyPress);
            // 
            // txtRegThree
            // 
            this.txtRegThree.Font = new System.Drawing.Font("Tahoma", 10F);
            this.txtRegThree.Location = new System.Drawing.Point(176, 350);
            this.txtRegThree.MaxLength = 4;
            this.txtRegThree.Name = "txtRegThree";
            this.txtRegThree.Size = new System.Drawing.Size(74, 20);
            this.txtRegThree.TabIndex = 2;
            this.txtRegThree.Tag = "";
            this.txtRegThree.TextChanged += new System.EventHandler(this.txtRegThree_TextChanged);
            this.txtRegThree.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtRegOne_KeyPress);
            // 
            // txtRegTwo
            // 
            this.txtRegTwo.Font = new System.Drawing.Font("Tahoma", 10F);
            this.txtRegTwo.Location = new System.Drawing.Point(92, 350);
            this.txtRegTwo.MaxLength = 4;
            this.txtRegTwo.Name = "txtRegTwo";
            this.txtRegTwo.Size = new System.Drawing.Size(73, 20);
            this.txtRegTwo.TabIndex = 1;
            this.txtRegTwo.Tag = "";
            this.txtRegTwo.TextChanged += new System.EventHandler(this.txtRegTwo_TextChanged);
            this.txtRegTwo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtRegOne_KeyPress);
            // 
            // txtRegOne
            // 
            this.txtRegOne.Font = new System.Drawing.Font("Tahoma", 10F);
            this.txtRegOne.Location = new System.Drawing.Point(7, 350);
            this.txtRegOne.MaxLength = 4;
            this.txtRegOne.Name = "txtRegOne";
            this.txtRegOne.Size = new System.Drawing.Size(74, 20);
            this.txtRegOne.TabIndex = 0;
            this.txtRegOne.TextChanged += new System.EventHandler(this.txtRegOne_TextChanged);
            this.txtRegOne.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtRegOne_KeyPress);
            // 
            // txtSalesNumber
            // 
            this.txtSalesNumber.Location = new System.Drawing.Point(124, 109);
            this.txtSalesNumber.Name = "txtSalesNumber";
            this.txtSalesNumber.Properties.Appearance.Font = new System.Drawing.Font("Tahoma", 10F);
            this.txtSalesNumber.Properties.Appearance.Options.UseFont = true;
            this.txtSalesNumber.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.txtSalesNumber.Properties.MaxLength = 6;
            this.txtSalesNumber.Size = new System.Drawing.Size(101, 23);
            this.txtSalesNumber.StyleController = this.layoutControl1;
            this.txtSalesNumber.TabIndex = 0;
            this.txtSalesNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtSalesNumber_KeyPress);
            this.txtSalesNumber.TextChanged += new System.EventHandler(this.txtSalesNumber_TextChanged);
            // 
            // layoutControl1
            // 
            this.layoutControl1.Appearance.DisabledLayoutGroupCaption.ForeColor = System.Drawing.SystemColors.GrayText;
            this.layoutControl1.Appearance.DisabledLayoutGroupCaption.Options.UseForeColor = true;
            this.layoutControl1.Appearance.DisabledLayoutItem.ForeColor = System.Drawing.SystemColors.GrayText;
            this.layoutControl1.Appearance.DisabledLayoutItem.Options.UseForeColor = true;
            this.layoutControl1.Controls.Add(this.labelControl14);
            this.layoutControl1.Controls.Add(this.labelControl13);
            this.layoutControl1.Controls.Add(this.chkLaunch);
            this.layoutControl1.Controls.Add(this.labelControl12);
            this.layoutControl1.Controls.Add(this.labelControl11);
            this.layoutControl1.Controls.Add(this.labelControl9);
            this.layoutControl1.Controls.Add(this.labelControl8);
            this.layoutControl1.Controls.Add(this.labelControl7);
            this.layoutControl1.Controls.Add(this.labelControl6);
            this.layoutControl1.Controls.Add(this.labelControl5);
            this.layoutControl1.Controls.Add(this.btnEmail);
            this.layoutControl1.Controls.Add(this.labelControl4);
            this.layoutControl1.Controls.Add(this.lblHttp);
            this.layoutControl1.Controls.Add(this.lblHelpDesk);
            this.layoutControl1.Controls.Add(this.lblVersion);
            this.layoutControl1.Controls.Add(this.pictureEdit1);
            this.layoutControl1.Controls.Add(this.lblProWrite);
            this.layoutControl1.Controls.Add(this.labelControl3);
            this.layoutControl1.Controls.Add(this.labelControl2);
            this.layoutControl1.Controls.Add(this.labelControl1);
            this.layoutControl1.Controls.Add(this.txtRegFour);
            this.layoutControl1.Controls.Add(this.txtRegThree);
            this.layoutControl1.Controls.Add(this.txtRegOne);
            this.layoutControl1.Controls.Add(this.txtSalesNumber);
            this.layoutControl1.Controls.Add(this.txtRegTwo);
            this.layoutControl1.Controls.Add(this.btnCopy);
            this.layoutControl1.Controls.Add(this.btnClose);
            this.layoutControl1.Controls.Add(this.btnLogin);
            this.layoutControl1.Controls.Add(this.btnReSet);
            this.layoutControl1.Controls.Add(this.labelControl10);
            this.layoutControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.layoutControl1.Location = new System.Drawing.Point(0, 0);
            this.layoutControl1.Name = "layoutControl1";
            this.layoutControl1.Root = this.layoutControlGroup1;
            this.layoutControl1.Size = new System.Drawing.Size(696, 432);
            this.layoutControl1.TabIndex = 23;
            this.layoutControl1.Text = "layoutControl1";
            //this.layoutControl1.Visible = false;
            this.layoutControl1.ShowContextMenu += new DevExpress.XtraLayout.LayoutMenuEventHandler(this.layoutControl1_ShowContextMenu);
            // 
            // labelControl14
            // 
            this.labelControl14.Location = new System.Drawing.Point(7, 381);
            this.labelControl14.Name = "labelControl14";
            this.labelControl14.Size = new System.Drawing.Size(10, 13);
            this.labelControl14.StyleController = this.layoutControl1;
            this.labelControl14.TabIndex = 46;
            this.labelControl14.Text = "6.";
            // 
            // labelControl13
            // 
            this.labelControl13.Location = new System.Drawing.Point(7, 296);
            this.labelControl13.Name = "labelControl13";
            this.labelControl13.Size = new System.Drawing.Size(10, 13);
            this.labelControl13.StyleController = this.layoutControl1;
            this.labelControl13.TabIndex = 45;
            this.labelControl13.Text = "4.";
            // 
            // chkLaunch
            // 
            this.chkLaunch.Location = new System.Drawing.Point(28, 296);
            this.chkLaunch.Name = "chkLaunch";
            this.chkLaunch.Properties.Caption = "Launch Quick Start Tutorial for the first use of ProWrite";
            this.chkLaunch.Size = new System.Drawing.Size(447, 19);
            this.chkLaunch.StyleController = this.layoutControl1;
            this.chkLaunch.TabIndex = 44;
            this.chkLaunch.CheckedChanged += new System.EventHandler(this.chkLaunch_CheckedChanged);
            // 
            // labelControl12
            // 
            this.labelControl12.Location = new System.Drawing.Point(7, 176);
            this.labelControl12.Name = "labelControl12";
            this.labelControl12.Size = new System.Drawing.Size(12, 13);
            this.labelControl12.StyleController = this.layoutControl1;
            this.labelControl12.TabIndex = 43;
            this.labelControl12.Text = "    ";
            // 
            // labelControl11
            // 
            this.labelControl11.Location = new System.Drawing.Point(7, 326);
            this.labelControl11.Name = "labelControl11";
            this.labelControl11.Size = new System.Drawing.Size(168, 13);
            this.labelControl11.StyleController = this.layoutControl1;
            this.labelControl11.TabIndex = 42;
            this.labelControl11.Text = "5.Enter Registration Number below";
            // 
            // labelControl9
            // 
            this.labelControl9.Location = new System.Drawing.Point(30, 239);
            this.labelControl9.Name = "labelControl9";
            this.labelControl9.Size = new System.Drawing.Size(10, 13);
            this.labelControl9.StyleController = this.layoutControl1;
            this.labelControl9.TabIndex = 40;
            this.labelControl9.Text = "or";
            // 
            // labelControl8
            // 
            this.labelControl8.Location = new System.Drawing.Point(7, 206);
            this.labelControl8.Name = "labelControl8";
            this.labelControl8.Size = new System.Drawing.Size(10, 13);
            this.labelControl8.StyleController = this.layoutControl1;
            this.labelControl8.TabIndex = 39;
            this.labelControl8.Text = "3.";
            // 
            // labelControl7
            // 
            this.labelControl7.Location = new System.Drawing.Point(162, 239);
            this.labelControl7.Name = "labelControl7";
            this.labelControl7.Size = new System.Drawing.Size(313, 13);
            this.labelControl7.StyleController = this.layoutControl1;
            this.labelControl7.TabIndex = 38;
            this.labelControl7.Text = "and paste to email addressed to: registration@tlxcommercial.com";
            // 
            // labelControl6
            // 
            this.labelControl6.Location = new System.Drawing.Point(7, 239);
            this.labelControl6.Name = "labelControl6";
            this.labelControl6.Size = new System.Drawing.Size(12, 13);
            this.labelControl6.StyleController = this.layoutControl1;
            this.labelControl6.TabIndex = 37;
            this.labelControl6.Text = "    ";
            // 
            // labelControl5
            // 
            this.labelControl5.Location = new System.Drawing.Point(7, 143);
            this.labelControl5.Name = "labelControl5";
            this.labelControl5.Size = new System.Drawing.Size(10, 13);
            this.labelControl5.StyleController = this.layoutControl1;
            this.labelControl5.TabIndex = 36;
            this.labelControl5.Text = "2.";
            // 
            // btnEmail
            // 
            this.btnEmail.Location = new System.Drawing.Point(28, 206);
            this.btnEmail.Name = "btnEmail";
            this.btnEmail.Size = new System.Drawing.Size(115, 22);
            this.btnEmail.StyleController = this.layoutControl1;
            this.btnEmail.TabIndex = 35;
            this.btnEmail.Text = "Email Seed Key";
            this.btnEmail.Click += new System.EventHandler(this.btnEmail_Click);
            // 
            // labelControl4
            // 
            this.labelControl4.Location = new System.Drawing.Point(154, 206);
            this.labelControl4.Name = "labelControl4";
            this.labelControl4.Size = new System.Drawing.Size(321, 13);
            this.labelControl4.StyleController = this.layoutControl1;
            this.labelControl4.TabIndex = 34;
            this.labelControl4.Text = "to registration@tlxcommercial.com                                                " +
                "    ";
            // 
            // lblHttp
            // 
            this.lblHttp.Location = new System.Drawing.Point(615, 157);
            this.lblHttp.Name = "lblHttp";
            this.lblHttp.Size = new System.Drawing.Size(63, 13);
            this.lblHttp.StyleController = this.layoutControl1;
            this.lblHttp.TabIndex = 32;
            this.lblHttp.Text = "labelControl6";
            // 
            // lblHelpDesk
            // 
            this.lblHelpDesk.Appearance.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold);
            this.lblHelpDesk.Appearance.Options.UseFont = true;
            this.lblHelpDesk.Location = new System.Drawing.Point(615, 133);
            this.lblHelpDesk.Name = "lblHelpDesk";
            this.lblHelpDesk.Size = new System.Drawing.Size(75, 13);
            this.lblHelpDesk.StyleController = this.layoutControl1;
            this.lblHelpDesk.TabIndex = 31;
            this.lblHelpDesk.Text = "labelControl5";
            // 
            // lblVersion
            // 
            this.lblVersion.Location = new System.Drawing.Point(615, 109);
            this.lblVersion.Name = "lblVersion";
            this.lblVersion.Size = new System.Drawing.Size(63, 13);
            this.lblVersion.StyleController = this.layoutControl1;
            this.lblVersion.TabIndex = 30;
            this.lblVersion.Text = "labelControl4";
            // 
            // pictureEdit1
            // 
            this.pictureEdit1.Location = new System.Drawing.Point(615, 181);
            this.pictureEdit1.Name = "pictureEdit1";
            this.pictureEdit1.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.pictureEdit1.Properties.Appearance.Options.UseBackColor = true;
            this.pictureEdit1.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.pictureEdit1.Size = new System.Drawing.Size(75, 189);
            this.pictureEdit1.StyleController = this.layoutControl1;
            this.pictureEdit1.TabIndex = 29;
            // 
            // lblProWrite
            // 
            this.lblProWrite.Appearance.Font = new System.Drawing.Font("Tahoma", 25F, System.Drawing.FontStyle.Bold);
            this.lblProWrite.Appearance.Options.UseFont = true;
            this.lblProWrite.Location = new System.Drawing.Point(467, 17);
            this.lblProWrite.Name = "lblProWrite";
            this.lblProWrite.Size = new System.Drawing.Size(223, 40);
            this.lblProWrite.StyleController = this.layoutControl1;
            this.lblProWrite.TabIndex = 33;
            this.lblProWrite.Text = "labelControl4";
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(7, 272);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(221, 13);
            this.labelControl3.StyleController = this.layoutControl1;
            this.labelControl3.TabIndex = 27;
            this.labelControl3.Text = "      and wait for a reply within 1 business day.";
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(148, 143);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(327, 13);
            this.labelControl2.StyleController = this.layoutControl1;
            this.labelControl2.TabIndex = 26;
            this.labelControl2.Text = "                                                                                 " +
                "                            ";
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(7, 109);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(106, 13);
            this.labelControl1.StyleController = this.layoutControl1;
            this.labelControl1.TabIndex = 25;
            this.labelControl1.Text = "1.Sales Order Number";
            // 
            // btnCopy
            // 
            this.btnCopy.Location = new System.Drawing.Point(51, 239);
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.Size = new System.Drawing.Size(100, 22);
            this.btnCopy.StyleController = this.layoutControl1;
            this.btnCopy.TabIndex = 28;
            this.btnCopy.Text = "Copy To Clipboard";
            this.btnCopy.ToolTip = "Copy To Clipboard";
            this.btnCopy.Click += new System.EventHandler(this.btnCopy_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(585, 381);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(105, 22);
            this.btnClose.StyleController = this.layoutControl1;
            this.btnClose.TabIndex = 22;
            this.btnClose.Text = "Close";
            this.btnClose.ToolTip = "Close";
            this.btnClose.Visible = false;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(28, 381);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(81, 22);
            this.btnLogin.StyleController = this.layoutControl1;
            this.btnLogin.TabIndex = 23;
            this.btnLogin.Text = "Register";
            this.btnLogin.ToolTip = "Register";
            this.btnLogin.Visible = false;
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // btnReSet
            // 
            this.btnReSet.Enabled = false;
            this.btnReSet.Location = new System.Drawing.Point(28, 143);
            this.btnReSet.Name = "btnReSet";
            this.btnReSet.Size = new System.Drawing.Size(109, 22);
            this.btnReSet.StyleController = this.layoutControl1;
            this.btnReSet.TabIndex = 24;
            this.btnReSet.Text = "Generate Seed Key";
            this.btnReSet.ToolTip = "Generate Seed Key";
            this.btnReSet.Click += new System.EventHandler(this.btnReSet_Click);
            // 
            // labelControl10
            // 
            this.labelControl10.Location = new System.Drawing.Point(346, 350);
            this.labelControl10.Name = "labelControl10";
            this.labelControl10.Size = new System.Drawing.Size(129, 13);
            this.labelControl10.StyleController = this.layoutControl1;
            this.labelControl10.TabIndex = 41;
            this.labelControl10.Text = "                                           ";
            // 
            // layoutControlGroup1
            // 
            this.layoutControlGroup1.BackgroundImageVisible = true;
            this.layoutControlGroup1.CustomizationFormText = "Root";
            this.layoutControlGroup1.Items.AddRange(new DevExpress.XtraLayout.BaseLayoutItem[] {
            this.emptySpaceItem4,
            this.layoutControlItem2,
            this.layoutControlItem3,
            this.layoutControlItem4,
            this.layoutControlItem5,
            this.lblErrorMSG,
            this.lblRegNumber,
            this.layoutControlItem10,
            this.layoutControlItem12,
            this.layoutControlItem13,
            this.emptySpaceItem3,
            this.layoutControlItem6,
            this.emptySpaceItem6,
            this.layoutControlItem14,
            this.itemVersion,
            this.itemlHelpDesk,
            this.itemHttp,
            this.emptySpaceItem2,
            this.emptySpaceItem7,
            this.emptySpaceItem1,
            this.layoutControlItem15,
            this.emptySpaceItem9,
            this.layoutControlItem16,
            this.layoutControlItem17,
            this.layoutControlItem9,
            this.layoutControlItem11,
            this.layoutControlItem18,
            this.layoutControlItem19,
            this.layoutControlItem1,
            this.layoutControlItem20,
            this.layoutControlItem21,
            this.layoutControlItem22,
            this.layoutControlItem7,
            this.layoutControlItem23,
            this.layoutControlItem24,
            this.layoutControlItem25,
            this.layoutControlItem26,
            this.layoutControlItem27,
            this.layoutControlItem28});
            this.layoutControlGroup1.Location = new System.Drawing.Point(0, 0);
            this.layoutControlGroup1.Name = "Root";
            this.layoutControlGroup1.Size = new System.Drawing.Size(696, 432);
            this.layoutControlGroup1.Spacing = new DevExpress.XtraLayout.Utils.Padding(0, 0, 0, 0);
            this.layoutControlGroup1.Text = "Root";
            this.layoutControlGroup1.TextVisible = false;
            // 
            // emptySpaceItem4
            // 
            this.emptySpaceItem4.CustomizationFormText = "emptySpaceItem4";
            this.emptySpaceItem4.Location = new System.Drawing.Point(0, 0);
            this.emptySpaceItem4.Name = "emptySpaceItem4";
            this.emptySpaceItem4.Size = new System.Drawing.Size(460, 102);
            this.emptySpaceItem4.Text = "emptySpaceItem4";
            this.emptySpaceItem4.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.emptySpaceItem4.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem2
            // 
            this.layoutControlItem2.Control = this.txtRegOne;
            this.layoutControlItem2.CustomizationFormText = "layoutControlItem2";
            this.layoutControlItem2.Location = new System.Drawing.Point(0, 343);
            this.layoutControlItem2.Name = "layoutControlItem2";
            this.layoutControlItem2.Size = new System.Drawing.Size(85, 31);
            this.layoutControlItem2.Text = "layoutControlItem2";
            this.layoutControlItem2.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem2.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem2.TextToControlDistance = 0;
            this.layoutControlItem2.TextVisible = false;
            // 
            // layoutControlItem3
            // 
            this.layoutControlItem3.Control = this.txtRegTwo;
            this.layoutControlItem3.CustomizationFormText = "layoutControlItem3";
            this.layoutControlItem3.Location = new System.Drawing.Point(85, 343);
            this.layoutControlItem3.Name = "layoutControlItem3";
            this.layoutControlItem3.Size = new System.Drawing.Size(84, 31);
            this.layoutControlItem3.Text = "layoutControlItem3";
            this.layoutControlItem3.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem3.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem3.TextToControlDistance = 0;
            this.layoutControlItem3.TextVisible = false;
            // 
            // layoutControlItem4
            // 
            this.layoutControlItem4.Control = this.txtRegThree;
            this.layoutControlItem4.CustomizationFormText = "layoutControlItem4";
            this.layoutControlItem4.Location = new System.Drawing.Point(169, 343);
            this.layoutControlItem4.Name = "layoutControlItem4";
            this.layoutControlItem4.Size = new System.Drawing.Size(85, 31);
            this.layoutControlItem4.Text = "layoutControlItem4";
            this.layoutControlItem4.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem4.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem4.TextToControlDistance = 0;
            this.layoutControlItem4.TextVisible = false;
            // 
            // layoutControlItem5
            // 
            this.layoutControlItem5.Control = this.txtRegFour;
            this.layoutControlItem5.CustomizationFormText = "layoutControlItem5";
            this.layoutControlItem5.Location = new System.Drawing.Point(254, 343);
            this.layoutControlItem5.Name = "layoutControlItem5";
            this.layoutControlItem5.Size = new System.Drawing.Size(85, 31);
            this.layoutControlItem5.Text = "layoutControlItem5";
            this.layoutControlItem5.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem5.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem5.TextToControlDistance = 0;
            this.layoutControlItem5.TextVisible = false;
            // 
            // lblErrorMSG
            // 
            this.lblErrorMSG.AppearanceItemCaption.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
            this.lblErrorMSG.AppearanceItemCaption.ForeColor = System.Drawing.Color.Red;
            this.lblErrorMSG.AppearanceItemCaption.Options.UseFont = true;
            this.lblErrorMSG.AppearanceItemCaption.Options.UseForeColor = true;
            this.lblErrorMSG.CustomizationFormText = "Sorry,you have not registered!";
            this.lblErrorMSG.Location = new System.Drawing.Point(113, 374);
            this.lblErrorMSG.Name = "simpleLabelItem1";
            this.lblErrorMSG.Size = new System.Drawing.Size(366, 33);
            this.lblErrorMSG.Text = "Sorry,you have not registered!                                         ";
            this.lblErrorMSG.TextSize = new System.Drawing.Size(354, 14);
            // 
            // lblRegNumber
            // 
            this.lblRegNumber.AppearanceItemCaption.Font = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblRegNumber.AppearanceItemCaption.ForeColor = System.Drawing.Color.Blue;
            this.lblRegNumber.AppearanceItemCaption.Options.UseFont = true;
            this.lblRegNumber.AppearanceItemCaption.Options.UseForeColor = true;
            this.lblRegNumber.CustomizationFormText = "LabelsimpleLabelItem6";
            this.lblRegNumber.Location = new System.Drawing.Point(23, 169);
            this.lblRegNumber.Name = "lblRegNumber";
            this.lblRegNumber.Size = new System.Drawing.Size(456, 30);
            this.lblRegNumber.Text = "LabellblRegNumber";
            this.lblRegNumber.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.lblRegNumber.TextSize = new System.Drawing.Size(390, 20);
            // 
            // layoutControlItem10
            // 
            this.layoutControlItem10.Control = this.txtSalesNumber;
            this.layoutControlItem10.CustomizationFormText = "layoutControlItem10";
            this.layoutControlItem10.Location = new System.Drawing.Point(117, 102);
            this.layoutControlItem10.Name = "layoutControlItem10";
            this.layoutControlItem10.Size = new System.Drawing.Size(112, 34);
            this.layoutControlItem10.Text = "layoutControlItem10";
            this.layoutControlItem10.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem10.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem10.TextToControlDistance = 0;
            this.layoutControlItem10.TextVisible = false;
            // 
            // layoutControlItem12
            // 
            this.layoutControlItem12.Control = this.labelControl2;
            this.layoutControlItem12.CustomizationFormText = "layoutControlItem12";
            this.layoutControlItem12.Location = new System.Drawing.Point(141, 136);
            this.layoutControlItem12.Name = "layoutControlItem12";
            this.layoutControlItem12.Size = new System.Drawing.Size(338, 33);
            this.layoutControlItem12.Text = "layoutControlItem12";
            this.layoutControlItem12.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem12.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem12.TextToControlDistance = 0;
            this.layoutControlItem12.TextVisible = false;
            // 
            // layoutControlItem13
            // 
            this.layoutControlItem13.Control = this.labelControl3;
            this.layoutControlItem13.CustomizationFormText = "layoutControlItem13";
            this.layoutControlItem13.Location = new System.Drawing.Point(0, 265);
            this.layoutControlItem13.Name = "layoutControlItem13";
            this.layoutControlItem13.Size = new System.Drawing.Size(479, 24);
            this.layoutControlItem13.Text = "layoutControlItem13";
            this.layoutControlItem13.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem13.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem13.TextToControlDistance = 0;
            this.layoutControlItem13.TextVisible = false;
            // 
            // emptySpaceItem3
            // 
            this.emptySpaceItem3.CustomizationFormText = "emptySpaceItem3";
            this.emptySpaceItem3.Location = new System.Drawing.Point(229, 102);
            this.emptySpaceItem3.Name = "emptySpaceItem3";
            this.emptySpaceItem3.Size = new System.Drawing.Size(250, 34);
            this.emptySpaceItem3.Text = "emptySpaceItem3";
            this.emptySpaceItem3.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem6
            // 
            this.layoutControlItem6.Control = this.btnClose;
            this.layoutControlItem6.CustomizationFormText = "layoutControlItem6";
            this.layoutControlItem6.Location = new System.Drawing.Point(578, 374);
            this.layoutControlItem6.Name = "layoutControlItem6";
            this.layoutControlItem6.Size = new System.Drawing.Size(116, 33);
            this.layoutControlItem6.Text = "layoutControlItem6";
            this.layoutControlItem6.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem6.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem6.TextToControlDistance = 0;
            this.layoutControlItem6.TextVisible = false;
            // 
            // emptySpaceItem6
            // 
            this.emptySpaceItem6.CustomizationFormText = "emptySpaceItem6";
            this.emptySpaceItem6.Location = new System.Drawing.Point(479, 374);
            this.emptySpaceItem6.Name = "emptySpaceItem6";
            this.emptySpaceItem6.Size = new System.Drawing.Size(99, 33);
            this.emptySpaceItem6.Text = "emptySpaceItem6";
            this.emptySpaceItem6.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem14
            // 
            this.layoutControlItem14.Control = this.pictureEdit1;
            this.layoutControlItem14.CustomizationFormText = "layoutControlItem14";
            this.layoutControlItem14.Location = new System.Drawing.Point(608, 174);
            this.layoutControlItem14.Name = "layoutControlItem14";
            this.layoutControlItem14.Size = new System.Drawing.Size(86, 200);
            this.layoutControlItem14.Text = "layoutControlItem14";
            this.layoutControlItem14.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem14.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem14.TextToControlDistance = 0;
            this.layoutControlItem14.TextVisible = false;
            // 
            // itemVersion
            // 
            this.itemVersion.Control = this.lblVersion;
            this.itemVersion.CustomizationFormText = "itemVersion";
            this.itemVersion.Location = new System.Drawing.Point(608, 102);
            this.itemVersion.Name = "itemVersion";
            this.itemVersion.Size = new System.Drawing.Size(86, 24);
            this.itemVersion.Text = "itemVersion";
            this.itemVersion.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.itemVersion.TextLocation = DevExpress.Utils.Locations.Left;
            this.itemVersion.TextSize = new System.Drawing.Size(0, 0);
            this.itemVersion.TextToControlDistance = 0;
            this.itemVersion.TextVisible = false;
            // 
            // itemlHelpDesk
            // 
            this.itemlHelpDesk.Control = this.lblHelpDesk;
            this.itemlHelpDesk.CustomizationFormText = "itemlHelpDesk";
            this.itemlHelpDesk.Location = new System.Drawing.Point(608, 126);
            this.itemlHelpDesk.Name = "itemlHelpDesk";
            this.itemlHelpDesk.Size = new System.Drawing.Size(86, 24);
            this.itemlHelpDesk.Text = "itemlHelpDesk";
            this.itemlHelpDesk.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.itemlHelpDesk.TextLocation = DevExpress.Utils.Locations.Left;
            this.itemlHelpDesk.TextSize = new System.Drawing.Size(0, 0);
            this.itemlHelpDesk.TextToControlDistance = 0;
            this.itemlHelpDesk.TextVisible = false;
            // 
            // itemHttp
            // 
            this.itemHttp.Control = this.lblHttp;
            this.itemHttp.CustomizationFormText = "itemHttp";
            this.itemHttp.Location = new System.Drawing.Point(608, 150);
            this.itemHttp.Name = "itemHttp";
            this.itemHttp.Size = new System.Drawing.Size(86, 24);
            this.itemHttp.Text = "itemHttp";
            this.itemHttp.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.itemHttp.TextLocation = DevExpress.Utils.Locations.Left;
            this.itemHttp.TextSize = new System.Drawing.Size(0, 0);
            this.itemHttp.TextToControlDistance = 0;
            this.itemHttp.TextVisible = false;
            // 
            // emptySpaceItem2
            // 
            this.emptySpaceItem2.CustomizationFormText = "emptySpaceItem2";
            this.emptySpaceItem2.Location = new System.Drawing.Point(460, 0);
            this.emptySpaceItem2.Name = "emptySpaceItem2";
            this.emptySpaceItem2.Size = new System.Drawing.Size(234, 10);
            this.emptySpaceItem2.Text = "emptySpaceItem2";
            this.emptySpaceItem2.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.emptySpaceItem2.TextSize = new System.Drawing.Size(0, 0);
            // 
            // emptySpaceItem7
            // 
            this.emptySpaceItem7.CustomizationFormText = "emptySpaceItem7";
            this.emptySpaceItem7.Location = new System.Drawing.Point(460, 61);
            this.emptySpaceItem7.Name = "emptySpaceItem7";
            this.emptySpaceItem7.Size = new System.Drawing.Size(234, 41);
            this.emptySpaceItem7.Text = "emptySpaceItem7";
            this.emptySpaceItem7.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.emptySpaceItem7.TextSize = new System.Drawing.Size(0, 0);
            // 
            // emptySpaceItem1
            // 
            this.emptySpaceItem1.CustomizationFormText = "emptySpaceItem1";
            this.emptySpaceItem1.Location = new System.Drawing.Point(0, 407);
            this.emptySpaceItem1.Name = "emptySpaceItem1";
            this.emptySpaceItem1.Size = new System.Drawing.Size(694, 23);
            this.emptySpaceItem1.Text = "emptySpaceItem1";
            this.emptySpaceItem1.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.emptySpaceItem1.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem15
            // 
            this.layoutControlItem15.Control = this.lblProWrite;
            this.layoutControlItem15.CustomizationFormText = "layoutControlItem15";
            this.layoutControlItem15.Location = new System.Drawing.Point(460, 10);
            this.layoutControlItem15.Name = "layoutControlItem15";
            this.layoutControlItem15.Size = new System.Drawing.Size(234, 51);
            this.layoutControlItem15.Text = "layoutControlItem15";
            this.layoutControlItem15.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.layoutControlItem15.TextLocation = DevExpress.Utils.Locations.Right;
            this.layoutControlItem15.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem15.TextToControlDistance = 0;
            this.layoutControlItem15.TextVisible = false;
            // 
            // emptySpaceItem9
            // 
            this.emptySpaceItem9.CustomizationFormText = "emptySpaceItem9";
            this.emptySpaceItem9.Location = new System.Drawing.Point(479, 102);
            this.emptySpaceItem9.Name = "emptySpaceItem9";
            this.emptySpaceItem9.Size = new System.Drawing.Size(129, 272);
            this.emptySpaceItem9.Text = "emptySpaceItem9";
            this.emptySpaceItem9.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.emptySpaceItem9.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem16
            // 
            this.layoutControlItem16.Control = this.labelControl4;
            this.layoutControlItem16.CustomizationFormText = "layoutControlItem16";
            this.layoutControlItem16.Location = new System.Drawing.Point(147, 199);
            this.layoutControlItem16.Name = "layoutControlItem16";
            this.layoutControlItem16.Size = new System.Drawing.Size(332, 33);
            this.layoutControlItem16.Text = "layoutControlItem16";
            this.layoutControlItem16.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem16.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem16.TextToControlDistance = 0;
            this.layoutControlItem16.TextVisible = false;
            // 
            // layoutControlItem17
            // 
            this.layoutControlItem17.Control = this.btnEmail;
            this.layoutControlItem17.CustomizationFormText = "layoutControlItem17";
            this.layoutControlItem17.Location = new System.Drawing.Point(21, 199);
            this.layoutControlItem17.Name = "layoutControlItem17";
            this.layoutControlItem17.Size = new System.Drawing.Size(126, 33);
            this.layoutControlItem17.Text = "layoutControlItem17";
            this.layoutControlItem17.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem17.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem17.TextToControlDistance = 0;
            this.layoutControlItem17.TextVisible = false;
            // 
            // layoutControlItem9
            // 
            this.layoutControlItem9.Control = this.btnReSet;
            this.layoutControlItem9.CustomizationFormText = "layoutControlItem9";
            this.layoutControlItem9.Location = new System.Drawing.Point(21, 136);
            this.layoutControlItem9.Name = "layoutControlItem9";
            this.layoutControlItem9.Size = new System.Drawing.Size(120, 33);
            this.layoutControlItem9.Text = "layoutControlItem9";
            this.layoutControlItem9.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem9.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem9.TextToControlDistance = 0;
            this.layoutControlItem9.TextVisible = false;
            // 
            // layoutControlItem11
            // 
            this.layoutControlItem11.Control = this.labelControl1;
            this.layoutControlItem11.CustomizationFormText = "layoutControlItem11";
            this.layoutControlItem11.Location = new System.Drawing.Point(0, 102);
            this.layoutControlItem11.Name = "layoutControlItem11";
            this.layoutControlItem11.Size = new System.Drawing.Size(117, 34);
            this.layoutControlItem11.Text = "layoutControlItem11";
            this.layoutControlItem11.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem11.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem11.TextToControlDistance = 0;
            this.layoutControlItem11.TextVisible = false;
            // 
            // layoutControlItem18
            // 
            this.layoutControlItem18.Control = this.labelControl5;
            this.layoutControlItem18.CustomizationFormText = "layoutControlItem18";
            this.layoutControlItem18.Location = new System.Drawing.Point(0, 136);
            this.layoutControlItem18.Name = "layoutControlItem18";
            this.layoutControlItem18.Size = new System.Drawing.Size(21, 33);
            this.layoutControlItem18.Text = "layoutControlItem18";
            this.layoutControlItem18.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem18.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem18.TextToControlDistance = 0;
            this.layoutControlItem18.TextVisible = false;
            // 
            // layoutControlItem19
            // 
            this.layoutControlItem19.Control = this.labelControl6;
            this.layoutControlItem19.CustomizationFormText = "layoutControlItem19";
            this.layoutControlItem19.Location = new System.Drawing.Point(0, 232);
            this.layoutControlItem19.Name = "layoutControlItem19";
            this.layoutControlItem19.Size = new System.Drawing.Size(23, 33);
            this.layoutControlItem19.Text = "layoutControlItem19";
            this.layoutControlItem19.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.layoutControlItem19.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem19.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem19.TextToControlDistance = 0;
            this.layoutControlItem19.TextVisible = false;
            // 
            // layoutControlItem1
            // 
            this.layoutControlItem1.Control = this.btnCopy;
            this.layoutControlItem1.CustomizationFormText = "layoutControlItem1";
            this.layoutControlItem1.Location = new System.Drawing.Point(44, 232);
            this.layoutControlItem1.Name = "layoutControlItem1";
            this.layoutControlItem1.Size = new System.Drawing.Size(111, 33);
            this.layoutControlItem1.Text = " ";
            this.layoutControlItem1.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.layoutControlItem1.TextLocation = DevExpress.Utils.Locations.Top;
            this.layoutControlItem1.TextSize = new System.Drawing.Size(100, 0);
            this.layoutControlItem1.TextToControlDistance = 0;
            // 
            // layoutControlItem20
            // 
            this.layoutControlItem20.Control = this.labelControl7;
            this.layoutControlItem20.CustomizationFormText = "layoutControlItem20";
            this.layoutControlItem20.Location = new System.Drawing.Point(155, 232);
            this.layoutControlItem20.Name = "layoutControlItem20";
            this.layoutControlItem20.Size = new System.Drawing.Size(324, 33);
            this.layoutControlItem20.Text = "layoutControlItem20";
            this.layoutControlItem20.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.layoutControlItem20.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem20.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem20.TextToControlDistance = 0;
            this.layoutControlItem20.TextVisible = false;
            // 
            // layoutControlItem21
            // 
            this.layoutControlItem21.Control = this.labelControl8;
            this.layoutControlItem21.CustomizationFormText = "layoutControlItem21";
            this.layoutControlItem21.Location = new System.Drawing.Point(0, 199);
            this.layoutControlItem21.Name = "layoutControlItem21";
            this.layoutControlItem21.Size = new System.Drawing.Size(21, 33);
            this.layoutControlItem21.Text = "layoutControlItem21";
            this.layoutControlItem21.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem21.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem21.TextToControlDistance = 0;
            this.layoutControlItem21.TextVisible = false;
            // 
            // layoutControlItem22
            // 
            this.layoutControlItem22.Control = this.labelControl9;
            this.layoutControlItem22.CustomizationFormText = "layoutControlItem22";
            this.layoutControlItem22.Location = new System.Drawing.Point(23, 232);
            this.layoutControlItem22.Name = "layoutControlItem22";
            this.layoutControlItem22.Size = new System.Drawing.Size(21, 33);
            this.layoutControlItem22.Text = "layoutControlItem22";
            this.layoutControlItem22.TextAlignMode = DevExpress.XtraLayout.TextAlignModeItem.CustomSize;
            this.layoutControlItem22.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem22.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem22.TextToControlDistance = 0;
            this.layoutControlItem22.TextVisible = false;
            // 
            // layoutControlItem7
            // 
            this.layoutControlItem7.Control = this.btnLogin;
            this.layoutControlItem7.CustomizationFormText = "layoutControlItem7";
            this.layoutControlItem7.Location = new System.Drawing.Point(21, 374);
            this.layoutControlItem7.Name = "layoutControlItem7";
            this.layoutControlItem7.Size = new System.Drawing.Size(92, 33);
            this.layoutControlItem7.Text = "layoutControlItem7";
            this.layoutControlItem7.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem7.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem7.TextToControlDistance = 0;
            this.layoutControlItem7.TextVisible = false;
            // 
            // layoutControlItem23
            // 
            this.layoutControlItem23.Control = this.labelControl10;
            this.layoutControlItem23.CustomizationFormText = "layoutControlItem23";
            this.layoutControlItem23.Location = new System.Drawing.Point(339, 343);
            this.layoutControlItem23.Name = "layoutControlItem23";
            this.layoutControlItem23.Size = new System.Drawing.Size(140, 31);
            this.layoutControlItem23.Text = "layoutControlItem23";
            this.layoutControlItem23.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem23.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem23.TextToControlDistance = 0;
            this.layoutControlItem23.TextVisible = false;
            // 
            // layoutControlItem24
            // 
            this.layoutControlItem24.Control = this.labelControl11;
            this.layoutControlItem24.CustomizationFormText = "layoutControlItem24";
            this.layoutControlItem24.Location = new System.Drawing.Point(0, 319);
            this.layoutControlItem24.Name = "layoutControlItem24";
            this.layoutControlItem24.Size = new System.Drawing.Size(479, 24);
            this.layoutControlItem24.Text = "layoutControlItem24";
            this.layoutControlItem24.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem24.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem24.TextToControlDistance = 0;
            this.layoutControlItem24.TextVisible = false;
            // 
            // layoutControlItem25
            // 
            this.layoutControlItem25.Control = this.labelControl12;
            this.layoutControlItem25.CustomizationFormText = "layoutControlItem25";
            this.layoutControlItem25.Location = new System.Drawing.Point(0, 169);
            this.layoutControlItem25.Name = "layoutControlItem25";
            this.layoutControlItem25.Size = new System.Drawing.Size(23, 30);
            this.layoutControlItem25.Text = "layoutControlItem25";
            this.layoutControlItem25.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem25.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem25.TextToControlDistance = 0;
            this.layoutControlItem25.TextVisible = false;
            // 
            // layoutControlItem26
            // 
            this.layoutControlItem26.Control = this.chkLaunch;
            this.layoutControlItem26.CustomizationFormText = "layoutControlItem26";
            this.layoutControlItem26.Location = new System.Drawing.Point(21, 289);
            this.layoutControlItem26.Name = "layoutControlItem26";
            this.layoutControlItem26.Size = new System.Drawing.Size(458, 30);
            this.layoutControlItem26.Text = "layoutControlItem26";
            this.layoutControlItem26.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem26.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem26.TextToControlDistance = 0;
            this.layoutControlItem26.TextVisible = false;
            // 
            // layoutControlItem27
            // 
            this.layoutControlItem27.Control = this.labelControl13;
            this.layoutControlItem27.CustomizationFormText = "layoutControlItem27";
            this.layoutControlItem27.Location = new System.Drawing.Point(0, 289);
            this.layoutControlItem27.Name = "layoutControlItem27";
            this.layoutControlItem27.Size = new System.Drawing.Size(21, 30);
            this.layoutControlItem27.Text = "layoutControlItem27";
            this.layoutControlItem27.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem27.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem27.TextToControlDistance = 0;
            this.layoutControlItem27.TextVisible = false;
            // 
            // layoutControlItem28
            // 
            this.layoutControlItem28.Control = this.labelControl14;
            this.layoutControlItem28.CustomizationFormText = "layoutControlItem28";
            this.layoutControlItem28.Location = new System.Drawing.Point(0, 374);
            this.layoutControlItem28.Name = "layoutControlItem28";
            this.layoutControlItem28.Size = new System.Drawing.Size(21, 33);
            this.layoutControlItem28.Text = "layoutControlItem28";
            this.layoutControlItem28.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem28.TextSize = new System.Drawing.Size(0, 0);
            this.layoutControlItem28.TextToControlDistance = 0;
            this.layoutControlItem28.TextVisible = false;
            // 
            // emptySpaceItem5
            // 
            this.emptySpaceItem5.CustomizationFormText = "emptySpaceItem5";
            this.emptySpaceItem5.Location = new System.Drawing.Point(0, 358);
            this.emptySpaceItem5.Name = "emptySpaceItem5";
            this.emptySpaceItem5.Size = new System.Drawing.Size(128, 30);
            this.emptySpaceItem5.Text = "emptySpaceItem5";
            this.emptySpaceItem5.TextSize = new System.Drawing.Size(0, 0);
            // 
            // layoutControlItem8
            // 
            this.layoutControlItem8.CustomizationFormText = "layoutControlItem8";
            this.layoutControlItem8.Location = new System.Drawing.Point(245, 297);
            this.layoutControlItem8.Name = "layoutControlItem8";
            this.layoutControlItem8.Size = new System.Drawing.Size(1, 33);
            this.layoutControlItem8.Text = "layoutControlItem8";
            this.layoutControlItem8.TextLocation = DevExpress.Utils.Locations.Left;
            this.layoutControlItem8.TextSize = new System.Drawing.Size(50, 20);
            // 
            // LoginForm
            // 
            FormBorderStyle = FormBorderStyle.None;
            StartPosition = FormStartPosition.CenterScreen;
            ShowInTaskbar = false;
            TransparencyKey = Color.Gainsboro;
            TopMost = true;
            this.ClientSize = new System.Drawing.Size(696, 432);
            this.Controls.Add(this.layoutControl1);
            this.Name = "LoginForm";
            this.Text = "ProWrite";
            ((System.ComponentModel.ISupportInitialize)(this.txtSalesNumber.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControl1)).EndInit();
            this.layoutControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chkLaunch.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureEdit1.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlGroup1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblErrorMSG)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lblRegNumber)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem10)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem12)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem13)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem6)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem14)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemVersion)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemlHelpDesk)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.itemHttp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem7)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem15)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem9)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem16)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem17)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem9)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem11)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem18)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem19)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem20)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem21)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem22)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem7)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem23)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem24)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem25)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem26)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem27)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem28)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emptySpaceItem5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.layoutControlItem8)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox txtRegFour;
        private System.Windows.Forms.TextBox txtRegThree;
        private System.Windows.Forms.TextBox txtRegTwo;
        private System.Windows.Forms.TextBox txtRegOne;
        private DevExpress.XtraEditors.TextEdit txtSalesNumber;
        private DevExpress.XtraEditors.SimpleButton btnClose;
        private DevExpress.XtraLayout.LayoutControl layoutControl1;
        private DevExpress.XtraLayout.LayoutControlGroup layoutControlGroup1;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem4;
        private DevExpress.XtraLayout.SimpleLabelItem lblRegNumber;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem2;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem3;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem4;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem5;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem6;
        private DevExpress.XtraEditors.SimpleButton btnLogin;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem7;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem5;
        private DevExpress.XtraLayout.SimpleLabelItem lblErrorMSG;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem8;
        private DevExpress.XtraEditors.SimpleButton btnReSet;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem9;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem10;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem11;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem12;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem13;
        private DevExpress.XtraEditors.SimpleButton btnCopy;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem1;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem3;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem6;
        private DevExpress.XtraEditors.LabelControl lblHttp;
        private DevExpress.XtraEditors.LabelControl lblHelpDesk;
        private DevExpress.XtraEditors.LabelControl lblVersion;
        private DevExpress.XtraEditors.PictureEdit pictureEdit1;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem14;
        private DevExpress.XtraLayout.LayoutControlItem itemVersion;
        private DevExpress.XtraLayout.LayoutControlItem itemlHelpDesk;
        private DevExpress.XtraLayout.LayoutControlItem itemHttp;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem2;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem7;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem1;
        private DevExpress.XtraEditors.LabelControl lblProWrite;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem15;
        private DevExpress.XtraLayout.EmptySpaceItem emptySpaceItem9;
        private DevExpress.XtraEditors.LabelControl labelControl4;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem16;
        private DevExpress.XtraEditors.SimpleButton btnEmail;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem17;
        private DevExpress.XtraEditors.LabelControl labelControl6;
        private DevExpress.XtraEditors.LabelControl labelControl5;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem18;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem19;
        private DevExpress.XtraEditors.LabelControl labelControl8;
        private DevExpress.XtraEditors.LabelControl labelControl7;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem20;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem21;
        private DevExpress.XtraEditors.LabelControl labelControl9;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem22;
        private DevExpress.XtraEditors.LabelControl labelControl10;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem23;
        private DevExpress.XtraEditors.LabelControl labelControl11;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem24;
        private DevExpress.XtraEditors.LabelControl labelControl12;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem25;
        private DevExpress.XtraEditors.CheckEdit chkLaunch;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem26;
        private DevExpress.XtraEditors.LabelControl labelControl14;
        private DevExpress.XtraEditors.LabelControl labelControl13;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem27;
        private DevExpress.XtraLayout.LayoutControlItem layoutControlItem28;
    }
}
