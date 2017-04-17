namespace ProWrite.UI.Controls
{
    partial class MessageSaveForm
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
            this.sbtnSave = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.txtModelName = new DevExpress.XtraEditors.TextEdit();
            this.lblTitle = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.txtModelName.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // sbtnSave
            // 
            this.sbtnSave.Location = new System.Drawing.Point(56, 73);
            this.sbtnSave.Name = "sbtnSave";
            this.sbtnSave.Size = new System.Drawing.Size(75, 23);
            this.sbtnSave.TabIndex = 1;
            this.sbtnSave.Click += new System.EventHandler(this.sbtnSave_Click);
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.Location = new System.Drawing.Point(137, 73);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(75, 23);
            this.sbtnCancel.TabIndex = 2;
            this.sbtnCancel.Click += new System.EventHandler(this.sbtnCancel_Click);
            // 
            // txtModelName
            // 
            this.txtModelName.Location = new System.Drawing.Point(12, 38);
            this.txtModelName.Name = "txtModelName";
            this.txtModelName.Properties.MaxLength = 30;
            this.txtModelName.Size = new System.Drawing.Size(200, 20);
            this.txtModelName.TabIndex = 0;
            this.txtModelName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtModelName_KeyPress);
            this.txtModelName.KeyUp += new System.Windows.Forms.KeyEventHandler(this.txtModelName_KeyUp);
            // 
            // lblTitle
            // 
            this.lblTitle.Location = new System.Drawing.Point(12, 12);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(0, 13);
            this.lblTitle.TabIndex = 3;
            // 
            // MessageSaveForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(224, 98);
            this.Controls.Add(this.lblTitle);
            this.Controls.Add(this.txtModelName);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.sbtnSave);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MessageSaveForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            ((System.ComponentModel.ISupportInitialize)(this.txtModelName.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton sbtnSave;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.TextEdit txtModelName;
        private DevExpress.XtraEditors.LabelControl lblTitle;

    }
}