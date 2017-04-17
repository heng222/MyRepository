namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class HotButtonSettingForm
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
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.panelControl3 = new DevExpress.XtraEditors.PanelControl();
            this.btnSmall = new ProWrite.UI.Controls.Live.Sessions.SmallButtonControl();
            this.labelControl4 = new DevExpress.XtraEditors.LabelControl();
            this.btnLarge = new ProWrite.UI.Controls.Live.Sessions.LargeButtonControl();
            this.rdoSize = new DevExpress.XtraEditors.RadioGroup();
            this.panelControl5 = new DevExpress.XtraEditors.PanelControl();
            this.btnHotKey = new DevExpress.XtraEditors.SimpleButton();
            this.txtHotKey = new DevExpress.XtraEditors.TextEdit();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.panelControl4 = new DevExpress.XtraEditors.PanelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.ddlColor = new DevExpress.XtraEditors.ColorEdit();
            this.panelControl2 = new DevExpress.XtraEditors.PanelControl();
            this.txtName = new DevExpress.XtraEditors.TextEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.btnApply = new DevExpress.XtraEditors.SimpleButton();
            this.btnOK = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.panelContainer = new DevExpress.XtraEditors.PanelControl();
            this.panelSign = new DevExpress.XtraEditors.PanelControl();
            this.scrBar = new DevExpress.XtraEditors.VScrollBar();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).BeginInit();
            this.panelControl3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rdoSize.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl5)).BeginInit();
            this.panelControl5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtHotKey.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl4)).BeginInit();
            this.panelControl4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).BeginInit();
            this.panelControl2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelContainer)).BeginInit();
            this.panelContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelSign)).BeginInit();
            this.SuspendLayout();
            // 
            // panelControl1
            // 
            this.panelControl1.Controls.Add(this.panelControl3);
            this.panelControl1.Controls.Add(this.rdoSize);
            this.panelControl1.Controls.Add(this.panelControl5);
            this.panelControl1.Controls.Add(this.panelControl4);
            this.panelControl1.Controls.Add(this.panelControl2);
            this.panelControl1.Location = new System.Drawing.Point(3, 9);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(175, 414);
            this.panelControl1.TabIndex = 0;
            // 
            // panelControl3
            // 
            this.panelControl3.Controls.Add(this.btnSmall);
            this.panelControl3.Controls.Add(this.labelControl4);
            this.panelControl3.Controls.Add(this.btnLarge);
            this.panelControl3.Location = new System.Drawing.Point(5, 218);
            this.panelControl3.Name = "panelControl3";
            this.panelControl3.Size = new System.Drawing.Size(163, 140);
            this.panelControl3.TabIndex = 4;
            // 
            // btnSmall
            // 
            this.btnSmall.BackColor = System.Drawing.Color.Transparent;
            this.btnSmall.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.btnSmall.ButtonColor = System.Drawing.Color.Transparent;
            this.btnSmall.Location = new System.Drawing.Point(26, 40);
            this.btnSmall.Name = "btnSmall";
            this.btnSmall.Size = new System.Drawing.Size(100, 40);
            this.btnSmall.TabIndex = 1;
            // 
            // labelControl4
            // 
            this.labelControl4.Location = new System.Drawing.Point(9, 10);
            this.labelControl4.Name = "labelControl4";
            this.labelControl4.Size = new System.Drawing.Size(42, 13);
            this.labelControl4.TabIndex = 0;
            this.labelControl4.Text = "Preview:";
            // 
            // btnLarge
            // 
            this.btnLarge.BackColor = System.Drawing.Color.Transparent;
            this.btnLarge.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.btnLarge.ButtonColor = System.Drawing.Color.Transparent;
            this.btnLarge.Location = new System.Drawing.Point(26, 40);
            this.btnLarge.Name = "btnLarge";
            this.btnLarge.Size = new System.Drawing.Size(100, 80);
            this.btnLarge.TabIndex = 1;
            // 
            // rdoSize
            // 
            this.rdoSize.EditValue = "Small";
            this.rdoSize.Location = new System.Drawing.Point(5, 70);
            this.rdoSize.Name = "rdoSize";
            this.rdoSize.Properties.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.rdoSize.Properties.Appearance.Options.UseBackColor = true;
            this.rdoSize.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem("Small", "Small"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("Large", "Large")});
            this.rdoSize.Size = new System.Drawing.Size(163, 27);
            this.rdoSize.TabIndex = 0;
            this.rdoSize.SelectedIndexChanged += new System.EventHandler(this.rdoSize_SelectedIndexChanged);
            // 
            // panelControl5
            // 
            this.panelControl5.Controls.Add(this.btnHotKey);
            this.panelControl5.Controls.Add(this.txtHotKey);
            this.panelControl5.Controls.Add(this.labelControl3);
            this.panelControl5.Location = new System.Drawing.Point(5, 142);
            this.panelControl5.Name = "panelControl5";
            this.panelControl5.Size = new System.Drawing.Size(163, 70);
            this.panelControl5.TabIndex = 3;
            // 
            // btnHotKey
            // 
            this.btnHotKey.Location = new System.Drawing.Point(132, 33);
            this.btnHotKey.Name = "btnHotKey";
            this.btnHotKey.Size = new System.Drawing.Size(24, 23);
            this.btnHotKey.TabIndex = 2;
            this.btnHotKey.Text = "...";
            this.btnHotKey.Click += new System.EventHandler(this.btnHotKey_Click);
            // 
            // txtHotKey
            // 
            this.txtHotKey.EditValue = "";
            this.txtHotKey.Location = new System.Drawing.Point(9, 35);
            this.txtHotKey.Name = "txtHotKey";
            this.txtHotKey.Properties.Appearance.BackColor = System.Drawing.Color.White;
            this.txtHotKey.Properties.Appearance.Options.UseBackColor = true;
            this.txtHotKey.Properties.ReadOnly = true;
            this.txtHotKey.Size = new System.Drawing.Size(117, 20);
            this.txtHotKey.TabIndex = 1;
            this.txtHotKey.DoubleClick += new System.EventHandler(this.txtHotKey_DoubleClick);
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(9, 15);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(76, 13);
            this.labelControl3.TabIndex = 0;
            this.labelControl3.Text = "Hot Key Assign:";
            // 
            // panelControl4
            // 
            this.panelControl4.Controls.Add(this.labelControl2);
            this.panelControl4.Controls.Add(this.ddlColor);
            this.panelControl4.Location = new System.Drawing.Point(5, 103);
            this.panelControl4.Name = "panelControl4";
            this.panelControl4.Size = new System.Drawing.Size(163, 33);
            this.panelControl4.TabIndex = 2;
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(11, 9);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(29, 13);
            this.labelControl2.TabIndex = 1;
            this.labelControl2.Text = "Color:";
            // 
            // ddlColor
            // 
            this.ddlColor.EditValue = System.Drawing.Color.Empty;
            this.ddlColor.Location = new System.Drawing.Point(49, 6);
            this.ddlColor.Name = "ddlColor";
            this.ddlColor.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlColor.Size = new System.Drawing.Size(107, 20);
            this.ddlColor.TabIndex = 0;
            this.ddlColor.EditValueChanged += new System.EventHandler(this.ddlColor_EditValueChanged);
            // 
            // panelControl2
            // 
            this.panelControl2.Controls.Add(this.txtName);
            this.panelControl2.Controls.Add(this.labelControl1);
            this.panelControl2.Location = new System.Drawing.Point(5, 6);
            this.panelControl2.Name = "panelControl2";
            this.panelControl2.Size = new System.Drawing.Size(163, 58);
            this.panelControl2.TabIndex = 0;
            // 
            // txtName
            // 
            this.txtName.EditValue = "";
            this.txtName.Location = new System.Drawing.Point(6, 27);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(150, 20);
            this.txtName.TabIndex = 1;
            this.txtName.EditValueChanging += new DevExpress.XtraEditors.Controls.ChangingEventHandler(this.txtName_EditValueChanging);
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(10, 8);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(82, 13);
            this.labelControl1.TabIndex = 0;
            this.labelControl1.Text = "Hot Button Name";
            // 
            // btnApply
            // 
            this.btnApply.Location = new System.Drawing.Point(607, 429);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(75, 23);
            this.btnApply.TabIndex = 1;
            this.btnApply.Text = "&Apply";
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(688, 429);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 2;
            this.btnOK.Text = "&OK";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(769, 429);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "&Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // panelContainer
            // 
            this.panelContainer.Controls.Add(this.panelSign);
            this.panelContainer.Controls.Add(this.scrBar);
            this.panelContainer.Location = new System.Drawing.Point(184, 9);
            this.panelContainer.Name = "panelContainer";
            this.panelContainer.Size = new System.Drawing.Size(660, 414);
            this.panelContainer.TabIndex = 4;
            // 
            // panelSign
            // 
            this.panelSign.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panelSign.Location = new System.Drawing.Point(5, 5);
            this.panelSign.Name = "panelSign";
            this.panelSign.Size = new System.Drawing.Size(630, 404);
            this.panelSign.TabIndex = 1;
            // 
            // scrBar
            // 
            this.scrBar.Dock = System.Windows.Forms.DockStyle.Right;
            this.scrBar.Location = new System.Drawing.Point(641, 2);
            this.scrBar.Name = "scrBar";
            this.scrBar.Size = new System.Drawing.Size(17, 410);
            this.scrBar.TabIndex = 0;
            this.scrBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.scrBar_Scroll);
            // 
            // HotButtonSettingForm
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(850, 459);
            this.Controls.Add(this.panelContainer);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.panelControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "HotButtonSettingForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HotButton Setting";
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).EndInit();
            this.panelControl3.ResumeLayout(false);
            this.panelControl3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rdoSize.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl5)).EndInit();
            this.panelControl5.ResumeLayout(false);
            this.panelControl5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtHotKey.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl4)).EndInit();
            this.panelControl4.ResumeLayout(false);
            this.panelControl4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ddlColor.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).EndInit();
            this.panelControl2.ResumeLayout(false);
            this.panelControl2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelContainer)).EndInit();
            this.panelContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelSign)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.RadioGroup rdoSize;
        private DevExpress.XtraEditors.PanelControl panelControl2;
        private DevExpress.XtraEditors.TextEdit txtName;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.PanelControl panelControl4;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.ColorEdit ddlColor;
        private DevExpress.XtraEditors.PanelControl panelControl5;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraEditors.SimpleButton btnApply;
        private DevExpress.XtraEditors.SimpleButton btnOK;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.PanelControl panelContainer;
        private SmallButtonControl btnSmall;
        private LargeButtonControl btnLarge;
        private DevExpress.XtraEditors.PanelControl panelControl3;
        private DevExpress.XtraEditors.LabelControl labelControl4;
        private DevExpress.XtraEditors.TextEdit txtHotKey;
        private DevExpress.XtraEditors.SimpleButton btnHotKey;
        private DevExpress.XtraEditors.VScrollBar scrBar;
        private DevExpress.XtraEditors.PanelControl panelSign;
    }
}