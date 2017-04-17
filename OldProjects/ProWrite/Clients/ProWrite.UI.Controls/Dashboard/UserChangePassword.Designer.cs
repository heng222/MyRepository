namespace ProWrite.UI.Controls.Dashboard
{
    partial class UserChangePassword
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
            this.lblRePwd = new System.Windows.Forms.Label();
            this.lblPwd = new System.Windows.Forms.Label();
            this.txtRePWD = new DevExpress.XtraEditors.TextEdit();
            this.txtPWD = new DevExpress.XtraEditors.TextEdit();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.txtRePWD.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPWD.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // lblRePwd
            // 
            this.lblRePwd.AutoSize = true;
            this.lblRePwd.Location = new System.Drawing.Point(17, 67);
            this.lblRePwd.Name = "lblRePwd";
            this.lblRePwd.Size = new System.Drawing.Size(94, 13);
            this.lblRePwd.TabIndex = 27;
            this.lblRePwd.Text = "Repeat Password:";
            // 
            // lblPwd
            // 
            this.lblPwd.AutoSize = true;
            this.lblPwd.Location = new System.Drawing.Point(55, 30);
            this.lblPwd.Name = "lblPwd";
            this.lblPwd.Size = new System.Drawing.Size(56, 13);
            this.lblPwd.TabIndex = 26;
            this.lblPwd.Text = "Password:";
            // 
            // txtRePWD
            // 
            this.txtRePWD.Location = new System.Drawing.Point(120, 64);
            this.txtRePWD.Name = "txtRePWD";
            this.txtRePWD.Properties.ExportMode = DevExpress.XtraEditors.Repository.ExportMode.DisplayText;
            this.txtRePWD.Properties.PasswordChar = '*';
            this.txtRePWD.Size = new System.Drawing.Size(180, 20);
            this.txtRePWD.TabIndex = 25;
            // 
            // txtPWD
            // 
            this.txtPWD.Location = new System.Drawing.Point(120, 27);
            this.txtPWD.Name = "txtPWD";
            this.txtPWD.Properties.PasswordChar = '*';
            this.txtPWD.Size = new System.Drawing.Size(180, 20);
            this.txtPWD.TabIndex = 24;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(77, 109);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 28;
            this.btnSave.Text = "Save";
            this.btnSave.Click += new System.EventHandler(btnSave_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(199, 109);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 29;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(btnCancel_Click);
            // 
            // UserChangePassword
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 144);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.lblRePwd);
            this.Controls.Add(this.lblPwd);
            this.Controls.Add(this.txtRePWD);
            this.Controls.Add(this.txtPWD);
            this.Name = "UserChangePassword";
            this.Text = "UserChangePassword";
            this.ShowIcon = false;
            ((System.ComponentModel.ISupportInitialize)(this.txtRePWD.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtPWD.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private System.Windows.Forms.Label lblRePwd;
        private System.Windows.Forms.Label lblPwd;
        private DevExpress.XtraEditors.TextEdit txtRePWD;
        private DevExpress.XtraEditors.TextEdit txtPWD;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
    }
}