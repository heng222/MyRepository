namespace ProWrite.UI.Controls.Dashboard
{
    partial class UserDetailForm
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
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.rdgRole = new DevExpress.XtraEditors.RadioGroup();
            this.lblPrivilegeLevel = new System.Windows.Forms.Label();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.lblName = new System.Windows.Forms.Label();
            this.txtName = new DevExpress.XtraEditors.TextEdit();
            ((System.ComponentModel.ISupportInitialize)(this.rdgRole.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtName.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(223, 185);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(53, 22);
            this.btnCancel.TabIndex = 26;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // rdgRole
            // 
            this.rdgRole.EditValue = "FileTransfer";
            this.rdgRole.Location = new System.Drawing.Point(115, 48);
            this.rdgRole.Name = "rdgRole";
            this.rdgRole.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.RadioGroupItem[] {
            new DevExpress.XtraEditors.Controls.RadioGroupItem("None", "None"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("Default", "Default"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("Administrator", "Administrator"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("All", "All"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("Commands", "Commands"),
            new DevExpress.XtraEditors.Controls.RadioGroupItem("FileTransfer", "File Transter")});
            this.rdgRole.Size = new System.Drawing.Size(179, 122);
            this.rdgRole.TabIndex = 24;
            // 
            // lblPrivilegeLevel
            // 
            this.lblPrivilegeLevel.AutoSize = true;
            this.lblPrivilegeLevel.Location = new System.Drawing.Point(26, 96);
            this.lblPrivilegeLevel.Name = "lblPrivilegeLevel";
            this.lblPrivilegeLevel.Size = new System.Drawing.Size(79, 13);
            this.lblPrivilegeLevel.TabIndex = 22;
            this.lblPrivilegeLevel.Text = "Privilege Level:";
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(156, 185);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(51, 22);
            this.btnSave.TabIndex = 25;
            this.btnSave.Text = "Save";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // lblName
            // 
            this.lblName.AutoSize = true;
            this.lblName.Location = new System.Drawing.Point(68, 15);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(38, 13);
            this.lblName.TabIndex = 21;
            this.lblName.Text = "Name:";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(115, 12);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(180, 20);
            this.txtName.TabIndex = 19;
            // 
            // UserDetailForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(332, 225);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.rdgRole);
            this.Controls.Add(this.lblPrivilegeLevel);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.lblName);
            this.Controls.Add(this.txtName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "UserDetailForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "User Detail";
            ((System.ComponentModel.ISupportInitialize)(this.rdgRole.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtName.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.RadioGroup rdgRole;
        private System.Windows.Forms.Label lblPrivilegeLevel;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private System.Windows.Forms.Label lblName;
        private DevExpress.XtraEditors.TextEdit txtName;

    }
}